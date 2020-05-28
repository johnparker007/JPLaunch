#include "headers.h"

const unsigned char kNirvanaByte0Value23Rows = 3;
const unsigned char kNirvanaByte1Value23Rows = 251;

const unsigned char kNirvanaByte0Value7Rows = 131;
const unsigned char kNirvanaByte1Value7Rows = 230;

const char * kNirvanaEnginePath23Rows = "../code/nirvana";
const char * kNirvanaEnginePath7Rows = "../code/nirvana7";

const unsigned int kStartAddressOfThisCFileCompiled = 25000; // where we loaded this z80 code block into ram

void NirvanaLoadEngine(_Bool rows23)
{
	if (_nirvanaRowHeightPatchAddress == 0)
	{
		NirvanaRowHeightPatchAddressInitialise();
	}

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
