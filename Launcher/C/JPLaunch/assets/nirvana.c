#include "headers.h"

const unsigned char kNirvanaByte0Value23Rows = 3;
const unsigned char kNirvanaByte1Value23Rows = 251;

const unsigned char kNirvanaByte0Value7Rows = 131;
const unsigned char kNirvanaByte1Value7Rows = 230;

const char * kNirvanaEnginePath23Rows = "../code/nirvana";
const char * kNirvanaEnginePath7Rows = "../code/nirvana7";

const unsigned int kStartAddressOfThisCFileCompiled = 24576; // where we loaded this z80 code block into ram

void NirvanaLoadEngine(_Bool rows23)
{
	if (_nirvanaRowHeightPatchAddress == 0)
	{
		NirvanaRowHeightPatchAddressInitialise();
	}

	intrinsic_di(); // otherwise Nirvana gets called during the patching/loading and crashes (on real hardware)
 
	if (rows23)
	{
		memset((void *)_nirvanaRowHeightPatchAddress, kNirvanaByte0Value23Rows, 1);
		memset((void *)(_nirvanaRowHeightPatchAddress + 1), kNirvanaByte1Value23Rows, 1);

		IOLoadBytes(kNirvanaEnginePath23Rows, kFrontendBasicDataPageLength, kNirvanaPlusStartAddress);
	}
	else // 7 row engine
	{
		memset((void *)_nirvanaRowHeightPatchAddress, kNirvanaByte0Value7Rows, 1);
		memset((void *)(_nirvanaRowHeightPatchAddress + 1), kNirvanaByte1Value7Rows, 1);

		IOLoadBytes(kNirvanaEnginePath7Rows, kFrontendBasicDataPageLength, kNirvanaPlusStartAddress);
	}

	intrinsic_ei(); // restore interrupts now Nirvana patched and (re)loaded, it can safely run again
}

void NirvanaRowHeightPatchAddressInitialise()
{
	_nirvanaRowHeightPatchAddress = kStartAddressOfThisCFileCompiled;

	for (;;)
	{
		if(*(unsigned char *)_nirvanaRowHeightPatchAddress == kNirvanaByte0Value23Rows
			&& *(unsigned char *)(_nirvanaRowHeightPatchAddress + 1) == kNirvanaByte1Value23Rows)
		{
			break;
		}

		++_nirvanaRowHeightPatchAddress;
	} 
}

void NirvanaRestartNextUpdate()
{
	if (InputHeldFrameCountIsRepeating()
		&&
		(_frontendLauncherState == kLauncherStateGameList || _frontendLauncherState == kLauncherStateSearchList)
		&&
		(	(_frontendListModeFull && (_inputStateData.LeftHeld || _inputStateData.RightHeld))
			||
			(!_frontendListModeFull && (_inputStateData.LeftHeld || _inputStateData.RightHeld || _inputStateData.UpHeld || _inputStateData.DownHeld))
		)
	)
	{
		return;
	}

	NirvanaStartAndCancelRestartNextUpdate();
}

void NirvanaStartAndCancelRestartNextUpdate()
{
	if (_nirvanaRestartNextUpdate)
	{
		NIRVANAP_start();
		_nirvanaRestartNextUpdate = FALSE;
	}
}
