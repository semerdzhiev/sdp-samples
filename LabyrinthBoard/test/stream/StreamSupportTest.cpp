/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "catch2/catch_all.hpp"
#include "stream/StreamLib.h"

void requireReversible(Cell::Type t)
{
  REQUIRE(t == toCellType(toChar(t)));
}

// From this test it also follows that each cell type has an unique representation
TEST_CASE("Conversions are reversible")
{
  requireReversible(Cell::Type::Corridor);
  requireReversible(Cell::Type::Wall);
  requireReversible(Cell::Type::Target);
  requireReversible(Cell::Type::Start);
}

TEST_CASE("operator<< correctly outputs boards to a stream")
{
  Board b(4, 5);

  b.cell(0, 0).type() = Cell::Type::Wall;
  b.cell(0, 1).type() = Cell::Type::Wall;
  b.cell(0, 2).type() = Cell::Type::Wall;
  b.cell(0, 3).type() = Cell::Type::Wall;
  b.cell(0, 4).type() = Cell::Type::Wall;

  b.cell(1, 0).type() = Cell::Type::Wall;
  b.cell(1, 1).type() = Cell::Type::Corridor;
  b.cell(1, 2).type() = Cell::Type::Corridor;
  b.cell(1, 3).type() = Cell::Type::Corridor;
  b.cell(1, 4).type() = Cell::Type::Wall;

  b.cell(2, 0).type() = Cell::Type::Wall;
  b.cell(2, 1).type() = Cell::Type::Corridor;
  b.cell(2, 2).type() = Cell::Type::Corridor;
  b.cell(2, 3).type() = Cell::Type::Target;
  b.cell(2, 4).type() = Cell::Type::Wall;

  b.cell(3, 0).type() = Cell::Type::Wall;
  b.cell(3, 1).type() = Cell::Type::Wall;
  b.cell(3, 2).type() = Cell::Type::Wall;
  b.cell(3, 3).type() = Cell::Type::Wall;
  b.cell(3, 4).type() = Cell::Type::Wall;

  b.setStartCell(1, 1);

  std::stringstream printed;
  printed << b;
  printed.seekg(0);

  std::string expected("#####\n#^  #\n#  $#\n#####\n");

  REQUIRE(printed.str() == expected);
}

TEST_CASE("operator>> correctly inputs board contents from a stream")
{

}