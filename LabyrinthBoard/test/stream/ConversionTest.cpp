/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "catch2/catch_all.hpp"
#include "stream/Conversion.h"

TEST_CASE("toString returns correct values", "[Conversion]")
{
  std::string expected[] = {
    "Up", "Right", "Down", "Left"
  };

  size_t i = 0;

  for (auto d : AllDirections()) {
    REQUIRE(toString(d) == expected[i++]);
  }
}

TEST_CASE("toString throws when supplied an incorrect direction", "[Conversion]")
{
  Direction d = static_cast<Direction>(static_cast<int>(Direction::Last) + 1);
  REQUIRE_THROWS(toString(d));
}