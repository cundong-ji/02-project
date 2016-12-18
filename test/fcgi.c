#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fcgi_stdio.h"


int main(int argc, char* argv[])
{
	int count = 0;
	while(FCGI_Accept() >= 0)
	{
		printf("Content-type: text/html\r\n");
		printf("\r\n");
		printf("<title>Fast CGI Hello!</title>");
		printf("<h1>Fast CGI Hello!</h1>");
		printf("Request number %d running on host <i>%s</i>\n", ++count, getenv("SERVER_NAME"));
		printf("query_string: %s\r\n", getenv("QUERY_STRING"));
		printf("remote addr: %s\r\n", getenv("REMOTE_ADDR"));
		printf("remote port: %s\r\n", getenv("REMOTE_PORT"));
		printf("server addr: %s\r\n", getenv("SERVER_ADDR"));
		printf("server port: %s\r\n", getenv("SERVER_PORT"));
	}
	return 0;
}
