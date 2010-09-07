/**
 *  \file CLASSNAMEConstraint.cpp
 *  \brief Use a CLASSNAMEModifier applied to a CLASSNAMEContainer to
 *  maintain an invariant
 *
 *  This file is generated by a script (core/tools/make-container).
 *  Do not edit directly.
 *
 *  Copyright 2007-2010 IMP Inventors. All rights reserved.
 *
 */

#include "IMP/core/CLASSNAMEConstraint.h"
#include "IMP/internal/container_helpers.h"

IMPCORE_BEGIN_NAMESPACE

CLASSNAMEConstraint::CLASSNAMEConstraint(CLASSNAMEModifier *before,
                                         CLASSNAMEModifier *after,
                                         ARGUMENTTYPE vt,
                                         std::string name):
  Constraint(name), v_(vt){
  if (before) f_=before;
  if (after) af_=after;
}


void CLASSNAMEConstraint::do_update_attributes()
{
  IMP_OBJECT_LOG;
  if (!f_) return;
  IMP_LOG(TERSE, "Begin CLASSNAMEsConstraint::update" << std::endl);
  IMP_CHECK_OBJECT(f_);
  f_->apply(v_);
  IMP_LOG(TERSE, "End CLASSNAMEsConstraint::update" << std::endl);
}

void CLASSNAMEConstraint::do_update_derivatives(DerivativeAccumulator *da)
{
  IMP_OBJECT_LOG;
  if (!af_) return;
  IMP_LOG(TERSE, "Begin CLASSNAMEsConstraint::after_evaluate" << std::endl);
  IMP_CHECK_OBJECT(af_);
  af_->apply(v_, *da);
  IMP_LOG(TERSE, "End CLASSNAMEsConstraint::after_evaluate" << std::endl);
}

ContainersTemp CLASSNAMEConstraint::get_input_containers() const {
  return ContainersTemp();
}

ContainersTemp CLASSNAMEConstraint::get_output_containers() const {
  return ContainersTemp();
}


ParticlesTemp CLASSNAMEConstraint::get_input_particles() const {
  ParticlesTemp ret;
  if (f_) {
    ret= IMP::internal::get_input_particles(f_.get(), v_);
    ParticlesTemp o= IMP::internal::get_output_particles(f_.get(), v_);
    ret.insert(ret.end(), o.begin(), o.end());
    IMP_IF_CHECK(USAGE) {
      if (af_) {
        ParticlesTemp oret= IMP::internal::get_input_particles(af_.get(), v_);
        std::sort(ret.begin(), ret.end());
        std::sort(oret.begin(), oret.end());
        ParticlesTemp t;
        std::set_union(ret.begin(), ret.end(), oret.begin(), oret.end(),
                       std::back_inserter(t));
        IMP_USAGE_CHECK(t.size() == ret.size(),
                        "The particles written by "
                        << " the after modifier in " << get_name() << " must "
                        << "be a subset of those read by the before "
                        << "modifier. Before: " << Particles(ret)
                        << " and after " << Particles(oret));
      }
    }
  } else {
    ret=IMP::internal::get_output_particles(af_.get(), v_);
  }
  return ret;
}

ParticlesTemp CLASSNAMEConstraint::get_output_particles() const {
  ParticlesTemp ret;
  if (f_) {
    ret= IMP::internal::get_output_particles(f_.get(), v_);
    IMP_IF_CHECK(USAGE) {
      if (af_) {
        ParticlesTemp oret= IMP::internal::get_input_particles(af_.get(), v_);
        ParticlesTemp iret=IMP::internal::get_input_particles(f_.get(), v_);
        iret.insert(iret.end(), ret.begin(), ret.end());
        std::sort(iret.begin(), iret.end());
        std::sort(oret.begin(), oret.end());
        ParticlesTemp t;
        std::set_union(iret.begin(), iret.end(), oret.begin(), oret.end(),
                       std::back_inserter(t));
        IMP_USAGE_CHECK(t.size() == iret.size(), "The particles read by "
                      << " the after modifier in " << get_name() << " must "
                        << "be a subset of those written by the before"
                        << " modifier.");
      }
    }
  } else {
    ret= IMP::internal::get_input_particles(af_.get(), v_);
  }
  return ret;
}

void CLASSNAMEConstraint::do_show(std::ostream &out) const {
  out << "on " << IMP::internal::streamable(v_).get_name() << std::endl;
  if (f_) out << "before " << *f_ << std::endl;
  if (af_) out << "after " << *af_ << std::endl;
}

IMPCORE_END_NAMESPACE
