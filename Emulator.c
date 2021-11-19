#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <conio.h>
#include <windows.h>
#include <fileapi.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h> 
#include <sys/stat.h>

/*void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}*/

void getTime()
{
  time_t raw;
  struct tm * info;
  time ( &raw );
  info = localtime ( &raw );
  printf ( "%s", asctime (info) );
}

char colortranslate(char* code)
{
	if (strncmp("black",code, 3) >= 0)
		return '0';
	else if (strncmp("blue",code, 3) >= 0)
		return '1';
	else if (strncmp("green",code, 3) >= 0)
		return '2';
	else if (strncmp("red",code, 3) >= 0)
		return '4';
	else if (strncmp("purple",code, 3) >= 0)
		return '5';
	else if (strncmp("yellow",code, 3) >= 0)
		return '6';
	else if (strncmp("white",code, 3) >= 0)
		return '7';
	else if (strncmp("gray",code, 3) >= 0)
		return '8';
}

void printcolor(char* bg, char* fg)
{
	char a, b, color[10];
	a = colortranslate(bg);
	b = colortranslate(fg);
	strcpy(color,"color ");
	//printf("\ncolors %c %c\n",a ,b );
	color[6]=a;
	color[7]=b;
	color[8]='\0';
	//printf("\ninput: %s\n", color);
	system(color);		
}

void printDir (){
  DIR *d;
  FILE *fp;
  struct dirent *dir;
  struct stat fStat;
  int size, start;
  
  
  d = opendir(".");
  if (d) {
  	dir = readdir(d);
  	dir = readdir(d);
    while ((dir = readdir(d)) != NULL) {
      printf("Filename: %s\n", dir->d_name);
    	stat(dir->d_name,&fStat);
		fp = fopen( dir->d_name, "rw" );
    	
    	if( fp == NULL )
        	printf( "Opening file error\n" );
		
		
    	else{
		
    		start = ftell(fp);
    		fseek (fp, 0, SEEK_END);
    		size = ftell(fp);
    		fseek (fp, start, SEEK_SET);
    		fclose(fp);
			printf( "File Size: %d bytes\n", size );
			
			printf("Created On: %s\n", ctime(&fStat.st_ctime));
		}
    	
    }
    closedir(d);
  }
}

void findFile(char * name)
{
  FILE *fp;
  struct stat fStat;
  int size, start;	
  //printf("Fname: %s", name);
  fp = fopen( name, "rw" );
  stat(name,&fStat);
  
  if( fp == NULL )
    printf( "ERROR FILE DOES NOT EXIST\n" );
		
		
  else{
  	
	printf("Filename: %s\n", "Time.c");		
    start = ftell(fp);
    
	fseek (fp, 0, SEEK_END);
    size = ftell(fp);
    fseek (fp, start, SEEK_SET);
    
    fclose(fp);
	printf( "File Size: %d bytes\n", size );
			
	printf("Created On: %s\n", ctime(&fStat.st_ctime));
	}
    	
}

void printWorkingDir()
{
	char wd[250];
	getcwd(wd, sizeof(wd));
	printf("%s\n\n", wd);
}

void * marquee(void * arg)
{
	//printf("\n");
	int i, max=0, min=80;
	while(1){
	
	sleep(1);
	printf("\r");
	if(max>80)
	{
		max = 0;
		min = 80;
		
	}
	for(i=0;i<max;i++){
		printf(" ");
	}
	printf("%s",(char*)arg);
	for(i=0;i<min;i++){
		printf(" ");
	}
	//printf("\n");
	max++;
	min--;
	}
}

int main()
{
	char cmd[100], exit[6], say[4], cls[5], dir[5], pwd[4], time[5], title[7], color[6], mkfldr[7], find[5], open[5], copy[5], rename[7], delete[7], sort[5], marquee[8];
	char * token1;
	
	//done
	strcpy (exit, "exit");
	exit[4]='\n';
	exit[5]='\0';
	
	//done
	strcpy (say, "say");
	
	//done
	strcpy (cls, "cls");
	cls[3]='\n';
	cls[4]='\0';
	
	//done
	strcpy (dir, "dir");
	dir[3]='\n';
	dir[4]='\0';
	
	//done
	strcpy (pwd, "pwd");
	pwd[3]='\n';
	pwd[4]='\0';
	
	//done
	strcpy (time, "time");
	time[4]='\n';
	time[5]='\0';
	
	//done
	strcpy (title, "title");
	
	//done
	strcpy (color, "color");
	
	//
	strcpy (mkfldr, "mkfldr");
	
	//done
	strcpy (find, "find");
	
	//
	strcpy (open, "open");
	
	//
	strcpy (copy, "copy");
	
	//
	strcpy (rename, "rename");
	
	//
	strcpy (delete, "delete");
	
	//
	strcpy (sort, "sort");
	
	//
	strcpy (marquee, "marquee");
	
	while(1)
	{
		
		printf("MyOS >");
		fgets(cmd, 99, stdin);
		
		token1 = strtok(cmd," ");
		//printf("%s",token1);
		if(strcmp(exit, token1)==0)
		{
				break;
		}
		else if(strcmp (token1, cls)==0)
		{
				system("cls");	
		}
		
		else if(strcmp (token1, say)==0)
		{
			token1 = strtok(NULL, "");
			printf("%s \n",token1);
		}
		
		else if(strcmp (token1, title)==0)
		{
			token1 = strtok(NULL, "");
			SetConsoleTitle(token1);
			printf("\n");
		}
		
		else if(strcmp (token1, time)==0)
		{
			getTime();
		}
		
		else if(strcmp (token1, dir)==0)
		{
			printDir();
		}
		
		else if(strcmp (token1, pwd)==0)
		{
			printWorkingDir();
		}
		
		else if(strcmp (token1, find)==0)
		{
			token1 = strtok(NULL, " \n");
			
			findFile(token1);
		}
		
		else if(strcmp (token1, color)==0)
		{
			char bg[20],fg[20];
			token1 = strtok(NULL, " ");
			strcpy(bg,token1);
			token1 = strtok(NULL, " ");
			strcpy(fg,token1);
			//printf("%s %s",bg ,fg);
			printcolor(bg,fg);
		}
		
		else{
			printf("SYNTAX ERROR!\n\n");
		}
		
	}
	
	//pthread_t thread1,thread2;
	//pthread_create(&thread1, NULL, myturn, NULL);
	//pthread_create(&thread2, NULL, yourturn, NULL);
	
	//pthread_create(&thread1, NULL, marquee, "Hello!");
    //pthread_create(&thread1, NULL, marquee, "world!");
	//pthread_join(thread1, NULL);
	//pthread_create(&thread2, NULL, marquee, "hello world");
	//pthread_join(thread1, NULL);
	//pthread_join(thread2, NULL);
	//marquee("Hello World");
    /*printf("HELLO HELLO HELLO HELLO");
	delay(250);
	printf("\rHELLO WORLD");
	printf("\n");*/
	return 0;	
}

