#ifndef CF_GooglePerfTools_ProfiledTestFixture_hpp
#define CF_GooglePerfTools_ProfiledTestFixture_hpp

#include <boost/filesystem.hpp>
#include <boost/test/test_observer.hpp>

#include <coolfluid_profiling_config.h>

using namespace CF;
using namespace CF::Common;

////////////////////////////////////////////////////////////////////////////////

namespace CF {
namespace Tools {
namespace GooglePerf { class GooglePerfToolsModule; }
namespace Testing {

////////////////////////////////////////////////////////////////////////////////


#ifdef CF_BUILD_GooglePerfTools
/// Any test using this fixture (or a derivative) will be profiled
class ProfiledTestFixture {
public:

  ProfiledTestFixture();
  ~ProfiledTestFixture();

  /// Start profiling when a test starts
  void test_unit_start( boost::unit_test::test_unit const& );

  /// Stop profiling when a test ends and process the file
  void test_unit_finish( boost::unit_test::test_unit const& );

protected:
  /// The profiling module that is used
  CF::Tools::GooglePerf::GooglePerfToolsModule& m_profiler;
  /// Start of the profile output name
  std::string m_prefix;
  /// Directory to store the profile data in
  boost::filesystem::path m_profile_dir;
private:
  /// Storage for the file being profiled to
  std::string m_current_filename;
  /// The full command that was ran
  std::string m_command;
};
#else

class ProfiledTestFixture {
public:
  ProfiledTestFixture();
};

#endif

////////////////////////////////////////////////////////////////////////////////

} // Testing
} // Tools
} // CF

////////////////////////////////////////////////////////////////////////////////

#endif // CF_GooglePerfTools_ProfiledTestFixture_hpp
