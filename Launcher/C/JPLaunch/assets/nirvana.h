#ifndef __NIRVANA_H__
#define __NIRVANA_H__

unsigned int  _nirvanaRowHeightPatchAddress;

_Bool _nirvanaRestartNextUpdate;


void NirvanaLoadEngine(_Bool rows23);
void NirvanaRowHeightPatchAddressInitialise();
void NirvanaRestartNextUpdate();
void NirvanaStartAndCancelRestartNextUpdate();




#endif
