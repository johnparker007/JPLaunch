@rem Create BASIC loader
cd basic_loader
call compile.bat 
cd..


@rem Generate output.tap file

copy /B "basic_loader\loader.tap" loader.tap
rem copy /B "basic_loader\loader.tap"+"raw_esxdos_basic_lines.bin" loader.tap
