/**
 *  \file Vector3D.h   \brief Simple 3D vector class.
 *
 *  Copyright 2007-2010 Sali Lab. All rights reserved.
 *
 */

#ifndef IMPALGEBRA_VECTOR_3D_H
#define IMPALGEBRA_VECTOR_3D_H

#include <IMP/base_types.h>
#include <IMP/macros.h>
#include <IMP/exception.h>

#include <cmath>

#include "VectorD.h"

IMPALGEBRA_BEGIN_NAMESPACE

IMPALGEBRA_EXPORT_TEMPLATE(VectorD<3>);

/** \name 3D Vectors
    We provide a specialization of VectorD for 3-space and
    several additional functions on it.
    @{
*/

//! A location in 3D space
/** Stores a 3-vector using Cartesian coordinates.
*/
IMP_NO_SWIG(typedef VectorD<3> Vector3D;)


//! A collection of Vector3D
/**
 */
typedef std::vector<Vector3D> Vector3Ds;

//! Returns the vector product (cross product) of two vectors.
/** \relatesalso Vector3D
 */
inline Vector3D vector_product(const Vector3D& p1, const Vector3D& p2) {
  return Vector3D(p1[1]*p2[2]-p1[2]*p2[1],
                  p1[2]*p2[0]-p1[0]*p2[2],
                  p1[0]*p2[1]-p1[1]*p2[0]);
}
//! Return a vector that is perpendicular to the given vector
/** Or, if you are Israeli, it is a vertical vector.
    \relatesalso Vector3D
*/
inline Vector3D orthogonal_vector(const Vector3D &v) {
  if (v[0] != 0) {
    return Vector3D((-v[1]-v[2])/v[0],1,1);
  } else if (v[1] != 0.0) {
    return Vector3D(1,(-v[0]-v[2])/v[1],1);
  } else if (v[2] != 0.0) {
    return Vector3D(1,1,(-v[0]-v[1])/v[2]);
  } else {
    return Vector3D(0.0,0.0,0.0);
  }
}

//! Returns the centroid of a set of vectors
/** \relatesalso Vector3D
 */
inline Vector3D centroid(const Vector3Ds &ps) {
 Vector3D cen(0.0,0.0,0.0);
 for (unsigned long i=0;i<ps.size();++i) {
   cen = cen + ps[i];
 }
 return cen/ps.size();
}

/** @} */
/** \genericgeometry */
inline const Vector3D &get_geometry(const Vector3D &v) {
  return v;
}

IMPALGEBRA_END_NAMESPACE

#endif  /* IMPALGEBRA_VECTOR_3D_H */
