/**
 *  \file IMP/SingletonModifier.h
 *  \brief A Modifier on ParticlesTemp
 *
 *  WARNING This file was generated from NAMEModifier.hpp
 *  in tools/maintenance/container_templates/kernel
 *  by tools/maintenance/make-container.
 *
 *  Copyright 2007-2012 IMP Inventors. All rights reserved.
 */

#ifndef IMPKERNEL_SINGLETON_MODIFIER_H
#define IMPKERNEL_SINGLETON_MODIFIER_H

#include "kernel_config.h"
#include "DerivativeAccumulator.h"
#include "base_types.h"
#include "ParticleTuple.h"
#include "internal/container_helpers.h"

IMP_BEGIN_NAMESPACE

//! A base class for modifiers of ParticlesTemp
/** The primary function of such a class is to change
    the passed particles.

    \see IMP::SingletonFunctor

    Implementors should see IMP_SINGLETON_MODIFIER(). Also see
    SingletonDerivativeModifier.
 */
class IMPEXPORT SingletonModifier : public base::Object
{
public:
  typedef Particle* Argument;
  typedef ParticleIndex IndexArgument;
  SingletonModifier(std::string name="SingletonModifier %1%");

  /** Apply the function to a single value*/
  virtual void apply(Particle*) const =0;

 /** Apply the function to a single value*/
  virtual void apply_index(Model *m, ParticleIndex v) const {
    apply(internal::get_particle(m, v));
  }

  /** Apply the function to a collection of ParticlesTemp */
  virtual void apply_indexes(Model *m, const ParticleIndexes &o) const {
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



IMP_END_NAMESPACE

#endif  /* IMPKERNEL_SINGLETON_MODIFIER_H */
