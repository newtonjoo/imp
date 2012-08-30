/**
 *  \file TripletContainer.cpp   \brief Container for triplet.
 *
 *  WARNING This file was generated from NAMEContainer.cc
 *  in tools/maintenance/container_templates/kernel
 *  by tools/maintenance/make-container.
 *
 *  Copyright 2007-2012 IMP Inventors. All rights reserved.
 *
 */

#include "IMP/TripletContainer.h"
#include "IMP/internal/utility.h"
#include "IMP/internal/InternalListTripletContainer.h"
#include "IMP/TripletModifier.h"
#include "IMP/internal/container_helpers.h"

IMP_BEGIN_NAMESPACE


TripletContainer::TripletContainer(Model *m, std::string name):
  Container(m,name){
}

// here for gcc
TripletContainer::~TripletContainer(){
}

TripletContainerAdaptor
::TripletContainerAdaptor(TripletContainer *c): P(c){}
TripletContainerAdaptor
::TripletContainerAdaptor(const ParticleTripletsTemp &t,
                                                 std::string name) {
  Model *m=internal::get_model(t);
  IMP_NEW(internal::InternalListTripletContainer, c,
          (m, name));
  c->set_particle_triplets(t);
  P::operator=(c);
}


IMP_END_NAMESPACE
