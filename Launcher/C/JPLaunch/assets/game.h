#ifndef __GAME_H__
#define __GAME_H__

// For the custom character set:
#define kNirvanaPlusStartAddress (56323)
#define kCharacterSetLength (2048)
#define kCharacterSetAddress (kNirvanaPlusStartAddress - kCharacterSetLength) // 54275

// TODO organise these further - standard defines, Nirvana defines etc...

#define kMemoryScreenPixelDataStart (16384)
#define kMemoryScreenPixelDataLength (6144)
#define kMemoryScreenAttributeDataStart (kMemoryScreenPixelDataStart + kMemoryScreenPixelDataLength)

// JP: would've thought this was 192, perhap because of the 8 pixel y offset plus another 8 to make it to top of next tile would cause it to go over?
//#define kNirvanaCompiledCharacterHeight (19)
#define kNirvanaCompiledCharacterHeight (20)


#define kScreenAttributeHeight (8)
#define kScreenTileHeight (kScreenAttributeHeight * 2)

#define kPixelRowStart (kScreenTileHeight)
#define kPixelRowHeight (2)
#define kPixelRowCount (kNirvanaCompiledCharacterHeight * kScreenAttributeHeight)

#define kCharacterColumnStart (0)
#define kCharacterColumnTileWidth (2)
#define kCharacterColumnWidth (32)
#define kCharacterColumnHalfWidth (kCharacterColumnWidth / 2)

#define kScrollSpeedCurrent (1) // this will end up a variable, so can change speed during level
#define kScrollSpeedMaximum (2) // any more than 2 and coins will go through the 2 char wide player


#define kCharacterIndexCoin0 ((char)0)
#define kCharacterIndexCoin1 ((char)1)
#define kCharacterIndexCoin2 ((char)2)
#define kCharacterIndexCoin3 ((char)3)
#define kCharacterIndexCoin4 ((char)4) //  duplicating a character, but less code to do the anim loop
#define kCharacterIndexCoin5 ((char)5) //  duplicating a character, but less code to do the anim loop



void GameInitialise();
void GameInitialiseScreen();
void GameMusicUpdate();
void GameUpdate();
void GameDraw();


#endif
