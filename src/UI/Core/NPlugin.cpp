// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "Common/XML/SignalOptions.hpp"
#include "UI/Core/NPlugin.hpp"

using namespace CF::Common;
using namespace CF::Common::XML;

////////////////////////////////////////////////////////////////////////////

namespace CF {
namespace UI {
namespace Core {

////////////////////////////////////////////////////////////////////////////

NPlugin::NPlugin(const std::string & name)
  : CNode(name.c_str(), "NPlugin", CNode::LOCAL_NODE)
{

}

////////////////////////////////////////////////////////////////////////////

NPlugin::~NPlugin()
{

}

////////////////////////////////////////////////////////////////////////////

QString NPlugin::toolTip() const
{
  return QString("%1 plugin").arg( name().c_str() );
}

////////////////////////////////////////////////////////////////////////////

} // Core
} // UI
} // CF