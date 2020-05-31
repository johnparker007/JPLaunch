#include "headers.h"

void IOLoadBytes(void * pathString, unsigned char pathStringLength, unsigned int startAddress)
{
	memcpy((void *)kRoutineBLoadFilePathAddress, pathString, pathStringLength);

	memset((void *)kRoutineBLoadAddressHighByteAddress, GET_HIGH_BYTE(startAddress), 1);
	memset((void *)kRoutineBLoadAddressLowByteAddress, GET_LOW_BYTE(startAddress), 1);

	// Note: preserve/restore regs code from Nirvana Engine source code
__asm
	; preserve all registers
		push    af
		push    bc
		push    de
		push    hl
;	//	ex      af, af'
		exx
		push    af
		push    bc
		push    de
		push    hl
		push    ix
		push    iy

	; call start address of recompiled routine
		CALL 43000; // kRoutineBLoadBaseAddress

		; restore all registers
			pop     iy
			pop     ix
			pop     hl
			pop     de
			pop     bc
			pop     af
			exx
			;	//	ex      af, af'
		pop     hl
		pop     de
		pop     bc
		pop     af
__endasm;

}

void IOSaveBytes(void * pathString, unsigned char pathStringLength, unsigned int startAddress, unsigned int byteCount)
{
	memcpy((void *)kRoutineBSaveFilePathAddress, pathString, pathStringLength);

	memset((void *)kRoutineBSaveAddressHighByteAddress, GET_HIGH_BYTE(startAddress), 1);
	memset((void *)kRoutineBSaveAddressLowByteAddress, GET_LOW_BYTE(startAddress), 1);

	memset((void *)kRoutineBSaveByteCountHighByteAddress, GET_HIGH_BYTE(byteCount), 1);
	memset((void *)kRoutineBSaveByteCountLowByteAddress, GET_LOW_BYTE(byteCount), 1);

	// Note: preserve/restore regs code from Nirvana Engine source code
	__asm
	; preserve all registers
		push    af
		push    bc
		push    de
		push    hl
		; //		ex      af, af'
		exx
		push    af
		push    bc
		push    de
		push    hl
		push    ix
		push    iy

	; call start address of recompiled routine
		CALL 44000; // kRoutineBSaveBaseAddress

		; restore all registers
			pop     iy
			pop     ix
			pop     hl
			pop     de
			pop     bc
			pop     af
			exx
			; // ex      af, af'
		pop     hl
		pop     de
		pop     bc
		pop     af
		__endasm;
}

void IOChangeDirectory(void * pathString, unsigned char pathStringLength)
{
	memcpy((void *)kRoutineChDirPathAddress, pathString, pathStringLength);

	// Note: preserve/restore regs code from Nirvana Engine source code
__asm
; preserve all registers
push    af
push    bc
push    de
push    hl
; // ex      af, af'
		exx
		push    af
		push    bc
		push    de
		push    hl
		push    ix
		push    iy

	; call start address of recompiled routine
		CALL 43500; // kRoutineChDirBaseAddress

		; restore all registers
			pop     iy
			pop     ix
			pop     hl
			pop     de
			pop     bc
			pop     af
			exx
			; // ex      af, af'
		pop     hl
		pop     de
		pop     bc
		pop     af
__endasm;

}

void IOFakeScreenLoadDelay()
{
	for (unsigned int delayCount = 0; delayCount < 5000; ++delayCount)
	{
	}
}