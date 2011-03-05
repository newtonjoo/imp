#!/usr/bin/env python
import sys,os

import IMP
import IMP.atom
import IMP.container
import IMP.saxs
import IMP.core
import IMP.isd
import IMP.isd.TBLReader
import IMP.isd.utils
from IMP.isd.Entry import Entry

from math import sqrt
from StringIO import StringIO

kB= (1.381 * 6.02214) / 4184.0

class sfo_common():
    """nonspecific methods used across all shared function objects.
    Rules: 
        - Their name starts with the name of the parent function (e.g.
                init_model_* )
        - they don't store anything in the class, but instead
                return all created objects. 
                Exceptions: the model, which is self._m
                            the statistics class, which is self.stat
        - they store what they have to store in the model (e.g. restraints)
        - they don't print out anything except for long routines (e.g. NOE
          parsing)
        - the prior RestraintSet is added to the model when it is created, so
          that when it is passed to another function, it is not added twice.
    """

    def hello(self):
        return "hello world"

    def set_checklevel(self,value):
        IMP.set_check_level(value)

    def set_loglevel(self,value):
        IMP.set_log_level(value)

    def m(self,name,*args,**kw):
        "wrapper to call methods of m"
        func=getattr(self._m,name)
        return func(*args, **kw)

    def init_model_base(self, wd):
        "moves to wd and creates model"
        os.chdir(wd)
        # Create an IMP model
        self._m = IMP.Model()

    def init_model_charmm_protein_and_ff(self, initpdb, top, par, selector, pairscore,
            ff_temp=300.0):
        """creates a CHARMM protein representation.  
        creates the charmm force field, bonded and nonbonded.
        - initpdb: initial structure in pdb format
        - top is a CHARMM top.lib
        - par is a CHARMM par.lib
        - selector is an instance of
            one of the selectors of IMP.atom, for example
            IMP.atom.NonWaterNonHydrogenPDBSelector(). 
        - pairscore is an instance of a Pair Score to score the interaction 
            between two atoms. usually, it's either
            LennardJonesDistancePairScore(0,1) or
            RepulsiveDistancePairScore(0,1)
        - ff_temp is the temperature at which the force field should be
          simulated.
        Returns: prot, ff, rsb, rs
            - prot: the protein
            - ff: the force field
            - rsb: the RestraintSet on bonded interactions
            - rs: the RestraintSet on nonbonded interactions. Both are weighted
              using ff_temp.
        """
        m=self._m
        prot = IMP.atom.read_pdb(initpdb, m, selector)
        if not prot.get_is_valid():
            raise ValueError, "invalid hierarchy!"
        # Read in the CHARMM heavy atom topology and parameter files
        ff = IMP.atom.CHARMMParameters(top,par)
        # equivalent:
        # ff = IMP.atom.get_heavy_atom_CHARMM_parameters()
        #
        # Using the CHARMM libraries, determine the ideal topology (atoms and their
        # connectivity) for the PDB file's primary sequence
        topology = ff.create_topology(prot)
        # Typically this modifies the C and N termini of each chain in the protein by
        # applying the CHARMM CTER and NTER patches. Patches can also be manually
        # applied at this point, e.g. to add disulfide bridges.
        topology.apply_default_patches()
        # Each atom is mapped to its CHARMM type. These are needed to look up bond
        # lengths, Lennard-Jones radii etc. in the CHARMM parameter file. Atom types
        # can also be manually assigned at this point using the CHARMMAtom decorator.
        topology.add_atom_types(prot)
        # Generate and return lists of bonds, angles, dihedrals and impropers for
        # the protein. Each is a Particle in the model which defines the 2, 3 or 4
        # atoms that are bonded, and adds parameters such as ideal bond length
        # and force constant. Note that bonds and impropers are explicitly listed
        # in the CHARMM topology file, while angles and dihedrals are generated
        # automatically from an existing set of bonds. These particles only define the
        # bonds, but do not score them or exclude them from the nonbonded list.
        bonds = topology.add_bonds(prot)
        angles = ff.create_angles(bonds)
        dihedrals = ff.create_dihedrals(bonds)
        impropers = topology.add_impropers(prot)
        # Maintain stereochemistry by scoring bonds, angles, dihedrals and impropers
        #
        # Score all of the bonds. This is done by combining IMP 'building blocks':
        # - A ListSingletonContainer simply manages a list of the bond particles.
        # - A BondSingletonScore, when given a bond particle, scores the bond by
        #   calculating the distance between the two atoms it bonds, subtracting the
        #   ideal value, and weighting the result by the bond's "stiffness", such that
        #   an "ideal" bond scores zero, and bonds away from equilibrium score non-zero.
        #   It then hands off to a UnaryFunction to actually penalize the value. In
        #   this case, a Harmonic UnaryFunction is used with a mean of zero, so that
        #   bond lengths are harmonically restrained.
        # - A SingletonsRestraint simply goes through each of the bonds in the
        #   container and scores each one in turn.
        rsb = IMP.RestraintSet('phys_bonded')
        cont = IMP.container.ListSingletonContainer(bonds, "bonds")
        bss = IMP.atom.BondSingletonScore(IMP.core.Harmonic(0, 1))
        rsb.add_restraint(IMP.container.SingletonsRestraint(bss, cont))
        # Score angles, dihedrals, and impropers. In the CHARMM forcefield, angles and
        # impropers are harmonically restrained, so this is the same as for bonds.
        # Dihedrals are scored internally by a periodic (cosine) function.
        cont = IMP.container.ListSingletonContainer(angles, "angles")
        bss = IMP.atom.AngleSingletonScore(IMP.core.Harmonic(0,1))
        rsb.add_restraint(IMP.container.SingletonsRestraint(bss, cont))
        #dihedrals
        cont = IMP.container.ListSingletonContainer(dihedrals, "dihedrals")
        bss = IMP.atom.DihedralSingletonScore()
        rsb.add_restraint(IMP.container.SingletonsRestraint(bss, cont))
        #impropers
        cont = IMP.container.ListSingletonContainer(impropers, "impropers")
        bss = IMP.atom.ImproperSingletonScore(IMP.core.Harmonic(0,1))
        rsb.add_restraint(IMP.container.SingletonsRestraint(bss, cont))
        rsb.set_weight(1.0/(kB*ff_temp))
        m.add_restraint(rsb)
        #
        # Add non-bonded interaction (in this case, Lennard-Jones). This needs to
        # know the radii and well depths for each atom, so add them from the forcefield
        # (they can also be assigned manually using the XYZR or LennardJones
        # decorators):
        ff.add_radii(prot)
        ff.add_well_depths(prot)
        # Get a list of all atoms in the protein, and put it in a container
        atoms = IMP.atom.get_by_type(prot, IMP.atom.ATOM_TYPE)
        cont = IMP.container.ListSingletonContainer(atoms)
        # Add a restraint for the Lennard-Jones interaction. Again, this is built from
        # a collection of building blocks. First, a ClosePairContainer maintains a list
        # of all pairs of Particles that are close. A StereochemistryPairFilter is used
        # to exclude atoms from this list that are bonded to each other or are involved
        # in an angle or dihedral (1-3 or 1-4 interaction). Then, a
        # LennardJonesPairScore scores a pair of atoms with the Lennard-Jones potential.
        # Finally, a PairsRestraint is used which simply applies the
        # LennardJonesPairScore to each pair in the ClosePairContainer.
        #non bonded list exclusion arguments: 0.0 distance cutoff = vdw contact
        #2.5 slack (recompute nbl if atoms have moved more than 2.5 angstrom)
        nbl = IMP.container.ClosePairContainer(cont, 0.0,2.5)
        pair_filter = IMP.atom.StereochemistryPairFilter()
        pair_filter.set_bonds(bonds)
        pair_filter.set_angles(angles)
        pair_filter.set_dihedrals(dihedrals)
        nbl.add_pair_filter(pair_filter)
        #should weight the ff restraint by a temperature, set to 300K.
        pr = IMP.container.PairsRestraint(pairscore, nbl)
        rs = IMP.RestraintSet('phys')
        rs.add_restraint(pr)
        rs.set_weight(1.0/(kB*ff_temp))
        m.add_restraint(rs)
        return prot, ff, rsb, rs

    def init_model_setup_scale(self, default, lower=-1, upper=-1):
        """sets up a Scale particle to the initial default value. It can
        optionnally be constrained between two positive bounds, or else its
        range  is 0 to infinity.
        """
        m=self._m
        scale = IMP.isd.Scale.setup_particle(IMP.Particle(m),default,lower,upper)
        #constrain it also for the optimizers
        if lower != -1 or upper != -1:
            m.add_score_state(IMP.core.SingletonConstraint(
                            IMP.isd.ScaleRangeModifier(),None,scale))
        return scale

    def init_model_jeffreys(self, scales, prior_rs=None):
        """given a list of scales, returns a RestraintSet('prior') with weight
        1.0 that contains a list of JeffreysRestraint on each scale.
        If argument prior_rs is used, add them to that RestraintSet instead.
        """
        if not prior_rs:
            prior_rs = IMP.RestraintSet('prior')
            self._m.add_restraint(prior_rs)
            prior_rs.set_weight(1.0)
        for i in scales:
            prior_rs.add_restraint(IMP.isd.JeffreysRestraint(i))
        return prior_rs

    def find_atom(self, atom, prot):
        """scans the prot hierarchy and tries to find atom = (resno, name)
        assumes that resno starts at 0"""
        try:
            sel=IMP.atom.Selection(hierarchy=prot,
                residue_index=atom[0]+1,
                atom_type=IMP.atom.AtomType(atom[1])
                ).get_selected_particles()
            if len(sel) > 1:
                print "found multiple atoms for atom %d %s!" % (r2,at2)
                return
            p0=IMP.core.XYZ(sel[0])
        except:
            print "atom %d %s not found" % (r2,at2)
            return
        return p0

    def init_model_NOE_restraint(self, prot, atoms, distance, sigma, gamma):
        """
        Sets up a lognormal distance restraint using the given sigma and gamma.
        Returns the restraint.
        assumes atoms = (atom1, atom2)
        where atom1 is (resno, atomname) and resno starts at 0.
        """
        #find corresponding atoms
        p0=self.find_atom(atoms[0], prot)
        p1=self.find_atom(atoms[1], prot)
        #create lognormal restraint using gamma_data = 1
        return IMP.isd.NOERestraint(p0,p1,sigma,gamma,distance**(-6))

    def init_model_ambiguous_NOE_restraint(self, contributions, distance, 
            sigma, gamma):
        """Reads an ambiguous NOE restraint. contributions is a list of
        (atom1, atom2) pairs, where atom1 is (resno, atomname) and resno starts
        at 0.  Sets up a lognormal distance restraint using the given sigma and
        gamma.  
        Returns the restraint.
        """
        raise NotImplementedError

    def init_model_NOEs(self, prot, seqfile, tblfile, name='NOE', prior_rs=None,
            bounds_sigma=(1.0,0.1,100), bounds_gamma=(1.0,0.1,100)):
        """read TBL file and store NOE restraints, using one sigma and one gamma
        for the whole dataset. Creates the necessary uninformative priors.
        - prot: protein hierarchy
        - seqfile: a file with 3-letter sequence
        - tblfile: a TBL file with the restraints
        - name: an optional name for the restraintset
        - prior_rs: when not None, add new sigma and gamma to this 
                    RestraintSet instance.
        - bounds_sigma or gamma: tuple of (initial value, lower, upper bound)
            bounds can be -1 to set to default range [0,+inf]
        Returns: data_rs, prior_rs, sigma, gamma
        """
        #prior
        sigma=self.init_model_setup_scale(*bounds_sigma)
        gamma=self.init_model_setup_scale(*bounds_gamma)
        prior_rs = self.init_model_jeffreys([sigma,gamma], prior_rs)
        #likelihood
        rs = IMP.RestraintSet(name)
        #use the TBLReader to parse the TBL file.
        sequence = IMP.isd.utils.read_sequence_file(seqfile)
        tblr = IMP.isd.TBLReader.TBLReader(sequence)
        restraints = tblr.read_distances(tblfile, 'NOE')['NOE']
        for i,restraint in enumerate(restraints):
            if i % 100 == 0:
               print i
            #a restraint is (contributions, dist, upper, lower, volume)
            #where contributions is a tuple of contributing pairs
            #and a pair is (c1, c2), where c1 is of the form (resno, atname)
            #residue numbers start at 0
            if len(restraint[0]) > 1:
                ln = self.init_model_ambiguous_NOE_restraint(prot, restraint[0],
                        restraint[1], sigma, gamma)
            else:
                ln = self.init_model_NOE_restraint(prot, restraint[0][0], 
                        restraint[1], sigma, gamma)
            rs.add_restraint(ln)
        print i, "NOE restraints read"
        #set weight of rs and add to model. 
        #Weight is 1.0 cause sigma particle already has this role.
        rs.set_weight(1.0)
        self._m.add_restraint(rs) 
        return rs, prior_rs, sigma, gamma

    def init_model_standard_SAXS_restraint(self, prot, profilefile, name='SAXS'):
        """read experimental SAXS profile and apply restraint the standard
        way (like foxs)
        Returns: a restraintset
        """
        rs = IMP.RestraintSet(name)
        saxs_profile = IMP.saxs.Profile(profilefile)
        particles = IMP.atom.get_by_type(prot, IMP.atom.ATOM_TYPE)
        saxs_restraint = IMP.saxs.Restraint(particles, saxs_profile)
        rs.add_restraint(saxs_restraint)
        rs.set_weight(1.0)
        self._m.add_restraint(rs)
        return rs

    def _setup_md(self,prot, temperature=300.0, thermostat='berendsen',
            coupling=500, md_restraints=None, timestep=1.0, recenter=1000,
            momentum=1000):
        """setup molecular dynamics
        - temperature: target temperature
        - thermostat: one of 'NVE', rescale_velocities',
                                'berendsen', 'langevin'
        - coupling: coupling constant (tau (fs) for berendsen, 
                                        gamma (/fs) for langevin)
        - md_restraints: if not None, specify the terms of the energy to be used
                            during the md steps via a list of restraints.
        - timestep: in femtoseconds.
        - recenter: recenter the molecule every so many steps (Langevin only)
        - momentum: remove angular momentum every so many steps (Berendsen only)
        Returns: an instance of md and an instance of an OptimizerState (the
        thermostat), or None if NVE.
        """
        ## Molecular Dynamics (from MAX BONOMI)
        md=IMP.atom.MolecularDynamics()
        md.set_model(self._m)
        md.assign_velocities(temperature)
        md.set_time_step(timestep)
        if thermostat == 'NVE':
            os = None
        elif thermostat == 'rescale_velocities':
            os=IMP.atom.VelocityScalingOptimizerState(
                    IMP.atom.get_leaves(prot), temperature, 0)
            md.add_optimizer_state(os)
        elif thermostat == 'berendsen':
            os=IMP.atom.BerendsenThermostatOptimizerState(
                    IMP.atom.get_leaves(prot), temperature, coupling)
            md.add_optimizer_state(os)
            mom = IMP.atom.RemoveRigidMotionOptimizerState(
                    IMP.atom.get_leaves(prot), momentum)
            md.add_optimizer_state(mom)
        elif thermostat == 'langevin':
            os=IMP.atom.LangevinThermostatOptimizerState(
                    IMP.atom.get_leaves(prot), temperature, coupling)
            md.add_optimizer_state(os)
            cen = IMP.atom.RemoveTranslationOptimizerState(
                    IMP.atom.get_leaves(prot), recenter)
            md.add_optimizer_state(cen)
        else:            
            raise NotImplementedError, thermostat

        if md_restraints:
            md.set_restraints(md_restraints)

        return md, os

    def _setup_normal_mover(self, particle, floatkey, stepsize):
        """setup NormalMover to move particle's floatkey attribute
        by a gaussian with standard deviation 'stepsize'
        Returns: mover instance.
        """
        cont=IMP.container.ListSingletonContainer(self._m)
        cont.add_particle(particle)
        nm=IMP.core.NormalMover(cont,
                IMP.FloatKeys([floatkey]),stepsize)
        return nm

    def _setup_md_mover(self, md, particles, temperature, n_md_steps=10):
        """setup MDMover using md and particles.
        - md: md instance
        - particles: particles to move, usually the leaves of the protein
          hierarchy
        - n_md_steps: number of md steps to perform on each move
        Returns: mover instance.
        """
        cont=IMP.container.ListSingletonContainer(self._m)
        cont.add_particles(particles)
        return IMP.atom.MDMover(cont, md, temperature, n_md_steps)

    def _setup_mc(self, mover, temperature=300.0, mc_restraints=None):
        """setup monte carlo using a certain mover.
        - mover: mover to use, NormalMover or MDMover usually.
        - temperature: target temperature.
        - mc_restraints: if not None, list of restraints for the metropolis
          criterion.
        Returns: mc instance.
        """
        mc = IMP.core.MonteCarlo(self._m)
        #why is this returning an int?
        mc.add_mover(mover)
        #set same temp as MD, careful with units
        mc.set_temperature(kB*temperature)
        #allow to go uphill
        mc.set_return_best(False)
        #update all particles each time
        mc.set_move_probability(1.0)
        if mc_restraints:
            #tell mc to only use restraints involving the particle
            mc.set_restraints(mc_restraints)
        return mc

    def init_simulation_setup_protein_hmc(self, prot, temperature=300.0,
            thermostat='berendsen', coupling=500, n_md_steps=10,
            md_restraints=None, mc_restraints=None, timestep=1.0):
        """setup hybrid monte-carlo on protein.
        - prot: protein hierarchy.
        - temperature: target temperature.
        - thermostat: one of 'NVE', rescale_velocities',
                                'berendsen', 'langevin'
        - coupling: coupling constant (tau (fs) for berendsen, 
                                        gamma (/fs) for langevin)
        - n_md_steps: number of md steps per mc step
        - md_restraints: if not None, specify the terms of the energy to be used
                            during the md steps.
        - mc_restraints: if not None, use these energy terms for the metropolis
                            criterion.
        - timestep: time step for md, in femtoseconds.
        Returns: hmc, mdmover, md and OptimizerState (thermostat)
        """
        md, os = self._setup_md(prot, temperature=temperature,
                thermostat=thermostat, coupling=coupling,
                md_restraints=md_restraints, timestep=timestep)
        particles=IMP.atom.get_by_type(prot, IMP.atom.ATOM_TYPE)
        mdmover = self._setup_md_mover(md, particles, temperature, n_md_steps)
        hmc = self._setup_mc(mdmover, temperature, mc_restraints)
        return hmc, mdmover, md, os

    def init_simulation_setup_scale_mc(self, scale, temperature=300.0,
            mc_restraints=None, floatkey=IMP.FloatKey("scale"), nm_stepsize=0.1):
        """sets up monte carlo on scale, at a certain target temperature,
        optionnally using a certain set of restraints only.
        - scale: scale particle
        - temperature: target temperature
        - mc_restraints: optional set of restraints from which the energy should
          be drawn instead of the energy of the complete system.
        - floatkey: the floatkey to move.
        - nm_stepsize: the stepsize of the normal mover
        Returns: mc instance, nm instance.
        """
        nm = self._setup_normal_mover(scale, floatkey, nm_stepsize)
        mc = self._setup_mc(nm, temperature, mc_restraints)
        return mc, nm

    def _mc_and_update_nm(self, nsteps, mc, nm, stats_key, 
            adjust_stepsize=True):
        """run mc using a normal mover on a single particle, 
        update stepsize and store nsteps, acceptance and stepsize in the
        statistics instance self.stat by using the key stats_key.
        """
        before = mc.get_number_of_forward_steps()
        #do the monte carlo
        mc.optimize(nsteps)
        after = mc.get_number_of_forward_steps()
        #increment the counter for this simulation
        self.stat.increment_counter(stats_key, nsteps)
        #get the acceptance rate, stepsize
        accept = float(after-before)/nsteps
        self.stat.update(stats_key, 'acceptance', accept)
        stepsize = nm.get_sigma()
        self.stat.update(stats_key, 'stepsize', stepsize)
        #update stepsize if needed and requested
        if adjust_stepsize:
            if 0.4 < accept < 0.6:
                return
            if accept < 0.05:
                accept = 0.05
            if accept > 1.0:
                accept = 1.0
            nm.set_sigma(stepsize*2*accept)

    def _hmc_and_update_md(self, nsteps, hmc, mv, stats_key,
            adjust_stepsize=True):
        """run hmc, update stepsize and print statistics. Updates number of MD
        steps to reach a target acceptance between 0.4 and 0.6, sends
        statistics to self.stat. MD steps are always at least 10 and at most 500.
        """
        before = hmc.get_number_of_forward_steps()
        hmc.optimize(nsteps)
        after = hmc.get_number_of_forward_steps()
        self.stat.increment_counter(stats_key, nsteps)
        accept = float(after-before)/nsteps
        self.stat.update(stats_key, 'acceptance', accept)
        mdsteps = mv.get_nsteps()
        self.stat.update(stats_key, 'n_md_steps', mdsteps)
        if adjust_stepsize:
            if 0.4 < accept < 0.6:
                return
            mdsteps = int(mdsteps *2**(accept-0.5))
            if mdsteps > 500:
                mdsteps = 500
            if mdsteps < 10:
                mdsteps = 10
            mv.set_nsteps(mdsteps)

    def get_pdb(self, prot):
        """returns a string corresponding to the pdb structure of hierarchy
        prot.
        """
        output = StringIO()
        output.write('MODEL\n')
        IMP.atom.write_pdb(prot, output)
        output.write('ENDMDL\n')
        return output.getvalue()

    def get_netcdf(self, prot):
        raise NotImplementedError

    def do_md_protein_statistics(self, md_key, nsteps, md_instance, 
            temperature=300.0, prot_coordinates=None):
        """updates statistics for md simulation: target temp, kinetic energy,
        kinetic temperature, writes coordinates and increments counter.
        - md_key: stats md key
        - nsteps: number of steps performed.
        - md_instance: instance of the MolecularDynamics class.
        - temperature: target temperature
        - prot_coordinates: protein coordinates to be passed to the stats class,
          (should be a string)
        """
        self.stat.update(md_key, 'target_temp', temperature)
        kinetic = md_instance.get_kinetic_energy()
        self.stat.update(md_key, 'E_kinetic', kinetic)
        self.stat.update(md_key, 'instant_temp', 
                         md_instance.get_kinetic_temperature(kinetic))
        self.stat.update_coordinates(md_key, 'protein', prot_coordinates)
        self.stat.increment_counter(md_key, nsteps)

    def init_stats_add_mc_category(self, stat, name='mc', coord='particle'):
        """shortcut for a frequent series of operations on MC simulations'
        statistics. Creates an entry for acceptance, stepsize and one
        coordinate set printed in the statistics file.
        """
        #create category
        mc_key = stat.add_category(name=name)
        #giving None as argument is a way to create a static entry.
        stat.add_entry(mc_key, entry=Entry('acceptance', '%10f', None))
        stat.add_entry(mc_key, entry=Entry('stepsize', '%10f', None))
        #special call to add coordinates to be dumped
        stat.add_entry(mc_key, entry=Entry(coord, '%10f', None))
        #add the counter to the output
        stat.add_entry(mc_key, name='counter')
        return mc_key

    def init_stats_add_md_category(self, stat, name='md', coord='protein'):
        """shortcut for a frequent series of operations on MD simulations'
        statistics. Creates an entry for target temp, instantaneous temp,
        kinetic energy, and one set of coordinates called 'protein' by 
        default.
        """
        #create category
        md_key = stat.add_category(name=name)
        #giving None as argument is a way to create a static entry.
        stat.add_entry(md_key, entry=Entry('target_temp', '%10f', None))
        stat.add_entry(md_key, entry=Entry('instant_temp', '%10f', None))
        stat.add_entry(md_key, entry=Entry('E_kinetic', '%10f', None))
        #special call to add coordinates to be dumped
        stat.add_coordinates(md_key, coord)
        #add the counter to the output
        stat.add_entry(md_key, name='counter')
        return md_key

    def init_stats_add_hmc_category(self, stat, name='hmc', coord='protein'):
        """shortcut for a frequent series of operations on HMC simulations'
        statistics. Adds acceptance, number of MD steps and a trajectory for
        a protein.
        """
        #create category
        hmc_key = stat.add_category(name=name)
        #giving None as argument is a way to create a static entry.
        stat.add_entry(hmc_key, entry=Entry('acceptance', '%10f', None))
        stat.add_entry(hmc_key, entry=Entry('n_md_steps', '%10d', None))
        #special call to add coordinates to be dumped
        stat.add_coordinates(hmc_key, coord)
        #add the counter to the output
        stat.add_entry(hmc_key, name='counter')
        return hmc_key

    def rescale_velocities(self, particles, factor):
        """rescale the velocities of a bunch of particles having vx vy and vz
        floatkeys
        """
        keys=[IMP.FloatKey("vx"), IMP.FloatKey("vy"), IMP.FloatKey("vz")]
        for p in particles:
            for k in keys:
                p.set_value(k, p.get_value(k)*factor)


