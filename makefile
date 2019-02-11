all:
	gcc -std=gnu11 server.c methods.c -lpthread -g -o server
	gcc -std=gnu11 client.c methods.c -g -o client
