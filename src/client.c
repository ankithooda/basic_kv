#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

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
    printf ("Connecting to hello world server...\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    char client_buffer [KV_COMMAND_BUFFER_SIZE];
    char server_buffer [KV_COMMAND_BUFFER_SIZE];

    scanf("$ %s", &client_buffer);
    zmq_send (requester, client_buffer, KV_COMMAND_BUFFER_SIZE, 0);
    zmq_recv (requester, server_buffer, KV_COMMAND_BUFFER_SIZE, 0);
    printf ("Received response for Request No. %s\n", server_buffer);

    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}