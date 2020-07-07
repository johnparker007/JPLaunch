#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM

#define kInputHeldRepeatStartFrameCountUpDown (240)
#define kInputHeldRepeatStartFrameCountLeftRight (215)


struct InputState
{
	_Bool BackHeld;
	_Bool SelectHeld;
	_Bool ViewModeToggleHeld;
	_Bool ConfigurationHeld;
	_Bool ShowFullScreenImageHeld;
	_Bool UpHeld;
	_Bool DownHeld;
	_Bool LeftHeld;
	_Bool RightHeld;
};


_Bool InputBlockedAwaitingKeyUp();
_Bool InputHeldFrameCountIsOneOrRepeating();
void InputGetUppercaseASCIIInput();
void InputSample();
void InputGetInput();
void InputUpdateInputHeldFrameCount();


_Bool _inputWaitForNoInput;
struct InputState _inputStateData;
unsigned char _inputASCIIInput;
unsigned int _inputHeldFrameCount;



#endif
