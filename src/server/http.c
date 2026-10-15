#include "http.h"

static const Route routes[] = {
  //get home page
  {
    .request = {
      .method = "GET", 
      .path = "/",
      .protocol = "HTTP/1.1" 
    },

    .handler = handle_home
  },

  //get account info
  {
    .request = {
      .method = "GET",
      .path = "/account",
      .protocol = "HTTP/1.1"
    },
  
    .handler = handle_account
  }

};

// typedef struct {
//  char method[10];
//  char path[256];
//  char protocol[16];
// } Request;

//passes in a request that is initialized but not filled
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

//passes in the same request after being filled by parseRequest()
void routeResponse(Request *request) {
  
  for (int i = 0; i < (sizeof(routes) - sizeof(routes[0]); i++) {
    break;
  }
  //find the request in the routes table
  //call the function associated with it
  
  //return error 404 if not in routing table

}

//Handler functions from here down
Response handle_home() {
  return(0);
}

Response handle_account() {
  return(0);
}
