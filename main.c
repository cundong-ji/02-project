#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "make_log.h"

int main(int argc, char *argv[])
{
	int a = 10;
	int b = 20;
    LOG("111", "222", "nihao");
        LOG("111", "222", "nihuai");
    LOG("111", "222", "nihaohuai");
	return 0;
}
