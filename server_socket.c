/* Server side implementation of socket programming 
   Author : Dovahkiin                           */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno,j;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     char filename[50];

     int flag = 1, i = 0;
     char arr[1000][10]; //Array that can store 1000 words each of max length 10
     FILE *ptr;

     if (argc < 2) {
         printf("ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        printf("ERROR opening socket\n");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
              printf("ERROR on binding\n");

     printf("Listening for requests from clients\n");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);

     if (newsockfd < 0)
          printf("ERROR on accept\n");
     else printf("obtained request\n");

     bzero(buffer,256);
     bzero(arr,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) printf("ERROR reading from socket\n");
     else printf("Reading from buffer for client request\n");
 strcpy(filename,buffer);
     printf("Searching for the file:%s\n",filename);

      ptr = fopen(filename, "r");
      if(!ptr)
      {
        printf("cant open file");
        exit(0);
      }
      // logic to obtain content from file
      while(flag > 0)
      {
      flag = fscanf(ptr, "%s",arr[i]);
      i++;
      }
      fclose(ptr);
      flag=i;

     /* optional printing of obtained text
      for(j=0;j<flag-1;j++) {
        printf("%s ",arr[j]);} */


      n = write(newsockfd,arr,1000);   //assuming max charecters in file is 1000.
      if (n < 0) error("ERROR writing to socket");
      close(newsockfd);
      close(sockfd);
      return 0;
}


