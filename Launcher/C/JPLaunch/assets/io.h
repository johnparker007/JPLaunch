#ifndef __IO_H__
#define __IO




void IOLoadBytes(void * pathString, unsigned char pathStringLength, unsigned int startAddress);
void IOSaveBytes(void * pathString, unsigned char pathStringLength, unsigned int startAddress, unsigned int byteCount);

void IOChangeDirectory(void * pathString, unsigned char pathStringLength);

void IOFakeScreenLoadDelay();


#endif
