from __future__ import print_function
import IMP
import IMP.test
import IMP.atom
import IMP.core
import io


class Tests(IMP.test.TestCase):

    def test_read(self):
        """Check reading a mol2 file containing small molecules"""
        m = IMP.kernel.Model()

        #! read Mol2
        root_d = IMP.atom.read_mol2(
            self.get_input_file_name("1d3d-ligands.mol2"),
            m, IMP.atom.AllMol2Selector())

        print("number of particles")
        print(m.get_number_of_particles())
        print(len(IMP.atom.get_by_type(root_d, IMP.atom.ATOM_TYPE)))
        self.assertEqual(
            146, len(IMP.atom.get_by_type(root_d, IMP.atom.ATOM_TYPE)))
        m2 = io.BytesIO()
        IMP.atom.write_mol2(root_d, m2)

        pdb = io.BytesIO()
        IMP.atom.write_pdb(root_d, pdb)
        # print m2.getvalue()
        # print pdb
        return

    def test_write(self):
        """Check that a mol2-created hierarchy can be written to a PDB"""
        m = IMP.kernel.Model()

        #! read Mol2
        root_d = IMP.atom.read_mol2(
            self.get_input_file_name("1d3d-ligands.mol2"),
            m, IMP.atom.AllMol2Selector())
        print("number of particles")
        print(m.get_number_of_particles())
        print(len(IMP.atom.get_by_type(root_d, IMP.atom.ATOM_TYPE)))
        self.assertEqual(
            146, len(IMP.atom.get_by_type(root_d, IMP.atom.ATOM_TYPE)))

        pdb = io.BytesIO()
        IMP.atom.write_pdb(root_d, pdb)
        print(pdb.getvalue())
        return

        m2 = IMP.kernel.Model()
        root_d2 = IMP.atom.read_mol2(
            self.get_input_file_name("1d3d-ligands.mol2"),
            m2, IMP.atom.NonhydrogenMol2Selector())

        print("number of particles")
        print(m2.get_number_of_particles())

        IMP.atom.write_file(root_d2, self.get_tmp_file_name("2.mol2"))
        IMP.atom.write_file(root_d2, self.get_tmp_file_name("2.pdb"))

    def test_hao(self):
        """Check that written mol2s look right"""
        m = IMP.kernel.Model()

        #! read Mol2
        root_d = IMP.atom.read_mol2(
            self.get_input_file_name("1d3d-ligands.mol2"),
            m, IMP.atom.AllMol2Selector())
        out = io.BytesIO()
        IMP.atom.write_mol2(root_d, out)
        testout = open(
            self.get_input_file_name(
                "1d3d-ligands.out1.mol2"),
            "rb").read(
        )
        # print out.getvalue()
        # print " vs "
        # print testout
        self.assertEqual(out.getvalue(), testout)

        m = IMP.kernel.Model()
        root_d = IMP.atom.read_mol2(
            self.get_input_file_name("1d3d-ligands.mol2"),
            m, IMP.atom.NonHydrogenMol2Selector())
        print("test 2")
        print("number of particles")
        print(m.get_number_of_particles())

        out = io.BytesIO()
        IMP.atom.write_mol2(root_d, out)
        testout = open(
            self.get_input_file_name(
                "1d3d-ligands.out2.mol2"),
            "rb").read(
        )
        # print out.getvalue()
        # print " vs "
        # print testout
        self.assertEqual(out.getvalue(), testout)

if __name__ == '__main__':
    IMP.test.main()
