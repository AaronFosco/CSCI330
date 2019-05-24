/*
  _______________________________________________________________
 /                                                               \
||  Course: CSCI-330      Assignment #: 4    Semester: Fall2017  ||
||                                                               ||
||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 3          ||
||                                                               ||
||  TA's Name: TA May Myo Khine                                  ||
||                                                               ||
||  Due: Monday, 10/30/17 by 11:59PM                             ||
||                                                               ||
||  Description:                                                 ||
||                                                               ||
||     This program will take commands from the user and attempt ||
||     to pipe the input of the first command into the second,   ||
||     the second into the third, and so on, for up to five      ||
||     commands. The program will loop until "quit" is used as   ||
||     one of the commands.                                      ||
||     WHAT WORKS: strtok, two commands                          ||
||     WHAT DOESN'T: More than two commands, commands after an   ||
||     error has occured, too many commands in a single run (?)  ||
||     COMMAND USED TO COMPILE:                                  ||
||     g++ -Wall -std=c++11 assign4.cpp -o as4out                ||
 \_______________________________________________________________/
*/

#include <iostream>
#include <cstring>
#include <climits>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;

void runcoms(char * coms[], int count, int fd[]);

/*
Funciton: main

Use: excutes the program, runs a loop to read user input and 
     split it into 5 diffrent commands.

Parameters: None

Returns: 0 
*/

int main()
{  

   //can hold 127 * 5 (+ 1 for null char)
   char hold[636];
   
   //pointers to commands
   char * comansp[5];
   
   int count;
   bool quit = false;
   int fd[2];
   
   while (quit == false)
   {
      // reset counter
      count = 0;
      
      //read user input
      cout << "Please enter two to five commands to be piped,"
           << " or \"quit\" to quit: \n";
      cin.getline(hold, 636);
      
      //split commands
      comansp[count] = strtok(hold," |");
      while (((comansp[count] != nullptr) && (count < 5)))
      {
         count++;
	 comansp[count] = strtok(NULL," |\n");
      }
      
      //function to fork, pipe, exec everything
      runcoms(comansp, count, fd);
      
      //test to see if "quit" appeared in commands
      quit = (strcmp(hold, "quit") != 0)? false : true;
   }
   return 0;
}

/*
Funciton: runcoms

Use: runs the commands based on how many there was.

Parameters: 1) coms: an array of pointers to the commands
            2) count: how many commands there are
	    3) fd[]: the file discriptor array used in pipe
	    4) fdhold: a placeholder for file descriptors

Returns: Nothing
*/

void runcoms(char * coms[], int count, int fd[])
{
   int fdhold = -1;
   
   //starting pipe
   pipe(fd);
      
   for (int i = 0; i < count; ++i)
   {
      
      pid_t pid = fork();
      if (pid > 0) // we are parent
      {
         int status;
	 
	 //closes fd[1] since waitpid will not end without doing so
         close(fd[1]);
	 
	 //closes fdhold (pipe output (read) file descriptor)
         close(fdhold);
	 
	 //waits for the child process to end
         waitpid(pid, &status, 0);
	 
	 //holds pipe output (read) file descriptor
         fdhold = fd[0];
	 
	 //new pipe since fd[1] had to be closed in parent
         pipe(fd);
	    
      } else if (pid == 0) // we are child
      {
         if (i == 0) // first argument
         {
	    //first argument, no need for stdin
	    close(0);
	    
	    //copy pipe write to stdout
	    dup2(fd[1], 1);
	    
	    //close uneeded pipes
	    close(fd[0]);
	    close(fd[1]);
	    
	    //exec with exit if it fails
	    execlp(coms[i], coms[i], '\0');
	    cout << "not a command!";
	    exit(1);
	 } else if (i < count-1) //not first command, not last
	 {
	    //nothing is going to be written to stdin, nor stdout
	    //closing each fd
	    close(0);
	    close(1);
	    
	    //fdhold was the old pipe output(read)
	    //so it is used as the input here
	    dup2(fdhold, 0);
	    
	    //copy pipe write to stdout
	    dup2(fd[1], 1);
	    
	    //close uneeded/old pipes
	    close(fd[1]);
	    close(fd[0]);
	    close(fdhold);
	    
	    //exec with exit if it fails
	    execlp(coms[i], coms[i], '\0');
	    cout << "not a command!";
	    exit(1);
	 } else //last command, fd 1 is needed for writing to stdout
	 {
	    //fdhold was the old pipe output(read)
	    //so it is used as the input here
	    dup2(fdhold, 0);
	    
	    //close old/uneeded pipes
	    close(fd[1]);
	    close(fd[0]);
	    close(fdhold);
	    
	    //exec with exit if it fails
	    execlp(coms[i], coms[i], '\0');
	    cout << "not a command!";
	    exit(1);
	 }
      } else //failue to fork
      {
	 exit(1);
      }
   }
   
   //cleanup just incase...
   close(fd[0]);
   close(fd[1]);
   close(fdhold);
}
