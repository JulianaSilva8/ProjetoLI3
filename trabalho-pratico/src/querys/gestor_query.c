#include <glib.h>
#include "../../include/gestor_user.h"
#include "../../include/gestor_music.h"
#include "../../include/gestor_artist.h"
#include "../../include/q1.h"
#include "../../include/q2.h"
#include "../../include/q3.h"
#include "../../include/q4.h"
#include "../../include/q6.h"
#include "../../include/q5.h"

void gestor_query(char* input,int line1,gestorUser* hashTableusers,gestorMusic* hashTablemusics, gestorArtist* hashTableartists,GTree* arvore, GTree* tree_data, void** matriz_q5){
    switch (input[0]){
        case '1':
        query1(input,line1,hashTableusers,hashTableartists);
        break;

        case '2':
        query2(input, line1, hashTableartists, hashTablemusics);
        break;

        case '3':
        q3(line1, input, arvore);
        break;

        case '4':
        query4(input,line1,hashTableartists, tree_data);
        break;

        case '5':
        query5(matriz_q5,hashTableusers, input, line1);
        break;

        case '6':
        query6(input,line1,hashTableusers,hashTablemusics);
        break;
    }
}   