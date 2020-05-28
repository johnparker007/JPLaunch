#include "headers.h"

#define kConfigPathString "../jpconfig"
#define kConfigPathStringLength (11 + 1)


void ConfigurationInitialise()
{
	ConfigurationLoad();

	// TODO preserve this in Installer on fresh Install over the top
	if (!_configurationData.ConfigurationFileLoaded)
	{
		_configurationData.ConfigurationFileLoaded = TRUE;
		_configurationData.DefaultViewMode = DefaultViewModeFullScreenList;
		_configurationData.InputAccelerationMode = InputAccelerationModePageAndRow;
		_configurationData.KeyboardType = KeyboardTypeNon48KWithCursor;
		_configurationData.JoystickType = JoystickTypeDisabled;

		ConfigurationSave();
	}
}

void ConfigurationSave()
{
	IOSaveBytes(kConfigPathString, kConfigPathStringLength, (unsigned int)(&_configurationData), sizeof(_configurationData));
}

void ConfigurationLoad()
{
	IOLoadBytes(kConfigPathString, kConfigPathStringLength, (unsigned int)(&_configurationData));
}