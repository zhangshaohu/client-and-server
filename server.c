/*//===========================================
// @author Shaohu Zhang
// Compiler used: gcc on Linux
// gcc server.c -o server
// ./server
// This program implements a TCP server
//===========================================*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define PORT 50003 //the port client will be connecting to.
#define MAX_CHRACTER 80 //receive a text message of no more than 80 characters.

int main()
{
    int sock, connected, bytes_recieved , true = 1;
    char send_data[MAX_CHRACTER ], recv_data[MAX_CHRACTER];
    char isFalse[] = "False";
    char is_user_id[] = "Your ID is correct";
    char is_password[] = "Your password is correct";
    FILE *fp;
    fp = fopen("log.txt", "w+");
    struct sockaddr_in server_addr,client_addr;
    int sin_size;
    int sin[MAX_CHRACTER],i,length;
    
    

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket");
        exit(1);
    }

    if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) {
        perror("Setsockopt");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero),8);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
       == -1) {
        perror("Unable to bind");
    exit(1);
}

if (listen(sock, 5) == -1) {
    perror("Listen");
    exit(1);
}

printf("\n Server is waiting for clients on port ");
fflush(stdout);

sin_size = sizeof(struct sockaddr_in);

connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

printf("\n build a connection from (%s , %d)",
   inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
while(1)
{

    bytes_recieved=recv(connected, recv_data, MAX_CHRACTER ,0);
    recv_data[bytes_recieved] = '\0';
    //printf("\n RECIEVED: %s length: %ld" ,recv_data, strlen(recv_data));
    fflush(stdout);
    int res=strcmp(recv_data, "fireeye");
    printf("The ID return: %d",res);
    if (res == 0){
       send(connected, is_user_id, strlen(is_user_id), 0);
       break; 
   }else{

       send(connected, isFalse, strlen(isFalse), 0);
   }
}
while(1)
{
    bytes_recieved=recv(connected,recv_data,MAX_CHRACTER ,0);
    recv_data[bytes_recieved] = '\0';
    printf("\n RECIEVED: %s " ,recv_data);
    fflush(stdout);
    if (strcmp(recv_data, "12345") != 0){
        send(connected, isFalse, strlen(isFalse), 0);
    }
    else{
        send(connected, is_password, strlen(is_password), 0);
        break;
    }
}
while(1)
{
    bytes_recieved=recv(connected,recv_data,MAX_CHRACTER ,0);
    recv_data[bytes_recieved] = '\0';
    if (strlen(recv_data) == 0){
        break;
    }
    fputs(recv_data, fp);
    fputs("\n", fp);
    printf("\n Log: %s " ,recv_data);
    fflush(stdout);
    send(connected, recv_data, strlen(recv_data), 0);
}
fclose(fp);
close(connected);
close(sock);
return 0;
}
