#include "Game.h"
#include <string>

int main(int argc, char* argv[])
{
	int len = strlen(argv[0]);
	char c;
	int n = len - 1;
	while (true)
	{
		c = argv[0][n];
		if (c == '\\' || c == '/') break;
		argv[0][n] = NULL;
		n--;
	}
	//Now argv[0] is the startup path

	Game game(argv[0], argv[1]);
	game.start();
	return 0;
}





