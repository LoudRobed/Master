#generateAgentPosition.c
all: constructActivityMap.c 
	gcc -Wall -pedantic -ansi -march=native -O2 -pipe -fomit-frame-pointer -finline-functions -finline-functions-called-once -fno-strict-aliasing -lm -lnetpbm -o constructActivityMap constructActivityMap.c
# gcc -Wall -pedantic -ansi -march=native -O2 -pipe -fomit-frame-pointer -finline-functions -finline-functions-called-once -fno-strict-aliasing -lm -lnetpbm -o generateAgentPosition generateAgentPosition.c

clean:
	rm -f *.pgm *.o

