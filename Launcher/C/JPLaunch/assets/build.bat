@echo off

set MAIN_C_CLASS_FILENAME=app

@echo on

zcc +zx -vn -SO3 -startup=1 -clib=sdcc_iy --max-allocs-per-node20000 %MAIN_C_CLASS_FILENAME%.c btile.asm -o %MAIN_C_CLASS_FILENAME%

@echo off

copy app_CODE.bin C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\jplaunch
copy app_NIRVANAP_23_ROWS.bin C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\nirvana
copy app_NIRVANAP_7_ROWS.bin C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\nirvana7

copy ld16384_recompiled C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\jpl16384
copy chdir C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\chdir
copy bsave C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\bsave

copy ibm_font.chr C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\graphics\8x8font
copy mini.fzx C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\graphics\propfont

@echo Finished!