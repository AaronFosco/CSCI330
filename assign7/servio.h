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
||     This is contains the function prototypes needed for the   ||
||     basic web server.                                         ||
 \_______________________________________________________________/
*/

#ifndef SERVIO_H
#define SERVIO_H

void sendFile(char*, int);
void chomp(char*);
bool inExsist(const char*);
bool isFile(const char*);

#endif
