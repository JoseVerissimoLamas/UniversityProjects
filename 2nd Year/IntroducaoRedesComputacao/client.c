/*************************************************************
* CLIENTE liga ao servidor (definido em argv[1]) no porto especificado
* (em argv[2]), escrevendo a palavra predefinida (em argv[3]).
* USO: >cliente <enderecoServidor> <porto> <Palavra>
*************************************************************/
//gcc client.c -lpthread -D_REENTRANT -Wall -o client
    
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
    
#define BUF_SIZE 1024
    
//__________________________________Global Vars__________________________________
   
//____________________________________Funçoes____________________________________
   
void escuta(int subs_fd){
    char buffer[BUF_SIZE];
    while(1){
        if(read(subs_fd, buffer, BUF_SIZE-1)>0){
            printf("%s\n", buffer);
        }       
    }
}
 
void process_server(int server_fd){
   
  char buffer[BUF_SIZE];
  char login[BUF_SIZE];
 
  while(1){
    //sleep(1);
    if(read(server_fd, buffer, BUF_SIZE-1) > 0){
      printf("%s\n", buffer);
      fgets(login, BUF_SIZE, stdin);
      write(server_fd, login, strlen(login)+1);
    }
  }
   
}
    
void erro(char *msg){
    printf("[Client:Error] %s\n", msg);
    exit(-1);
}
   
//______________________________________Main______________________________________
   
int main(int argc, char *argv[]) {
    char endServer[100]; //addr IP
    int fd, subs_fd; //file descriptor do socket
    struct sockaddr_in addr, subs_addr;
    struct hostent *hostPtr;
   
    if (argc != 2) {
        printf("cliente <port>\n");
        exit(-1);
    }
      
    strcpy(endServer, "127.0.0.1");
   
    if ((hostPtr = gethostbyname(endServer)) == 0)
        erro("Nao consegui obter endereço");
   
 
  //struct para estabelecer ligaçao
    bzero((void *) &addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ((struct in_addr *)(hostPtr->h_addr))->s_addr;
    addr.sin_port = htons((short) atoi(argv[1]));
   
    //Abre e liga ao socket
    if((fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
        erro("Socket");
 
    if( connect(fd,(struct sockaddr *)&addr,sizeof (addr)) < 0){
        erro("Connect");
    }
 
    //struct para establecer ligaçao2
    /*bzero((void *) &subs_addr, sizeof(subs_addr));
    subs_addr.sin_family = AF_INET;
    subs_addr.sin_addr.s_addr = ((struct in_addr *)(hostPtr->h_addr))->s_addr;
    subs_addr.sin_port = htons((short) atoi(argv[1])+5);
   
    //Abre e liga ao socket2
    if((subs_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
        erro("Socket");
    if( connect(subs_fd,(struct sockaddr *)&subs_addr,sizeof (subs_addr)) < 0)
        erro("Connect");*/
   
    /*if(fork()==0){
      escuta(subs_fd);
      exit(0);
    }*/
    
    process_server(fd);//Faz a comunicaçao com o servidor
    
    close(fd);
    exit(0);
}
