#include "headers.h"

#include "io.c"
#include "configuration.c"
#include "nirvana.c"
#include "frontend.c"
#include "game.c"
#include "font.c"


#pragma output CRT_ORG_CODE          = 25000
#pragma output CLIB_OPT_PRINTF       = 0x00000400   // enable %c for printf only
#pragma output CLIB_MALLOC_HEAP_SIZE = 0            // do not create a heap
#pragma output REGISTER_SP           = -1           // do not change sp

#pragma output CLIB_EXIT_STACK_SIZE  = 0   // no exit stack
#pragma output CLIB_STDIO_HEAP_SIZE  = 0   // no stdio heap for fd structures
#pragma output CLIB_FOPEN_MAX        = 0   // no allocated FILE structures
#pragma output CLIB_OPEN_MAX         = 0   // no fd table

//extern unsigned char btiles[];


main()
{
	AppLoadResources();

	ConfigurationInitialise();

	NirvanaLoadEngine(_configurationData.DefaultViewMode == DefaultViewModeFullScreenList);

	FrontendInitialise();

	while (TRUE)
	{
		FrontendUpdate();
	}
}

void AppLoadResources()
{
	// TODO figure out why these only work in certain orders!  had to put the fonts at the end otherwise they
	// didn't load/were overwritten and the memory was all zeros instead of the data

	const char * kSearchWindowPath = "../graphics/srch_win";
	IOLoadBytes(kSearchWindowPath, kFrontendBasicDataPageLength, kSearchWindowPixelDataReadAddress);

	const char * kChDirRoutinePath = "../code/chdir";
	IOLoadBytes(kChDirRoutinePath, kFrontendBasicDataPageLength, kRoutineChDirBaseAddress);

	const char * kBSaveRoutinePath = "../code/bsave";
	IOLoadBytes(kBSaveRoutinePath, kFrontendBasicDataPageLength, kRoutineBSaveBaseAddress);

	const char* kFontProportionalPath = "../graphics/propfont";
	IOLoadBytes(kFontProportionalPath, kFrontendBasicDataPageLength, kProportionalFontBaseAddress);

	const char* kFontFixedPath = "../graphics/8x8font";
	IOLoadBytes(kFontFixedPath, kFrontendBasicDataPageLength, kFontSheetBaseAddress);
}
