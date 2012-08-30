/**
 *  \file ListSingletonContainer.h
 *  \brief Store a list of ParticlesTemp
 *
 *  WARNING This file was generated from InternalDynamicListNAMEContainer.hpp
 *  in tools/maintenance/container_templates/kernel/internal
 *  by tools/maintenance/make-container.
 *
 *  Copyright 2007-2012 IMP Inventors. All rights reserved.
 */

#ifndef IMPKERNEL_INTERNAL_INTERNAL_DYNAMIC_LIST_SINGLETON_CONTAINER_H
#define IMPKERNEL_INTERNAL_INTERNAL_DYNAMIC_LIST_SINGLETON_CONTAINER_H

#include "../kernel_config.h"
#include "container_helpers.h"
#include "ListLikeSingletonContainer.h"
#include <IMP/base/Pointer.h>

IMP_BEGIN_INTERNAL_NAMESPACE


class IMPEXPORT InternalDynamicListSingletonContainer:
  public ListLikeSingletonContainer
{
  typedef ListLikeSingletonContainer P;
  // use this to define the set of all possible particles when it is dynamic
  base::Pointer<Container> scope_;
  bool check_list(const ParticleIndexes& cp) const;
 public:
  InternalDynamicListSingletonContainer(Container *m, std::string name);
  InternalDynamicListSingletonContainer(Container *m, const char *name);
  void add_particle(Particle* vt) {
    IMP_USAGE_CHECK(IMP::internal::is_valid(vt),
                    "Passed Singleton cannot be nullptr (or None)");

    add_to_list(IMP::internal::get_index(vt));
    IMP_USAGE_CHECK(check_list(IMP::internal::flatten
                               (IMP::internal::get_index(vt))),
                    "Invalid entries added to list " << vt);
  }
  void add_particle(ParticleIndex vt) {
    add_to_list(vt);
    IMP_USAGE_CHECK(check_list(IMP::internal::flatten(vt)),
                    "Invalid entries added to list " << vt);
  }
  void add_particles(const ParticlesTemp &c) {
    if (c.empty()) return;
    ParticleIndexes cp= IMP::internal::get_index(c);
    add_to_list(cp);
    IMP_USAGE_CHECK(check_list(IMP::internal::flatten
                               (cp)),
                    "Invalid entries added to list " << cp);
  }
  void remove_particles(const ParticlesTemp &c);
  void set_particles(ParticlesTemp c) {
    ParticleIndexes cp= IMP::internal::get_index(c);
    update_list(cp);
    IMP_USAGE_CHECK(check_list(IMP::internal::flatten
                               (cp)),
                    "Invalid entries added to list " << c);
  }
  void set_particles(ParticleIndexes cp) {
    update_list(cp);
    IMP_USAGE_CHECK(check_list(IMP::internal::flatten(cp)),
                    "Invalid entries added to list " << cp);
  }
  void clear_particles() {
    ParticleIndexes t;
    update_list(t);
  }
  IMP_LISTLIKE_SINGLETON_CONTAINER(InternalDynamicListSingletonContainer);
};

IMP_END_INTERNAL_NAMESPACE

#endif  /* IMPKERNEL_INTERNAL_INTERNAL_DYNAMIC_LIST_SINGLETON_CONTAINER_H */
