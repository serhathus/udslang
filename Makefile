CXX = g++
CXXFLAGS = -std=c++17

all: tds

tds: parser.tab.o lex.yy.o main.o symbol_table.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lfl

parser.tab.cpp parser.tab.h: parser.y
	bison -d -o parser.tab.cpp parser.y

lex.yy.c: lexer.l parser.tab.h
	flex -o lex.yy.c lexer.l

parser.tab.o: parser.tab.cpp symbol_table.h ast.h
	$(CXX) $(CXXFLAGS) -c parser.tab.cpp

lex.yy.o: lex.yy.c parser.tab.h
	$(CXX) $(CXXFLAGS) -c lex.yy.c

main.o: main.cpp parser.tab.h symbol_table.h ast.h
	$(CXX) $(CXXFLAGS) -c main.cpp

symbol_table.o: symbol_table.cpp symbol_table.h
	$(CXX) $(CXXFLAGS) -c symbol_table.cpp

clean:
	rm -f tds parser.tab.* lex.yy.c *.o

.PHONY: all clean
