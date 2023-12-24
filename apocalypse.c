#include<stdio.h>
#include<unistd.h>
 
int 
main()
{
    int flag = 0;

    while (fork() > 0)
    {
        flag++;
        printf("%d\n", flag);
    }

    return 0;
}
