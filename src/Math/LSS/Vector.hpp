// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_Math_LSS_Vector_hpp
#define CF_Math_LSS_Vector_hpp

////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/utility.hpp>

#include "Math/LibMath.hpp"
#include "Common/MPI/CommPattern.hpp"
#include "Common/Log.hpp"
#include "Math/LSS/BlockAccumulator.hpp"

////////////////////////////////////////////////////////////////////////////////////////////

/**
  @file Vector.hpp implementation of LSS::Vector
  @author Tamas Banyai
**/

////////////////////////////////////////////////////////////////////////////////////////////

namespace CF {
namespace Math {
namespace LSS {

////////////////////////////////////////////////////////////////////////////////////////////

class Math_API Vector : public CF::Common::Component {
public:

  /// @name CREATION, DESTRUCTION AND COMPONENT SYSTEM
  //@{

  /// pointer to this type
  typedef boost::shared_ptr<Vector> Ptr;

  /// const pointer to this type
  typedef boost::shared_ptr<Vector const> ConstPtr;

  /// name of the type
  static std::string type_name () { return "Vector"; }

  /// Accessor to solver type
  virtual const std::string solvertype() = 0;

  /// Default constructor
  Vector(const std::string& name) : Component(name) { }

  /// Setup sparsity structure
  virtual void create(const Common::Comm::CommPattern& cp, Uint neq) = 0;

  /// Deallocate underlying data
  virtual void destroy() = 0;


  //@} END CREATION, DESTRUCTION AND COMPONENT SYSTEM

  /// @name INDIVIDUAL ACCESS
  //@{

  /// Set value at given location in the matrix
  virtual void set_value(const Uint irow, const Real value) = 0;

  /// Add value at given location in the matrix
  virtual void add_value(const Uint irow, const Real value) = 0;

  /// Get value at given location in the matrix
  virtual void get_value(const Uint irow, Real& value) = 0;

  /// Set value at given location in the matrix
  virtual void set_value(const Uint iblockrow, const Uint ieq, const Real value) = 0;

  /// Add value at given location in the matrix
  virtual void add_value(const Uint iblockrow, const Uint ieq, const Real value) = 0;

  /// Get value at given location in the matrix
  virtual void get_value(const Uint iblockrow, const Uint ieq, Real& value) = 0;

  //@} END INDIVIDUAL ACCESS

  /// @name EFFICCIENT ACCESS
  //@{

  /// Set a list of values to rhs
  virtual void set_rhs_values(const BlockAccumulator& values) = 0;

  /// Add a list of values to rhs
  virtual void add_rhs_values(const BlockAccumulator& values) = 0;

  /// Get a list of values from rhs
  virtual void get_rhs_values(BlockAccumulator& values) = 0;

  /// Set a list of values to sol
  virtual void set_sol_values(const BlockAccumulator& values) = 0;

  /// Add a list of values to sol
  virtual void add_sol_values(const BlockAccumulator& values) = 0;

  /// Get a list of values from sol
  virtual void get_sol_values(BlockAccumulator& values) = 0;

  /// Reset Vector
  virtual void reset(Real reset_to=0.) = 0;

  //@} END EFFICCIENT ACCESS

  /// @name MISCELLANEOUS
  //@{

  /// Print to wherever
  virtual void print(Common::LogStream& stream) = 0;

  /// Print to wherever
  virtual void print(std::ostream& stream) = 0;

  /// Print to file given by filename
  virtual void print(const std::string& filename, std::ios_base::openmode mode = std::ios_base::out ) = 0;

  /// Accessor to the state of create
  virtual const bool is_created() = 0;

  /// Accessor to the number of equations
  virtual const Uint neq() = 0;

  /// Accessor to the number of block rows
  virtual const Uint blockrow_size() = 0;

  //@} END MISCELLANEOUS

  /// @name TEST ONLY
  //@{

  /// exports the vector into big linear array
  /// @attention only for debug and utest purposes
  virtual void data(std::vector<Real>& values) = 0;

  //@} END TEST ONLY

};

////////////////////////////////////////////////////////////////////////////////////////////

} // namespace LSS
} // namespace Math
} // namespace CF

#endif // CF_Math_LSS_Vector_hpp
