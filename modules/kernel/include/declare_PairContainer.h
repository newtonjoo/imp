/**
 *  \file IMP/declare_PairContainer.h
 *  \brief A container for Pairs.
 *
 *  WARNING This file was generated from declare_NAMEContainer.hpp
 *  in tools/maintenance/container_templates/kernel
 *  by tools/maintenance/make-container.
 *
 *  Copyright 2007-2012 IMP Inventors. All rights reserved.
 */

#ifndef IMPKERNEL_DECLARE_PAIR_CONTAINER_H
#define IMPKERNEL_DECLARE_PAIR_CONTAINER_H

#include "kernel_config.h"
#include "internal/IndexingIterator.h"
#include "declare_Particle.h"
#include "container_base.h"
#include "internal/container_helpers.h"
#include "DerivativeAccumulator.h"
#include "internal/OwnerPointer.h"
#include "ParticleTuple.h"
#include <IMP/base/ref_counted_macros.h>
#include <IMP/base/check_macros.h>
#include <IMP/base/Pointer.h>
#include <IMP/base/InputAdaptor.h>
#include <IMP/base/utility_macros.h>


IMP_BEGIN_NAMESPACE
class PairModifier;
class PairDerivativeModifier;
class PairScore;

//! A shared container for Pairs
/** Stores a searchable shared collection of Pairs.
    \headerfile PairContainer.h "IMP/PairContainer.h"
    \implementationwithoutexample{PairContainer, IMP_PAIR_CONTAINER}
 */
class IMPEXPORT PairContainer : public Container
{
  IMP_PROTECTED_CONSTRUCTOR(PairContainer, (Model *m,
                           std::string name="PairContainer %1%"), );
public:
  typedef ParticlePair ContainedType;
  typedef ParticlePairsTemp ContainedTypes;
  typedef ParticleIndexPairs ContainedIndexTypes;
  typedef ParticleIndexPair ContainedIndexType;
  /** \note This function may be linear. Be aware of the complexity
      bounds of your particular container.
   */
  virtual bool get_contains_particle_pair(const ParticlePair& v) const =0;

  ParticlePairsTemp get_particle_pairs() const {
    return IMP::internal::get_particle(get_model(),
                                       get_indexes());
  }
#ifndef IMP_DOXGEN
  //! return the number of Pairs in the container
  /** \note this isn't always constant time
   */
  virtual unsigned int get_number_of_particle_pairs() const {
    return get_number();
  }
  /** Return the ith ParticlePair of the container.*/
  virtual ParticlePair get_particle_pair(unsigned int i) const {
    return get(i);
  }

#endif

  //! Apply a SingletonModifier to the contents
  virtual void apply(const PairModifier *sm) const=0;
  //! Apply a SingletonModifier to the contents
  virtual void apply(const PairDerivativeModifier *sm,
                     DerivativeAccumulator &da) const=0;

  //! Evaluate a score on the contents
  virtual double evaluate(const PairScore *s,
                          DerivativeAccumulator *da) const=0;

  //! Evaluate a score on the contents
  virtual double evaluate_if_good(const PairScore *s,
                                  DerivativeAccumulator *da,
                                  double max) const=0;

#ifndef IMP_DOXYGEN
  ParticlePair get(unsigned int i) const {
    return IMP::internal::get_particle(get_model(),
                                       get_indexes()[i]);
  }
  ParticlePairsTemp get() const {
    return IMP::internal::get_particle(get_model(),
                                       get_indexes());
  }
  /** Return true if the container contains the passed ParticlePair.*/
  bool get_contains(const ParticlePair& v) const {
    return get_contains_particle_pair(v);
  }
  /** Return true if the container contains the passed ParticlePair.*/
  virtual bool get_contains_index(ParticleIndexPair v) const {
    return get_contains_particle_pair(IMP::internal
                                     ::get_particle(get_model(),
                                                    v));
  }
  unsigned int get_number() const {return get_indexes().size();}
  virtual ParticleIndexPairs get_indexes() const=0;
  virtual ParticleIndexPairs get_all_possible_indexes() const=0;
#ifndef SWIG
  virtual bool get_provides_access() const {return false;}
  virtual const ParticleIndexPairs& get_access() const {
    IMP_THROW("Object not implemented properly.", base::IndexException);
  }


  template <class Modifier>
  void template_apply(const Modifier *sm,
                      DerivativeAccumulator &da) const {
    apply(sm, da);
  }
  template <class Modifier>
      void template_apply(const Modifier *sm) const {
    apply(sm);
  }
  template <class Score>
      double template_evaluate(const Score *s,
                               DerivativeAccumulator *da) const {
    return evaluate(s, da);
  }
  template <class Score>
      double template_evaluate_if_good(const Score *s,
                                       DerivativeAccumulator *da,
                                       double max) const {
    return evaluate_if_good(s, da, max);
  }


#endif
#endif

  IMP_REF_COUNTED_NONTRIVIAL_DESTRUCTOR(PairContainer);
};


/** This class allows either a list or a container to be
    accepted as input.
*/
class IMPEXPORT PairContainerAdaptor:
#if !defined(SWIG) && !defined(IMP_DOXYGEN)
public base::Pointer<PairContainer>
#else
public base::InputAdaptor
#endif
{
  typedef base::Pointer<PairContainer> P;
 public:
  PairContainerAdaptor(){}
  PairContainerAdaptor(PairContainer *c);
  template <class C>
  PairContainerAdaptor(base::internal::PointerBase<C> c): P(c){}
  PairContainerAdaptor(const ParticlePairsTemp &t,
                          std::string name="PairContainerAdaptor%1%");
};


IMP_END_NAMESPACE

#endif  /* IMPKERNEL_DECLARE_PAIR_CONTAINER_H */
