CC=gcc

CFLGS=-c -Wall

DELETE=rm -rf conf

build:
	$(CC) -o conf $(CFLGS) conf.c
	$(CC) -o sprey  main.c conf
	$(DELETE)

	#./main -h 1.1.1.1 -p 443 -t 1

