#include <sys/types.h>
#include <dirent.h>
#include <iostream>

using namespace std;

int main()
{
   const char* naem = "/";
   DIR* dirin = opendir(naem);
   struct dirent* sdir;
   while ((sdir = readdir(dirin)) != NULL)
      cout << sdir->d_name << endl;
   return 0;
}
