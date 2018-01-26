# StrategiC
#### Dima Hvirtsman, Asim Kapparova, and Matteo Wong | Period 5

## Project Overview


StrategiC is an implementation of Stratego across either two processes on one computer or two different computers on the same local network. A server runs continuously and waits for two clients to be connected to it. Once two clients are connected to the server, the server connects the clients to each other. From there, the clients set up their boards and play Stratego.

## Basic Description of Internal Code

### Pipe Setup
Server runs in a while(1) loop waiting on open of a well-known pipe. Client A connects, and the server facilitates a 3-way handshake. Client B connects, and the server facilitates a 3-way handshake. The server then sends the PID of client A to  client B. After this point both clients have closed all pipes connecting to the server. Client A makes a pipe with its PID as the name, client B opens it, 3-way handshake ensues.

### Socket Setup
Same as pipe setup but with sockets.

### Gameplay
There are two standard 10x10 int arrays (int [][]). One has pieces and one has the loyalty of pieces. Different stratego pieces have different numerical values which are then translated into a baord by a display_board() function. Each client sets up their board then sends it to the other client. Once both have set up, the game begins. There are two core functions, is_valid_move() and do_move(), which do what their names describe using either boolean statements or chains of if/if else statements. Information is sent over the pipes in strings with the format "x x x x" where x represents integers.


## Instructions

### Setup Instructions

#### Pipes

`$ make pipes` -- compiles for connecting two processes on one machine

`$ ./server` -- runs server. `$^c` to exit server

`$ ./client` -- run twice on two separate terminals. 

exiting

`^c` to exit first client while it is waiting for a second client

`$exit` to exit client while playing game


#### Sockets

`$make` -- compiles for connecting two machines through a server

`$./server` -- makes server

`$./client <IP of server>` -- makes client. run twice on separate terminals. first client will input their IP and server initiates handshake between them
	
can exclude <IP of server> and it will use 127.0.0.1

`^c` to exit first client while it is waiting for a second client

`$exit` to exit client while playing game

### Gameplay Instructions

Sample board: 

-- | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
---|---|---|---|---|---|---|---|---|---|---|
0| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 
1| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 
2| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 
3| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 
4| _ | _ | X | X | _ | _ | X | X | _ | _ | 
5| _ | _ | X | X | _ | _ | X | X | _ | _ | 
6| 9 | 5 | 9 | 7 | 5 | 9 | 9 | 5 | 6 | 9 | 
7| 6 | 4 | 7 | 6 | 8 | 7 | B | 4 | 9 | 6 | 
8| 3 | B | 2 | B | 9 | 8 | 3 | B | S | 8 | 
9| B | F | B | 5 | 8 | 4 | 9 | 1 | 8 | 7 | 



Insert moves in format `$a b c d`. This will be interpreted as move piece at square (a,b) to (c,d), or if you are setting up, swap pieces at the same coordinates.

Pieces go from 1-9. 1 is the strongest, 9 is the weakest. all pieces can only move one square adjacent to them, except the 9, which can move any number of squares horizontally or vertically (like a rook in chess).

The S is a spy, which can kill the 1.

Bombs kill everything except 8, which "defuse" bombs.

Capture the flag(F) to win!

see in-depth Stratego rules here: https://en.wikipedia.org/wiki/Stratego

### Known Bugs

If the first client to connect to the server exits (^c), it does not tell the server and the server doesn't start over.

   We couldn't fix this on the pipe version because the first client waits on open instead of read, so select would not work.
   
   We couldn't fix on the socket version bc it would require putting a select() statement in the server and the server waits while establishing the socket() connection, rather than on read().
   
   Basically this bug means if one client connects and then disconnects before another client joins, the setup doesn't work.
   

Note on commits: Dima has a lot less because some of his commits are under the username DimaHvirStuy and some are dimahvirstuy which are separated and only the lowercase one shows up in the chart