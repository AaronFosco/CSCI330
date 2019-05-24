#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
//test
using namespace std;

int main()
{
   int pipefd[2], rs;
   pid_t parent = getpid();
   pipe(pipefd);
   
   pid_t pid = fork();
   if (pid > 0) // parent
   {
      int status;
      waitpid(pid, &status, '\0');
   } else if (pid == 0) //child
   {
      execlp("ls", "ls", "-l", '\0');
      cout << "incorrect command!";
      exit(1);
   }
   
   return 0;
}
