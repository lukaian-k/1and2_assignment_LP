//imports files
#include "fuctions_ncurses.h"

//define
#define WIDTH_FC 20
#define HEIGHT_FC 5

//create variables
int fp_size, pos_board;


//fuctions

void board_size(){
    ifstream fp("database.bin");

    if (fp.is_open()){
        Node *node = new Node; int i = 0;
        
        while (fp.read(reinterpret_cast<char *> (node), sizeof(Node))){
            if (node->active != false){i++;}}

        fp_size = i; pos_board = 0; delete(node);} fp.close();}


void add(Node *new_node){
    ofstream fp("database.bin", ios::app);
    
    if (fp.is_open()){fp.write(reinterpret_cast<const char *> (new_node), sizeof(Node));}

    else {
        clear(); attron(COLOR_PAIR(6)); mvprintw(3, 45, " Erro ao abrir o arquivo: database.bin "); attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(5)); mvprintw(30, 38, " Pressione qualquer tecla para encerrar o programa.\n "); attroff(COLOR_PAIR(5)); getch(); return;}
    
    fp.close();}


bool form(WINDOW *window, Node *aux, bool show, const char *text, int textx, int texty, int color_tag, bool delete_check, bool update_check){
    if (show != true){
        bool answered_board, answered_student, answered_evaluators, answered_advisor = false;
        choice = 0; highlight = 1; const char *choices[] = {"   Banca          ", "   Aluno          ", "   Avaliadores    ", "   Instrutor      ", "   Salvar         "};
        n_choices = sizeof(choices)/sizeof(char *);
        
        while (true){
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
                case 1: {
                    clear(); ifstream fp("database.bin");
                    Node *node = new Node;

                    if (fp.is_open()){
                        bool stop = false;
                        
                        while (stop != true){
                            fp.seekg(fp.beg);

                            string title = writer(window, aux->board.title, " Nome da Banca:", 20, 3);
                            transform(title.begin(), title.end(), title.begin(), ::tolower);

                            while (fp.read(reinterpret_cast<char *> (node), sizeof(Node))){
                                string title_board = node->board.title;
                                transform(title_board.begin(), title_board.end(), title_board.begin(), ::tolower);

                                if (title == title_board && node->active == true){
                                    attron(COLOR_PAIR(6)); mvprintw(28, 13, " Banca já existente! Utilize outro nome para a banca. Pressione a tecla: Enter, para prosseguir..."); attroff(COLOR_PAIR(6));
                                    getch(); clear(); stop = false; break;}
                                else {stop = true;}}
                                
                            if (node->active == 0){
                                break;}} fp.close(); delete(node);}

                    else {
                        delete(node); clear(); attron(COLOR_PAIR(6)); mvprintw(3, 45, " Erro ao abrir o arquivo: database.bin "); attroff(COLOR_PAIR(6));
                        attron(COLOR_PAIR(5)); mvprintw(30, 38, " Pressione qualquer tecla para encerrar o programa.\n "); attroff(COLOR_PAIR(5)); getch();}
                    
                    writer(window, aux->board.summary, " Sobre:", 20, 5);
                    writer(window, aux->board.time, " Horário:", 20, 7);
                    writer(window, aux->board.local, " Local:", 20, 9);
                    writer(window, aux->board.attendance, " Frequência:", 20, 11);
                    answered_board = true; break;}

                case 2:
                    clear();
                    writer(window, aux->student.name, "Nome do aluno:", 20, 3);
                    writer(window, aux->student.email, "E-mail do aluno:", 20, 5);
                    writer(window, aux->student.registration, "Matrícula:", 20, 7);
                    writer(window, aux->student.course, " Curso:", 20, 9);
                    answered_student = true; break;

                case 3:
                    for (int i=0; i<3; i++){
                        clear();
                        writer(window, aux->evaluators[i].name, " Nome do avaliador:", 20, 3);
                        writer(window, aux->evaluators[i].email, " E-mail do aluno:", 20, 5);
                        writer(window, aux->evaluators[i].institution, " Instituição:", 20, 7);

                        attron(COLOR_PAIR(2)); mvprintw(18, 34, " Para adionar outro avaliador, pressione a tecla: Enter... "); attroff(COLOR_PAIR(2));
                        attron(COLOR_PAIR(4)); mvprintw(20, 35, " Para sair do menu de exibição basta pressionar tecla: q "); attroff(COLOR_PAIR(4));
                        answered_evaluators = true;

                        if (getch() == 'q'){break;}} break;

                case 4:
                    clear();
                    writer(window, aux->advisor.name, " Nome do instrutor:", 20, 3);
                    writer(window, aux->advisor.email, " E-mail do instrutor:", 20, 5);
                    answered_advisor = true; break;
                    
                case 5:
                    if (answered_board, answered_student, answered_evaluators, answered_advisor == true || update_check == true){
                        if (quit("Deseja salvar a banca?", 40, 0) == true){
                            highlight = 1; choice = 0; const char *choices[] = {"   Cadastrar      ", "   Exibir         ", "   Atualizar      ", "   Apagar         ", "   Sair           "};
                            n_choices = sizeof(choices)/sizeof(char *); return true;}
                            
                        else {
                            highlight = 1; choice = 0; const char *choices[] = {"   Cadastrar      ", "   Exibir         ", "   Atualizar      ", "   Apagar         ", "   Sair           "};
                            n_choices = sizeof(choices)/sizeof(char *); return false;}}
                    else {
                        highlight = 1; choice = 0;
                        attron(COLOR_PAIR(6)); mvprintw(26, 38, " Para cancelar sem salvar, pressione: q "); attroff(COLOR_PAIR(6));
                        attron(COLOR_PAIR(5)); mvprintw(28, 35, " Preencha todos os dados para antes de salvar... "); attroff(COLOR_PAIR(5));
                        
                        if (getch() == 'q'){
                            const char *choices[] = {"   Cadastrar      ", "   Exibir         ", "   Atualizar      ", "   Apagar         ", "   Sair           "};
                            n_choices = sizeof(choices)/sizeof(char *); return false;}}}}}
    
    else {
        clear(); attron(COLOR_PAIR(1)); mvprintw(texty, textx, text);
        mvprintw(0, 1, "Banca: %d/%d", pos_board, fp_size); attroff(COLOR_PAIR(1));
        mvchgat(0, 0, -1, A_BLINK, 1, NULL);

        if (delete_check == false){
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
        mvprintw(11, 5, " Nome: %s ", aux->student.name);
        mvprintw(12, 5, " E-mail: %s ", aux->student.email);
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
        mvprintw(5, 63, " Nome do avaliador 1: %s ", aux->evaluators[0].name);
        mvprintw(6, 63, " E-mail: %s ", aux->evaluators[0].email);
        mvprintw(7, 63, " Instituição: %s ", aux->evaluators[0].institution);
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(6)); mvprintw(9, 63, " Avaliador 2 "); attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(1));
        mvprintw(10, 63, " Nome do avaliador 2: %s ", aux->evaluators[1].name);
        mvprintw(11, 63, " E-mail: %s ", aux->evaluators[1].email);
        mvprintw(12, 63, " Instituição: %s ", aux->evaluators[1].institution);
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(6)); mvprintw(14, 63, " Avaliador 3 "); attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(1));
        mvprintw(15, 63, " Nome do avaliador 3: %s ", aux->evaluators[2].name);
        mvprintw(16, 63, " E-mail: %s ", aux->evaluators[2].email);
        mvprintw(17, 63, " Instituição: %s ", aux->evaluators[2].institution);
        attroff(COLOR_PAIR(1));

        refresh(); if (getch() == 'q'){return true;}} return false;}


void sign_up(WINDOW *window){
    Node *new_node = new Node; new_node->active = true;

    if (form(window, new_node, false, "Cadastro de Banca: preencha as informações abaixo.", 36, 0, 0, false, false) != false){
        add(new_node);} delete(new_node);}


Node *search(fstream *fp, int color1, int color2, const char *text, int textx, int texty, const char *text2, int textx2, int texty2){
    Node *node = new Node; char *quest = new char;
    
    clear(); attron(COLOR_PAIR(color1)); mvprintw(texty, textx, text); attroff(COLOR_PAIR(color1));
    mvchgat(0, 0, -1, A_BLINK, color1, NULL);
    attron(COLOR_PAIR(2)); mvprintw(texty2, textx2, text2); attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(color2)); mvprintw(3, 20, " Qual o título da banca? "); attroff(COLOR_PAIR(color2));
    attron(COLOR_PAIR(1));

    getstr(quest); string quest_string = quest;
    transform(quest_string.begin(), quest_string.end(), quest_string.begin(), ::tolower);
    mvprintw(5, 20, "%s %s ", " Banca selecionada:", quest); attroff(COLOR_PAIR(1));

    if ((*fp).is_open()){
        highlight = 1; choice = 0;
        while ((*fp).read(reinterpret_cast<char *> (node), sizeof(Node))){
            long int pos = (*fp).tellg();
            string title_board = node->board.title;
            transform(title_board.begin(), title_board.end(), title_board.begin(), ::tolower);

            if (quest_string == title_board && node->active == true){
                (*fp).seekg(pos-sizeof(Node));
                delete(quest); pos_board++; return node;}
            else if (node->active == true){pos_board++;}}
        
        delete(quest); return NULL;}

    else {
        delete(node); delete(quest); clear(); attron(COLOR_PAIR(6)); mvprintw(3, 45, " Erro ao abrir o arquivo: database.bin "); attroff(COLOR_PAIR(6));
        attron(COLOR_PAIR(5)); mvprintw(30, 38, " Pressione qualquer tecla para encerrar o programa.\n "); attroff(COLOR_PAIR(5)); getch();} return NULL;}


void show(WINDOW *window){
    WINDOW *window_local = newwin(HEIGHT_FC, WIDTH_FC, y, x); keypad(window_local, TRUE);

    choice = 0; highlight = 1;
    const char *choices[] = {" Exibir em ordem  ", " Busca especifica ", "       Sair       "};
    int n_choices = sizeof(choices)/sizeof(char *);
    highlight = 1; choice = 0; bool node_check = false;
    
    while (true) {
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
            case 1: {
                ifstream fp("database.bin");
                Node *node = new Node;

                if (fp.is_open()){

                    while (fp.read(reinterpret_cast<char *> (node), sizeof(Node))){
                        if (node->active == true){
                            node_check = true; pos_board++; highlight = 1; choice = 0;
                            if (form(window, node, true, "Exibir bancas", 56, 0, 3, false, false) == true){
                                fp.close(); delete(node); return;}}}

                    if (node_check != true){
                        highlight = 1; choice = 0;
                        delete(node); clear(); attron(COLOR_PAIR(1)); mvprintw(3, 45, " Nenhuma banca foi encontrada. "); attroff(COLOR_PAIR(1));
                        attron(COLOR_PAIR(2)); mvprintw(30, 39, " Pressione qualquer tecla para prosseguir. "); attroff(COLOR_PAIR(2));
                        getch();} fp.close(); return;}
                
                else {
                    delete(node); clear(); attron(COLOR_PAIR(6)); mvprintw(3, 45, " Erro ao abrir o arquivo: database.bin "); attroff(COLOR_PAIR(6));
                    attron(COLOR_PAIR(5)); mvprintw(30, 38, " Pressione qualquer tecla para encerrar o programa.\n "); attroff(COLOR_PAIR(5)); getch();}}

            case 2: {
                fstream fp2("database.bin", ios::in);
                Node *node2 = search(&fp2, 3, 1, "Exibir banca", 56, 0, " Informe o título da banca que deseja exibir! ", 39, 30);

                if (node2 != NULL){
                    highlight = 1; choice = 0;
                    form(window, node2, true, "Exibir bancas", 56, 0, 3, true, false);
                    fp2.close(); delete(node2); return;}
                else {
                    highlight = 1; choice = 0;
                    delete(node2); clear(); attron(COLOR_PAIR(1)); mvprintw(3, 45, " Nenhuma banca foi encontrada. "); attroff(COLOR_PAIR(1));
                    attron(COLOR_PAIR(2)); mvprintw(30, 39, " Pressione qualquer tecla para prosseguir. "); attroff(COLOR_PAIR(2));
                    getch(); fp2.close(); return;}}

            case 3:
                highlight = 1; choice = 0; const char *choices[] = {"   Cadastrar      ", "   Exibir         ", "   Atualizar      ", "   Apagar         ", "   Sair           "};
                n_choices = sizeof(choices)/sizeof(char *); return;}}}


void update(WINDOW *window){
    fstream fp("database.bin");
    Node *node = search(&fp, 1, 3, "Atualizar bancas", 53, 0, " Informe o título da banca que deseja atualizar! ", 39, 30);

    if (node != NULL){
        attron(COLOR_PAIR(2)); mvprintw(30, 39, " Pressione qualquer tecla para prosseguir.      "); attroff(COLOR_PAIR(2)); getch();
        
        if (form(window, node, false, "Aqui você poderá atualizar as bancas!", 42, 0, 0, false, true) == true){
            fp.write(reinterpret_cast<const char *> (node), sizeof(Node));
            fp.close(); delete(node); return;}
        else {fp.close(); delete(node); return;}}
    
    else {
        delete(node); clear(); attron(COLOR_PAIR(1)); mvprintw(3, 38, "Nenhuma banca foi cadastrada com esse nome."); attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(2)); mvprintw(30, 39, "Pressione qualquer tecla para prosseguir."); attroff(COLOR_PAIR(2)); getch();
        highlight = 1; choice = 0; refresh();} fp.close();}


void delete_board(WINDOW *window){
    fstream fp("database.bin");
    Node *node = search(&fp, 4, 1, "Deletar banca", 54, 0, " Informe o título da banca que deseja remover! ", 39, 30);

    if (node != NULL){
        form(window, node, true, "Banca selecionada", 53, 0, 4, true, false);

        if (quit("Deseja remover mesmo a banca?", 46, 0) == true){
            clear(); highlight = 1; choice = 0;
                        
            attron(COLOR_PAIR(6)); mvprintw(5, 43, " A banca: %s, foi deletada com sucesso! ", node->board.title); attroff(COLOR_PAIR(6));
            attron(COLOR_PAIR(5)); mvprintw(30, 39, " Pressione qualquer tecla para prosseguir. "); attroff(COLOR_PAIR(5)); getch();
                        
            node->active = false; fp.write(reinterpret_cast<const char *> (node), sizeof(Node));
            fp.close(); delete(node); return;}
        else {delete(node); highlight = 1; choice = 0; fp.close(); return;}}
    
    else {
        delete(node); clear(); highlight = 1; choice = 0;
        attron(COLOR_PAIR(1)); mvprintw(3, 38, " Nenhuma banca foi cadastrada com esse nome. "); attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(2)); mvprintw(30, 39, " Pressione qualquer tecla para prosseguir. "); attroff(COLOR_PAIR(2)); getch(); fp.close();}}