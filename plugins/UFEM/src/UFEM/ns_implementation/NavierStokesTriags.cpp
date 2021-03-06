// Copyright (C) 2010-2011 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include <coolfluid-ufem-config.hpp>

#include "../NavierStokes.hpp"
#include "../NavierStokesAssembly.hpp"

namespace cf3 {
namespace UFEM {

using namespace common;
using namespace solver;
using namespace solver::actions;
using namespace solver::actions::Proto;

void NavierStokes::set_triag_assembly(const bool use_specialization)
{
#ifdef CF3_UFEM_ENABLE_TRIAGS
  if(use_specialization)
  {
    set_assembly_expression< boost::mpl::vector0<>, boost::mpl::vector1<mesh::LagrangeP1::Triag2D> >("AssemblyTriags");
  }
  else
  {
    set_assembly_expression< boost::mpl::vector1<mesh::LagrangeP1::Triag2D>, boost::mpl::vector0<> >("AssemblyTriags");
  }
#endif
}


} // UFEM
} // cf3
