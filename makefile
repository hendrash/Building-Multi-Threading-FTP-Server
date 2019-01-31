all:
	gcc server.c -g -o server
	gcc -std=gnu11 client.c -g -o client
