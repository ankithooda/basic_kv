cc = gcc
cflags = -Wall
ldflags = -lzmq
bindir = ./bin
srcdir = ./src
serversrc =  $(srcdir)/server.c
clientsrc = $(srcdir)/client.c
serverbin = server
clientbin = client

$(serverbin): $(serversrc)
	$(cc) $(cflags) $^ -o $(bindir)/$@ $(ldflags)
	$(bindir)/$@

$(clientbin): $(clientsrc)
	$(cc) $(cflags) $^ -o $(bindir)/$@ $(ldflags)
	$(bindir)/$@


.PHONY: clean

clean:
	rm -f $(bindir)/$(serverbin) $(bindir)/$(clientbin)
