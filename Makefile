tree_lib: main.o input.o traversal.o
	gcc main.o input.o traversal.o -o tree_lib
main.o:main.c node.h
	gcc -g -c main.c
input.o:input.c node.h
	gcc -g -c input.c 
traversal.o:traversal.c node.h
	gcc -g -c traversal.c
clean:
	rm main.o traversal.o input.o tree_lib