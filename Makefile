# Makefile for ArbitraryPrecisionInteger

FLAGS   = -Wall
SOURCES = apint.c Test.c
OBJECTS = apint.o Test.o
EXEBIN  = Test
all: $(EXEBIN)
$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)
$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)
clean :
	rm -f $(EXEBIN) $(OBJECTS)