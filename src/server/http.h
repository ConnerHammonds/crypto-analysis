#ifndef HTTP_H // if this file is not defined
#define HTTP_H // define it

typedef struct {
  char method[10];
  char path[256];
  char protocol[16];
} Request;

typedef struct {
  char protocol[16];
  char status_code[10];
  char status_message[16];
} Response;

// define the handler function type
// Accepts the appropriate http request and sends the appropriate response
// Will be stored in a routing table with the request that it corresponds to
typedef Response (*handlerFunction)(Request *request);

typedef struct {
  Request request;
  handlerFunction handler;
} Route;

// accepts a request buffer and writes to the struct that the pointer points to
int parseRequest(char buffer[], Request *request);
int sendResponse();

#endif // end if
