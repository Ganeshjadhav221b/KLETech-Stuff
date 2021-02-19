#include <stdio.h>
//#include <sys/resource.h>
#include "stdio.h"
#include "unistd.h"
void main()
{
        printf("MAX CHILD ID IS :%ld\n",sysconf(_SC_CHILD_MAX));
}
