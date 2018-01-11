all: basic_server.c client.c
	gcc -o server basic_server.c pipe_networking.c
	gcc -o client client.c pipe_networking.c
clean:
	rm server
	rm client
	rm *~