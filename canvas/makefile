run.exe : main.cpp screen_manager.cpp draw.cpp settings.h screen_manager.h object.h debug.h
	cl /EHsc -Ferun.exe main.cpp screen_manager.cpp draw.cpp /link /LIBPATH:"../lib"

clean :
	del run.exe
