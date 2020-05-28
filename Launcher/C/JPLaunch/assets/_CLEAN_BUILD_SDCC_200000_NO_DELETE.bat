@echo off


REM ***************************** COMPILE SDCC (smaller tap, slower compile)
REM zcc +zx -vn -SO3 -startup=1 -clib=sdcc_iy --max-allocs-per-node200000 %MAIN_C_CLASS_FILENAME%.c btile.asm -o %MAIN_C_CLASS_FILENAME%


REM ***************************** COMPILE SCCZ80 (larger tap, faster compile)
REM zcc +zx -vn -startup=1 -clib=new %MAIN_C_CLASS_FILENAME%.c btile.asm -o %MAIN_C_CLASS_FILENAME%


set MAIN_C_CLASS_FILENAME=app
set TAP_FILENAME=jetpack_joyride
set CHARACTER_GRAPHICS_FILENAME=database


@echo on

zcc +zx -vn -SO3 -startup=1 -clib=sdcc_iy --max-allocs-per-node200000 %MAIN_C_CLASS_FILENAME%.c btile.asm -o %MAIN_C_CLASS_FILENAME%

@echo off

appmake +zx -b %MAIN_C_CLASS_FILENAME%_CODE.bin -o %MAIN_C_CLASS_FILENAME%.tap --noloader --org 32768 --blockname %MAIN_C_CLASS_FILENAME%
copy /B loader.tap+%MAIN_C_CLASS_FILENAME%.tap %TAP_FILENAME%.tap

appmake +zx -b %CHARACTER_GRAPHICS_FILENAME%.chr -o %CHARACTER_GRAPHICS_FILENAME%.tap --noloader --org 54275 --blockname %CHARACTER_GRAPHICS_FILENAME%
copy /B %TAP_FILENAME%.tap+%CHARACTER_GRAPHICS_FILENAME%.tap %TAP_FILENAME%.tap

del %MAIN_C_CLASS_FILENAME%
del %MAIN_C_CLASS_FILENAME%.tap
del %MAIN_C_CLASS_FILENAME%_CODE.bin
del zcc_proj.lst
del zcc_opt.def

