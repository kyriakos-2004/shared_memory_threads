#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

#define BUF_SIZE 1024
#define SHM_KEY 0x568547

struct shmsegment 
{
   int cnt;
   int opercompleted;
   char buffer[BUF_SIZE];
};

int fill_buffer(char * buffptr, int size);

int 
main(int argc, char *argv[]) 
{
   int shmid, times;
   int availspace;
   struct shmsegment *shmp;
   char *buffptr;
   
   shmid = shmget(SHM_KEY, sizeof(struct shmsegment), 0644 | IPC_CREAT);
   if (shmid == -1) 
   {
      perror("Error creating shared memory");
      return 1;
   }
   
   // Attach to shared memory segment to get a pointer to it
   shmp = shmat(shmid, NULL, 0);
   if (shmp == (void *) -1) 
   {
      perror("Error attaching to shared memory");
      return 1;
   }
   
   // Transfer data from buffer to shared memory
   buffptr = shmp->buffer;
   availspace = BUF_SIZE;
   
   for (times = 0; times < 5; times++) 
   {
      shmp->cnt = fill_buffer(buffptr, availspace);
      shmp->opercompleted = 0;
      
	  printf("WP: Wrote %d bytes in shared memory\n", shmp->cnt);
      buffptr = shmp->buffer;
      availspace = BUF_SIZE;
      
	  sleep(3);
   }
   
   printf("WP: Wrote %d times\n", times);
   shmp->opercompleted = 1;

   if (shmdt(shmp) == -1) 
   {
      perror("Unable to detach from shared memory");
      return 1;
   }

   if (shmctl(shmid, IPC_RMID, 0) == -1) 
   {
      perror("Unable to perform shared memory control operations");
      return 1;
   }
   
   printf("Writting process has been completed\n");
   return 0;
}

int 
fill_buffer(char* buffptr, int size) 
{
   static char c = 'K';
   int fillcount;
   
   memset(buffptr, c, size - 1);
   buffptr[size-1] = '\0';

   if (c > 122)
   {
	c = 65;
   }
   
   if ( (c >= 65) && (c <= 122) ) 
   {
      	if ( (c >= 91) && (c <= 96) ) 
	{
        	c = 65;
      	}
   }
   
   fillcount = strlen(buffptr);
   c++;
   
   return fillcount;
}
