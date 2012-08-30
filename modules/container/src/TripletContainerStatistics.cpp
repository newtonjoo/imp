/**
 *  \file TripletContainerStatistics.cpp   \brief Container for triplet.
 *
 *  WARNING This file was generated from NAMEContainerStatistics.cc
 *  in tools/maintenance/container_templates/container
 *  by tools/maintenance/make-container.
 *
 *  Copyright 2007-2012 IMP Inventors. All rights reserved.
 *
 */

#include "IMP/container/TripletContainerStatistics.h"
#include <limits>

IMPCONTAINER_BEGIN_NAMESPACE


TripletContainerStatistics
::TripletContainerStatistics(TripletContainerAdaptor c):
  ScoreState(c->get_name()+" statistics"){
  container_=c;
  total_=0;
  max_=0;
  min_=std::numeric_limits<unsigned int>::max();
  checks_=0;
  track_unique_=false;
}

void
TripletContainerStatistics::do_show(std::ostream &out) const {
  show_statistics(out);
}


void TripletContainerStatistics::set_track_unique(bool tf) {
  track_unique_=tf;
  unique_.clear();
}
void
TripletContainerStatistics::show_statistics(std::ostream &out) const {
  out << "Average: " << static_cast<double>(total_)/checks_ <<  std::endl;
  out << "Min, Max: " << min_ <<", " << max_ << std::endl;
  if (track_unique_) {
    out << "Number unique: " << unique_.size() << std::endl;
  }
}

void TripletContainerStatistics::do_before_evaluate() {
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

void TripletContainerStatistics
::do_after_evaluate(DerivativeAccumulator *) {
}
ContainersTemp TripletContainerStatistics::get_input_containers() const {
  return ContainersTemp(1, container_);
}
ContainersTemp TripletContainerStatistics::get_output_containers() const {
  return ContainersTemp();
}
ParticlesTemp TripletContainerStatistics::get_input_particles() const {
  return ParticlesTemp();
}
ParticlesTemp TripletContainerStatistics::get_output_particles() const {
  return ParticlesTemp();
}

IMPCONTAINER_END_NAMESPACE
