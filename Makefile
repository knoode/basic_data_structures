CFLAGS=-O2 -Wall

all: linked_list hashmap
linked_list: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -o $@ $<
hashmap: hashmap.c hashmap.h
	$(CC) $(CFLAGS) -o $@ $<
clean:
	find -type f -executable -delete
