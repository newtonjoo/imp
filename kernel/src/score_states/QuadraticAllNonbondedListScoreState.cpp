/**
 *  \file QuadraticAllNonbondedListScoreState.cpp
 *  \brief Allow iteration through pairs of a set of s.
 *
 *  Copyright 2007-8 Sali Lab. All rights reserved.
 */

#include "IMP/score_states/QuadraticAllNonbondedListScoreState.h"
#include "IMP/decorators/XYZDecorator.h"

#include <algorithm>

namespace IMP
{


QuadraticAllNonbondedListScoreState
::QuadraticAllNonbondedListScoreState(FloatKey radius, 
                                      const Particles &ps): P(radius)
{
  set_particles(ps);
}

QuadraticAllNonbondedListScoreState::~QuadraticAllNonbondedListScoreState()
{
}

void QuadraticAllNonbondedListScoreState::set_particles(const Particles &ps)
{
  Particles moving;
  fixed_.clear();
  for (unsigned int i=0; i< ps.size(); ++i) {
    XYZDecorator d= XYZDecorator::cast(ps[i]);
    if (d.get_coordinates_are_optimized()) {
      moving.push_back(ps[i]);
    } else {
      fixed_.push_back(ps[i]);
    }
  }
  P::set_particles(moving);
}


void QuadraticAllNonbondedListScoreState::update()
{ 
  P::update();
}


void QuadraticAllNonbondedListScoreState::rebuild_nbl(Float cut)
{
  IMP_LOG(TERSE, "Rebuilding QNBL with cutoff " << cut << std::endl);
  const Particles &moving= P::get_particles();
  for (unsigned int j=0; j< moving.size(); ++j) {
    for (unsigned int i=0; i< fixed_.size(); ++i) {
      P::handle_nbl_pair(fixed_[i], moving[j], cut);
    }
    for (unsigned int i=0; i< j; ++i) {
      P::handle_nbl_pair(moving[i], moving[j], cut);
    }
  }
  IMP_LOG(TERSE, "NBL has " << P::nbl_.size() << " pairs" << std::endl);
}


void QuadraticAllNonbondedListScoreState::show(std::ostream &out) const
{
  out << "QuadraticAllNonbondedListScoreState" << std::endl;
}

} // namespace IMP
