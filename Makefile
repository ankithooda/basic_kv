server:
	gcc -Wall ./src/server.c -o ./bin/server -lzmq 
	./bin/server

client:
	gcc -Wall ./src/client.c -o ./bin/client -lzmq 
	./bin/client