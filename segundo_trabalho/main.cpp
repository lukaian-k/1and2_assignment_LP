//imports files
#include "fuctions_crud.h"

//define
#define WIDTH 20
#define HEIGHT 7

//declare fuctions
//functions_crud.h
void board_size();
void add(Node *new_node);
bool form(WINDOW *window, Node *aux, bool show, const char *text, int textx, int texty, int color_tag, bool delete_check, bool update_check);
void sign_up(WINDOW *window);
Node *search(FILE *fp, int color1, int color2, const char *text, int textx, int texty, const char *text2, int textx2, int texty2);
void show(WINDOW *window);
void update(WINDOW *window);
void delete_board(WINDOW *window);
//functions_ncurses.h
void show_menu(WINDOW *window, int highlight, const char *choices[], int n_choices, int x, int y, int asciiw, int asciih);
string writer(WINDOW *window, char *node_char, const char *text, int x, int y);
bool quit(const char *text, int textx, int texty);


int main(int argc, char **argv){
    initscr(); clear(); noecho(); cbreak(); start_color();
    
    //create file
    ofstream fp("database.bin", ios::app); fp.close();

    //create colors
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_RED);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_WHITE);

    x = (122 - WIDTH)/2; y = (14 - HEIGHT)/2;
    WINDOW *window = newwin(HEIGHT, WIDTH, y, x); keypad(window, TRUE);
    
    while (true){
        clear(); board_size();
        attron(COLOR_PAIR(1)); mvprintw(0, 33, "Bem-vindo ao Cadastro de Bancas do TCC da UFC - Russas!"); attroff(COLOR_PAIR(1));
        mvchgat(0, 0, -1, A_BLINK, 1, NULL);
        attron(COLOR_PAIR(2)); mvprintw(30, 26, "Pressione as setas: para cima e para baixo, para selecionar um opção."); attroff(COLOR_PAIR(2));
        refresh(); show_menu(window, highlight, choices, n_choices, 1, 1, 32, 0);
        
        option = wgetch(window);
        switch (option){
                case KEY_UP:
                    wrefresh(window); refresh(); 
                    if (highlight == 1){highlight = n_choices;}
                    else {highlight--;} break;

                case KEY_DOWN:
                    wrefresh(window); refresh(); 
                    if (highlight == n_choices){highlight = 1;}
                    else {highlight++;} break;

                case 10:
                    choice = highlight; break;}

        switch (choice){
            case 1:
                sign_up(window); break;
            case 2:
                show(window); break;
            case 3:
                update(window); break;
            case 4:
                delete_board(window); break;
            case 5:
                if (quit("Deseja finalizar o programa?", 46, 0) == true){
                    clear(); attron(COLOR_PAIR(1)); mvprintw(3, 44, "Programa finalizado com sucesso!"); attroff(COLOR_PAIR(1));
                    attron(COLOR_PAIR(2)); mvprintw(30, 39, "Pressione qualquer tecla para prosseguir."); attroff(COLOR_PAIR(2));
                    clrtoeol(); refresh(); getch(); endwin(); exit(1);}
                else {highlight = 1; choice = 0;}}}}