/**
 *  \file IMP/core/RigidBodyAnglePairScore.h
 *  \brief A Score on the crossing angle between two rigid bodies
 *
 *  Copyright 2007-2015 IMP Inventors. All rights reserved.
 */

#ifndef IMPCORE_RIGID_BODY_ANGLE_PAIR_SCORE_H
#define IMPCORE_RIGID_BODY_ANGLE_PAIR_SCORE_H

#include "core_config.h"

#include <IMP/PairScore.h>
#include <IMP/pair_macros.h>
#include <IMP/base/Pointer.h>
#include <IMP/UnaryFunction.h>

IMPCORE_BEGIN_NAMESPACE

//! Score on the crossing angle between two rigid bodies
class IMPCOREEXPORT RigidBodyAnglePairScore : public PairScore
{
  IMP::base::PointerMember<UnaryFunction> f_;
public:
  RigidBodyAnglePairScore(UnaryFunction *f);

  virtual double evaluate_index(kernel::Model *m,
                                const kernel::ParticleIndexPair &pi,
                                DerivativeAccumulator *da) const IMP_OVERRIDE;
  virtual kernel::ModelObjectsTemp do_get_inputs(
      kernel::Model *m, const kernel::ParticleIndexes &pis) const IMP_OVERRIDE;
  IMP_PAIR_SCORE_METHODS(RigidBodyAnglePairScore);
  IMP_OBJECT_METHODS(RigidBodyAnglePairScore);
};

IMPCORE_END_NAMESPACE

#endif  /* IMPCORE_RIGID_BODY_ANGLE_PAIR_SCORE_H */
