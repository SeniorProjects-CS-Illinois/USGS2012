
INCLUDE = -I"C:\\Program Files (x86)\\Intel\\OpenCL SDK\\2.0\\include"
LINK = -L"C:\\Program Files (x86)\\Intel\\OpenCL SDK\\2.0\\lib\\x86" 
CC = g++
CFLAGS = -c -Wall -O3

all: RiverModelCL.o
	$(CC) -o cl_test RiverModelCL.o main.cpp $(INCLUDE) $(LINK) -lOpenCL

RiverModelCL.o: RiverModelCL.h RiverModelCL.cpp
	$(CC) $(CFLAGS) RiverModelCL.cpp -o RiverModelCL.o $(INCLUDE) $(LINK)

clean:
	rm -rf *o cl_test
