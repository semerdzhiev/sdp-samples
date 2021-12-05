/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "catch2/catch_all.hpp"
#include "board/Direction.h"

TEST_CASE("Incrementing past the last direction throws an exception", "[Direction]")
{
   Direction d = Direction::Last;

   REQUIRE_THROWS_AS(++d, std::invalid_argument);
}

TEST_CASE("Directions enumerate in the correct order", "[Direction]")
{
  const size_t size = 4;
  Direction expected[size] = {
    Direction::Up,
    Direction::Right,
    Direction::Down,
    Direction::Left
  };

  size_t i = 0;

  for (auto d : AllDirections()) {
    REQUIRE(i < size);
    REQUIRE(d == expected[i++]);
  }

  REQUIRE(i == size);
}
