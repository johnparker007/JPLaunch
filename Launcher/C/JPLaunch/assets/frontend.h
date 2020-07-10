#ifndef __FRONTEND_H__
#define __FRONTEND_H__

#define kFrontendMenuOptionNumberCharacterColumn		(2)
#define kFrontendMenuOptionNameCharacterColumn			(4)

#define kFrontendMenuSelectedAttributeArrayLength		(12)

#define kFrontendGameNameLength							(64)

#define kFrontendColorCycleFrameCount					(8)

#define kFrontendSearchInputStringMaximumLength			(16)
#define kFrontendBasicDataSearchMaximumLength			(((kFrontendSearchInputStringMaximumLength * 2) - 1) + 4 + 7) //+4 for ".scr", +8 for _000000

#define kFrontendTapSnaZ80FileNumberPaddedLength		(5)
#define kFrontendBasicDataTapSnaZ80Length				((kFrontendTapSnaZ80FileNumberPaddedLength * 2) + 5) //+5 for "0.tap"

#define kFrontendGameListPageIndexPaddedMaximumLength	(4)

#define kFrontendBasicDataPageLength					(54)


#define kLauncherStateGetFirstPage (0)
#define kLauncherStateUninitialised (1)
#define kLauncherStateGameList (2)
//#define kLauncherStateSearching (3) unused
#define kLauncherStateSearchInput (4)
#define kLauncherStateSearchList (5)
#define kLauncherStateShowLoadingScreenFull (6)
#define kLauncherStateExitMenu (7)
#define kLauncherStateConfigurationMenu (8)


unsigned char _frontendFrameCount;


unsigned char _frontendTitleAttributeValues[4];
unsigned char _frontendCopyrightAttributeValues[4];
unsigned char _frontendMenuAttributeValues[4];
unsigned char _frontendScrollBarAttributeValues[4];
unsigned char _frontendSearchRow0Attributes[4];
unsigned char _frontendSearchRow1Attributes[4];
unsigned char _frontendSearchRow2Attributes[4];
unsigned char _frontendSearchRow3Attributes[4];
unsigned char _frontendSearchRow4Attributes[4];
unsigned char _frontendSearchRow5Attributes[4];
unsigned char _frontendSearchRow6Attributes[4];
unsigned char _frontendSearchRow7Attributes[4];



unsigned char _frontendMenuSelectedAttributeValues[12];
unsigned char _frontendMenuSelectedAttributeStartIndex;

unsigned char _frontendCurrentRow;
unsigned int _frontendCurrentPage;

unsigned char _frontendSearchListCurrentRow;
unsigned int _frontendSearchListCurrentPage;
unsigned char _frontendGameListCurrentRow;
unsigned int _frontendGameListCurrentPage;

unsigned char _frontendLauncherState;
unsigned char _frontendFontMode;
_Bool _frontendListModeFull;
unsigned char _frontendRowsPerPage;

unsigned char _frontendColorCycleScrollBuffer[32 + kFrontendColorCycleFrameCount];
unsigned char _frontendColorCycleFrame;

unsigned char _frontendFillBarFrame;

unsigned char _frontendSearchInputString[kFrontendSearchInputStringMaximumLength + 1]; // +1 for end of c string null terminator (required?)
unsigned char _frontendSearchInputStringLength;
unsigned char _frontendSearchCursorPosition;

void FrontendInitialise();
void FrontendInitialiseScreen();
void FrontendPaintTopRowAttributes();
void FrontendPaintNirvanaRowsAttributes(_Bool includeScrollbar, unsigned char rowCount);
void FrontendInitialiseAttributeValues();

void FrontendUpdate();

void FrontendUpdateProcessInputList();

void FrontendProcessInputListUp();
void FrontendProcessInputListDown();
void FrontendProcessInputListLeft();
void FrontendProcessInputListRight();
void FrontendProcessInputGamelistSelect(_Bool disable128kPaging);
void FrontendProcessInputGamelistShowLoadingScreen();
void FrontendProcessInputListToggleMode();
void FrontendProcessInputListBack();
void FrontendProcessInputSearchListBack();
void FrontendProcessInputGameListBack();
void FrontendProcessInputListConfiguration();


void FrontendBackToGameList(_Bool fromMenu);
void FrontendBackToSearchList();

void FrontendUpdateProcessInputSearch();

void FrontendUpdateProcessInputLoadingScreenFull();

void FrontendUpdateProcessInputExitMenu();

void FrontendProcessInputMenuUp();
void FrontendProcessInputMenuDown();
void FrontendProcessInputMenuLeft();
void FrontendProcessInputMenuRight();

void FrontendProcessInputMenuBack();

void FrontendProcessInputExitMenuSelect();

void FrontendUpdateProcessInputConfigurationMenu();

void FrontendProcessInputConfigurationMenuLeft();
void FrontendProcessInputConfigurationMenuRight();
void FrontendProcessInputConfigurationMenuSelect();
void FrontendProcessInputConfigurationMenuBack();

unsigned int FrontendGetCurrentListPageCount();
unsigned char FrontendGetCurrentPageRowCount();
void FrontendSetCurrentPageRowCount(int value);

unsigned int FrontendGetFileIndexFromListRowIndex(unsigned char listRowIndex);
void FrontendGetMetadataRowColumnFromIndex(unsigned char *characterColumnRef, unsigned char *pixelRowRef, unsigned char listRowIndex);
unsigned int FrontendGetFileIndexFromMetadata(unsigned char characterColumn, unsigned char pixelRow);


void FrontendDrawCurrentRowUnselected(); 
void FrontendDrawCurrentRowSelected();
void FrontendDrawCurrentRowUnselectedNoScrollBar();
void FrontendDrawCurrentRowSelectedNoScrollBar();
void FrontendDrawCurrentRowSelectedStandardAttributes();

void FrontendDrawPopupFade();
void FrontendDrawSearchWindow();
void FrontendDrawSearchString();

void FrontendDrawTopBar();
void FrontendClearScreenPixelsExceptTopBar();

void FrontendUpdateBottomRowColorCycle();
void FrontendEraseBottomRowColorCycle();

void FrontendLoadFile(_Bool disable128kPaging);

void FrontendShowLoadingScreenFile(_Bool partial);

unsigned char FrontendGetFileFormat(unsigned char rowIndex);
void FrontendLoadGameListScreen();
void FrontendLoadSearchListScreen();
void FrontendLoadExitMenuScreen();
void FrontendLoadConfigurationMenuScreen();

void FrontEndConfigurationMenuDrawRows();
void FrontEndConfigurationMenuDrawRow(unsigned char rowIndex);

void FrontendConfigurationMenuDrawArrows(_Bool eraseArrows);

_Bool FrontendConfigurationCurrentRowCanMoveLeft();
_Bool FrontendConfigurationCurrentRowCanMoveRight();




void FrontendPageUp();
void FrontendPageDown();

void FrontendGetChars(unsigned int value, char * chars, _Bool fiveChars);

void FrontendSearchInputInitialise();
void FrontendSearchInputUpdate();



#endif
