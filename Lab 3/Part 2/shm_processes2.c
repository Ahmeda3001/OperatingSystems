#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

void  PoorStudent(int []);
void  DearOldDad(int []);

int  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;

     ShmID = shmget(IPC_PRIVATE, 2*sizeof(int), IPC_CREAT | 0666);
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     printf("Main has received a shared memory of four integers...\n");

     ShmPTR = (int *) shmat(ShmID, NULL, 0);
     if (*ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     printf("Main has attached the shared memory...\n");

     ShmPTR[0] = 0;  //BankAcc
     ShmPTR[1] = 0;  //Turn
  
     printf("Main has filled BankAcc = %d and Turn = %d in shared memory...\n",
            ShmPTR[0], ShmPTR[1]);

     printf("Main is about to fork a child process...\n");
     pid = fork();
     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
     }
     else if (pid == 0) {
          PoorStudent(ShmPTR);
          exit(0);
     }
     else{
         DearOldDad(ShmPTR);
     }

     wait(&status);
     printf("Main has detected the completion of its child...\n");
     shmdt((void *) ShmPTR);
     printf("Main has detached its shared memory...\n");
     shmctl(ShmID, IPC_RMID, NULL);
     printf("Main has removed its shared memory...\n");
     printf("Main exits...\n");
     exit(0);
}

void  PoorStudent(int  SharedMem[])
{
     int i;
     int account;
     int randVal;
      
     srand(getpid()); // seed the rand num generator
  
     for (i = 0; i < 25; i++){
         //sleep between 0 and 5 seconds
         sleep(rand() % 6);
       
         account = SharedMem[0]; // Set local account to sharedMem account
       
         while(SharedMem[1] != 1); // Do nothing when the turn is set to 0
       
         randVal = rand() % 51; // random generates a num between 0 - 50
         printf("Poor Student needs $%d\n", randVal);
       
         if(randVal <= account){
             account -= randVal;
             
             printf("Poor Student: Withdraws $%d / Balance = $%d\n", randVal, account);
         }
         else {
             printf("Poor Student: Not Enough Cash ($%d)\n", account );
         }
         
         SharedMem[0] = account;
         
         SharedMem[1] = 0;
     } 

}

void  DearOldDad(int  SharedMem[])
{
     int i;
     int account;
     int randVal;
      
     srand(getpid()); // seed the rand num generator
  
     for (i = 0; i < 25; i++){
         //sleep between 0 and 5 seconds
         sleep(rand() % 6);
       
         account = SharedMem[0]; // Set local account to sharedMem account
       
         while(SharedMem[1] != 0); // Do nothing when the turn is set to 0
       
         if(account <= 100){
             //Deposit Money
             
             randVal = rand() % 101; // random generates a num between 0 - 100
           
             if(randVal % 2 == 0){
                 account += randVal;
               
                 printf("Dear old Dad: Deposits $%d / Balance = $%d\n", randVal, account);
             }
             else {
                 printf("Dear old Dad: Doesn't have any money to give\n");
             }
           
             SharedMem[0] = account;        
             
         }
         else {
             printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", account);
         }   
         
         SharedMem[1] = 1;
       
     } 
  
}