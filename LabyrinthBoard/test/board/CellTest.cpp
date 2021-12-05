/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "catch2/catch_all.hpp"
#include "board/Cell.h"

void requireValidTypeAndMarking(const Cell& c, Cell::Type expectedType, bool isVisited)
{
   REQUIRE(c.type() == expectedType);
   REQUIRE(c.isVisited() == isVisited);
}

TEST_CASE("Cell constructor correctly stores the passed values", "[Cell]")
{
   SECTION("When marked as visited and corridor")
   {
      Cell::Type expectedType = Cell::Type::Corridor;
      bool isVisited = false;
      Cell c(expectedType, isVisited);
      requireValidTypeAndMarking(c, expectedType, isVisited);
   }

   SECTION("When marked as NOT visited and wall", "[Cell]")
   {
      Cell::Type expectedType = Cell::Type::Wall;
      bool isVisited = true;
      Cell c(expectedType, isVisited);
      requireValidTypeAndMarking(c, expectedType, isVisited);
   }
}

TEST_CASE("After marking a cell as visited, it is reported as such", "[Cell]")
{
   Cell c(Cell::Type::Corridor, false);
   c.markVisited();
   REQUIRE(c.isVisited());
}

TEST_CASE("After marking a cell as NOT visited, it is reported as such", "[Cell]")
{
   Cell c(Cell::Type::Corridor, true);
   c.markNotVisited();
   REQUIRE(! c.isVisited());
}

TEST_CASE("All cell types are passable, except for walls.", "[Cell]")
{
   REQUIRE(Cell(Cell::Type::Corridor).isPassable());
   REQUIRE_FALSE(Cell(Cell::Type::Wall).isPassable());
   REQUIRE(Cell(Cell::Type::Start).isPassable());
   REQUIRE(Cell(Cell::Type::Target).isPassable());
}

TEST_CASE("Only the Target cell type is reported as target", "[Cell]")
{
   REQUIRE_FALSE(Cell(Cell::Type::Corridor).isTarget());
   REQUIRE_FALSE(Cell(Cell::Type::Wall).isTarget());
   REQUIRE_FALSE(Cell(Cell::Type::Start).isTarget());
   REQUIRE(Cell(Cell::Type::Target).isTarget());
}