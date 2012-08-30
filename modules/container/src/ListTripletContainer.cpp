/**
 *  \file ListTripletContainer.cpp   \brief A list of ParticleTripletsTemp.
 *
 *  WARNING This file was generated from ListNAMEContainer.cc
 *  in tools/maintenance/container_templates/container
 *  by tools/maintenance/make-container.
 *
 *  Copyright 2007-2012 IMP Inventors. All rights reserved.
 *
 */

#include "IMP/container/ListTripletContainer.h"
#include "IMP/TripletModifier.h"
#include "IMP/TripletScore.h"
#include <IMP/internal/InternalListTripletContainer.h>
#include <algorithm>


IMPCONTAINER_BEGIN_NAMESPACE


ListTripletContainer
::ListTripletContainer(const ParticleTripletsTemp &ps):
  P(IMP::internal::get_model(ps[0]),
    "ListSingletonContainer%1%")
{
  set_particle_triplets(ps);
}

ListTripletContainer
::ListTripletContainer(const ParticleTripletsTemp &ps,
                         std::string name):
  P(IMP::internal::get_model(ps[0]), name)
{
  set_particle_triplets(ps);
}

ListTripletContainer
::ListTripletContainer(Model *m, std::string name):
  P(m, name){
}

ListTripletContainer
::ListTripletContainer(Model *m, const char *name):
  P(m, name){
}

void ListTripletContainer::do_show(std::ostream &out) const {
  IMP_CHECK_OBJECT(this);
  out <<  get_number_of_particle_triplets()
      << " Triplets" << std::endl;
}

IMPCONTAINER_END_NAMESPACE
