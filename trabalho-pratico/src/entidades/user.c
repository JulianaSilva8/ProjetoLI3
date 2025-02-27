#include "../../include/user.h"
#include "../../include/gestor_music.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>



struct Historico {
    char musicid[100][9];
    char timestamp[100][20];
    char duration[100][9];
    int size;
    struct Historico* prox;
};

struct User {
    char* username;
    char* email;
    char* first_name;
    char* last_name;
    char* data_nascimento;
    char* pais;
    char* subscriçao;
    char* gostos_musicas;
    struct Historico historico;
    int gostos_musicas_count;
    int gostos_musicas_capacidade;
};

// DAR FREE DEPOIS DE INVOCAR GETTERS
// Getters


void getDataOnMatrix(char ***matrix, const User* user) {
    // Aloca memória para a matriz de strings (6 campos do User)
    *matrix = (char**)malloc(5 * sizeof(char*));
    // Copia os dados do usuário para a matriz
    (*matrix)[0] = (char*)malloc((strlen(user->email) + 1) * sizeof(char));
    strcpy((*matrix)[0], user->email);

    (*matrix)[1] = (char*)malloc((strlen(user->first_name) + 1) * sizeof(char));
    strcpy((*matrix)[1], user->first_name);

    (*matrix)[2] = (char*)malloc((strlen(user->last_name) + 1) * sizeof(char));
    strcpy((*matrix)[2], user->last_name);

    int age = idade(user->data_nascimento);
    char str[20];
    sprintf(str, "%d", age);
    (*matrix)[3] = (char*)malloc((strlen(str) +1 * sizeof(char)));
    strcpy((*matrix)[3], str);

    int t = strlen(user->pais);
    (*matrix)[4] = (char*)malloc((t + 2) * sizeof(char)); // +2 para '\n' e '\0'
    strncpy((*matrix)[4], user->pais, t);
    (*matrix)[4][t] = '\n'; // Adiciona '\n' ao final
    (*matrix)[4][t + 1] = '\0'; // Adiciona o caractere nulo ao final


}
const Historico* getHistoricoAtIndex(const Historico* historico, int* index) {
    while (historico != NULL && *index >= 100) {
        historico = historico->prox;
        *index -= 100;
    }
    return historico;
}


char* getMusicId_Historico(const User* user, int index) {
    const Historico* historico = getHistoricoAtIndex(&user->historico, &index);
    if (historico == NULL || index >= historico->size) {
        return NULL;
    }
    return strdup(historico->musicid[index]);
}
char* getTimestamp_Historico(const User* user, int index) {
    const Historico* historico = getHistoricoAtIndex(&user->historico, &index);
    if (historico == NULL || index >= historico->size) {
        return NULL;
    }
    return strdup(historico->timestamp[index]);
}
char* getDuration_Historico(const User* user, int index) {
    const Historico* historico = getHistoricoAtIndex(&user->historico, &index);
    if (historico == NULL || index >= historico->size) {
        return NULL;
    }
    return strdup(historico->duration[index]);
}
int getHistoricoSize(const User* user) {
    int size = 0;
    const Historico* historico = &user->historico;
    while (historico != NULL) {
        size += historico->size;
        historico = historico->prox;
    }
    return size;
}
 

char* getUsername(const User* user) {
    return strdup(user->username);
}

char* getEmail(const User* user) {
    return strdup(user->email);
}

char* getFirstName(const User* user) {
    return strdup(user->first_name);
}

char* getLastName(const User* user) {
    return strdup(user->last_name);
}

char* getDataNascimento(const User* user) {
    return strdup(user->data_nascimento);
}

char* getPais(const User* user) {
    return strdup(user->pais);
}

char* getSubscriçao(const User* user) {
    return strdup(user->subscriçao);
}

char* getListaMusicas(const User* user) {
    return strdup(user->gostos_musicas);
}

// Setters
void setHistory(User* user, History* history) {
    Historico* current = &user->historico;
    while (current->prox != NULL) {
        current = current->prox;
    }
    if (current->size >= 100) {
        current->prox = (Historico*)malloc(sizeof(struct Historico));
       
        current = current->prox;
        current->size = 0;
        current->prox = NULL;
    }

    // Get values from History
    char* musicId = getMusicId_History(history);
    char* duration = getDuration_History(history);
    char* timestamp = getTimestamp_History(history);


    
    strcpy(current->musicid[current->size], musicId);
    
    
    
    strcpy(current->duration[current->size], duration);
    
   
    strcpy(current->timestamp[current->size], timestamp);
    
    current->size++;
    
    // Free temporary values
    free(musicId);
    free(duration); 
    free(timestamp);
}


void setUsername(User* user, const char* username) {
    free(user->username);
    user->username = strdup(username);
}

void setEmail(User* user, const char* email) {
    free(user->email);
    user->email = strdup(email);
}

void setFirstName(User* user, const char* firstName) {
    free(user->first_name);
    user->first_name = strdup(firstName);
}

void setLastName(User* user, const char* lastName) {
    free(user->last_name);
    user->last_name = strdup(lastName);
}

void setDataNascimento(User* user, const char* dataNascimento) {
    free(user->data_nascimento);
    user->data_nascimento = strdup(dataNascimento);
}

void setPais(User* user, const char* pais) {
    free(user->pais);
    user->pais = strdup(pais);
}

void setSubscriçao(User* user, const char* subscriçao) {
    free(user->subscriçao);
    user->subscriçao = strdup(subscriçao);
}

User* criaUser() {
    User* user = (User*)malloc(sizeof(User));
    if (user == NULL) {
        fprintf(stderr, "Erro\n");
        exit(1);
    }
    user->username = NULL;
    user->email = NULL;
    user->first_name = NULL;
    user->last_name = NULL;
    user->data_nascimento = NULL;
    user->pais = NULL;
    user->subscriçao = NULL;
    user->gostos_musicas = NULL;
    user->gostos_musicas_count = 0;
    user->gostos_musicas_capacidade = 0;
    user->historico.size = 0;
    user->historico.prox = NULL;
    
    return user;
}

void freeUser(User* user) {
    free(user->username);
    free(user->email);
    free(user->first_name);
    free(user->last_name);
    free(user->data_nascimento);
    free(user->pais);
    free(user->subscriçao);
    free(user->gostos_musicas);

    Historico* current = &user->historico;

    free(user);
}

int emailValida(const char* email) {
    const char* arroba =strchr(email, '@');
    if (arroba ==NULL) return 0; // @ n existe
    if (arroba ==email) return 0; // Username vazio
    if (arroba[1] =='\0') return 0; // dominio vazio

    // ver se apenas existe um '@'
    if (strchr(arroba+1, '@') != NULL) return 0; //mais do que um '@'

    // validar username
    const char* username =email;
    const char* p =username;
    while (p < arroba) {
        if (!((islower(*p)) || (isdigit(*p)))) {
            return 0; // char invalido no username
        }
        p++;
    }
    if (p==username) return 0; // Username vazio

    // validar dominio
    const char* dominio = arroba+1;
    const char* ponto = strchr(dominio,'.');
    if (ponto ==NULL) return 0; // n tem '.' no dominio
    if (ponto ==dominio) return 0; // lstring esta vazia
    if (ponto[1] =='\0') return 0; // rstring esta vazia

    // checkar se so tem um '.'
    if (strchr(ponto+1,'.')!= NULL) return 0; // tem mais do que um  '.'

    // validar lstring
    p=dominio;
    while (p < ponto) {
        if (!islower((unsigned char)*p)) {
            return 0; // char invalido na lstring
        }
        p++;
    }
    if (p==dominio) return 0; // lstring esta vazia

    // validar rstring
    const char* rstring = ponto+ 1;
    int rstring_length = 0;
    p = rstring;
    while (*p!='\0') {
        if (!islower((unsigned char)*p)) {
            return 0; // char invalido na rstring
        }
        rstring_length++;
        p++;
    }
    if (rstring_length<2 || rstring_length>3) return 0; // tamanho errado na rstring

    return 1;
}

int subValida(const char* sub) {
    // devolve false se a subscrição não for normal ou premium
    if (strcmp(sub, "normal") == 0 || strcmp(sub, "premium") == 0) {
        return 1;
    }
    return 0;
}

int listaValida(const char* lista, gestorMusic* hashTable) {
    char* trim = strdup(lista);
    if (!trim) return 0;

    // remover []
    if (trim[0] == '[' && trim[strlen(trim) - 1] == ']') {
        trim[strlen(trim) - 1] = '\0';
        memmove(trim, trim + 1, strlen(trim));
    } else {
        free(trim);
        return 0;
    }

    // checkar cada id da lista de musicas
    char* token = strtok(trim, ",");
    while (token != NULL) {
        // remover espaços e ' '
        while (isspace((unsigned char)*token) || *token == '\'') token++;
        char* end = token + strlen(token) - 1;
        while (end > token && (isspace((unsigned char)*end) || *end == '\'')) end--;
        end[1] = '\0';

        // checkar se a musica existe
        if (procuraMusic(hashTable, token) == NULL) {
            free(trim);
            return 0;
        }
        token = strtok(NULL, ",");
    }
    free(trim);
    return 1;
}


int dataValida(const char* data) {

    if (strlen(data) != 10) return 0; // tamanho tem de ser 10
    // posições 4 e 7 têm de ser '/' e as outras digitos
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (data[i]!= '/') return 0;
        } else {
            if (!isdigit((unsigned char)data[i])) return 0;
        }
    }
    // extrair ano,mes e dia
    char anoStr[5], mesStr[3],diaStr[3];
    strncpy(anoStr,data, 4);
    anoStr[4]= '\0';
    strncpy(mesStr, data+5,2);
    mesStr[2] ='\0';
    strncpy(diaStr, data+8,2);
    diaStr[2]= '\0';

    int ano =atoi(anoStr);
    int mes =atoi(mesStr);
    int dia =atoi(diaStr);

    // range do mes e dia
    if (mes<1 || mes>12) return 0;
    if (dia<1 || dia>31) return 0;

    // data n pode ser mais recente que 2024/09/09
    if (ano>2024) return 0;
    if (ano == 2024) {
        if (mes>9) return 0;
        if (mes==9 && dia>9) return 0;
    }

    return 1;
}

void userField(User* user, int index, const char* value) {
    char* trim = strdup(value);
    // verificar as aspas
    if (trim[0] == '"' && trim[strlen(trim) - 1] == '"') {
        trim[strlen(trim) - 1] = '\0'; // remove as últimas aspas
        memmove(trim, trim + 1, strlen(trim)); // shift para a esquerda para remover as primeiras aspas
    }

    switch (index) {
        case 0:
            user->username = strdup(trim);
            break;
        case 1:
            user->email = strdup(trim);
            break;
        case 2:
            user->first_name = strdup(trim);
            break;
        case 3:
            user->last_name = strdup(trim);
            break;
        case 4:
            user->data_nascimento = strdup(trim);
            break;
        case 5:
            user->pais = strdup(trim);
            break;
        case 6:
            user->subscriçao = strdup(trim);
            break;
        case 7:
            user->gostos_musicas = strdup(trim);
            break;
        default:
            break;
    }
    free(trim);
}

int idade(const char* data_nascimento) {
    int anoNasc = 0, mesNasc = 0, diaNasc = 0;
    sscanf(data_nascimento, "%d/%d/%d", &anoNasc, &mesNasc, &diaNasc);

    int anoAtual = 2024;
    int mesAtual = 9;
    int diaAtual = 9;

    int idade = anoAtual - anoNasc;

    if (mesAtual < mesNasc || (mesAtual == mesNasc && diaAtual < diaNasc)) {
        idade--;
    }

    return idade;
}

void printUser(User* user, int n) {
    char filename[64];
    FILE *cmd;

    sprintf(filename, "resultados/command%d_output.txt", n);
    cmd = fopen(filename, "w");
    if (user == NULL) {
        fprintf(cmd, "\n");
        fclose(cmd);
        return;
    }

    int age = idade(user->data_nascimento);
    char str[20];
    sprintf(str, "%d", age);
    fprintf(cmd, "%s;%s;%s;%s;%s\n", user->email, user->first_name, user->last_name, str, user->pais);
    fclose(cmd);
}

void erro(User* user,int flag,char* header) {
    char filename[64];
    FILE *cmd;

    sprintf(filename, "resultados/users_errors.csv");
    cmd = fopen(filename, "a");
    if (flag == 0) fprintf(cmd, "%s\n",header);
    if (user == NULL) {
        fprintf(cmd, "\n");
        fclose(cmd);
        return;
    }

    int age = idade(user->data_nascimento);
    char str[20];
    sprintf(str, "%d", age);
    fprintf(cmd, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n", user->username, user->email, user->first_name, user->last_name, user->data_nascimento, user->pais,user->subscriçao,user->gostos_musicas);
    fclose(cmd);
}