/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include "board/BoardLib.h"

#include <vector>
#include <string>

class BoardBuilder {
  std::vector<std::string> data;

public:
  void addRow(std::string row);
  Board build() const;

  /// Add the next row of the labyrinth
  /// 
  /// This function has the same effect as calling addRow(row).
  BoardBuilder& operator<<(std::string row)
  {
	  addRow(row);
	  return *this;
  }

private:
  size_t findMaxWidth() const;
};