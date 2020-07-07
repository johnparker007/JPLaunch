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
	return _inputHeldFrameCount == 1 || _inputHeldFrameCount > kInputHeldRepeatStartFrameCountUpDown;
}

void InputGetUppercaseASCIIInput()
{
	_inputASCIIInput = in_inkey();

	if (_inputASCIIInput >= 'a' && _inputASCIIInput <= 'z')
	{
		const int kUpperCaseOffset = 32;
		_inputASCIIInput -= kUpperCaseOffset;
	}
}

void InputSample()
{
	_inputStateData.BackHeld = in_key_pressed(IN_KEY_SCANCODE_CAPS) && in_key_pressed(IN_KEY_SCANCODE_SPACE);
	_inputStateData.SelectHeld = in_key_pressed(IN_KEY_SCANCODE_ENTER);
	_inputStateData.ViewModeToggleHeld = in_key_pressed(IN_KEY_SCANCODE_CAPS) && in_key_pressed(IN_KEY_SCANCODE_SYM);
	_inputStateData.ConfigurationHeld = in_key_pressed(IN_KEY_SCANCODE_CAPS) && in_key_pressed(IN_KEY_SCANCODE_1);
	_inputStateData.ShowFullScreenImageHeld = in_key_pressed(IN_KEY_SCANCODE_SPACE);
	_inputStateData.UpHeld = in_key_pressed(IN_KEY_SCANCODE_7);
	_inputStateData.DownHeld = in_key_pressed(IN_KEY_SCANCODE_6);
	_inputStateData.LeftHeld = in_key_pressed(IN_KEY_SCANCODE_5);
	_inputStateData.RightHeld = in_key_pressed(IN_KEY_SCANCODE_8);
}

void InputGetInput()
{
	InputUpdateInputHeldFrameCount();
	InputSample();
}

void InputUpdateInputHeldFrameCount()
{
	if (in_test_key() == 0)
	{
		_inputHeldFrameCount = 0;
	}
	else
	{
		InputGetUppercaseASCIIInput(); // have to call this just after in_test_key check above, otherwise can miss alphanumeric keystrokes

		if (_inputHeldFrameCount < 65535)
		{
			++_inputHeldFrameCount;
		}
	}
}