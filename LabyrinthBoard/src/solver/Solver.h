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

/// Abstract base class for all Solvers
class Solver {
protected:
  Board& m_board;

public:
  Solver(Board& board)
    : m_board(board)
  {
  }

  virtual ~Solver() = default;

  virtual bool pathExists() = 0;
};