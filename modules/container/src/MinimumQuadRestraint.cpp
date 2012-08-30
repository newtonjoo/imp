/**
 *  \file MinimumQuadRestraint.cpp
 *  \brief The minimum score over a container.
 *
 *  WARNING This file was generated from MinimumNAMERestraint.cc
 *  in tools/maintenance/container_templates/container
 *  by tools/maintenance/make-container.
 *
 *  Copyright 2007-2012 IMP Inventors. All rights reserved.
 *
 */

#include "IMP/container/MinimumQuadRestraint.h"
#include "IMP/algebra/internal/MinimalSet.h"
#include <IMP/internal/container_helpers.h>
#include <IMP/core/QuadRestraint.h>
#include <IMP/quad_macros.h>

IMPCONTAINER_BEGIN_NAMESPACE

MinimumQuadRestraint
::MinimumQuadRestraint(QuadScore *f,
                           QuadContainerAdaptor c,
                           unsigned int n,
                           std::string name):
  Restraint(c->get_model(), name),
  f_(f), c_(c), n_(n){
}

namespace {
  typedef algebra::internal::MinimalSet<double,
          ParticleQuad, std::less<double> > QuadMinimumMS;
  template <class C, class F>
  QuadMinimumMS find_minimal_set_QuadMinimum(C* c, F *f,
                                                         unsigned int n) {
    IMP_LOG(VERBOSE, "Finding Minimum " << n << " of "
            << c->get_number() << std::endl);
    QuadMinimumMS bestn(n);
    IMP_FOREACH_QUAD(c, {
        double score= f->evaluate(_1, nullptr);
        IMP_LOG(VERBOSE, "Found " << score << " for "
                << _1 << std::endl);
        bestn.insert(score, _1);
      });
    return bestn;
  }
}

double MinimumQuadRestraint
::unprotected_evaluate(DerivativeAccumulator *da) const {
  IMP_OBJECT_LOG;
  QuadMinimumMS bestn
    = find_minimal_set_QuadMinimum(c_.get(),
                                         f_.get(), n_);

  double score=0;
  for (unsigned int i=0; i< bestn.size(); ++i) {
    if (da) {
      f_->evaluate(bestn[i].second, da);
    }
    score+= bestn[i].first;
  }
  IMP_LOG(VERBOSE, "Total score is " << score << std::endl);
  return score;
}

double MinimumQuadRestraint
::unprotected_evaluate_if_good(DerivativeAccumulator *da,
                               double max) const {
  IMP_OBJECT_LOG;
  QuadMinimumMS bestn
    = find_minimal_set_QuadMinimum(c_.get(),
                                         f_.get(), n_);

  double score=0;
  for (unsigned int i=0; i< bestn.size(); ++i) {
    if (da) {
      f_->evaluate(bestn[i].second, da);
    }
    score+= bestn[i].first;
    if (score > max) break;
  }
  IMP_LOG(VERBOSE, "Total score is " << score << std::endl);
  return score;
}

Restraints MinimumQuadRestraint
::do_create_current_decomposition() const {
  IMP_OBJECT_LOG;
  QuadMinimumMS bestn
    = find_minimal_set_QuadMinimum(c_.get(),
                                         f_.get(), n_);
  Restraints ret;
  for (unsigned int i=0; i< bestn.size(); ++i) {
    ret.push_back(new core::QuadRestraint(f_, bestn[i].second));
  }
  return ret;
}


void MinimumQuadRestraint::do_show(std::ostream &out) const {
  out << "container " << *c_ << std::endl;
  out << "score " << *f_ << std::endl;
}


ParticlesTemp MinimumQuadRestraint::get_input_particles() const
{
  return IMP::internal::get_input_particles(f_.get(),
                                            c_->get_all_possible_particles());
}

ContainersTemp MinimumQuadRestraint::get_input_containers() const
{
  return ContainersTemp(1, c_);
}


IMPCONTAINER_END_NAMESPACE
