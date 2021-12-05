/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include "Solver.h"
#include <memory>

std::unique_ptr<Solver> createSolver(Board& board, char solverType, std::ostream& outputStream);