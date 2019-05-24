/*
  _______________________________________________________________
 /                                                               \
||  Course: CSCI-330      Assignment #: 7    Semester: Fall2017  ||
||                                                               ||
||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 3          ||
||                                                               ||
||  TA's Name: TA May Myo Khine                                  ||
||                                                               ||
||  Due: Friday, 12/8/17 by 11:59PM                              ||
||                                                               ||
||  Description:                                                 ||
||                                                               ||
||     This is contains the function definitions needed for the  ||
||     basic web server.                                         ||
 \_______________________________________________________________/
*/

#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "servio.h"

/*
Function: sendFile

Use: will send the contents of a requested filename to a set
     file descriptor

Parameters: pName: a requested file name
            fdSock: The file descritor to send the contents of
	            a file to

Returns: Nothing
*/

void sendFile(char* pName, int fdSock)
{
   int openFd;
   char buffer[256];
   ssize_t bytesr;
   char errmsg[] = "File Doesn't exsist!\n";
   
   openFd = open(pName, O_RDWR);
   
   if (openFd < 0)
   {
      write(fdSock, errmsg, strlen(errmsg));
      exit(1);
   }
   
   bytesr = read(openFd, (char*) buffer, 256);
   write(fdSock, buffer, (size_t) bytesr);
   while ((int) bytesr >= 256)
   {
      bytesr = read(openFd, (char*) buffer, 256);
      write(fdSock, buffer, (size_t) bytesr);
   }
}

/*
Function: inExsist

Use: checks if the file with the requested name exsists

parameters: name: the reqested name

Returns: true if the file exsists, false otherwise
*/

bool inExsist(const char* name)
{
   struct stat buffer;
   return (stat(name, &buffer) == 0);
}

/*
Function: isFile

Use: will check to see if the reqested name is the name of a file
     or a directory
     
Parameters: name: the name of a file or directory

Returns: True if it is a file, false otherwise
*/

bool isFile(const char* name)
{
   bool rv = false;
   struct stat buffer;
   stat(name, &buffer);
   if ((buffer.st_mode & S_IFMT) == S_IFREG)
      rv = true;
      
   return rv;
}

/*
Function: chomp

Use: removes leading returns and newlines and replaces them
     with null characters

Parameters: s: a pointer to a string to be manipulated

Returns: nothing
*/

void chomp(char *s) {
for (char *p = s + strlen(s)-1; *p == '\r' || *p == '\n'; p--)
   *p = '\0';
}
