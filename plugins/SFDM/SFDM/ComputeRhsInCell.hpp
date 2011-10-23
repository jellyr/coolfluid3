// Copyright (C) 2010-2011 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_solver_Actions_ComputeRhsInCell_hpp
#define CF_solver_Actions_ComputeRhsInCell_hpp

#include "solver/Actions/CLoopOperation.hpp"
#include "SFDM/LibSFDM.hpp"
#include "common/Table.hpp"
#include "math/MatrixTypes.hpp"
#include "mesh/CFieldView.hpp"
#include "mesh/MeshElements.hpp"

/////////////////////////////////////////////////////////////////////////////////////

namespace cf3 {
namespace solver { class State; class Physics; }
namespace RiemannSolvers { class RiemannSolver; }
namespace SFDM {

  class Reconstruct;
  class Flux;
  class ShapeFunction;

///////////////////////////////////////////////////////////////////////////////////////

/// @class ComputeRhsInCell
/// @brief Computes the RHS in one cell.
///
/// It is the workhorse of SFD Solver.

class SFDM_API ComputeRhsInCell : public solver::Actions::CLoopOperation {

public: // typedefs

  /// pointers
  typedef boost::shared_ptr<ComputeRhsInCell> Ptr;
  typedef boost::shared_ptr<ComputeRhsInCell const> ConstPtr;

public: // functions
  /// Contructor
  /// @param name of the component
  ComputeRhsInCell ( const std::string& name );

  /// Virtual destructor
  virtual ~ComputeRhsInCell() {};

  /// Get the class name
  static std::string type_name () { return "ComputeRhsInCell"; }

  /// execute the action
  virtual void execute ();

  RiemannSolvers::RiemannSolver& riemann_solver() { return *m_riemann_solver; }

private: // helper functions

  void config_solution();
  void config_residual();
  void config_jacobian_determinant();
  void config_wavespeed();
  void config_solution_physics();
  void trigger_elements();

  void build_riemann_solver();

  RealRowVector    to_row_vector(common::Table<Real>::ConstRow row) const ;
  RealMatrix       to_matrix(mesh::CMultiStateFieldView::View data) const ;

private: // data

  boost::shared_ptr<mesh::CMultiStateFieldView> m_solution;
  boost::shared_ptr<mesh::CMultiStateFieldView> m_residual;
  boost::shared_ptr<mesh::CMultiStateFieldView> m_jacobian_determinant;

  boost::shared_ptr<mesh::CScalarFieldView> m_wave_speed;

  boost::shared_ptr<Reconstruct> m_reconstruct_solution;
  boost::shared_ptr<Reconstruct> m_reconstruct_flux;

  boost::weak_ptr<mesh::MeshElements> m_mesh_elements;

  boost::shared_ptr<RiemannSolvers::RiemannSolver> m_riemann_solver;
  boost::weak_ptr<solver::State> m_sol_state;
  boost::shared_ptr<solver::Physics> m_sol_vars;

  boost::shared_ptr<SFDM::ShapeFunction const> m_solution_sf;
  boost::shared_ptr<SFDM::ShapeFunction const> m_flux_sf;

  std::vector<RealVector> m_normal;
  Uint m_dimensionality;
  Uint m_nb_vars;
  Real left_wave_speed;
  Real right_wave_speed;
  RealVector flux;
  Real max_wave_speed;
  RealMatrix flux_in_line;
  RealMatrix flux_grad_in_line;
  RealMatrix solution;
  RealMatrix neighbor_solution;
};

/////////////////////////////////////////////////////////////////////////////////////

} // SFDM
} // CF

/////////////////////////////////////////////////////////////////////////////////////

#endif // CF_solver_Actions_ComputeRhsInCell_hpp
