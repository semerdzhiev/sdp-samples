/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "catch2/catch_all.hpp"
#include "solver/SolverLib.h"

#include <fstream>

TEST_CASE("SolverFactory throws on incorrect solver name", "[SolverFactory]")
{
  Board b(2,2);
  std::ofstream nullStream;
  nullStream.setstate(std::ios_base::badbit);

  REQUIRE_THROWS_AS(createSolver(b, 'Z', nullStream), std::domain_error);
}

TEST_CASE("SolverFactory creates correct objects", "[SolverFactory]")
{
  Board b(2, 2);
  std::ofstream nullStream;
  nullStream.setstate(std::ios_base::badbit);

  REQUIRE(typeid(*createSolver(b, 'b', nullStream)) == typeid(BfsSolver));
  REQUIRE(typeid(*createSolver(b, 'B', nullStream)) == typeid(BfsSolver));
  REQUIRE(typeid(*createSolver(b, 'd', nullStream)) == typeid(DfsSolver));
  REQUIRE(typeid(*createSolver(b, 'D', nullStream)) == typeid(DfsSolver));
}