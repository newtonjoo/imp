/**
 *  \file HarmonicLowerBound.h    \brief Harmonic lower bound function.
 *
 *  Copyright 2007-8 Sali Lab. All rights reserved.
 */

#ifndef IMPCORE_HARMONIC_LOWER_BOUND_H
#define IMPCORE_HARMONIC_LOWER_BOUND_H

#include "config.h"
#include "Harmonic.h"

IMPCORE_BEGIN_NAMESPACE

//! Lower bound harmonic function (non-zero when feature < mean)
/** */
class HarmonicLowerBound : public Harmonic
{
public:
  HarmonicLowerBound(Float mean, Float k) : Harmonic(mean, k) {}
  virtual ~HarmonicLowerBound() {}

  //! Calculate lower-bound harmonic score with respect to the given feature.
  /** If the feature is greater than or equal to the mean, the score is zero.
      \param[in] feature Value of feature being tested.
      \return Score
  */
  virtual Float evaluate(Float feature) const {
    if (feature >= Harmonic::get_mean()) {
      return 0.0;
    } else {
      return Harmonic::evaluate(feature);
    }
  }

  //! Calculate lower-bound harmonic score and derivative for a feature.
  /** If the feature is greater than or equal to the mean, the score is zero.
      \param[in] feature Value of feature being tested.
      \return Score
   */
  virtual FloatPair evaluate_with_derivative(Float feature) const {
    if (feature >= Harmonic::get_mean()) {
      return std::make_pair(0.0f, 0.0f);
    } else {
      return Harmonic::evaluate_with_derivative(feature);
    }
  }

  void show(std::ostream &out=std::cout) const {
    out << "HarmonicLB: " << Harmonic::get_mean()
        << " and " << Harmonic::get_k() << std::endl;
  }
};

IMPCORE_END_NAMESPACE

#endif  /* IMPCORE_HARMONIC_LOWER_BOUND_H */
