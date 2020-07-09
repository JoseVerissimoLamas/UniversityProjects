/*******************************************************************
* SERVIDOR no porto 9000, à escuta de novos clientes. Quando surjem
* novos clientes os dados por eles enviados são lidos e descarregados no ecrã.
*******************************************************************/
      
//gcc server.c -D_REENTRANT -lcurl -ljson-c -lpthread -Wall -o server
      
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <json-c/json.h>
#include <curl/curl.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
     
//ISTO AINDA TEM ERROS!!
     
#define SERVER_PORT 9000
#define BUF_SIZE 512
#define DADOS_NUM 10
      
struct string {
    char *ptr;
    size_t len;
};
     
typedef struct _ISABELA{
    char id[100];
    char type[100];
    char activity[100];
    char location[100];
    char calls_duration[100];
    char calls_made[100];
    char calls_missed[100];
    char calls_received[100];
    char department[100];
    char sms_received[100];
    char sms_sent[100];
    int subscricoes[6];
}ISABELA;
 
typedef struct _MEDIAS{
    double calls_duration;
    double calls_made;
    double calls_missed;
    double calls_received;
    double sms_received;
    double sms_sent; 
}MEDIAS;
    
//Para evitar compilation errors
void info_pessoal(int client_fd);
    
void info_grupo(int client_fd);
    
void subscricao(int client_fd);
     
//__________________________________Global Vars__________________________________
     
int shmid; //ID da shared mem
int shmid_medias;
int n_clients=0;
int pid_main;
int login_client;
int temp_login_client;
     
ISABELA *isa_info; //vai ser usado para a shared mem
MEDIAS *info_media;
     
sem_t *semaf;
     
//_________________________________Funçoes JSON__________________________________
 
//JSON obect
struct json_object *jobj_array, *jobj_obj;
struct json_object *jobj_object_id,  *jobj_object_type, *jobj_object_activity, *jobj_object_location,  *jobj_object_latlong, *jobj_object_callsduration, 
*jobj_object_callsmade, *jobj_object_callsmissed, *jobj_object_callsreceived, *jobj_object_department, *jobj_object_smsreceived, *jobj_object_smssent;
enum json_type type = 0;
int arraylen;
 
//Write function to write the payload response in the string structure
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s){
    size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;
     
    return size*nmemb;
}
//Initilize the payload string
void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}
//Get the Data from the API and return a JSON Object
struct json_object *get_student_data(){
    struct string s;
    struct json_object *jobj;
    
     
    //Intialize the CURL request
    CURL *hnd = curl_easy_init();
     
    //Initilize the char array (string)
    init_string(&s);
     
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    //To run on department network uncomment this request and comment the other
    //curl_easy_setopt(hnd, CURLOPT_URL, "http://10.3.4.75:9014/v2/entities?options=keyValues&type=student&attrs=activity,calls_duration,calls_made,calls_missed,calls_received,department,location,sms_received,sms_sent&limit=1000");
        //To run from outside
    curl_easy_setopt(hnd, CURLOPT_URL, "http://socialiteorion2.dei.uc.pt:9014/v2/entities?options=keyValues&type=student&attrs=activity,calls_duration,calls_made,calls_missed,calls_received,department,location,sms_received,sms_sent&limit=1000");
     
    //Add headers
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "cache-control: no-cache");
    headers = curl_slist_append(headers, "fiware-servicepath: /");
    headers = curl_slist_append(headers, "fiware-service: socialite");
     
    //Set some options
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writefunc); //Give the write function here
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &s); //Give the char array address here
     
    //Perform the request
    CURLcode ret = curl_easy_perform(hnd);
    if (ret != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
     
        /*jobj will return empty object*/
        jobj = json_tokener_parse(s.ptr);
     
        /* always cleanup */
        curl_easy_cleanup(hnd);
        return jobj;
     
    }
    else if (CURLE_OK == ret) {
        jobj = json_tokener_parse(s.ptr);
        free(s.ptr);
     
        /* always cleanup */
        curl_easy_cleanup(hnd);
        return jobj;
    }
    exit(0);
}
void erro(char *msg){
    printf("[Server:Erro] %s\n", msg);
    exit(-1);
}
     
//____________________________________Opçoes____________________________________
 
void info_pessoal(int client_fd){ //DONE
    sem_wait(semaf);
    char infop_1[BUF_SIZE];
    char infop_2[BUF_SIZE];
    char infop_3[BUF_SIZE];
    int i=login_client;
 
    sprintf(infop_1,"id=%s\ntype=%s\nactivity=%s\nlocation=%s\n",isa_info[i].id, isa_info[i].type, isa_info[i].activity, isa_info[i].location);
    sprintf(infop_2,"Calls duration(s)=%s\nCalls made=%s\nCalls missed=%s\nCalls received=%s\n",isa_info[i].calls_duration, isa_info[i].calls_made,isa_info[i].calls_missed, isa_info[i].calls_received);
    sprintf(infop_3,"Department=%s\nSms received=%s\nSms sent=%s\n", isa_info[i].department, isa_info[i].sms_received, isa_info[i].sms_sent);
    strcat(infop_1,infop_2);
    strcat(infop_1,infop_3);
 
    if(write(client_fd, infop_1, BUF_SIZE-1) <= 0){
        perror("wtf: ");
    }
 
    sem_post(semaf);
}
      
void info_grupo(int client_fd){ //DONE
    sem_wait(semaf);
 
    char infog[BUF_SIZE];
 
    sprintf(infog, "\nMedia de Duracao de chamadas= %lf\nMedia de chamadas feitas= %lf\nMedia de chamadas perdidas= %lf\nMedia de chamadas recebidas= %lf\nMedia de SMS recebidas= %lf\nMedia de SMS enviadas= %lf\n", info_media->calls_duration, info_media->calls_made, info_media->calls_missed, info_media->calls_received, info_media->sms_received, info_media->sms_sent);
 
    write(client_fd, infog, BUF_SIZE-1);
 
    sem_post(semaf);
}
 
void call_d(int client_fd){ //DONE
    sem_wait(semaf);
 
    char d[BUF_SIZE];
 
    sprintf(d, "\nMedia de Duracao de chamadas= %.6lf\n", info_media->calls_duration);
 
    write(client_fd, d, BUF_SIZE-1);
 
    sem_post(semaf);
}
 
void call_m(int client_fd){ //DONE
    sem_wait(semaf);
 
    char d[BUF_SIZE];
 
    sprintf(d, "\nMedia de Chamadas feitas= %.6lf\n", info_media->calls_made);
 
    write(client_fd, d, BUF_SIZE-1);
 
    sem_post(semaf);
}
 
void call_mssd(int client_fd){ //DONE
    sem_wait(semaf);
 
    char d[BUF_SIZE];
 
    sprintf(d, "\nMedia de Chamadas perdidas= %.6lf\n", info_media->calls_missed);
 
    write(client_fd, d, BUF_SIZE-1);
 
    sem_post(semaf);
}
 
void call_rcv(int client_fd){ //DONE
    sem_wait(semaf);
 
    char d[BUF_SIZE];
 
    sprintf(d, "\nMedia de Chamadas recebidas= %.6lf\n", info_media->calls_received);
 
    write(client_fd, d, BUF_SIZE-1);
 
    sem_post(semaf);
}
 
void sms_rcv(int client_fd){ //DONE
    sem_wait(semaf);
 
    char d[BUF_SIZE];
 
    sprintf(d, "\nMedia de SMS recebidas= %.6lf\n", info_media->sms_received);
 
    write(client_fd, d, BUF_SIZE-1);
 
    sem_post(semaf);
}
 
void sms_snt(int client_fd){ //DONE
    sem_wait(semaf);
 
    char d[BUF_SIZE];
 
    sprintf(d, "\nMedia de SMS enviadas= %.6lf\n", info_media->sms_sent);
 
    write(client_fd, d, BUF_SIZE-1);
 
    sem_post(semaf);
}
 
//____________________________________Funçoes____________________________________
void sigint(){
    if(getpid()==pid_main){//Verifica se é o processo main
        for(int i=0; i< n_clients +1; i++){//Espera que os prcessos filhos terminem | o +1 é do processo refresh
            wait(NULL);
        }
        sem_close(semaf);
        sem_unlink("SEMAF");
        shmdt(isa_info);
        shmctl(shmid,IPC_RMID,NULL);
        exit(0);
    }
    else{
        for(int i=0; i<n_clients +1; i++){
            kill(getpid(), SIGTERM);
        }       
    }
    printf("\nCliente encerrado...");
 
 
 
}
    
//Esta função verifica se o id existe na shared memory aka base de dados
int verifica_id(char *id){
    char buffer[BUF_SIZE];
    strcpy(buffer, id);
    sem_wait(semaf);
    for(int i=0;i< arraylen;i++){
      if ((strcmp(buffer,isa_info[i].id))==0){
        login_client=i;
        sem_post(semaf);
        return 1;
      }
    }
    sem_post(semaf);
    return 0;
}
   
void process_client(int client_fd, struct sockaddr_in client_addr){   
    char buffer[BUF_SIZE];
    int nread;
    char login_message[] = "Insira o id:\n";
    char menu_message[] = "\n\n------------[MENU]------------\n1-Informacao pessoal\n\n -Informacao grupo\n\t2-Info.Geral\n\t3-Calls Duration\n\t4-Calls Made\n\t5-Calls Missed\n\t6-Calls Recived\n\t7-Sms Recived\n\t8-Sms Sent\n\n -Subscricao\n\t9-CallDur\n\t10-CallMade\n\t11-CallMissed\n\t12-CallRcvd\n\t13-SmsSent\n\t14-SmsRcvd\n------------------------------\n";
   
    write(client_fd, login_message, 1 + sizeof(login_message));   
 
    while(1){ //check aos IDS
        write(client_fd, login_message, sizeof(login_message)+1);
        if(read(client_fd, buffer, BUF_SIZE-1)>0){//ele daqui le o id
            buffer[strlen(buffer)-1]='\0';
            printf("-%s-", buffer);
            if(verifica_id(buffer) == 1){
                printf("A Client has logged in\n");
                break;
            }
            else{
                printf("Wrong ID\n");
            }
        }
    }
 
    write(client_fd, menu_message, strlen(menu_message));
    printf("%s", menu_message);
    while(1){ //Escolha do menu
        fflush(NULL);
        if( (nread = read(client_fd, buffer, BUF_SIZE-1)) > 0){
             
            switch(atoi(buffer)){ //Ha aqui um erro 
                case(1):
                    info_pessoal(client_fd);
                    break;
                case(2):
                    info_grupo(client_fd);
                    break;
                case(3):
                    call_d(client_fd);
                    break;
                case(4):
                    call_m(client_fd);
                    break;
                case(5):
                    call_mssd(client_fd);
                    break;
                case(6):
                    call_rcv(client_fd);
                    break;
                case(7):
                    sms_rcv(client_fd);
                    break;
                case(8):
                    sms_snt(client_fd);
                    break;
                case(9):
                    //call duration | estas funcoes ainda têm de fazer um write qualquer se nao o cliente tripa todo
                    isa_info[login_client].subscricoes[0]=1;
                    write(client_fd, "Esta subscrito na CallDuration!\n", sizeof("Esta subscrito na CallDuration!\n"));
                    break;
                case(10):
                    //call made
                    isa_info[login_client].subscricoes[1]=1;
                    write(client_fd, "Esta subscrito na CallMade!\n", sizeof("Esta subscrito na CallMade!\n"));
                    read(client_fd, buffer, BUF_SIZE-1);
                    write(client_fd, menu_message, strlen(menu_message));
                    break;
                case(11):
                    //call missed
                    isa_info[login_client].subscricoes[2]=1;
                    write(client_fd, "Esta subscrito na CallMissed!\n", sizeof("Esta subscrito na CallMissed!\n"));
                    break;
                case(12):
                    //call call recv
                    isa_info[login_client].subscricoes[3]=1;
                    write(client_fd, "Esta subscrito na CallRecived!\n", sizeof("Esta subscrito na CallRecived!\n"));
                    break;
                case(13):
                    //sms sent
                    isa_info[login_client].subscricoes[4]=1;
                    write(client_fd, "Esta subscrito na SmsSent!\n", sizeof("Esta subscrito na SmsSent!\n"));
                    break;
                case(14):
                    //sms rcv
                    isa_info[login_client].subscricoes[5]=1;
                    write(client_fd, "Esta subscrito na SmsRecived!\n", sizeof("Esta subscrito na SmsRecived!\n"));
                    break;
 
                default:
                    write(client_fd, "Entrada nao existente\n", sizeof("Entrada nao existente\n"));
                    break;
            }   
        } 
    }     
    close(client_fd);
}
      
void process_refresh(){
    //Get the student data
    jobj_array = get_student_data();
     
    //Get array length
    arraylen = json_object_array_length(jobj_array);
     
    while(1){ //atualiza a informaçao de 3 em 3 minutos
        //sem_wait(semaf);
        //Example of howto retrieve the data
        for (int i = 0; i < arraylen; i++) {
            //get the i-th object in jobj_array
            jobj_obj = json_object_array_get_idx(jobj_array, i);
     
            //get the name attribute in the i-th object
            jobj_object_id = json_object_object_get(jobj_obj, "id");
                if(json_object_get_string(jobj_object_id) != NULL){
                    strcpy(isa_info[i].id, json_object_get_string(jobj_object_id));
                } 
            jobj_object_type = json_object_object_get(jobj_obj, "type"); 
                if(json_object_get_string(jobj_object_type) != NULL){
                    strcpy(isa_info[i].type, json_object_get_string(jobj_object_type));
                } 
            jobj_object_activity = json_object_object_get(jobj_obj, "activity");
                if(json_object_get_string(jobj_object_activity) != NULL){
                    strcpy(isa_info[i].activity, json_object_get_string(jobj_object_activity));
                }
            jobj_object_location = json_object_object_get(jobj_obj, "location");
                if(json_object_get_string(jobj_object_location) != NULL){
                    strcpy(isa_info[i].location, json_object_get_string(jobj_object_location));
                }   
            jobj_object_callsduration = json_object_object_get(jobj_obj, "calls_duration");
                if(json_object_get_string(jobj_object_callsduration) != NULL){
                    strcpy(isa_info[i].calls_duration, json_object_get_string(jobj_object_callsduration));
                }   
            jobj_object_callsmade = json_object_object_get(jobj_obj, "calls_made");
                if(json_object_get_string(jobj_object_callsmade) != NULL){
                    strcpy(isa_info[i].calls_made, json_object_get_string(jobj_object_callsmade));
                }
            jobj_object_callsmissed = json_object_object_get(jobj_obj, "calls_missed");
                if(json_object_get_string(jobj_object_callsmissed) != NULL){
                    strcpy(isa_info[i].calls_missed, json_object_get_string(jobj_object_callsmissed));
                }
            jobj_object_callsreceived= json_object_object_get(jobj_obj, "calls_received");
                if(json_object_get_string(jobj_object_callsreceived) != NULL){
                    strcpy(isa_info[i].calls_received, json_object_get_string(jobj_object_callsreceived));
                }
            jobj_object_department = json_object_object_get(jobj_obj, "department");
                if(json_object_get_string(jobj_object_department) != NULL){
                    strcpy(isa_info[i].department, json_object_get_string(jobj_object_department));
                }
            jobj_object_smsreceived = json_object_object_get(jobj_obj, "sms_received");
                if(json_object_get_string(jobj_object_smsreceived) != NULL){
                    strcpy(isa_info[i].sms_received, json_object_get_string(jobj_object_smsreceived));
                }
            jobj_object_smssent = json_object_object_get(jobj_obj, "sms_sent");
                if(json_object_get_string(jobj_object_smssent) != NULL){
                    strcpy(isa_info[i].sms_sent, json_object_get_string(jobj_object_smssent));
                }
             
            info_media->calls_duration += atoi(isa_info[i].calls_duration);
            info_media->calls_made += atoi(isa_info[i].calls_made);
            info_media->calls_missed += atoi(isa_info[i].calls_missed);
            info_media->calls_received += atoi(isa_info[i].calls_received);
            info_media->sms_received += atoi(isa_info[i].sms_received);
            info_media->sms_sent += atoi(isa_info[i].sms_sent);
 
            for(int i=0; i<6; i++){ //inicialmente nao esta subscrito a nada
                isa_info[i].subscricoes[i]=0;
            }
    
            //print out the name attribute
            printf("i = %d\n", i);
            printf("id=%s\n", json_object_get_string(jobj_object_id));
            printf("type=%s\n", json_object_get_string(jobj_object_type));
            printf("activity=%s\n", json_object_get_string(jobj_object_activity));
            printf("location=%s\n", json_object_get_string(jobj_object_location));
            printf("Calls duration(s)=%s\n", json_object_get_string(jobj_object_callsduration));
            printf("Calls made=%s\n", json_object_get_string(jobj_object_callsmade));
            printf("Calls missed=%s\n", json_object_get_string(jobj_object_callsmissed));
            printf("Calls received=%s\n", json_object_get_string(jobj_object_callsreceived));
            printf("Department=%s\n", json_object_get_string(jobj_object_department));
            printf("Sms received=%s\n", json_object_get_string(jobj_object_smsreceived));
            printf("Sms sent=%s\n", json_object_get_string(jobj_object_smssent));
            printf("\n");
        }
        info_media->calls_duration /= arraylen;
        info_media->calls_made /= arraylen;
        info_media->calls_missed /= arraylen;
        info_media->calls_received /= arraylen;
        info_media->sms_received /= arraylen;
        info_media->sms_sent /= arraylen;
 
        //sem_post(semaf);
        sleep(180);
    }
}
 
void subsz(int subs_fd){
    /*
    opcoes no menu (check)
    consoante a opcao, a alteracao é logo feita no menu (check)
    e a var da subs (na struct do cliente) que fica a 0/1 (check)
    func para a subs que recebe o valor e trabalha-o para as atualizacoes
    */
    double media=0;
    char aux[BUF_SIZE];
 
    while(1){
        if(isa_info[login_client].subscricoes[0] == 1){
            for(int i=0; i< arraylen; i++){
                jobj_object_callsduration = json_object_object_get(jobj_obj, "calls_duration");
                if(json_object_get_string(jobj_object_callsduration) != NULL){
                    strcpy(aux, json_object_get_string(jobj_object_callsduration));
                    media += atoi(aux);
                } 
            }
            media /= arraylen;
            if(media != info_media->calls_duration){
                info_media->calls_duration= media;
                write(subs_fd, "Houve alteração na media das CallsDurations!", sizeof("Houve alteração na media das CallsDurations!"));
            }
        }
        else if(isa_info[login_client].subscricoes[1] == 1){
            for(int i=0; i< arraylen; i++){
                jobj_object_callsmade = json_object_object_get(jobj_obj, "calls_made");
                if(json_object_get_string(jobj_object_callsmade) != NULL){
                    strcpy(aux, json_object_get_string(jobj_object_callsmade));
                    media += atoi(aux);
                } 
            }
            media /= arraylen;
            if(media != info_media->calls_made){
                info_media->calls_made= media;
                write(subs_fd, "Houve alteração na media das CallsMade!", sizeof("Houve alteração na media das CallsMade!"));
            }
        }
        else if(isa_info[login_client].subscricoes[2] == 1){
            for(int i=0; i< arraylen; i++){
                jobj_object_callsmissed = json_object_object_get(jobj_obj, "calls_missed");
                if(json_object_get_string(jobj_object_callsmissed) != NULL){
                    strcpy(aux, json_object_get_string(jobj_object_callsmissed));
                    media += atoi(aux);
                } 
            }
            media /= arraylen;
            if(media != info_media->calls_missed){
                info_media->calls_missed= media;
                write(subs_fd, "Houve alteração na media das CallsMissed!", sizeof("Houve alteração na media das CallsMissed!"));
            }
        }
        else if(isa_info[login_client].subscricoes[3] == 1){
            for(int i=0; i< arraylen; i++){
                jobj_object_callsreceived = json_object_object_get(jobj_obj, "calls_received");
                if(json_object_get_string(jobj_object_callsreceived) != NULL){
                    strcpy(aux, json_object_get_string(jobj_object_callsreceived));
                    media += atoi(aux);
                } 
            }
            media /= arraylen;
            if(media != info_media->calls_received){
                info_media->calls_received= media;
                write(subs_fd, "Houve alteração na media das CallsRecived!", sizeof("Houve alteração na media das CallsRecived!"));
            }
        }
        else if(isa_info[login_client].subscricoes[4] == 1){
            for(int i=0; i< arraylen; i++){
                jobj_object_smsreceived = json_object_object_get(jobj_obj, "sms_received");
                if(json_object_get_string(jobj_object_smsreceived) != NULL){
                    strcpy(aux, json_object_get_string(jobj_object_smsreceived));
                    media += atoi(aux);
                } 
            }
            media /= arraylen;
            if(media != info_media->sms_received){
                info_media->sms_received= media;
                write(subs_fd, "Houve alteração na media das SmsRecived!", sizeof("Houve alteração na media das SmsRecived!"));
            }
        }
        else if(isa_info[login_client].subscricoes[5] == 1){
            for(int i=0; i< arraylen; i++){
                jobj_object_smssent = json_object_object_get(jobj_obj, "sms_sent");
                if(json_object_get_string(jobj_object_smssent) != NULL){
                    strcpy(aux, json_object_get_string(jobj_object_smssent));
                    media += atoi(aux);
                } 
            }
            media /= arraylen;
            if(media != info_media->sms_sent){
                info_media->sms_sent= media;
                write(subs_fd, "Houve alteração na media das SmsSent!", sizeof("Houve alteração na media das SmsSent!"));
            }
        }
        sleep(20);
    }
}
 
void socketSubscricao(){ //WIP
    int subs, client_subs, client_addr_size;
    struct sockaddr_in subs_addr, client_addr;
 
    //Subscrição
    bzero((void *) &subs_addr, sizeof(subs_addr));
    subs_addr.sin_family = AF_INET;
    subs_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    subs_addr.sin_port = htons(SERVER_PORT+5);
 
    //Subscrção socket
    if ( (subs = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        erro("na funcao socket");
    if ( bind(subs,(struct sockaddr*)&subs_addr,sizeof(subs_addr)) < 0)
        erro("na funcao bind");
    if( listen(subs, 5) < 0)
        erro("na funcao listen");
     
    client_addr_size = sizeof(client_addr);
    client_subs = accept(subs,(struct sockaddr *)&client_addr, (socklen_t *)&client_addr_size);
        if (fork() == 0) {
            subsz(subs);                
            exit(0);
        }
        close(subs);
        close(client_subs);
}
     
//______________________________________Main______________________________________
     
int main() {
    pid_main=getpid();
    signal(SIGINT, sigint);
 
    //Get the student data
    jobj_array = get_student_data();
    //Get array length
    arraylen = json_object_array_length(jobj_array);
     
    int fd, client;
    struct sockaddr_in addr, client_addr;
    int client_addr_size;
     
    //Abre o semaphore
    semaf= sem_open("SEMAF", O_CREAT|O_EXCL, 0700, 1);
     
    //Main
    bzero((void *) &addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(SERVER_PORT);
 
     
    //Shared mem
    if( (shmid= shmget(IPC_PRIVATE, (sizeof(struct _ISABELA)*arraylen), IPC_CREAT|0766)) <0 ){
        erro("[SHM] Ipc creat");
        exit(1);
    }
    if( (isa_info = (ISABELA*)shmat(shmid, NULL, 0))== (void*)-1 ){
        erro("[SHM] SHMAT");
        exit(1);
    }
    if( (shmid_medias= shmget(IPC_PRIVATE, (sizeof(struct _MEDIAS)), IPC_CREAT|0766)) <0 ){
        erro("[SHM_M] Ipc creat");
        exit(1);
    }
    if( (info_media = (MEDIAS*)shmat(shmid_medias, NULL, 0))== (void*)-1 ){
        erro("[SHM_M] SHMAT");
        exit(1);
    }
     
    //Processo refresh
    if(fork()==0){
        process_refresh();
        printf("\n\nERRO\n\n");
    }
     
    //socketSubscricao();
 
    //Socket stuff
    if ( (fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        erro("na funcao socket");
    if ( bind(fd,(struct sockaddr*)&addr,sizeof(addr)) < 0)
        erro("na funcao bind");
    if( listen(fd, 5) < 0)
        erro("na funcao listen");
 
    while (1) {
        //while(waitpid(-1,NULL,WNOHANG)>0);
        client_addr_size = sizeof(client_addr);
        client = accept(fd,(struct sockaddr *)&client_addr, (socklen_t *)&client_addr_size);
        if (client > 0) {
            if (fork() == 0) {
                close(fd);
                //n_clients++;
                process_client(client, client_addr);                 
                exit(0);
            }
            close(client);
        }
    }
     
return 0;
}
