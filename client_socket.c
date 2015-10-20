#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n,j;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    char fbuffer[1000][10];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    printf("Enter the file to be fetched :\n");
    bzero(buffer,256);
//    fgets(buffer,255,stdin);
fflush(stdin);
        scanf("%s",buffer);
fflush(stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
         error("ERROR writing to socket");

    bzero(fbuffer,400);
    n = read(sockfd,fbuffer,400);
    if (n < 0)
 error("ERROR reading from socket");

    printf("File fetched,contents are :\n");
   for(j=0;j<400;j++) { printf("%s ",fbuffer[j]);}
    close(sockfd);
    return 0;
}
                                                                                                                                                                                           64,1          Bot

