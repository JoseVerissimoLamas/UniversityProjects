#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TLENG 75
#define NLEN 25

int load_max_tasks(){
    FILE* fich=fopen("mxt.txt","r");
    int i=0;
    fscanf(fich,"%d",&i);
    fclose(fich);
    return i;
}

void replace_max_tasks(int i){
    FILE* fich=fopen("mxt.txt","w");
    putc(i,fich);
    fclose(fich);
}

typedef struct data{
    int dia, mes, ano;
}Data;

typedef struct task{
    int id;
    char tarefa[TLENG];
    int prioridade;
    Data prazo;
    int id_user;
    struct task* next;
}Task;

typedef struct user{
    char nome[NLEN];
    int id;
    char email[TLENG];
    int n_tarefas;
    struct user* next;
    Task* l_task;
}User;

Task* inicia_lista(){
    Task *h=(Task*)malloc(sizeof(Task));
    assert(h);
    h->next=NULL;
    return h;
}

User* inicia_lista_user(){
    User *u=(User*)malloc(sizeof(User));

    assert(u);
    u->next=NULL;
    return u;
}

void new_task(Task*h){///nova tarefa em to do
    Task*aux=h;
    while(h->next){
        h=h->next;
    }
    int info;
    h->next=(Task*)malloc(sizeof(Task));
    h->next->next=NULL;
    ERROR2:
    printf("ID: ");
    scanf("%d",&info);
    while(aux->next){ if(aux->id==info){goto ERROR2;} aux=aux->next;}
    h->next->id=info;
    fflush(stdin);
    printf("\nTarefa:\n-");
    fgets(h->next->tarefa,TLENG,stdin);

    ERROR:
    printf("\nPrioridade(0-9): ");
    scanf("%d",&info);
    fflush(stdin);
    h->next->prioridade=info;
    if(info > 9 || info < 0){printf("ERROR");goto ERROR;}

    /*FILE* fich= fopen("to_do.txt","a");printf("coiso");
        fprintf(fich,"\n%d",h->next->id);
        fprintf(fich,"\n%s",h->next->tarefa);
        fprintf(fich,"%d",h->next->prioridade);
    fclose(fich);*/
}

void reset_tasks(char*fnome){///limpa o ficheiro
    FILE* fich= fopen(fnome,"w");
    fclose(fich);
}

int empty_file(char*fnome){/// verifica se o fich esta vazio
    FILE* fich= fopen(fnome,"r");
    char c=fgetc(fich);
    fclose(fich);
    if(c==EOF){return 1;}
    else{return 0;}
}

void annihilation(Task*h){///apaga tudo o que esta na tarefa
    while(h->next){
        Task*aux=h;
        h=h->next;
        free(aux);
    }
}

void load_users(User*u){///carrega os utilizadores
    FILE* fich=fopen("users.txt","r");
        char aux[NLEN];
        while(fgetc(fich)!=EOF){
            u->next=(User*)malloc(sizeof(User));
            u->next->next=NULL;
            u=u->next;
            fscanf(fich,"%[^\n]s",u->nome);
            fgetc(fich);
            fgets(aux,NLEN,fich);
            u->id=atoi(aux);
            fscanf(fich,"%[^\n]s",u->email);
            fgetc(fich);
            u->l_task=inicia_lista_user();
            u->n_tarefas=0;
        }
    fclose(fich);
}

void load_tasks(Task*h,char*fnome){///carrega as tarefas para as listas
    FILE* fich=fopen(fnome,"r");
        //Task* aux=NULL;
        char aux2[NLEN];
        while(fgetc(fich)!=EOF){
            h->next= (Task*)malloc(sizeof(Task));
            h->next->next=NULL;
            fgets(aux2, NLEN, fich);
                h->next->id=atoi(aux2);
            fgets(h->next->tarefa, TLENG, fich);
            fgets(aux2,NLEN,fich);
                h->next->prioridade=atoi(aux2);
            if(strncmp("to_do.txt",fnome, NLEN)!=0){
                fgets(aux2,NLEN,fich);
                h->next->id_user=atoi(aux2);
            }
            //aux=h;
            h=h->next;
        }
        //aux->next=NULL;///ele criava uma struct a mais... nao percebi pk... UPDATE: nao sei pk mas no portatil é necessario isto no fixo ja nao
        //free(h);
    fclose(fich);
}

void load_tasks_user(User*u, Task*h, char*fname){///carregas as tarefas atribuidas aos utilizadores
    if(empty_file(fname)==0){
        while(u->next){
            u=u->next;
            Task*aux=h;
            while(aux->next){
                aux=aux->next;
                if(u->id==aux->id_user){
                    transfer_to_l_user(u->l_task, aux);
                    u->n_tarefas+=1;
                }}}}
}

void display_users(User*u){/// display dos users
    while(u->next){
        printf("\n- %s\nid: %s\nemail: %s\n",u->next->nome, u->next->id, u->next->email);
        u=u->next;
    }
}

void display_tasks(Task*h, int i){///displar de todas as funcoes
    while(h->next){
        printf("\nID:%d",h->next->id);
        printf("\n-%s",h->next->tarefa);
        if(i!=1){printf("Prior: %d\n",h->next->prioridade);}
        else{printf("Data: %d\n",h->next->prioridade);}
        if(i==1){printf("User ID: %d\n", h->next->id_user);}
        h=h->next;
    }
    fflush(stdin);
}

void define_priority(Task*h){///redefinir prioridade
    printf("\tDefine Priority\n");
    int info=NULL;
    while(h->next){
        ERROR:
            printf("\n- %s\n",h->next->tarefa);
            printf("\nPrioridade(1->10): ");
            scanf("%d", &info);
        if(info>10||info<1){
            system("@cls||clear");
            printf("\tDefine Priority\n");
            goto ERROR;
        }
        h->next->prioridade=info;
        h=h->next;
    }
}

void ordena(Task*h,Task*f){ ///Troca as informacoes de cada lista
    int priory= h->prioridade;
    char tar[TLENG];
    int idy= h->id;
    strncpy(tar,h->tarefa,TLENG);
    h->prioridade=f->prioridade;
    h->id =f->id;
    strncpy(h->tarefa,f->tarefa,TLENG);
    f->prioridade=priory;
    f->id=idy;
    strncpy(f->tarefa,tar,TLENG);
}

void priorize_tasks(Task*h){///ordena por prioridade
    int flag=1;
    Task* aux;
    Task* aux2=NULL;
    h=h->next;
    if(h==NULL){return;}
    while(flag==1){
        flag=0;
        aux=h;
        while(aux->next != aux2){
            if(aux->prioridade < aux->next->prioridade){
                ordena(aux,aux->next);
                flag=1;
            }
            aux=aux->next;
        }
        aux2=aux;
    }
}

void save_tasks(Task*h,char*fnome){///guarda as tarefas no ficheiro
    FILE*fich=fopen(fnome,"w");
    while(h->next){
        fprintf(fich,"\n%d",h->next->id);
        fprintf(fich,"\n%s",h->next->tarefa);
        fprintf(fich,"%d",h->next->prioridade);
        if(strncmp("to_do.txt",fnome,NLEN)!=0){fprintf(fich, "\n%d\n", h->next->id_user);}
        h=h->next;
    }
    fclose(fich);
}

Task* display_select(Task*h,char*palavra){///display as tarefas e a opcao de a escolher
    int i;
    Task*aux;
ERROR:
    i=0;
    aux=h;
    while(aux->next){
        printf("\n%d- %s\n",i++,aux->next->tarefa);
        aux=aux->next;
    }
    int max=i;
    printf("\nQual e que quer %s?: ",palavra);
    scanf("%d",&i);
    for(int j=0; j<i; j++){///vai para a anterior da que se quer apagar
        if(i>=max){system("@cls||clear");goto ERROR;}///fool proof
        h=h->next;
    }
    return h;
}

int check_id_user(User*u,int idy){
    while(u->next){
        u=u->next;
        if(u->id==idy){return 1;}
    }
    return 0;
}

User* display_select_user(User*u){///auxiliar que da display aos user e a opcao de o selecionar
    User* aux= u;
    while(aux->next){
        aux=aux->next;
        printf("\n%d -%s\n",aux->id,aux->nome);
    }
    ERROR:
    printf("\nIndique o ID do user: ");
    int idy;
    scanf("%d",&idy);
    if(check_id_user(u,idy)==0){goto ERROR;}
    while(u->id != idy){u=u->next;}
    return u;
}

void delete_task(Task*h){/// apaga tarefa
    Task*aux;
    aux=display_select(h,"apagar");
    Task*aux2;
    aux2=aux->next;
    aux->next=aux->next->next;
    free(aux2);
}

void switch_list(Task*h, Task*d){///muda a tarefa de lista
    h=display_select(h,"mudar");
    while(d->next){d=d->next;}
    d->next=(Task*)malloc(sizeof(Task));
    d->next->next=NULL;
    ordena(h->next,d->next);
    Task*aux=h->next;
    h->next=h->next->next;
    free(aux);
}

Data soma_7(Data ola){///adiciona 7 dias
    Data coiso;
    if(coiso.dia + 7 > 31){
        coiso.dia=31-coiso.dia;
        if(coiso.mes+1>12){
            coiso.mes=1;
            coiso.ano+=1;
        }
    }
    return coiso;
}

Data sub_7(Data ola){///subtrai 7 dias
    Data coiso;
    if(coiso.dia - 7 < 0){
        coiso.dia=31-(7-coiso.dia);
        if(coiso.mes-1<0){
            coiso.mes=12;
            coiso.ano-=1;
        }
    }
    return coiso;
}

int validade(Task*u, Data testada){/// ve se a data introduzida esta no espaco de 1 semana
    while(u->next){
        u=u->next;
        if(compara_datas(sub_7(testada),u->prazo)!=-1||compara_datas(soma_7(testada),u->prazo)!=1 ){return 0;}
    }
    return 1;
}

int compara_datas(Data i, Data f){///ve se é maior ou menor
    if(f.ano>i.ano){return 1;}
    else if(f.ano==i.ano){
        if(f.mes>i.mes){return 1;}
        else if(f.mes==i.mes){
            if(f.dia>i.dia){return 1;}
            else if(f.dia==i.dia){return 0;}
            else{return -1;}
        }
        else{return -1;}
    }
    else{return -1;}
}


void switch_list_user(Task*h, Task*d, User*u, int max){
    Task*aux2;
    User* aux=display_select_user(u);
    aux->n_tarefas+=1;
    if(aux->n_tarefas > max){aux->n_tarefas-=1;goto END;}

    h=display_select(h,"mudar");
    while(d->next){d=d->next;}
    d->next=(Task*)malloc(sizeof(Task));
    d->next->next=NULL;
    ordena(h->next,d->next);

    fflush(stdin);

    printf("\nIntroduza o prazo(dd/mm/aa): ");
    //ERROR:

    scanf("%d/%d/%d",&d->prazo.dia,&d->prazo.mes,&d->prazo.ano);
    ///este if iria verificar se a data era valida
    //if( (d->prazo.dia > 31) || (d->prazo.dia < 0) || (d->prazo.mes > 12) || (d->prazo.mes < 0) || (d->prazo.ano > 2018) || (d->prazo.ano < 0) || (validade(u->l_task,d->prazo)==0)){printf("ERROR\n");goto ERROR;}
    d->next->prioridade= d->prazo.ano*10000 + d->prazo.mes*100 + d->prazo.dia;

    fflush(stdin);

    d->next->id_user=aux->id;
    transfer_to_l_user(aux->l_task,d->next);

    aux2=h->next;
    h->next=h->next->next;
    free(aux2);
    END:
        printf("");
}

void transfer_to_l_user(Task*u, Task*h){
    while(u->next){
        u=u->next;
    }
    u->next=(Task*)malloc(sizeof(Task));
    u=u->next;
    u->prioridade=h->prioridade;
    u->id=h->id;
    strncpy(u->tarefa, h->tarefa, TLENG);
    u->next=NULL;
}

void display_task_users(Task*u){
    while(u->next){
        u=u->next;
        u->prazo.dia=u->prioridade%100;
        u->prazo.mes= ((u->prioridade- u->prazo.dia)/100)%100;
        u->prazo.ano= (u->prioridade- u->prazo.dia)/10000;
        printf("------------\nID: %d\nTarefa: %sData: %d/%d/%d\n------------",u->id, u->tarefa, u->prazo.dia,u->prazo.mes,u->prazo.ano);
    }
}

void display_users_n_tasks(User*u){
    while(u->next){
        u=u->next;
        printf("\nNome: %s\nId: %d\nemail: %s\n\nTarefas:\n",u->nome,u->id,u->email);
        if(u->l_task->next != NULL){display_task_users(u->l_task);}
        else{printf("(null)\n");}
        printf("\n");
    }
}

Task* reset_everything(Task*h, char*fname){
    annihilation(h);
    reset_tasks(fname);
    h=inicia_lista();
    return h;
}

/*Task* anterior(Task*h, int id){
    while(h->next && h->next->id != id){
        h=h->next;
    }
    return h->next;
}

void switch_users(User*u, Task* doing, Task* done){
    User*de;
    ERROR:
    de=display_select_user(u);
    if(de->l_task->next==NULL){system("@cls||clear");goto ERROR;}

    Task*aux=display_select(u->l_task, "trasnferir");

    User*para;
    ERROR2:
    para=display_select_user(u);
    if(de==para){system("@cls||clear");goto ERROR2;}

    Task* aux2=anterior(doing, aux->id);
    if(aux2!=NULL){aux2->id_user=para->id;}
    else{aux2=anterior(done, aux->id);aux2->id_user=para->id;}
}*/

int main(){
    Task* to_do=inicia_lista();
        load_tasks(to_do,"to_do.txt");
    Task* doing=inicia_lista();
        load_tasks(doing,"doing.txt");
    Task* done=inicia_lista();
        load_tasks(done,"done.txt");
    User* l_users=inicia_lista_user();
    int max=load_max_tasks();


    MENU:
        load_users(l_users);
        load_tasks_user(l_users, doing, "doing.txt");
        load_tasks_user(l_users, done, "done.txt");
        system("@cls||clear");///CLEAR SCREEN
        int opcao;
        printf("\tMenu\n(0) Lista de Pessoas\n(1) Nova Tarefa em To Do\n(2) Muda de lista\n(3) Apagar Tarefas\n(4) Visualizar Listas de Tarefas\n(5) Redefinir Prioridade\n(6) APAGAR TUDO\n(9) Exit\n\nSelect: ");
        scanf("%d",&opcao);
        fflush(stdin);///RESOLVER O BUG DO NEW_TASK
        system("@cls||clear");

        switch(opcao){
            case(0):
                display_users_n_tasks(l_users);
                system("pause");
                break;///VIEW LISTs
///___________________________________________________________________________________________
            case(1):
                system("@cls||clear");///NEW TASK
                new_task(to_do);
                priorize_tasks(to_do);
                break;
///___________________________________________________________________________________________
            case(2):
                AGAIN:
                printf("\n\tDe que lista deseja trocar?:\n\n0-To Do\t\t1-Doing\t\t2-Done");
                scanf("%d",&opcao);
                system("@cls||clear");
                switch(opcao){
                    case(0):
                        if(empty_file("to_do.txt")==1){break;}
                        printf("\n\tDe To Do para: Doing");
                            switch_list_user(to_do,doing,l_users,max);
                            save_tasks(to_do,"to_do.txt");
                            save_tasks(doing,"doing.txt");
                        break;

                    case(1):
                        if(empty_file("doing.txt")==1){break;}
                        printf("\n\tDe Doing para?:\n\n0-To Do\t\t2-Done");
                        scanf("%d",&opcao);
                        if(opcao==0){
                            switch_list(doing,to_do);
                            save_tasks(to_do,"to_do.txt");
                            save_tasks(doing,"doing.txt");
                        }
                        else if(opcao==2){
                            switch_list(doing,done);
                            save_tasks(done,"done.txt");
                            save_tasks(doing,"doing.txt");
                        }
                        else{system("@cls||clear");goto AGAIN;}
                        break;

                    case(2):
                        if(empty_file("done.txt")==1){break;}
                        printf("\n\tDe Done para?:\n\n0-To Do\t\t1-Doing");
                        scanf("%d",&opcao);
                        if(opcao==0){
                            switch_list(done,to_do);
                            save_tasks(to_do,"to_do.txt");
                            save_tasks(done,"done.txt");
                        }
                        else if(opcao==1){
                            switch_list(done,doing);
                            save_tasks(done,"done.txt");
                            save_tasks(doing,"doing.txt");
                        }
                        else{system("@cls||clear");goto AGAIN;}
                        break;

                    default:system("@cls||clear");goto AGAIN;
                }
                break;
///___________________________________________________________________________________________
            case(3):
                AGAIN0:
                printf("\tDe que lista quer apagar?:\n\n0-To Do\t\t1-Doing\t\t2-Done");
                scanf("%d",&opcao);
                system("@cls||clear");
                switch(opcao){
                    case(0):printf("\n\tTo Do\n");
                        if(empty_file("to_do.txt")==1){break;}
                        delete_task(to_do);
                        save_tasks(to_do,"to_do.txt");
                        break;
                    case(1):printf("\n\tDoing\n");
                        if(empty_file("doing.txt")==1){break;}
                        delete_task(doing);
                        save_tasks(doing,"doing.txt");
                        break;
                    case(2):printf("\n\tDone\n");
                        if(empty_file("done.txt")==1){break;}
                        delete_task(done);
                        save_tasks(done,"done.txt");
                    break;
                    default:system("@cls||clear");goto AGAIN0;break;
                }

                break;
///___________________________________________________________________________________________
            case(4):///Test to display
                printf("\tTo Do\n");
                display_tasks(to_do,0);
                printf("\n\tDoing\n");
                display_tasks(doing,1);
                printf("\n\tDone\n");
                display_tasks(done,1);
                printf("\n");
                system("pause");
                break;
///___________________________________________________________________________________________
            case(5):system("@cls||clear");
                define_priority(to_do);
                priorize_tasks(to_do);
                save_tasks(to_do,"to_do.txt");
                break;
///___________________________________________________________________________________________
            case(6):
                to_do=reset_everything(to_do,"to_do.txt");
                doing=reset_everything(doing,"doing.txt");
                done=reset_everything(done,"done.txt");
                break;
            default:goto END;///EXIT
        }
    save_tasks(to_do,"to_do.txt");
    goto MENU;
    END:

    return 0;
}
