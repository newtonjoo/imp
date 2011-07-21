/**
 *  \file FixedRefiner.cpp
 *  \brief XXXX.
 *
 *  Copyright 2007-2011 IMP Inventors. All rights reserved.
 *
 */

#include "IMP/core/FixedRefiner.h"
#include <IMP/log.h>


IMPCORE_BEGIN_NAMESPACE

IMP_LIST_IMPL(FixedRefiner, Particle, particle, Particle*,Particles);

FixedRefiner::FixedRefiner(const Particles &ps): Refiner("FixedRefiner%d"){
  IMP_LOG(VERBOSE, "Created fixed particle refiner with " << ps.size()
          << " particles" << std::endl);
  set_particles(ps);
}

void FixedRefiner::do_show(std::ostream &out) const {
  out << "producing " << get_number_of_particles() << " particles"
      << std::endl;
}

bool FixedRefiner::get_can_refine(Particle *) const {
  return true;
}

Particle* FixedRefiner::get_refined(Particle *, unsigned int i) const {
  IMP_CHECK_OBJECT(this);
  return get_particle(i);
}

unsigned int FixedRefiner::get_number_of_refined(Particle *) const {
  IMP_CHECK_OBJECT(this);
  return get_number_of_particles();
}

const ParticlesTemp FixedRefiner::get_refined(Particle *) const {
  return ParticlesTemp(particles_begin(), particles_end());
}

ParticlesTemp FixedRefiner::get_input_particles(Particle *) const {
  return ParticlesTemp();
}

ContainersTemp FixedRefiner::get_input_containers(Particle *) const {
  return ContainersTemp();
}

IMPCORE_END_NAMESPACE
