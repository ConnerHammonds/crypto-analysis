#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

#define PORT "1738"
#define BACKLOG 5

int main(int argc, char *argv[])
{
  int status;
  struct addrinfo hints;
  struct addrinfo *servinfo; // pointer to results
  int listen_sock; // socket that listens for incoming connections
  int conn_sock; // socket that is created on accept() call for communication

  

  memset(&hints, 0, sizeof hints); // initializes every byte in hints with 0
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  // getaddrinfo returns an integer. nonzero codes indicate an error so this checks for that
  // Note: the NULL parameter defaults to the localhost IP but a specific IP can be set if desired
  // servinfo is filled in with the server information after the call.
  // getaddrinfo expects a pointer to a pointer which is why the & operator is there
  status = getaddrinfo(NULL, PORT, &hints, &servinfo);
  if (status != 0) {
    fprintf(stderr, "gai error: %s\n", gai_strerror(status));
    exit(1);
  }

  // create socket
  // pass in the address family (IPv4 or IPv6), socket type (stream or datagram), and protocol (tcp for stream, and udp for datagram)
  listen_sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  if (listen_sock == -1) {
    printf("Error creating socket");
    exit(1);
  }

  // bind to port (free addrinfo after)
  if (bind(listen_sock, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
    printf("Error binding port");
    exit(1);
  }

  // free memory. Use freeaddrinfo() because it knows that servinfo is a linked list
  // and will free the memory recursively
  // no longer need servinfo
  freeaddrinfo(servinfo);

  // pass in the socket file descriptor, and the maximum backlog of connection requests
  if (listen(listen_sock, BACKLOG) == -1) {
    printf("Error listening to port");
    exit(1);
  }

  // pass in the socket file descriptor as well as the incoming connection's
  // address and address length
  // Note that the connection address has to be type cast to sockaddr
  struct sockaddr_storage their_addr;
  socklen_t addrlen = sizeof(their_addr);
  conn_sock = accept(listen_sock,  (struct sockaddr *)&their_addr, &addrlen);
  if (conn_sock == -1) {
    printf("Error accepting connection");
    exit(1);
  }
  
  char prompt[] = "Ask for message 1, 2, or 3 by typing the respective number\n";
  char msg1[] = "This is message 1\n";
  char msg2[] = "This is message 2\n";
  char msg3[] = "This is message 3\n";
  char buffer[100];
  
  while (1) {
  send(conn_sock, prompt, strlen(prompt), 0);
  ssize_t byte_count = recv(conn_sock, buffer, sizeof(buffer) - 1, 0);
  if (byte_count <= 0) {
      printf("No message received");
      break;
    }

  buffer[byte_count] = '\0'; //add null terminator on the end of the message
    
    switch (buffer[0]) {
      case '1':
        send(conn_sock, msg1, strlen(msg1), 0);
        break;
      case '2':
        send(conn_sock, msg2, strlen(msg2), 0);
        break;
      case '3':
        send(conn_sock, msg3, strlen(msg3), 0);
        break;
      case 'q':
        exit(0);
      default:
        printf("invalid input");
    }
  }
  
  close(conn_sock);
}

