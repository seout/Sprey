CC=gcc

CFLGS=-c

DELETE=rm -rf conf

build:
	$(CC) -o conf $(CFLGS) conf.c
	$(CC) -o main  main.c conf
	$(DELETE)
	./main
