/**
 * @file testRuner.cpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 6 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "terrainTest.hpp"

#include <cute/cute_runner.h>
#include <cute/cute_suite.h>
#include <cute/cute_xml_file.h>
#include <cute/ide_listener.h>
#include <cute/xml_listener.h>
#include <cstdlib>



bool runAllTests(int argc, char const *argv[])
{
  //TODO add your test here
  cute::xml_file_opener xmlfile(argc, argv);
  cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);

  auto runner = cute::makeRunner(lis, argc, argv);

  cute::suite terrainTest = makeTerrainTestSuite();
  bool success = runner(terrainTest, "AllTests");

  // TODO : add test
  //  success &= runner(dz, "dz");
  return success;
}

int main(int argc, char const *argv[])
{
  return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
