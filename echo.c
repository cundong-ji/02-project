#ifndef lint
static const char rcsid[] = "$Id: echo.c,v 1.5 1999/07/28 00:29:37 roberts Exp $";
#endif /* not lint */

#include "fcgi_config.h"

#include <stdlib.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef _WIN32
#include <process.h>
#else
extern char **environ;
#endif

#include "fcgi_stdio.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
char* memstr(char* full_data, int full_data_len, char* substr)  
{  
    if (full_data == NULL || full_data_len <= 0 || substr == NULL) {  
        return NULL;  
    }  
  
    if (*substr == '\0') {  
        return NULL;  
    }  
  
    int sublen = strlen(substr);  
  
    int i;  
    char* cur = full_data;  
    int last_possible = full_data_len - sublen + 1;  
    for (i = 0; i < last_possible; i++) {  
        if (*cur == *substr) {  
            //assert(full_data_len - i >= sublen);  
            if (memcmp(cur, substr, sublen) == 0) {  
                //found  
                return cur;  
            }  
        }  
        cur++;  
    }  
  
    return NULL;  
}
static void PrintEnv(char *label, char **envp)
{
	printf("%s:<br>\n<pre>\n", label);
	for ( ; *envp != NULL; envp++) {
		printf("%s\n", *envp);
	}
	printf("</pre><p>\n");
}

int main ()
{
	char **initialEnv = environ;
	int count = 0;
	char* file_buf = NULL;
	char boundary[256] = {0};
	char content_text[256] = {0};
	char filename[256] = {0};
	while (FCGI_Accept() >= 0) {
		char *contentLength = getenv("CONTENT_LENGTH");
		int len;
		FILE* fp = fopen("./1.txt", "w");
		if(fp == NULL)
		{
			printf("fopen err");
		}
		printf("Content-type: text/html\r\n"
				"\r\n"
				"<title>FastCGI echo</title>"
				"<h1>FastCGI echo</h1>\n"
				"Request number %d,  Process ID: %d<p>\n", ++count, getpid());

		if (contentLength != NULL) {
			len = strtol(contentLength, NULL, 10);
		}
		else {
			len = 0;
		}

		if (len <= 0) {
			printf("No data from standard input.<p>\n");
		}
		else {
			int i, ch;
			char* temp = (char*)malloc(len);
			char* begin = NULL;
			char* end = NULL;
			char* p = NULL;
			char* q = NULL;
			char* k = NULL;
			begin = temp;

			if(NULL == temp)
			{
				printf("malloc err\n");
				return 0;
			}
			printf("Standard input:<br>\n<pre>\n");
			for (i = 0; i < len; i++) {
				if ((ch = getchar()) < 0) {
					printf("Error: Not enough bytes received on standard input<p>\n");
					break;
				}

				*temp = ch;
				temp++;
				putchar(ch);
			} 
			end = p;
			p = begin;
			p = strstr(begin, "\r\n");
			if(NULL == p)
			{
				printf("boundary err!\n");
				goto END;
			}
			strncpy(boundary, begin, p-begin);
			boundary[p-begin] = '\0';
			p+=2;
			len -= (p - begin);
			begin = p;
			
			p = strstr(begin, "\r\n");
			if(NULL == p)	
			{
				printf("context err!\n");
				goto END;
			}
			strncpy(content_text, begin, p-begin);
			content_text[p-begin] = '\0';
			p += 2;
			len -= (p-begin);
			
			q = begin;
			q = strstr(begin, "filename=");
			q += strlen("filename=");
			q++;

			k = strchr(q, '"');
			strncpy(filename, q, k-q);
			filename[k-q] = '\0';
			
			begin = p;
			p = strstr(begin, "\r\n");
			p += 4;
			len -= (p-begin);
			begin = p;

			p = memstr(begin, len, boundary);
			if(NULL == p)
			{
				p = end - 2;
			}
			else
			{
				p = p - 2;
			}
			int fd = open(filename, O_CREAT | O_WRONLY, 0644);
			if(fd < 0)
			{
				printf("open err\n");
			}
			ftruncate(fd, (p-begin));
			write(fd, begin, (p-begin));
			close(fd);
END:
			memset(boundary, 0, 256);
			memset(content_text, 0, 256);
			memset(filename, 0, 256);
		}

		//PrintEnv("Request environment", environ);
		//PrintEnv("Initial environment", initialEnv);
	} /* while */
	return 0;
}
