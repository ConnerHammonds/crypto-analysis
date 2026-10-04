#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
  int status;

  // this is the struct that contains the parameters I am looking for.
  // I set some of the values for the struct below according to the kind of address I am looking for
  struct addrinfo hints;
  struct addrinfo *servinfo; // pointer to results

  memset(&hints, 0, sizeof hints); // initializes every byte in hints with 0
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  // check for status error
  if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
    fprintf(stderr, "gai error: %s\n", gai_strerror(status));
    exit(1);
  }

  // free memory. Use freeaddrinfo() because it knows that servinfo is a linked list
  // and will free the memory recursively
  freeaddrinfo(servinfo);
}

