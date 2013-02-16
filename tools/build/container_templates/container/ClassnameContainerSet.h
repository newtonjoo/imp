/**
 *  \file IMP/container/ClassnameContainerSet.h
 *  \brief Store a set of ClassnameContainers
 *
 *  This file is generated by a script (tools/maintenance/make-container).
 *  Do not edit directly.
 *
 *  Copyright 2007-2013 IMP Inventors. All rights reserved.
 */

#ifndef IMPCONTAINER_CLASSNAME_CONTAINER_SET_H
#define IMPCONTAINER_CLASSNAME_CONTAINER_SET_H

#include <IMP/container/container_config.h>
#include <IMP/ClassnameContainer.h>
#include <IMP/container_macros.h>
#include <IMP/internal/container_helpers.h>
#include <IMP/scoped.h>

IMPCONTAINER_BEGIN_NAMESPACE

//! Stores a set of ClassnameContainers
/** The input sets must be disjoint. This can change if there is
    demand for it.

    \usesconstraint
*/
class IMPCONTAINEREXPORT ClassnameContainerSet
  : public ClassnameContainer
{
  static ClassnameContainerSet* get_set(ClassnameContainer* c) {
    return dynamic_cast<ClassnameContainerSet*>(c);
  }
 public:
  //! Construct and empty set
  ClassnameContainerSet(Model *m,
                        std::string name="ClassnameContainerSet %1%");

  ClassnameContainerSet(const ClassnameContainersTemp &pc,
                        std::string name="ClassnameContainerSet %1%");

  /** \brief apply modifer sm to all classname containers */
  IMP_IMPLEMENT(void do_apply(const ClassnameModifier *sm) const);

  template <class M>
      void apply_generic(const M*m) const {
    apply(m);
  }

  ParticleIndexes get_all_possible_indexes() const;
  IMP_OBJECT(ClassnameContainerSet);

  /** @name Methods to control the nested container

      This container merges a set of nested containers. To add
      or remove nested containers, use the methods below.
  */
  /**@{*/
  IMP_LIST_ACTION(public, ClassnameContainer, ClassnameContainers,
                  CLASSFUNCTIONNAME_container, CLASSFUNCTIONNAME_containers,
                  ClassnameContainer*, ClassnameContainers,
                  {
                    obj->set_was_used(true);
                    set_is_changed(true);
                  },{},
                  );
  /**@}*/

#ifndef IMP_DOXYGEN
  PLURALINDEXTYPE get_indexes() const;
  PLURALINDEXTYPE get_range_indexes() const;
  ModelObjectsTemp do_get_inputs() const;
#endif

  IMP_IMPLEMENT(void do_before_evaluate());
};


IMPCONTAINER_END_NAMESPACE

#endif  /* IMPCONTAINER_CLASSNAME_CONTAINER_SET_H */