/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp

//  Todos os arquivos do projeto devem ser .cpp
//
//  Versao 2.0
//
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gl_canvas2d.h"

#include "auxiliar.h"

//variaveis globais

int screenWidth = 720, screenHeight = 500; //largura e altura inicial da tela. Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().
int LINHAS=5;
int COLUNAS=5;
int matriz[5][5];
int DESTAQUE=0;
int SOMA=0;
int SOMAGRUPO=0;
int GRUPO=0;
int somalinhas[5];
int somacolunas[5];
int A=13;
int B=13;
int C=13;
int D=13;
int contA=0;
int contB=0;
int contC=0;
float VERMELHO=0.785;
float VERDE=0.821;
float AZUL=0.8;


void Geradormatriz(){ //funcao feita para gerar uma nova matriz toda vez que for chamada.
    int i, j;

    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++){
            matriz[i][j]=rand()%10;
        }
    }
}

int PintarSomaLinha(){  //funcao feita para pintar a linha de maior soma toda vez que for chamada.
    int somadalinha=0, linhams=matriz[0][0], i, j, sl;  //sl eh o index da linha de maior soma.

    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++){
            somadalinha=somadalinha + matriz[i][j];
        }

        somalinhas[i]=somadalinha;

        if(somadalinha>linhams){
            linhams=somadalinha;
            sl=i;
        }

        somadalinha=0;
    }

    return sl;
}

int PintarSomaColuna(){ //funcao feita para pintar a coluna de maior soma toda vez que for chamada.
    int somadacoluna=0, colunams=matriz[0][0], i, j, sc;    //sl eh o index da coluna de maior soma.

    for(j=0; j<COLUNAS; j++){
        for(i=0; i<LINHAS; i++){
            somadacoluna=somadacoluna + matriz[i][j];
        }

        somacolunas[j]=somadacoluna;

        if(somadacoluna>colunams){
            colunams=somadacoluna;
            sc=j;
        }

        somadacoluna=0;
    }

    return sc;
}

void PintarGrupos(){    //funcao feita para pintar o grupo que possui maior soma(acima, abaixo ou a diagonal principal).
    int i, j, somaacima=0, somadiagonal=0, somaabaixo=0;

    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++){
            if(i<j){
                somaacima = somaacima + matriz[i][j];
            }
            if(i==j){
                somadiagonal = somadiagonal + matriz[i][j];
            }
            if(i>j){
                somaabaixo = somaabaixo + matriz[i][j];
            }
        }
    }

    if(somaacima>somadiagonal && somaacima>somaabaixo){
        GRUPO=1;
    }

    if(somadiagonal>somaacima && somadiagonal>somaabaixo){
        GRUPO=2;
    }

    if(somaabaixo>somaacima && somaabaixo>somadiagonal){
        GRUPO=3;
    }
}

void render(){   //funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais que podem ser setadas pelo metodo keyboard()
    int i, j, sl, sc;
    char str[1];

    //design do programa.
    CV::clear(VERMELHO,VERDE,AZUL);

    CV::color(0.171,0.174,0.181);
    CV::rectFill(screenWidth-screenWidth, screenHeight-screenHeight, screenWidth/2-300, screenHeight);
    CV::rectFill(screenWidth-600, screenHeight-screenHeight, screenWidth, screenHeight);

    CV::color(0.230, 0.230, 0.230);
    CV::rectFill(screenWidth-500, screenHeight-800, screenWidth-100, screenHeight-260);

    CV::color(0.230, 0.230, 0.230);
    CV::rectFill(screenWidth/50+25, screenHeight-800, screenWidth/50+375, screenHeight-260);

    CV::color(0,0,0);
    CV::rectFill((screenWidth/2)-230, (screenHeight/2)+120, (screenWidth/2)+30, (screenHeight/2)+90-190);

    //impressao da matriz.

    CV::color(1,1,1);
    for(i=0; i<LINHAS; i++){

        for(j=0; j<COLUNAS; j++){
            sprintf(str, "%d", matriz[i][j]);
            CV::text(((screenWidth/2)-205) +(j*50), ((screenHeight/2)+85)-(i*40), str);
        }
    }

    //destaque da linha e da coluna de maior soma.

    if(DESTAQUE%2!=0){
        sl=PintarSomaLinha();
        sc=PintarSomaColuna();

        CV::color(1,0,0);
            for(j=0; j<COLUNAS; j++){
                sprintf(str, "%d", matriz[sl][j]);
                CV::text(((screenWidth/2)-205)+j*50, ((screenHeight/2)+85)-sl*40, str);
        }

        CV::color(1,0,0);
            for(i=0; i<LINHAS; i++){
                sprintf(str, "%d", matriz[i][sc]);
                CV::text(((screenWidth/2)-205)+sc*50, ((screenHeight/2)+85)-i*40, str);
        }
    }

    //somas das linhas e colunas e impressao delas.

    if(SOMA%2!=0){
        CV::color(0,0,0);
        for(i=0; i<LINHAS; i++){
            sprintf(str, "%d", somalinhas[i]);
            CV::text(((screenWidth/2)-205)+6*50, ((screenHeight/2)+85)-i*40, str);
        }

        CV::color(0,0,0);
        for(i=0; i<COLUNAS; i++){
            sprintf(str, "%d", somacolunas[i]);
            CV::text(((screenWidth/2)-205)+i*50, ((screenHeight/2)+85)-6*40, str);
        }
    }

    //somas dos grupos e impressao da maior;

    if(SOMAGRUPO%2!=0){
        if(GRUPO==1){
            for(i=0; i<LINHAS; i++){
                for(j=0; j<COLUNAS; j++){
                    if(i<j){
                        CV::color(0, 0, 1);
                        sprintf(str, "%d", matriz[i][j]);
                        CV::text(((screenWidth/2)-205)+j*50, ((screenHeight/2)+85)-i*40, str);
                    }
                }
            }
        }


        if(GRUPO==2){
            for(i=0; i<LINHAS; i++){
                for(j=0; j<COLUNAS; j++){
                    if(i==j){
                        CV::color(0, 0, 1);
                        sprintf(str, "%d", matriz[i][j]);
                        CV::text(((screenWidth/2)-205)+j*50, ((screenHeight/2)+85)-i*40, str);
                    }
                }
            }
        }

        if(GRUPO==3){
            for(i=0; i<LINHAS; i++){
                for(j=0; j<COLUNAS; j++){
                    if(i>j){
                        CV::color(0, 0, 1);
                        sprintf(str, "%d", matriz[i][j]);
                        CV::text(((screenWidth/2)-205)+j*50, ((screenHeight/2)+85)-i*40, str);
                    }
                }
            }
        }
    }

    //botoes.

    CV::color(A);
    CV::rectFill(screenWidth-350, screenHeight-380, screenWidth-150, screenHeight-330);
    CV::rectFill(screenWidth-450, screenHeight-380, screenWidth-400, screenHeight-330);
    CV::color(0,0,0);
    CV::text(screenWidth-429, screenHeight-360, "A");
    CV::text(screenWidth-349, screenHeight-347, "<-- APERTE AQUI PARA");
    CV::text(screenWidth-349, screenHeight-359, "DESTACAR A LINHA E A");
    CV::text(screenWidth-349, screenHeight-371, "COLUNA DE MAIOR SOMA");

    CV::color(B);
    CV::rectFill(screenWidth-350, screenHeight-500, screenWidth-150, screenHeight-450);
    CV::rectFill(screenWidth-450, screenHeight-500, screenWidth-400, screenHeight-450);
    CV::color(0,0,0);
    CV::text(screenWidth-429, screenHeight-480, "B");
    CV::text(screenWidth-349, screenHeight-467, "<-- APERTE AQUI PARA");
    CV::text(screenWidth-349, screenHeight-479, "IMPRIMIR O VALOR DAS");
    CV::text(screenWidth-349, screenHeight-491, "SOMAS DA MATRIZ     ");

    CV::color(C);
    CV::rectFill(screenWidth-350, screenHeight-620, screenWidth-150, screenHeight-570);
    CV::rectFill(screenWidth-450, screenHeight-620, screenWidth-400, screenHeight-570);
    CV::color(0,0,0);
    CV::text(screenWidth-429, screenHeight-600, "C");
    CV::text(screenWidth-349, screenHeight-587, "<-- APERTE AQUI PARA");
    CV::text(screenWidth-349, screenHeight-599, "DESTACAR O GRUPO QUE");
    CV::text(screenWidth-349, screenHeight-611, "TEM A MAIOR SOMA    ");

    CV::color(D);
    CV::rectFill(screenWidth-350, screenHeight-740, screenWidth-150, screenHeight-690);
    CV::rectFill(screenWidth-450, screenHeight-740, screenWidth-400, screenHeight-690);
    CV::color(0,0,0);
    CV::text(screenWidth-429, screenHeight-720, "D");
    CV::text(screenWidth-349, screenHeight-707, "<-- APERTE AQUI PARA");
    CV::text(screenWidth-349, screenHeight-719, "MOSTRAR OUTRA MATRIZ");
    CV::text(screenWidth-349, screenHeight-731, "NA TELA             ");

    CV::color(VERMELHO, VERDE, AZUL);
    CV::rectFill(screenWidth/50+65, screenHeight-310, screenWidth/50+330, screenHeight-280);
    CV::color(0,0,0);
    CV::text(screenWidth/50+100, screenHeight-300, "MUDAR A COR DO FUNDO");

    CV::color(VERMELHO,0,0);
    CV::rectFill(screenWidth/50+65, screenHeight-330, screenWidth/50+125, screenHeight-390);
    CV::color(0,0,0);
    CV::text(screenWidth/50+92, screenHeight-360, "R");
    CV::text(screenWidth/50+92, screenHeight-370, "+");

    CV::color(0,VERDE,0);
    CV::rectFill(screenWidth/50+167, screenHeight-330, screenWidth/50+227, screenHeight-390);
    CV::color(0,0,0);
    CV::text(screenWidth/50+194, screenHeight-360, "G");
    CV::text(screenWidth/50+194, screenHeight-370, "+");

    CV::color(0,0,AZUL);
    CV::rectFill(screenWidth/50+270, screenHeight-330, screenWidth/50+330, screenHeight-390);
    CV::color(0,0,0);
    CV::text(screenWidth/50+296, screenHeight-360, "B");
    CV::text(screenWidth/50+296, screenHeight-370, "+");

    CV::color(VERMELHO,0,0);
    CV::rectFill(screenWidth/50+65, screenHeight-450, screenWidth/50+125, screenHeight-510);
    CV::color(0,0,0);
    CV::text(screenWidth/50+92, screenHeight-480, "R");
    CV::text(screenWidth/50+92, screenHeight-490, "-");

    CV::color(0,VERDE,0);
    CV::rectFill(screenWidth/50+167, screenHeight-450, screenWidth/50+227, screenHeight-510);
    CV::color(0,0,0);
    CV::text(screenWidth/50+194, screenHeight-480, "G");
    CV::text(screenWidth/50+194, screenHeight-490, "-");

    CV::color(0,0,AZUL);
    CV::rectFill(screenWidth/50+270, screenHeight-450, screenWidth/50+330, screenHeight-510);
    CV::color(0,0,0);
    CV::text(screenWidth/50+296, screenHeight-480, "B");
    CV::text(screenWidth/50+296, screenHeight-490, "-");

    CV::color(1,1,1);
    CV::rectFill(screenWidth/50+65, screenHeight-580, screenWidth/50+167, screenHeight-630);
    CV::color(0,0,0);
    CV::text(screenWidth/50+68, screenHeight-608, "MATRIZ 2X2");

    CV::color(1,1,1);
    CV::rectFill(screenWidth/50+227, screenHeight-580, screenWidth/50+330, screenHeight-630);
    CV::color(0,0,0);
    CV::text(screenWidth/50+230, screenHeight-608, "MATRIZ 3X3");

    CV::color(1,1,1);
    CV::rectFill(screenWidth/50+65, screenHeight-680, screenWidth/50+167, screenHeight-730);
    CV::color(0,0,0);
    CV::text(screenWidth/50+68, screenHeight-708, "MATRIZ 4X4");

    CV::color(1,1,1);
    CV::rectFill(screenWidth/50+227, screenHeight-680, screenWidth/50+330, screenHeight-730);
    CV::color(0,0,0);
    CV::text(screenWidth/50+230, screenHeight-708, "MATRIZ 5X5");
}

void keyboard(int key){  //funcao chamada toda vez que uma tecla for pressionada.
   switch(key){
      case 97:
      case 65:
        DESTAQUE++;
        SOMAGRUPO=0;
        if(C==3){
            contA=0;
            contC++;
        }
        contA++;
        A=3;
        C=13;
        if(contA%2==0){
            A=13;
        }

        break;

	  case 98:
      case 66:
        SOMA++;
        PintarSomaLinha();
        PintarSomaColuna();
        contB++;
        B=3;
        if(contB%2==0){
            B=13;
        }
        break;

	  case 99:
      case 67:
        SOMAGRUPO++;
        PintarGrupos();
        DESTAQUE=0;
        if(A==3){
            contC=0;
            contA++;
        }
        contC++;
        C=3;
        A=13;
        if(contC%2==0){
            C=13;
        }
        break;

	  case 100:
      case 68:
        Geradormatriz();
        PintarGrupos();
        PintarSomaLinha();
        PintarSomaColuna();

        if(DESTAQUE%2!=0 && SOMAGRUPO%2!=0){
            SOMAGRUPO=0;
            DESTAQUE=0;
        }
        break;

   }
}

void keyboardUp(int key){   //funcao chamada toda vez que uma tecla for liberada.
    switch(key){
       case 97:

         break;

	   case 98:

         break;

	   case 99:

         break;

	   case 100:

         break;
    }
}

void mouse(int button, int state, int wheel, int direction, int x, int y){  //funcao para tratamento de mouse: cliques, movimentos e arrastos.
    mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    mouseY = y;

    if(screenWidth-450<=x && x<=screenWidth-400 && screenHeight-380<=y && y<=screenHeight-330){
        if(button==0 && state==0){
            DESTAQUE++;
            SOMAGRUPO=0;
            if(C==3){
                contA=0;
                contC++;
            }
            contA++;
            A=3;
            C=13;
            if(contA%2==0){
                A=13;
            }
        }


    }

    if(screenWidth-450<=x && x<=screenWidth-400 && screenHeight-500<=y && y<=screenHeight-450){
        if(button==0 && state==0){
            SOMA++;
            PintarSomaLinha();
            PintarSomaColuna();
            contB++;
            B=3;
            if(contB%2==0){
                B=13;
            }
        }
    }

    if(screenWidth-450<=x && x<=screenWidth-400 && screenHeight-620<=y && y<=screenHeight-570){
        if(button==0 && state==0){
            SOMAGRUPO++;
            PintarGrupos();
            DESTAQUE=0;
            if(A==3){
                contC=0;
                contA++;
            }
            contC++;
            C=3;
            A=13;
            if(contC%2==0){
                C=13;
            }
        }
    }

    if(screenWidth-450<=x && x<=screenWidth-400 && screenHeight-740<=y && y<=screenHeight-690){
        if(button==0 && state==0){
            Geradormatriz();
            PintarGrupos();
            PintarSomaLinha();
            PintarSomaColuna();

            if(A==3 && C==3){
                contA++;
                contC++;
                SOMAGRUPO=0;
                DESTAQUE=0;
                if(contA%2==0){
                A=13;
                }
                if(contC%2==0){
                C=13;
                }
            }
        }
    }

    if(screenWidth/50+65<=x && x<=screenWidth/50+125 && screenHeight-390<=y && y<=screenHeight-330){
        if(button==0 && state==0){
            VERMELHO=VERMELHO + 0.01;
        }
    }

    if(screenWidth/50+167<=x && x<=screenWidth/50+227 && screenHeight-390<=y && y<=screenHeight-330){
        if(button==0 && state==0){
            VERDE=VERDE + 0.01;
        }
    }

    if(screenWidth/50+270<=x && x<=screenWidth/50+330 && screenHeight-390<=y && y<=screenHeight-330){
        if(button==0 && state==0){
            AZUL=AZUL + 0.01;
        }
    }

    if(screenWidth/50+65<=x && x<=screenWidth/50+125 && screenHeight-510<=y && y<=screenHeight-450){
        if(button==0 && state==0){
            VERMELHO=VERMELHO - 0.01;
        }
    }

    if(screenWidth/50+167<=x && x<=screenWidth/50+227 && screenHeight-510<=y && y<=screenHeight-450){
        if(button==0 && state==0){
            VERDE = VERDE - 0.01;
        }
    }

    if(screenWidth/50+270<=x && x<=screenWidth/50+330 && screenHeight-510<=y && y<=screenHeight-450){
        if(button==0 && state==0){
            AZUL = AZUL - 0.01;
        }
    }

    if(screenWidth/50+65<=x && x<=screenWidth/50+167 && screenHeight-630<=y && y<=screenHeight-580){
        if(button==0 && state==0){
            LINHAS = 2;
            COLUNAS = 2;
            Geradormatriz();
        }
    }

    if(screenWidth/50+227<=x && x<=screenWidth/50+330 && screenHeight-630<=y && y<=screenHeight-580){
        if(button==0 && state==0){
            LINHAS = 3;
            COLUNAS = 3;
            Geradormatriz();
        }
    }

    if(screenWidth/50+65<=x && x<=screenWidth/50+167 && screenHeight-730<=y && y<=screenHeight-680){
        if(button==0 && state==0){
            LINHAS = 4;
            COLUNAS = 4;
            Geradormatriz();
        }
    }

    if(screenWidth/50+227<=x && x<=screenWidth/50+330 && screenHeight-730<=y && y<=screenHeight-680){
        if(button==0 && state==0){
            LINHAS = 5;
            COLUNAS = 5;
            Geradormatriz();
        }
    }
}


int main(void){    //funcao main.
    srand(time(NULL));

    Geradormatriz();

    CV::init(&screenWidth, &screenHeight, "TRABALHO LA - RAFAEL CARNEIRO PREGARDIER");

    CV::run();
}
