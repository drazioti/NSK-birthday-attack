#CC is the compiler used.
CC =  g++
#LIBS used from the compiler.
LIBS =  -lgmpxx -lgmp -lcrypto
LIBS_PAR =  -fopenmp -D_GLIBCXX_PARALLEL
#CFLAGS passed to the compiler.
#-fomit-frame-pointer flag does not help much
CFLAGS =  -std=c++11 -c -O3 $(LIBS) $(LIBS_PAR)
#Names of main objects
OBJ_ONE_ATTACK = main.o
OBJ_MULTIPLE_ATTACKS= main2.o
# Names of all objects exept main
OBJS_NO_MAIN =  Utilities.o Combinations.o Ns.o
# Names of executables
EXECUTABLE_ONE_ATTACK = attack.out
EXECUTABLE_MULTIPLE_ATTACKS = multy.out
# Names for all files of certain type
CPP_FILES     = $(wildcard *.cpp)
OBJ_FILES     = $(wildcard *.o)
#clean does not work with wildcard when .o files are not compiled
#thats why I use .o on clean_obj

# Makefile commands start here
all:  one clean_obj
	@echo "Build ns attack executable"

all2:  multy clean_obj
	@echo "Build repeated ns attacks executable"

allpar:  one_par clean_obj
	@echo "Build ns parallel attack executable"

all2par:  multy_par clean_obj
	@echo "Build repeated ns parallel attacks executable"
	
one: $(OBJ_ONE_ATTACK) $(OBJS_NO_MAIN)
	$(CC) $(LIBS) $(OBJ_ONE_ATTACK) $(OBJS_NO_MAIN) -o $(EXECUTABLE_ONE_ATTACK)

multy: $(OBJ_MULTIPLE_ATTACKS) $(OBJS_NO_MAIN)
	$(CC) $(LIBS) $(OBJ_MULTIPLE_ATTACKS) $(OBJS_NO_MAIN) -o $(EXECUTABLE_MULTIPLE_ATTACKS)

one_par: $(OBJ_ONE_ATTACK) $(OBJS_NO_MAIN)
	$(CC) $(LIBS) $(LIBS_PAR) $(OBJ_ONE_ATTACK) $(OBJS_NO_MAIN) -o $(EXECUTABLE_ONE_ATTACK)

multy_par: $(OBJ_MULTIPLE_ATTACKS) $(OBJS_NO_MAIN)
	$(CC) $(LIBS) $(LIBS_PAR) $(OBJ_MULTIPLE_ATTACKS) $(OBJS_NO_MAIN) -o $(EXECUTABLE_MULTIPLE_ATTACKS)
	
main.o:  main.cpp
	$(CC) $(CFLAGS) main.cpp

main2.o:  main2.cpp
	$(CC) $(CFLAGS) main2.cpp

Utilities.o:  Utilities.cpp
	$(CC) $(CFLAGS) Utilities.cpp

Combinations.o:  Combinations.cpp
	$(CC) $(CFLAGS) Combinations.cpp

Ns.o:  Ns.cpp
	$(CC) $(CFLAGS) Ns.cpp

clean: clean_obj
	rm -f $(EXECUTABLE_ONE_ATTACK)
	rm -f $(EXECUTABLE_MULTIPLE_ATTACKS)
	@echo "Cleanned dir of executables"

clean_obj:
	rm -f *.o
	@echo "Cleanned dir of objs"

show_vars:
	@echo -e CC : '\t\t\t\t'					$(CC)
	@echo -e LIBS : '\t\t\t\t'					$(LIBS)
	@echo -e LIBS_PAR : '\t\t\t\t'					$(LIBS_PAR)
	@echo -e CFLAGS : '\t\t\t'					$(CFLAGS)
	@echo -e OBJS_NO_MAIN : '\t\t\t'			$(OBJS_NO_MAIN)
	@echo -e CPP_FILES : '\t\t\t'				$(CPP_FILES)
	@echo -e OBJ_FILES : '\t\t\t'				$(OBJ_FILES)
	@echo -e EXECUTABLE_ONE_ATTACK : '\t'		$(EXECUTABLE_ONE_ATTACK)
	@echo -e EXECUTABLE_MULTIPLE_ATTACKS : '\t'	$(EXECUTABLE_MULTIPLE_ATTACKS)

help:
	@echo -e Makefile commands
	@echo -e all : '\t\t' Builds the attack executable, cleans objs
	@echo -e all2 : '\t\t' Builds the repeated ns attacks executable, cleans objs
	@echo -e one : '\t\t' Builds the attack executable
	@echo -e main.o : '\t' Build main obj
	@echo -e main2.o : '\t' Builds main2 obj
	@echo -e Utilities.o : '\t' Build Utilities obj
	@echo -e Combinations.o : Builds Combinations obj
	@echo -e Ns.o : '\t\t' Ns main obj
	@echo -e clean : '\t' Cleans dir of objs, and executables
	@echo -e clean_obj : '\t' Cleans dir of objs
	@echo -e show_vars : '\t' Shows makefile variables
# Makefile commands end here

