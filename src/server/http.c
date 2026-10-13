#include "http.h"

// typedef struct {
//  char method[10];
//  char path[256];
//  char protocol[16];
// } Request;


int parseRequest(char buffer[], Request *request) {
  
  //initialize poiters at the end of the method, path, and protocol
  char *method = strchr(buffer, ' ');
  if (method == NULL) {
    fprintf(stderr, "Method is null");
    return(-1);
  }
  char *path = strchr(method+1, ' ');
  if (path == NULL) {
    fprintf(stderr, "Path is null");
    return(-1);
  }
  char *protocol = strchr(path+1, '\r'); //search for the beginning of the \r\n at end of line
  if (protocol == NULL) {
   fprintf(stderr, "Protocol is null"); 
    return(-1);
  }

  //subtract the pointers from the end and beginning of each part of the request
  size_t methodSize = method - buffer;
  size_t pathSize = path - (method+1);
  size_t protocolSize = protocol - (path+1);

  if (methodSize >= sizeof(request->method) ||
      pathSize >= sizeof(request->path) ||
      protocolSize >= sizeof(request->protocol)) {
    fprintf(stderr,"Request is too big\n");
    return(-1);
  }
  //copy into request struct and add null terminator on the end of each string
  memcpy(request->method, buffer, methodSize);
  request->method[methodSize] = '\0';
  memcpy(request->path, (method+1), pathSize);
  request->path[pathSize] = '\0';
  memcpy(request->protocol, (path+1), protocolSize);
  request->protocol[protocolSize] = '\0';

  return(0);
}

