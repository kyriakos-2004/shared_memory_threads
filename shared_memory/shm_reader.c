#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>

#define BUF_SIZE 1024
#define SHM_KEY 0x568547

struct shmsegment 
{
   int cnt;
   int opercompleted;
   char buffer[BUF_SIZE];
};

int 
main(int argc, char *argv[]) 
{
   int shmid;
   struct shmsegment *shmp;
   
   shmid = shmget(SHM_KEY, sizeof(struct shmsegment), 0644 | IPC_CREAT);
   if (shmid == -1) 
   {
      perror("Error getting the shared memory segment");
      return 1;
   }
   
   // Attach to shared memory segment to get a pointer to it
   shmp = shmat(shmid, NULL, 0);
   if (shmp == (void *) -1) 
   {
      perror("Error attaching to shared memory");
      return 1;
   }
   
   // Transfer data from shared memory segment to standard output
   while (shmp->opercompleted != 1) 
   {
      printf("Memory segment contains : \n\"%s\"\n", shmp->buffer);
      if (shmp->cnt == -1) 
	  {
         perror("Error reading shared memory segment");
         return 1;
      }
	  
      printf("RP: Read %d bytes from shared memory\n", shmp->cnt);
      sleep(3);
   }
   
   printf("Reading process has been completed\n");
   printf("Detaching from shared memory\n");
   
   if (shmdt(shmp) == -1) 
   {
      perror("Unable to detach from shared memory");
      return 1;
   }
   
   printf("Reading process has been completed\n");
   return 0;
}