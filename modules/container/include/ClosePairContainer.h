/**
 *  \file IMP/container/ClosePairContainer.h
 *  \brief Return all pairs from a SingletonContainer
 *
 *  This file is generated by a script (core/tools/make-container).
 *  Do not edit directly.
 *
 *  Copyright 2007-2013 IMP Inventors. Close rights reserved.
 */

#ifndef IMPCONTAINER_CLOSE_PAIR_CONTAINER_H
#define IMPCONTAINER_CLOSE_PAIR_CONTAINER_H

#include <IMP/container/container_config.h>
#include <IMP/core/internal/CoreClosePairContainer.h>
#include <IMP/Optimizer.h>

IMPCONTAINER_BEGIN_NAMESPACE

/** \brief Return all close unordered pairs of particles taken from
    the SingletonContainer

The ClosePairContainer class maintains a list of particle pairs whose
distance (opportunely defined by the decorator, eg., sphere surface
distance for XYZR, and center-to-center distance for XYZ) is smaller
than the `distance_cutoff` parameter.
It is generally used to construct the non-bonded list for the excluded
volume score,  as well as electrostatic and van der Waals potential
terms.

To increase the efficiency, the stored list actually includes all pairs that
are closer than `distance_cutoff + slack`. This allows us to reuse the list
and only recompute it when a particle moves more than `slack`.
The class keeps track
internally of how far the particles have moved using a score state,
and is also updated via a score state. A too small a `slack`
value can slow things down because the non-bonded list will be updated
frequently. Also, a too large a slack value generates many particle pairs
whose score is zero, thereby unnecessarily slowing down the score
calculation. As a result,
it may be useful to experiment with the parameter. You may wish to use
the get_slack_estimate() function to help with this experimentation.

\note The non-bonded list will contain pairs that are further than
`distance_cutoff` apart. If you use an IMP::PairScore with the generated
list of pairs, make sure the IMP::PairScore is 0 for distances beyond
the `distance_cutoff`.

\note As with any invariant in \imp, the contents of the container will
only be value during restraint evaluation, or immediately following
a call to Model::update().

\note The ClosePairContainer is strongly associated with the
      SingletonContainerAdaptor provided to it in the constructor.
      For instance, if the list of particles in the adaptor changes dynamically
      (by e.g., changing them in the SingltonContainer), the close pair
      container will also change dynamically.

    Here is a simple example of using this for a nonbonded list
    \include nonbonded_interactions.py

    See also AllPairContainer, CloseBipartitePairContainer,
    AllBipartitePairContainer for variants on the functionality provided.

 */
class IMPCONTAINEREXPORT ClosePairContainer :
#if defined(IMP_DOXYGEN) || defined(SWIG)
    public PairContainer
#else
    public core::internal::CoreClosePairContainer
#endif
    {
  typedef core::internal::CoreClosePairContainer P;

 public:
  //! Get the individual particles from the passed SingletonContainer
  /**
     Creates a close pair container associated with c.

     @param c an adaptor to a SingletonContainer. Note that if the contents
              of c change dynamically, so will the contents of the
              ClosePairContainer.
     @param distance_cutoff the cutoff beneath which pairs are considerd
                            close (returned by this container)
     @param slack the slack parameter for close pair updating
                  (affects performance but not results - see class description)
   */
  ClosePairContainer(SingletonContainerAdaptor c, double distance_cutoff,
                     double slack = 1);

  //! Get the individual particles from the passed SingletonContainer
  /**
     Creates a close pair container associated with c.

     @param c an adaptor to a SingletonContainer. Note that if the contents
              of c change dynamically, so will the contents of the
              ClosePairContainer
     @param distance_cutoff the cutoff beneath which pairs are considerd
                            close (returned by this container)
     @param slack the slack parameter for close pair updating
                  (affects performance but not results - see class description)

   */
  ClosePairContainer(SingletonContainerAdaptor c, double distance_cutoff,
                     core::ClosePairsFinder *cpf, double slack = 1);

#if defined(SWIG) || defined(IMP_DOXYGEN)
  /** @name Methods to control the set of filters

     PairPredicate objects can be used as filters to prevent
     the addition of pairs to the container output list. Pairs
     for which the predicates evaluate to a non-zero value are
     excluded from the list.
  */
  /**@{*/
  IMP_LIST(public, PairPredicate, pair_filter, PairPredicate *, PairPredicates);
  /**@}*/
  void set_slack(double s);
  double get_slack() const;
  ParticleIndexPairs get_indexes() const;
  ParticleIndexPairs get_range_indexes() const;
  void do_before_evaluate();
  ModelObjectsTemp do_get_inputs() const;
  void do_apply(const PairModifier *sm) const;
  ParticleIndexes get_all_possible_indexes() const;
#endif
  IMP_OBJECT_METHODS(ClosePairContainer);
};

IMP_OBJECTS(ClosePairContainer, ClosePairContainers);

/** Estimate the proper slack based on
    - the time taken to evaluate the passed restraints for a given
    number of particles in the non-bonded list
    - the number of pairs in the list as a function of slack size
    - the amount the particles are moved by the optimizer
    - the time taken to compute the close pairs as a function
    of slack size

    For best results, make the particles start in a
    that is "typical" for the optimization.
*/
IMPCONTAINEREXPORT double get_slack_estimate(const ParticlesTemp &ps,
                                             double upper_bound, double step,
                                             const RestraintsTemp &restraints,
                                             bool derivatives, Optimizer *opt,
                                             ClosePairContainer *cpc);

IMPCONTAINER_END_NAMESPACE

#endif /* IMPCONTAINER_CLOSE_PAIR_CONTAINER_H */
