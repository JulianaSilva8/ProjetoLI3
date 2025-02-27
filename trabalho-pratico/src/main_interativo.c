#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <string.h>
#include <ncurses.h>
#include <dirent.h>
#include "../include/main.h"
#include "../include/main_interativo.h"

void exibir_mensagem(WINDOW* win, const char* mensagem, int color_pair) {
    wattron(win, COLOR_PAIR(color_pair));
    wprintw(win, "%s\n", mensagem);
    wattroff(win, COLOR_PAIR(color_pair));
    wrefresh(win);
}

void clear_input_line(WINDOW* win, int y) {
    wmove(win, y, 1);
    wclrtoeol(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, "[ Input ]");
}

void get_input_with_prompt(WINDOW* win, char* buffer, const char* prompt, int y, int color) {
    wmove(win, y, 1);
    wclrtoeol(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, "[ Input ]");
    wattron(win, COLOR_PAIR(color));
    mvwprintw(win, y, 2, "%s", prompt);
    wattroff(win, COLOR_PAIR(color));
    wmove(win, y, strlen(prompt) + 3);
    wrefresh(win);
    wgetnstr(win, buffer, 255);
}

int modo_interativo(WINDOW* input_win, WINDOW* results_win) {
    scrollok(input_win, TRUE);
    scrollok(results_win, TRUE);
    keypad(results_win, TRUE);
    
    FILE* users = fopen("input_interativo.txt", "w");
    if (!users) {
        exibir_mensagem(input_win, "Erro ao criar arquivo de input!", 2);
        return -1;
    }

    char input[256];
    char caminho[256];
    char query_num[2];
    char output_file[256];
    int flag = 0;
    int command_count = 0;
    int input_y = 1;

    // Get dataset path
    while(!flag) {
        get_input_with_prompt(input_win, caminho, "Indique o caminho do dataset: ", input_y, 3);
        input_y += 2;
        DIR* dir = opendir(caminho);
        if (dir) {
            closedir(dir);
            flag = 1;
        } else {
            exibir_mensagem(input_win, "Caminho inválido!", 2);
        }
    }

    // Command input loop
    while(1) {
        if (input_y > getmaxy(input_win) - 3) {
            wclear(input_win);
            box(input_win, 0, 0);
            mvwprintw(input_win, 0, 2, "[ Input ]");
            input_y = 1;
        }

        get_input_with_prompt(input_win, query_num, "Insira o número da query (0 para sair): ", input_y, 3);
        input_y += 1;
        
        if (query_num[0] == '0') break;

        size_t len = strlen(query_num);
        char base_num = query_num[0];
        
        if (len > 2 || !isdigit(base_num) || 
            (len == 2 && query_num[1] != 'S') ||
            (base_num < '1' || base_num > '6')) {
            exibir_mensagem(input_win, "Query inválida! Use números de 1 a 6, opcionalmente seguidos de S", 2);
            continue;
        }

        get_input_with_prompt(input_win, input, "Insira o comando da query: ", input_y, 3);
        input_y += 2;

        char comando[256];
        if (len == 2 && query_num[1] == 'S') {
            char base_query[2] = {query_num[0], '\0'};  
            snprintf(comando, sizeof(comando), "%sS %s", base_query, input);
        } else {
            snprintf(comando, sizeof(comando), "%s %s", query_num, input);
        }
        fprintf(users, "%s\n", comando);
        command_count++;
    }

    fclose(users);

    // Process and display results
    if (command_count > 0) {
        wmove(input_win, input_y, 2);
        wattron(input_win, COLOR_PAIR(3));
        wprintw(input_win, "A processar comandos...");
        wattroff(input_win, COLOR_PAIR(3));
        wrefresh(input_win);
        input_y += 2;
        
        int ret = process_input(caminho, "input_interativo.txt");
        
        // Show results menu
        wclear(results_win);
        box(results_win, 0, 0);
        mvwprintw(results_win, 0, 2, "[ Resultados ]");
        mvwprintw(results_win, 1, 2, "Resultados disponíveis (1-%d)", command_count);
        mvwprintw(results_win, 2, 2, "Digite o número do resultado que deseja ver (0 para sair):");
        wrefresh(results_win);
        
        // Result navigation loop
        while(1) {
            if (input_y > getmaxy(input_win) - 3) {
        wclear(input_win);
        box(input_win, 0, 0);
        mvwprintw(input_win, 0, 2, "[ Input ]");
        input_y = 1;
    }

            char choice[3];
            get_input_with_prompt(input_win, choice, "Escolha o resultado: ", input_y, 3);
            
            if (choice[0] == '0') break;
            
            int result_num = atoi(choice);
            if (result_num >= 1 && result_num <= command_count) {
                wclear(results_win);
                box(results_win, 0, 0);
                mvwprintw(results_win, 0, 2, "[ Resultados ]");
                
                snprintf(output_file, sizeof(output_file), "resultados/command%d_output.txt", result_num);
                FILE* output = fopen(output_file, "r");
                if (output) {
                    int display_y = 1;
                    
                    char result_msg[256];
                    snprintf(result_msg, sizeof(result_msg), "=== Resultado do comando %d ===", result_num);
                    wmove(results_win, display_y++, 2);
                    wattron(results_win, COLOR_PAIR(5));
                    wprintw(results_win, "%s", result_msg);
                    wattroff(results_win, COLOR_PAIR(5));
                    
                    char line[256];
                    while (fgets(line, sizeof(line), output)) {
                        if (line[strlen(line)-1] == '\n') 
                            line[strlen(line)-1] = '\0';
                        
                        wmove(results_win, display_y++, 4);
                        wattron(results_win, COLOR_PAIR(4));
                        wprintw(results_win, "%s", line);
                        wattroff(results_win, COLOR_PAIR(4));
                    }
                    fclose(output);
                    
                    mvwprintw(results_win, getmaxy(results_win)-1, 2, 
                             "Escolha outro resultado ou digite 0 para sair");
                } else {
                    wmove(results_win, 1, 2);
                    wattron(results_win, COLOR_PAIR(2));
                    wprintw(results_win, "Erro ao abrir resultado %d", result_num);
                    wattroff(results_win, COLOR_PAIR(2));
                }
                wrefresh(results_win);
            } else {
                exibir_mensagem(input_win, "  Número de resultado inválido!", 2);
            }
            input_y += 2;
        }
    }

    if (input_y > getmaxy(input_win) - 3) {
        wclear(input_win);
        box(input_win, 0, 0);
        mvwprintw(input_win, 0, 2, "[ Input ]");
        input_y = 1;
    }
    wmove(input_win, input_y, 2);
    wattron(input_win, COLOR_PAIR(1));
    wprintw(input_win, "Pressione qualquer tecla para sair...");
    wattroff(input_win, COLOR_PAIR(1));
    wrefresh(input_win);
    wgetch(input_win);

    return 0;
}

int main_interativo() {
    initscr();            
    cbreak();
    echo();
    start_color();
    use_default_colors();
    
    init_pair(1, COLOR_GREEN, -1);   // Success messages
    init_pair(2, COLOR_RED, -1);     // Errors
    init_pair(3, COLOR_BLUE, -1);    // Input prompts
    init_pair(4, COLOR_YELLOW, -1);  // Results
    init_pair(5, COLOR_CYAN, -1);    // Headers

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    WINDOW* input_win = newwin(max_y/2, max_x, 0, 0);
    WINDOW* results_win = newwin(max_y/2, max_x, max_y/2, 0);
    
    box(input_win, 0, 0);
    box(results_win, 0, 0);
    
    mvwprintw(input_win, 0, 2, "[ Input ]");
    mvwprintw(results_win, 0, 2, "[ Results ]");
    
    scrollok(input_win, TRUE);
    scrollok(results_win, TRUE);
    
    refresh();
    wrefresh(input_win);
    wrefresh(results_win);
    
    int ret = modo_interativo(input_win, results_win);

    delwin(results_win);
    delwin(input_win);
    endwin();

    return ret;
}