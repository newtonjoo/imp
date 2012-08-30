/**
 *  \file IMP/container/EventQuadsOptimizerState.h
 *  \brief Define some predicates.
 *
 *  WARNING This file was generated from EventNAMEsOptimizerState.hpp
 *  in tools/maintenance/container_templates/container
 *  by tools/maintenance/make-container.
 *
 *  Copyright 2007-2012 IMP Inventors. All rights reserved.
 */

#ifndef IMPCONTAINER_EVENT_QUADS_OPTIMIZER_STATE_H
#define IMPCONTAINER_EVENT_QUADS_OPTIMIZER_STATE_H

#include "container_config.h"
#include <IMP/QuadPredicate.h>
#include <IMP/OptimizerState.h>
#include <IMP/QuadContainer.h>
#include <IMP/optimizer_state_macros.h>

IMPCONTAINER_BEGIN_NAMESPACE

/** Raise an IMP::base::EventException when a certain condition is met.
    Currently the supported logic is when the number of items in the
    container for which the predicate returns a certain value is in the
    range [min_count, max_count).
 */
class IMPCONTAINEREXPORT EventQuadsOptimizerState:
    public OptimizerState {
  IMP::OwnerPointer<QuadPredicate> pred_;
  IMP::OwnerPointer<QuadContainer> container_;
  int v_;
  int min_, max_;
public:
  EventQuadsOptimizerState(QuadPredicate *pred,
                                QuadContainerAdaptor container,
                                int value, int min_count, int max_count,
                                std::string name="ConstQuadPredicate%1%");
  IMP_OPTIMIZER_STATE(EventQuadsOptimizerState);
};

IMPCONTAINER_END_NAMESPACE

#endif  /* IMPCONTAINER_EVENT_QUADS_OPTIMIZER_STATE_H */
