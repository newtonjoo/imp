%module(directors="1") IMP

%{
#include "IMP.h"
%}

%include "std_vector.i"
%include "std_map.i"
%include "std_string.i"
%include "std_pair.i"

%include "IMP_macros.i"
%include "IMP_exceptions.i"

/* Return derivatives from unary functions */
%include "typemaps.i"
%apply double &OUTPUT { IMP::Float& deriv };

namespace IMP {
  %pythonprepend Model::add_particle %{
        args[1].thisown=0
  %}
  %pythonprepend Model::add_restraint %{
        args[1].thisown=0
  %}
  %pythonprepend Model::add_score_state %{
        args[1].thisown=0
  %}
  %pythonprepend Optimizer::add_optimizer_state %{
        args[1].thisown=0
  %}
  %pythonprepend RestraintSet::add_restraint %{
        args[1].thisown=0
  %}
  %pythonprepend NonbondedListScoreState::add_bonded_list %{
        args[1].thisown=0
  %}
  %pythonprepend DistanceRestraint::DistanceRestraint %{
        args[0].thisown=0
  %}
  %pythonprepend AngleRestraint::AngleRestraint %{
        args[0].thisown=0
  %}
  %pythonprepend DihedralRestraint::DihedralRestraint %{
        args[0].thisown=0
  %}
  %pythonprepend TorusRestraint::TorusRestraint %{
        args[3].thisown=0
  %}
  %pythonprepend NonbondedRestraint::NonbondedRestraint %{
        args[0].thisown=0
  %}
  %pythonprepend BondDecoratorRestraint::BondDecoratorRestraint %{
        args[0].thisown=0
  %}
  %pythonprepend SingletonListRestraint::SingletonListRestraint %{
        args[0].thisown=0
  %}
  %pythonprepend PairListRestraint::PairListRestraint %{
        args[0].thisown=0
  %}
  %pythonprepend TripletChainRestraint::TripletChainRestraint %{
        args[0].thisown=0
  %}
  %pythonprepend ConnectivityRestraint::ConnectivityRestraint %{
        args[0].thisown=0
  %}
  %pythonprepend DistancePairScore::DistancePairScore %{
        args[0].thisown=0
  %}
  %pythonprepend SphereDistancePairScore::SphereDistancePairScore %{
        args[0].thisown=0
  %}
  %pythonprepend DistanceToSingletonScore::DistanceToSingletonScore %{
        args[0].thisown=0
  %}
  %pythonprepend AttributeSingletonScore::AttributeSingletonScore %{
        args[0].thisown=0
  %}
  %pythonprepend AngleTripletScore::AngleTripletScore %{
        args[0].thisown=0
  %}
  %pythonprepend MonteCarlo::add_mover %{
        args[1].thisown=0
  %}
  %pythonprepend MonteCarlo::set_local_optimizer %{
        args[1].thisown=0
  %}
}

/* Don't wrap internal functions */
%ignore IMP::internal::evaluate_distance_pair_score;

/* Map C++ operators to equivalent Python methods */
%rename(__getitem__) IMP::Vector3D::operator[];

%feature("director");

%include "IMP/internal/Object.h"
%include "IMP/Index.h"
%include "IMP/base_types.h"
%include "IMP/VersionInfo.h"
%include "IMP/Key.h"
%include "IMP/UnaryFunction.h"
%include "IMP/unary_functions/Harmonic.h"
%include "IMP/unary_functions/HarmonicLowerBound.h"
%include "IMP/unary_functions/HarmonicUpperBound.h"
%include "IMP/unary_functions/OpenCubicSpline.h"
%include "IMP/unary_functions/ClosedCubicSpline.h"
%include "IMP/unary_functions/Cosine.h"
%include "IMP/unary_functions/Linear.h"
%include "IMP/DerivativeAccumulator.h"
%include "IMP/Restraint.h"
%include "IMP/ScoreState.h"
%include "IMP/OptimizerState.h"
%include "IMP/log.h"
%include "IMP/Model.h"
%include "IMP/PairScore.h"
%include "IMP/SingletonScore.h"
%include "IMP/TripletScore.h"
%include "IMP/Particle.h"
%include "IMP/Vector3D.h"
%include "IMP/DecoratorBase.h"
%include "IMP/decorators/HierarchyDecorator.h"
%include "IMP/decorators/MolecularHierarchyDecorator.h"
%include "IMP/decorators/NameDecorator.h"
%include "IMP/decorators/ResidueDecorator.h"
%include "IMP/decorators/XYZDecorator.h"
%include "IMP/decorators/bond_decorators.h"
%include "IMP/decorators/AtomDecorator.h"
%include "IMP/Optimizer.h"
%include "IMP/optimizers/SteepestDescent.h"
%include "IMP/optimizers/ConjugateGradients.h"
%include "IMP/optimizers/MolecularDynamics.h"
%include "IMP/optimizers/Mover.h"
%include "IMP/optimizers/MoverBase.h"
%include "IMP/optimizers/MonteCarlo.h"
%include "IMP/optimizers/movers/BallMover.h"
%include "IMP/optimizers/movers/NormalMover.h"
%include "IMP/optimizers/states/VRMLLogOptimizerState.h"
%include "IMP/optimizers/states/CMMLogOptimizerState.h"
%include "IMP/optimizers/states/VelocityScalingOptimizerState.h"
%include "IMP/pair_scores/DistancePairScore.h"
%include "IMP/pair_scores/SphereDistancePairScore.h"
%include "IMP/singleton_scores/DistanceToSingletonScore.h"
%include "IMP/singleton_scores/AttributeSingletonScore.h"
%include "IMP/triplet_scores/AngleTripletScore.h"
%include "IMP/restraints/DistanceRestraint.h"
%include "IMP/restraints/AngleRestraint.h"
%include "IMP/restraints/TripletChainRestraint.h"
%include "IMP/restraints/DihedralRestraint.h"
%include "IMP/restraints/ConnectivityRestraint.h"
%include "IMP/restraints/NonbondedRestraint.h"
%include "IMP/restraints/BondDecoratorRestraint.h"
%include "IMP/restraints/SingletonListRestraint.h"
%include "IMP/restraints/PairListRestraint.h"
%include "IMP/restraints/RestraintSet.h"
%include "IMP/score_states/BondedListScoreState.h"
%include "IMP/score_states/MaxChangeScoreState.h"
%include "IMP/score_states/NonbondedListScoreState.h"
%include "IMP/score_states/AllNonbondedListScoreState.h"
%include "IMP/score_states/BondDecoratorListScoreState.h"
%include "IMP/score_states/QuadraticNonbondedListScoreState.h"
%include "IMP/score_states/QuadraticAllNonbondedListScoreState.h"
%include "IMP/score_states/QuadraticBipartiteNonbondedListScoreState.h"
%include "IMP/score_states/BipartiteNonbondedListScoreState.h"

namespace IMP {
  %template(ParticleIndex) Index<ParticleTag>;
  %template(RestraintIndex) Index<RestraintTag>;
  %template(ScoreStateIndex) Index<ScoreStateTag>;
  %template(OptimizerStateIndex) Index<OptimizerStateTag>;
  %template(MoverIndex) Index<Mover>;
  %template(BondedListIndex) Index<BondedListScoreState>;
  %template(FloatKey) Key<Float>;
  %template(IntKey) Key<Int>;
  %template(StringKey) Key<String>;
  %template(AtomType) Key<AtomTypeTag>;
  %template(ResidueType) Key<ResidueTypeTag>;     
  %template(show_named_hierarchy) show<NameDecorator>;
  %template(show_molecular_hierarchy) show<MolecularHierarchyDecorator>;
  %template(Particles) ::std::vector<Particle*>;
  %template(ParticlePair) ::std::pair<IMP::Particle*, IMP::Particle*>;
  %template(ParticlePairs) ::std::vector<ParticlePair>;
  %template(Restraints) ::std::vector<Restraint*>;
  %template(ScoreStates) ::std::vector<ScoreState*>;
  %template(OptimizerStates) ::std::vector<OptimizerState*>;
  %template(ParticleIndexes) ::std::vector<ParticleIndex>;
  %template(FloatKeys) ::std::vector<FloatKey>;
  %template(StringKeys) ::std::vector<StringKey>;
  %template(IntKeys) ::std::vector<IntKey>;
  %template(Floats) ::std::vector<Float>;
  %template(Strings) ::std::vector<String>;
  %template(Ints) ::std::vector<Int>;
}
