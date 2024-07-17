CFLAGS=-O2 -Wall

all: linked_list hashmap
linked_list: linked_list.c
	$(CC) $(CFLAGS) -o $@ $<
hashmap: hashmap.c
	$(CC) $(CFLAGS) -o $@ $<
clean:
	find -type f -executable -delete
