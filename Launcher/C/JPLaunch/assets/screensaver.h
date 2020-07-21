#ifndef __SCREENSAVER_H__
#define __SCREENSAVER

#define kScreensaverFrameCount (1000)

#define kScreensaverFrameIndexPaddedMaximumLength	(5)

#define kScreensaverIdleSecondsBeforeShow	(10)
#define kScreensaverIdleFramesBeforeShow	(kScreensaverIdleSecondsBeforeShow * 50) // * 50 FPS when idle

void ScreensaverInitialise();
void ScreensaverUpdate();
void ScreensaverLoadCurrentFrameScreen();
void ScreensaverExit();

int _screensaverCurrentFrame;
_Bool _screensaverPositiveSpeed;

#endif
