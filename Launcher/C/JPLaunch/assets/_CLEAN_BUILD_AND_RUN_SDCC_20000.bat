@echo off


REM ***************************** COMPILE SDCC (smaller tap, slower compile)
REM zcc +zx -vn -SO3 -startup=1 -clib=sdcc_iy --max-allocs-per-node200000 %MAIN_C_CLASS_FILENAME%.c btile.asm -o %MAIN_C_CLASS_FILENAME%


REM ***************************** COMPILE SCCZ80 (larger tap, faster compile)
REM zcc +zx -vn -startup=1 -clib=new %MAIN_C_CLASS_FILENAME%.c btile.asm -o %MAIN_C_CLASS_FILENAME%


set MAIN_C_CLASS_FILENAME=app
set TAP_FILENAME=jetpack_joyride
set CHARACTER_GRAPHICS_FILENAME=characters
set VORTEXTRACKER_FILENAME=vortextrackersave

set NIRVANA_ENGINE_FILENAME=NIRVANA_ENGINE_23_ROWS_CHAR_ADDR_54275_COMPILED


@echo on

zcc +zx -vn -SO3 -startup=1 -clib=sdcc_iy --max-allocs-per-node20000 %MAIN_C_CLASS_FILENAME%.c btile.asm -o %MAIN_C_CLASS_FILENAME%

@echo off



appmake +zx -b %NIRVANA_ENGINE_FILENAME% -o %NIRVANA_ENGINE_FILENAME%.tap --noloader --org 56323 --blockname NIRVANA+
copy /B loader.tap+%TAP_FILENAME%.tap+%NIRVANA_ENGINE_FILENAME%.tap %TAP_FILENAME%.tap

appmake +zx -b %MAIN_C_CLASS_FILENAME%_CODE.bin -o %MAIN_C_CLASS_FILENAME%.tap --noloader --org 32768 --blockname %MAIN_C_CLASS_FILENAME%
copy /B %TAP_FILENAME%.tap+%MAIN_C_CLASS_FILENAME%.tap %TAP_FILENAME%.tap

appmake +zx -b %CHARACTER_GRAPHICS_FILENAME%.chr -o %CHARACTER_GRAPHICS_FILENAME%.tap --noloader --org 54275 --blockname %CHARACTER_GRAPHICS_FILENAME%
copy /B %TAP_FILENAME%.tap+%CHARACTER_GRAPHICS_FILENAME%.tap %TAP_FILENAME%.tap

REM copy /B %TAP_FILENAME%.tap+%VORTEXTRACKER_FILENAME%.tap %TAP_FILENAME%.tap

%TAP_FILENAME%.tap

REM del %TAP_FILENAME%.tap