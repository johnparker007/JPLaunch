#include "headers.h"

void ScreensaverInitialise()
{
	NIRVANAP_stop();

	//memset((void*)(16384 + 6144), PAPER_BLACK | INK_BLACK, 768); // quick hide display via attributes
	//memset((void*)(16384), 0, 6144); // clear pixel data
	memset((void*)(16384 + 6144), PAPER_BLACK | INK_WHITE | BRIGHT, 768); // set up attributes for screensaver

	// move to frames directory for maximum loading speed
	const char* kScreensaverPath = "/jplaunch/graphics/scrnsave";
	IOChangeDirectory(kScreensaverPath, kFrontendBasicDataPageLength);

	_screensaverCurrentFrame = 0;
	_screensaverPositiveSpeed = TRUE;
}

void ScreensaverUpdate()
{
	ScreensaverLoadCurrentFrameScreen();

	_screensaverCurrentFrame += _screensaverPositiveSpeed ? 1 : -1;
	if (_screensaverCurrentFrame == kScreensaverFrameCount)
	{
		_screensaverPositiveSpeed = FALSE;
		_screensaverCurrentFrame -= 2; // so we don't show the final frame twice
	}
	else if (_screensaverCurrentFrame < 0)
	{
		_screensaverPositiveSpeed = TRUE;
		_screensaverCurrentFrame = 1; // so we don't show the zeroth frame twice
	}
}

void ScreensaverLoadCurrentFrameScreen()
{
	unsigned char basicData[kFrontendBasicDataPageLength];
	memset(&basicData, 0, kFrontendBasicDataPageLength);

	uchar paddedPageNumberString[kScreensaverFrameIndexPaddedMaximumLength];
	FrontendGetChars(_screensaverCurrentFrame, paddedPageNumberString, TRUE);

	unsigned char basicDataIndex = 0;
	for (unsigned char paddedPageNumberStringIndex = 0; paddedPageNumberStringIndex < kScreensaverFrameIndexPaddedMaximumLength; ++paddedPageNumberStringIndex)
	{
		basicData[basicDataIndex] = paddedPageNumberString[paddedPageNumberStringIndex];
		++basicDataIndex;
		basicData[basicDataIndex] = '/';
		++basicDataIndex;
	}

	basicData[basicDataIndex] = '0';

#ifdef kDebugFakeLoadDelayForEmulator
	IOFakeScreenLoadDelay();
#endif

	IOLoadBytes(&basicData, kFrontendBasicDataPageLength, 16384);

	//_nirvanaRestartNextUpdate = TRUE;
}
