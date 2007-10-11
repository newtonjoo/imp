import modeller
import modeller.optimizers
import IMP
import IMP.modeller_intf

# intialize Modeller
modeller.log.level(0,0,0,0,0)
env = modeller.environ()
env.io.atom_files_directory = '../data/'
env.edat.dynamic_sphere = False
env.libs.topology.read(file='$(LIB)/top_heav.lib')
env.libs.parameters.read(file='$(LIB)/par.lib')

# get particles for Modeller
modeller_model = modeller.model(env, file='./particles.pdb')
atoms = modeller_model.atoms

# intialize particles for IMP
imp_model = IMP.Model()
print "adding particles"
particles = []
IMP.modeller_intf.Init_IMP_From_Modeller(imp_model, particles, atoms)

# create a restraint set
rs = IMP.Restraint_Set("dist_rsrs")
imp_model.add_restraint_set(rs)

# add Modeller restraints
rsr = modeller_model.restraints
rsr.add(modeller.forms.gaussian(group=modeller.physical.xy_distance,
                          feature=modeller.features.distance(atoms[1], atoms[2]),
                          mean=5., stdev=0.1))

# make Modeller restraints accessible to IMP
r = IMP.modeller_intf.Modeller_Restraints(imp_model, modeller_model, particles)
print "adding Modeller restraints"
rs.add_restraint(r)

# create IMP restraints
score_func = IMP.Harmonic()
dist_rsr = IMP.RSR_Distance(imp_model, particles[0], particles[2], 5.0, 0.1, score_func)
print "adding IMP restraints"
rs.add_restraint(dist_rsr)

IMP.modeller_intf.Show_Modeller_and_IMP(atoms, particles)

print "run optimizer"
steepest_descent = IMP.Steepest_Descent()
steepest_descent.optimize(imp_model, 10)

IMP.modeller_intf.Show_Modeller_and_IMP(atoms, particles)

IMP.modeller_intf.Show_Distances(particles)
