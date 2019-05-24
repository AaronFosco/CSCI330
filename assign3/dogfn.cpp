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
||   This file contains the struct prototype for dogflags and    ||
||   the classes functions required for each command passes      ||
||                                                               ||
 \_______________________________________________________________/
 */

#include <iostream>
#include <unistd.h>
#include "dogfn.h"
using namespace std;

dogflags::dogflags()
{
   buffch = false;
   bytech = false;
   cipher = false;
   rotat = false;
   hexch = false;
}

/*
Function: newprint

Use: Prints the contents of the file descriptor that was passed
     to it. if there were any command line arguments to be used,
     an if statement would handle it by using the dogflags passed
     to it

Parameters: 
            1) filed: this is a previously opened file discriptor
	    2) df: this is a struct type that holds information 
	           from the command line that will change the 
		   output of the file or change how it is read

Returns: nothing
*/

void newprint(int filed, dogflags &df)
{
      long int buffsize = (df.buffch == true)? 
      (long int) df.buffsize:512;
      ssize_t ammountr;
      char inpBuffer[buffsize];
      
      if (df.bytech == true)
      {
        //code for changing how many bytes to read
      } else if (df.hexch == true)
      {
         hexch(filed);
      } else
      {
         //inizalization of the ammountr variable
	 // & filling of inpBuffer
         ammountr = read(filed, inpBuffer, buffsize);
         write(1, inpBuffer, ammountr);
      
         while (((int)ammountr) >= buffsize)
         {
            ammountr = read(filed, inpBuffer, buffsize);
  	    write(1, inpBuffer, ammountr);
          }
      }

}

/*
Function: hexselect

Use: converts an int into a hex character

Parameters: 
            convr: the intgr to convert

Returns: the converted hex character (was going to make it return             two but couldn't figure that out either)
*/

char hexselect(int convr)
{
   char rval[2];
   if (convr == 0)
      rval[0] = '0';
   else if (convr == 1)
      rval[0] = '1';
   else if (convr == 2)
      rval[0] = '2';
   else if (convr == 3)
      rval[0] = '3';
   else if (convr == 4)
      rval[0] = '4';
   else if (convr == 5)
      rval[0] = '5';
   else if (convr == 6)
      rval[0] = '6';
   else if (convr == 7)
      rval[0] = '7';
   else if (convr == 8)
      rval[0] = '8';
   else if (convr == 9)
      rval[0] = '9';
   else if (convr == 10)
      rval[0] = 'A';
   else if (convr == 11)
      rval[0] = 'B';
   else if (convr == 12)
      rval[0] = 'C';
   else if (convr == 13)
      rval[0] = 'D';
   else if (convr == 14)
      rval[0] = 'E';
   else if (convr == 15)
      rval[0] = 'F';
   return rval[0];
}

/*
Function: hexch

Use: changes the input from a file into hex

Parameters: 
            filed: a file descriptor

Returns: nothing
*/

void hexch(int filed)
{

   int buffsize = 512;
   ssize_t ammountr;
   char hold;
   int inp1;
   char inpBuffer[buffsize];
   char outpBuffer[buffsize*2];
   
   ammountr = read(filed, inpBuffer, buffsize);
   
   //for loop to convert every char in inpBuffer to a hex
   //and then place it into outpBuffer
   for (int i = 0; i < buffsize; i += 2)
   {
      cout << inpBuffer[i] << endl;
      inp1 = (inpBuffer[i]);
      cout << inp1;
      hold = hexselect(inp1);
      outpBuffer[i] = hold;
      outpBuffer[i+1] = hold;
   }
   
   write(1, outpBuffer, (ammountr*2));
      
   //contiunes what was done above if there is still more 
   //data to be read
   while (((int)ammountr) >= buffsize)
   {
      ammountr = read(filed, inpBuffer, buffsize);
         for (int i = 0; i < buffsize; i += 2)
         {
	    cout << inpBuffer[i] << endl;
            inp1 = (inpBuffer[i]);
            cout << inp1;
            hold = hexselect(inp1);
            outpBuffer[i] = hold;
            outpBuffer[i+1] = hold;
         }
      write(1, outpBuffer, (ammountr*2));
   }
}

/*
Function: rotat

Use: 

Parameters: 
            filed: file discriptor

Returns: nothing
*/

void rotat(int filed)
{


}

/*
Function: cipher

Use: 

Parameters: 
            filed: file discriptor

Returns: nothing
*/

void cipher(int filed)
{


}
