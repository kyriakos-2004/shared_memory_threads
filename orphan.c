#include <unistd.h>
  
int 
main()
{     
    pid_t pid = fork();
    
    if (pid == 0)
    {
        sleep(30);
    }
  
    return 0;
}
