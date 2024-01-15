CC=g++ 
CCFLAGS=-Wall -Wextra -Wold-style-cast -Werror -Weffc++
INC=-Iinclude
LIN=
DEF=
STD=-std=c++17

src=src/main.cc 
exe=test.exe
prexe=aoeu.exe

all: com 

dbg: dbgc 

prod: $(src) 
	rm -f $(prexe) 
	$(CC) $(CCFLAGS) -o$(prexe) $(src) $(INC) $(LIN) $(DEF) $(STD) -O3

com: $(src)
	rm -f $(exe)
	$(CC) $(CCFLAGS) -o$(exe) $(src) $(INC) $(LIN) $(DEF) $(STD)

dbgc: $(src) 
	rm -f $(exe)
	$(CC) $(CCFLAGS) -o$(exe) $(src) $(INC) $(LIN) $(DEF) $(STD) -g3 

run: $(exe)
	./$(exe)

dbgr: $(exe)
	gdb $(exe)

clear: 
	rm -rf build/*