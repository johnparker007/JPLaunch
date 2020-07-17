#ifndef __SCREENSAVER_H__
#define __SCREENSAVER

#define kScreensaverFrameCount (1000)

#define kScreensaverFrameIndexPaddedMaximumLength	(5)

void ScreensaverInitialise();
void ScreensaverUpdate();
void ScreensaverLoadCurrentFrameScreen();

int _screensaverCurrentFrame;
_Bool _screensaverPositiveSpeed;

#endif
