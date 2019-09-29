
/* TCP client */
/* E/15/208 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv)
{

FILE *File;
int sockfd,n, size,i;
struct sockaddr_in servaddr;
char banner[] = "request";
char buffer[1000];
int flag = 0;


if (argc != 2)
{
printf("usage: ./%s <IP address>\n",argv[0]);
return -1;
}

/* socket to connect */
sockfd=socket(AF_INET,SOCK_STREAM,0);

/* IP address information of the server to connect to */
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr=inet_addr(argv[1]);
servaddr.sin_port=htons(32000);

/* connect to the server */
connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

/* send request */
printf("request\n");
sendto(sockfd,banner,strlen(banner),0, (struct sockaddr*)&servaddr,sizeof(servaddr));

/* open file to append */    
File = fopen("serverfile.txt", "a");
if (File == NULL) {
   printf("error opening file.\n");
}

/* get the file size */
n=recvfrom(sockfd,buffer,10000,0,NULL,NULL);
buffer[n]=0;
sscanf(buffer,"%d",&size);
printf("Received:%d\n",size);

//calculate no of iteration for both round values and other values
int iter;
if((size/1000)<(size/1000.0))iter=(size/1000)+1;
else iter=(size/1000);

/* receive the content of the file and append it to the file created */ 
for(i = 0;i<iter;i++){
 char buffer2[1000];
n=recvfrom(sockfd,buffer2,10000,0,NULL,NULL);
buffer2[n]=0;
//sscanf(buffer2,"%d",&size);
fprintf(File,"%s",buffer2);
flag = 1;
}

/* finish downloading */
fclose(File);

if(flag == 1){
printf("file successfully downloaded. :) \n");
}

return 0 ;
}
