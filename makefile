main: main.o Worker.o Sender.o
	g++ -std=c++17 main.o Worker.o Sender.o -o main

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

Worker.o: Worker.cpp	
	g++ -std=c++17 -c Worker.cpp 

Sender.o: Sender.cpp
	g++ -std=c++17 -c Sender.cpp

clean:
	rm *.o