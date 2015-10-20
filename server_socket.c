/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno,j;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     char filename[50];

     int flag = 1, i = 0;
     char arr[1000][10];
     FILE *ptr;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     printf("Listening for requests from clients\n");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);
     if (newsockfd < 0)
          error("ERROR on accept");
     else printf("obtained request\n");
     bzero(buffer,256);
     bzero(arr,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
 else printf("Reading from buffer\n");
    // printf("Searching for the file: %s\n",buffer);
//printf("Searching for the file: %s!\n",filename);
strcpy(filename,buffer);
printf("Searching for the file:%s\n",filename);

      ptr = fopen(filename, "r");
      if(!ptr)
      {
        printf("cant open file");
        exit(0);
}
      while(flag > 0)
      {printf("inside while\n");
      flag = fscanf(ptr, "%s",arr[i]);

      i++;
      }
      fclose(ptr);
      flag=i;
      printf("flag= %d",flag);
      for(j=0;j<flag-1;j++) {
        printf("%s ",arr[j]);}


     n = write(newsockfd,arr,1000);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0;
}

