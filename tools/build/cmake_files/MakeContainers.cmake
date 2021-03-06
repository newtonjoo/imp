
add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/include/IMP/container/SingletonContainerSet.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/SingletonContainerStatistics.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/SingletonsConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/SingletonsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/SingletonsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DistributeSingletonsScoreState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DynamicListSingletonContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/EventSingletonsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/InContainerSingletonFilter.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/ListSingletonContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumSingletonRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumSingletonScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PredicateSingletonsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/SingletonConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/SingletonRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/singleton_predicates.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/SingletonContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/SingletonDerivativeModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/SingletonModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/SingletonPredicate.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/SingletonScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/singleton_macros.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/internal/SingletonContainerIndex.h
   ${PROJECT_BINARY_DIR}/src/container/singletons.cpp
   ${PROJECT_BINARY_DIR}/src/core/singleton_predicates.cpp
   ${PROJECT_BINARY_DIR}/src/kernel/singletons.cpp
   ${PROJECT_BINARY_DIR}/test/container/test_particle_restraint.py
   ${PROJECT_BINARY_DIR}/test/container/test_particle_state.py
   ${PROJECT_BINARY_DIR}/include/IMP/container/PairContainerSet.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PairContainerStatistics.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PairsConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PairsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PairsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DistributePairsScoreState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DynamicListPairContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/EventPairsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/InContainerPairFilter.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/ListPairContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumPairRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumPairScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PredicatePairsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/PairConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/PairRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/pair_predicates.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/PairContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/PairDerivativeModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/PairModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/PairPredicate.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/PairScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/pair_macros.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/internal/PairContainerIndex.h
   ${PROJECT_BINARY_DIR}/src/container/pairs.cpp
   ${PROJECT_BINARY_DIR}/src/core/pair_predicates.cpp
   ${PROJECT_BINARY_DIR}/src/kernel/pairs.cpp
   ${PROJECT_BINARY_DIR}/test/container/test_particle_pair_restraint.py
   ${PROJECT_BINARY_DIR}/test/container/test_particle_pair_state.py
   ${PROJECT_BINARY_DIR}/include/IMP/container/TripletContainerSet.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/TripletContainerStatistics.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/TripletsConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/TripletsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/TripletsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DistributeTripletsScoreState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DynamicListTripletContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/EventTripletsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/InContainerTripletFilter.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/ListTripletContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumTripletRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumTripletScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PredicateTripletsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/TripletConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/TripletRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/triplet_predicates.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/TripletContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/TripletDerivativeModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/TripletModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/TripletPredicate.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/TripletScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/triplet_macros.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/internal/TripletContainerIndex.h
   ${PROJECT_BINARY_DIR}/src/container/triplets.cpp
   ${PROJECT_BINARY_DIR}/src/core/triplet_predicates.cpp
   ${PROJECT_BINARY_DIR}/src/kernel/triplets.cpp
   ${PROJECT_BINARY_DIR}/include/IMP/container/QuadContainerSet.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/QuadContainerStatistics.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/QuadsConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/QuadsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/QuadsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DistributeQuadsScoreState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DynamicListQuadContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/EventQuadsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/InContainerQuadFilter.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/ListQuadContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumQuadRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumQuadScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PredicateQuadsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/QuadConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/QuadRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/quad_predicates.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/QuadContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/QuadDerivativeModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/QuadModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/QuadPredicate.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/QuadScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/quad_macros.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/internal/QuadContainerIndex.h
   ${PROJECT_BINARY_DIR}/src/container/quads.cpp
   ${PROJECT_BINARY_DIR}/src/core/quad_predicates.cpp
   ${PROJECT_BINARY_DIR}/src/kernel/quads.cpp
  COMMAND "python" "${PROJECT_SOURCE_DIR}/tools/build/make_containers.py"
  DEPENDS "${PROJECT_SOURCE_DIR}/tools/build/make_containers.py" ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnameContainerSet.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnameContainerStatistics.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnamesConstraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnamesOptimizerState.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnamesRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/DistributeClassnamesScoreState.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/DynamicListClassnameContainer.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/EventClassnamesOptimizerState.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/InContainerClassnameFilter.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ListClassnameContainer.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/MinimumClassnameRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/MinimumClassnameScore.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/PredicateClassnamesRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/ClassnameConstraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/ClassnameRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/classname_predicates.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameContainer.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameDerivativeModifier.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameModifier.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnamePredicate.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameScore.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/classname_macros.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/internal/ClassnameContainerIndex.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/classnames.cpp
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/classname_predicates.cpp
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/classnames.cpp
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/test.py
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/test_state.py
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnameContainerSet.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnameContainerStatistics.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnamesConstraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnamesOptimizerState.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnamesRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/DistributeClassnamesScoreState.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/DynamicListClassnameContainer.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/EventClassnamesOptimizerState.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/InContainerClassnameFilter.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ListClassnameContainer.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/MinimumClassnameRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/MinimumClassnameScore.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/PredicateClassnamesRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/ClassnameConstraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/ClassnameRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/classname_predicates.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameContainer.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameDerivativeModifier.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameModifier.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnamePredicate.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameScore.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/classname_macros.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/internal/ClassnameContainerIndex.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/classnames.cpp
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/classname_predicates.cpp
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/classnames.cpp
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/test.py
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/test_state.py
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnameContainerSet.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnameContainerStatistics.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnamesConstraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnamesOptimizerState.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnamesRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/DistributeClassnamesScoreState.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/DynamicListClassnameContainer.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/EventClassnamesOptimizerState.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/InContainerClassnameFilter.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ListClassnameContainer.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/MinimumClassnameRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/MinimumClassnameScore.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/PredicateClassnamesRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/ClassnameConstraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/ClassnameRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/classname_predicates.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameContainer.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameDerivativeModifier.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameModifier.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnamePredicate.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameScore.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/classname_macros.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/internal/ClassnameContainerIndex.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/classnames.cpp
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/classname_predicates.cpp
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/classnames.cpp
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnameContainerSet.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnameContainerStatistics.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnamesConstraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnamesOptimizerState.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ClassnamesRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/DistributeClassnamesScoreState.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/DynamicListClassnameContainer.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/EventClassnamesOptimizerState.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/InContainerClassnameFilter.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/ListClassnameContainer.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/MinimumClassnameRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/MinimumClassnameScore.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/PredicateClassnamesRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/ClassnameConstraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/ClassnameRestraint.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/classname_predicates.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameContainer.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameDerivativeModifier.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameModifier.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnamePredicate.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/ClassnameScore.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/classname_macros.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/internal/ClassnameContainerIndex.h
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/container/classnames.cpp
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/core/classname_predicates.cpp
   ${PROJECT_SOURCE_DIR}/tools/build/container_templates/kernel/classnames.cpp
  WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
  COMMENT "Making decorator headers")
add_custom_target(IMP-containers ALL DEPENDS ${PROJECT_BINARY_DIR}/include/IMP/container/SingletonContainerSet.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/SingletonContainerStatistics.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/SingletonsConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/SingletonsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/SingletonsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DistributeSingletonsScoreState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DynamicListSingletonContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/EventSingletonsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/InContainerSingletonFilter.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/ListSingletonContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumSingletonRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumSingletonScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PredicateSingletonsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/SingletonConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/SingletonRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/singleton_predicates.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/SingletonContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/SingletonDerivativeModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/SingletonModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/SingletonPredicate.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/SingletonScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/singleton_macros.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/internal/SingletonContainerIndex.h
   ${PROJECT_BINARY_DIR}/src/container/singletons.cpp
   ${PROJECT_BINARY_DIR}/src/core/singleton_predicates.cpp
   ${PROJECT_BINARY_DIR}/src/kernel/singletons.cpp
   ${PROJECT_BINARY_DIR}/test/container/test_particle_restraint.py
   ${PROJECT_BINARY_DIR}/test/container/test_particle_state.py
   ${PROJECT_BINARY_DIR}/include/IMP/container/PairContainerSet.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PairContainerStatistics.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PairsConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PairsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PairsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DistributePairsScoreState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DynamicListPairContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/EventPairsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/InContainerPairFilter.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/ListPairContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumPairRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumPairScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PredicatePairsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/PairConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/PairRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/pair_predicates.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/PairContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/PairDerivativeModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/PairModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/PairPredicate.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/PairScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/pair_macros.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/internal/PairContainerIndex.h
   ${PROJECT_BINARY_DIR}/src/container/pairs.cpp
   ${PROJECT_BINARY_DIR}/src/core/pair_predicates.cpp
   ${PROJECT_BINARY_DIR}/src/kernel/pairs.cpp
   ${PROJECT_BINARY_DIR}/test/container/test_particle_pair_restraint.py
   ${PROJECT_BINARY_DIR}/test/container/test_particle_pair_state.py
   ${PROJECT_BINARY_DIR}/include/IMP/container/TripletContainerSet.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/TripletContainerStatistics.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/TripletsConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/TripletsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/TripletsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DistributeTripletsScoreState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DynamicListTripletContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/EventTripletsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/InContainerTripletFilter.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/ListTripletContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumTripletRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumTripletScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PredicateTripletsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/TripletConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/TripletRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/triplet_predicates.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/TripletContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/TripletDerivativeModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/TripletModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/TripletPredicate.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/TripletScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/triplet_macros.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/internal/TripletContainerIndex.h
   ${PROJECT_BINARY_DIR}/src/container/triplets.cpp
   ${PROJECT_BINARY_DIR}/src/core/triplet_predicates.cpp
   ${PROJECT_BINARY_DIR}/src/kernel/triplets.cpp
   ${PROJECT_BINARY_DIR}/include/IMP/container/QuadContainerSet.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/QuadContainerStatistics.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/QuadsConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/QuadsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/QuadsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DistributeQuadsScoreState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/DynamicListQuadContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/EventQuadsOptimizerState.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/InContainerQuadFilter.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/ListQuadContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumQuadRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/MinimumQuadScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/PredicateQuadsRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/QuadConstraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/QuadRestraint.h
   ${PROJECT_BINARY_DIR}/include/IMP/core/quad_predicates.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/QuadContainer.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/QuadDerivativeModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/QuadModifier.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/QuadPredicate.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/QuadScore.h
   ${PROJECT_BINARY_DIR}/include/IMP/kernel/quad_macros.h
   ${PROJECT_BINARY_DIR}/include/IMP/container/internal/QuadContainerIndex.h
   ${PROJECT_BINARY_DIR}/src/container/quads.cpp
   ${PROJECT_BINARY_DIR}/src/core/quad_predicates.cpp
   ${PROJECT_BINARY_DIR}/src/kernel/quads.cpp)
set_property(TARGET "IMP-containers" PROPERTY FOLDER "IMP")

set( IMP_kernel_LIBRARY_EXTRA_DEPENDENCIES ${IMP_kernel_LIBRARY_EXTRA_DEPENDENCIES} IMP-containers)
set( IMP_core_LIBRARY_EXTRA_DEPENDENCIES ${IMP_core_LIBRARY_EXTRA_DEPENDENCIES} IMP-containers)
set( IMP_container_LIBRARY_EXTRA_DEPENDENCIES ${IMP_container_LIBRARY_EXTRA_DEPENDENCIES} IMP-containers)

set( IMP_kernel_PYTHON_EXTRA_DEPENDENCIES ${IMP_kernel_LIBRARY_EXTRA_DEPENDENCIES} IMP-containers)
set( IMP_core_PYTHON_EXTRA_DEPENDENCIES ${IMP_core_LIBRARY_EXTRA_DEPENDENCIES} IMP-containers)
set( IMP_container_PYTHON_EXTRA_DEPENDENCIES ${IMP_container_LIBRARY_EXTRA_DEPENDENCIES} IMP-containers)

set( IMP_kernel_LIBRARY_EXTRA_SOURCES ${IMP_kernel_LIBRARY_EXTRA_SOURCES} ${CMAKE_BINARY_DIR}/src/kernel/singletons.cpp
   ${CMAKE_BINARY_DIR}/src/kernel/pairs.cpp
   ${CMAKE_BINARY_DIR}/src/kernel/triplets.cpp
   ${CMAKE_BINARY_DIR}/src/kernel/quads.cpp)
set( IMP_core_LIBRARY_EXTRA_SOURCES ${IMP_container_LIBRARY_EXTRA_SOURCES} ${CMAKE_BINARY_DIR}/src/core/singleton_predicates.cpp
   ${CMAKE_BINARY_DIR}/src/core/pair_predicates.cpp
   ${CMAKE_BINARY_DIR}/src/core/triplet_predicates.cpp
   ${CMAKE_BINARY_DIR}/src/core/quad_predicates.cpp)
set( IMP_container_LIBRARY_EXTRA_SOURCES ${IMP_core_LIBRARY_EXTRA_SOURCES} ${CMAKE_BINARY_DIR}/src/container/singletons.cpp
   ${CMAKE_BINARY_DIR}/src/container/pairs.cpp
   ${CMAKE_BINARY_DIR}/src/container/triplets.cpp
   ${CMAKE_BINARY_DIR}/src/container/quads.cpp)

set( IMP_kernel_EXTRA_HEADERS ${IMP_kernel_EXTRA_HEADERS} SingletonContainer.h
   SingletonDerivativeModifier.h
   SingletonModifier.h
   SingletonPredicate.h
   SingletonScore.h
   singleton_macros.h
   PairContainer.h
   PairDerivativeModifier.h
   PairModifier.h
   PairPredicate.h
   PairScore.h
   pair_macros.h
   TripletContainer.h
   TripletDerivativeModifier.h
   TripletModifier.h
   TripletPredicate.h
   TripletScore.h
   triplet_macros.h
   QuadContainer.h
   QuadDerivativeModifier.h
   QuadModifier.h
   QuadPredicate.h
   QuadScore.h
   quad_macros.h)
set( IMP_core_EXTRA_HEADERS ${IMP_core_EXTRA_HEADERS} SingletonConstraint.h
   SingletonRestraint.h
   singleton_predicates.h
   PairConstraint.h
   PairRestraint.h
   pair_predicates.h
   TripletConstraint.h
   TripletRestraint.h
   triplet_predicates.h
   QuadConstraint.h
   QuadRestraint.h
   quad_predicates.h)
set( IMP_container_EXTRA_HEADERS ${IMP_container_EXTRA_HEADERS} SingletonContainerSet.h
   SingletonContainerStatistics.h
   SingletonsConstraint.h
   SingletonsOptimizerState.h
   SingletonsRestraint.h
   DistributeSingletonsScoreState.h
   DynamicListSingletonContainer.h
   EventSingletonsOptimizerState.h
   InContainerSingletonFilter.h
   ListSingletonContainer.h
   MinimumSingletonRestraint.h
   MinimumSingletonScore.h
   PredicateSingletonsRestraint.h
   PairContainerSet.h
   PairContainerStatistics.h
   PairsConstraint.h
   PairsOptimizerState.h
   PairsRestraint.h
   DistributePairsScoreState.h
   DynamicListPairContainer.h
   EventPairsOptimizerState.h
   InContainerPairFilter.h
   ListPairContainer.h
   MinimumPairRestraint.h
   MinimumPairScore.h
   PredicatePairsRestraint.h
   TripletContainerSet.h
   TripletContainerStatistics.h
   TripletsConstraint.h
   TripletsOptimizerState.h
   TripletsRestraint.h
   DistributeTripletsScoreState.h
   DynamicListTripletContainer.h
   EventTripletsOptimizerState.h
   InContainerTripletFilter.h
   ListTripletContainer.h
   MinimumTripletRestraint.h
   MinimumTripletScore.h
   PredicateTripletsRestraint.h
   QuadContainerSet.h
   QuadContainerStatistics.h
   QuadsConstraint.h
   QuadsOptimizerState.h
   QuadsRestraint.h
   DistributeQuadsScoreState.h
   DynamicListQuadContainer.h
   EventQuadsOptimizerState.h
   InContainerQuadFilter.h
   ListQuadContainer.h
   MinimumQuadRestraint.h
   MinimumQuadScore.h
   PredicateQuadsRestraint.h)

