#include "terrainTest.hpp"

#include "../src/model/MAssException.hpp"
#include "../src/model/MCoordonnees.hpp"
#include "../src/model/MTerrain.hpp"

#include <cute/cute_test.h>
#include <cute/cute.h>
#include <cute/cute_throws.h>

void borderTestThrows()
{
  MTerrain t;
  int xOverMax = MTerrain::getTaille().getX();
  int yOverMax = MTerrain::getTaille().getY();


  ASSERT_THROWSM("Test (-1,0)", t(-1, 0), MExceptionOutOfTerrain);
  ASSERT_THROWSM("Test (0,-1)", t(0, -1), MExceptionOutOfTerrain);
  ASSERT_THROWSM("Test (-1,-1)", t(-1, -1), MExceptionOutOfTerrain);

  // TODO : test to complete
  ASSERT_THROWSM("Test (max+1,0)", t(xOverMax, 0), MExceptionOutOfTerrain);
  ASSERT_THROWSM("Test (0,max+1)", t(0, yOverMax), MExceptionOutOfTerrain);
  ASSERT_THROWSM("Test (max+1,max)", t(xOverMax, yOverMax - 1), MExceptionOutOfTerrain);
  ASSERT_THROWSM("Test (max,max+1)", t(xOverMax - 1, yOverMax), MExceptionOutOfTerrain);
  ASSERT_THROWSM("Test (max+1,max+1)", t(xOverMax, yOverMax), MExceptionOutOfTerrain);

}

void borderTestNoThrow()
{
  MTerrain t;
  int xOverMax = MTerrain::getTaille().getX();
  int yOverMax = MTerrain::getTaille().getY();

  t(0, 0);
  t(xOverMax - 1, 0);
  t(0, yOverMax - 1);
  t(xOverMax - 1, yOverMax - 1);
}



cute::suite makeTerrainTestSuite()
{
  cute::suite suite;
  suite.push_back(CUTE(borderTestThrows));
  suite.push_back(CUTE(borderTestNoThrow));
  return suite;
}
