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
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Cell& c);
std::ostream& operator<<(std::ostream& out, Direction direction);
std::ostream& operator<<(std::ostream& out, Board::Coordinates c);
std::ostream& operator<<(std::ostream& out, const Board& board);
std::istream& operator>>(std::istream& in, Board& board);