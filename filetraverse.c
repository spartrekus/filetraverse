
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
#include <stdio.h>
#define PATH_MAX 2500
#if defined(__linux__) //linux
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__) 
#define MYOS 4  // freebsd
#define PATH_MAX 2500
#else
#define MYOS 0
#endif
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <time.h>
#include <errno.h>

#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>  
#include <time.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define ESC "\033"
#define home() 			printf(ESC "[H") //Move cursor to the indicated row, column (origin at 1,1)
#define clrscr()		printf(ESC "[2J") //clear the screen, move to (1,1)
#define gotoxy(x,y)		printf(ESC "[%d;%dH", y, x);
#define ansigotoyx(y,x)		printf(ESC "[%d;%dH", y, x);
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

/* 
Set Display Attribute Mode	<ESC>[{attr1};...;{attrn}m
*/
#define resetcolor() printf(ESC "[0m")
#define set_display_attrib(color) 	printf(ESC "[%dm",color)



//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
void filetraverse(char *fn, int indent) 
{
  DIR *dir;
  struct dirent *entry;
  int count;
  char path[PATH_MAX]; /*** EXTRA STORAGE MAY BE NEEDED ***/
  struct stat info;

  //for (count=0; count<indent; count++) 
  //   printf("  ");
  //printf("%s\n", fn);

  if ((dir = opendir(fn)) == NULL)
    perror("opendir() error");
  else 
  {
    while ((entry = readdir(dir)) != NULL) 
    {
      if (entry->d_name[0] != '.') 
      {

        strcpy(path, fn);
        strcat(path, "/");
        strcat(path, entry->d_name);

        if (S_ISDIR(info.st_mode))
        {    
           //  printf("PATH: %s\n",  entry->d_name);
        }
        else
        {
           //printf("FILE:      %s\n", entry->d_name);
           //printf("FILE (fn): %s\n", path );
           printf("%s\n", path );
        }

        if (stat(path, &info) != 0)
          fprintf(stderr, "stat() error on %s: %s\n", path, strerror(errno));


        else if (S_ISDIR(info.st_mode))
            filetraverse(path, indent+1);

      }
    }
    closedir(dir);
  }
}













//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
int main( int argc, char *argv[])
{


    if ( argc >= 2 ) 
      filetraverse( argv[ 1 ], 0 );

    return 0;
}
