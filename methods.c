#include "header.h"
#include <dirent.h>
int cmpstr(char str1[], char str2[]){
	int i =0;
		while(str1[i] != '\n'&&str1[i] !='\000'&&str2[i] !='\n'&&str2[i] !='\000'){
		if(str1[i] != str2[i]){
		return 0;	
		}
	i++;	
	}
		return 1;
}
char* list(){
char * content=(char *)malloc(sizeof(char)*2048);
memset(content,0,sizeof(content));
int i=0;
int c=0;
DIR *d;
struct dirent *dir;
d=opendir(".");
if(d){
	strcat(content, "\n");
	while ((dir =readdir(d)) != NULL)
	{
		strcat(dir->d_name," 	 ");
		strcat(content,dir->d_name);
		if(c>5)
		{
			strcat(content,"\n");
			c=0;
		}
		c++;
	}
	closedir(d);
}

return content;
}

void writeTofile(char* file, char data[]){
FILE *outfile;
outfile=fopen(file, "w");
fprintf(outfile, "%s\n", data);
fclose(outfile);
}

char* readFile(char file[]){
 FILE *fp;
    char temp[2048];
    char* str=(char *)malloc(sizeof(char)*2048);

memset(str,0,sizeof(str));
int i=0;
 
    fp = fopen(file, "r");
    if (fp == NULL){
        printf("Could not open file %s",file);
        return NULL;
    }
    while (fgets(temp, 2048, fp) != NULL){
        printf("%s", temp);
	strcat(str, temp);
    }
    fclose(fp);
    return str;
}
char* strsegment(char *str, char garbage) {
char* s=(char*)malloc(sizeof(char)*2048);
memset(s,0,sizeof(s));
int i=0;
	while(str[i] != garbage){
	s[i]=str[i];
		i++;
	}
	return s;
}

