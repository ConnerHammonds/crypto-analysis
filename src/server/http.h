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

// accepts a request buffer and writes to the struct that the pointer points to
int parseRequest(char buffer[], Request *request);
int sendResponse();

#endif // end if
