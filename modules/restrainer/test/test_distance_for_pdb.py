import sys
import os
import unittest
import IMP
import IMP.test
import IMP.restrainer

class RestraintTest(IMP.test.TestCase):
    def setUp(self):
        IMP.test.TestCase.setUp(self)

        RepParser = IMP.restrainer.XMLRepresentation(self.get_input_file_name('pdb_representation.xml'))
        RestraintParser = IMP.restrainer.XMLRestraint(self.get_input_file_name('pdb_distance_restraint.xml'))

        self.representation = RepParser.run()
        self.restraint = RestraintParser.run()

        self.Model = self.representation.to_model()
        self.restraint.add_to_representation(self.representation)


    def test_show(self):
        """Check distance restraint for pdb"""

        restraint_name = 'distance_restraint'
        r = self.restraint.get_restraint_by_name(restraint_name)

        r.imp_restraint.evaluate(False)
        self.Model.show()
        self.Model.evaluate(False)

if __name__ == '__main__':
    unittest.main()
