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

Response send404() {
  Response response;

  response.status_code = "404";
  response.status_message = "Not Found";
  response.protocol = "HTTP/1.1";

  return(response);
}
//passes in the same request after being filled by parseRequest()
void routeResponse(Request *request) {
  
  size_t routesLen = sizeof(routes) / sizeof(routes[0]);

  for (int i = 0; i < routesLen; i++) {
    //use strcmp to compare current http request in the routes table to the passed in request
    //if they are equal, call the corresponding handler
    if (strcmp(request->method, routes[i].request.method) == 0 &&
        strcmp(request->path, routes[i].request.path) == 0 &&
        strcmp(request->protocol, routes[i].request.protocol) == 0) {
          routes[i].handler(request);
          return;
    }
  }
  //return error 404 if not in routing table
  send404();
}

//Handler functions from here down
Response handle_home() {
  Response response;

  response.status_code = "200";
  response.status_message = "OK";
  response.protocol = "HTTP/1.1";
  
  return(response);
}

Response handle_account() {
  Response response;

  response.status_code = "200";
  response.status_message = "Account info";
  response.protocol = "HTTP/1.1";
 
  return(response);
}
