/**
 *  \file IMP/container/DistributeSingletonsScoreState.h
 *  \brief Apply a SingletonScore to each Singleton in a list.
 *
 *  WARNING This file was generated from DistributeNAMEsScoreState.hpp
 *  in tools/maintenance/container_templates/container
 *  by tools/maintenance/make-container.
 *
 *  Copyright 2007-2012 IMP Inventors. All rights reserved.
 *
 */

#ifndef IMPCONTAINER_DISTRIBUTE_SINGLETONS_SCORE_STATE_H
#define IMPCONTAINER_DISTRIBUTE_SINGLETONS_SCORE_STATE_H

#include "container_config.h"

#include "DynamicListSingletonContainer.h"
#include <IMP/SingletonPredicate.h>
#include <IMP/SingletonContainer.h>
#include <IMP/base/Vector.h>
#include <IMP/singleton_macros.h>
#include <IMP/score_state_macros.h>
#include <boost/tuple/tuple.hpp>

#include <iostream>

IMPCONTAINER_BEGIN_NAMESPACE

//! Distribute contents of one container into several based on predicates
/** This ScoreState takes a list of predicates and values. For
    each tuple in the input container, it is placed in a given output container
    if the predicate, when applied, has the passed value.

    \note The output containers contents are not necessarily disjoint.
*/
class IMPCONTAINEREXPORT DistributeSingletonsScoreState :
public ScoreState
{
  OwnerPointer<SingletonContainer> input_;
  typedef boost::tuple<Pointer<DynamicListSingletonContainer>,
    OwnerPointer<SingletonPredicate>, int> Data;
  base::Vector<Data> data_;
  mutable bool updated_;
  void update_lists_if_necessary() const;
public:
  DistributeSingletonsScoreState(SingletonContainerAdaptor input,
                      std::string name="DistributeSingletonsScoreState %1%");

  /** A given tuple will go into the returned container if \c predicate
      returns \c value when applied to it.*/
  DynamicListSingletonContainer *add_predicate(SingletonPredicate *predicate,
                                        int value) {
    IMP_NEW(DynamicListSingletonContainer, c, (input_,
                                        predicate->get_name()+ " output"));
    data_.push_back(Data(c, predicate, value));
    return c;
  }
  IMP_SCORE_STATE(DistributeSingletonsScoreState);
};

IMPCONTAINER_END_NAMESPACE

#endif  /* IMPCONTAINER_DISTRIBUTE_SINGLETONS_SCORE_STATE_H */
