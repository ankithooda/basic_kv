#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "hashmap.c"

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

    /*
      Create server.
    */
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);

    /*
      Create in-memory hashmap
    */
    HashMap store = hm_create();


    /*
      Start receiving commands.
    */
    char buffer [KV_COMMAND_BUFFER_SIZE];
    char* command;
    char* response;
    char* input_key;
    char* input_value;

    while (1) {
      zmq_recv (responder, buffer, KV_COMMAND_BUFFER_SIZE, 0);

      /*
        Parse received commands.
      */
      command = strtok(buffer, " ");

      if (strcmp(command, KV_GET_COMMAND) == 0) {

        input_key = strtok(NULL, " ");
        response = hm_get(store, input_key);

        if (response == NULL) {
          response = "NOT FOUND";
        }

      } else if (strcmp(command, KV_SET_COMMAND) == 0) {

        input_key = strtok(NULL, " ");
        input_value = strtok(NULL, " ");

        hm_set(store, input_key, input_value);
        response = "OK";

      } else {
        response = "UNKNOWN COMMAND";
      }

      // Send response
      zmq_send (responder, response, KV_COMMAND_BUFFER_SIZE, 0);
    }
    return 0;
}