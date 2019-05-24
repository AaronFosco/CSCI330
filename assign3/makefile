#  _______________________________________________________________
# /                                                               \
#||  Course: CSCI-330      Assignment #: 3    Semester: Fall2017  ||
#||                                                               ||
#||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 3          ||
#||                                                               ||
#||  TA's Name: May Myo Khine                                     ||
#||                                                               ||
#||  Due: Wednesday 10/11/2017 by 11:59PM                         ||
#||                                                               ||
#||  Description:                                                 ||
#||    This will make the program compile correctly               ||
#||                                                               ||
# \_______________________________________________________________/

# Compiler variables
CCFLAGS = -Wall -std=c++11

# Rule to link object code files to create executable file
dog: dogassign.o dogfn.o
	g++ $(CCFLAGS) -o dog dogassign.o dogfn.o

# Rules to compile source code file to object code
dogassign.o: dogassign.cpp dogfn.h
	g++ $(CCFLAGS) -c dogassign.cpp
dogfn.o: dogfn.cpp dogfn.h
	g++ $(CCFLAGS) -c dogfn.cpp


# Pseudo-target to remove object code and executable files
clean:
	-rm *.o dog
