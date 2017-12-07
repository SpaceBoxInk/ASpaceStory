#include "terrainTest.hpp"

#include "../src/model/MAssException.hpp"
#include "../src/model/MTerrain.hpp"

#include <cute/cute_test.h>
#include <cute/cute.h>
#include <cute/cute_throws.h>

void borderTest()
{
  MTerrain t;

  ASSERT_THROWSM("Test (-1,0)", t(-1, 0), MExceptionOutOfTerrain);
  ASSERT_THROWSM("Test (0,-1)", t(0, -1), MExceptionOutOfTerrain);

  // TODO : test to complete
  ASSERT_THROWSM("Test (-1,0)", t(-1, 0), MExceptionOutOfTerrain);
  ASSERT_THROWSM("Test (-1,0)", t(-1, 0), MExceptionOutOfTerrain);
}

cute::suite makeTerrainTestSuite()
{
  cute::suite suite;
  suite.push_back(CUTE(borderTest));
  return suite;
}
