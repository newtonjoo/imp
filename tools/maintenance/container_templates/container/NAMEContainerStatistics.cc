/**
 *  \file CLASSNAMEContainerStatistics.cpp   \brief Container for LCCLASSNAME.
 *
 *  BLURB
 *
 *  Copyright 2007-2012 IMP Inventors. All rights reserved.
 *
 */

#include "IMP/container/CLASSNAMEContainerStatistics.h"
#include <limits>

IMPCONTAINER_BEGIN_NAMESPACE


CLASSNAMEContainerStatistics
::CLASSNAMEContainerStatistics(CLASSNAMEContainerAdaptor c):
  ScoreState(c->get_name()+" statistics"){
  container_=c;
  total_=0;
  max_=0;
  min_=std::numeric_limits<unsigned int>::max();
  checks_=0;
  track_unique_=false;
}

void
CLASSNAMEContainerStatistics::do_show(std::ostream &out) const {
  show_statistics(out);
}


void CLASSNAMEContainerStatistics::set_track_unique(bool tf) {
  track_unique_=tf;
  unique_.clear();
}
void
CLASSNAMEContainerStatistics::show_statistics(std::ostream &out) const {
  out << "Average: " << static_cast<double>(total_)/checks_ <<  std::endl;
  out << "Min, Max: " << min_ <<", " << max_ << std::endl;
  if (track_unique_) {
    out << "Number unique: " << unique_.size() << std::endl;
  }
}

void CLASSNAMEContainerStatistics::do_before_evaluate() {
unsigned int n=container_->get_number();
  total_+= n;
  ++checks_;
  max_=std::max(max_, n);
  min_= std::min(min_, n);
  if (track_unique_) {
    for (unsigned int i=0; i < container_->get_number(); ++i) {
      unique_.insert(container_->get(i));
    }
  }
}

void CLASSNAMEContainerStatistics
::do_after_evaluate(DerivativeAccumulator *) {
}
ContainersTemp CLASSNAMEContainerStatistics::get_input_containers() const {
  return ContainersTemp(1, container_);
}
ContainersTemp CLASSNAMEContainerStatistics::get_output_containers() const {
  return ContainersTemp();
}
ParticlesTemp CLASSNAMEContainerStatistics::get_input_particles() const {
  return ParticlesTemp();
}
ParticlesTemp CLASSNAMEContainerStatistics::get_output_particles() const {
  return ParticlesTemp();
}

IMPCONTAINER_END_NAMESPACE
