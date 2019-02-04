// Server side C/C++ program to demonstrate Socket programming 
/*#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>*/
#include "header.h"
#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[2048] = {0}; 
    char *hello = "Server successfully connected"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    }
   printf("Enter q to exit!"); 
    while(buffer !="q"){
     valread = read(new_socket , buffer,2048);
     char ptr[15];
     strcpy(ptr,strtok(buffer," ")); 
    if(cmpstr(ptr,"list")==1||cmpstr(ptr,"l")==1){
     printf("Printing the current directory!");
     strcpy(buffer,list());
     send(new_socket,buffer, strlen(buffer),0);		
    }
	
    if(cmpstr(ptr,"r")==1||cmpstr(ptr,"retrieve")==1){
     strcpy(ptr,strtok(NULL," "));
     strcpy(buffer,readFile(ptr));
     send(new_socket,buffer,strlen(buffer),0);
    }
    
    if(cmpstr(ptr,"s")==1||cmpstr(ptr,"store")==1){
    strcpy(ptr, strtok(NULL, " "));
    strcpy(ptr, strtok(NULL, " "));
    strcpy(ptr,strsegment(ptr,'\n'));
    read(new_socket, buffer, 2048);
    writeTofile(ptr, buffer);
    }
    memset(buffer, 0, sizeof(buffer));
    }
    return 0; 
}
