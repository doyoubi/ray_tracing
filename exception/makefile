test.exe : test.o exception.o
	g++ -o test.exe test.o exception.o
test.o : test.cpp
	g++ -c -o test.o test.cpp
exception.o : exception.cpp
	g++ -c -o exception.o exception.cpp

clean : 
	rm -rf test.exe test.o exception.o
