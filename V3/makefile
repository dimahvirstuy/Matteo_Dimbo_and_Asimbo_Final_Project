socket: sockclient sockserver

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
