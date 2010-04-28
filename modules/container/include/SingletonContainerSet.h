/**
 *  \file SingletonContainerSet.h
 *  \brief Store a set of SingletonContainers
 *
 *  This file is generated by a script (core/tools/make-container).
 *  Do not edit directly.
 *
 *  Copyright 2007-2010 IMP Inventors. All rights reserved.
 */

#ifndef IMPCONTAINER_SINGLETON_CONTAINER_SET_H
#define IMPCONTAINER_SINGLETON_CONTAINER_SET_H

#include "container_config.h"
#include <IMP/SingletonContainer.h>
#include <IMP/container_macros.h>
#include <IMP/internal/container_helpers.h>

IMPCONTAINER_BEGIN_NAMESPACE

//! Stores a set of SingletonContainers
/** The input sets must be disjoint. This can change if there is
    demand for it.

    \usesconstraint
*/
class IMPCONTAINEREXPORT SingletonContainerSet
  : public SingletonContainer
{
  IMP_CONTAINER_DEPENDENCIES(SingletonContainerSet,
                             {
                               ret.insert(ret.end(),
                                          back_->singleton_containers_begin(),
                                          back_->singleton_containers_end());
                             });
  // to not have added and removed
  SingletonContainerSet();
 public:
  //! Construct and empty set
  SingletonContainerSet(Model *m,
                        std::string name="SingletonContainerSet %1%");

  SingletonContainerSet(const SingletonContainersTemp &pc,
                        std::string name="SingletonContainerSet %1%");

  IMP_SINGLETON_CONTAINER(SingletonContainerSet);
  /** @name Methods to control the nested container

      This container merges a set of nested containers. To add
      or remove nested containers, use the methods below.
  */
  /**@{*/
  IMP_LIST(public, SingletonContainer, singleton_container,
           SingletonContainer*, SingletonContainers);
  /**@}*/

  static SingletonContainerSet *create_untracked_container() {
    SingletonContainerSet *lsc = new SingletonContainerSet();
    return lsc;
  }
#ifndef IMP_DOXYGEN
  bool get_is_up_to_date() const {
    for (unsigned int i=0;
         i< get_number_of_singleton_containers(); ++i) {
      if (!get_singleton_container(i)->get_is_up_to_date()) return false;
    }
    return true;
  }
#endif
};


IMPCONTAINER_END_NAMESPACE

#endif  /* IMPCONTAINER_SINGLETON_CONTAINER_SET_H */
