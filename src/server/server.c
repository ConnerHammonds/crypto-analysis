#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

//Note since I always forget
//the * operator indicates a pointer
//the & operator indicates an address
//that means int x = *ptr assigns the value at ptr to x
//int ptr = &x assigns ptr the memory address of x (not the value)

/*
  struct addrinfo {
               int              ai_flags;
               int              ai_family;
               int              ai_socktype;
               int              ai_protocol;
               socklen_t        ai_addrlen;
               struct sockaddr *ai_addr;
               char            *ai_canonname;
               struct addrinfo *ai_next;
            };
*/


int main(int argc, char *argv[])
{
  int status;

  struct addrinfo hints;
  struct addrinfo *servinfo; // pointer to results

  

  memset(&hints, 0, sizeof hints); // initializes every byte in hints with 0
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  // getaddrinfo returns an integer. nonzero codes indicate an error so this checks for that
  // Note: the NULL parameter defaults to the localhost IP but a specific IP can be set if desired
  // servinfo is filled in with the server information after the call.
  // getaddrinfo expects a pointer to a pointer which is why the & operator is there
  status = getaddrinfo(NULL, "3490", &hints, &servinfo)
  if (status != 0) {
    fprintf(stderr, "gai error: %s\n", gai_strerror(status));
    exit(1);
  }

  // create socket
  // pass in the address family (IPv4 or IPv6), socket type (stream or datagram), and protocol (tcp for stream, and udp for datagram)
  socketfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  if (socketfd == -1) {
    printf("Error creating socket");
  }

  // bind to port (free addrinfo after)
  bind(socketfd, servinfo->ai_addr, servinfo->ai_addrlen);
  // free memory. Use freeaddrinfo() because it knows that servinfo is a linked list
  // and will free the memory recursively
  // no longer need servinfo
  freeaddrinfo(servinfo);

  // listen for connections
  // pass in the socket file descriptor, and the maximum backlog of connection requests
  listen(socketfd, 5);

  // RESUME WORK HERE
  // accept connections
  accept();

  // start main loop
  
  // close socket after done
}

