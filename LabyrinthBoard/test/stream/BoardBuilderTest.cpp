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

TEST_CASE("BoardBuilder throws when passed a line with invalid characters", "[BoardBuilder]")
{
  BoardBuilder builder;
  REQUIRE_THROWS(builder.addRow("##^$%"));
}

TEST_CASE("BoardBuilder throws when building an empty board", "[BoardBuilder]")
{
  BoardBuilder builder;
  REQUIRE_THROWS(builder.build());
}

TEST_CASE("BoardBuilder throws when it was passed only empty strings", "[BoardBuilder]")
{
  BoardBuilder builder;
  builder.addRow("");
  builder.addRow("");
  REQUIRE_THROWS(builder.build());
}

TEST_CASE("BoardBuilder creates correct boards", "[BoardBuilder]")
{
  std::string arr[] = {
    "#######",
    "# ^# $#",
    "#     #",
    "#######"
  };

  BoardBuilder builder;
  std::stringstream expected;
  for (auto& str : arr) {
    builder.addRow(str);
    expected << str << "\n";
  }

  std::stringstream output;
  output << builder.build(); // relies on operator<< to work correctly!

  REQUIRE(output.str() == expected.str());
}