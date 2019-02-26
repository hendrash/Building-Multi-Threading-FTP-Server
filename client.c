#include <stdio.h>
//#include <sys/socket.h> 
//#include <stdlib.h> 
//#include <netinet/in.h> 
//#include <string.h>
//#include <unistd.h>
//#include <arpa/inet.h>
#include "header.h"
#include<setjmp.h>
#define PORT 8080 
int cmpstr(char* str1, char* str2);
int connection(char* ip);

int main(int argc, char const *argv[]) 
{
    char* ipAddress = malloc(15*sizeof(char));
    printf("=====================================================\n");
    printf("You are currently not connected to a server please enter \nin the ip and port number you wanna connect to!");
    printf("\n=====================================================\n");   
    char command[50];
    strcpy(command," ");
    while(cmpstr(command,"q")==0&&cmpstr(command, "QUIT")==0&&cmpstr(command, "quit")==0){
    printf("You can quit q or connect c the server\n");
    printf(">");
    fgets(command, sizeof(command), stdin);
    if(cmpstr(command, "connect")==1||cmpstr(command, "CONNECT")==1||cmpstr(command, "c")==1){
    printf("Enter the following \n");
   
    printf("Ip address: ");
    fgets(ipAddress, 15*sizeof(ipAddress), stdin);
    strcpy(ipAddress,strsegment(ipAddress,'\n'));
    //strncpy(ipAddress, "127.0.0.1",15);
    printf("\nAttempting to connect to the server\n");
    connection(ipAddress);
    }  
    }
return 1;}

int connection(char *ip){
    struct sockaddr_in address; 
    static jmp_buf s_jumpBuffer;
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *inComingMessage = "Client is connected"; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
   printf("Connection successful!!\n");
   char command[50];
   char* buffer=malloc(2048*sizeof(char)); 
   do {
    printf("\n==========================================================================");
    printf("\n l to list the directory | r to retrieve a file | s to store a file | q to quit \n"); 
    printf("\n============================================================================\n"); 
    printf("> ");
   memset(command,0,sizeof(command));
   fgets(command, sizeof(command)*15, stdin); 
    send(sock , command , strlen(command) , 0); 
    char* ptr=malloc(20*sizeof(char*));
    strcpy(ptr,strtok(command," "));
    
    if(cmpstr(ptr,"l")==1||cmpstr(ptr,"list")==1){
    read(sock,buffer,2048);
    printf("%s",buffer); 
    }
    if(cmpstr(ptr,"r")==1||cmpstr(ptr,"retrieve")==1){
    if(countWords(command)==2){
    strcpy(ptr,strtok(NULL," "));
    valread = read( sock , buffer, 2048); 
    strcpy(ptr,strtok(NULL," "));
    strcpy(ptr,strsegment(ptr,'\n'));
    writeTofile(ptr, buffer);}
    else{
	    printf("Formatting error from retrieve a file. Type:\nr <Filename> <Destination File>");
    }	}
   if(cmpstr(ptr, "s")==1||cmpstr(ptr,"saveFile")==1){
    if(countWords(command)==2){
    strcpy(ptr,strtok(NULL," "));
    strcpy(buffer, readFile(ptr));
    if(strlen(buffer)!=0){
    send(sock,buffer,strlen(buffer),0);}
    else{printf("FILE COULD NOT BE FOUND");}
    }
    else{
	    printf("Formatting error from sending a file. Type:\nr <Filename> <Destination File>");
    }
   }
    memset(buffer, 0, sizeof(buffer));
}while (cmpstr(command,"q")==0 && cmpstr(command, "QUIT")==0&&cmpstr(command, "quit")==0);
send(sock,"q",strlen("q"),0);
return 0;
}
 
