#include "Common/CLink.hpp"
#include "Common/BasicExceptions.hpp"

namespace CF {
namespace Common {

////////////////////////////////////////////////////////////////////////////////

CLink::CLink ( const CName& name, const CPath& parent_path ) : Component ( name )
{
  m_is_link = true;
}

////////////////////////////////////////////////////////////////////////////////

CLink::~CLink()
{
}

////////////////////////////////////////////////////////////////////////////////

SafePtr<Component> CLink::get ()
{
  return m_link_component.lock().get();
}

////////////////////////////////////////////////////////////////////////////////

void CLink::link_to ( boost::shared_ptr<Component> lnkto )
{
  if (lnkto->is_link())
    throw SetupError(FromHere(), "Cannot link a CLink to another CLink");

  m_link_component = lnkto;
}

////////////////////////////////////////////////////////////////////////////////

} // Common
} // CF
