//imports files
#include "structs.h"

//define
#define WIDTH_FN 20
#define HEIGHT_FN 4

//create variables
int x, y, option; int highlight = 1; int choice = 0;

char *choices[] = {"   Cadastrar      ", "   Exibir         ", "   Atualizar      ", "   Apagar         ", "   Sair           "};
int n_choices = sizeof(choices)/sizeof(char *);


void show_menu(WINDOW *window, int highlight, char *choices[], int n_choices, int x, int y, int asciiw, int asciih){
    box(window, asciiw, asciih);
    
    for (int i=0; i<n_choices; i++){
        if (highlight == i+1){ 
            wattron(window, A_REVERSE);
            mvwprintw(window, y, x, "%s", choices[i]);
            wattroff(window, A_REVERSE);}
        else {mvwprintw(window, y, x, "%s", choices[i]);} y++;}
    
    wrefresh(window);}


char *writer(WINDOW *window, char *node_char, char *text, int x, int y){   
    attron(COLOR_PAIR(1)); mvprintw(0, 44, "Preencha as informações abaixo."); attroff(COLOR_PAIR(1));
    mvchgat(0, 0, -1, A_BLINK, 1, NULL);
    attron(COLOR_PAIR(2)); mvprintw(30, 33, " Pressione a tecla: Enter, para prosseguir no formulário. "); attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3)); mvprintw(y, x, "%s ", text); attroff(COLOR_PAIR(3));
    
    attron(COLOR_PAIR(1)); getstr(node_char);
    while (strcasecmp(node_char, "") == 0){
        mvprintw(28, 44, " Preencha o campo para prosseguir. "); getstr(node_char);}
    mvprintw(y, x, "%s %s", text, node_char); getch(); attroff(COLOR_PAIR(1));

    highlight = 1; choice = 0; refresh(); return node_char;}


int quit(char *text, int textx, int texty){
    WINDOW *window_local = newwin(HEIGHT_FN, WIDTH_FN, y, x); keypad(window_local, TRUE);

    choice = 0; highlight = 1; char *choices[] = {"       Sim        ", "       Não        "};
    int n_choices = sizeof(choices)/sizeof(char *);

    while (1){
        clear(); attron(COLOR_PAIR(3)); mvprintw(texty, textx, text); attroff(COLOR_PAIR(3));
        mvchgat(0, 0, -1, A_BLINK, 3, NULL);
        attron(COLOR_PAIR(2)); mvprintw(30, 26, "Pressione as setas: para cima e para baixo, para selecionar um opção."); attroff(COLOR_PAIR(2));
        refresh(); show_menu(window_local, highlight, choices, n_choices, 1, 1, 32, 0);

        option = wgetch(window_local);
            switch (option){
                    case KEY_UP:
                        wrefresh(window_local); refresh(); 
                        if (highlight == 1){highlight = n_choices;}
                        else {highlight--;} break;

                    case KEY_DOWN:
                        wrefresh(window_local); refresh(); 
                        if (highlight == n_choices){highlight = 1;}
                        else {highlight++;} break;

                    case 10:
                        choice = highlight; break;}

            switch (choice){
                case 1:
                    return 1;
                case 2:
                    return 0;}}}