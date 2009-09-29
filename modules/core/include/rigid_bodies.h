/**
 *  \file core/rigid_bodies.h
 *  \brief functionality for defining rigid bodies
 *
 *  Copyright 2007-9 Sali Lab. All rights reserved.
 */

#ifndef IMPCORE_RIGID_BODIES_H
#define IMPCORE_RIGID_BODIES_H

#include "config.h"
#include "internal/rigid_bodies.h"

#include "XYZ.h"
#include "XYZR.h"
#include <IMP/SingletonContainer.h>
#include <IMP/SingletonModifier.h>
#include <IMP/Refiner.h>
#include <IMP/ScoreState.h>
#include <IMP/algebra/Vector3D.h>
#include <IMP/algebra/Rotation3D.h>
#include <IMP/algebra/Transformation3D.h>

IMPCORE_BEGIN_NAMESPACE


class RigidMember;
class UpdateRigidBodyOrientation;
class AccumulateRigidBodyDerivatives;
class UpdateRigidBodyMembers;

typedef Decorators<RigidMember, XYZs> RigidMembers;

//! A decorator for a rigid body
/** A rigid body's orientation is stored using a transformation that
    takes a set of internal coordinates for the member particles
    to the current location of the member particles.

    The body is modeled as a collection of balls of radius and mass
    given by the RigidBodyTraits. I, the inertial tensor, is
    computed and diagonalized, but not stored. It can be stored if
    someone wants it.

    \note In \imp, a rigid body is associated with two, possibly
    identical, sets of particles
    - those particles which transform rigidly along with the rigid
    body, namely the members. The members are accessed through
    methods on the decorator.
    - those particles who make up the detailed representation of
    the rigid body, namely the representation. These are accessed
    through an associated Refiner. If the RigidMembersRefiner is
    used, the two sets are identical.

    It is often desirable to randomize the orientation of a rigid
    body:
    \verbinclude randomize_rigid_body.py

    \see RigidMember
    \see AccumulateRigidBodyDerivatives
    \see UpdateRigidBodyMembers
    \see UpdateRigidBodyOrientation
 */
class IMPCOREEXPORT RigidBody: public XYZ {
#ifndef SWIG
  friend class AccumulateRigidBodyDerivatives;
  friend class UpdateRigidBodyOrientation;
  friend class UpdateRigidBodyMembers;
#endif
  //! Return the location of a member particle given the current position
  /** This method computes the coordinates of p given its internal coordinates
      and the current position and orientation of the rigid body.
   */
  algebra::Vector3D get_coordinates(RigidMember p) const;
public:

  RigidMembers get_members() const;

  IMP_DECORATOR(RigidBody, XYZ)

  //! Create a new rigid body, but do not add score states
  /** \param[in] p The particle to make into a rigid body
      \param[in] members The particles to use as members of the rigid body

      The initial position and orientation of p is computed, as are the
      relative positions of the member particles. The member particles
      do not already need to be RigidMember particles, only
      XYZ particles.

      Use the function IMP::core::create_rigid_body() to create the needed
      score states in order to keep the rigid body rigid.
   */
  static RigidBody setup_particle(Particle *p,
                          const XYZs &members);

  ~RigidBody();

  //!Return true of the particle is a rigid body
  static bool particle_is_instance(Particle *p) {
    return internal::get_has_required_attributes_for_body(p);
  }

  // swig doesn't support using, so the method is wrapped
  //! Get the coordinates of the particle
  algebra::Vector3D get_coordinates() const {
    return XYZ::get_coordinates();
  }

  //! Get the transformation implied by the rigid body
  IMP::algebra::Transformation3D get_transformation() const;

  //! Set the current orientation and translation
  /** All members of the rigid body will have their coordinates updated.
      See lazy_set_transformation() if you can weight until evaluate for
      that.
   */
  void set_transformation(const IMP::algebra::Transformation3D &tr);

  //! Change the transformation, but let the score state update the members
  /** See set_transformation()
   */
  void lazy_set_transformation(const IMP::algebra::Transformation3D &tr);

  bool get_coordinates_are_optimized() const;

  //! Set whether the rigid body coordinates are optimized
  void set_coordinates_are_optimized(bool tf,
                                     bool snapping=false);

  //! Normalized the quaternion
  void normalize_rotation();

  //! Get the derivatives of the quaternion
  algebra::VectorD<4> get_rotational_derivatives() const;

  unsigned int get_number_of_members() const;

  RigidMember get_member(unsigned int i) const;
};

IMP_OUTPUT_OPERATOR(RigidBody);

typedef Decorators<RigidBody, XYZs> RigidBodies;

//! A decorator for a particle that is part of a rigid body
/**
   \see RigidBody
 */
class IMPCOREEXPORT RigidMember: public XYZ {
 public:
  IMP_DECORATOR(RigidMember, XYZ);

  //! Return the current orientation of the body
  algebra::Vector3D get_internal_coordinates() const {
    return algebra::Vector3D(get_particle()
                    ->get_value(internal::rigid_body_data().child_keys_[0]),
                    get_particle()
                    ->get_value(internal::rigid_body_data().child_keys_[1]),
                    get_particle()
                    ->get_value(internal::rigid_body_data().child_keys_[2]));
  }

  //! set the internal coordinates for this member
  void set_internal_coordinates(const algebra::Vector3D &v) const {
    get_particle()->set_value(internal::rigid_body_data().child_keys_[0],
                              v[0]);
    get_particle()->set_value(internal::rigid_body_data().child_keys_[1],
                              v[1]);
    get_particle()->set_value(internal::rigid_body_data().child_keys_[2],
                              v[2]);
  }

  //! set the coordinates of the body
  // this is here since swig does like using statements
  void set_coordinates(const algebra::Vector3D &center) {
    XYZ::set_coordinates(center);
  }

  //! Set the coordinates from the internal coordinates
  void set_coordinates(const algebra::Transformation3D &tr) {
    set_coordinates(tr.transform(get_internal_coordinates()));
  }
  ~RigidMember();

  //! return true if it is a rigid member
  static bool particle_is_instance(Particle *p) {
    return internal::get_has_required_attributes_for_member(p);
  }
};

IMP_OUTPUT_OPERATOR(RigidMember);

//! Compute the orientation of the rigid body from the refined particles
/** This should be applied before evaluate to keep the bodies rigid. It
    computes the optimal orientation given the position of the members and
    then snaps the members to their rigid locations. You can
    use the setup_rigid_bodies and setup_rigid_body methods instead of
    creating these objects yourself.
    \see setup_rigid_bodies
    \see setup_rigid_body
    \verbinclude rigid_bodies.py

    \see RigidBody
*/
class IMPCOREEXPORT UpdateRigidBodyOrientation: public SingletonModifier {
 public:
  UpdateRigidBodyOrientation(){}
  IMP_SINGLETON_MODIFIER(UpdateRigidBodyOrientation,
                         get_module_version_info());
};

//! Accumulate the derivatives from the refined particles in the rigid body
/** You can
    use the setup_rigid_bodies and setup_rigid_body methods instead of
    creating these objects yourself.
    \see setup_rigid_bodies
    \see setup_rigid_body
    \see RigidBody
    \verbinclude rigid_bodies.py
    \see UpdateRigidBodyMembers
 */
class IMPCOREEXPORT AccumulateRigidBodyDerivatives:
  public SingletonModifier {
 public:
  AccumulateRigidBodyDerivatives(){}
  IMP_SINGLETON_MODIFIER_DA(AccumulateRigidBodyDerivatives,
                            get_module_version_info());
};


//! Compute the coordinates of the RigidMember objects bases on the orientation
/** This should be applied after evaluate to keep the bodies rigid. You can
    use the setup_rigid_bodies and setup_rigid_body methods instead of
    creating these objects yourself.
    \see setup_rigid_bodies
    \see setup_rigid_body
    \see RigidBody
    \see AccumulateRigidBodyDerivatives */
class IMPCOREEXPORT UpdateRigidBodyMembers: public SingletonModifier {
 public:
  UpdateRigidBodyMembers(){}
  IMP_SINGLETON_MODIFIER(UpdateRigidBodyMembers,
                         get_module_version_info());
};


//! A refiner which returns the members of a rigid body
/** You can use this to easily define a rigid body when you want the
    set of particles representing a rigid body to be the same as the
    set of members.
 */
class IMPCOREEXPORT RigidMembersRefiner: public Refiner {
 public:
  RigidMembersRefiner(){}
  IMP_SIMPLE_REFINER(RigidMembersRefiner, get_module_version_info());
};

IMPCORE_END_NAMESPACE

#endif  /* IMPCORE_RIGID_BODIES_H */
