/**
 * \file IMP/atom/CADihedralRestraint.h
 * \brief Dihedral restraint between five residues in CA-only representation.
 *
 *  Copyright 2007-2015 IMP Inventors. All rights reserved.
 *
 */

#ifndef IMPATOM_CA_DIHEDRAL_RESTRAINT_H
#define IMPATOM_CA_DIHEDRAL_RESTRAINT_H

#include "atom_config.h"

#include <IMP/kernel/Restraint.h>
#include <IMP/Particle.h>
#include <IMP/generic.h>
#include <map>

IMPATOM_BEGIN_NAMESPACE

//! Dihedral restraint between five residues in CA-only representation
/** This restraint is designed to be used in conjunction with a CA-only
    representation; each restraint is applied to five CA atoms that
    correspond to five residues that are adjacent in sequence.
    A simple statistical potential is applied to score the pair of dihedral
    angles that involve the five atoms. Currently, no splining or other
    smoothing is done and no derivatives are calculated.
 */
class IMPATOMEXPORT CADihedralRestraint : public kernel::Restraint
{
public:
  //! Create the dihedral restraint.
  /** The value of the restraint is simply score[i*N+j] where phi0[i]
      is the closest angle in phi0 to that between p1-p2-p3-p4,
      phi1[j] is the closest angle in phi1 to that between p2-p3-p4-p5,
      and N is the number of elements in phi0.
      \param[in] p1 First CA atom
      \param[in] p2 Second CA atom
      \param[in] p3 Third CA atom
      \param[in] p4 Fourth CA atom
      \param[in] p5 Fifth CA atom
      \param[in] phi0 First list of angles for which scores are available
      \param[in] phi1 Second list of angles for which scores are available
      \param[in] score List of scores that correspond to phi0*phi1
   */
  CADihedralRestraint(Particle* p1, Particle* p2, Particle* p3,
                      Particle* p4, Particle* p5,
                      Floats phi0,  Floats phi1,
                      Floats score);

  virtual double
  unprotected_evaluate(IMP::kernel::DerivativeAccumulator *accum)
     const IMP_OVERRIDE;
  virtual IMP::kernel::ModelObjectsTemp do_get_inputs() const IMP_OVERRIDE;
  IMP_OBJECT_METHODS(CADihedralRestraint);

private:
  base::PointerMember<Particle> p_[5];
  Floats phi0_;
  Floats phi1_;
  Floats score_;

  double get_distance(double v0, double v1) const;
  int get_closest(std::vector<double> const& vec, double value) const;

};

IMPATOM_END_NAMESPACE

#endif  /* IMPATOM_CA_DIHEDRAL_RESTRAINT_H */
