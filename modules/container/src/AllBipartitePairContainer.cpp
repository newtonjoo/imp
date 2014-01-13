/**
 *  \file AllBipartitePairContainer.cpp   \brief A list of
 *kernel::ParticlePairs.
 *
 *  This file is generated by a script (core/tools/make-container).
 *  Do not edit directly.
 *
 *  Copyright 2007-2013 IMP Inventors. AllBipartite rights reserved.
 *
 */

#include "IMP/container/AllBipartitePairContainer.h"
#include <IMP/PairModifier.h>
#include <IMP/SingletonModifier.h>
#include <IMP/PairScore.h>
#include <IMP/SingletonScore.h>
#include <algorithm>

IMPCONTAINER_BEGIN_NAMESPACE

AllBipartitePairContainer::AllBipartitePairContainer(
    SingletonContainerAdaptor a, SingletonContainerAdaptor b, std::string name)
    : PairContainer(a->get_model(), name), a_(a), b_(b) {
  a.set_name_if_default("AllBipartitePairContainerInput0%1%");
  b.set_name_if_default("AllBipartitePairContainerInput1%1%");
}

ParticleIndexPairs AllBipartitePairContainer::get_indexes() const {
  kernel::ParticleIndexes ia = a_->get_indexes();
  kernel::ParticleIndexes ib = b_->get_indexes();
  kernel::ParticleIndexPairs ret;
  ret.reserve(ia.size() * ib.size());
  for (unsigned int i = 0; i < ia.size(); ++i) {
    for (unsigned int j = 0; j < ib.size(); ++j) {
      ret.push_back(kernel::ParticleIndexPair(ia[i], ib[j]));
    }
  }
  return ret;
}

ParticleIndexPairs AllBipartitePairContainer::get_range_indexes() const {
  kernel::ParticleIndexes ia = a_->get_range_indexes();
  kernel::ParticleIndexes ib = b_->get_range_indexes();
  kernel::ParticleIndexPairs ret;
  ret.reserve(ia.size() * ib.size());
  for (unsigned int i = 0; i < ia.size(); ++i) {
    for (unsigned int j = 0; j < ib.size(); ++j) {
      ret.push_back(kernel::ParticleIndexPair(ia[i], ib[j]));
    }
  }
  return ret;
}

ParticleIndexes AllBipartitePairContainer::get_all_possible_indexes() const {
  kernel::ParticleIndexes ret = a_->get_all_possible_indexes();
  ret += b_->get_all_possible_indexes();
  return ret;
}

ModelObjectsTemp AllBipartitePairContainer::do_get_inputs() const {
  kernel::ModelObjectsTemp ret;
  ret.push_back(a_);
  ret.push_back(b_);
  return ret;
}

IMPCONTAINER_END_NAMESPACE
