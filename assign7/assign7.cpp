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
||     This is a basic web server written in c++. Since the      ||
||     socket closes after listing the directory or the contents ||
||     of a file to the client, a web browser will show an error ||
||     saying connection was reset.                              ||
 \_______________________________________________________________/
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "servio.h"

using namespace std;

//main routine
int main(int argc, char **argv)
{

   //check for all arguments, if not show usage
   if (argc != 3)
   {
      cerr << "Invalid command!\nUsage: portnumber directory\n";
      exit(1);
   }
   
   
   DIR * gdir;
   int succh;
   int newsockfd;
   char buffer[256];
   socklen_t serverlen = sizeof(sockaddr_in);
   socklen_t clientlen = sizeof(sockaddr_in);
   ssize_t received;
   char * comansp[2];
   char * webDir = argv[2];
   
   
   //create a new socket and check to see if it failed
   int sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
   {
      cerr << "Failed to create socket";
      exit(1);
   }
   
   struct sockaddr_in server;
   struct sockaddr_in client;
   
   //set default values for the server
   memset(&server, 0, sizeof(server));
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = htons(atoi(argv[1]));
   
   serverlen = sizeof(server);
   
   //bind the socket and check if the bind failed
   succh = bind(sockfd, (struct sockaddr*) &server, serverlen);
   if (succh < 0)
   {
      cerr << "binding failed!\n";
      exit(1);
   }
   
   //listen on a socket, and check if the listen failed
   succh = listen(sockfd, 128);
   if (succh < 0)
   {
      cerr << "listen failed!\n";
      exit(1);
   }
   
   
   clientlen = sizeof(client);
   
   //run until it breaks
   while (true)
   {
      //except new oncomming connections
      newsockfd = accept(sockfd, (struct sockaddr*) &client, &clientlen);
      
      //check to see if the connection failed
      if (newsockfd < 0)
      {
          cerr << "Accept Failed!";
	  exit(1);
      }
      
      
      //Split connections to allow parent to accept new requests
      //Child will handle the requests
      if (fork()) //we are parent
      {
      
         close(newsockfd);
	 
      } else //we are child
      {
         //read what was read and check to see if the read failed
         received = read(newsockfd, buffer, 256);
         if (received < 0)
         {
            cerr << "failed to get message!\n";
	    exit(1);
         }
	 
	 cout << buffer;
         //check to see if "GET" was recived as a command
         comansp[0] = strtok(buffer, " ");
         if (strcmp(comansp[0], "GET") == 0)
         {
            comansp[1] = strtok(NULL, " \n");
	    
	    //check to see if msg began with a '/'
	    if (comansp[1][0] != '/')
	    {
	       char errorMsg[] = "GET Request must begin with an '/'!\n";
	       write(newsockfd, errorMsg, strlen(errorMsg));
	       exit(1);
	    }
	    
	    //check to see if msg contained '..'
	    if (strstr(comansp[1], "..") != NULL)
	    {
	       char errorMsg[] = "GET Request cannot contain \"..\"\n";
	       write(newsockfd, errorMsg, strlen(errorMsg));
	       exit (1);
	    }
	    
	    
	    chomp(comansp[1]);
	    strcat(webDir, comansp[1]);
	    
	    //check if the last character in the path is a '/'
	    if (webDir[strlen(webDir)-1] != '/')
	    {
	       //double check to see if the path is a file
	       if (isFile(webDir))
	       {
	          sendFile(webDir, newsockfd);
	          close(newsockfd);
	          exit(1);
	       }
	    } else //path refers to a directory
	    {
	       char indexPath[128];
	       char indexName[] = "index.html";
	       strcpy(indexPath, webDir);
	       strcat(indexPath, indexName);
	       chomp(indexPath);
	       
	       //check to see if the directory contains 'index.html'
	       if (inExsist(indexPath))
	       {
	          sendFile(indexPath, newsockfd);
		  sleep(10);
	          close(newsockfd);
	          exit(1);
	       }
	    }
	    
	    //attempt to open requested directory
	    gdir = opendir((const char*) webDir);
	    if (gdir == NULL)
	    {
	       char errorMsg[] = "File or directory doesn't exsist!\n";
	       write(newsockfd, errorMsg, strlen(errorMsg));
	       exit(1);
	    } 
	    
            struct dirent* thedir;
	    
	    //redirect everything that would be outputted on to cout
	    //and output it to the client
            if (dup2(newsockfd, 1) < 0)
	    {
	       cerr << "Socket dup2 failed!";
	       exit(1);
	    }
	    
	    //read the contents of a directory and print the name
	    //of each file/directory
	    while ((thedir = readdir(gdir)) != NULL)
	    {
	       if (thedir->d_name[0] != '.')
	       {
	          cout << thedir->d_name << endl;
	       }
	    }
	 
	 } else //request didn't start with 'GET'
	 {
	    char errorMsg[] = "Any request must start with 'GET'!\n";
	    write(newsockfd, errorMsg, strlen(errorMsg));
	 }
	 
         close(newsockfd);
	 exit(1);
      }
      
      //Null out the buffer so strlen doesn't misinterpet how
      //full it is
      memset(buffer, 0, sizeof(buffer));
   }
   
   
  close(sockfd);
   return 0;
}
