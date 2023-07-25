#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#define KV_GET_COMMAND "GET"
#define KV_SET_COMMAND "SET"

/*
  Only Two commands are allowed
  -> SET <KEY> <VALUE>
  -> GET
  Len of KV Commands       -> 3
  Two Space Characters     -> 2
  Size of Key              -> 100
  Size of Value            -> 100
*/
#define KV_COMMAND_BUFFER_SIZE 205

int main (void)
{

    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);


    char buffer [KV_COMMAND_BUFFER_SIZE];
    int z = zmq_recv (responder, buffer, KV_COMMAND_BUFFER_SIZE, 0);

    
    printf ("Bytes %d - Received - %s\n", z, buffer);
    sleep (1);          //  Do some 'work'
    zmq_send (responder, buffer, KV_COMMAND_BUFFER_SIZE, 0);

    return 0;
}