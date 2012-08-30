/**
 *  \file ListCLASSNAMEContainer.h
 *  \brief Store a list of PLURALVARIABLETYPE
 *
 *  BLURB
 *
 *  Copyright 2007-2012 IMP Inventors. All rights reserved.
 */

#ifndef IMPKERNEL_INTERNAL_INTERNAL_DYNAMIC_LIST_HEADERNAME_CONTAINER_H
#define IMPKERNEL_INTERNAL_INTERNAL_DYNAMIC_LIST_HEADERNAME_CONTAINER_H

#include "../kernel_config.h"
#include "container_helpers.h"
#include "ListLikeCLASSNAMEContainer.h"
#include <IMP/base/Pointer.h>

IMP_BEGIN_INTERNAL_NAMESPACE


class IMPEXPORT InternalDynamicListCLASSNAMEContainer:
  public ListLikeCLASSNAMEContainer
{
  typedef ListLikeCLASSNAMEContainer P;
  // use this to define the set of all possible particles when it is dynamic
  base::Pointer<Container> scope_;
  bool check_list(const ParticleIndexes& cp) const;
 public:
  InternalDynamicListCLASSNAMEContainer(Container *m, std::string name);
  InternalDynamicListCLASSNAMEContainer(Container *m, const char *name);
  void add_FUNCTIONNAME(ARGUMENTTYPE vt) {
    IMP_USAGE_CHECK(IMP::internal::is_valid(vt),
                    "Passed CLASSNAME cannot be nullptr (or None)");

    add_to_list(IMP::internal::get_index(vt));
    IMP_USAGE_CHECK(check_list(IMP::internal::flatten
                               (IMP::internal::get_index(vt))),
                    "Invalid entries added to list " << vt);
  }
  void add_FUNCTIONNAME(PASSINDEXTYPE vt) {
    add_to_list(vt);
    IMP_USAGE_CHECK(check_list(IMP::internal::flatten(vt)),
                    "Invalid entries added to list " << vt);
  }
  void add_FUNCTIONNAMEs(const PLURALARGUMENTTYPE &c) {
    if (c.empty()) return;
    PLURALINDEXTYPE cp= IMP::internal::get_index(c);
    add_to_list(cp);
    IMP_USAGE_CHECK(check_list(IMP::internal::flatten
                               (cp)),
                    "Invalid entries added to list " << cp);
  }
  void remove_FUNCTIONNAMEs(const PLURALARGUMENTTYPE &c);
  void set_FUNCTIONNAMEs(PLURALARGUMENTTYPE c) {
    PLURALINDEXTYPE cp= IMP::internal::get_index(c);
    update_list(cp);
    IMP_USAGE_CHECK(check_list(IMP::internal::flatten
                               (cp)),
                    "Invalid entries added to list " << c);
  }
  void set_FUNCTIONNAMEs(PLURALINDEXTYPE cp) {
    update_list(cp);
    IMP_USAGE_CHECK(check_list(IMP::internal::flatten(cp)),
                    "Invalid entries added to list " << cp);
  }
  void clear_FUNCTIONNAMEs() {
    PLURALINDEXTYPE t;
    update_list(t);
  }
  IMP_LISTLIKE_HEADERNAME_CONTAINER(InternalDynamicListCLASSNAMEContainer);
};

IMP_END_INTERNAL_NAMESPACE

#endif  /* IMPKERNEL_INTERNAL_INTERNAL_DYNAMIC_LIST_HEADERNAME_CONTAINER_H */
