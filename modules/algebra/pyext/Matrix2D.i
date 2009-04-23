%ignore IMP::algebra::Matrix2D::operator=;

/* Provide our own implementations for some operators */
%ignore IMP::algebra::Matrix2D::operator+=;
%ignore IMP::algebra::Matrix2D::operator-=;
%ignore IMP::algebra::Matrix2D::operator*=;
%ignore IMP::algebra::Matrix2D::operator/=;

/* Ignore friend operators */
%ignore operator+(const T& X, const This& a1);
%ignore operator-(const T& X, const This& a1);
%ignore operator*(const T& X, const This& a1);
%ignore operator/(const T& X, const This& a1);

// Matrix2D
%include "IMP/algebra/MultiArray.h"
%include "IMP/algebra/Matrix2D.h"

/* Make sure that we return the original Python object from C++ inplace
   operators (not a new Python proxy around the same C++ object) */
namespace IMP {
 namespace algebra {
  %feature("shadow") Matrix2D::__iadd__ %{
    def __iadd__(self, *args):
        $action(self, *args)
        return self
  %}
  %feature("shadow") Matrix2D::__imul__ %{
    def __imul__(self, *args):
        $action(self, *args)
        return self
  %}
  %feature("shadow") Matrix2D::__idiv__ %{
    def __idiv__(self, *args):
        $action(self, *args)
        return self
  %}
  %feature("shadow") Matrix2D::__isub__ %{
    def __isub__(self, *args):
        $action(self, *args)
        return self
  %}
 }
}

// Extend Matrix2D with _internal_get and _internal_set
%extend IMP::algebra::Matrix2D<double> {
  double _internal_get(int j, int i) const {
    return self->operator()(j,i);
  }
  void _internal_set(int j, int i, double val) {
    self->operator()(j,i) = val;
  }

  /* Ignore any C++ return value from inplace operators, so that SWIG does not
     generate a new SWIG wrapper for the return value (see above). */
  void __iadd__(const Matrix2D<double> &x) { self->operator+=(x); }
  void __iadd__(double x) { self->operator+=(x); }
  void __imul__(const Matrix2D<double> &x) { self->operator*=(x); }
  void __imul__(double x) { self->operator*=(x); }
  void __idiv__(const Matrix2D<double> &x) { self->operator/=(x); }
  void __idiv__(double x) { self->operator/=(x); }
  void __isub__(const Matrix2D<double> &x) { self->operator-=(x); }
  void __isub__(double x) { self->operator-=(x); }

  // Compose the python calls to _internal_get and _internal_set
  %pythoncode {
    def __setitem__(self, indx, val):
      self._internal_set(indx[0], indx[1], val)
    def __getitem__(self, indx):
      return self._internal_get(indx[0], indx[1])
  }
}

// Instantiating the templates for Python
namespace IMP {
 namespace algebra {
   %template() ::boost::multi_array<double,2>;
   %template(MultiArray2D) ::IMP::algebra::MultiArray<double,2>;
   %template(_Matrix2D) ::IMP::algebra::Matrix2D<double>;
 }
}

// Cannot instantiate Matrix2D directly, since SWIG complains about an
// attempt to redefine the template class; so rename it in the Python layer
%pythoncode {
  Matrix2D = _Matrix2D
}
