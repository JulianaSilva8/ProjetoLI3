#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include "../../include/history.h"

struct History {
    char* historyId;
    char* user_id;
    char* music_id;
    char* timestamp;
    char* duration;
    char* platform;
};

char* getUserid_History(History* history) {
    return strdup(history->user_id);
}

char* getHistoryId(const History* history) {
    return strdup(history->historyId);
}

char* getMusicId_History(History* history) {
    return strdup(history->music_id);
}

char* getDuration_History(History* history) {
    return strdup(history->duration);
}

char* getTimestamp_History(History* history) {
    return strdup(history->timestamp);
}

char* getPlatform_History(History* history) {
    return strdup(history->platform);
}

History* criaHistory() {
    History* history = (History*)malloc(sizeof(History));
    if (history == NULL) {
        fprintf(stderr, "Erro\n");
        exit(1);
    }
    history->historyId = NULL;
    history->user_id = NULL;
    history->music_id = NULL;
    history->timestamp = NULL;
    history->duration = NULL;
    history->platform = NULL;
    return history;
}

void freeHistory(History* historical) {
    free(historical->historyId);
    free(historical->user_id);
    free(historical->music_id);
    free(historical->timestamp);
    free(historical->duration);
    free(historical->platform);
    free(historical);
}

void historyField(History* history, int index, const char* value) {
    char* trim = strdup(value);
    // Verifica as aspas
    if (trim[0] == '"' && trim[strlen(trim) - 1] == '"') {
        trim[strlen(trim) - 1] = '\0'; // Remove as últimas aspas
        memmove(trim, trim + 1, strlen(trim)); // Shift para a esquerda para remover as primeiras aspas
    }

    switch (index) {
        case 0:
            history->historyId = strdup(trim);
            break;
        case 1:
            history->user_id = strdup(trim);
            break;
        case 2:
            history->music_id = strdup(trim);
            break;
        case 3:
            history->timestamp = strdup(trim);
            break;
        case 4:
            history->duration = strdup(trim);
            break;
        case 5:
            history->platform = strdup(trim);
            break;
        default:
            break;
    }
    free(trim);
}

void erro_history(History* history,int flag,char* header) {
    char filename[64];
    FILE *cmd;

    sprintf(filename, "resultados/history_errors.csv");
    cmd = fopen(filename, "a");
    if (flag == 0) fprintf(cmd, "%s\n",header);
    if (history == NULL) {
        fprintf(cmd, "\n");
        fclose(cmd);
        return;
    }

    fprintf(cmd, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
    history->historyId, history->user_id, history->music_id, history->timestamp, history->duration, history->platform);
    fclose(cmd);
}