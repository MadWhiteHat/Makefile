all:
	gcc -DNDEBUG -Wall -g -o elfloader.out elf_loader.c main.c wheelc/list.c -ldl \
		-lpthread -lm

clean:
	rm -rf *.o wheelc/*.o elfloader

