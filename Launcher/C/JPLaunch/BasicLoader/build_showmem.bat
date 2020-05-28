@rem Create BASIC loader
cd basic_loader
call compile_showmem.bat 
cd..


@rem Generate output.tap file

copy /B "basic_loader\showmem.tap" showmem.tap
