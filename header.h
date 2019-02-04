#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
int cmpstr(char str1[], char str2[]);
char* list();
char* readFile(char* file);
void writeTofile(char* file, char* data);
char* strsegment(char *str, char garbage);
