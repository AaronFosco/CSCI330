#  _______________________________________________________________
# /                                                               \
#||  Course: CSCI-330      Assignment #: 7    Semester: Fall2017  ||
#||                                                               ||
#||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 3          ||
#||                                                               ||
#||  TA's Name: May Myo Khine                                     ||
#||                                                               ||
#||  Due: Friday 12/8/2017 by 11:59PM                             ||
#||                                                               ||
#||  Description:                                                 ||
#||    This is the makefile for the basic webserver. It will      ||
#||    make object files and link them, as well as provide a      ||
#||    command for cleaning all of the objects and executables    ||
# \_______________________________________________________________/

# Compiler variables
CCFLAGS = -Wall -std=c++11

# Rule to link object code files to create executable file
assign7: assign7.o servio.o
	g++ $(CCFLAGS) -o assign7 assign7.o servio.o

# Rules to compile source code file to object code
assign7.o: assign7.cpp servio.h
	g++ $(CCFLAGS) -c assign7.cpp

servio.o: servio.cpp servio.h
	g++ $(CCFLAGS) -c servio.cpp

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o assign7
