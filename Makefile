server:
	gcc -Wall ./src/server.c -o ./bin/server -lzmq 
	./bin/server

client:
	gcc -Wall ./src/client.c -o ./bin/client -lzmq 
	./bin/client

hm:
	gcc src/hashmap.c `pkg-config --cflags --libs glib-2.0` -o ./bin/hm
	./bin/hm
