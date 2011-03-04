// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_GUI_Client_Core_NPlotXY_hpp
#define CF_GUI_Client_Core_NPlotXY_hpp

#include <boost/multi_array.hpp>

#include "GUI/Client/Core/CNode.hpp"

class QString;

namespace CF {
namespace GUI {
namespace ClientCore {

class ClientCore_API NPlotXY :
    public QObject,
    public CNode
{
  Q_OBJECT

public: //typedefs

  typedef boost::shared_ptr<NPlotXY> Ptr;
  typedef boost::shared_ptr<NPlotXY const> ConstPtr;
  typedef boost::multi_array<Real,2> PlotData;
  typedef boost::shared_ptr< PlotData > PlotDataPtr;

public:

  NPlotXY(const QString & name);

  virtual QString toolTip() const;

  void convergence_history ( Common::Signal::arg_t& node );

}; //  XYPlot


class ClientCore_API NPlotXYNotifier{
public:

  /// signal for the set_xy_data of graph.
  /*
  typedef boost::signals2::signal< void ( std::vector<double>&, std::vector<double>& ) >  sig_type;
  */
  typedef boost::signals2::signal< void ( NPlotXY::PlotDataPtr & fcts,
                                          std::vector<QString> & fct_label) >  sig_type;

  /// implementation of instance that return this ( staticly ).
  static NPlotXYNotifier & instance(){
     static NPlotXYNotifier inst; // create static instance
     return inst; // return the static instance
  }

  sig_type notify_history;

private:
  /// Empty constructor.
  NPlotXYNotifier(){}

  /// Destructor.
  ~NPlotXYNotifier(){}
};


} // ClientCore
} // GUI
} // CF


#endif // CF_GUI_Client_Core_NPlotXY_hpp