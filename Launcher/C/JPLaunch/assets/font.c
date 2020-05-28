#include "headers.h"



void FontInitialise()
{
	//fzx_state_init(&fs, &ff_ao_Dutch, &screen);   // sets xor mode by default
	// ************ TODO this fzx_state_init probably justr wants doing once at start for extra speed:
	fzx_state_init(&fs, font, &screen);   // sets xor mode by default
}


void FontDrawNumber(unsigned int number, unsigned char rightmostCharacterColumn, unsigned char pixelRow, char attributeValues[])
{
	const int kPixelRow = 160;

	NIRVANAP_halt();

	NIRVANAP_printC(kFontZeroOffset + (number % 10),
		attributeValues,
		pixelRow,
		rightmostCharacterColumn);

	if (number >= 10)
	{
		NIRVANAP_printC(kFontZeroOffset + ((number / 10) % 10),
			attributeValues,
			pixelRow,
			rightmostCharacterColumn - 1);
	}

	if (number >= 100)
	{
		NIRVANAP_printC(kFontZeroOffset + ((number / 100) % 10),
			attributeValues,
			pixelRow,
			rightmostCharacterColumn - 2);
	}

}

void FontDrawCharsCenter(char characters[], unsigned char charCount, unsigned char pixelRow, char attributeValues[])
{
	FontDrawChars(characters, charCount, (32 - charCount) >> 1, pixelRow, attributeValues);
}

void FontDrawChars(char characters[], unsigned char charCount, unsigned char characterColumn, unsigned char pixelRow, char attributeValues[])
{
	NIRVANAP_halt(); // todo every n chars?

	for (unsigned char charIndex = 0; charIndex != charCount; charIndex++)
	{
		NIRVANAP_printC(characters[charIndex] - kFontASCIISpace,
			attributeValues,
			pixelRow,
			characterColumn + charIndex);
	}

}

void FontDrawCharStandard(char characters[], unsigned char charCount, unsigned char x, unsigned char y)
{
	unsigned char *p, *dat;

	for (unsigned char charIndex = 0; charIndex != charCount; charIndex++)
	{
		//dat = (unsigned char *)(15360 + characters[charIndex] * 8);                // points into the rom character set
		dat = (unsigned char *)(kFontSpaceCharacterStartAddress + characters[charIndex] * 8);                // points into the custom character set

		p = zx_cxy2saddr(x + charIndex, y);

		//for (i = 0; i < 8; ++i)
		//{
		//	*p = *dat++;
		//	p += 256;
		//}

		// unrolled
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
	}

}

void FontDrawCharsNullTerminated(char characters[], unsigned char x, unsigned char y)
{
	unsigned char *p, *dat;

	unsigned char charIndex = 0;

	while (characters[charIndex] != 0)
	{
		dat = (unsigned char *)(kFontSpaceCharacterStartAddress + characters[charIndex] * 8);                // points into the custom character set

		p = zx_cxy2saddr(x + charIndex, y);

		//for (i = 0; i < 8; ++i)
		//{
		//	*p = *dat++;
		//	p += 256;
		//}

		// unrolled
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;
		*p = *dat++;
		p += 256;

		++charIndex;
	}

}



void FontPaintAttributesRow(unsigned char charCount, unsigned char characterColumn, unsigned char pixelRow, char attributeValues[])
{
	for (unsigned char charIndex = 0; charIndex != charCount; charIndex++)
	{
		NIRVANAP_paintC(attributeValues,
			pixelRow,
			characterColumn + charIndex);
	}
}
void FontPaintAttributesRowFast(unsigned char pixelRow, char attributeValues[])
{
	NIRVANAP_paintC(attributeValues, pixelRow, 0);
	NIRVANAP_paintC(attributeValues, pixelRow, 1);
	NIRVANAP_paintC(attributeValues, pixelRow, 2);
	NIRVANAP_paintC(attributeValues, pixelRow, 3);
	NIRVANAP_paintC(attributeValues, pixelRow, 4);
	NIRVANAP_paintC(attributeValues, pixelRow, 5);
	NIRVANAP_paintC(attributeValues, pixelRow, 6);
	NIRVANAP_paintC(attributeValues, pixelRow, 7);
	NIRVANAP_paintC(attributeValues, pixelRow, 8);
	NIRVANAP_paintC(attributeValues, pixelRow, 9);
	NIRVANAP_paintC(attributeValues, pixelRow, 10);
	NIRVANAP_paintC(attributeValues, pixelRow, 11);
	NIRVANAP_paintC(attributeValues, pixelRow, 12);
	NIRVANAP_paintC(attributeValues, pixelRow, 13);
	NIRVANAP_paintC(attributeValues, pixelRow, 14);
	NIRVANAP_paintC(attributeValues, pixelRow, 15);
	NIRVANAP_paintC(attributeValues, pixelRow, 16);
	NIRVANAP_paintC(attributeValues, pixelRow, 17);
	NIRVANAP_paintC(attributeValues, pixelRow, 18);
	NIRVANAP_paintC(attributeValues, pixelRow, 19);
	NIRVANAP_paintC(attributeValues, pixelRow, 20);
	NIRVANAP_paintC(attributeValues, pixelRow, 21);
	NIRVANAP_paintC(attributeValues, pixelRow, 22);
	NIRVANAP_paintC(attributeValues, pixelRow, 23);
	NIRVANAP_paintC(attributeValues, pixelRow, 24);
	NIRVANAP_paintC(attributeValues, pixelRow, 25);
	NIRVANAP_paintC(attributeValues, pixelRow, 26);
	NIRVANAP_paintC(attributeValues, pixelRow, 27);
	NIRVANAP_paintC(attributeValues, pixelRow, 28);
	NIRVANAP_paintC(attributeValues, pixelRow, 29);
	NIRVANAP_paintC(attributeValues, pixelRow, 30);
	//NIRVANAP_paintC(attributeValues, pixelRow, 31); column for scrollbar
}

void FontPaintAttributesRowFastNoScrollBar(unsigned char pixelRow, char attributeValues[])
{
	NIRVANAP_paintC(attributeValues, pixelRow, 0);
	NIRVANAP_paintC(attributeValues, pixelRow, 1);
	NIRVANAP_paintC(attributeValues, pixelRow, 2);
	NIRVANAP_paintC(attributeValues, pixelRow, 3);
	NIRVANAP_paintC(attributeValues, pixelRow, 4);
	NIRVANAP_paintC(attributeValues, pixelRow, 5);
	NIRVANAP_paintC(attributeValues, pixelRow, 6);
	NIRVANAP_paintC(attributeValues, pixelRow, 7);
	NIRVANAP_paintC(attributeValues, pixelRow, 8);
	NIRVANAP_paintC(attributeValues, pixelRow, 9);
	NIRVANAP_paintC(attributeValues, pixelRow, 10);
	NIRVANAP_paintC(attributeValues, pixelRow, 11);
	NIRVANAP_paintC(attributeValues, pixelRow, 12);
	NIRVANAP_paintC(attributeValues, pixelRow, 13);
	NIRVANAP_paintC(attributeValues, pixelRow, 14);
	NIRVANAP_paintC(attributeValues, pixelRow, 15);
	NIRVANAP_paintC(attributeValues, pixelRow, 16);
	NIRVANAP_paintC(attributeValues, pixelRow, 17);
	NIRVANAP_paintC(attributeValues, pixelRow, 18);
	NIRVANAP_paintC(attributeValues, pixelRow, 19);
	NIRVANAP_paintC(attributeValues, pixelRow, 20);
	NIRVANAP_paintC(attributeValues, pixelRow, 21);
	NIRVANAP_paintC(attributeValues, pixelRow, 22);
	NIRVANAP_paintC(attributeValues, pixelRow, 23);
	NIRVANAP_paintC(attributeValues, pixelRow, 24);
	NIRVANAP_paintC(attributeValues, pixelRow, 25);
	NIRVANAP_paintC(attributeValues, pixelRow, 26);
	NIRVANAP_paintC(attributeValues, pixelRow, 27);
	NIRVANAP_paintC(attributeValues, pixelRow, 28);
	NIRVANAP_paintC(attributeValues, pixelRow, 29);
	NIRVANAP_paintC(attributeValues, pixelRow, 30);
	NIRVANAP_paintC(attributeValues, pixelRow, 31); // column for scrollbar
}

void FontPaintScrollBar(char attributeValues[])
{
	// dont get why this needs to actually include 24, seems like it should be 0-23 inclusive
	for (unsigned char characterRow = 1; characterRow <= 24; ++characterRow)
	{
		NIRVANAP_paintC(attributeValues, characterRow * 8, 31);
	}
}

void FontDrawCharsProportional(char characters[], unsigned char x, unsigned char y)
{


	//fs.fgnd_attr = INK_WHITE | PAPER_BLACK;
	//fs.fgnd_mask = 0;

	fs.y = y;
	fs.x = x;

	//fzx_puts(&fs, txt_intro);
	fzx_puts(&fs, characters);
}
