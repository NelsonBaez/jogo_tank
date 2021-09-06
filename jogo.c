#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#define INI 4

void hidecursor()
{
    PlaySound(TEXT("theme.wav"), NULL, SND_LOOP | SND_ASYNC);
    system("color 0E");
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

char mapa[20][20] = {
    {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', ' '},
    {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', ' '},
    {'_', '_', '_', '_', '_', '_', '_', '_', '_', 'P', '_', '_', '_', 'P', 'P', 'P', '_', '_', '_', ' '},
    {'_', '_', '_', '_', '_', '_', '_', '_', '_', 'P', '_', '_', '_', 'P', '_', '_', '_', '_', '_', ' '},
    {'_', '_', 'P', 'P', 'P', '_', '_', '_', '_', 'P', '_', '_', '_', 'P', '_', '_', '_', '_', '_', ' '},
    {'_', '_', '_', '_', '_', '_', '_', '_', '_', 'p', '_', '_', '_', 'P', '_', '_', '_', '_', '_', ' '},
    {'_', '_', '_', '_', '_', 'p', '_', '_', '_', 'p', '_', '_', '_', 'P', '_', '_', '_', '_', '_', ' '},
    {'_', '_', '_', '_', '_', 'p', '_', '_', '_', 'p', '_', '_', '_', 'P', '_', '_', 'P', '_', '_', ' '},
    {'_', '_', '_', '_', 'P', 'p', '_', '_', '_', 'P', '_', '_', '_', '_', '_', '_', 'P', '_', '_', ' '},
    {'_', '_', '_', '_', 'P', 'p', '_', '_', '_', 'P', '_', '_', 'p', 'p', 'p', 'p', 'P', '_', '_', ' '},
    {'_', '_', '_', '_', 'P', 'p', '_', '_', '_', 'P', '_', '_', '_', '_', '_', '_', 'P', '_', '_', ' '},
    {'_', '_', '_', '_', 'P', 'p', '_', '_', '_', 'P', '_', '_', '_', 'P', '_', '_', 'P', '_', '_', ' '},
    {'_', '_', '_', '_', 'P', '_', '_', '_', '_', 'P', '_', '_', '_', 'P', '_', '_', 'P', '_', '_', ' '},
    {'_', 'P', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', 'P', '_', '_', 'P', '_', '_', ' '},
    {'_', 'P', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', 'P', '_', '_', ' '},
    {'_', 'P', 'P', 'P', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '*', 'P', '_', '_', ' '},
    {'_', '_', '_', 'P', '_', '_', '_', 'P', 'P', 'P', 'P', 'P', '_', 'P', 'P', 'P', 'P', '_', '_', ' '},
    {'_', '_', '_', 'P', '_', '_', '_', 'P', 'P', 'P', 'P', 'P', '_', '_', '_', '_', '_', '_', '_', ' '},
    {'_', '_', '_', '_', '_', '_', '_', 'P', 'P', 'B', 'P', 'P', '_', '_', '_', '_', '_', '_', '_', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
};

char score[4][20] = {
    {'_', 'P', 'P', 'P', '_', '_', 'P', '_', '_', 'P', '_', '_', 'P', '_', 'P', '_', 'P', '_', '_', ' '},
    {'_', '_', 'P', '_', '_', 'P', '_', 'P', '_', 'P', 'P', '_', 'P', '_', 'P', '_', 'P', '_', '_', ' '},
    {'_', '_', 'P', '_', '_', 'P', 'P', 'P', '_', 'P', '_', 'P', 'P', '_', 'P', 'P', '_', '_', '_', ' '},
    {'_', '_', 'P', '_', '_', 'P', '_', 'P', '_', 'P', '_', '_', 'P', '_', 'P', '_', 'P', '_', '_', ' '},
};

char gameover[5][67] = {
    {"  PPP     PP   PP       PP PPPPP      PPP   P        P PPPPP PPP  "},
    {" P   P   P  P  P P     P P P         P   P   P      P  P     P  P "},
    {" P      PPPPPP P  P   P  P PPPPP    P     P   P    P   PPPPP PPP  "},
    {" P   PP P    P P   P P   P P         P   P     P  P    P     P  P "},
    {"  PPP P P    P P    P    P PPPPP      PPP       PP     PPPPP P   P"},
};

int scorepoint = 0;

void desenhagameover(){
    for(int ls=0; ls<5; ls++){
        for(int cs=0; cs<66; cs++){
            gotoxy(10+cs,2+ls);
            switch(gameover[ls][cs]){
                case 'P' : printf("%c", 177);
                break;
                default : printf("%c", gameover[ls][cs]);
            }
        }
    }
}

struct tposicao{
    int x, y;
    int sentido;
    int ini_morto;
    int ini_tiro;
};
int posx, posy;
int bx = 18, by = 9;
struct tposicao inimigos[INI];
struct tposicao tiro;
struct tposicao tiro_inimigo[INI];
int tem_tiro = 0;
int morto = 0;
int alldead = 0;
int suicidio = 0;

void gotoxy(int x, int y){
    COORD c;
    c.X = x -1;
    c.Y = y -1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void moldura(int ci, int cf, int li, int lf){
    int l,c;
    for(c=ci+1; c<=cf-1; c++){
        gotoxy(c, li);
        printf("%c", 205);
        gotoxy(c, lf);
        printf("%c", 205);
    }
    for(l=li+1; l<=lf-1; l++){
        gotoxy(ci, l);
        printf("%c", 186);
        gotoxy(cf, l);
        printf("%c", 186);
    }
    gotoxy(ci, li);
    printf("%c", 201);
    gotoxy(ci, lf);
    printf("%c", 200);
    gotoxy(cf, li);
    printf("%c", 187);
    gotoxy(cf, lf);
    printf("%c", 188);
}

void desenhamapa(){
    int l, c, ls, cs;

    moldura(9, 29, 1, 6);
    moldura(9, 29, 9, 29);

    gotoxy(9,7);
    printf("   SCORE: %d", scorepoint);
    for(ls=0; ls<4; ls++){
        for(cs=0; cs<19; cs++){
            gotoxy(10+cs,2+ls);
            switch(score[ls][cs]){
                case '*' : printf("%c", 1);
                break;
                case '_' : printf(" ");
                break;
                case 'P' : printf("%c", 177);
                break;
                default : printf("%c", score[ls][cs]);
            }
        }
    }

    for(l=0; l<19; l++){
        for(c=0; c<19; c++){
            gotoxy(10+c,10+l);
            switch(mapa[l][c]){
                case '*' : printf("%c", 207);
                break;
                case '_' : printf(" ");
                break;
                case 'P' : printf("%c", 177);
                break;
                case 'p' : printf("%c", 219);
                break;
                case 'I' : printf("%c", 190);
                break;
                case '.' : printf("%c", 169);
                break;
                default : printf("%c", mapa[l][c]);
            }
        }
    }
}

void movimentaperso(int tecla){
    mapa[posx][posy] = '_';
    if(tecla == 120){
        morto=1;
    }
    if(tecla == 80){
        if(mapa[posx+1][posy] == '_'){
            posx++;
        }
    }else if(tecla == 72){
        if(mapa[posx-1][posy] == '_'){
            posx--;
        }
    }else if(tecla == 77){
        if(mapa[posx][posy+1] == '_'){
            posy++;
        }
    }else if(tecla == 75){
        if(mapa[posx][posy-1] == '_'){
            posy--;
        }
    }
    if(tem_tiro == 0){
        if(tecla == 115 && (mapa[posx+1][posy] == '_' || mapa[posx+1][posy] == 'P' || mapa[posx+1][posy] == 'I' || mapa[posx+1][posy] == 'B')){
            tem_tiro = 1;
            Beep(1000,5);
            tiro.x = posx + 1;
            tiro.y = posy;
            tiro.sentido = 0;
            if(mapa[tiro.x][tiro.y] == 'P'){
                tem_tiro = 0;
                mapa[tiro.x][tiro.y] = '_';
            }else if(mapa[tiro.x][tiro.y] == 'I'){
                for(int i=0; i<INI; i++){
                    if(inimigos[i].x == tiro.x && inimigos[i].y == tiro.y){
                        scorepoint = scorepoint + 50;
                        inimigos[i].ini_morto = 1;
                        tem_tiro = 0;
                        mapa[tiro.x][tiro.y] = '_';
                    }
                }
            }else if(mapa[tiro.x][tiro.y] == 'B'){
                morto = 1;
                suicidio = 1;
            }else{
                mapa[tiro.x][tiro.y] = '.';
            }
        }else if(tecla == 119 && (mapa[posx-1][posy] == '_' || mapa[posx-1][posy] == 'P' || mapa[posx-1][posy] == 'I' || mapa[posx-1][posy] == 'B')){
            tem_tiro = 1;
            Beep(1000,5);
            tiro.x = posx - 1;
            tiro.y = posy;
            tiro.sentido = 1;
            if(mapa[tiro.x][tiro.y] == 'P'){
                tem_tiro = 0;
                mapa[tiro.x][tiro.y] = '_';
            }else if(mapa[tiro.x][tiro.y] == 'I'){
                for(int i=0; i<INI; i++){
                    if(inimigos[i].x == tiro.x && inimigos[i].y == tiro.y){
                        scorepoint = scorepoint + 50;
                        inimigos[i].ini_morto = 1;
                        tem_tiro = 0;
                        mapa[tiro.x][tiro.y] = '_';
                    }
                }
            }else if(mapa[tiro.x][tiro.y] == 'B'){
                morto = 1;
            }else{
                mapa[tiro.x][tiro.y] = '.';
            }
        }else if(tecla == 100 && (mapa[posx][posy+1] == '_' || mapa[posx][posy+1] == 'P' || mapa[posx][posy+1] == 'I' || mapa[posx][posy+1] == 'B')){
            tem_tiro = 1;
            Beep(1000,5);
            tiro.x = posx;
            tiro.y = posy + 1;
            tiro.sentido = 2;
            if(mapa[tiro.x][tiro.y] == 'P'){
                tem_tiro = 0;
                mapa[tiro.x][tiro.y] = '_';
            }else if(mapa[tiro.x][tiro.y] == 'I'){
                for(int i=0; i<INI; i++){
                    if(inimigos[i].x == tiro.x && inimigos[i].y == tiro.y){
                        scorepoint = scorepoint + 50;
                        inimigos[i].ini_morto = 1;
                        tem_tiro = 0;
                        mapa[tiro.x][tiro.y] = '_';
                    }
                }
            }else if(mapa[tiro.x][tiro.y] == 'B'){
                morto = 1;
            }else{
                mapa[tiro.x][tiro.y] = '.';
            }
        }else if(tecla == 97 && (mapa[posx][posy-1] == '_' || mapa[posx][posy-1] == 'P' || mapa[posx][posy-1] == 'I' || mapa[posx][posy-1] == 'B')){
            tem_tiro = 1;
            Beep(1000,5);
            tiro.x = posx;
            tiro.y = posy - 1;
            tiro.sentido = 3;
            if(mapa[tiro.x][tiro.y] == 'P'){
                tem_tiro = 0;
                mapa[tiro.x][tiro.y] = '_';
            }else if(mapa[tiro.x][tiro.y] == 'I'){
                for(int i=0; i<INI; i++){
                    if(inimigos[i].x == tiro.x && inimigos[i].y == tiro.y){
                        scorepoint = scorepoint + 50;
                        inimigos[i].ini_morto = 1;
                        tem_tiro = 0;
                        mapa[tiro.x][tiro.y] = '_';
                    }
                }
            }else if(mapa[tiro.x][tiro.y] == 'B'){
                morto = 1;
            }else{
                mapa[tiro.x][tiro.y] = '.';
            }
        }
    }

    mapa[posx][posy] = '*';
}


void funcao_tiro_ini(i){
    if((inimigos[i].x == posx && inimigos[i].y < posy || inimigos[i].x == bx && inimigos[i].y < by) && inimigos[i].ini_morto == 0){ // ini a esquerda
        tiro_inimigo[i].sentido = 0; // tiro a direita
        inimigos[i].ini_tiro = 1;
        Beep(1000,5);
        tiro_inimigo[i].x = inimigos[i].x;
        tiro_inimigo[i].y = inimigos[i].y + 1;
        if(mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == 'P'){
                inimigos[i].ini_tiro = 0;
                mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] = '_';
        }else if(mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == 'B' || mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == '*'){
            morto = 1;
        }else{
            mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] = '.';
        }

    }else if((inimigos[i].x == posx && inimigos[i].y > posy || inimigos[i].x == bx && inimigos[i].y > by) && inimigos[i].ini_morto == 0){ // ini a direita
        tiro_inimigo[i].sentido = 1; // tiro a esquerda
        inimigos[i].ini_tiro = 1;
        Beep(1000,5);
        tiro_inimigo[i].x = inimigos[i].x;
        tiro_inimigo[i].y = inimigos[i].y - 1;
        if(mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == 'P'){
                inimigos[i].ini_tiro = 0;
                mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] = '_';
        }else if(mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == 'B' || mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == '*'){
            morto = 1;
        }else{
            mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] = '.';
        }

    }else if((inimigos[i].x > posx && inimigos[i].y == posy || inimigos[i].x > bx && inimigos[i].y == by) && inimigos[i].ini_morto == 0){ // ini em cima
        tiro_inimigo[i].sentido = 2; // tiro pra baixo
        inimigos[i].ini_tiro = 1;
        Beep(1000,5);
        tiro_inimigo[i].x = inimigos[i].x -1;
        tiro_inimigo[i].y = inimigos[i].y;
        if(mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == 'P'){
                inimigos[i].ini_tiro = 0;
                mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] = '_';
        }else if(mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == 'B' || mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == '*'){
            morto = 1;
        }else{
            mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] = '.';
        }

    }else if((inimigos[i].x < posx && inimigos[i].y == posy || inimigos[i].x < bx && inimigos[i].y == by) && inimigos[i].ini_morto == 0){ // ini em baixo
        tiro_inimigo[i].sentido = 3; // tiro pra cima
        inimigos[i].ini_tiro = 1;
        Beep(1000,5);
        tiro_inimigo[i].x = inimigos[i].x +1;
        tiro_inimigo[i].y = inimigos[i].y;
        if(mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == 'P'){
                inimigos[i].ini_tiro = 0;
                mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] = '_';
        }else if(mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == 'B' || mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == '*'){
            morto = 1;
        }else{
            mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] = '.';
        }
    }
}



void movimentainimigo(){
    int chute, contaMorto=0;
    for(int i=0; i<INI; i++){
        if(inimigos[i].ini_tiro == 0){
            funcao_tiro_ini(i);
        }
        if(inimigos[i].ini_morto == 0){
            mapa[inimigos[i].x][inimigos[i].y] = '_';
            chute = rand()%4;
            switch(chute){
                case 0:
                    if(mapa[inimigos[i].x-1][inimigos[i].y] == '_'){
                        inimigos[i].x--;
                    }else if(mapa[inimigos[i].x-1][inimigos[i].y] == '*'){
                        morto=1;
                    }
                break;
                case 1:
                    if(mapa[inimigos[i].x][inimigos[i].y+1] == '_'){
                        inimigos[i].y++;
                    }else if(mapa[inimigos[i].x][inimigos[i].y+1] == '*'){
                        morto=1;
                    }
                break;
                case 2:
                    if(mapa[inimigos[i].x+1][inimigos[i].y] == '_'){
                        inimigos[i].x++;
                    }else if(mapa[inimigos[i].x+1][inimigos[i].y] == '*'){
                        morto=1;
                    }
                break;
                case 3:
                    if(mapa[inimigos[i].x][inimigos[i].y-1] == '_'){
                        inimigos[i].y--;
                    }else if(mapa[inimigos[i].x][inimigos[i].y-1] == '*'){
                        morto=1;
                    }
                break;
            }
            mapa[inimigos[i].x][inimigos[i].y] = 'I';
        }else{
            contaMorto++;
        }
        if(contaMorto == INI){
            alldead = 1;
        }
    }
}


void movimentatiro_inimigo(int i){

    mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] = '_';
    switch(tiro_inimigo[i].sentido){
        case 0:
            if(mapa[tiro_inimigo[i].x][tiro_inimigo[i].y+1] == '_' || mapa[tiro_inimigo[i].x][tiro_inimigo[i].y+1] == '*' || mapa[tiro_inimigo[i].x][tiro_inimigo[i].y+1] == 'P' || mapa[tiro_inimigo[i].x][tiro_inimigo[i].y+1] == 'B'){
                tiro_inimigo[i].y++; break; //pra direita
            }else{
                inimigos[i].ini_tiro = 0;
            }
        case 1:
            if(mapa[tiro_inimigo[i].x][tiro_inimigo[i].y-1] == '_' || mapa[tiro_inimigo[i].x][tiro_inimigo[i].y-1] == '*' || mapa[tiro_inimigo[i].x][tiro_inimigo[i].y-1] == 'P' || mapa[tiro_inimigo[i].x][tiro_inimigo[i].y-1] == 'B'){
                tiro_inimigo[i].y--; break; //pra esquerda
            }else{
                inimigos[i].ini_tiro = 0;
            }
        case 2:
            if(mapa[tiro_inimigo[i].x-1][tiro_inimigo[i].y] == '_' || mapa[tiro_inimigo[i].x-1][tiro_inimigo[i].y] == '*' || mapa[tiro_inimigo[i].x-1][tiro_inimigo[i].y] == 'P' || mapa[tiro_inimigo[i].x-1][tiro_inimigo[i].y] == 'B'){
                tiro_inimigo[i].x--; break; // pra baixo
            }else{
                inimigos[i].ini_tiro = 0;
            }
        case 3:
            if(mapa[tiro_inimigo[i].x+1][tiro_inimigo[i].y] == '_' || mapa[tiro_inimigo[i].x+1][tiro_inimigo[i].y] == '*' || mapa[tiro_inimigo[i].x+1][tiro_inimigo[i].y] == 'P' || mapa[tiro_inimigo[i].x+1][tiro_inimigo[i].y] == 'B'){
                tiro_inimigo[i].x++; break; // pra cima
            }else{
                inimigos[i].ini_tiro = 0;
            }
    }
    if(mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == '*' || mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == 'B'){
        morto=1;
    }else if(mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == 'P' || mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] == 'I'){
        inimigos[i].ini_tiro = 0;
    }
    if(inimigos[i].ini_tiro == 0){
        mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] = '_';
    }else{
        mapa[tiro_inimigo[i].x][tiro_inimigo[i].y] = '.';
    }

}

void movimentatiro(){

    mapa[tiro.x][tiro.y] = '_';
    switch(tiro.sentido){
        case 0:
            if(mapa[tiro.x+1][tiro.y] == '_' || mapa[tiro.x+1][tiro.y] == '*' || mapa[tiro.x+1][tiro.y] == 'P' || mapa[tiro.x+1][tiro.y] == 'p' || mapa[tiro.x+1][tiro.y] == 'I' || mapa[tiro.x+1][tiro.y] == 'B'){
                tiro.x++; break; //pra baixo
            }else{
                tem_tiro = 0;
            }
        case 1:
            if(mapa[tiro.x-1][tiro.y] == '_' || mapa[tiro.x-1][tiro.y] == '*' || mapa[tiro.x-1][tiro.y] == 'P' || mapa[tiro.x-1][tiro.y] == 'p' || mapa[tiro.x-1][tiro.y] == 'I' || mapa[tiro.x-1][tiro.y] == 'B'){
                tiro.x--; break; //pra cima
            }else{
                tem_tiro = 0;
            }
        case 2:
            if(mapa[tiro.x][tiro.y+1] == '_' || mapa[tiro.x][tiro.y+1] == '*' || mapa[tiro.x][tiro.y+1] == 'P' || mapa[tiro.x][tiro.y+1] == 'p' || mapa[tiro.x][tiro.y+1] == 'I' || mapa[tiro.x][tiro.y+1] == 'B'){
                tiro.y++; break; //direita
            }else{
                tem_tiro = 0;
            }
        case 3:
            if(mapa[tiro.x][tiro.y-1] == '_' || mapa[tiro.x][tiro.y-1] == '*' || mapa[tiro.x][tiro.y-1] == 'P' || mapa[tiro.x][tiro.y-1] == 'p' || mapa[tiro.x][tiro.y-1] == 'I' || mapa[tiro.x][tiro.y-1] == 'B'){
                tiro.y--; break; //esquerda
            }else{
                tem_tiro = 0;
            }
    }
    if(mapa[tiro.x][tiro.y] == 'I'){
        for(int i=0; i<INI; i++){
            if(inimigos[i].x == tiro.x && inimigos[i].y == tiro.y){
                scorepoint = scorepoint + 50;
                inimigos[i].ini_morto = 1;
            }
        }
        tem_tiro = 0;
    }else if(mapa[tiro.x][tiro.y] == '*' || mapa[tiro.x][tiro.y] == 'B'){
        scorepoint = scorepoint - 1000;
        suicidio = 1;
        morto=1;
    }else if(mapa[tiro.x][tiro.y] == 'P' || mapa[tiro.x][tiro.y] == 'p'){
        tem_tiro = 0;
    }
    if(tem_tiro == 0 && mapa[tiro.x][tiro.y] != 'p'){
        mapa[tiro.x][tiro.y] = '_';
    }else if(mapa[tiro.x][tiro.y] != 'p'){
        mapa[tiro.x][tiro.y] = '.';
    }

}


main(){
    hidecursor();
    int retarda=0;
    int spawnado;
    int retardatiro=0;
    int retarda_tiro_ini = 0;
    posx = posy = 15;
    char tecla;
    int chutex, chutey;
    srand(time(NULL));
    do{
        for(int inis=0; inis < INI; inis++){
            do{
                chutex = rand()%15;
                chutey = rand()%20;
                if (mapa[chutex][chutey] == '_'){
                    inimigos[inis].x=chutex;
                    inimigos[inis].y=chutey;
                    inimigos[inis].ini_morto = 0;
                }
            }while(mapa[chutex][chutey] != '_');
            mapa[chutex][chutey] = 'I';
        }
        do{
            desenhamapa();
            if(kbhit()){
                tecla = getch();
                movimentaperso(tecla);
            }
            if(retarda %15 ==0){
                movimentainimigo();
                retarda=0;
            }
            retarda++;
            if(tem_tiro == 1){
                if(retardatiro % 3 == 0){
                    movimentatiro();
                    retardatiro = 0;
                }
                retardatiro++;
            }

            for(int i = 0; i<INI; i++){
                if(inimigos[i].ini_tiro == 1){
                    if(retarda_tiro_ini % 3 == 0){
                        movimentatiro_inimigo(i);
                        retarda_tiro_ini = 0;
                    }
                    retarda_tiro_ini++;
                }
            }

            if(morto != 0){
                system("cls");
                do{
                    desenhagameover();
                    if(kbhit()){
                        tecla = getch();
                    }
                    gotoxy(9,9);
                    printf("   Seu SCORE Final foi de: %d", scorepoint);
                    if(suicidio == 1){
                        gotoxy(9,8);
                        printf("   Voce se auto suicidou-se a si mesmo!!");
                    }
                }while(tecla != 27);
            }

        }while(tecla != 27 && morto == 0 && alldead == 0);
        if(alldead == 1){
            alldead = 0;
        }
    }while(tecla != 27  && morto == 0);
}
