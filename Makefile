all: server client

server: server.c types.c
	gcc -o server server.c types.c

client: client.c types.c
	gcc -o client client.c types.c