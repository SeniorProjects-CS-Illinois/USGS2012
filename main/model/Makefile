all: main.c
	g++ -B /usr/lib/x86_64-linux-gnu -g -Wall -o rivermodel main.c -lm

nogui: main.c
	g++ -D NO_GUI -B /usr/lib/x86_64-linux-gnu -g -Wall -o rivermodel main.c -lm

clean:
	rm -f *.o rivermodel
