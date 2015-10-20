/* Client side implementation of socket programming 
   Author : Dovahkiin                           */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


int main(int argc, char *argv[])
{
    int sockfd, portno, n,j,fetch=400; //fetch specifies number of charecters that client wants to fetch. 
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    char fbuffer[1000][10];
    if (argc < 3) {
       printf("usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        printf("ERROR opening socket\n");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        printf("ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        printf("ERROR connecting\n");
    printf("Enter the file to be fetched :\n");
    bzero(buffer,256);

     fflush(stdin);
     scanf("%s",buffer);
     fflush(stdin);
     n = write(sockfd,buffer,strlen(buffer));
     if (n < 0)
         printf("ERROR writing to socket\n");


     bzero(fbuffer,fetch);
     n = read(sockfd,fbuffer,fetch);
     if (n < 0)
         printf("ERROR reading from socket\n");
     printf("File fetched,the contents are :\n\n");
     for(j=0;j<fetch;j++) { printf("%s ",fbuffer[j]);}
     close(sockfd);
     return 0;
}

