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

char toChar(Cell::Type t);
Cell::Type toCellType(char c);
const char* toString(Direction& d);