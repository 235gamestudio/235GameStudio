#include <iostream>
#include "Game.h"
#include "memdbg.h"
#include "vld.h"

/**********************************************************************/
/*						TO DO
/* - create objects lists for each object (f.e. for NPC's or for sth else)
/* - change gui represantation (few structures, not only 1)
/* - repair bug with running animation (f.e. if you keep pressing 2 keys it should stop animate)
/* - rendering present hp/mana percentage while holding mouse cursor on orbs
/* - add changing minimap size (button event)
/* - create fog of war (maybe)
/* - delete all tmp's
/* - repair player movement speed - it should move per second, not per pixel
/**********************************************************************/
/*						WORKING ON
/* - full compatibilty with Tiled Map Editor (right now: sth like 50%~)
/* - collisions using boost library (geometry) - it depends on Tiled Map Editor (right now: 5%)
/**********************************************************************/
s
//#define BOOST_LIB_DIAGNOSTIC

int main(int argc, char *argv[])
{
	Game *game = new Game();
	delete game;

	return 0;
}