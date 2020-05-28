rem copy /B "source_taps\manicminer.tap"+"source_taps\treasureisland.tap" output.tap

@rem Create BASIC loader
cd basic_loader
call compile.bat 
cd..


@rem Generate output.tap file

copy /B "basic_loader\loader.tap" launcher.tap
