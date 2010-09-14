/**
 *  \file RegistrationResult.h
 *  \brief Registration results class
 *  Copyright 2007-2010 IMP Inventors. All rights reserved.
*/

#ifndef IMPEM2D_REGISTRATION_RESULT_H
#define IMPEM2D_REGISTRATION_RESULT_H

#include "IMP/em2d/em2d_config.h"
#include "IMP/em2d/align2D.h"
#include "IMP/em2d/internal/rotation_helper.h"
#include "IMP/em/Image.h"
#include "IMP/em/ImageReaderWriter.h"
#include "IMP/em/SpiderReaderWriter.h"
#include "IMP/algebra/Vector3D.h"
#include "IMP/algebra/VectorD.h"
#include "IMP/algebra/Vector2D.h"
#include "IMP/algebra/Rotation3D.h"
#include "IMP/algebra/Rotation2D.h"
#include "IMP/Pointer.h"
#include <string>

IMPEM2D_BEGIN_NAMESPACE

//! Class to manage registration results
/**
  \note  Stores the rotation and in-plane translation needed to register a
  model
**/

class IMPEM2DEXPORT RegistrationResult {
public:

  RegistrationResult() {
    shift_[0]=0.0;   shift_[1]=0.0;
    ccc_=0.0;
    name_="";
    index_=0;
    set_rotation(0,0,0);
  }

  RegistrationResult(double phi,double theta,double psi,double shift_x,
                  double shift_y,long index=0,double ccc=0.0,String name="") {
    IMP_LOG(IMP::VERBOSE," initialzing RegistrationResult " << std::endl);
    shift_[0]=shift_x; shift_[1]=shift_y;
    ccc_=ccc;
    name_=name;
    index_=index;
    set_rotation(phi,theta,psi);
    IMP_LOG(IMP::VERBOSE," end init RegistrationResult " << std::endl);

  }

  RegistrationResult(algebra::Rotation3D &R,algebra::Vector2D &shift,
                      long index=0,double ccc=0.0,String name="") {
    shift_[0]=shift[0]; shift_[1]=shift[1];
    ccc_=ccc;
    name_=name;
    index_=index;
    set_rotation(R);
  }

  inline double get_Phi() const { return phi_;}
  inline double get_Theta() const { return theta_;}
  inline double get_Psi() const { return psi_;}
  inline algebra::Vector2D get_shift() const { return shift_;}
  inline algebra::Vector3D get_shift3D() const {
    return algebra::Vector3D(shift_[0],shift_[1],0.0);
  }
  inline long get_index() const { return index_;}
  inline String get_name() const { return name_;}
  inline double get_ccc() const { return ccc_;}
  inline void set_rotation(double phi,double theta,double psi) {
    phi_=phi; theta_=theta; psi_=psi;
    R_=algebra::get_rotation_from_fixed_zyz(phi_,theta_,psi_);
  }

  void set_rotation(algebra::Rotation3D &R);

  inline void set_ccc(double ccc) { ccc_=ccc;}
  inline void set_shift(algebra::Vector2D shift) { shift_=shift;}
  inline void set_shift(double shift_y,double shift_x) {
    shift_[0]=shift_y; shift_[1]=shift_x;
  }
  inline void set_index(long index) {index_=index;}
  inline void set_name(String name) {name_=name;}

  inline void add_in_plane_transformation(algebra::Transformation2D &t) {
    set_rotation(phi_,theta_,psi_+t.get_rotation().get_angle());
    // The translation is understood as a shift (in pixels)
    shift_ += t.get_translation();
  }

  void show(std::ostream& out) const {
    algebra::VectorD<4> quaternion=R_.get_quaternion();
    out << "Name: "  << get_name() <<  " Index: " << get_index()
    << " (Phi,Theta,Psi) = ( " << phi_ << " , " << theta_ << " , "
    << psi_ << " ) | Shift (x,y) " << get_shift()  << " CCC = " << get_ccc()
    <<  " Quaternion " << quaternion;
  }

  //! Writes a result line to a file
//  inline void write(std::ofstream& out) const {
  inline void write(std::ostream& out = std::cout) const {
    algebra::VectorD<4> quaternion=R_.get_quaternion();
    char c='|';
    out << get_index() <<c<< phi_ <<c<< theta_ <<c<< psi_
    <<c<< quaternion[0] <<c<< quaternion[1] <<c<< quaternion[2]
    <<c<< quaternion[3] <<c<< get_shift()[0] <<c<< get_shift()[1]
    <<c<< get_ccc() <<c<< std::endl;
  }

  //! read
  void read(const String &s);

  //! Gets a random result
  void set_random_registration(unsigned long index,double maximum_shift);

  //! Returns the rotation for the 3 projection angles
  inline algebra::Rotation3D get_rotation() const {
    return R_;
  }

  //! Sets the registration results to the header of an image
  void set_in_image(em::Image &im);

  //! Reads the registration parameters from an image and puts it in this class
  /**
    \param[in] im the image
   **/
  void read_from_image(em::Image &im);


  ~RegistrationResult();

protected:
  //! Translation in pixels and the rows first (y rows, x columns)
  algebra::Vector2D shift_;
  //! Cross correlation coefficient
  double ccc_;
  //!
  //! name and index of the projection compared
  String name_;
  long index_;
  //! Euler angles (ZYZ)
  double phi_;
  double theta_;
  double psi_;
  algebra::Rotation3D R_;
  // false when the RegistrationResult is built from a rotation directly
  bool angles_defined_;
};

IMP_OUTPUT_OPERATOR(RegistrationResult);

// typedef std::vector<RegistrationResult> RegistrationResults;
// Does the same as above
IMP_VALUES(RegistrationResult,RegistrationResults);

//! Checks the best of 2 cross correlation coefficients
inline bool better_ccc(RegistrationResult &r1,RegistrationResult &r2) {
  return r1.get_ccc()<r2.get_ccc();
}

//! Reads a set of registration results
IMPEM2DEXPORT RegistrationResults read_registration_results(String filename);

//! Writes a set of registration results
IMPEM2DEXPORT void  write_registration_results(
                        String filename,RegistrationResults results);


//! Provides a set of random registration results (or parameters)
/**
  \param[in] n the number of requested results
  \param[in] maximum_shift shift from the center in pixels
**/
IMPEM2DEXPORT RegistrationResults get_random_registration_results
      (unsigned long n,double maximum_shift=5.0);


//! Provides a set of registration results with directions of projection
//!      evenly distributed in the semisphere
/**
  \param[in] n_projections the number of requested projections
**/
IMPEM2DEXPORT RegistrationResults
    evenly_distributed_registration_results(unsigned long n_projections);

//! returns true if the ccc of the first is higher than the second
IMPEM2DEXPORT bool compare_registration_results(const RegistrationResult &rr1,
                                  const RegistrationResult &rr2);


inline double random_between_zero_and_one() {
  return ((double)rand() /((double)RAND_MAX+1));
}

IMPEM2D_END_NAMESPACE

#endif /* IMPEM2D_REGISTRATION_RESULT_H */
