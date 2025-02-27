#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "../include/utils.h"

void freeMatrix(char **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int durationToseconds(const char* duration) {
    int horas, minutos, segundos;
    if (sscanf(duration, "%2d:%2d:%2d", &horas, &minutos, &segundos) != 3) {
        return -1;
    }

    if (horas < 0 || horas > 99 || minutos < 0 || minutos > 59 || segundos < 0 || segundos > 59) {
        return -1;
    }

    return horas * 3600 + minutos * 60 + segundos;
}

/**
 * Converte uma data para dias desde 1970/01/01.
 */
static int dateToDays(int year, int month, int day) {
    static int diasPorMes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int anos = year - 1970;
    int dias = anos * 365 + (anos + 1)/4 - (anos + 69)/100 + (anos + 369)/400;

    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) {
        diasPorMes[1] = 29;
    } else {
        diasPorMes[1] = 28;
    }

    for (int i = 0; i < month; i++) {
        dias += diasPorMes[i];
    }

    dias += day - 1;
    return dias;
}

/**
 * Calcula o dia da semana de uma data.
 */
int dayOfWeek(int year, int month, int day) {
    int totalDias = dateToDays(year, month, day);
    int wday = (totalDias + 4) % 7;
    return wday < 0 ? wday + 7 : wday;
}

int calculateDateDifference(const char* dataStr) {
    int yy, mm, dd;
    int refY = 2024, refM = 8, refD = 9;
    sscanf(dataStr, "%d/%d/%d", &yy, &mm, &dd);
    yy = yy;
    mm = mm - 1;

    int entradaDias = dateToDays(yy, mm, dd);
    int wday = dayOfWeek(yy, mm, dd);
    entradaDias -= wday;
    int refDias = dateToDays(refY, refM, refD);
    int diff = refDias - entradaDias;

    return (int)floor(diff / 7.0);
}

char** parse_Artist_string(char* artists_str) {
    if (!artists_str || artists_str[0] != '[' ||
        artists_str[strlen(artists_str)-1] != ']') {
        return NULL;
    }

    int num_artists = 0;
    for (char* p = artists_str; *p; p++) {
        if (*p == '\'') num_artists++;
    }
    num_artists /= 2;

    char** result = malloc((num_artists + 1) * sizeof(char*));
    char* current = artists_str + 1;
    int artist_idx = 0;

    while (*current && artist_idx < num_artists) {
        while (*current && *current != '\'') current++;
        if (!*current) break;
        current++;

        result[artist_idx] = malloc((8 + 1) * sizeof(char));
        strncpy(result[artist_idx], current, 8);
        result[artist_idx][8] = '\0';

        artist_idx++;
        current += 8 + 1;
    }

    result[num_artists] = NULL;
    return result;
}

int duracao_to_seconds(const char* duracao) {
    int horas, minutos, segundos;
    sscanf(duracao, "%02d:%02d:%02d", &horas, &minutos, &segundos);
    return (horas * 3600) + (minutos * 60) + segundos;
}
