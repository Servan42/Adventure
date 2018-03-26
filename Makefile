EXE= Adventure
FLAGS= -Wall -g

all : $(EXE)

Adventure : main.o fight.o display_fight.o
	gcc -o Adventure main.o fight.o display_fight.o -lm

main.o : main.c main.h fight.h global.h
	gcc $(FLAGS) -c main.c main.h fight.h global.h

fight.o : fight.c fight.h global.h display_fight.h
	gcc $(FLAGS) -c fight.c fight.h global.h display_fight.h

display_fight.o : display_fight.c display_fight.h fight.h global.h
	gcc $(FLAGS) -c display_fight.c display_fight.h fight.h global.h

clean : 
	rm -f -v *.o *.gch