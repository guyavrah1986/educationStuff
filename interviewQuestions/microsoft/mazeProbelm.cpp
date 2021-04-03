#include <stdio.h>

#define ROW 5
#define COL 5

bool findPathInMaze(char* maze, int width, int height, int x, int y)
{
	// stop condition
	if (x == width - 1 && y == height - 1)
	{
		if (maze[(sizeof(char) * width * x) + (sizeof(char) * y)] == '0')
		{
			printf("found the exit!!\n");
			return true;
		}

		printf("got to the end of the maze but has no exit\n");
		return false;
	}

	// out of maze's bounds
	if (x < 0 || x >= ROW || y < 0 || y >= COL)
	{
		printf("reached the edge of the maze array\n");
		return false;
	}

	size_t currSquare = (sizeof(char) * width * x) + (sizeof(char) * y);
	if (maze[currSquare] == 'X')
	{
		printf("already checked maze[%d][%d]:%c\n", x, y, maze[currSquare]);
		return false;
	}

	printf("checking maze[%d][%d]:%c (which is %d bytes from the start of the maze)\n", x, y, maze[(sizeof(char) * width * x) + (sizeof(char) * y)], currSquare + 1);
	if (maze[(sizeof(char) * width * x) + (sizeof(char) * y)] == '1')
	{
		printf("current square is 1, refolding\n");
		return false;
	}

	// mark this square as "been here"
	maze[currSquare] == 'X';

        	// right				         // down		
	return  (findPathInMaze(maze, width, height, x, y + 1) || findPathInMaze(maze, width, height, x + 1, y)); 
}

void printMaze(const char* maze, size_t width, size_t length)
{
	for (size_t row = 0; row < width; ++row)
	{
		size_t rowAddition = row * (ROW * sizeof(char));
		for (size_t col = 0; col < length; ++col)
		{
			printf("|%c|", maze[(rowAddition + col)]);
		}

		printf("\n");
	}
}

int main(int argc, char** argv)
{
	const char* funcName = "main - ";
	printf("%s start\n", funcName);

	char maze1 [] = {'0', '0', '1', '0', '1', 
			'1', '0', '1', '0', '0',
			'1', '0', '1', '1', '0',
			'1', '0', '0', '0', '1',
			'0', '1', '1', '0', '0'};

	char maze2 [] = {'0', '1', 
			 '0', '0'};

	printf("%sthe maze2 is as follows:\n", funcName);
	printMaze(maze2, 2, 2);
	bool pathExists = findPathInMaze(maze2, 2, 2, 0, 0);
	printf("%s end\n", funcName);
	return 0;
}
