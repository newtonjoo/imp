# NOTE: This file is generated from modules/core/tools/container_tempates/test.py
# do not edit.


import unittest
import IMP
import IMP.test
import IMP.core
import IMP.container
import math




class SingletonTestModifier(IMP.SingletonModifier):
    def __init__(self, k):
        IMP.SingletonModifier.__init__(self)
        self.k=k
    def do_show(self, fh):
        fh.write("Test Particle")
    def apply(self, a0, a1=None):
        if str(type(a0)) == "<class 'IMP.Particle'>":
            if a0.has_attribute(self.k):
                pass
            else:
                a0.add_attribute(self.k, 1)
        else:
            for p in a0:
                self.apply(p, a1)
    def get_version_info(self):
        return 1
    def get_input_particles(self, p):
        return IMP.ParticlesTemp([p])
    def get_output_particles(self, p):
        return IMP.ParticlesTemp([p])


class PairTestModifier(IMP.PairModifier):
    def __init__(self, k):
        IMP.PairModifier.__init__(self)
        self.k=k
    def do_show(self, fh):
        fh.write("Test Particle")
    def apply(self, a0, a2=None):
        for p in a0:
            if type(p) == tuple:
                for q in p:
                    if not q.has_attribute(self.k):
                        q.add_attribute(self.k, 1)
            else:
                if not p.has_attribute(self.k):
                    p.add_attribute(self.k, 1)
    def get_version_info(self):
        return 1
    def get_input_particles(self, p):
        return IMP.ParticlesTemp([p[0],p[1]])
    def get_output_particles(self, p):
        return IMP.ParticlesTemp([p[0],p[1]])


def particle_has_attribute(p, k):
    return p.has_attribute(k)

def particle_pair_has_attribute(p, k):
    return p[0].has_attribute(k) and p[1].has_attribute(k)

def particle_triplet_has_attribute(p, k):
    return p[0].has_attribute(k) and p[1].has_attribute(k) and p[2].has_attribute(k)

# This file is generated by the make-container script

class ParticleContainerTest(IMP.test.TestCase):
    """Tests for SingletonContainer related objects"""

    def create_particle(self,m):
        p= IMP.Particle(m)
        p.add_attribute(IMP.FloatKey("thekey"), float(1))
        return p

    def create_particle_pair(self,m):
        p0= IMP.Particle(m)
        p1= IMP.Particle(m)
        d0= IMP.core.XYZ.setup_particle(p0)
        d1= IMP.core.XYZ.setup_particle(p1)
        d0.set_coordinates(IMP.algebra.Vector3D(0,0,1))
        d1.set_coordinates(IMP.algebra.Vector3D(0,0,0))
        return IMP.ParticlePair(p0,p1)

    def same(self, a,b):
        return a.get_name() == b.get_name()

    def create_singleton_score_state(self, f, a, t):
        return IMP.core.SingletonConstraint(f, a, t)

    def create_pair_score_state(self, f, a, t):
        return IMP.core.PairConstraint(f, a, t)

    def create_particle_score(self):
        uf= IMP.core.Linear(0,1)
        return IMP.core.AttributeSingletonScore(uf,IMP.FloatKey("thekey"))

    def create_particle_pair_score(self):
        uf= IMP.core.Linear(0,1)
        return IMP.core.DistancePairScore(uf)

    def test_set(self):
        """Testing SingletonsConstraint"""
        # write increment an int field
        # call evaluate and check that it is incremented
        IMP.set_log_level(IMP.VERBOSE)
        print "start"
        m= IMP.Model()
        print "hi"
        c= IMP.container.ListSingletonContainer(m)
        cs=[]
        for i in range(0,30):
            t=self.create_particle(m)
            c.add_particle(t)
            cs.append(t)
        print "dl"
        k= IMP.IntKey("thevalue")
        f= SingletonTestModifier(k)
        print "apply"
        s= IMP.container.SingletonsConstraint(c, f, None)
        print "add"
        m.add_score_state(s)
        m.evaluate(False)
        for p in cs:
            self.assert_(particle_has_attribute(p, k))
        print "done"

    def test_sset(self):
        """Testing SingletonConstraint"""
        # write increment an int field
        # call evaluate and check that it is incremented
        IMP.set_log_level(IMP.VERBOSE)
        print "start"
        m= IMP.Model()
        print "hi"
        t=self.create_particle(m)
        print "dl"
        k= IMP.IntKey("thevalue")
        f= SingletonTestModifier(k)
        print "apply"
        s= self.create_singleton_score_state(f, None, t)
        m.add_score_state(s)
        print "add"
        m.evaluate(False)
        self.assert_(particle_has_attribute(t, k))
        print "done"

if __name__ == '__main__':
    unittest.main()
