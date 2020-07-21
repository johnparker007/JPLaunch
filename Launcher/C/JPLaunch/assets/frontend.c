#include "headers.h"

#define kReturnCodeLoadTapDisable128kPaging (1000)
#define kReturnCodeLoadTap (1010)
#define kReturnCodeLoadSnaZ80Disable128kPaging (2000)
#define kReturnCodeLoadSnaZ80 (2010)




#define kRowCountFull (23)
#define kRowCountMini (7)

#define kSearchStringCharacterColumn (9)
#define kSearchStringCharacterRow (13)

// values from this Spectrum ASCII control code table here: https://en.wikipedia.org/wiki/ZX_Spectrum_character_set
#define kInputASCIICursorUp (0x0B)
#define kInputASCIICursorDown (0x0A)
#define kInputASCIICursorLeft (0x08)
#define kInputASCIICursorRight (0x09)
#define kInputASCIIDelete (0x0C)
#define kInputASCIIEnter (0x0D)




#define kInputScancodeUp		(IN_KEY_SCANCODE_7)
#define kInputScancodeDown		(IN_KEY_SCANCODE_6)
#define kInputScancodeLeft		(IN_KEY_SCANCODE_5)
#define kInputScancodeRight		(IN_KEY_SCANCODE_8)
#define kInputScancodeSelect	(IN_KEY_SCANCODE_ENTER)
#define kInputScancodeShowLoadingScreen	(IN_KEY_SCANCODE_SPACE)


#define kMetadataAddressTopRightRow0 (16384 + 31)
#define kMetadataAddressTopRightRow1 (kMetadataAddressTopRightRow0 + (256 * 1))
#define kMetadataAddressTopRightRow2 (kMetadataAddressTopRightRow0 + (256 * 2))
#define kMetadataAddressTopRightRow3 (kMetadataAddressTopRightRow0 + (256 * 3))

#define kMetadataFileIndexStartColumn (19)
#define kRowsPer16BitNumber (2)

#define kMetadataFileFormatStartColumn (25)
#define kBitPairsPerPixelRow (4)

// TODO calculate this dynamically!
#define kMetadataIndicesStartColumn = 16;
#define kMetadataIndicesAddressColumn0Row0 = 16384 + kMetadataIndicesStartColumn;
#define kMetadataIndicesAddressColumn0Row1 = 16384 + kMetadataIndicesStartColumn;
#define kMetadataIndicesAddressColumn0Row2 = 16384 + kMetadataIndicesStartColumn;
#define kMetadataIndicesAddressColumn0Row1 = 16384 + kMetadataIndicesStartColumn;
#define kMetadataIndicesAddressColumn0Row3 = 16384 + kMetadataIndicesStartColumn;
#define kMetadataIndicesAddressColumn0Row1 = 16384 + kMetadataIndicesStartColumn;
#define kMetadataIndicesAddressColumn0Row1 = 16384 + kMetadataIndicesStartColumn;
#define kMetadataIndicesAddressColumn0Row1 = 16384 + kMetadataIndicesStartColumn;

#define kFileFormatTypeTap (0)
#define kFileFormatTypeSna (1)
#define kFileFormatTypeZ80 (2)

#define kSearchWindowPixelDataReadAddress (48952)
#define kSearchWindowPixelDataWriteAddress (16384 + 2048)

#define kExitMenuOptionNMI		(0)
#define kExitMenuOptionReset	(1)
#define kExitMenuOptionBack		(2)
#define kExitMenuOptionCount	(3)

#define kConfigurationMenuOptionDefaultView			(0)
#define kConfigurationMenuOptionNMISYSStartupPath	(1)
#define kConfigurationMenuOptionInputAcceleration	(2)
#define kConfigurationMenuOptionKeyboardType		(3)
#define kConfigurationMenuOptionJoystickType		(4)
#define kConfigurationMenuOptionScreensaverType		(5)
#define kConfigurationMenuOptionScreensaverDelayType (6)

#define kConfigurationMenuOptionBack				(7)
#define kConfigurationMenuOptionCount				(8)


		
void * _basicTapFilenameAddress = (void *)(0x5cf7); // in use
void * _basicSnaZ80IndexAddress = (void *)(0x5d4e); // in use 

void * _searchWindowPixelDataReadAddress = (void *)(48952);
void * _searchWindowPixelDataWriteAddress = (void *)(16384 + 2048);


unsigned char *_listPageCountAddressHighByte = (unsigned char *)(kMetadataAddressTopRightRow0);
unsigned char *_listPageCountAddressLowByte = (unsigned char *)(kMetadataAddressTopRightRow1);
unsigned char *_listPageRowCountAddress = (unsigned char *)(kMetadataAddressTopRightRow2);


unsigned char *_listPageFileIndexAddressHighByte;
unsigned char *_listPageFileIndexAddressLowByte;

unsigned char *_listPageFileFormatAddress;

void FrontendInitialise()
{
	_frontendCurrentRow = 0;

	_frontendListModeFull = _configurationData.DefaultViewMode == DefaultViewModeFullScreenList;
	_frontendRowsPerPage = _configurationData.DefaultViewMode == DefaultViewModeFullScreenList ? kRowCountFull : kRowCountMini;

	FontInitialise();

	FrontendInitialiseAttributeValues();
	FrontendInitialiseScreen();

	FrontendLoadGameListScreen();
	if (!_frontendListModeFull)
	{
		FrontendShowLoadingScreenFile(TRUE);
	}

	_frontendLauncherState = kLauncherStateGameList;

	NIRVANAP_start();
}

void FrontendInitialiseAttributeValues()
{
	_frontendMenuAttributeValues[0] = ATTRIBUTE_ENCODE(6, 0, 0, 0); 
	_frontendMenuAttributeValues[1] = ATTRIBUTE_ENCODE(7, 0, 1, 0); 
	_frontendMenuAttributeValues[2] = ATTRIBUTE_ENCODE(6, 0, 0, 0); 
	_frontendMenuAttributeValues[3] = ATTRIBUTE_ENCODE(2, 0, 1, 0); 

	_frontendMenuSelectedAttributeValues[0] = ATTRIBUTE_ENCODE(0, 6, 0, 0);
	_frontendMenuSelectedAttributeValues[1] = ATTRIBUTE_ENCODE(0, 7, 1, 0);
	_frontendMenuSelectedAttributeValues[2] = ATTRIBUTE_ENCODE(0, 6, 0, 0);
	_frontendMenuSelectedAttributeValues[3] = ATTRIBUTE_ENCODE(0, 2, 1, 0);

	_frontendScrollBarAttributeValues[0] = ATTRIBUTE_ENCODE(2, 0, 1, 0);
	_frontendScrollBarAttributeValues[1] = ATTRIBUTE_ENCODE(2, 0, 0, 0);
	_frontendScrollBarAttributeValues[2] = ATTRIBUTE_ENCODE(2, 0, 1, 0);
	_frontendScrollBarAttributeValues[3] = ATTRIBUTE_ENCODE(2, 0, 0, 0);

	_frontendSearchRow0Attributes[0] = ATTRIBUTE_ENCODE(7, 0, 1, 0);
	_frontendSearchRow0Attributes[1] = ATTRIBUTE_ENCODE(7, 0, 1, 0);
	_frontendSearchRow0Attributes[2] = ATTRIBUTE_ENCODE(0, 0, 1, 0);
	_frontendSearchRow0Attributes[3] = ATTRIBUTE_ENCODE(0, 0, 1, 0);

	_frontendSearchRow1Attributes[0] = ATTRIBUTE_ENCODE(0, 0, 1, 0);
	_frontendSearchRow1Attributes[1] = ATTRIBUTE_ENCODE(1, 0, 1, 0);
	_frontendSearchRow1Attributes[2] = ATTRIBUTE_ENCODE(5, 0, 0, 0);
	_frontendSearchRow1Attributes[3] = ATTRIBUTE_ENCODE(5, 0, 1, 0);

	_frontendSearchRow2Attributes[0] = ATTRIBUTE_ENCODE(7, 0, 1, 0);
	_frontendSearchRow2Attributes[1] = ATTRIBUTE_ENCODE(7, 0, 1, 0);
	_frontendSearchRow2Attributes[2] = ATTRIBUTE_ENCODE(5, 0, 1, 0);
	_frontendSearchRow2Attributes[3] = ATTRIBUTE_ENCODE(5, 0, 0, 0);

	_frontendSearchRow3Attributes[0] = ATTRIBUTE_ENCODE(1, 0, 1, 0);
	_frontendSearchRow3Attributes[1] = ATTRIBUTE_ENCODE(0, 0, 1, 0);
	_frontendSearchRow3Attributes[2] = ATTRIBUTE_ENCODE(0, 0, 1, 0);
	_frontendSearchRow3Attributes[3] = ATTRIBUTE_ENCODE(0, 0, 1, 0);

	_frontendSearchRow4Attributes[0] = ATTRIBUTE_ENCODE(7, 0, 1, 0);
	_frontendSearchRow4Attributes[1] = ATTRIBUTE_ENCODE(7, 0, 1, 0);
	_frontendSearchRow4Attributes[2] = ATTRIBUTE_ENCODE(7, 0, 1, 0);
	_frontendSearchRow4Attributes[3] = ATTRIBUTE_ENCODE(7, 0, 1, 0);

	_frontendSearchRow7Attributes[0] = ATTRIBUTE_ENCODE(0, 0, 1, 0);
	_frontendSearchRow7Attributes[1] = ATTRIBUTE_ENCODE(0, 0, 1, 0);
	_frontendSearchRow7Attributes[2] = ATTRIBUTE_ENCODE(7, 0, 1, 0);
	_frontendSearchRow7Attributes[3] = ATTRIBUTE_ENCODE(7, 0, 1, 0);

	_frontendMenuSelectedAttributeStartIndex = 0;
}

void FrontendInitialiseScreen()
{
	// clear top third screen to cover up leftovers from loading in top bar 
	memset((void *)16384, 0, 2048);

	// Nirvana attributes (slow, draw first while real screen attributes are black
	FrontendPaintNirvanaRowsAttributes(TRUE, _frontendRowsPerPage);
	FrontendDrawCurrentRowSelected();

	// native Spectrum screen attributes (fast, draw last)
	FrontendPaintTopRowAttributes();
}

void FrontendPaintNirvanaRowsAttributes(_Bool includeScrollbar, unsigned char rowCount)
{
	if (includeScrollbar)
	{
		FontPaintScrollBar(_frontendScrollBarAttributeValues);
	}

	for (uchar row = 0; row != rowCount; ++row)
	{
		if (includeScrollbar)
		{
			FontPaintAttributesRowFast((row + 2) * 8, _frontendMenuAttributeValues);
		}
		else
		{
			FontPaintAttributesRowFastNoScrollBar((row + 2) * 8, _frontendMenuAttributeValues);
		}
	}
}

void FrontendPaintTopRowAttributes()
{
	memset(zx_cxy2aaddr(0, 0), (PAPER_BLUE | INK_WHITE | BRIGHT), kMetadataFileIndexStartColumn);
	memset(zx_cxy2aaddr(kMetadataFileIndexStartColumn, 0), (PAPER_BLUE | INK_BLUE | BRIGHT), 32 - kMetadataFileIndexStartColumn);

	memset(zx_cxy2aaddr(26, 0), (PAPER_BLUE | INK_RED | BRIGHT), 1);
	memset(zx_cxy2aaddr(27, 0), (PAPER_RED | INK_YELLOW | BRIGHT), 1);
	memset(zx_cxy2aaddr(28, 0), (PAPER_YELLOW | INK_GREEN | BRIGHT), 1);
	memset(zx_cxy2aaddr(29, 0), (PAPER_GREEN | INK_CYAN | BRIGHT), 1);
	memset(zx_cxy2aaddr(30, 0), (PAPER_CYAN | INK_BLUE | BRIGHT), 1);
}



void FrontendUpdate()
{
	if (InputBlockedAwaitingKeyUp())
	{
		return;
	}

	if (_frontendLauncherState != kLauncherStateScreensaver)
	{
		if (_inputFramesSinceInputCount > kScreensaverIdleFramesBeforeShow)
		{
			_frontendLauncherState = kLauncherStateScreensaver;
			ScreensaverInitialise();
			_inputFramesSinceInputCount = 0;
			return;
		}
		else if(_inputFramesSinceInputCount > 1)
		{
			// we're idling in a menu, limit to 50FPS for accurate timing
			intrinsic_halt(); 
		}
	}

	InputGetInput();

	if (_nirvanaRestartNextUpdate)
	{
		NirvanaRestartNextUpdate();
	}

	switch (_frontendLauncherState)
	{
	case kLauncherStateGameList:
		_frontendGameListCurrentRow = _frontendCurrentRow;
		_frontendGameListCurrentPage = _frontendCurrentPage;

		FrontendUpdateProcessInputList();
		break;
	case kLauncherStateSearchInput:
		FrontendUpdateProcessInputSearch();
		break;
	case kLauncherStateSearchList:
		_frontendSearchListCurrentRow = _frontendCurrentRow;
		_frontendSearchListCurrentPage = _frontendCurrentPage;

		FrontendUpdateProcessInputList();
		break;
	case kLauncherStateShowLoadingScreenFull:
		FrontendUpdateProcessInputLoadingScreenFull();
	case kLauncherStateExitMenu:
		FrontendUpdateProcessInputExitMenu();
		break;
	case kLauncherStateConfigurationMenu:
		// draw needs to be done before update to avoid leaving unwanted draws on exiting config menu
		FrontendConfigurationMenuDrawArrows(FALSE); 
		FrontendUpdateProcessInputConfigurationMenu();
		break;
	case kLauncherStateScreensaver:
		ScreensaverUpdate();
		break;
	}

	++_frontendFrameCount;
}

void FrontendUpdateProcessInputList()
{
	if (InputHeldFrameCountIsOneOrRepeating())
	{
		if(_inputStateData.UpHeld)
		{
			FrontendProcessInputListUp();
			return;
		}
		else if (_inputStateData.DownHeld)
		{
			FrontendProcessInputListDown();
			return;
		}

		if (_inputStateData.LeftHeld)
		{
			FrontendProcessInputListLeft();
			return;
		}
		else if (_inputStateData.RightHeld)
		{
			FrontendProcessInputListRight();
			return;
		}
	}

	if (_inputHeldFrameCount != 1)
	{
		return;
	}

	if (_inputStateData.ViewModeToggleHeld)
	{
		FrontendProcessInputListToggleMode();
		_inputWaitForNoInput = TRUE;
	}
	else if (_inputStateData.BackHeld)
	{
		FrontendProcessInputListBack();
	}
	else if (_inputStateData.ConfigurationHeld)
	{
		FrontendProcessInputListConfiguration();
	}
	else if (_inputStateData.SelectHeld)
	{
		FrontendProcessInputGamelistSelect(in_key_pressed(IN_KEY_SCANCODE_CAPS));
	}
	else if (_inputStateData.ShowFullScreenImageHeld)
	{
		FrontendProcessInputGamelistShowLoadingScreen();
		_inputWaitForNoInput = TRUE;
	}
	else if (
		// TODO this could be written better/with less code:
		(_configurationData.KeyboardType == KeyboardTypeNon48KWithCursor
		&& (_inputASCIIInput >= '0' && _inputASCIIInput <= '9')
			|| (_inputASCIIInput >= 'A' && _inputASCIIInput <= 'Z'))
		||
		(_configurationData.KeyboardType == KeyboardType48KWithoutCursor
		&& ((_inputASCIIInput >= '0' && _inputASCIIInput <= '4') || _inputASCIIInput == '9')
			|| (_inputASCIIInput >= 'A' && _inputASCIIInput <= 'Z'))
	)
	{
		FrontendSearchInputInitialise();
	}
}

void FrontendProcessInputListUp()
{
	if (_frontendCurrentRow > 0)
	{
		FrontendDrawCurrentRowUnselected();
		--_frontendCurrentRow;
		FrontendDrawCurrentRowSelected();

		if (!_frontendListModeFull)
		{
			FrontendShowLoadingScreenFile(TRUE);
		}
	}
	else if (_frontendCurrentPage > 0)
	{
		NIRVANAP_stop(); // since there'll be a pause from loading new screen on real Spectrum

		FrontendDrawCurrentRowUnselected();
		_frontendCurrentRow = _frontendRowsPerPage - 1;
		FrontendDrawCurrentRowSelected();

		FrontendPageUp();

		if (!_frontendListModeFull)
		{
			FrontendShowLoadingScreenFile(TRUE);
		}
	}
	else
	{
		NirvanaStartAndCancelRestartNextUpdate();
	}
}

void FrontendProcessInputListDown()
{
	if (_frontendCurrentRow < FrontendGetCurrentPageRowCount() - 1)
	{
		FrontendDrawCurrentRowUnselected();
		++_frontendCurrentRow;
		FrontendDrawCurrentRowSelected();

		if (!_frontendListModeFull)
		{
			FrontendShowLoadingScreenFile(TRUE);
		}
	}
	else if (_frontendCurrentPage < FrontendGetCurrentListPageCount() - 1)
	{
		NIRVANAP_stop(); // since there'll be a pause from loading new screen on real Spectrum

		FrontendDrawCurrentRowUnselected();
		_frontendCurrentRow = 0;
		FrontendDrawCurrentRowSelected();

		FrontendPageDown();

		if (!_frontendListModeFull)
		{
			FrontendShowLoadingScreenFile(TRUE);
		}
	}
	else
	{
		NirvanaStartAndCancelRestartNextUpdate();
	}
}

void FrontendProcessInputListLeft()
{
	if (_frontendCurrentPage > 0)
	{
		FrontendPageUp();

		if (!_frontendListModeFull)
		{
			FrontendShowLoadingScreenFile(TRUE);
		}
	}
	else
	{
		NirvanaStartAndCancelRestartNextUpdate();
	}
}

void FrontendProcessInputListRight()
{
	if (_frontendCurrentPage < FrontendGetCurrentListPageCount() - 1)
	{
		FrontendPageDown();
		if (_frontendCurrentRow >= FrontendGetCurrentPageRowCount())
		{
			FrontendDrawCurrentRowUnselected();
			_frontendCurrentRow = FrontendGetCurrentPageRowCount() - 1;
			FrontendDrawCurrentRowSelected();
		}

		if (!_frontendListModeFull)
		{
			FrontendShowLoadingScreenFile(TRUE);
		}
	}
	else
	{
		NirvanaStartAndCancelRestartNextUpdate();
	}
}

void FrontendProcessInputGamelistSelect(_Bool disable128kPaging)
{
	FrontendLoadFile(disable128kPaging);
}

void FrontendProcessInputGamelistShowLoadingScreen()
{
	FrontendShowLoadingScreenFile(FALSE);
	_frontendLauncherState = kLauncherStateShowLoadingScreenFull;
}

void FrontendProcessInputListToggleMode()
{
	NIRVANAP_stop();

	unsigned int listPosition = (_frontendCurrentPage * _frontendRowsPerPage) + _frontendCurrentRow;

	if (_frontendListModeFull)
	{
		_frontendListModeFull = FALSE;
		_frontendRowsPerPage = kRowCountMini;
	}
	else
	{
		_frontendListModeFull = TRUE;
		_frontendRowsPerPage = kRowCountFull;
	}

	_frontendCurrentPage = listPosition / _frontendRowsPerPage;
	_frontendCurrentRow = listPosition - (_frontendCurrentPage * _frontendRowsPerPage);


	NirvanaLoadEngine(_frontendListModeFull);

	NIRVANAP_stop(); //additional stop needed, Nirvana restarts itself after reloading back to 23 mode
	FrontendPaintNirvanaRowsAttributes(TRUE, _frontendRowsPerPage);
	FrontendDrawCurrentRowSelected();

	if (_frontendLauncherState == kLauncherStateSearchList)
	{
		FrontendLoadSearchListScreen();
	}
	else
	{
		FrontendLoadGameListScreen();
	}

	if (!_frontendListModeFull)
	{
		FrontendShowLoadingScreenFile(TRUE);
	}
}

void FrontendProcessInputListBack()
{
	if (_frontendLauncherState == kLauncherStateSearchList)
	{
		FrontendProcessInputSearchListBack();
	}
	else // kLauncherStateGameList
	{
		FrontendProcessInputGameListBack();
	}
}

void FrontendProcessInputSearchListBack()
{
	FrontendBackToGameList(FALSE);
}

void FrontendProcessInputGameListBack()
{
	NIRVANAP_stop();
	if (!_frontendListModeFull)
	{
		NirvanaLoadEngine(TRUE);

		NIRVANAP_stop(); //additional stop needed, Nirvana restarts itself after reloading back to 23 mode

		FrontendPaintNirvanaRowsAttributes(FALSE, kRowCountFull);
	}
	else
	{
		FrontendDrawCurrentRowUnselected();
	}

	_frontendCurrentRow = 0;
	FrontendDrawCurrentRowSelectedNoScrollBar();

	_frontendLauncherState = kLauncherStateExitMenu;
	FrontendLoadExitMenuScreen();

	_inputWaitForNoInput = TRUE;
}

void FrontendProcessInputListConfiguration()
{
	NIRVANAP_stop();
	if (!_frontendListModeFull)
	{
		NirvanaLoadEngine(TRUE);

		NIRVANAP_stop(); //additional stop needed, Nirvana restarts itself after reloading back to 23 mode

		FrontendPaintNirvanaRowsAttributes(FALSE, kRowCountFull);
	}
	else
	{
		FrontendDrawCurrentRowUnselected();
	}
	_frontendCurrentRow = 0;
	FrontendDrawCurrentRowSelectedNoScrollBar();

	_frontendLauncherState = kLauncherStateConfigurationMenu;
	FrontendLoadConfigurationMenuScreen();
	FrontEndConfigurationMenuDrawRows();

	_inputWaitForNoInput = TRUE;
}

void FrontendBackToGameList(_Bool fromMenu)
{
	NIRVANAP_stop();

	_frontendLauncherState = kLauncherStateGameList;

	_inputASCIIInput = 0;
	_inputWaitForNoInput = TRUE;

	if (fromMenu)
	{
		if (!_frontendListModeFull)
		{
			NIRVANAP_stop();
			NirvanaLoadEngine(FALSE);

			NIRVANAP_stop(); //additional stop needed, Nirvana restarts itself after reloading back to 23 mode

			FrontendPaintNirvanaRowsAttributes(TRUE, _frontendRowsPerPage);
		}
		else
		{
			FrontendDrawCurrentRowUnselectedNoScrollBar();
			FontPaintScrollBar(_frontendScrollBarAttributeValues); // TOIMPROVE just paint the single character cell instead of whole scroll bar for speed
		}
	}
	else
	{
		FrontendDrawCurrentRowUnselected();
	}
	_frontendCurrentPage = _frontendGameListCurrentPage;
	_frontendCurrentRow = _frontendGameListCurrentRow;
	FrontendDrawCurrentRowSelected();

	FrontendLoadGameListScreen();
	if (!_frontendListModeFull)
	{
		FrontendShowLoadingScreenFile(TRUE);
	}
}

void FrontendBackToSearchList()
{

}

void FrontendUpdateProcessInputSearch()
{
	if(InputHeldFrameCountIsOneOrRepeating())
	{
		switch (_inputASCIIInput)
		{
		case kInputASCIIDelete:
			if (_frontendSearchCursorPosition > 0)
			{
				--_frontendSearchCursorPosition;
				--_frontendSearchInputStringLength;

				FrontendDrawSearchString();
			}
			break;
		case kInputASCIIEnter:
			//test code copied from frontend initialise
			NIRVANAP_stop();

			memset((void *)(16384 + 6144 + 256), PAPER_BLACK | INK_RED | BRIGHT, 256);

			FontPaintScrollBar(_frontendScrollBarAttributeValues);

			for (uchar row = 7; row != 15; ++row)
			{
				FontPaintAttributesRowFast((row + 2) * 8, _frontendMenuAttributeValues);
			}
			// end test code

			_frontendLauncherState = kLauncherStateSearchList;

			FrontendDrawCurrentRowUnselected();
			_frontendCurrentPage = 0;
			_frontendCurrentRow = 0;
			FrontendDrawCurrentRowSelected();

			FrontendSetCurrentPageRowCount(0);
			FrontendLoadSearchListScreen();
			if (FrontendGetCurrentPageRowCount() == 0)
			{
				_frontendLauncherState = kLauncherStateGameList;
				FrontendLoadGameListScreen();
			}
			else
			{
				_frontendLauncherState = kLauncherStateSearchList;
			}
			break;
		default:
			if (_frontendSearchInputStringLength < kFrontendSearchInputStringMaximumLength
				&& ((_inputASCIIInput >= '0' && _inputASCIIInput <= '9')
					|| (_inputASCIIInput >= 'A' && _inputASCIIInput <= 'Z'))
				)
			{
				_frontendSearchInputString[_frontendSearchCursorPosition] = _inputASCIIInput;

				++_frontendSearchInputStringLength;
				++_frontendSearchCursorPosition;

				FrontendDrawSearchString();
			}
			break;
		}
	}

	if (_inputStateData.BackHeld)
	{
		//test code copied from frontend initialise
		NIRVANAP_stop();

		memset((void *)(16384 + 6144 + 256), PAPER_BLACK | INK_RED | BRIGHT, 256);

		FontPaintScrollBar(_frontendScrollBarAttributeValues);

		for (uchar row = 0; row != _frontendRowsPerPage; ++row)
		{
			//FontPaintAttributesRow(kFrontendGameNameLength,
			//	0,
			//	(row + 2) * 8,
			//	_frontendMenuAttributeValues);
			FontPaintAttributesRowFast((row + 2) * 8, _frontendMenuAttributeValues);
		}
		// end test code

		FrontendDrawCurrentRowSelected();

		_frontendLauncherState = kLauncherStateGameList;
		FrontendLoadGameListScreen();

		_inputWaitForNoInput = TRUE;
		return;
	}


}

void FrontendUpdateProcessInputLoadingScreenFull()
{
	if (in_test_key() != 0)
	{
		_frontendLauncherState = kLauncherStateGameList;

		FrontendLoadGameListScreen();
		FrontendPaintTopRowAttributes();

		if (!_frontendListModeFull)
		{
			FrontendShowLoadingScreenFile(TRUE);
		}

		_inputWaitForNoInput = TRUE;
	}
}

void FrontendUpdateProcessInputExitMenu()
{
	if (InputHeldFrameCountIsOneOrRepeating())
	{
		if (_inputStateData.UpHeld)
		{
			FrontendProcessInputMenuUp();
			return;
		}
		else if (_inputStateData.DownHeld)
		{
			FrontendProcessInputMenuDown();
			return;
		}
	}

	if (_inputHeldFrameCount != 1)
	{
		return;
	}

	if (_inputStateData.BackHeld)
	{
		FrontendProcessInputMenuBack();
	}
	else if (_inputStateData.SelectHeld)
	{
		FrontendProcessInputExitMenuSelect();
	}
}

void FrontendProcessInputMenuUp()
{
	if (_frontendCurrentRow > 0)
	{
		if (_frontendLauncherState == kLauncherStateConfigurationMenu)
		{
			FrontendConfigurationMenuDrawArrows(TRUE);
		}

		FrontendDrawCurrentRowUnselectedNoScrollBar();
		--_frontendCurrentRow;
		FrontendDrawCurrentRowSelectedNoScrollBar();
	}
}

void FrontendProcessInputMenuDown()
{
	unsigned char menuRowCount;
	if (_frontendLauncherState == kLauncherStateExitMenu)
	{
		menuRowCount = kExitMenuOptionCount;
	}
	else // config menu
	{
		menuRowCount = kConfigurationMenuOptionCount;
	}

	if (_frontendCurrentRow < menuRowCount - 1)
	{
		if (_frontendLauncherState == kLauncherStateConfigurationMenu)
		{
			FrontendConfigurationMenuDrawArrows(TRUE);
		}

		FrontendDrawCurrentRowUnselectedNoScrollBar();
		++_frontendCurrentRow;
		FrontendDrawCurrentRowSelectedNoScrollBar();
	}
}

void FrontendProcessInputMenuLeft()
{
	if (!FrontendConfigurationCurrentRowCanMoveLeft())
	{
		return;
	}

	switch (_frontendCurrentRow)
	{
	case kConfigurationMenuOptionDefaultView:
		--_configurationData.DefaultViewMode;
		break;
	case kConfigurationMenuOptionInputAcceleration:
		--_configurationData.InputAccelerationMode;
		break;
	case kConfigurationMenuOptionKeyboardType:
		--_configurationData.KeyboardType;
		break;
	case kConfigurationMenuOptionJoystickType:
		--_configurationData.JoystickType;
		break;
	case kConfigurationMenuOptionScreensaverType:
		--_configurationData.ScreensaverType;
		break;
	case kConfigurationMenuOptionScreensaverDelayType:
		--_configurationData.ScreensaverDelayType;
		break;
	}

	FrontEndConfigurationMenuDrawRow(_frontendCurrentRow);
}

void FrontendProcessInputMenuRight()
{
	if (!FrontendConfigurationCurrentRowCanMoveRight())
	{
		return;
	}

	switch (_frontendCurrentRow)
	{
	case kConfigurationMenuOptionDefaultView:
		++_configurationData.DefaultViewMode;
		break;
	case kConfigurationMenuOptionInputAcceleration:
		++_configurationData.InputAccelerationMode;
		break;
	case kConfigurationMenuOptionKeyboardType:
		++_configurationData.KeyboardType;
		break;
	case kConfigurationMenuOptionJoystickType:
		++_configurationData.JoystickType;
		break;
	case kConfigurationMenuOptionScreensaverType:
		++_configurationData.ScreensaverType;
		break;
	case kConfigurationMenuOptionScreensaverDelayType:
		++_configurationData.ScreensaverDelayType;
		break;
	}

	FrontEndConfigurationMenuDrawRow(_frontendCurrentRow);
}

void FrontendProcessInputMenuBack()
{
	if (_frontendLauncherState == kLauncherStateConfigurationMenu)
	{
		NIRVANAP_stop();
		ConfigurationSave();
	}

	// TODO call either FrontendBackToGameList() or FrontendBackToSearchList()?
	FrontendBackToGameList(TRUE);
}

void FrontendProcessInputExitMenuSelect()
{
	const char * kRootPath = "/";
	
	switch (_frontendCurrentRow)
	{
	case kExitMenuOptionNMI:
		IOChangeDirectory(kRootPath, kFrontendBasicDataPageLength);
		while (in_test_key() != 0)
		{
			// wait for all keys released so don't trigger instant exit from NMI browser
		}

		__asm
		call 102;
		__endasm;

		zx_border(INK_BLACK);
		memset((void *)(16384 + 6144 + 32), 0, 768 - 32);

		_inputASCIIInput = 0;

		const char * kLibraryPath = "/jplaunch/library";
		IOChangeDirectory(kLibraryPath, kFrontendBasicDataPageLength);

		FrontendBackToGameList(TRUE);
		break;
	case kExitMenuOptionReset:
		__asm
		call 0;
		__endasm;
		break;
	case kExitMenuOptionBack:
		FrontendProcessInputMenuBack();
		break;
	}
}

void FrontendUpdateProcessInputConfigurationMenu()
{
	if (InputHeldFrameCountIsOneOrRepeating())
	{
		if (_inputStateData.UpHeld)
		{
			FrontendProcessInputMenuUp();
			return;
		}
		else if (_inputStateData.DownHeld)
		{
			FrontendProcessInputMenuDown();
			return;
		}
		else if (_inputStateData.LeftHeld)
		{
			FrontendProcessInputMenuLeft();
			return;
		}
		else if (_inputStateData.RightHeld)
		{
			FrontendProcessInputMenuRight();
			return;
		}
	}

	if (_inputHeldFrameCount != 1)
	{
		return;
	}

	if (_inputStateData.BackHeld)
	{
		FrontendProcessInputConfigurationMenuBack();
	}
	else if (_inputStateData.SelectHeld)
	{
		FrontendProcessInputConfigurationMenuSelect();
	}
}

void FrontendProcessInputConfigurationMenuLeft()
{

}

void FrontendProcessInputConfigurationMenuRight()
{

}

void FrontendProcessInputConfigurationMenuSelect()
{
	switch (_frontendCurrentRow)
	{
	case kConfigurationMenuOptionBack:
		FrontendProcessInputConfigurationMenuBack();
		break;
	}
}

void FrontendProcessInputConfigurationMenuBack()
{
	// TODO save config

	FrontendProcessInputMenuBack();
}


// TOIMPROVE - check if these [0] are necessary, or if there's a cleaner way
unsigned int FrontendGetCurrentListPageCount()
{
	return (_listPageCountAddressHighByte[0] * 256) + _listPageCountAddressLowByte[0];
}

unsigned char FrontendGetCurrentPageRowCount()
{
	return _listPageRowCountAddress[0];
}

void FrontendSetCurrentPageRowCount(int value)
{
	_listPageRowCountAddress[0] = value;
}

unsigned int FrontendGetFileIndexFromListRowIndex(unsigned char listRowIndex)
{
	unsigned char characterColumn[1];
	unsigned char pixelRow[1];

	FrontendGetMetadataRowColumnFromIndex(characterColumn, pixelRow, listRowIndex);

	unsigned int fileIndex = FrontendGetFileIndexFromMetadata(characterColumn[0], pixelRow[0]);

	return fileIndex;
}

void FrontendGetMetadataRowColumnFromIndex(unsigned char *characterColumnRef, unsigned char *pixelRowRef, unsigned char listRowIndex)
{
	uchar characterColumn = kMetadataFileIndexStartColumn;
	uchar pixelRow = 0;

	for (uchar index = 0; index < listRowIndex; ++index)
	{
		pixelRow += kRowsPer16BitNumber;
		if (pixelRow == 8) // TODO there should be a const for charHeight in bytes
		{
			pixelRow = 0;
			++characterColumn;
		}
	}

	characterColumnRef[0] = characterColumn;
	pixelRowRef[0] = pixelRow;
}

unsigned int FrontendGetFileIndexFromMetadata(unsigned char characterColumn, unsigned char pixelRow)
{
	int startAddress = 16384 + characterColumn;

	_listPageFileIndexAddressHighByte = (unsigned char*)(startAddress + (pixelRow * 256));
	_listPageFileIndexAddressLowByte = (unsigned char*)(startAddress + ((pixelRow + 1) * 256));// TODO this simplified code doesn't account for 3 bytes of data per row

	int fileIndex = (_listPageFileIndexAddressHighByte[0] * 256) + _listPageFileIndexAddressLowByte[0];

	return fileIndex;
}

void FrontendDrawPopupFade()
{
	// TODO skip top bar?
	// TODO skip middle third

	unsigned int nextLineAddress = 16384;
	do
	{
		memset((void *)nextLineAddress, 0, 32 * 8);
		nextLineAddress += 32 * 8 * 2;
	} 
	while (nextLineAddress != 16384 + 6144);
}

void FrontendDrawSearchWindow()
{
	NIRVANAP_stop();

//	memcpy(_searchWindowPixelDataWriteAddress, _searchWindowPixelDataReadAddress, 2048);
	memcpy((void *)kSearchWindowPixelDataWriteAddress, (void *)kSearchWindowPixelDataReadAddress, 2048);

	// top line
	FontPaintAttributesRowFast(9 * 8, _frontendSearchRow0Attributes);
	NIRVANAP_paintC(_frontendSearchRow0Attributes, 9 * 8, 31);

	// search logo
	FontPaintAttributesRowFast(10 * 8, _frontendSearchRow1Attributes);
	FontPaintAttributesRowFast(11 * 8, _frontendSearchRow2Attributes);
	FontPaintAttributesRowFast(12 * 8, _frontendSearchRow3Attributes);

	//search box
	FontPaintAttributesRowFast(13 * 8, _frontendSearchRow4Attributes);
	FontPaintAttributesRowFast(14 * 8, _frontendSearchRow4Attributes);
	FontPaintAttributesRowFast(15 * 8, _frontendSearchRow4Attributes);

	// bottom line
	FontPaintAttributesRowFast(16 * 8, _frontendSearchRow7Attributes);
	NIRVANAP_paintC(_frontendSearchRow7Attributes, 16 * 8, 31); 

	NIRVANAP_start();
}

void FrontendDrawSearchString()
{
	FontDrawCharStandard("                ", 16, kSearchStringCharacterColumn, kSearchStringCharacterRow);
	FontDrawCharStandard(_frontendSearchInputString, _frontendSearchInputStringLength, kSearchStringCharacterColumn, kSearchStringCharacterRow);
}

//void FrontendDrawGameNames()
//{
//	switch (_frontendFontMode)
//	{
//	case kFontModeProportional:
//		FrontendDrawGameNamesProportional();
//		break;
//	case kFontModeFixed:
//		FrontendDrawGameNamesFixed();
//		break;
//	case kFontModePreRendered:
//		// nothing to do, we already loaded the SCREEN$ in with the game names drawn
//		break;
//	}
//}

//void FrontendDrawGameNamesFixed()
//{
//	// TODO this is probably slowing things down having this test icon declarations here, should be set up once during init:
//	char tapIconChars[2];
//	tapIconChars[0] = 128;
//	tapIconChars[1] = 129;
//
//	char snaIconChars[2];
//	snaIconChars[0] = 130;
//	snaIconChars[1] = 131;
//
//	char z80IconChars[2];
//	z80IconChars[0] = 132;
//	z80IconChars[1] = 133;
//
//	for (uchar row = 0; row != kRowCount; ++row)
//	{
//		//	FontDrawCharStandard(&_database[row * kFrontendGameNameLength], kFrontendGameNameLength, 0, row + 1);
//
//		// version with filetype on left 2 columns
//		const int kFileTypeCharWidth = 2;
//		//FontDrawCharStandard(&_database[row * kFrontendGameNameLength], 32 - kFileTypeCharWidth, kFileTypeCharWidth, row + 1);
//		FontDrawCharsNullTerminated(&_database[row * kFrontendGameNameLength], kFileTypeCharWidth, row + 1);
//
//		//unsigned char testFiletype = row % 3;
//		unsigned char testFiletype = 0;
//		switch (testFiletype)
//		{
//		case 0:
//			FontDrawCharStandard(tapIconChars, 2, 0, row + 1);
//			break;
//		case 1:
//			FontDrawCharStandard(snaIconChars, 2, 0, row + 1);
//			break;
//		case 2:
//			FontDrawCharStandard(z80IconChars, 2, 0, row + 1);
//			break;
//		}
//	}
//}
//
//void FrontendDrawGameNamesProportional()
//{
//	// TODO this is probably slowing things down (and copy pasted from other function!) having this test icon declarations here, should be set up once during init:
//	char tapIconChars[2];
//	tapIconChars[0] = 128;
//	tapIconChars[1] = 129;
//
//	char snaIconChars[2];
//	snaIconChars[0] = 130;
//	snaIconChars[1] = 131;
//
//	char z80IconChars[2];
//	z80IconChars[0] = 132;
//	z80IconChars[1] = 133;
//
//	//memset((void *)16384, 0, 6912 - 768); // clear screen pixels so xor doesn't corrupt with old font gfx
//
//	//FrontendDrawTopBar(); // redraw erase topbar
//
//	FrontendClearScreenPixelsExceptTopBar();
//
//	memset((void *)(16384 + 6912 - 768 + 32), 0, 768 - 32); // clear attribute rows below the top title bar, so clean up leftover selector bar
//
//	for (uchar row = 0; row != kRowCount; ++row)
//	{
//		if (row == kRowCount - 1)
//		{
//			FrontendEraseBottomRowColorCycle();
//		}
//		else
//		{
//			_frontendFillBarFrame = row;
//			FrontendUpdateBottomRowColorCycle();
//		}
//
//		FontDrawCharsProportional(&_database[row * kFrontendGameNameLength], 2, row + 1);
//
//		//unsigned char testFiletype = row % 3;
//		unsigned char testFiletype = 0;
//		switch (testFiletype)
//		{
//		case 0:
//			FontDrawCharStandard(tapIconChars, 2, 0, row + 1);
//			break;
//		case 1:
//			FontDrawCharStandard(snaIconChars, 2, 0, row + 1);
//			break;
//		case 2:
//			FontDrawCharStandard(z80IconChars, 2, 0, row + 1);
//			break;
//		}
//	}
//}
 
void FrontendDrawTopBar()
{
	unsigned char titleChars[13 + 1] = "JPLaunch v0.1"; // array + 1 length for the terminating \0 in c strings
	FontDrawCharStandard(titleChars, 13, 9, 0);

	unsigned char spectrumStripesChars[5];
	spectrumStripesChars[0] = 134;
	spectrumStripesChars[1] = 134;
	spectrumStripesChars[2] = 134;
	spectrumStripesChars[3] = 134;
	spectrumStripesChars[4] = 134;
	FontDrawCharStandard(spectrumStripesChars, 5, 26, 0);
}

void FrontendClearScreenPixelsExceptTopBar()
{
	// top third except top character row
	memset((void *)(16384 + (256 * 0) + 32), 0, 256 - 32);
	memset((void *)(16384 + (256 * 1) + 32), 0, 256 - 32);
	memset((void *)(16384 + (256 * 2) + 32), 0, 256 - 32);
	memset((void *)(16384 + (256 * 3) + 32), 0, 256 - 32);
	memset((void *)(16384 + (256 * 4) + 32), 0, 256 - 32);
	memset((void *)(16384 + (256 * 5) + 32), 0, 256 - 32);
	memset((void *)(16384 + (256 * 6) + 32), 0, 256 - 32);
	memset((void *)(16384 + (256 * 7) + 32), 0, 256 - 32);

	// bottom two thirds
	memset((void *)(16384 + 2048), 0, 6912 - 2048 - 768);

}

void FrontendUpdateBottomRowColorCycle()
{
	//memset((void *)(16384 + 6912 - 32), 0, 32);
	//memset((void *)(16384 + 6912 - 32), PAPER_RED, _frontendFillBarFrame);


	//thin horizontal line instead of blocky bar
	memset((void *)(16384 + 6912 - 768 - 32), 255, 32);
	memset((void *)(16384 + 6912 - 32), INK_RED | BRIGHT, (((int)_frontendFillBarFrame * 150) / 100) + 1);


	//++_frontendColorCycleFrame;
	//if (_frontendColorCycleFrame == kFrontendColorCycleFrameCount)
	//{
	//	_frontendColorCycleFrame = 0;
	//}
}

void FrontendEraseBottomRowColorCycle()
{
	memset((void *)(16384 + 6912 - 768 - 32), 0, 32);
}

void FrontendDrawCurrentRowUnselected()
{
	//FontPaintAttributesRow(kFrontendGameNameLength, 0, (_frontendCurrentRow + 2) * 8, _frontendMenuAttributeValues);

	FontPaintAttributesRowFast((_frontendCurrentRow + 2) * 8, _frontendMenuAttributeValues);
}

void FrontendDrawCurrentRowSelected()
{
	//FontPaintAttributesRow(kFrontendGameNameLength, 0, (_frontendCurrentRow + 2) * 8, _frontendMenuSelectedAttributeValues);

	FontPaintAttributesRowFast((_frontendCurrentRow + 2) * 8, _frontendMenuSelectedAttributeValues);
}

void FrontendDrawCurrentRowUnselectedNoScrollBar()
{
	//FontPaintAttributesRow(kFrontendGameNameLength, 0, (_frontendCurrentRow + 2) * 8, _frontendMenuAttributeValues);

	FontPaintAttributesRowFastNoScrollBar((((_frontendCurrentRow + 1) * 2) + 2) * 8, _frontendMenuAttributeValues);
}

void FrontendDrawCurrentRowSelectedNoScrollBar()
{
	//FontPaintAttributesRow(kFrontendGameNameLength, 0, (_frontendCurrentRow + 2) * 8, _frontendMenuSelectedAttributeValues);

	FontPaintAttributesRowFastNoScrollBar((((_frontendCurrentRow + 1) * 2) + 2) * 8, _frontendMenuSelectedAttributeValues);
}

void FrontendDrawCurrentRowSelectedStandardAttributes()
{
	memset((void *)(16384 + 6144 + 32 + (_frontendCurrentRow * 32)), PAPER_RED | INK_BLACK | BRIGHT, 31);
}

void FrontendLoadFile(_Bool disable128kPaging)
{
// WON'T COMPILE UNDER z88dk, need to precompile with pasmo - have just done in the BASIC code for now to get working
	// TODO preserve registers:
//__asm
//ld (ix), 255; // address
//;//LD A, 48; // value
//OUT (IX), A; // disable 128k RAM paging to fix Ultimate and other games
//__endasm;


	uchar basicData[kFrontendBasicDataTapSnaZ80Length];
	memset(&basicData, kInputASCIIEnter, kFrontendBasicDataTapSnaZ80Length);
	unsigned int fileIndex = FrontendGetFileIndexFromListRowIndex(_frontendCurrentRow);

	uchar paddedTapSnaZ80NumberString[kFrontendTapSnaZ80FileNumberPaddedLength];
	FrontendGetChars(fileIndex, paddedTapSnaZ80NumberString, TRUE);

	unsigned char basicDataIndex = 0;
	for (unsigned char paddedTapSnaZ80NumberStringIndex = 0; paddedTapSnaZ80NumberStringIndex < kFrontendTapSnaZ80FileNumberPaddedLength; ++paddedTapSnaZ80NumberStringIndex)
	{
		basicData[basicDataIndex] = paddedTapSnaZ80NumberString[paddedTapSnaZ80NumberStringIndex];
		++basicDataIndex;
		basicData[basicDataIndex] = '/';
		++basicDataIndex;
	}

	basicData[basicDataIndex] = '0';
	++basicDataIndex;
	basicData[basicDataIndex] = '.';
	++basicDataIndex;

	unsigned char fileFormatType = FrontendGetFileFormat(_frontendCurrentRow);
	switch (fileFormatType)
	{
	case kFileFormatTypeTap:
		basicData[basicDataIndex] = 't';
		++basicDataIndex;
		basicData[basicDataIndex] = 'a';
		++basicDataIndex;
		basicData[basicDataIndex] = 'p';
		++basicDataIndex;

		memcpy(_basicTapFilenameAddress, &basicData, kFrontendBasicDataTapSnaZ80Length);

		if (disable128kPaging)
		{
			exit(kReturnCodeLoadTapDisable128kPaging);
		}
		else
		{
			exit(kReturnCodeLoadTap);
		}
		break;
	case kFileFormatTypeSna:
		basicData[basicDataIndex] = 's';
		++basicDataIndex;
		basicData[basicDataIndex] = 'n';
		++basicDataIndex;
		basicData[basicDataIndex] = 'a';
		++basicDataIndex;

		memcpy(_basicSnaZ80IndexAddress, &basicData, kFrontendBasicDataTapSnaZ80Length);

		if (disable128kPaging)
		{
			exit(kReturnCodeLoadSnaZ80Disable128kPaging);
		}
		else
		{
			exit(kReturnCodeLoadSnaZ80);
		}
		break;
	case kFileFormatTypeZ80:
		basicData[basicDataIndex] = 'z';
		++basicDataIndex;
		basicData[basicDataIndex] = '8';
		++basicDataIndex;
		basicData[basicDataIndex] = '0';
		++basicDataIndex;

		memcpy(_basicSnaZ80IndexAddress, &basicData, kFrontendBasicDataTapSnaZ80Length);

		if (disable128kPaging)
		{
			exit(kReturnCodeLoadSnaZ80Disable128kPaging);
		}
		else
		{
			exit(kReturnCodeLoadSnaZ80);
		}
		break;
	}
}

void FrontendShowLoadingScreenFile(_Bool partial)
{
	NIRVANAP_stop();

	unsigned char basicData[kFrontendBasicDataPageLength];
	memset(&basicData, 0, kFrontendBasicDataPageLength);

	unsigned char basicDataIndex = 0;

	if (partial)
	{
		basicData[basicDataIndex] = 'p';
		++basicDataIndex;
		basicData[basicDataIndex] = 'a';
		++basicDataIndex;
		basicData[basicDataIndex] = 'r';
		++basicDataIndex;
		basicData[basicDataIndex] = 't';
	}
	else
	{
		basicData[basicDataIndex] = 'l';
		++basicDataIndex;
		basicData[basicDataIndex] = 'o';
		++basicDataIndex;
		basicData[basicDataIndex] = 'a';
		++basicDataIndex;
		basicData[basicDataIndex] = 'd';
	}
	++basicDataIndex;
	basicData[basicDataIndex] = '_';
	++basicDataIndex;
	basicData[basicDataIndex] = 's';
	++basicDataIndex;
	basicData[basicDataIndex] = 'c';
	++basicDataIndex;
	basicData[basicDataIndex] = 'r';
	++basicDataIndex;
	basicData[basicDataIndex] = '/';
	++basicDataIndex;

	unsigned int fileIndex = FrontendGetFileIndexFromListRowIndex(_frontendCurrentRow);

	uchar paddedTapSnaZ80NumberString[kFrontendTapSnaZ80FileNumberPaddedLength];
	FrontendGetChars(fileIndex, paddedTapSnaZ80NumberString, TRUE);

	for (unsigned char paddedTapSnaZ80NumberStringIndex = 0; paddedTapSnaZ80NumberStringIndex < kFrontendTapSnaZ80FileNumberPaddedLength; ++paddedTapSnaZ80NumberStringIndex)
	{
		basicData[basicDataIndex] = paddedTapSnaZ80NumberString[paddedTapSnaZ80NumberStringIndex];
		++basicDataIndex;
		basicData[basicDataIndex] = '/';
		++basicDataIndex;
	}

	basicData[basicDataIndex] = '0';

#ifdef kDebugFakeLoadDelayForEmulator
	IOFakeScreenLoadDelay();
#endif

	if (partial)
	{
		IOLoadBytes(&basicData, kFrontendBasicDataPageLength, 16384 + 2048);
		FrontendDrawCurrentRowSelectedStandardAttributes();

		_nirvanaRestartNextUpdate = TRUE;
	}
	else
	{
		IOLoadBytes(&basicData, kFrontendBasicDataPageLength, 16384);
	}

}

unsigned char FrontendGetFileFormat(unsigned char rowIndex)
{
	uchar pixelRow = 0;
	uchar bitPairIndex = 0;

	for (uchar index = 0; index < rowIndex; ++index)
	{
		++bitPairIndex;
		if (bitPairIndex == kBitPairsPerPixelRow)
		{
			bitPairIndex = 0;
			++pixelRow;
		}
	}

	int startAddress = 16384 + kMetadataFileFormatStartColumn;
	_listPageFileFormatAddress = (unsigned char*)(startAddress + (pixelRow * 256));

	unsigned char fileFormatPackedByte = _listPageFileFormatAddress[0];
	unsigned char fileFormat = (fileFormatPackedByte >> ((kBitPairsPerPixelRow - 1 - bitPairIndex) * 2)) & 3;
	
	return fileFormat;
}

void FrontendLoadGameListScreen()
{
	NIRVANAP_stop();

	//memset((void *)(16384 + 6144 + 32), PAPER_BLACK | INK_YELLOW | BRIGHT, 768 - 32);

	unsigned char basicData[kFrontendBasicDataPageLength];
	memset(&basicData, 0, kFrontendBasicDataPageLength);

	uchar paddedPageNumberString[kFrontendGameListPageIndexPaddedMaximumLength];
	FrontendGetChars(_frontendCurrentPage, paddedPageNumberString, FALSE);

	unsigned char basicDataIndex = 0;

	basicData[basicDataIndex] = 'g';
	++basicDataIndex;
	basicData[basicDataIndex] = 'a';
	++basicDataIndex;
	basicData[basicDataIndex] = 'm';
	++basicDataIndex;
	basicData[basicDataIndex] = 'e';
	++basicDataIndex;
	if (_frontendListModeFull)
	{
		basicData[basicDataIndex] = 'f';
		++basicDataIndex;
		basicData[basicDataIndex] = 'u';
		++basicDataIndex;
		basicData[basicDataIndex] = 'l';
		++basicDataIndex;
		basicData[basicDataIndex] = 'l';
	}
	else
	{
		basicData[basicDataIndex] = 'm';
		++basicDataIndex;
		basicData[basicDataIndex] = 'i';
		++basicDataIndex;
		basicData[basicDataIndex] = 'n';
		++basicDataIndex;
		basicData[basicDataIndex] = 'i';
	}
	++basicDataIndex;
	basicData[basicDataIndex] = '/';
	++basicDataIndex;

	for (unsigned char paddedPageNumberStringIndex = 0; paddedPageNumberStringIndex < kFrontendGameListPageIndexPaddedMaximumLength; ++paddedPageNumberStringIndex)
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
	
	_nirvanaRestartNextUpdate = TRUE;
}

void FrontendLoadSearchListScreen()
{
	NIRVANAP_stop();
	
	uchar basicData[kFrontendBasicDataSearchMaximumLength];
	memset(&basicData, 0, kFrontendBasicDataSearchMaximumLength);

	uchar paddedPageNumberString[4];
	FrontendGetChars(_frontendCurrentPage, paddedPageNumberString, FALSE);

	unsigned char basicDataIndex = 0;

	basicData[basicDataIndex] = 's';
	++basicDataIndex;
	basicData[basicDataIndex] = 'r';
	++basicDataIndex;
	basicData[basicDataIndex] = 'c';
	++basicDataIndex;
	basicData[basicDataIndex] = 'h';
	++basicDataIndex;
	if (_frontendListModeFull)
	{
		basicData[basicDataIndex] = 'f';
		++basicDataIndex;
		basicData[basicDataIndex] = 'u';
		++basicDataIndex;
		basicData[basicDataIndex] = 'l';
		++basicDataIndex;
		basicData[basicDataIndex] = 'l';
	}
	else
	{
		basicData[basicDataIndex] = 'm';
		++basicDataIndex;
		basicData[basicDataIndex] = 'i';
		++basicDataIndex;
		basicData[basicDataIndex] = 'n';
		++basicDataIndex;
		basicData[basicDataIndex] = 'i';
	}
	++basicDataIndex;
	basicData[basicDataIndex] = '/';
	++basicDataIndex;

	for (unsigned char searchInputStringCharIndex = 0; searchInputStringCharIndex < _frontendSearchInputStringLength; ++searchInputStringCharIndex)
	{
		basicData[basicDataIndex] = _frontendSearchInputString[searchInputStringCharIndex];
		++basicDataIndex;
		basicData[basicDataIndex] = '/';
		++basicDataIndex;
	}

	basicData[basicDataIndex] = paddedPageNumberString[0];
	++basicDataIndex;
	basicData[basicDataIndex] = paddedPageNumberString[1];
	++basicDataIndex;
	basicData[basicDataIndex] = paddedPageNumberString[2];
	++basicDataIndex;
	basicData[basicDataIndex] = paddedPageNumberString[3];
	
#ifdef kDebugFakeLoadDelayForEmulator
	IOFakeScreenLoadDelay();
#endif

	IOLoadBytes(&basicData, kFrontendBasicDataSearchMaximumLength, 16384);

	_nirvanaRestartNextUpdate = TRUE;
}

void FrontendLoadExitMenuScreen()
{
#ifdef kDebugFakeLoadDelayForEmulator
	IOFakeScreenLoadDelay();
#endif

	const char * kExitMenuScreenPath = "../graphics/exit";
	IOLoadBytes(kExitMenuScreenPath, kFrontendBasicDataPageLength, 16384);

	NIRVANAP_start();
}

void FrontendLoadConfigurationMenuScreen()
{
#ifdef kDebugFakeLoadDelayForEmulator
	IOFakeScreenLoadDelay();
#endif

	const char * kConfigurationMenuScreenPath = "../graphics/config";
	IOLoadBytes(kConfigurationMenuScreenPath, kFrontendBasicDataPageLength, 16384);

	NIRVANAP_start();
}

void FrontEndConfigurationMenuDrawRows()
{
	for (unsigned char rowIndex = 0; rowIndex != kConfigurationMenuOptionCount - 1; ++rowIndex)
	{
		FrontEndConfigurationMenuDrawRow(rowIndex);
	}
}

void FrontEndConfigurationMenuDrawRow(unsigned char rowIndex)
{
	const char* string;
	switch (rowIndex)
	{
	case kConfigurationMenuOptionDefaultView:
		switch (_configurationData.DefaultViewMode)
		{
		case DefaultViewModeFullScreenList:
			string = "Full screen list";
			break;
		case DefaultViewModeMiniListAndImage:
			string = "Mini-list and image";
			break;
		}
		break;

	case kConfigurationMenuOptionInputAcceleration:
		switch (_configurationData.InputAccelerationMode)
		{
		case InputAccelerationModePageAndRow:
			string = "Page up/down and row up/down";
			break;
		case InputAccelerationModePage:
			string = "Page up/down";
			break;
		case InputAccelerationModeRow:
			string = "Row up/down";
			break;
		case InputAccelerationModeDisabled:
			string = "Disabled";
			break;
		}
		break;

	case kConfigurationMenuOptionKeyboardType:
		switch (_configurationData.KeyboardType)
		{
		case KeyboardTypeNon48KWithCursor:
			string = "48K+ / 128K / +2 / +3";
			break;
		case KeyboardType48KWithoutCursor:
			string = "48K";
			break;
		}
		break;

	case kConfigurationMenuOptionJoystickType:
		switch (_configurationData.JoystickType)
		{
		case JoystickTypeDisabled:
			string = "Disabled";
			break;
		case JoystickTypeSinclair:
			string = "Sinclair";
			break;
		case JoystickTypeKempston:
			string = "Kempston";
			break;
		case JoystickTypeCursor:
			string = "Cursor";
			break;
		}
		break;

	case kConfigurationMenuOptionScreensaverType:
		switch (_configurationData.ScreensaverType)
		{
		case ScreensaverTypeDisabled:
			string = "Disabled";
			break;
		case ScreensaverTypeFractalZoom:
			string = "Fractal Zoom";
			break;
		}
		break;

	case kConfigurationMenuOptionScreensaverDelayType:
		switch (_configurationData.ScreensaverDelayType)
		{
		case ScreensaverDelayTypeTwoMinutes:
			string = "2 Minutes";
			break;
		case ScreensaverDelayTypeThreeMinutes:
			string = "3 Minutes";
			break;
		case ScreensaverDelayTypeFiveMinutes:
			string = "5 Minutes";
			break;
		case ScreensaverDelayTypeTenMinutes:
			string = "10 Minutes";
			break;
		}
		break;

	case kConfigurationMenuOptionNMISYSStartupPath:
		string = "/newgames";
		break;
	}

	// TODO much faster way of clearing this:

	unsigned char charY = 3 + (rowIndex * 2);

	FontDrawCharsNullTerminated("               ", 16, charY); // VERY SLOW WAY OF ERASING FOR NOW!

	FontDrawCharsProportional((char *)string, (unsigned char)(128 + 8), charY * 8);
}

void FrontendConfigurationMenuDrawArrows(_Bool eraseArrows)
{
	if (!FrontendConfigurationCurrentRowCanMoveLeft() && !FrontendConfigurationCurrentRowCanMoveRight())
	{
		return;
	}

	unsigned char charY = 3 + (_frontendCurrentRow * 2);

	if (!eraseArrows && _frontendFrameCount % 128 < 64)
	{
		if (FrontendConfigurationCurrentRowCanMoveLeft())
		{
			FontDrawCharsNullTerminated("<", 16, charY);
		}
		if (FrontendConfigurationCurrentRowCanMoveRight())
		{
			FontDrawCharsNullTerminated(">", 31, charY);
		}
	}
	else
	{
		FontDrawCharsNullTerminated(" ", 16, charY);
		FontDrawCharsNullTerminated(" ", 31, charY);
	}
}

_Bool FrontendConfigurationCurrentRowCanMoveLeft()
{
	switch (_frontendCurrentRow)
	{
	case kConfigurationMenuOptionDefaultView:
		return _configurationData.DefaultViewMode > 0;
	case kConfigurationMenuOptionInputAcceleration:
		return _configurationData.InputAccelerationMode > 0;
	case kConfigurationMenuOptionKeyboardType:
		return _configurationData.KeyboardType > 0;
	case kConfigurationMenuOptionJoystickType:
		return _configurationData.JoystickType > 0;
	case kConfigurationMenuOptionScreensaverType:
		return _configurationData.ScreensaverType > 0;
	case kConfigurationMenuOptionScreensaverDelayType:
		return _configurationData.ScreensaverDelayType > 0;
	default:
		return FALSE;
	}
}

_Bool FrontendConfigurationCurrentRowCanMoveRight()
{
	switch (_frontendCurrentRow)
	{
	case kConfigurationMenuOptionDefaultView:
		return _configurationData.DefaultViewMode < DefaultViewModeCount - 1;
	case kConfigurationMenuOptionInputAcceleration:
		return _configurationData.InputAccelerationMode < InputAccelerationModeCount - 1;
	case kConfigurationMenuOptionKeyboardType:
		return _configurationData.KeyboardType < KeyboardTypeCount - 1;
	case kConfigurationMenuOptionJoystickType:
		return _configurationData.JoystickType < JoystickTypeCount - 1;
	case kConfigurationMenuOptionScreensaverType:
		return _configurationData.ScreensaverType < ScreensaverTypeCount - 1;
	case kConfigurationMenuOptionScreensaverDelayType:
		return _configurationData.ScreensaverDelayType < ScreensaverDelayTypeCount - 1;
	default:
		return FALSE;
	}
}

void FrontendPageUp()
{
	_frontendCurrentPage--;
	if (_frontendLauncherState == kLauncherStateSearchList)
	{
		FrontendLoadSearchListScreen();
	}
	else
	{
		FrontendLoadGameListScreen();
	}
}

void FrontendPageDown()
{
	_frontendCurrentPage++;
	if (_frontendLauncherState == kLauncherStateSearchList)
	{
		FrontendLoadSearchListScreen();
	}
	else
	{
		FrontendLoadGameListScreen();
	}
}

void FrontendGetChars(unsigned int value, char * chars, _Bool fiveChars)
{
	chars[0] = '0';
	chars[1] = '0';
	chars[2] = '0';
	chars[3] = '0';

	unsigned int startIndex = 3;
	if (fiveChars)
	{
		startIndex = 4;
		chars[4] = '0';
	}

	const int kZeroASCII = 48;
	chars[startIndex] = (uchar)(kZeroASCII + (value % 10));
	--startIndex;

	if (value >= 10)
	{
		chars[startIndex] = (uchar)(kZeroASCII + (value % 100) / 10);
	}
	--startIndex;

	if (value >= 100)
	{
		chars[startIndex] = (uchar)(kZeroASCII + (value % 1000) / 100);
	}
	--startIndex;

	if (value >= 1000)
	{
		chars[startIndex] = (uchar)(kZeroASCII + (value % 10000)/ 1000);
	}
	--startIndex;

	if (value >= 10000)
	{
		chars[startIndex] = (uchar)(kZeroASCII + (value % 100000) / 10000);
	}
}

void FrontendSearchInputInitialise()
{
	_frontendLauncherState = kLauncherStateSearchInput;

	_frontendSearchInputStringLength = 0;
	_frontendSearchCursorPosition = 0;

	//FrontendDrawPopupFade();
	FrontendDrawSearchWindow();

	FrontendUpdateProcessInputSearch();
}

void FrontendSearchInputUpdate()
{

}

