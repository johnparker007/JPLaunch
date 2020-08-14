#ifndef __FONT_H__
#define __FONT_H__

#define kFontASCIISpace	(32)
#define kFontZeroOffset	(16)


#define kFontSheetBaseAddress (52000)
#define kProportionalFontBaseAddress (51000)
//#define kFontSpaceCharacterStartAddress (kFontSheetBaseAddress + (32 * 8))
#define kFontSpaceCharacterStartAddress (kFontSheetBaseAddress - (32 * 8))

struct fzx_state fs;
struct fzx_font * font = (void *)(kProportionalFontBaseAddress);
struct r_Rect16 screen = { 0, 256, 0, 192 };


void FontInitialise();

void FontDrawNumber(unsigned int number, unsigned char characterColumn, unsigned char pixelRow, char attributeValues[]);


void FontDrawCharsCenter(char characters[], unsigned char charCount, unsigned char pixelRow, char attributeValues[]);

void FontDrawChars(char characters[], unsigned char charCount, unsigned char characterColumn, unsigned char pixelRow, char attributeValues[]);

void FontDrawCharStandard(char characters[], unsigned char charCount, unsigned char x, unsigned char y);
void FontDrawCharsNullTerminated(char characters[], unsigned char x, unsigned char y);

void FontPaintAttributesRow(unsigned char charCount, unsigned char characterColumn, unsigned char pixelRow, char attributeValues[]);
void FontPaintAttributesRowFast(unsigned char pixelRow, char attributeValues[]);
void FontPaintAttributesRowFastNoScrollBar(unsigned char pixelRow, char attributeValues[]);

void FontPaintScrollBar(char attributeValues[]);

void FontDrawCharsProportional(char characters[], unsigned char x, unsigned char y);
unsigned int FontGetProportionalStringWidth(char characters[]);

#endif
