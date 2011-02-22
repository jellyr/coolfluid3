// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_Mesh_CMeshWriter_hpp
#define CF_Mesh_CMeshWriter_hpp

////////////////////////////////////////////////////////////////////////////////

#include <boost/filesystem/path.hpp>

#include "Common/ComponentPredicates.hpp"

#include "Mesh/LibMesh.hpp"
#include "Mesh/CMesh.hpp"
#include "Mesh/CElements.hpp"

namespace CF {
namespace Mesh {

  class CNodes;
  class CField2;

////////////////////////////////////////////////////////////////////////////////

/// CMeshWriter component class
/// This class serves as a component that that will write
/// the mesh to a file
/// @author Willem Deconinck
class Mesh_API CMeshWriter : public Common::Component {

public: // typedefs

  /// pointer to this type
  typedef boost::shared_ptr<CMeshWriter> Ptr;
  typedef boost::shared_ptr<CMeshWriter const> ConstPtr;

public: // functions

  /// Contructor
  /// @param name of the component
  CMeshWriter ( const std::string& name );

  /// Virtual destructor
  virtual ~CMeshWriter();

  /// Get the class name
  static std::string type_name () { return "CMeshWriter"; }

  // --------- Signals ---------

  void signal_write( Common::Signal::arg_t& node  );

  // --------- Direct access ---------

  virtual std::string get_format() = 0;

  virtual std::vector<std::string> get_extensions() = 0;

  virtual void write_from_to(const CMesh::Ptr& mesh, boost::filesystem::path& path) = 0;

  void write();

  void set_fields(const std::vector<boost::shared_ptr<CField2> >& fields);

private: // functions

  void config_fields();

protected: // classes

  class IsGroup
  {
   public:
     IsGroup () {}

     bool operator()(const Component& component)
     {
       return count(Common::find_components<CEntities>(component));
     }

  }; // IsGroup

protected:

  CMesh::Ptr m_mesh;

  typedef std::map<CNodes*,std::list<CElements*> > NodesElementsMap;
  NodesElementsMap m_all_nodes;
  Uint m_coord_dim;
  Uint m_max_dimensionality;

  void compute_mesh_specifics();

  std::vector<boost::weak_ptr<CField2> > m_fields;

};

////////////////////////////////////////////////////////////////////////////////

} // Mesh
} // CF

////////////////////////////////////////////////////////////////////////////////

#endif // CF_Mesh_CMeshWriter_hpp
