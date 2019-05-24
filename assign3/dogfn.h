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
||   Creates a dogflags structure for holding all of the flags   ||
||   and parameters that are passed into the program             ||
||                                                               ||
 \_______________________________________________________________/
 */

#ifndef DOGFN_H
#define DOGFN_H

/*
struct: dogflags

Use: holds the flags data obtained from command line, this 
     includes the information required to change the buffer
     size, change bytes to read, and information on cipher or
     rotat functions
*/
struct dogflags
{
   bool buffch;
   int buffsize;
   bool bytech;
   int bytes2read;
   bool cipher;
   bool rotat;
   char *shOrRotat = NULL;
   bool hexch;
   dogflags();
};

//function prototypes
void hexch(int);
char hexselect(int);
void byte2r(int);
void buffch(int);
void cipher(int);
void rotat(int);
void newprint(int, dogflags&);
#endif
