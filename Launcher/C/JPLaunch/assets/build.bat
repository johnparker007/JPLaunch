@echo off

set MAIN_C_CLASS_FILENAME=app

@echo on

zcc +zx -vn -SO3 -startup=1 -clib=sdcc_iy --max-allocs-per-node20000 %MAIN_C_CLASS_FILENAME%.c btile.asm -o %MAIN_C_CLASS_FILENAME%

@echo off

set SD_CARD_JPLAUNCH_PATH=C:\Users\John\Desktop\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH
set INSTALLER_SPECTRUM_FILES_PATH=C:\projects\GitRepos\JPLaunch\Installer\UnityProject\JPLaunch\Assets\_App\SpectrumFiles

set APP_CODE_BIN_TARGET_NAME=jplaunch
set APP_NIRVANAP_23_ROWS_BIN_TARGET_NAME=nirvana
set APP_NIRVANAP_7_ROWS_BIN_TARGET_NAME=nirvana7




copy app_CODE.bin %SD_CARD_JPLAUNCH_PATH%\code\%APP_CODE_BIN_TARGET_NAME%
copy app_CODE.bin %INSTALLER_SPECTRUM_FILES_PATH%\app_CODE_bin\app_CODE.bytes


REM *** TODO copy all below installer spectrum files to the new subdirectory per file, with the .bytes extension


REM copy app_NIRVANAP_23_ROWS.bin %SD_CARD_JPLAUNCH_PATH%\code\%APP_NIRVANAP_23_ROWS_BIN_TARGET_NAME%
REM copy app_NIRVANAP_23_ROWS.bin %INSTALLER_SPECTRUM_FILES_PATH%\%APP_NIRVANAP_23_ROWS_BIN_TARGET_NAME%

REM copy app_NIRVANAP_7_ROWS.bin C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\%APP_NIRVANAP_7_ROWS_BIN_TARGET_NAME%
REM copy app_NIRVANAP_7_ROWS.bin %INSTALLER_SPECTRUM_FILES_PATH%\%APP_NIRVANAP_7_ROWS_BIN_TARGET_NAME%

REM copy ld16384_recompiled C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\jpl16384
REM copy ld16384_recompiled %INSTALLER_SPECTRUM_FILES_PATH%\ld16384_recompiled

REM copy chdir C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\chdir
REM copy chdir %INSTALLER_SPECTRUM_FILES_PATH%\chdir

REM copy bsave C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\bsave
REM copy bsave %INSTALLER_SPECTRUM_FILES_PATH%\bsave

REM copy ibm_font.chr C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\graphics\8x8font
REM copy ibm_font.chr %INSTALLER_SPECTRUM_FILES_PATH%\ibm_font.chr

REM copy mini.fzx C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\graphics\propfont
REM copy mini.fzx %INSTALLER_SPECTRUM_FILES_PATH%\mini.fzx

REM LD25000
REM LD43000





@echo Finished!