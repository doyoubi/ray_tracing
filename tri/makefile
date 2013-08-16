test.exe : test.o tri.o ../exception/exception.o
	g++ -o test.exe test.o tri.o ../exception/exception.o

test.o : test.cpp
	g++ -c -o test.o test.cpp

tri.o : tri.cpp
	g++ -c -o tri.o tri.cpp

clean :
	rm -rf test.exe *.o

test :
	make
	./test.exe
	make clean
