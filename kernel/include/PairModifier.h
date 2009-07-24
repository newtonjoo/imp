/**
 *  \file PairModifier.h    \brief A Modifier on ParticlePairs
 *
 *  This file is generated by a script (core/tools/make-container).
 *  Do not edit directly.
 *
 *  Copyright 2007-9 Sali Lab. All rights reserved.
 */

#ifndef IMP_PAIR_MODIFIER_H
#define IMP_PAIR_MODIFIER_H

#include "config.h"
#include "internal/kernel_version_info.h"
#include "internal/container_helpers.h"
#include "DerivativeAccumulator.h"
#include "base_types.h"
#include "VectorOfRefCounted.h"

IMP_BEGIN_NAMESPACE
// to keep swig happy
class Particle;

//! A base class for modifiers of ParticlePairs
/** The primary function of such a class is to change
    the passed particles. You can use the associated PairFunction
    along with \c map or \c std::for_each to easily apply a
    PairModifier to a set of ParticlePairs.

    \see IMP::PairFunctor
 */
class IMPEXPORT PairModifier : public Object
{
public:
  PairModifier();

  /** Apply the function to a single value*/
  virtual void apply(Particle *a, Particle *b,
                     DerivativeAccumulator &da) const=0;

  /** Apply the function to a single value*/
  virtual void apply(Particle *a, Particle *b) const=0;

  /** Print out information about the function, ending in a newline.*/
  virtual void show(std::ostream &out = std::cout) const=0;

  /** return information about the authors */
  virtual VersionInfo get_version_info() const = 0;

  IMP_REF_COUNTED_DESTRUCTOR(PairModifier);
};

IMP_OUTPUT_OPERATOR(PairModifier)


//! A collection
typedef VectorOfRefCounted<PairModifier*> PairModifiers;

//! Create a functor which can be used with build in C++ and python commands
/** For example, you can do
    \code
    std::for_each(particles.begin(), particles.end(),
                  IMP::SingletonFunctor(new IMP::core::Transform(tr)));
    IMP::for_each(particles,
                  IMP::SingletonFunctor(new IMP::core::Transform(tr)));
    \endcode
    in C++ (the second can be used with when \c particles is a temporary
    value) or
    \verbatim
    map(particles, SingletonFunctor(Transform(tr)))
    \endverbatim
    in python.

    \see IMP::PairModifier
 */
class PairFunctor {
  Pointer<const PairModifier> f_;
  DerivativeAccumulator *da_;
public:
  //! Store the PairModifier and the optional DerivativeAccumulator
  PairFunctor(const PairModifier *f): f_(f), da_(NULL){}
  PairFunctor(const PairModifier *f,
                   DerivativeAccumulator *da): f_(f), da_(da){
    IMP_check(da_, "The passed derivative accumulator should not be null.",
              InvalidStateException);
  }
  void operator()( ParticlePair p) const {
    if (da_) {
      IMP::internal::ContainerTraits<ParticlePair>::apply(f_.get(), p, da_);
    } else {
      IMP::internal::ContainerTraits<ParticlePair>::apply(f_.get(), p);
    }
  }
};


IMP_END_NAMESPACE

#endif  /* IMP_PAIR_MODIFIER_H */
