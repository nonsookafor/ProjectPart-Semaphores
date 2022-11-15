#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

void  ClientProcess(int []);

int  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
		 int i;
     pid_t  pid;
		//  int fd,nloop=10,zero=0;
  	 sem_t *mutex;

     ShmID = shmget(IPC_PRIVATE, 1*sizeof(int), IPC_CREAT | 0666);
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }

     ShmPTR = (int *) shmat(ShmID, NULL, 0);
     if (*ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }

		 ShmPTR[0] = 0; //bank account

		 sem_unlink("examplesemaphore");
		 if ((mutex = sem_open("examplesemaphore", O_CREAT, 0644, 1)) == SEM_FAILED) {
				perror("semaphore initilization");
				exit(1);
			}
     
		 pid = fork();
		 while (1) {
			 if (pid > 0) {
				 sem_wait(mutex);
				 sleep(1);
				 int account;
				 int randomNumber = rand() % (5);
				 srand(getpid() + 1233 +i); // ensure different random numbers were chosen
				 sleep(randomNumber);
				 printf("Dear Old Dad: Attempting to Check Balance\n");
				 account = ShmPTR[0];
				 int rando = rand() % (100);
				 srand(getpid() + i + 999);
				 if (rando % 2 == 0) {
					 
					//  printf("%d\n", balance);
					 if (account < 100) {
						 int amount = rand() % (100);
					 	 srand(getpid() + i + 9999); 
						 if (amount %2 == 0) {
							account = account + amount;
						 	printf("Dear old Dad: Deposits $%d / Balance = $%d\n", amount, account);
						 }
						 else {
							 printf("Dear old Dad: Doesn't have any money to give\n");
						 }
						 
					 }
					 else {
						 printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", account);
					 }

				 }
				 else {
					 printf("Dear Old Dad: Last Checking Balance = $%d\n", account);
					 
				 }
				//  printf("Account: %d\n", account);
				 ShmPTR[0] = account;
				 sem_post(mutex);
				 sleep(1);
				//  printf("ShmPTR[0]: %d\n", ShmPTR[0]);
			 }
			 else {
				 sem_wait(mutex);
				 sleep(1);
				 int balance;
				 int account;
				 int randomNumber;
				 randomNumber = rand() % (5);
				 srand(getpid() + i + 99); // ensure different random numbers were chosen
				 sleep(randomNumber);
				 printf("Poor Student: Attempting to Check Balance\n");
				//  printf("Now checking ShmPTR[0]:%d\n", ShmPTR[0]);
				 account = ShmPTR[0];
				 int myrandom = rand() % (100);
				 srand(getpid() + i + 909);
				 if (myrandom %2 != 0) {
					 printf("Poor Student: Last Checking Balance = $%d\n", account);
				 }
				 else {
					int need = rand() % (50);
				 	srand(getpid() + i + 309);
					printf("Poor Student needs $%d\n", need);
					if (need <= account) {
						account = account - need;
						printf("Poor Student: Withdraws $%d / Balance = $%d\n", need, account);
					}
					else {
						printf("Poor Student: Not Enough Cash ($%d)\n", account );
					}
				 }
				 ShmPTR[0] = account;
				 sem_post(mutex);
				 sleep(1);
			 }
			 i ++;
		 }

     printf("Process has detected the completion of its child...\n");
     shmdt((void *) ShmPTR);
     printf("Process has detached its shared memory...\n");
     shmctl(ShmID, IPC_RMID, NULL);
     printf("Process has removed its shared memory...\n");
     printf("Process exits...\n");
     exit(0);
}
