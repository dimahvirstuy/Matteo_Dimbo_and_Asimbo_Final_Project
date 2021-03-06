socket: sockclient sockserver

pipes: basic_server.c basic_client.c play.c
	gcc -o server basic_server.c pipe_networking.c
	gcc -o client basic_client.c pipe_networking.c play.c

sockserver: socket_server.o networking.o
	gcc -o server socket_server.o networking.o


sockclient: socket_client.o networking.o play.o
	gcc -o client socket_client.o networking.o play.o

client.o: socket_client.c networking.h heads.h
	gcc -c socket_client.c 

play.o: play.c
	gcc -c play.c

forking_server.o: socket_server.c networking.h
	gcc -c socket_server.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm server
	rm client
	rm *.o
	rm *~
