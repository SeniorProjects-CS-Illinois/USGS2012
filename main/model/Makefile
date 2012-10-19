all: main.c
	gcc -shared -fPIC -B/usr/lib/x86_64-linux-gnu -I /usr/include/python2.7/ -lpython2.7 -o MainModule.so main.c
	mv MainModule.so ../controller

nogui: main.c
	gcc -D NO_GUI -D NO_PYTHON -B /usr/lib/x86_64-linux-gnu -g -Wall -o rivermodel main.c -lm

clean:
	rm -f *.so
	rm -f ../controller/MainModule.so
