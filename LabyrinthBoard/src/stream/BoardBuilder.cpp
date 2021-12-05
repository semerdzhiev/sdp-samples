/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "BoardBuilder.h"
#include "Conversion.h"

/// @brief Add the next row of the labyrinth
/// @throws std::invalid_argument if the string contains invalid symbols
void BoardBuilder::addRow(std::string row)
{
  auto pos = row.find_first_not_of(" #^$");

  if (pos != std::string::npos)
    throw std::invalid_argument("Invalid symbol in the row representation");

  data.push_back(row);
}

Board BoardBuilder::build() const
{
	size_t rows = data.size();
	size_t columns = findMaxWidth();

	if (rows == 0 || columns == 0)
		throw std::runtime_error("Board dimensions are not valid");

  Board result(rows, columns);

	for (size_t row = 0; row < data.size(); row++) {
    for (size_t col = 0; col < data[row].size(); ++col)	{
			result.cell(row, col) = toCellType(data[row][col]);

			if (result.cell(row, col).type() == Cell::Type::Start)
				result.setStartCell(row, col);
		}
	}

	return result;
}

size_t BoardBuilder::findMaxWidth() const
{
	size_t result = 0;

	for (auto& s : data)
		result = std::max(result, s.size());

	return result;
}