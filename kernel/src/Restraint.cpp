/**
 *  \file Restraint.cpp   \brief Abstract base class for all restraints.
 *
 *  Copyright 2007-8 Sali Lab. All rights reserved.
 *
 */

#include <cmath>

#include "IMP/Particle.h"
#include "IMP/Model.h"
#include "IMP/log.h"
#include "IMP/Restraint.h"

namespace IMP
{

Restraint::Restraint()
{
  model_=NULL;
  is_active_ = true; // active by default
}


//! Destructor
Restraint::~Restraint()
{
  if (!was_owned_) {
    // can't use virtual functions in the destructor
    std::cerr << "Restraint " << this << " is being destroyed "
              << "without ever having been added to a model."
              << std::endl;
  }
}


void Restraint::set_is_active(const bool is_active)
{
  is_active_ = is_active;
}


bool Restraint::get_is_active() const
{
  return is_active_;
}


void Restraint::set_model(Model* model)
{
  IMP_assert(model==NULL || get_number_of_particles()==0
             || model == get_particle(0)->get_model()
             || (model_ && model_ == model),
             "Model* different from Particle Model*");
  model_=model;
  was_owned_=true;
}

void Restraint::show(std::ostream& out) const
{
  if (get_is_active()) {
    out << "unknown restraint (active):" << std::endl;
  } else {
    out << "unknown restraint (inactive):" << std::endl;
  }

  get_version_info().show(out);
}

ParticlesList Restraint::get_interacting_particles() const
{
  return ParticlesList(1, Particles(particles_begin(), particles_end()));
}

// The index line is to disable a warning
IMP_LIST_IMPL(Restraint, Particle, particle,Particle*,  {
    IMP_assert(get_number_of_particles()==0 
               || obj->get_model() == (*particles_begin())->get_model(),
               "All particles in Restraint must belong to the "
               "same Model.");
  },);

}  // namespace IMP
