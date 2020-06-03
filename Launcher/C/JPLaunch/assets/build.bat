@echo off

set MAIN_C_CLASS_FILENAME=app

@echo on

zcc +zx -vn -SO3 -startup=1 -clib=sdcc_iy --max-allocs-per-node20000 %MAIN_C_CLASS_FILENAME%.c btile.asm -o %MAIN_C_CLASS_FILENAME%

@echo off

set SD_CARD_JPLAUNCH_PATH=C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH
set INSTALLER_SPECTRUM_FILES_PATH=C:\projects\GitRepos\JPLaunch\Installer\UnityProject\JPLaunch\Assets\_App\SpectrumFiles

set APP_CODE_BIN_TARGET_NAME=jplaunch
set APP_NIRVANAP_23_ROWS_BIN_TARGET_NAME=nirvana
set APP_NIRVANAP_7_ROWS_BIN_TARGET_NAME=nirvana7


copy app_CODE.bin %SD_CARD_JPLAUNCH_PATH%\code\%APP_CODE_BIN_TARGET_NAME%
copy app_CODE.bin %INSTALLER_SPECTRUM_FILES_PATH%\%APP_CODE_BIN_TARGET_NAME%

copy app_NIRVANAP_23_ROWS.bin %SD_CARD_JPLAUNCH_PATH%\code\%APP_NIRVANAP_23_ROWS_BIN_TARGET_NAME%
copy app_NIRVANAP_23_ROWS.bin %INSTALLER_SPECTRUM_FILES_PATH%\%APP_NIRVANAP_23_ROWS_BIN_TARGET_NAME%

copy app_NIRVANAP_7_ROWS.bin C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\%APP_NIRVANAP_7_ROWS_BIN_TARGET_NAME%
copy app_NIRVANAP_7_ROWS.bin %INSTALLER_SPECTRUM_FILES_PATH%\%APP_NIRVANAP_7_ROWS_BIN_TARGET_NAME%

copy ld16384_recompiled C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\jpl16384
copy ld16384_recompiled %INSTALLER_SPECTRUM_FILES_PATH%\ld16384_recompiled

copy chdir C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\chdir
copy chdir %INSTALLER_SPECTRUM_FILES_PATH%\chdir

copy bsave C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\code\bsave
copy bsave %INSTALLER_SPECTRUM_FILES_PATH%\bsave

copy ibm_font.chr C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\graphics\8x8font
copy ibm_font.chr %INSTALLER_SPECTRUM_FILES_PATH%\ibm_font.chr

copy mini.fzx C:\Users\John\Desktop\ZEsarUX_win-8.1\_SD_CARD_ROOT_087\JPLAUNCH\graphics\propfont
copy mini.fzx %INSTALLER_SPECTRUM_FILES_PATH%\mini.fzx

LD25000
LD43000





@echo Finished!