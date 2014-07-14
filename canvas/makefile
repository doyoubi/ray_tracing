run.exe : main.obj draw.obj screen_manager.obj
	cl /EHsc -Ferun.exe main.obj draw.obj screen_manager.obj freeglut.lib /link /LIBPATH:"../lib"

main.obj : main.cpp screen_manager.h settings.h
	cl /EHsc /Fo /c main.cpp

draw.obj : draw.cpp screen_manager.h object.h settings.h coordinate.h material.h intersect.h
	cl /EHsc /Fo /c draw.cpp

screen_manager.obj : screen_manager.h
	cl /EHsc /Fo /c screen_manager.cpp

#run.exe : main.cpp screen_manager.cpp draw.cpp settings.h screen_manager.h object.h debug.h
#	cl /EHsc -Ferun.exe main.cpp screen_manager.cpp draw.cpp /link /LIBPATH:"../lib"

clean :
	del run.exe
