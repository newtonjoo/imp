/**
 *  \file IMP/base/object_macros.h
 *  \brief Various general useful macros for IMP.
 *
 *  Copyright 2007-2015 IMP Inventors. All rights reserved.
 *
 */

#ifndef IMPBASE_OBJECT_MACROS_H
#define IMPBASE_OBJECT_MACROS_H
#include <IMP/base/base_config.h>
#include "doxygen_macros.h"
#include "ref_counted_macros.h"
#include "Vector.h"
#include "Pointer.h"
#include "WeakPointer.h"
#include "SetLogState.h"

//! Define the basic things needed by any Object
/** This defines
    - IMP::base::Object::get_version_info()
    - IMP::base::Object::get_type_name()
    - a protected destructor
*/
#define IMP_OBJECT_METHODS(Name)                                              \
 public:                                                                      \
  virtual std::string get_type_name() const IMP_OVERRIDE { return #Name; }    \
  virtual ::IMP::base::VersionInfo get_version_info() const IMP_OVERRIDE {    \
    return ::IMP::base::VersionInfo(get_module_name(), get_module_version()); \
  }                                                                           \
                                                                              \
 protected:                                                                   \
  virtual ~Name() { IMP::base::Object::_on_destruction(); }                   \
                                                                              \
 public:

//! Only to work around a gcc bug
#define IMP_OBJECT_NO_WARNING(Name)                                           \
 public:                                                                      \
  virtual std::string get_type_name() const IMP_OVERRIDE { return #Name; }    \
  virtual ::IMP::base::VersionInfo get_version_info() const IMP_OVERRIDE {    \
    return ::IMP::base::VersionInfo(get_module_name(), get_module_version()); \
  }                                                                           \
  void do_show(std::ostream &out) const;                                      \
  IMP_REF_COUNTED_INLINE_DESTRUCTOR(Name, IMP::base::Object::_on_destruction();)

//! Define the types for storing sets of objects
/** The macro defines the types PluralName and PluralNameTemp.
    PluralName should be Names unless the English spelling is
    different.
 */
#define IMP_OBJECTS(Name, PluralName)                              \
  /** Store a set of objects.*/                                    \
  typedef IMP::base::Vector<IMP::base::Pointer<Name> > PluralName; \
  /** Pass a set of objects. \see Name */                          \
  typedef IMP::base::Vector<IMP::base::WeakPointer<Name> > PluralName##Temp;

#define IMP_GENERIC_OBJECT(Name, lcname, targument, carguments, cparguments) \
  typedef Generic##Name<targument> Name;                                     \
  template <class targument>                                                 \
  Generic##Name<targument> *create_##lcname carguments {                     \
    return new Generic##Name<targument> cparguments;                         \
  }

//! Declare a ref counted pointer to a new object
/** \param[in] Typename The namespace qualified type being declared
    \param[in] varname The name for the ref counted pointer
    \param[in] args The arguments to the constructor, or ()
    if there are none.
    Please read the documentation for IMP::Pointer before using.
*/
#define IMP_NEW(Typename, varname, args) \
  IMP::base::Pointer<Typename> varname(new Typename args)

#endif /* IMPBASE_OBJECT_MACROS_H */
