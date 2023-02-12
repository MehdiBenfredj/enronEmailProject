main: main.o Worker.o Sender.o
	g++ -std=c++17 -Ofast main.o Worker.o Sender.o -o main

main.o: main.cpp
	g++ -std=c++17 -Ofast -c main.cpp

Worker.o: Worker.cpp	
	g++ -std=c++17 -Ofast -c Worker.cpp 

Sender.o: Sender.cpp
	g++ -std=c++17 -Ofast -c Sender.cpp

clean:
	rm *.o