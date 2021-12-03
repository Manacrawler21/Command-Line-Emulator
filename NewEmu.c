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

int cursorPosition;

void getTime()
{
  time_t raw;
  struct tm * info;
  time ( &raw );
  info = localtime ( &raw );
  printf ( "%s\n", asctime (info) );
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
	printf("\n\n");
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
      cursorPosition++;

    	stat(dir->d_name,&fStat);
		fp = fopen( dir->d_name, "rw" );
    	
    	if( fp == NULL )
    	{
        	printf( "Opening file error\n\n" );
        	cursorPosition += 2 ;
    	}
    	else{
		
    		start = ftell(fp);
    		fseek (fp, 0, SEEK_END);
    		size = ftell(fp);
    		fseek (fp, start, SEEK_SET);
    		fclose(fp);
				printf( "File Size: %d bytes\n", size );
				printf("Created On: %s\n", ctime(&fStat.st_ctime));

				cursorPosition += 2;
		}
    	
    }

    printf("\n");
    cursorPosition += 2;
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
    printf( "ERROR FILE DOES NOT EXIST\n\n" );
		
		
  else{
  	
	printf("Filename: %s\n", name);		
    start = ftell(fp);
    
	fseek (fp, 0, SEEK_END);
    size = ftell(fp);
    fseek (fp, start, SEEK_SET);
    
    fclose(fp);
		printf( "File Size: %d bytes\n", size );
				
		printf("Created On: %s\n", ctime(&fStat.st_ctime));
		cursorPosition += 2;
	}
    	
}

void printWorkingDir()
{
	char wd[250];
	getcwd(wd, sizeof(wd));
	printf("%s\n\n", wd);
}

void renameFile(char* old, char* newname)
{
	 FILE * fp = fopen( old, "rw" );
	 if(fp==NULL)
	 {
	 	printf("ERROR FILE NOT FOUND\n\n");
	 }
	 else{
	 	fclose(fp);
	 	rename(old, newname);
	 	printf("\n\n");
	 }
}

deleteFile(char* name)
{
	 FILE * fp = fopen( name, "rw" );
	 if(fp==NULL)
	 {
	 	printf("ERROR FILE NOT FOUND\n\n");
	 }
	 else{
	 	fclose(fp);
	 	remove(name);
	 	printf("\n\n");
	 }
}

void sortCommand(char* filename, int lineCount)
{
	 strcat(filename, ".txt");
	 FILE * fp = fopen( filename, "r" );
	 if(fp==NULL)
	 {
	 	printf("ERROR FILE NOT FOUND\n\n");
	 }
	 else{
	 	
	 	int i, j;
	 	int bufferLength = 255;
	 	char buffer[bufferLength];
	 	char temp[bufferLength];
	 	char c[100][255];

	 	printf("Input: \n");
	 	for (i = 0; i < lineCount; i++)
	 	{
	 		fgets(buffer, bufferLength, fp);
	 		printf("%s", buffer);
	 		strcpy(c[i], buffer);
	 		cursorPosition++;
	 	}
	 	
		fclose(fp);

	 	printf("\nOutput: \n");
	 	for (i = 0; i < lineCount-1; i++)
	 	{
	 		for (j = i+1; j < lineCount; j++)
	 		{
	 			if (strcmp(c[i], c[j]) > 0)
	 			{
	 				strcpy(temp, c[i]);
	 				strcpy(c[i], c[j]);
	 				strcpy(c[j], temp);
	 			}
	 		}
	 	}
		for (i = 0; i < lineCount; i++)
		{
		 		printf("%s", c[i]);
				cursorPosition++;
		}
	 	
	 		
	 }

	 cursorPosition += 2;
}

void openFile (char* textFile)
{
	textFile[strcspn(textFile, "\n")] = 0;
	strcat(textFile, ".txt");
	 FILE * fp = fopen( textFile, "r" );
	 if(fp==NULL)
	 {
	 	printf("ERROR FILE NOT FOUND\n\n");
	 }
	 else
	 {
	 		char ch;
	 	while((ch = fgetc(fp)) != EOF)
	 	{
	 		putchar(ch);

	 		if(ch == '\n') cursorPosition++;
	 	}

	 }

	 cursorPosition++;

	 fclose(fp);
}

void copyCommand (char* sourceFile, char* destFile)
{
	 strcat(sourceFile, ".txt");
	 strcat(destFile, ".txt");
	 FILE * fp = fopen( sourceFile, "r" );
	 FILE * fp2;

	 char c;

	 if(fp==NULL)
	 {
	 	printf("ERROR FILE NOT FOUND\n\n");
	 }
	 else
	 {
	 	fp2 = fopen( destFile, "r" );

	 	if (fp2 == NULL)
	 	{
	 		fclose (fp2);
	 		fp2 = fopen( destFile, "w");
	 		c = fgetc(fp);
	 		while (c != EOF)
	 		{
	 			fputc(c, fp2);
	 			c = fgetc(fp);
	 		}

	 		printf("\n\n");
	 	}
	 	else printf("Destination file already exists.\n");
	 }

	 fclose(fp);
	 fclose(fp2);
}

void * testMarquee(void * text){

	int stringLength;
	int c, loop;

	int barLength = 100;

	stringLength = strlen(text)-1;

	//printf("%d", stringLength);
	
	char subtext[50];
	strcpy(subtext, text);

	HANDLE wHnd;

	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD characterBufferSize = {barLength, 1}; // Should not exceed CHAR_INFO str
	COORD characterPosition = {0,0}; // Starts at leftmost
	SMALL_RECT consoleWriteArea = {0, cursorPosition-2, barLength, cursorPosition-2}; //SYNTAX: 1stparam= x of top left, 2ndparam= y of top left, 3rdparam= x of bottom right, 4thparam=y of bottom right

	CHAR_INFO str[barLength];

	// INITIALIZE LINE
	for (loop = 0; loop < barLength; loop++)
	{
		// Placeholder
		str[loop].Char.AsciiChar = ' ';
		str[loop].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	}

	int count;
	// DRAW
	int lineCounter;

	for (loop = 0; loop < barLength-stringLength ; loop++)
	{
		count = 0;

		str[loop].Char.AsciiChar = ' ';

		for (c = loop+1; c < stringLength+loop+1; c++)
		{
			str[c].Char.AsciiChar = subtext[count];
			str[c].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
			count++;
		}
		
		WriteConsoleOutput(wHnd, str, characterBufferSize, characterPosition, &consoleWriteArea);

		sleep(1);
	}
}

int main()
{
	char cmd[100], exit[6], say[4], cls[5], dir[5], pwd[4], time[5], title[7], color[6], mkfldr[7], find[5], open[5], copy[5], rename[7], delete[7], sort[5], marquee[8];
	char * token1;

	//HANDLE wHnd; /* write (output) handle */

	//SMALL_RECT windowSize = {0, 0, 69, 99};
	//COORD bufferSize = {70, 100};

	/* Set the window size */
  //SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
  //SetConsoleScreenBufferSize(wHnd, bufferSize);

  cursorPosition = 1;	

	system("cls");
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
		printf("[%d] MyOS >", cursorPosition);

		fgets(cmd, 99, stdin);
		
		token1 = strtok(cmd," ");

		if(strcmp(exit, token1)==0)
		{
				break;
		}
		else if(strcmp (token1, cls)==0)
		{
				system("cls");	
				cursorPosition = 1;

				// TODO: What if there is marquee and cls is called
		}
		
		else if(strcmp (token1, say)==0)
		{
			cursorPosition += 3;
			token1 = strtok(NULL, "");
			if (token1==NULL)
				printf("SYNTAX ERROR!\n\n");
			else
				printf("%s \n",token1);
		}
		
		else if(strcmp (token1, mkfldr)==0)
		{
			cursorPosition += 3;
			token1 = strtok(NULL, "\n");
			int check;
			if (token1==NULL)
				printf("SYNTAX ERROR!\n\n");
			else{
				check = mkdir(token1);
				if (!check)
        			printf("DIRECTORY %s HAS BEEN CREATED\n\n", token1);
    			else 
        			printf("UNABLE TO CREATE DIRECTORY\n\n");
			}
		}
		
		else if(strcmp (token1, title)==0)
		{
			cursorPosition += 3;
			token1 = strtok(NULL, "");
			SetConsoleTitle(token1);
			printf("Title has been set.\n\n");
		}
		
		else if(strcmp (token1, time)==0)
		{
			cursorPosition += 3;
			getTime();
		}
		
		else if(strcmp (token1, dir)==0)
		{
			cursorPosition += 5;
			printDir();
		}
		
		else if(strcmp (token1, pwd)==0)
		{
			cursorPosition += 3;
			printWorkingDir();
		}
		
		else if(strcmp (token1, find)==0)
		{
			cursorPosition += 3;
			token1 = strtok(NULL, " \n");
			if(token1!=NULL)	
				findFile(token1);
			else
				printf("SYNTAX ERROR!\n\n");
		}
		
		else if(strcmp (token1, delete)==0)
		{
			cursorPosition += 3;
			token1 = strtok(NULL, " \n");
			if(token1!=NULL)	
				deleteFile(token1);
			else
				printf("SYNTAX ERROR!\n\n");
		}
		
		else if(strcmp (token1, color)==0)
		{
			cursorPosition += 3;
			char bg[20],fg[20];
			token1 = strtok(NULL, " ");
			if(token1==NULL)
				printf("SYNTAX ERROR!\n\n");
			else{
				strcpy(bg,token1);
				token1 = strtok(NULL, " \n");
				if (token1==NULL)
					printf("SYNTAX ERROR!\n\n");
				else
					{
						strcpy(fg,token1);
						printcolor(bg,fg);
					}
				}
		}
		
		else if(strcmp (token1, rename)==0)
		{
			cursorPosition += 3;
			char old[40],newname[40];
			token1 = strtok(NULL, " ");
			if(token1==NULL)
				printf("SYNTAX ERROR!\n\n");
			else{
			
				strcpy(old,token1);
				token1 = strtok(NULL, " \n");
				if(token1==NULL)
					printf("SYNTAX ERROR!\n\n");
				else{
					strcpy(newname,token1);
				
					renameFile(old,newname);
				}
			}
		}
		
		// TODO : Configure cursorPosition for this
		else if(strcmp (token1, sort)==0)
		{
			char filename[20],numLines[4];
			token1 = strtok(NULL, " ");
			if(token1==NULL)
				printf("SYNTAX ERROR!\n\n");
			else{
				strcpy(filename,token1);
				token1 = strtok(NULL, " \n");
				if (token1==NULL)
					printf("SYNTAX ERROR!\n\n");
				else
					{
						strcpy(numLines,token1);
						int lineCount = atoi(numLines);
						sortCommand(filename,lineCount	);
					}
				}
				cursorPosition += 2;
		}

		// TODO : Configure cursorPosition for this
		else if(strcmp (token1, open)==0)
		{
			char textFile[20];
			token1 = strtok(NULL, " ");
			if(token1==NULL)
				printf("SYNTAX ERROR!\n\n");
			else{
				strcpy(textFile,token1);
				openFile(textFile);
			}
		}

		else if(strcmp (token1, copy)==0)
		{
			cursorPosition += 3;
			char sourceFile[20], destFile[20];
			token1 = strtok(NULL, " ");
			if(token1==NULL)
				printf("SYNTAX ERROR!\n\n");
			else{
				strcpy(sourceFile,token1);
				token1 = strtok(NULL, " \n");
				if (token1==NULL)
					printf("SYNTAX ERROR!\n\n");
				else
					{
						strcpy(destFile,token1);
						copyCommand(sourceFile,destFile);
					}
				}
		}

		else if(strcmp (token1, marquee) == 0)
		{
			pthread_t id;
			char stringMarquee[50];
			
			token1 = strtok(NULL, "");

			if (token1 == NULL)
				printf("SYNTAX ERROR!\n\n");
			else{
				strcpy(stringMarquee, token1);
				//printf("%s \n", stringMarquee);
				pthread_create(&id, NULL, testMarquee, stringMarquee);
				cursorPosition += 2;
				printf("\n");
			}			
		}

		else{
				printf("SYNTAX ERROR!\n\n");
				cursorPosition += 3;
			}
	}

	return 0;	
}

