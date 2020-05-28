#ifndef __MACROS_H__
#define __MACROS_H__


#define TRUE (1)
#define FALSE (0)

#define GET_HIGH_BYTE(value) ((value >> 8) & 255)
#define GET_LOW_BYTE(value) (value & 255)

// TODO can I do the multiplies with shifts, would it be faster?
#define ATTRIBUTE_ENCODE(ink, paper, bright, flash) (ink + (8 * paper) + (64 * bright) + (128 * flash))

// z88dk docs (where I got the UDG info from): https://www.z88dk.org/wiki/doku.php?id=platform:zx
#define printInk(k)			printf("\x10%c", (k))
#define printPaper(k)		printf("\x11%c", (k))
#define printFlash(k)		printf("\x12%c", (k))
#define printBright(k)		printf("\x13%c", (k))
#define printAt(row, col)	printf("\x16%c%c", (col), (row))
#define printUDGAddress(addressHighByte, addressLowByte)	printf("\x2%c%c", (addressLowByte), (addressHighByte))



#endif
