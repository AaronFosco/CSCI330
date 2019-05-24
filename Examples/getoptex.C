#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
   int opt; 
   bool cflagused = false;
   char optstring[] = "c";
   while ((opt = getopt(argc, argv, optstring)) != -1)
   {
      cout << opt << endl;
      switch(opt)
      {
         case 'c':
	    cflagused = true;
	    break;
      }
   }
   return 0;
}
