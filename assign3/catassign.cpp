/*
  _______________________________________________________________
 /                                                               \
||  Course: CSCI-330      Assignment #: 2    Semester: Fall2017  ||
||                                                               ||
||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 3          ||
||                                                               ||
||  TA's Name: TA May Myo Khine                                  ||
||                                                               ||
||  Due: Friday 9/29/2017 by 11:59PM                             ||
||                                                               ||
||  Description:                                                 ||
||                                                               ||
||     This Program will open files based on given parameters    ||
||     passed into the program at the time of excution. It will  ||
||     then print out everyting inside of the given file into    ||
||     cout.                                                     ||
 \_______________________________________________________________/
*/

#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>

using namespace std;
/*
Funciton: main

Use: excutes the program

Parameters: 
            1) argc: Number of parameters passed into the program
	    2) argv: an array of pointers to characters that hold 
	             the commands passed into the program

Returns: 0 if successful, 1 if open failed
*/
int main(int argc, char * argv[])
{
   int fd;
   ssize_t ammountr;
   char inpBuffer[512];
   
   //loop to run thru every file passed into the program
   for(int i = 1; i < argc; i++)
   {
      //open file & check if the open failed
      fd = open(argv[i], O_RDWR);
      if(fd == -1)
      {
         cerr << "FILE CANNOT BE OPENED!" << endl;
	 exit(1);
      }
      //inizalization of the ammountr variable, filling of inpBuffer
      ammountr = read(fd, inpBuffer, 512);
      
      //loop to print contents of inpBuffer
      for (int j = 0; ((int)ammountr) > j; j++)
      {
         cout << ((inpBuffer[j] !=0)?inpBuffer[j]:' ');
      }
      
      /*loop to check if no more data is read.
      * If there is still data to be read, it will continue 
      * through the file.
      */
      while (((int)ammountr) >= 512)
      {
         ammountr = read(fd, inpBuffer, 512);
         for (int j = 0; ((int)ammountr) > j; j++)
         {
            cout << ((inpBuffer[j] !=0)?inpBuffer[j]:' ');
         }
      }
      
      //close each file discriptor after the file is done reading
      close(fd);
   }
   
   return 0;
}
