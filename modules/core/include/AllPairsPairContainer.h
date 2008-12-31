/**
 *  \file AllPairsPairContainer.h
 *  \brief Return all pairs from a SingletonContainer
 *
 *  This file is generated by a script (core/tools/make-container).
 *  Do not edit directly.
 *
 *  Copyright 2007-8 Sali Lab. All rights reserved.
 */

#ifndef IMPCORE_ALL_PAIRS_PAIR_CONTAINER_H
#define IMPCORE_ALL_PAIRS_PAIR_CONTAINER_H

#include "config.h"

#include "internal/core_version_info.h"
#include <IMP/core/PairContainer.h>
#include <IMP/core/SingletonContainer.h>

IMPCORE_BEGIN_NAMESPACE

//! Return all pairs of particles taken from the wrapped SingletonContainer
/** Here is an example using this container to restrain all particles in a set
    to be within a a certain distance of one another.
    \verbinclude restrain_diameter.py

    \note Sequential access is much more efficient than random access which is
    suicidally slow for now. Complain if you want fast(er) random access.
    We might listen.
 */
class IMPCOREEXPORT AllPairsPairContainer : public PairContainer
{
  Pointer<SingletonContainer> c_;
  mutable int a_, b_;
public:
  //! Get the individual particles from the passed SingletonContainer
  AllPairsPairContainer(SingletonContainer *c);

  virtual ~AllPairsPairContainer();

  IMP_PAIR_CONTAINER(internal::core_version_info);
};


IMPCORE_END_NAMESPACE

#endif  /* IMPCORE_ALL_PAIRS_PAIR_CONTAINER_H */
