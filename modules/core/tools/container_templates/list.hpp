/**
 *  \file ListGroupnameContainer.h    \brief Store a list of Classnames
 *
 *  This file is generated by a script (core/tools/make-container).
 *  Do not edit directly.
 *
 *  Copyright 2007-8 Sali Lab. All rights reserved.
 */

#ifndef IMPCORE_LIST_GROUPNAME_CONTAINER_H
#define IMPCORE_LIST_GROUPNAME_CONTAINER_H

#include "core_exports.h"
#include "GroupnameContainer.h"
#include "internal/core_version_info.h"

IMPCORE_BEGIN_NAMESPACE

//! Store a list of Classnames
/** \note The indexes can change when particles are inserted
    as the list is maintained in sorted order.
 */
class IMPCOREEXPORT ListGroupnameContainer : public GroupnameContainer
{
public:
  ListGroupnameContainer(const Classnames &ps= Classnames());

  virtual ~ListGroupnameContainer();

  //! log n time
  virtual bool get_contains_classname(Value vt) const;

  IMP_LIST(public, Classname, classname, Value);

  IMP::VersionInfo get_version_info() const {
    return internal::core_version_info;
  }

  //!
  virtual void show(std::ostream &out = std::cout) const;
};


IMPCORE_END_NAMESPACE

#endif  /* IMPCORE_LIST_GROUPNAME_CONTAINER_H */
