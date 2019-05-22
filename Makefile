cc = gcc
CFLAGS = -std=c11 -Werror -Wall
LDLIBS = -lm -lcurses
OUTPUT = game

all: main
main : main.o ui.o functions.o
	$(cc) ui.o main.o functions.o -o game $(CFLAGS) $(LDLIBS)
ui.o :  ui.c
	cppcheck --enable=performance --error-exitcode=1 ui.c
	$(cc) -c ui.c $(CFLAGS) $(LDLIBS)
functions.o : functions.c
	cppcheck --enable=performance --error-exitcode=1 functions.c
	$(cc) -c functions.c $(CFLAGS) $(LDLIBS)
main.o : main.c
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 main.c
	$(cc) -c main.c $(CFLAGS) $(LDLIBS)
clean:
	rm *o
	rm $(OUTPUT)
