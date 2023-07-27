server:
	gcc -g -Wall ./src/server.c `pkg-config --cflags --libs glib-2.0` -o ./bin/server -lzmq 
	./bin/server

client:
	gcc -g -Wall ./src/client.c -o ./bin/client -lzmq 
	./bin/client

hm:
	gcc -Wall src/hashmap.c `pkg-config --cflags --libs glib-2.0` -o ./bin/hm
	./bin/hm
