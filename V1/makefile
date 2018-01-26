all: basic_server.c basic_client.c play.c
	gcc -o server basic_server.c pipe_networking.c
	gcc -o client basic_client.c pipe_networking.c play.c
clean:
	rm server
	rm client
	rm *~