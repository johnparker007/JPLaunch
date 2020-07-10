#include "headers.h"

_Bool InputBlockedAwaitingKeyUp()
{
	if (_inputWaitForNoInput && in_test_key() != 0)
	{
		return TRUE;
	}

	_inputWaitForNoInput = FALSE;
	return FALSE;
}

_Bool InputHeldFrameCountIsOneOrRepeating()
{
	// TODO - default to 23 rows shen not in list view (ie full screen menus etc)
	return _inputHeldFrameCount == 1 
		|| _inputHeldFrameCount > 
			(_frontendListModeFull || (_frontendLauncherState != kLauncherStateSearchList && _frontendLauncherState != kLauncherStateGameList)
			? kInputHeldRepeatStartFrameCount23Rows : kInputHeldRepeatStartFrameCount7Rows);
}

void InputGetInput()
{
	_inputASCIIInput = in_inkey();

	// TODO read these scancode states as a couple of keyboard joystick scans

	_inputStateData.BackHeld = in_key_pressed(IN_KEY_SCANCODE_CAPS) && in_key_pressed(IN_KEY_SCANCODE_SPACE);
	_inputStateData.ShowFullScreenImageHeld = !in_key_pressed(IN_KEY_SCANCODE_CAPS) && in_key_pressed(IN_KEY_SCANCODE_SPACE);
	_inputStateData.SelectHeld = in_key_pressed(IN_KEY_SCANCODE_ENTER);
	_inputStateData.ViewModeToggleHeld = in_key_pressed(IN_KEY_SCANCODE_CAPS) && in_key_pressed(IN_KEY_SCANCODE_SYM);
	_inputStateData.ConfigurationHeld = in_key_pressed(IN_KEY_SCANCODE_CAPS) && in_key_pressed(IN_KEY_SCANCODE_1);

	if (_configurationData.KeyboardType == KeyboardTypeNon48KWithCursor)
	{
		_inputStateData.UpHeld = in_key_pressed(IN_KEY_SCANCODE_CAPS) && in_key_pressed(IN_KEY_SCANCODE_7);
		_inputStateData.DownHeld = in_key_pressed(IN_KEY_SCANCODE_CAPS) && in_key_pressed(IN_KEY_SCANCODE_6);
		_inputStateData.LeftHeld = in_key_pressed(IN_KEY_SCANCODE_CAPS) && in_key_pressed(IN_KEY_SCANCODE_5);
		_inputStateData.RightHeld = in_key_pressed(IN_KEY_SCANCODE_CAPS) && in_key_pressed(IN_KEY_SCANCODE_8);
	}
	else
	{
		_inputStateData.UpHeld = in_key_pressed(IN_KEY_SCANCODE_7);
		_inputStateData.DownHeld = in_key_pressed(IN_KEY_SCANCODE_6);
		_inputStateData.LeftHeld = in_key_pressed(IN_KEY_SCANCODE_5);
		_inputStateData.RightHeld = in_key_pressed(IN_KEY_SCANCODE_8);
	}

	if (!_inputStateData.BackHeld
		&& !_inputStateData.SelectHeld
		&& !_inputStateData.ViewModeToggleHeld
		&& !_inputStateData.ConfigurationHeld
		&& !_inputStateData.ShowFullScreenImageHeld
		&& !_inputStateData.UpHeld
		&& !_inputStateData.DownHeld
		&& !_inputStateData.LeftHeld
		&& !_inputStateData.RightHeld
		&& _inputASCIIInput == 0)
	{
		_inputHeldFrameCount = 0;
	}
	else
	{
		if (_inputHeldFrameCount < 65535)
		{
			++_inputHeldFrameCount;
		}

		InputGetUppercaseASCIIInput();
	}
}

void InputGetUppercaseASCIIInput()
{
	if (_inputASCIIInput >= 'a' && _inputASCIIInput <= 'z')
	{
		const int kUpperCaseOffset = 32;
		_inputASCIIInput -= kUpperCaseOffset;
	}
}
