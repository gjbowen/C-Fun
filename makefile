
# define a makefile variable for the java & compiler
CC = gcc
run  = ./

default:  compile clear run

# Clear Console
#
clear:
	clear

# Compile c files
#
build:
	$(CC) ./main.c -o main.out
compile:
	 $(CC) ./main.c -o main.out

# Run
#
run: clear
	./main.out program.txt

# Removes all .out files
#
clean: 
	$(RM) *.out *.o
