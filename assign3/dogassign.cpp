/*
  _______________________________________________________________
 /                                                               \
||  Course: CSCI-330      Assignment #: 3    Semester: Fall2017  ||
||                                                               ||
||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 3          ||
||                                                               ||
||  TA's Name: May Myo Khine                                     ||
||                                                               ||
||  Due: Wednesday 10/11/2017 by 11:59PM                         ||
||                                                               ||
||  Description:                                                 ||
||    This is the main routine that runs when the program        ||
||    executes. It will start to use getopt to obtain all the    ||
||    needed flags and store them into the dogflags struct       ||
||    it will then attempt to open the file with a given file    ||
||    name and pass the filedescriptor into the functions        ||
||    listed in dogfn.cpp                                        ||
||                                                               ||
 \_______________________________________________________________/
 */

#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "dogfn.h"
using namespace std;
extern char * optarg;
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
   
   int fd, opt;
   char optstr[] = "bncrx";
   dogflags openfilef;
   
   while ((opt = getopt(argc, argv, optstr)) != -1)
   {
      /* failed attempts in getting optarg to work correctly
       *  every time I tried to obtain the value following the
       *  command, It did not work...
       */
      switch(opt)
      {
         case 'b': // change buff size
	    openfilef.buffch = true;
	    openfilef.buffsize = *optarg;
	    break;
	    
	 case 'n': //change number of bytes read
	    openfilef.bytech = true;
	    openfilef.bytes2read = *optarg; 
	    break;
	    
	 case 'c': // cesar cipher
	    if (openfilef.rotat == true)
	    {
	       cerr << "Cipher cannot be combined with rotate!\n";
	       exit(-1);
	    } else
	    {
	       openfilef.cipher = true;
	       openfilef.shOrRotat = optarg;
	    }
	    break; 
	      
         case 'r': //rotation for data
	    if (openfilef.cipher == true)
	    {
	       cerr << "Rotate cannot be combined with cipher!\n";
	       exit(-1);
	    } else
	    {
	       openfilef.rotat = true;
	       openfilef.shOrRotat = optarg;
	    }
	    break;
	    
	 case 'x': //output data in hex
	    openfilef.hexch = true;
	    break; 
	         
      }
   }

    
   
   //loop to run thru every file passed into the program
   for(int i = optind; i < argc; i++)
   {
      
         //open file & check if the open failed
         fd = open(argv[i], O_RDWR);
         if(fd == -1)
         {
            cerr << "myownfilecannot be opended" << endl;
	    exit(1);
         }
      
         newprint(fd, openfilef); 
      
         //close each file discriptor after the file is done reading
         close(fd);
      
   }
   
   return 0;
}

