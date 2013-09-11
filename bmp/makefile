test.exe : bmp.cpp test.cpp
	g++ -g -o test.exe bmp.cpp test.cpp

clean :
	rm -rf test.exe *.o savetest.bmp

test :
	make
	./test.exe
	make clean
