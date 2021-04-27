tree_lib: main.o input.o traversal.o comparator.o
	gcc comparator.c main.o input.o traversal.o -o tree_lib
comparator.o: comparator.c node.h
	gcc -g -c comparator.c 
main.o:main.c node.h
	gcc -g -c main.c
input.o:input.c node.h
	gcc -g -c input.c 
traversal.o:traversal.c node.h
	gcc -g -c traversal.c
clean:
	rm main.o traversal.o input.o comparator.o tree_lib