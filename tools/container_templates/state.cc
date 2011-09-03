/**
 *  \file CLASSNAMEsConstraint.cpp
 *  \brief Use a CLASSNAMEModifier applied to a CLASSNAMEContainer to
 *  maintain an invariant
 *
 *  This file is generated by a script (core/tools/make-container).
 *  Do not edit directly.
 *
 *  Copyright 2007-2011 IMP Inventors. All rights reserved.
 *
 */

#include "IMP/container/CLASSNAMEsConstraint.h"
#include "IMP/internal/container_helpers.h"
#include <IMP/core/CLASSNAMEConstraint.h>
#include <utility>

IMPCONTAINER_BEGIN_NAMESPACE

CLASSNAMEsConstraint::CLASSNAMEsConstraint(CLASSNAMEModifier *before,
                                  CLASSNAMEDerivativeModifier *after,
                                           CLASSNAMEContainer *c,
                                           std::string name):
  Constraint(name), c_(c) {
  if (before) f_=before;
  if (after) af_=after;
}


void CLASSNAMEsConstraint::do_update_attributes()
{
  IMP_OBJECT_LOG;
  if (!f_) return;
  IMP_LOG(TERSE, "Begin CLASSNAMEsConstraint::update" << std::endl);
  IMP_CHECK_OBJECT(f_);
  IMP_CHECK_OBJECT(c_);
  c_->apply(f_);
  IMP_LOG(TERSE, "End CLASSNAMEsConstraint::update" << std::endl);
}

void CLASSNAMEsConstraint::do_update_derivatives(DerivativeAccumulator *da)
{
  IMP_OBJECT_LOG;
  if (!af_) return;
  IMP_LOG(TERSE, "Begin CLASSNAMEsConstraint::after_evaluate" << std::endl);
  IMP_CHECK_OBJECT(af_);
  IMP_CHECK_OBJECT(c_);
  c_->apply(af_, *da);
  IMP_LOG(TERSE, "End CLASSNAMEsConstraint::after_evaluate" << std::endl);
}


ContainersTemp CLASSNAMEsConstraint::get_input_containers() const {
  return ContainersTemp(1, c_);
}

ContainersTemp CLASSNAMEsConstraint::get_output_containers() const {
  return ContainersTemp();
}

ParticlesTemp CLASSNAMEsConstraint::get_input_particles() const {
  ParticlesTemp ret;
  if (f_) {
    ret= IMP::internal::get_input_particles(f_.get(),
                                            c_->get_contained_particles());
    ParticlesTemp o= IMP::internal::get_output_particles(f_.get(),
                                            c_->get_contained_particles());
    ret.insert(ret.end(), o.begin(), o.end());
    IMP_IF_CHECK(USAGE) {
      if (af_) {
        ParticlesTemp oret= IMP::internal::get_output_particles(af_.get(),
                                               c_->get_contained_particles());
        std::sort(ret.begin(), ret.end());
        std::sort(oret.begin(), oret.end());
        ParticlesTemp t;
        std::set_union(ret.begin(), ret.end(), oret.begin(), oret.end(),
                       std::back_inserter(t));
        IMP_USAGE_CHECK(t.size() == ret.size(), "The particles written by "
                        << " the after modifier in " << get_name()
                        << " must be a subset of those read by the before "
                        << "modifier. Before: " << ret
                        << " and after " << oret);
      }
    }
  } else {
    ret= IMP::internal::get_output_particles(af_.get(),
                                          c_->get_contained_particles());
  }
  return ret;
}

ParticlesTemp CLASSNAMEsConstraint::get_output_particles() const {
  ParticlesTemp ret;
  if (f_) {
    ret= IMP::internal::get_output_particles(f_.get(),
                                       c_->get_contained_particles());
    IMP_IF_CHECK(USAGE) {
      if (af_) {
        ParticlesTemp oret= IMP::internal::get_input_particles(af_.get(),
                                               c_->get_contained_particles());
        ParticlesTemp iret=IMP::internal::get_input_particles(f_.get(),
                                               c_->get_contained_particles());
        iret.insert(iret.end(), ret.begin(), ret.end());
        std::sort(iret.begin(), iret.end());
        std::sort(oret.begin(), oret.end());
        ParticlesTemp t;
        std::set_union(iret.begin(), iret.end(), oret.begin(), oret.end(),
                       std::back_inserter(t));
        IMP_USAGE_CHECK(t.size() == iret.size(), "The particles read by "
                      << " the after modifier in " << get_name() << " must "
                        << "be a subset of those written by the before "
                        << "modifier.");
      }
    }
  } else {
    ret= IMP::internal::get_input_particles(af_.get(),
                                           c_->get_contained_particles());
  }
  return ret;
}

ScoreStates CLASSNAMEsConstraint::create_decomposition() const {
  ScoreStates ret;
  IMP_FOREACH_HEADERNAME_INDEX(c_, {
      ret.push_back(new core::CLASSNAMEConstraint(f_.get(), af_.get(),
                               IMP::internal::get_particle(get_model(),
                                                           _1)));
    });
  return ret;
}

void CLASSNAMEsConstraint::do_show(std::ostream &out) const {
  out << "on " << *c_ << std::endl;
  if (f_) out << "before " << *f_ << std::endl;
  if (af_) out << "after " << *af_ << std::endl;
}

IMPCONTAINER_END_NAMESPACE
