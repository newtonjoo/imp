# NOTE: This file is generated from modules/core/tools/container_tempates/test.py
# do not edit.

from __future__ import print_function
import IMP
import IMP.test
import IMP.core
import IMP.container
import math


# This file is generated by the make-container script

class ClassnameContainerTest(IMP.test.TestCase):

    """Tests for ClassnameContainer related objects"""

    def create_particle(self, m):
        p = IMP.kernel.Particle(m)
        d = IMP.core.XYZ.setup_particle(p)
        d.set_coordinates(IMP.algebra.get_random_vector_in(
            IMP.algebra.get_unit_bounding_box_3d()))
        p.add_attribute(IMP.FloatKey("thekey"), d.get_x())
        return p

    def create_particle_pair(self, m):
        p0 = IMP.kernel.Particle(m)
        p1 = IMP.kernel.Particle(m)
        d0 = IMP.core.XYZ.setup_particle(p0)
        d1 = IMP.core.XYZ.setup_particle(p1)
        d0.set_coordinates(IMP.algebra.get_random_vector_in(
            IMP.algebra.get_unit_bounding_box_3d()))
        d1.set_coordinates(IMP.algebra.get_random_vector_in(
            IMP.algebra.get_unit_bounding_box_3d()))
        return (p0, p1)

    def create_singleton_score(self):
        uf = IMP.core.Linear(0, 1)
        return IMP.core.AttributeSingletonScore(uf, IMP.FloatKey("thekey"))

    def create_pair_score(self):
        uf = IMP.core.Linear(0, 1)
        return IMP.core.DistancePairScore(uf)

    def create_singleton_restraint(self, ps, p):
        return IMP.core.SingletonRestraint(ps, p)

    def create_pair_restraint(self, ps, p):
        return IMP.core.PairRestraint(ps, (p[0], p[1]))

    def test_restraint(self):
        """Test the ClassnamesRestraint"""
        m = IMP.kernel.Model()
        gs = self.create_CLASSFUNCTIONNAME_score()
        c = IMP.container.ListClassnameContainer(m)
        f = 0
        for i in range(0, 10):
            p = self.create_FUNCTIONNAME(m)
            f = f + gs.evaluate(p, None)
            c.add_FUNCTIONNAME(p)
        r = IMP.container.ClassnamesRestraint(gs, c)
        r.set_was_used(True)
        m.add_restraint(r)
        self.assertAlmostEqual(m.evaluate(False), f, delta=.1 * f)
        self.assertAlmostEqual(m.evaluate(False), f, delta=.1 * f)
        p = self.create_FUNCTIONNAME(m)
        f = f + gs.evaluate(p, None)
        c.add_FUNCTIONNAME(p)
        self.assertAlmostEqual(m.evaluate(False), f, delta=.1 * f)
        self.assertAlmostEqual(m.evaluate(False), f, delta=.1 * f)

    def test_srestraint(self):
        """Test the ClassnameRestraint"""
        m = IMP.kernel.Model()
        gs = self.create_CLASSFUNCTIONNAME_score()
        p = self.create_FUNCTIONNAME(m)
        f = gs.evaluate(p, None)
        r = self.create_CLASSFUNCTIONNAME_restraint(gs, p)
        r.set_was_used(True)
        m.add_restraint(r)
        self.assertAlmostEqual(m.evaluate(False), f, delta=.1 * f)

    def test_min_restraint(self):
        """Test the MinimumClassnameRestraint"""
        m = IMP.kernel.Model()
        c = IMP.container.ListClassnameContainer(m)
        self.assertEqual(c.get_ref_count(), 1)
        for i in range(0, 10):
            c.add_FUNCTIONNAME(self.create_FUNCTIONNAME(m))
        print(c.get_number_of_FUNCTIONNAMEs())
        d = self.create_CLASSFUNCTIONNAME_score()
        self.assertEqual(d.get_ref_count(), 1)
        r = IMP.container.MinimumClassnameRestraint(d, c)
        self.assertEqual(d.get_ref_count(), 2)
        self.assertEqual(c.get_ref_count(), 2)
        r.set_n(4)
        m.add_restraint(r)
        f = m.evaluate(False)
        print(f)
        ms = []
        print(c.get_number_of_FUNCTIONNAMEs())
        for i in range(0, 10):
            ps = c.get_FUNCTIONNAME(i)
            cm = d.evaluate(ps, None)
            ms.append(cm)
        print(ms)
        ms.sort()
        mt = 0
        for i in range(0, 4):
            mt = mt + ms[i]
        print(mt)
        self.assertAlmostEqual(mt, f, delta=.1 * f)

    def test_min_score(self):
        """Test the MinimumClassnameScore"""
        m = IMP.kernel.Model()
        s = []
        for i in range(0, 5):
            s.append(IMP.kernel._ConstClassnameScore(i))
        ps = IMP.container.MinimumClassnameScore(s, 3)
        p = self.create_FUNCTIONNAME(m)
        ps.set_was_used(True)
        v = ps.evaluate(p, None)
        self.assertEqual(v, 3)

    def test_set(self):
        """Testing ClassnameContainerSet"""
        IMP.base.set_log_level(IMP.base.VERBOSE)
        m = IMP.kernel.Model()
        print("hi")
        c = IMP.container.ClassnameContainerSet(m)
        ls = []
        cs = []
        for i in range(0, 3):
            l = IMP.container.ListClassnameContainer(m)
            c.add_CLASSFUNCTIONNAME_container(l)
            for j in range(0, 3):
                t = self.create_FUNCTIONNAME(m)
                l.add_FUNCTIONNAME(t)
                cs.append(t)
        ret = c.get_contents()
        cs = IMP.get_indexes(cs)
        for pi in cs:
            self.assertIn(pi, ret)
        ret.sort(cmp)
        # print ret
        cs.sort(cmp)
        # rint cs
        self.assertEqual(len(ret), len(cs))
        for i in range(0, len(ret)):
            self.assertEqual(cmp(ret[i], cs[i]), 0)

if __name__ == '__main__':
    IMP.test.main()
