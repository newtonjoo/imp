/**
 *  \file DiscreteSampler.h   \brief Storage of a discrete sampling space
 *
 *  Copyright 2007-8 Sali Lab. All rights reserved.
 */

#ifndef __IMP_DISCRETE_SAMPLER_H
#define __IMP_DISCRETE_SAMPLER_H

#include "domino_config.h"
#include "IMP/Particle.h"
#include <vector>

namespace IMP
{

//! Holds the states of a single particle
class DOMINODLLEXPORT DiscreteSampler
{
public:
  virtual ~DiscreteSampler() {};

  virtual void show(std::ostream& out = std::cout) const {}
  virtual Float get_state_val(const Particle &p, unsigned int i,
                              FloatKey key) const;
  virtual unsigned int get_space_size(const Particle &p) const;
  virtual FloatKey get_attribute(const Particle &p,
                                 unsigned int att_index) const;
  virtual unsigned int get_number_of_attributes(const Particle &p) const;
  virtual void show_space(const Particle &p,
                          std::ostream& out = std::cout) const {}
  //! Shallow copy of the sampler instance
  virtual void shallow_copy(DiscreteSampler *copy_ds) const {}
  virtual void change_mapping(const Particles &orig_particles,
                              const Particles &shuffled_particles) {}
};

} // namespace IMP

#endif  /* __IMP_DISCRETE_SAMPLER_H */
