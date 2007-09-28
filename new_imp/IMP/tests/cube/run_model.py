import modeller
import modeller.optimizers

# set the appropriate search path
import sys

sys.path.append("../../")
sys.path.append("../python_libs/")
import IMP_Modeller_Intf
import imp2
import load_imp_xml_model

model = imp2.Model()

# load document from an XML file
doc = load_imp_xml_model.load_imp_model(model, "gold_model.xml")

# intialize Modeller
modeller.log.level(0,0,0,0,0)
env = modeller.environ()
env.io.atom_files_directory = "../data/"
env.edat.dynamic_sphere = False
env.libs.topology.read(file="$(LIB)/top_heav.lib")
env.libs.parameters.read(file="$(LIB)/par.lib")


# add IMP model and restraints as an energy term to Modeller model
t = env.edat.energy_terms
t.append(IMP_Modeller_Intf.IMP_Restraints(model, model.particles))
        
# get particles for Modeller
mdl = IMP_Modeller_Intf.Create_Particles_From_IMP(env, model)


atmsel = modeller.selection(mdl)
atoms = mdl.atoms
score = 10000.0
num_runs = 0
opt = modeller.optimizers.conjugate_gradients()
md = modeller.optimizers.molecular_dynamics()
while score > 10.0 and num_runs < 1000:
    atmsel.randomize_xyz(deviation=100.0)
    
    # comment out if you do not want to save the trajectory
    # model.set_up_trajectory("trajectory.txt");
    
    print "initial opt ..."
    new_mdl = opt.optimize (atmsel, max_iterations=20, actions=None)
    e = atmsel.energy()
    score = e[0]
    print score
    
    print "heating ..."
    temp = 100
    while temp <= 1000:
        new_mdl = md.optimize(atmsel, max_iterations=1, temperature=temp, actions=None, md_return='MINIMAL', init_velocities=False)
        temp += 20
        
    e = atmsel.energy()
    score = e[0]
    print score

    print "cooling ..."
    while temp >= 10:
        new_mdl = md.optimize(atmsel, max_iterations=1, temperature=temp, actions=None, md_return='MINIMAL', init_velocities=False)
        temp -= 3

    e = atmsel.energy()
    score = e[0]
    print score

    print "stabilizing ..."
    new_mdl = md.optimize(atmsel, max_iterations=50, temperature=temp, actions=None, md_return='MINIMAL', init_velocities=False)

    e = atmsel.energy()
    score = e[0]
    print score

    print "settling ..."
    new_mdl = opt.optimize (atmsel, max_iterations=250, actions=None)
    e = atmsel.energy()
    
    e = atmsel.energy()
    score = e[0]
    print score

    num_runs = num_runs+1
    
    score = e[0]
    if score < 30.0:
        fname = "out" + str(score) + ".pdb"
        mdl.write(file=fname, model_format="PDB")

    print num_runs, score
    
IMP_Modeller_Intf.Show_Distances(model.particles)
mdl.write(file="out.pdb", model_format="PDB")

