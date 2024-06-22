#include <map>

// =============================================================================
// Utilities functions:
// =============================================================================

#define ROW_LEN 9
#define COL_LEN 9

int origSodukoBoard [ROW_LEN * COL_LEN];
std::map<unsigned short, unsigned short> bankerIndexToValMap;

void initBankerMap(std::map<unsigned short, unsigned short>& indexToValMap)
{
	indexToValMap.emplace(3, 2);
	indexToValMap.emplace(4, 6);
	indexToValMap.emplace(6, 7);
	indexToValMap.emplace(8, 1);

	indexToValMap.emplace(9, 6);
	indexToValMap.emplace(10, 8);
	indexToValMap.emplace(13, 7);
	indexToValMap.emplace(16, 9);

	indexToValMap.emplace(18, 1);
	indexToValMap.emplace(19, 9);
	indexToValMap.emplace(23, 4);
	indexToValMap.emplace(23, 5);

	indexToValMap.emplace(27, 8);
	indexToValMap.emplace(28, 2);
	indexToValMap.emplace(30, 1);
	indexToValMap.emplace(34, 4);

	indexToValMap.emplace(38, 4);
	indexToValMap.emplace(35, 6);
	indexToValMap.emplace(37, 2);
	indexToValMap.emplace(38, 9);

	indexToValMap.emplace(46, 5);
	indexToValMap.emplace(50, 3);
	indexToValMap.emplace(52, 2);
	indexToValMap.emplace(53, 8);

	indexToValMap.emplace(56, 9);
	indexToValMap.emplace(57, 3);
	indexToValMap.emplace(61, 7);
	indexToValMap.emplace(62, 4);

	indexToValMap.emplace(64, 4);
	indexToValMap.emplace(67, 5);
	indexToValMap.emplace(70, 3);
	indexToValMap.emplace(71, 6);

	indexToValMap.emplace(72, 7);
	indexToValMap.emplace(74, 3);
	indexToValMap.emplace(76, 1);
	indexToValMap.emplace(77, 8);
}

void initBoard(int board [])
{
	for (unsigned char row = 0; row < ROW_LEN; ++row)
	{
		for (unsigned char col = 0; col < COL_LEN; ++col)
		{
			unsigned short index = (row * ROW_LEN) + col;
			unsigned short valToSet = 0;
			try
			{
				valToSet = bankerIndexToValMap.at(index);
			}
			catch(const std::exception& e)
			{
				//valToSet = 0;
			}
			std::cout << "setting board[" << index << "]" << valToSet << std::endl;
			board[index] = valToSet;
		}
	}
}

void displayBoard(const int board [])
{
	std::cout << std::endl;
	for (unsigned char row = 0; row < ROW_LEN; ++row)
	{
		std::cout << "|";
		for (unsigned char col = 0; col < COL_LEN; ++col)
		{
			std::cout << board[(row * ROW_LEN) + col ] << "\t|";
		}

		std::cout << std::endl;
	}
}

bool isValidRow(const int board [], unsigned char startIndex)
{
	unsigned char isPresentArr [ROW_LEN] = {0};
	for (unsigned char i = startIndex; i < ROW_LEN; ++i)
	{
		isPresentArr[board[i] - 1] += 1;
	}

	for (unsigned char i = 0; i < ROW_LEN; ++i)
	{
		if (1 != isPresentArr[i])
		{
			return false;
		}
	}

	return true;
}

bool isValidCol(const int board [], unsigned char colNum)
{
	unsigned char isPresentArr [COL_LEN] = {0};
	unsigned char colOffset = colNum * ROW_LEN;
	for (unsigned char i = 0; i < COL_LEN; ++i)
	{
		isPresentArr[board[colOffset + (i * ROW_LEN)] - 1] += 1;
	}

	for (unsigned char i = 0; i < COL_LEN; ++i)
	{
		if (1 != isPresentArr[i])
		{
			return false;
		}
	}

	return true;
}

bool isValidSubTable(const int board [], unsigned char subTableStartIndex)
{
	unsigned char isPresentArr [COL_LEN] = {0};
	unsigned char subTableLen = 3;
	std::cout << "start index is:" << subTableStartIndex << std::endl;
	for (unsigned char row = 0; row < subTableLen; ++row)
	{
		for (unsigned char col = 0; col < subTableLen; ++col)
		{
			isPresentArr[board[subTableStartIndex + (row * ROW_LEN) + col] - 1] += 1;
		}
	}

	for (unsigned char i = 0; i < COL_LEN; ++i)
	{
		if (1 != isPresentArr[i])
		{
			std::cout << "the number:" << i + 1 << " is NOT present (or appears more than once) in the sub table, return false" << std::endl;
			return false;
		}
	}

	return true;
}

bool isBanker(unsigned char index)
{
	unsigned short valToSet;
	try
	{
		valToSet = bankerIndexToValMap.at(index);
		std::cout << "index[" << index << "]:" << valToSet << std::endl;
		return true;
	}
	catch(const std::exception& e)
	{
		std::cout << "index:" << index << " is NOT a banker value" << std::endl;
		return false;
	}
}

unsigned short getSubTableStartIndex(unsigned short row, unsigned short col)
{
	unsigned short rowCont;
	unsigned short colCont;
	if (row <= 2)
	{
		rowCont = 0;
	}
	else if (row >= 3 && row <= 5)
	{
		rowCont = 3;
	}
	else
	{
		rowCont = 6;
	}

	if (col <= 2)
	{
		colCont = 0;
	}
	else if (col >= 3 && col <= 5)
	{
		colCont = 3;
	}
	else
	{
		colCont = 6;
	}

	unsigned short cont = (rowCont * ROW_LEN) + colCont;
	std::cout << "row,col:" << row << "," << col << " - contributed:" << cont << std::endl;
	return cont;
}

bool sodukoSolver(int board [], unsigned short index, const std::map<unsigned short, unsigned short>& bankerMap)
{
	std::cout << "checking index:" << index << std::endl;
	// If we reached the end of the board, return true
	if ((ROW_LEN * COL_LEN) == index)
	{
		std::cout << "reached end of board (index 81)" << std::endl;
		return true;
	}

	// If this index is a banker index, carry on to the next index
	if (bankerMap.contains(index))
	{
		std::cout << "index:" << index << " is in the bankers map" << std::endl;
		return sodukoSolver(board, ++index, bankerMap);
	}
	
	unsigned short indexRow = index / ROW_LEN;
	unsigned short indexCol = index % COL_LEN;
	std::cout << "index [row,col]:[" << indexRow << "," << indexCol << "]" << std::endl; 
	for (unsigned char val = 1; val <= COL_LEN; ++val)
	{
		board[index] = val;

		// Validate row
		if (false == isValidRow(board, indexRow * ROW_LEN))
		{
			board[index] = 0;
			continue; 	
		}

		// Validate col
		if (false == isValidCol(board, indexCol))
		{
			board[index] = 0;
			continue; 	
		}

		// Validate sub table
		if (false == isValidSubTable(board, getSubTableStartIndex(indexRow, indexCol)))
		{
			board[index] = 0;
			continue; 	
		}

		std::cout << "setting index:" << index << " with:" << val << " --> is valid, carry on" << std::endl;
		return sodukoSolver(board, ++index, bankerMap);
	}

	return false;
}

int main(int argc, char** argv)
{
	initBankerMap(bankerIndexToValMap);

	// Generate the original soduko board
	initBoard(origSodukoBoard);
	std::cout << "originally the board is:" << std::endl;
	displayBoard(origSodukoBoard);

	if (true == sodukoSolver(origSodukoBoard, 0, bankerIndexToValMap))
	{
		std::cout << "was able to solve soduko, the board is now:" << std::endl;
		displayBoard(origSodukoBoard);
	}
	else
	{
		std::cout << "was NOT able to solve the board soduko!" << std::endl;
	}

  return 0;
}
