// saveoff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <process.h>

void makedir(char *newdir)
{
	/// Make up the dest dir
	char dbuffer [9];
	char tbuffer [9];
	_strdate( dbuffer );
	_strtime( tbuffer );

	struct tm *newtime;
	time_t aclock;

	time( &aclock );                 
	newtime = localtime( &aclock );  
	char ascc[29];
	strcpy(ascc , asctime( newtime ) );
	char dirname[255];
	memset(dirname,0,255);
	strncpy(dirname,ascc+20,4);
	strncat(dirname,dbuffer,2);
	strncat(dirname,dbuffer+3,2);
	strncat(dirname,tbuffer,2);
	strncat(dirname,tbuffer+3,2);

	strcpy(newdir,dirname);
}

void main(int argc, char* argv[])
{
	char newdir[255];
	memset(newdir,0,255);
	makedir(newdir);

	char fulpath[512];
	memset(fulpath,0,512);
	
	char quicker[512];
	memset(quicker,0,512);
    if( _getcwd(quicker, 512 ) == NULL )
		strcpy(quicker,"c:\\");

	sprintf (fulpath,"%s\\",quicker);
	//sprintf (fulpath,"%s\\",argv[1]);
	// take off last dir
	int iCnt=0;
	printf("heres fulpath %s\n",fulpath);
	for (int i=strlen(fulpath);i>0;i--)
	{
		if (fulpath[i]=='\\')
		{
			iCnt++;
			if (iCnt>1)
				break;
		}
		fulpath[i]=0;
	}
	// now concat the new dir 
	char cmd[512];
	memset(cmd,0,512);
	sprintf(cmd,"mkdir %s%s",fulpath,newdir);
	printf ("heres the thing %s\n",cmd);
	system(cmd);

	system("dir /b *.jpg > dirfile.txt");

	FILE *infile;
	if( (infile  = fopen("dirfile.txt", "r")) == NULL )
	{
	   printf("The dir was not opened\n" );
	   return;
	}

	char oneline[255];
	bool bFukd = false;
	int newnum=0;
	while (!bFukd)
	{
		if(fgets(oneline,255,infile)==NULL)
		{
			bFukd=true;
			break;
		}
		newnum++;
		oneline[strlen(oneline)-1]=NULL;
		sprintf(cmd,"copy %s,..\\%s\\pik%04d.jpg",oneline,newdir,newnum);
		printf ("%s\n",cmd);
		system(cmd);
	}
	//gets(newdir);
}

