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
	return _inputHeldFrameCount == 1 || InputHeldFrameCountIsRepeating();
}

_Bool InputHeldFrameCountIsRepeating()
{
	return _inputHeldFrameCount >
		(_frontendListModeFull || (_frontendLauncherState != kLauncherStateSearchList && _frontendLauncherState != kLauncherStateGameList)
			? kInputHeldRepeatStartFrameCount23Rows : kInputHeldRepeatStartFrameCount7Rows);
}

void InputGetInput()
{
	_inputASCIIInput = in_inkey();

	// TODO read these scancode states as a couple of keyboard joystick scans

	_inputStateData.BackHeld = in_key_pressed(IN_KEY_SCANCODE_SPACE) && in_key_pressed(IN_KEY_SCANCODE_CAPS);
	_inputStateData.ShowFullScreenImageHeld = in_key_pressed(IN_KEY_SCANCODE_SPACE) && !in_key_pressed(IN_KEY_SCANCODE_CAPS);
	_inputStateData.SelectHeld = in_key_pressed(IN_KEY_SCANCODE_ENTER);
	_inputStateData.ViewModeToggleHeld = in_key_pressed(IN_KEY_SCANCODE_SYM) && in_key_pressed(IN_KEY_SCANCODE_CAPS);
	_inputStateData.ConfigurationHeld = in_key_pressed(IN_KEY_SCANCODE_1) && in_key_pressed(IN_KEY_SCANCODE_CAPS);

	if (_configurationData.KeyboardType == KeyboardTypeNon48KWithCursor)
	{
		_inputStateData.UpHeld = in_key_pressed(IN_KEY_SCANCODE_7) && in_key_pressed(IN_KEY_SCANCODE_CAPS);
		_inputStateData.DownHeld = in_key_pressed(IN_KEY_SCANCODE_6) && in_key_pressed(IN_KEY_SCANCODE_CAPS);
		_inputStateData.LeftHeld = in_key_pressed(IN_KEY_SCANCODE_5) && in_key_pressed(IN_KEY_SCANCODE_CAPS);
		_inputStateData.RightHeld = in_key_pressed(IN_KEY_SCANCODE_8) && in_key_pressed(IN_KEY_SCANCODE_CAPS);
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

		if (_frontendLauncherState != kLauncherStateScreensaver)
		{
			if (in_test_key() == 0)
			{
				++_inputFramesSinceInputCount;
			}
			else
			{
				_inputFramesSinceInputCount = 0;
			}
		}
	}
	else
	{
		if (_inputHeldFrameCount < 65535)
		{
			++_inputHeldFrameCount;
		}

		InputGetUppercaseASCIIInput();

		_inputFramesSinceInputCount = 0;
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
