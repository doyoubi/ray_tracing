test.exe : paper_layer.cpp test_main.cpp paper_layer.h main.cpp screen_manager.cpp primitive.hpp
	g++ -std=c++0x -o test.exe paper_layer.cpp main.cpp screen_manager.cpp -lGL -lglut -lGLU 

clean :
	rm test.exe

run:
	LIBGL_ALLWAYS_INDIRECT=1 ./test.exe
