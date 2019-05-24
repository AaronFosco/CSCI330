#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
using namespace std;
int main(int argc, char * argv[])
{
   if(argc != 4) 
   {
      cerr << "Usage: echoClient server_ip port message\n";
      exit(EXIT_FAILURE);
   }
   char buffer[256]; 
   int echolen, received = 0;  
   unsigned int addrlen;
   int sock;
   struct sockaddr_in echoserver; // structure for server address
   
   // Create the UDP socket
   if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
   {
      perror("Failed to create socket"); 
      exit(EXIT_FAILURE); 
   }
   
   // Construct the server sockaddr_in structure
   memset(&echoserver, 0, sizeof(echoserver));       // Clear struct
   echoserver.sin_family = AF_INET;                  // Internet IP
   
   //inet_addr converts a string to a computer readable 
   //IP adress
   echoserver.sin_addr.s_addr = inet_addr(argv[1]);  // IP address
   echoserver.sin_port = htons(atoi(argv[2]));       // server port
   
   // Send the message to the server
   echolen = strlen(argv[3]);
   if (sendto(sock, argv[3], strlen(argv[3]), 0, 
   (struct sockaddr *) &echoserver, sizeof(echoserver)) != echolen) 
   {
      perror("Mismatch in number of sent bytes"); 
      exit(EXIT_FAILURE);
   }
   
   // Receive the message back from the server
   addrlen = sizeof(echoserver);
   if ((received = recvfrom(sock, buffer, 256, 0, (struct sockaddr *) &echoserver, &addrlen)) != echolen) 
   {
      perror("Mismatch in number of received bytes"); 
      exit(EXIT_FAILURE); 
   }
   
   buffer[received] = '\0';
   cout << "Message received: " << buffer << endl;
}
