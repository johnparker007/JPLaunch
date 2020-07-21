#ifndef __CONFIGURATION_H__
#define __CONFIGURATION

enum DefaultViewModes
{
	DefaultViewModeFullScreenList,
	DefaultViewModeMiniListAndImage,

	DefaultViewModeCount
};

enum InputAccelerationModes
{
	InputAccelerationModePageAndRow,
	InputAccelerationModePage,
	InputAccelerationModeRow,
	InputAccelerationModeDisabled,

	InputAccelerationModeCount
};

enum KeyboardTypes
{
	KeyboardTypeNon48KWithCursor,
	KeyboardType48KWithoutCursor,

	KeyboardTypeCount
};

enum JoystickTypes
{
	JoystickTypeDisabled,
	JoystickTypeSinclair,
	JoystickTypeKempston,
	JoystickTypeCursor,

	JoystickTypeCount
};

enum ScreensaverTypes
{
	ScreensaverTypeDisabled,
	ScreensaverTypeFractalZoom,

	ScreensaverTypeCount
};

enum ScreensaverDelayTypes
{
	ScreensaverDelayTypeTwoMinutes,
	ScreensaverDelayTypeThreeMinutes,
	ScreensaverDelayTypeFiveMinutes,
	ScreensaverDelayTypeTenMinutes,

	ScreensaverDelayTypeCount
};

struct ConfigurationData
{
	_Bool ConfigurationFileLoaded;

	unsigned char DefaultViewMode;
	unsigned char InputAccelerationMode;
	unsigned char KeyboardType;
	unsigned char JoystickType;
	unsigned char ScreensaverType;
	unsigned char ScreensaverDelayType;
};

struct ConfigurationData _configurationData;

void ConfigurationInitialise();
void ConfigurationSave();
void ConfigurationLoad();

#endif
