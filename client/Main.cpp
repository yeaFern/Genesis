#include "Genesis.h"

int main(int argc, char** argv)
{
	Genesis game;
	game.Construct(640, 360, 2, 2);
	game.Start();

	return 0;
}
