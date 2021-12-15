CXX      = g++ -std=c++17
CXXFLAGS = -g  -Wall -Werror -pedantic-errors -fmessage-length=0

main: main.o uci.o board.o movegen.o
	$(CXX) $(CXXFLAGS) -o main main.o uci.o board.o movegen.o

main.o: main.cpp uci.h board.h movegen.h
	$(CXX) $(CXXFLAGS) -c main.cpp

uci.o: uci.h

board.o: board.h

movegen.o: movegen.h

clean:
	rm *.o main
