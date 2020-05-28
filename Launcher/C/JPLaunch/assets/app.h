#ifndef __APP_H__
#define __APP_H__

#define kAppStateFrontend	(0)
#define kAppStateGame		(1)
#define kAppStateGameOver	(2)

#define kRoutineChDirBaseAddress (43500)
#define kRoutineChDirPathOffset (10)
#define kRoutineChDirPathAddress (kRoutineChDirBaseAddress + kRoutineChDirPathOffset)

#define kRoutineBLoadBaseAddress (43000)
#define kRoutineBLoadFilePathOffset (34)
#define kRoutineBLoadAddressHighByteOffset (18)
#define kRoutineBLoadAddressLowByteOffset (17)
#define kRoutineBLoadFilePathAddress (kRoutineBLoadBaseAddress + kRoutineBLoadFilePathOffset)
#define kRoutineBLoadAddressHighByteAddress (kRoutineBLoadBaseAddress + kRoutineBLoadAddressHighByteOffset)
#define kRoutineBLoadAddressLowByteAddress (kRoutineBLoadBaseAddress + kRoutineBLoadAddressLowByteOffset)

#define kRoutineBSaveBaseAddress (44000)
#define kRoutineBSaveFilePathOffset (32)
#define kRoutineBSaveAddressHighByteOffset (17)
#define kRoutineBSaveAddressLowByteOffset (16)
#define kRoutineBSaveByteCountHighByteOffset (20)
#define kRoutineBSaveByteCountLowByteOffset (19)
#define kRoutineBSaveFilePathAddress (kRoutineBSaveBaseAddress + kRoutineBSaveFilePathOffset)
#define kRoutineBSaveAddressHighByteAddress (kRoutineBSaveBaseAddress + kRoutineBSaveAddressHighByteOffset)
#define kRoutineBSaveAddressLowByteAddress (kRoutineBSaveBaseAddress + kRoutineBSaveAddressLowByteOffset)
#define kRoutineBSaveByteCountHighByteAddress (kRoutineBSaveBaseAddress + kRoutineBSaveByteCountHighByteOffset)
#define kRoutineBSaveByteCountLowByteAddress (kRoutineBSaveBaseAddress + kRoutineBSaveByteCountLowByteOffset)


//const unsigned int kFilePathAddress = 43000 + 34;
//
//const unsigned int kHighByteAddress = 43000 + 18;
//const unsigned int kLowByteAddress = 43000 + 17;


unsigned char _appState;

void AppSetState(unsigned char state);

void AppLoadResources();

//void AppLoadNirvanaEngine(_Bool rows23);



#endif
