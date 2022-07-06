all: main.c stack.c double_stack.c
	gcc -c main.c stack.c double_stack.c
	gcc -o ../build/graph main.o stack.o double_stack.o
	rm main.o stack.o double_stack.o
clean: main.o stack.o double_stack.o
	rm main.o stack.o double_stack.o ../build/graph
rebuild: clean all
