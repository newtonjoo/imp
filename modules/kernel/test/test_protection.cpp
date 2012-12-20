/**
 *   Copyright 2007-2012 IMP Inventors. All rights reserved
 */
#include <IMP/Model.h>
#include <IMP/Particle.h>
#include <IMP/Restraint.h>
#include <IMP/restraint_macros.h>
#include <IMP/base/threads.h>

std::string get_module_version() {
  return std::string();
}

std::string get_module_name() {
  return std::string();
}

class TouchyRestraint: public IMP::Restraint {
  IMP::Particle *p_;
  IMP::FloatKey fk_;
 public:
  TouchyRestraint(IMP::Particle *p, IMP::FloatKey fk):
      IMP::Restraint(p->get_model(), "Touchy"), p_(p), fk_(fk) {}
  IMP_RESTRAINT_2(TouchyRestraint);
};

void TouchyRestraint::do_show(std::ostream &) const{}

double TouchyRestraint::unprotected_evaluate(IMP::DerivativeAccumulator *)
    const {
  return p_->get_value(fk_);
}

IMP::ModelObjectsTemp TouchyRestraint::do_get_inputs() const {
  return IMP::ModelObjectsTemp();
}

int main(int, char*[]) {
  IMP_NEW(IMP::Model, m, ());
  IMP_NEW(IMP::Particle, p, (m));
  IMP::base::SetNumberOfThreads no(1);
  IMP_NEW(TouchyRestraint, r, (p, IMP::FloatKey(0)));
  try {
    r->evaluate(false);
    // there had better be an exception
    return 1;
  } catch (const IMP::base::ExceptionBase &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}