// Copyright (C) 2010-2011 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Test module for CF::Math::LSS where testing on a distributed matrix."

////////////////////////////////////////////////////////////////////////////////

#include <boost/test/unit_test.hpp>

#include "Common/Log.hpp"
#include "Common/MPI/PE.hpp"
#include "Math/LSS/System.hpp"

////////////////////////////////////////////////////////////////////////////////

using namespace CF;
using namespace CF::Math;
using namespace CF::Math::LSS;

////////////////////////////////////////////////////////////////////////////////

struct LSSDistributedMatrixFixture
{
  /// common setup for each test case
  LSSDistributedMatrixFixture()
  {
    m_argc = boost::unit_test::framework::master_test_suite().argc;
    m_argv = boost::unit_test::framework::master_test_suite().argv;
  }

  /// common tear-down for each test case
  ~LSSDistributedMatrixFixture()
  {
  }

  /// common params
  int m_argc;
  char** m_argv;
};

////////////////////////////////////////////////////////////////////////////////

BOOST_FIXTURE_TEST_SUITE( LSSDistributedMatrixSuite, LSSDistributedMatrixFixture )

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE( init_parallel_environment )
{
  Common::Comm::PE::instance().init(m_argc,m_argv);
  BOOST_CHECK_EQUAL(Common::Comm::PE::instance().is_active(),true);
  CFinfo.setFilterRankZero(false);
}

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE( finalize_parallel_environment )
{
  CFinfo.setFilterRankZero(true);
  Common::Comm::PE::instance().finalize();
  BOOST_CHECK_EQUAL(Common::Comm::PE::instance().is_active(),false);
}

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

