//imports files
#include "fuctions_ncurses.h"

//define
#define WIDTH_FC 20
#define HEIGHT_FC 5

//create variables
int fp_size, pos_board;


//fuctions

int board_size(){
    FILE *fp = fopen("./database.bin", "r");
    Node *node = malloc(sizeof(Node)); int i = 0;

    while (fread(node, sizeof(Node), 1, fp)){
        if (node->active == 0){i++;}}
    
    fseek(fp, 0, SEEK_END);
    fp_size = ftell(fp)/sizeof(Node)-i; pos_board = 0;
    fclose(fp); free(node);}


int add(Node *new){
    FILE *fp = fopen("./database.bin", "a");
    if (fp == NULL){
        clear(); attron(COLOR_PAIR(6)); mvprintw(3, 45, " Erro ao abrir o arquivo: database.bin "); attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(5)); mvprintw(30, 38, " Pressione qualquer tecla para encerrar o programa.\n "); attroff(COLOR_PAIR(5)); getch(); return 1;}
    
    else if (fwrite(new, sizeof(Node), 1, fp) != 1){
        clear(); attron(COLOR_PAIR(6)); mvprintw(3, 44, " Erro ao gravar o conteúdo no arquivo: database.bin "); attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(5)); mvprintw(30, 38, " Pressione qualquer tecla para encerrar o programa.\n "); attroff(COLOR_PAIR(5)); getch(); fclose(fp); return 1;}
    
    fclose(fp);}


int form(WINDOW *window, Node *aux, int show, char *text, int textx, int texty, int color_tag, int delete_check, int update_check){
    if (show != 1){
        int answered_board, answered_student, answered_evaluators, answered_advisor = 0;
        choice = 0; highlight = 1; char *choices[] = {"   Banca          ", "   Aluno          ", "   Avaliadores    ", "   Instrutor      ", "   Salvar         "};
        n_choices = sizeof(choices)/sizeof(char *);
        
        while (1) {
            clear(); attron(COLOR_PAIR(1)); mvprintw(texty, textx, text); attroff(COLOR_PAIR(1));
            mvchgat(0, 0, -1, A_BLINK, 1, NULL);
            attron(COLOR_PAIR(2)); mvprintw(30, 26, " Pressione as setas: para cima e para baixo, para selecionar um opção. "); attroff(COLOR_PAIR(2));
            refresh(); show_menu(window, highlight, choices, n_choices, 1, 1, 32, 0);

            option = wgetch(window);
            switch (option){
                    case KEY_UP:
                        if (highlight == 1){highlight = n_choices;}
                        else {highlight--;} break;

                    case KEY_DOWN:
                        if (highlight == n_choices){highlight = 1;}
                        else {highlight++;} break;

                    case 10:
                        choice = highlight; break;}
            
            
            switch (choice){
                case 1:
                    clear();
                    FILE *fp = fopen("./database.bin", "r");
                    Node *node = malloc(sizeof(Node));

                    if (!fp){
                        free(node); clear(); attron(COLOR_PAIR(6)); mvprintw(3, 45, " Erro ao abrir o arquivo: database.bin "); attroff(COLOR_PAIR(6));
                        attron(COLOR_PAIR(5)); mvprintw(30, 38, " Pressione qualquer tecla para encerrar o programa.\n "); attroff(COLOR_PAIR(5)); getch();}
                    
                    else {
                        int stop = 0;
                        while (stop != 1){
                            rewind(fp);
                            char *title = writer(window, aux->board.title, " Nome da Banca:", 20, 3);
                            while (feof(fp) == 0){
                                fread(node, sizeof(Node), 1, fp);

                                if (strcasecmp(title, node->board.title) == 0 && node->active == 1){
                                    attron(COLOR_PAIR(6)); mvprintw(28, 13, " Banca já existente! Utilize outro nome para a banca. Pressione a tecla: Enter, para prosseguir..."); attroff(COLOR_PAIR(6));
                                    getch(); clear(); stop = 0; break;}
                                else {stop = 1;}}} fclose(fp); free(node);}
                    
                    writer(window, aux->board.summary, " Sobre:", 20, 5);
                    writer(window, aux->board.time, " Horário:", 20, 7);
                    writer(window, aux->board.local, " Local:", 20, 9);
                    writer(window, aux->board.attendance, " Frequência:", 20, 11);
                    answered_board = 1; break;

                case 2:
                    clear();
                    writer(window, aux->student.person.name, "Nome do aluno:", 20, 3);
                    writer(window, aux->student.person.email, "E-mail do aluno:", 20, 5);
                    writer(window, aux->student.registration, "Matrícula:", 20, 7);
                    writer(window, aux->student.course, " Curso:", 20, 9);
                    answered_student = 1; break;

                case 3:
                    for (int i=0; i<3; i++){
                        clear();
                        writer(window, aux->evaluators[i].person.name, " Nome do avaliador:", 20, 3);
                        writer(window, aux->evaluators[i].person.email, " E-mail do aluno:", 20, 5);
                        writer(window, aux->evaluators[i].institution, " Instituição:", 20, 7);

                        attron(COLOR_PAIR(2)); mvprintw(18, 34, " Para adionar outro avaliador, pressione a tecla: Enter... "); attroff(COLOR_PAIR(2));
                        attron(COLOR_PAIR(4)); mvprintw(20, 35, " Para sair do menu de exibição basta pressionar tecla: q "); attroff(COLOR_PAIR(4));
                        answered_evaluators = 1;

                        if (getch() == 'q'){break;}} break;

                case 4:
                    clear();
                    writer(window, aux->advisor.name, " Nome do instrutor:", 20, 3);
                    writer(window, aux->advisor.email, " E-mail do instrutor:", 20, 5);
                    answered_advisor = 1; break;
                    
                case 5:
                    if (answered_board, answered_student, answered_evaluators, answered_advisor == 1 || update_check == 1){
                        if (quit("Deseja salvar a banca?", 40, 0) == 1){
                            highlight = 1; choice = 0; char *choices[] = {"   Cadastrar      ", "   Exibir         ", "   Atualizar      ", "   Apagar         ", "   Sair           "};
                            n_choices = sizeof(choices)/sizeof(char *); return 1;}
                            
                        else {
                            highlight = 1; choice = 0; char *choices[] = {"   Cadastrar      ", "   Exibir         ", "   Atualizar      ", "   Apagar         ", "   Sair           "};
                            n_choices = sizeof(choices)/sizeof(char *); return 0;}}
                    else {
                        highlight = 1; choice = 0;
                        attron(COLOR_PAIR(6)); mvprintw(26, 38, " Para cancelar sem salvar, pressione: q "); attroff(COLOR_PAIR(6));
                        attron(COLOR_PAIR(5)); mvprintw(28, 35, " Preencha todos os dados para antes de salvar... "); attroff(COLOR_PAIR(5));
                        
                        if (getch() == 'q'){
                            char *choices[] = {"   Cadastrar      ", "   Exibir         ", "   Atualizar      ", "   Apagar         ", "   Sair           "};
                            n_choices = sizeof(choices)/sizeof(char *); return 0;}}}}}
    
    else {        
        clear(); attron(COLOR_PAIR(1)); mvprintw(texty, textx, text);
        mvprintw(0, 1, "Banca: %d/%d", pos_board, fp_size); attroff(COLOR_PAIR(1));
        mvchgat(0, 0, -1, A_BLINK, 1, NULL);

        if (delete_check == 0){
            attron(COLOR_PAIR(2)); mvprintw(28, 33, " Para continuar vendo as bancas, pressione a tecla: Enter... "); attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(4)); mvprintw(30, 35, " Para sair do menu de exibição basta pressionar tecla: q "); attroff(COLOR_PAIR(4));}
        else {
            attron(COLOR_PAIR(2)); mvprintw(30, 39, "Pressione qualquer tecla para prosseguir."); attroff(COLOR_PAIR(2));}

        attron(COLOR_PAIR(color_tag)); mvprintw(3, 5, " Banca "); attroff(COLOR_PAIR(color_tag));
        attron(COLOR_PAIR(1));
        mvprintw(4, 5, " Nome da banca: %s ", aux->board.title);
        mvprintw(5, 5, " Sumário: %s ", aux->board.summary);
        mvprintw(6, 5, " Horário: %s ", aux->board.time);
        mvprintw(7, 5, " Local: %s ", aux->board.local);
        mvprintw(8, 5, " Frequência da banca: %s ", aux->board.attendance);
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(color_tag)); mvprintw(10, 5, " Aluno "); attroff(COLOR_PAIR(color_tag));
        attron(COLOR_PAIR(1));
        mvprintw(11, 5, " Nome: %s ", aux->student.person.name);
        mvprintw(12, 5, " E-mail: %s ", aux->student.person.email);
        mvprintw(13, 5, " Matrícula: %s ", aux->student.registration);
        mvprintw(14, 5, " Curso: %s ", aux->student.course);
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(color_tag)); mvprintw(16, 5, " Instrutor "); attroff(COLOR_PAIR(color_tag));
        attron(COLOR_PAIR(1));
        mvprintw(17, 5, " Nome: %s ", aux->advisor.name);
        mvprintw(18, 5, " E-mail: %s ", aux->advisor.email);
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(color_tag)); mvprintw(3, 63, " Avaliadores "); attroff(COLOR_PAIR(color_tag));
        attron(COLOR_PAIR(6)); mvprintw(4, 63, " Avaliador 1 "); attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(1));
        mvprintw(5, 63, " Nome do avaliador 1: %s ", aux->evaluators[0].person.name);
        mvprintw(6, 63, " E-mail: %s ", aux->evaluators[0].person.email);
        mvprintw(7, 63, " Instituição: %s ", aux->evaluators[0].institution);
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(6)); mvprintw(9, 63, " Avaliador 2 "); attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(1));
        mvprintw(10, 63, " Nome do avaliador 2: %s ", aux->evaluators[1].person.name);
        mvprintw(11, 63, " E-mail: %s ", aux->evaluators[1].person.email);
        mvprintw(12, 63, " Instituição: %s ", aux->evaluators[1].institution);
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(6)); mvprintw(14, 63, " Avaliador 3 "); attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(1));
        mvprintw(15, 63, " Nome do avaliador 3: %s ", aux->evaluators[2].person.name);
        mvprintw(16, 63, " E-mail: %s ", aux->evaluators[2].person.email);
        mvprintw(17, 63, " Instituição: %s ", aux->evaluators[2].institution);
        attroff(COLOR_PAIR(1));

        refresh(); if (getch() == 'q'){return 1;}}}


void sign_up(WINDOW *window){
    Node *new = malloc(sizeof(Node)); new->active = 1;

    if (form(window, new, 0, "Cadastro de Banca: preencha as informações abaixo.", 36, 0, 0, 0, 0) != 0){
        add(new);} free(new);}


Node *search(FILE *fp, int color1, int color2, char *text, int textx, int texty, char *text2, int textx2, int texty2){
    Node *node = malloc(sizeof(Node)); char *quest = malloc(sizeof(char *));
    
    clear(); attron(COLOR_PAIR(color1)); mvprintw(texty, textx, text); attroff(COLOR_PAIR(color1));
    mvchgat(0, 0, -1, A_BLINK, color1, NULL);
    attron(COLOR_PAIR(2)); mvprintw(texty2, textx2, text2); attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(color2)); mvprintw(3, 20, " Qual o título da banca? "); attroff(COLOR_PAIR(color2));
    attron(COLOR_PAIR(1)); getstr(quest); mvprintw(5, 20, "%s %s ", " Banca selecionada:", quest); attroff(COLOR_PAIR(1));

    if (!fp){
        free(node); free(quest); clear(); attron(COLOR_PAIR(6)); mvprintw(3, 45, " Erro ao abrir o arquivo: database.bin "); attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(5)); mvprintw(30, 38, " Pressione qualquer tecla para encerrar o programa.\n "); attroff(COLOR_PAIR(5)); getch();}
    
    else {
        highlight = 1; choice = 0;
        while (feof(fp) == 0){
            long int pos = ftell(fp);
            fread(node, sizeof(Node), 1, fp);

            if (strcasecmp(quest, node->board.title) == 0 && node->active == 1){
                fseek(fp, pos, SEEK_SET); free(quest);
                pos_board++; return node;}
            else if (node->active == 1){pos_board++;}}
        
        free(quest); return NULL;}}


void show(WINDOW *window){
    WINDOW *window_local = newwin(HEIGHT_FC, WIDTH_FC, y, x); keypad(window_local, TRUE);

    choice = 0; highlight = 1;
    char *choices[] = {" Exibir em ordem  ", " Busca especifica ", "       Sair       "};
    int n_choices = sizeof(choices)/sizeof(char *);
    highlight = 1; choice = 0; int node_check = 0;
    
    while (1) {
        clear(); attron(COLOR_PAIR(1)); mvprintw(0, 33, "Bem-vindo ao Cadastro de Bancas do TCC da UFC - Russas!"); attroff(COLOR_PAIR(1));
        mvchgat(0, 0, -1, A_BLINK, 1, NULL);
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
                FILE *fp = fopen("./database.bin", "r");
                Node *node = malloc(sizeof(Node));

                while (fread(node, sizeof(Node), 1, fp)){
                    if (node->active == 1){
                        node_check = 1; pos_board++; highlight = 1; choice = 0;
                        if (form(window, node, 1, "Exibir bancas", 56, 0, 3, 0, 0) == 1){
                            fclose(fp); free(node); return;}}}

                if (node_check != 1){
                    highlight = 1; choice = 0;
                    free(node); clear(); attron(COLOR_PAIR(1)); mvprintw(3, 45, " Nenhuma banca foi encontrada. "); attroff(COLOR_PAIR(1));
                    attron(COLOR_PAIR(2)); mvprintw(30, 39, " Pressione qualquer tecla para prosseguir. "); attroff(COLOR_PAIR(2));
                    getch();} fclose(fp); return;

            case 2:
                FILE *fp2 = fopen("./database.bin", "r");
                Node *node2 = search(fp2, 3, 1, "Exibir banca", 56, 0, " Informe o título da banca que deseja exibir! ", 39, 30);

                if (node2 != NULL){
                    highlight = 1; choice = 0;
                    form(window, node2, 1, "Exibir bancas", 56, 0, 3, 1, 0);
                    fclose(fp2); free(node2); return;}
                else {
                    highlight = 1; choice = 0;
                    free(node2); clear(); attron(COLOR_PAIR(1)); mvprintw(3, 45, " Nenhuma banca foi encontrada. "); attroff(COLOR_PAIR(1));
                    attron(COLOR_PAIR(2)); mvprintw(30, 39, " Pressione qualquer tecla para prosseguir. "); attroff(COLOR_PAIR(2));
                    getch(); fclose(fp2); return;}

            case 3:
                highlight = 1; choice = 0; char *choices[] = {"   Cadastrar      ", "   Exibir         ", "   Atualizar      ", "   Apagar         ", "   Sair           "};
                n_choices = sizeof(choices)/sizeof(char *); return;}}}


void update(WINDOW *window){
    FILE *fp = fopen("./database.bin", "r+");
    Node *node = search(fp, 1, 3, "Atualizar bancas", 53, 0, " Informe o título da banca que deseja atualizar! ", 39, 30);

    if (node != NULL){
        attron(COLOR_PAIR(2)); mvprintw(30, 39, " Pressione qualquer tecla para prosseguir.      "); attroff(COLOR_PAIR(2)); getch();
        
        if (form(window, node, 0, "Aqui você poderá atualizar as bancas!", 42, 0, 0, 0, 1) == 1){
            fwrite(node, sizeof(Node), 1, fp); fclose(fp); free(node); return;}
        else {fclose(fp); free(node); return;}}
    
    else {
        free(node); clear(); attron(COLOR_PAIR(1)); mvprintw(3, 38, "Nenhuma banca foi cadastrada com esse nome."); attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(2)); mvprintw(30, 39, "Pressione qualquer tecla para prosseguir."); attroff(COLOR_PAIR(2)); getch();
        highlight = 1; choice = 0; refresh();} fclose(fp);}


void delete(WINDOW *window){
    FILE *fp = fopen("./database.bin", "r+");
    Node *node = search(fp, 4, 1, "Deletar banca", 54, 0, " Informe o título da banca que deseja remover! ", 39, 30);

    if (node != NULL){
        form(window, node, 1, "Banca selecionada", 53, 0, 4, 1, 0);

        if (quit("Deseja remover mesmo a banca?", 46, 0) == 1){
            clear(); highlight = 1; choice = 0;
                        
            attron(COLOR_PAIR(6)); mvprintw(5, 43, " A banca: %s, foi deletada com sucesso! ", node->board.title); attroff(COLOR_PAIR(6));
            attron(COLOR_PAIR(5)); mvprintw(30, 39, " Pressione qualquer tecla para prosseguir. "); attroff(COLOR_PAIR(5)); getch();
                        
            node->active = 0; fwrite(node, sizeof(Node), 1, fp); fclose(fp); free(node); return;}      
        else {free(node); highlight = 1; choice = 0; fclose(fp); return;}}
    
    else {
        free(node); clear(); highlight = 1; choice = 0;
        attron(COLOR_PAIR(1)); mvprintw(3, 38, " Nenhuma banca foi cadastrada com esse nome. "); attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(2)); mvprintw(30, 39, " Pressione qualquer tecla para prosseguir. "); attroff(COLOR_PAIR(2)); getch(); fclose(fp);}}