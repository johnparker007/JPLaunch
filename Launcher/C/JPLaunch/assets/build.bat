@echo off


REM ***************************** COMPILE SDCC (smaller tap, slower compile)
REM zcc +zx -vn -SO3 -startup=1 -clib=sdcc_iy --max-allocs-per-node200000 %MAIN_C_CLASS_FILENAME%.c btile.asm -o %MAIN_C_CLASS_FILENAME%


REM ***************************** COMPILE SCCZ80 (larger tap, faster compile)
REM zcc +zx -vn -startup=1 -clib=new %MAIN_C_CLASS_FILENAME%.c btile.asm -o %MAIN_C_CLASS_FILENAME%


set MAIN_C_CLASS_FILENAME=app
set TAP_FILENAME=launcher
set IBM_FONT_FILENAME=ibm_font
set MINI_FONT_FILENAME=mini

set NIRVANA_ENGINE_FILENAME=NIRVANA_ENGINE_23_ROWS_CHAR_ADDR_54275_COMPILED


@echo on

zcc +zx -vn -SO3 -startup=1 -clib=sdcc_iy --max-allocs-per-node20000 %MAIN_C_CLASS_FILENAME%.c btile.asm -o %MAIN_C_CLASS_FILENAME%

@echo off

appmake +zx -b %MAIN_C_CLASS_FILENAME%_CODE.bin -o %MAIN_C_CLASS_FILENAME%.tap --noloader --org 25000 --blockname %MAIN_C_CLASS_FILENAME%

pause

appmake +zx -b %IBM_FONT_FILENAME%.chr -o %IBM_FONT_FILENAME%.tap --noloader --org 52000 --blockname %IBM_FONT_FILENAME%
appmake +zx -b %MINI_FONT_FILENAME%.fzx -o %MINI_FONT_FILENAME%.tap --noloader --org 51000 --blockname %MINI_FONT_FILENAME%

appmake +zx -b %NIRVANA_ENGINE_FILENAME% -o %NIRVANA_ENGINE_FILENAME%.tap --noloader --org 56323 --blockname NIRVANA+

copy /B loader_from_spectrum.tap+%TAP_FILENAME%.tap+%NIRVANA_ENGINE_FILENAME%.tap %TAP_FILENAME%.tap

copy /B %TAP_FILENAME%.tap+%MAIN_C_CLASS_FILENAME%.tap %TAP_FILENAME%.tap

copy /B %TAP_FILENAME%.tap+%IBM_FONT_FILENAME%.tap %TAP_FILENAME%.tap
copy /B %TAP_FILENAME%.tap+%MINI_FONT_FILENAME%.tap %TAP_FILENAME%.tap

REM copy %TAP_FILENAME%.tap C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\%TAP_FILENAME%.tap
copy app_CODE.bin C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\jplaunch

copy app_NIRVANAP_23_ROWS.bin C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\nirvana
copy app_NIRVANAP_7_ROWS.bin C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\nirvana7

copy ld16384_recompiled C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\jpl16384

copy chdir C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\chdir

copy bsave C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\bsave


copy ibm_font.chr C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\graphics\8x8font
copy mini.fzx C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\graphics\propfont




