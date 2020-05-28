#include "headers.h"
#pragma preproc_asm -


void GameInitialise()
{
	//printUDGAddress(GET_HIGH_BYTE(kCharacterSetAddress), GET_LOW_BYTE(kCharacterSetAddress));

	GameInitialiseScreen();
}

void GameInitialiseScreen()
{
	zx_border(INK_BLACK);
	zx_cls(INK_BLACK);
}

void GameMusicUpdate()
{

	NIRVANAP_halt();

GameUpdate();
}

void GameUpdate()
{

}

void GameDraw()
{
//	SpriteDraw();
}