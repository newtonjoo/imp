/**
 *  \file CLASSNAMEModifier.h    \brief A Modifier on PLURALVARIABLETYPE
 *
 *  This file is generated by a script (core/tools/make-container).
 *  Do not edit directly.
 *
 *  Copyright 2007-2011 IMP Inventors. All rights reserved.
 */

#ifndef IMP_HEADERNAME_MODIFIER_H
#define IMP_HEADERNAME_MODIFIER_H

#include "kernel_config.h"
#include "DerivativeAccumulator.h"
#include "base_types.h"
#include "ParticleTuple.h"
#include "internal/container_helpers.h"

IMP_BEGIN_NAMESPACE
// to keep swig happy
class Particle;

//! A base class for modifiers of PLURALVARIABLETYPE
/** The primary function of such a class is to change
    the passed particles.

    \see IMP::CLASSNAMEFunctor

    Implementors should see IMP_HEADERNAME_MODIFIER(). Also see
    CLASSNAMEDerivativeModifier.
 */
class IMPEXPORT CLASSNAMEModifier : public Object
{
public:
  typedef VARIABLETYPE Argument;
  CLASSNAMEModifier(std::string name="CLASSNAMEModifier %1%");

  /** Apply the function to a single value*/
  virtual void apply(ARGUMENTTYPE) const =0;

 /** Apply the function to a single value*/
  virtual void apply_index(Model *m, PASSINDEXTYPE v) const {
    apply(internal::get_particle(m, v));
  }

  /** Apply the function to a collection of PLURALVARIABLETYPE */
  virtual void apply_indexes(Model *m, const PLURALINDEXTYPE &o) const {
    for (unsigned int i=0; i < o.size(); ++i) {
      apply_index(m, o[i]);
    }
  }

  /** Get the set of particles read when applied to the arguments.*/
  virtual ParticlesTemp
    get_input_particles(Particle* p) const =0;
  /** Get the set of particles modifier when applied to the arguments.*/
  virtual ParticlesTemp
    get_output_particles(Particle *p) const =0;
  /** Get the set of input containers when this modifier is applied to
      the arguments. */
  virtual ContainersTemp
    get_input_containers(Particle *p) const =0;
  /** Get the set of output containers when this modifier is applied to
      the arguments. */
  virtual ContainersTemp
    get_output_containers(Particle *p) const =0;
};

IMP_OUTPUT_OPERATOR(CLASSNAMEModifier);

#ifdef IMP_DOXYGEN
/** Create a modifier from a functor. C++ only. The function should take
    a CLASSNAME as an argument.
    This is intended to be used as a temporary object and not stored.
    A reference to the functor is saved.
 */
template <class Functor>
CLASSNAMEModifier *create_FUNCTIONNAME_modifier(const Functor& f);
#elif !defined(SWIG)
template <class Functor>
class FunctorCLASSNAMEModifier: public CLASSNAMEModifier {
  const Functor &f_;
public:
  FunctorCLASSNAMEModifier(const Functor& f):
    CLASSNAMEModifier("FunctorModifier %1%"),
    f_(f){}
  IMP_HEADERNAME_MODIFIER(FunctorCLASSNAMEModifier);
};

template <class Functor>
void FunctorCLASSNAMEModifier<Functor>::apply(ARGUMENTTYPE v) const {
  f_(v);
}

template <class Functor>
 ParticlesTemp
FunctorCLASSNAMEModifier<Functor>::get_input_particles(Particle* p) const {
  return ParticlesTemp(1,p);
}
template <class Functor>
ParticlesTemp
FunctorCLASSNAMEModifier<Functor>::get_output_particles(Particle *p) const {
  return ParticlesTemp(1,p);
}
template <class Functor>
ContainersTemp
FunctorCLASSNAMEModifier<Functor>::get_input_containers(Particle *) const {
  return ContainersTemp();
}
template <class Functor>
ContainersTemp
FunctorCLASSNAMEModifier<Functor>::get_output_containers(Particle *) const {
  return ContainersTemp();
}

/** Create a modifier from a functor. C++ only.*/
template <class Functor>
inline FunctorCLASSNAMEModifier<Functor> *
create_FUNCTIONNAME_modifier(const Functor& f) {
  return new FunctorCLASSNAMEModifier<Functor>(f);
}

#endif

IMP_OBJECTS(CLASSNAMEModifier,CLASSNAMEModifiers);

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
    map(SingletonFunctor(Transform(tr)), particles)
    \endverbatim
    in python.

    \see IMP::CLASSNAMEModifier
 */
class CLASSNAMEFunctor {
  Pointer<const CLASSNAMEModifier> f_;
public:
  //! Store the CLASSNAMEModifier and the optional DerivativeAccumulator
  CLASSNAMEFunctor(const CLASSNAMEModifier *f): f_(f){}
  void operator()( VARIABLETYPE p) const {
    f_->apply(p);
  }
};



IMP_END_NAMESPACE

#endif  /* IMP_HEADERNAME_MODIFIER_H */
