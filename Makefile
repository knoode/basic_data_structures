CFLAGS=-O2 -Wall

all: linked_list hashmap queue stack
linked_list: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -o $@ $<
hashmap: hashmap.c hashmap.h
	$(CC) $(CFLAGS) -o $@ $<
queue: queue.c queue.h
	$(CC) $(CFLAGS) -o $@ $<
stack: stack.c stack.h
	$(CC) $(CFLAGS) -o $@ $<
clean:
	find -type f -executable -delete
