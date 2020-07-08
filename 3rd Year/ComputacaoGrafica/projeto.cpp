/*
	Aluno: José Veríssimo Lamas
	Número: 2017259895
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>

#include "RgbImage.h"
void initMaterials(int material);

#define PI		 3.14159

/*==============================================================
	Teclas:


==============================================================*/


//............... Objectos (sistema coordenadas)
GLint	wScreen = 800, hScreen = 600;				//.. janela (pixeis)
GLfloat	xC = 1000.0, yC = 1000.0, zC = 1000.0;		//.. Mundo  (unidades mundo)

//............... Visualizacao/Observador 
GLfloat  rVisao = 25, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao), 7.0, rVisao * sin(aVisao) };
GLfloat  angZoom = 90;
GLfloat  incZoom = 3;


//================= Caracteristicas dos obj =================

//............... Sky && Grass
GLfloat radius = 50;
GLfloat slices = 100;
GLint txId = 8;
GLboolean dia = true;

GLfloat xGrass = radius*2;
GLfloat yGrass = 0;
GLfloat zGrass = radius*2;
GLboolean visibleGrass[6] = { true, false, false, false, false, false };
GLint txGrass[6] = { 10, 10, 10, 10, 10, 10 };

//............... Room
GLfloat xRoom = 30;
GLfloat yRoom = 20;
GLfloat zRoom = 30;
GLboolean visibleRoom[6] = { true, true, true, true, true, true };
GLint txRoom[6] = { 7, 7, 6, 6, 6, 6 };

//............... Tapete
GLfloat xTapete = xRoom/2;
GLfloat yTapete = 0.1;
GLfloat zTapete = zRoom/2;
GLboolean visibleTapete[6] = { true, false, true, true, true, true };


//............... pernas da mesa
GLfloat xPernas = 0.3;
GLfloat yPernas = 2.0;
GLfloat zPernas = 0.3;
GLboolean visiblePernas[6] = { false, false, true, true, true, true };
GLint txPernas[6] = { 0, 0, 0, 0, 0, 0 };

//............... tabua da mesa
GLfloat xMesa = 6.0;
GLfloat yMesa = 0.2;
GLfloat zMesa = 5.0;
GLfloat angleMesa = 0.0;
GLboolean visibleMesa[6] = { true, true, true, true, true, true };
GLint txMesa[6] = { 0, 0, 0, 0, 0, 0 };

//............... gaveta da mesa
GLfloat xMesaGaveta = xMesa*5/6;
GLfloat yMesaGaveta = 0.1;
GLfloat zMesaGaveta = zMesa*5/6;
GLfloat abreGaveta = 0.0;
GLboolean visibleGaveta[6] = { true, true, true, true, true, true };
GLint txGaveta[6] = { 0, 0, 0, 0, 0, 0 };

//............... suportes da gaveta
GLfloat xSuportes = 0.1;
GLfloat ySuportes = yMesaGaveta * 2;
GLfloat zSuportes = zMesaGaveta;
GLboolean visibleSuportes[6] = { false, true, true, true, true, true };
GLint txSuportes[6] = { 1, 1, 1, 1, 1, 1 };

//............... computador
GLfloat xComputador = 2.0;
GLfloat yComputador = 0.1;
GLfloat zComputador = xComputador*2;
GLboolean visibleScreen[6] = { true, true, true, true, true, true };
GLint txScreen[6] = { 3, 4, 4, 4, 4, 4 };
GLboolean visibleKeyboard[6] = { true, false, true, true, true, true };
GLint txKeyboard[6] = { 2, 4, 4, 4, 4, 4 };

GLfloat angleAbreComputador = 90.0;
GLfloat angleMax = 30.0;

//............... copo
GLfloat xCopo = 0.5;
GLfloat yCopo = 1;
GLfloat zCopo = xCopo;
GLboolean visibleCopo[6] = { true, true, true, true, true, true };
GLint txCopo[6] = { 1, 1, 1, 1, 1, 1 };


//............... Animacoes/ reposicoes
GLfloat angle = 0.0;
GLfloat xWalk = 0.0;
GLfloat zWalk = 0.0;
GLboolean frenteVisivel = true;


// =============== Texturas ===============

//............... array com as texturas
GLuint texture[11];

//............... var aux para as imagens
RgbImage img;


// =============== Luzes ==================

//............... Luz Ambiente
GLboolean luzAmbOn = true;

GLfloat luzAmbInt = 1.0;
GLfloat luzAmb[4] = { luzAmbInt, luzAmbInt, luzAmbInt, 1.0 };

//............... Luz Foco
GLboolean luzFocoOn = false;
GLfloat luzFocoAng[] = {180};
GLfloat luzFocoDir[] = { 0, 0, -1 };
GLfloat luzFocoR = 1.0;
GLfloat luzFocoG = 1.0;
GLfloat luzFocoB = 1.0;
GLfloat luzFoco[4] = { luzFocoR, luzFocoG, luzFocoB, 1.0 };
GLfloat luzFocoCoords[] = { 10 , 0, 10 };

//............... Luz Teto
GLboolean luzTetoOn = false;
GLfloat luzTetoAng[] = { 20.0 };
GLfloat luzTetoDir[] = { 0, -1, 0 };
GLfloat luzTetoR = 0.25;
GLfloat luzTetoG = 0.25;
GLfloat luzTetoB = 0.25;
GLfloat luzTeto[4] = { luzFocoR, luzFocoG, luzFocoB, 1.0 };
GLfloat luzTetoCoords[] = { 0 , yRoom -2 , 0 };


// =============== Funcs ==================

void saveTexture(GLint arrayIndex, const char* fileName) {
	glGenTextures(1, &texture[arrayIndex]);
	glBindTexture(GL_TEXTURE_2D, texture[arrayIndex]);
	img.LoadBmpFile(fileName);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img.GetNumCols(),
		img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		img.ImageData());
}

void saveTextureRoom(GLint arrayIndex, const char* fileName) {
	glGenTextures(1, &texture[arrayIndex]);
	glBindTexture(GL_TEXTURE_2D, texture[arrayIndex]);
	img.LoadBmpFile(fileName);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img.GetNumCols(),
		img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		img.ImageData());
}

void initTexturas(){

	//----------------------------------------- Tabua mesa
	saveTexture(0, "./textures/oak.bmp");
	//----------------------------------------- Ferro
	saveTexture(1, "./textures/iron.bmp");
	//----------------------------------------- Keyboard
	saveTexture(2, "./textures/keyboard_computer.bmp");
	//----------------------------------------- screen
	saveTexture(3, "./textures/screen_computer.bmp");
	//----------------------------------------- back
	saveTexture(4, "./textures/back_computer.bmp");
	//----------------------------------------- screen off
	saveTexture(5, "./textures/screen_off_computer.bmp");
	//----------------------------------------- wall
	saveTexture(6, "./textures/wall.bmp");
	//----------------------------------------- ground
	saveTexture(7, "./textures/bamboo.bmp");
	//----------------------------------------- day sky
	saveTexture(8, "./textures/day.bmp");
	//----------------------------------------- night sky
	saveTexture(9, "./textures/night.bmp");
	//----------------------------------------- grass
	saveTexture(10, "./textures/grass.bmp");

}

// =============== Luzes ==================

void initLuz() {

	// light0 -> luzAmb
	//glLightfv(GL_LIGHT0, GL_POSITION, luzAmbCoords);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmb);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmb);

	// light0 -> luzFoco
	glLightfv(GL_LIGHT0, GL_POSITION, obsP);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, luzFocoDir);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, luzFocoAng);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzFoco);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzFoco);

	//light1 -> teto
	glLightfv(GL_LIGHT1, GL_POSITION, luzTetoCoords);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, luzTetoDir);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, luzTetoAng);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzTeto);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzTeto);

}

void updateLuz() {

	if (dia) luzAmbInt = 1.0;
	else luzAmbInt = 0.5;

	luzAmb[0] = luzAmbInt;
	luzAmb[1] = luzAmbInt;
	luzAmb[2] = luzAmbInt;

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmb);

	luzFoco[0] = luzFocoR;
	luzFoco[1] = luzFocoG;
	luzFoco[2] = luzFocoB;
	//glLightfv(GL_LIGHT1, GL_POSITION, luzFocoCoords);
	glLightfv(GL_LIGHT0, GL_POSITION, obsP);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, luzFoco);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, luzFocoAng);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzFoco);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzFoco);
}

void OnAndOffs() {
	updateLuz();
	if (luzFocoOn) glEnable(GL_LIGHT0);
	else glDisable(GL_LIGHT0);

	if (luzTetoOn) glEnable(GL_LIGHT1);
	else glDisable(GL_LIGHT1);
}


// =============== Desenhos ===============

void desenhaPolig(GLfloat largura, GLfloat altura, GLfloat comprimento, GLboolean invisible[6], GLint typeTexture[6]) {

	altura /= 2;
	largura /= 2;
	comprimento /= 2;

	glEnable(GL_TEXTURE_2D);

	if (frenteVisivel)	glCullFace(GL_BACK);	//.. o de tras = eliminado
	else				glCullFace(GL_FRONT);	//.. o de frente = eliminado

	// cria as coordenadas dos vertices, as normais e as cores
	GLfloat vertices[] = {
		//=============== x=tam Esquerda
			-largura,  -altura,  comprimento,	// 0 
			-largura,   altura,  comprimento,	// 1 
			-largura,   altura, -comprimento,	// 2 
			-largura,  -altura, -comprimento,	// 3 
		//====================	Direita
			 largura,  -altura,  comprimento,	// 4 
			 largura,   altura,  comprimento,	// 5 
			 largura,   altura, -comprimento,	// 6 
			 largura,  -altura, -comprimento,	// 7 
		//===================== Cima
			-largura,  altura,  comprimento,	// 8 
			-largura,  altura, -comprimento,	// 9 
			 largura,  altura, -comprimento,	// 10 
			 largura,  altura,  comprimento,	// 11 
		//===================== Frente
			-largura,  altura,  comprimento,	// 12 
			 largura,  altura,  comprimento,	// 13
			 largura, -altura,  comprimento,	// 14 
			-largura, -altura,  comprimento,	// 15 
		//===================== Tras
			-largura,  altura, -comprimento,	// 16 
			 largura,  altura, -comprimento,	// 17 
			 largura, -altura, -comprimento,	// 18 
			-largura, -altura, -comprimento,	// 19 
		//===================== Baixo
			-largura, -altura,  comprimento,	// 20
			-largura, -altura, -comprimento,	// 21
			 largura, -altura, -comprimento,	// 22 
			 largura, -altura,  comprimento,	// 23 


	};
	GLfloat normais[] = {
		//====================================== x=tam (Esquerda)
			-1.0,  0.0,  0.0,
			-1.0,  0.0,  0.0,
			-1.0,  0.0,  0.0,
			-1.0,  0.0,  0.0,
		//====================================== x=tam (Direita)
			1.0,  0.0,  0.0,
			1.0,  0.0,  0.0,
			1.0,  0.0,  0.0,
			1.0,  0.0,  0.0,
		//====================================== y=tam (Cima)
			0.0,  1.0,  0.0,
			0.0,  1.0,  0.0,
			0.0,  1.0,  0.0,
			0.0,  1.0,  0.0,
		//====================================== z=tam (Frente)
			0.0,  0.0,  1.0,
			0.0,  0.0,  1.0,
			0.0,  0.0,  1.0,
			0.0,  0.0,  1.0,
		//====================================== z=-tam (Tras)
			0.0,  0.0, -1.0,
			0.0,  0.0, -1.0,
			0.0,  0.0, -1.0,
			0.0,  0.0, -1.0,
		//====================================== y=-tam (Baixo)
			0.0,  -1.0,  0.0,
			0.0,  -1.0,  0.0,
			0.0,  -1.0,  0.0,
			0.0,  -1.0,  0.0,
	};
	GLfloat arrayTexture[] = {
		0,0, 1,0, 1,1,
		0,1, 0,0, 1,0,
		1,1, 0,1, 0,0,
		1,0, 1,1, 0,1,
		0,0, 1,0, 1,1,
		0,1, 0,0, 1,0,
		1,1, 0,1, 0,0,
		1,0, 1,1, 0,1,
		0,0, 1,0, 1,1,
		0,1, 0,0, 1,0,
		1,1, 0,1, 0,0,
		1,0, 1,1, 0,1,
		0,0, 1,0, 1,1,
		0,1, 0,0, 1,0,
		1,1, 0,1, 0,0,
		1,0, 1,1, 0,1,
		0,0, 1,0, 1,1,
		0,1
	};

	GLboolean   frenteVisivel = 1;

	GLuint cima[]	= { 8, 11, 10,  9 };		
	GLuint esq[]	= { 0, 1, 2,  3 };
	GLuint dir[]	= { 4, 7, 6,  5 };
	GLuint front[]	= { 15, 14, 13, 12 };
	GLuint back[]	= { 16, 17, 18, 19 };
	GLuint down[]	= { 20, 21, 22, 23 };

	
	// Cria o VertexArrays: vertices + normais + cores + texturas
	glVertexPointer(3, GL_FLOAT, 0, vertices); 
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, arrayTexture);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	initMaterials(typeTexture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[typeTexture[0]]);
	if (invisible[0]) glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);

	initMaterials(typeTexture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[typeTexture[1]]);
	if (invisible[1]) glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, down);

	initMaterials(typeTexture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[typeTexture[2]]);
	if (invisible[2]) glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esq);

	initMaterials(typeTexture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[typeTexture[3]]);
	if (invisible[3]) glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, dir);

	initMaterials(typeTexture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[typeTexture[4]]);
	if (invisible[4]) glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, front);

	initMaterials(typeTexture[5]);
	glBindTexture(GL_TEXTURE_2D, texture[typeTexture[5]]);
	if (invisible[5]) glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);

	glDisable(GL_TEXTURE_2D);

}

void desenhaPoligCor(GLfloat largura, GLfloat altura, GLfloat comprimento, GLboolean invisible[6]) {

	altura /= 2;
	largura /= 2;
	comprimento /= 2;

	glDisable(GL_TEXTURE_2D);

	if (frenteVisivel)	glCullFace(GL_BACK);	//.. o de tras = eliminado
	else				glCullFace(GL_FRONT);	//.. o de frente = eliminado

	// cria as coordenadas dos vertices, as normais e as cores
	GLfloat vertices[] = {
		//=============== x=tam Esquerda
			-largura,  -altura,  comprimento,	// 0 
			-largura,   altura,  comprimento,	// 1 
			-largura,   altura, -comprimento,	// 2 
			-largura,  -altura, -comprimento,	// 3 
		//====================	Direita
			 largura,  -altura,  comprimento,	// 4 
			 largura,   altura,  comprimento,	// 5 
			 largura,   altura, -comprimento,	// 6 
			 largura,  -altura, -comprimento,	// 7 
		//===================== Cima
			-largura,  altura,  comprimento,	// 8 
			-largura,  altura, -comprimento,	// 9 
			 largura,  altura, -comprimento,	// 10 
			 largura,  altura,  comprimento,	// 11 
		//===================== Frente
			-largura,  altura,  comprimento,	// 12 
			 largura,  altura,  comprimento,	// 13
			 largura, -altura,  comprimento,	// 14 
			-largura, -altura,  comprimento,	// 15 
		//===================== Tras
			-largura,  altura, -comprimento,	// 16 
			 largura,  altura, -comprimento,	// 17 
			 largura, -altura, -comprimento,	// 18 
			-largura, -altura, -comprimento,	// 19 
		//===================== Baixo
			-largura, -altura,  comprimento,	// 20
			-largura, -altura, -comprimento,	// 21
			 largura, -altura, -comprimento,	// 22 
			 largura, -altura,  comprimento,	// 23 


	};
	GLfloat normais[] = {
		//====================================== x=tam (Esquerda)
			-1.0,  0.0,  0.0,
			-1.0,  0.0,  0.0,
			-1.0,  0.0,  0.0,
			-1.0,  0.0,  0.0,
			//====================================== x=tam (Direita)
				1.0,  0.0,  0.0,
				1.0,  0.0,  0.0,
				1.0,  0.0,  0.0,
				1.0,  0.0,  0.0,
				//====================================== y=tam (Cima)
					0.0,  1.0,  0.0,
					0.0,  1.0,  0.0,
					0.0,  1.0,  0.0,
					0.0,  1.0,  0.0,
					//====================================== z=tam (Frente)
						0.0,  0.0,  1.0,
						0.0,  0.0,  1.0,
						0.0,  0.0,  1.0,
						0.0,  0.0,  1.0,
						//====================================== z=-tam (Tras)
							0.0,  0.0, -1.0,
							0.0,  0.0, -1.0,
							0.0,  0.0, -1.0,
							0.0,  0.0, -1.0,
							//====================================== y=-tam (Baixo)
								0.0,  -1.0,  0.0,
								0.0,  -1.0,  0.0,
								0.0,  -1.0,  0.0,
								0.0,  -1.0,  0.0,
	};

	GLfloat red = 1;
	GLfloat green = 0.0;
	GLfloat blue = 0.0;

	GLfloat cor[] = {
		//====================================== x=tam (Esquerda) - Red
		  red,  green, blue,	// 0 
		  red,  green, blue,	// 1 
		  red,  green, blue,	// 2 
		  red,  green, blue,	// 3 
		//====================================== x=2*tam (Direita) - Green
		  red,  green, blue,	// 4 
		  red,  green, blue,	// 5 
		  red,  green, blue,	// 6 
		  red,  green, blue,	// 7 
		//====================================== y=tam (Cima) - Blue
		  red,  green, blue,	// 8 
		  red,  green, blue,	// 9 
		  red,  green, blue,	// 10 
		  red,  green, blue,	// 11 
		//====================================== y=tam (frente) - magenta
		  red,  green, blue,	// 12 
		  red,  green, blue,	// 13 
		  red,  green, blue,	// 14 
		  red,  green, blue,	// 15 
		//====================================== y=tam (tras) - ciano
		  red,  green, blue,	// 16 
		  red,  green, blue,	// 17 
		  red,  green, blue,	// 18 
		  red,  green, blue,	// 19 
		//====================================== y=tam (baixo) - brando
		  red,  green, blue,	// 20 
		  red,  green, blue,	// 21 
		  red,  green, blue,	// 22 
		  red,  green, blue,	// 23 
	};
	
	GLboolean   frenteVisivel = 1;

	GLuint cima[] = { 8, 11, 10,  9 };
	GLuint esq[] = { 0, 1, 2,  3 };
	GLuint dir[] = { 4, 7, 6,  5 };
	GLuint front[] = { 15, 14, 13, 12 };
	GLuint back[] = { 16, 17, 18, 19 };
	GLuint down[] = { 20, 21, 22, 23 };


	// Cria o VertexArrays: vertices + normais + cores + texturas
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, cor);
	glEnableClientState(GL_COLOR_ARRAY);

	initMaterials(11);
	if (invisible[0]) glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	if (invisible[1]) glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, down);
	if (invisible[2]) glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esq);
	if (invisible[3]) glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, dir);
	if (invisible[4]) glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, front);
	if (invisible[5]) glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);

}

void inicializa(void){

	glClearColor(1.0, 1.0, 1.0, 1.0);		//==============================Apagar
	glShadeModel(GL_SMOOTH);	//==============================Interpolacao de cores
	glEnable(GL_DEPTH_TEST);	//==============================Profundidade
	glEnable(GL_NORMALIZE);

	initTexturas(); // texturas

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_LIGHTING);
	initLuz();		//==============================Luz

	glEnable(GL_CULL_FACE);		//==============================Faces visiveis
	glCullFace(GL_BACK);		//==============================Mostrar so as da frente
	
}

void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(5, 0, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(0.0, 1.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 5, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 5);
	glEnd();

}


// =============== Objetos ===============

void makeSky() {
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glTranslatef(0, yPernas, 0);
		glRotatef(90, 0, 1, 0);

		initMaterials(txId);
		glBindTexture(GL_TEXTURE_2D, texture[txId]);

		GLUquadric* quad = gluNewQuadric();
		gluQuadricOrientation(quad, GLU_INSIDE);
		gluQuadricTexture(quad, texture[txId]);

		gluSphere(quad, radius, slices, slices);

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void makeRoom() {
	
	glPushMatrix();

		// chao
		glPushMatrix();
			glTranslatef(0, -yPernas/2, 0);
			// chao
			desenhaPolig(xRoom, 0, zRoom, visibleRoom, txRoom);
		glPopMatrix();

		// teto
		glPushMatrix();
			glTranslatef(0, -yPernas/ 2 + yRoom , 0);
			// chao
			desenhaPolig(xRoom, 0, zRoom, visibleRoom, txRoom);
		glPopMatrix();

		// esq
		glPushMatrix();
			glTranslatef(-xRoom/2, yRoom / 2 - yPernas / 2, 0);
			// parede lado
			desenhaPolig(0, yRoom, zRoom, visibleRoom, txRoom);
		glPopMatrix();

		// dir
		glPushMatrix();
			glTranslatef(xRoom / 2, yRoom / 2 - yPernas / 2, 0);
			// parede lado
			desenhaPolig(0, yRoom, zRoom, visibleRoom, txRoom);
		glPopMatrix();

		// tras
		glPushMatrix();
			glTranslatef(0, yRoom / 2 - yPernas / 2, zRoom / 2);
			// parede frente
			desenhaPolig(xRoom, yRoom, 0, visibleRoom, txRoom);
		glPopMatrix();

		// frente
		glPushMatrix();
			glTranslatef(0, yRoom / 12 - yPernas / 2, -zRoom / 2);
			// parede frente baixo
			desenhaPolig(xRoom, yRoom / 6, 0, visibleRoom, txRoom);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 11 * yRoom / 12 - yPernas / 2, -zRoom / 2);
			// parede frente cima
			desenhaPolig(xRoom, yRoom / 6, 0, visibleRoom, txRoom);
		glPopMatrix();
		glPushMatrix();
			glEnable(GL_BLEND);			// invisibilidade
				glBlendFunc(GL_ONE, GL_ONE);
				glTranslatef(0, yRoom / 2 - yPernas / 2, -zRoom / 2);
				// parede frente janela
				desenhaPolig(xRoom, 4 * yRoom / 6, 0, visibleRoom, txSuportes);
			glDisable(GL_BLEND);
		glPopMatrix();

	glPopMatrix();
}

void makeGrass() {

	glPushMatrix();
	
		glTranslatef(0, -1-yPernas / 2, 0);
		
		desenhaPolig(xGrass, yGrass, zGrass, visibleGrass, txGrass);

	glPopMatrix();
}

void displayTapete() {
	glPushMatrix();
		glTranslatef(0, -yPernas/2 + yTapete/2, 0);

		desenhaPoligCor(xTapete, yTapete, zTapete, visibleTapete);

	glPopMatrix();
}

void copo() {
	glPushMatrix();
		glEnable(GL_BLEND);			// invisibilidade
		glBlendFunc(GL_ONE, GL_ONE);
		glTranslatef(xCopo, yPernas/2 + yMesa, zMesa - zCopo*2);
		// chao
		glPushMatrix();
			// chao
			desenhaPolig(xCopo, 0, zCopo, visibleCopo, txCopo);
		glPopMatrix();

		// esq
		glPushMatrix();
			glTranslatef(-xCopo / 2, yCopo / 2, 0);
			// parede lado
			desenhaPolig(0, yCopo, zCopo, visibleCopo, txCopo);
		glPopMatrix();

		// dir
		glPushMatrix();
			glTranslatef(xCopo / 2, yCopo / 2, 0);
			// parede lado
			desenhaPolig(0, yCopo, zCopo, visibleCopo, txCopo);
		glPopMatrix();

		// frente
		glPushMatrix();
			glTranslatef(0, yCopo / 2, -zCopo / 2);
			// parede frente
			desenhaPolig(xCopo, yCopo, 0, visibleCopo, txCopo);
		glPopMatrix();

		// tras
		glPushMatrix();
			glTranslatef(0, yCopo / 2, zCopo / 2);
			// parede frente
			desenhaPolig(xCopo, yCopo, 0, visibleCopo, txCopo);
		glPopMatrix();

		glDisable(GL_BLEND);
	glPopMatrix();
}

void mesaTabua(GLint typeTexture[]) {
	// Animacoes tabua toda
	glRotatef(angleMesa, 1, 0, 0);

	// Desenhar a tabua da mesa
	glPushMatrix();
	// desenho da tabua
	glTranslatef(xMesa / 2 - xPernas / 2, yMesa / 2 + yPernas / 2, zMesa / 2 - zPernas / 2);
	desenhaPolig(xMesa, yMesa, zMesa, visibleMesa, typeTexture);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void mesaPernas(GLint typeTexture[]) {
	glPushMatrix();
	desenhaPolig(xPernas, yPernas, zPernas, visiblePernas, typeTexture);
	glTranslatef(xMesa - xPernas, 0, 0);
	desenhaPolig(xPernas, yPernas, zPernas, visiblePernas, typeTexture);
	glTranslatef(0, 0, zMesa - zPernas);
	desenhaPolig(xPernas, yPernas, zPernas, visiblePernas, typeTexture);
	glTranslatef(-xMesa + xPernas, 0, 0);
	desenhaPolig(xPernas, yPernas, zPernas, visiblePernas, typeTexture);
	glPopMatrix();
}

void gavetaSuportes(GLint typeTexture[]) {
	// suportes da gaveta
	GLfloat xS = xMesaGaveta / 2 - xMesaGaveta / 20;
	GLfloat yS = yMesaGaveta / 2 + ySuportes / 2;
	GLfloat zS = 0;

	glPushMatrix();
	glTranslatef(-xS, yS, zS);
	desenhaPolig(xSuportes, ySuportes, zSuportes, visibleSuportes, typeTexture);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(xS, yS, zS);
	desenhaPolig(xSuportes, ySuportes, zSuportes, visibleSuportes, typeTexture);
	glPopMatrix();
}

void gavetaTabua(GLint typeTexture[]) {
	glTranslatef(xMesa / 2 - xPernas / 2, yPernas / 2 - yMesaGaveta * 5 / 2, zMesaGaveta / 2); // deslocar gaveta + suportes

	glPushMatrix();
	// animations
	glTranslatef(0, 0, abreGaveta);
	//desenho da gaveta
	desenhaPolig(xMesaGaveta, yMesaGaveta, zMesaGaveta, visibleGaveta, typeTexture);
	glPopMatrix();
}

void computadorBase(GLint typeTexture[]) {
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-xComputador / 2, -yComputador / 2, 0);
	desenhaPolig(xComputador, yComputador, zComputador, visibleKeyboard, typeTexture);
	glPopMatrix();
}

void computadorEcra(GLint typeTexture[]) {
	glPushMatrix();
		// animacao
		glRotatef(angleAbreComputador, 0, 0, 1);
		// desenho
		glTranslatef(xComputador / 2, -yComputador / 2, 0);
		desenhaPolig(xComputador, yComputador, zComputador, visibleScreen, typeTexture);
	glPopMatrix();
}

// =============== Draw Scene ===============

void drawScene() {
	
	// MESA	
	glPushMatrix();

		glTranslatef(xWalk, 0, zWalk);
		glRotatef(angle, 0, 1, 0);
		glScalef(2, 2, 2);

		// ............. Desenhar as pernas da mesa .............
		mesaPernas(txPernas);
		//.......................................................
		// .................. Tabua e gaveta ....................
		glPushMatrix();

			mesaTabua(txMesa);

			// Desenhar Gaveta
			glPushMatrix();
				gavetaTabua(txGaveta);
				gavetaSuportes(txSuportes);
			glPopMatrix();
		glPopMatrix();
		//.......................................................
		// .................... Computador ......................
		glPushMatrix();
			glTranslatef(xMesa / 2, yPernas/2 + 3*yComputador, zMesa/4);
			
			glRotatef(90, 1, 0, 0);	// inicialmente o computador estava de pe e de lado
			glRotatef(90, 0, 1, 0);
			// Keyboard
			computadorBase(txKeyboard);
			// Screen
			computadorEcra(txScreen);
		glPopMatrix();

		// objts com propriedades de transpaerncia (os mais para cima sao os primeiros a serem desenhados)
		
		displayTapete();
		makeGrass();
		makeSky();
		makeRoom();
		copo();

	glPopMatrix();

}

void display(void) {

	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//================================================================= N=o modificar !!!!!!!!!!!!
	
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	//================================================================= N=o modificar !!!!!!!!!!!!

	glEnable(GL_LIGHTING);
	
	//================================================================= Objectos
	drawEixos();
	drawScene();

	OnAndOffs();

	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

// ================ Eventos ================

// some animation functions

void openComputer(int) {
	if (angleAbreComputador >= -angleMax) {
		angleAbreComputador -= 1.0;
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, openComputer, 0);
	}
}
void closeComputer(int) {
	if (angleAbreComputador <= 90) {
		angleAbreComputador += 1.0;
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, closeComputer, 0);
	}
}

void openGaveta(int) {
	if (abreGaveta < zMesaGaveta / 2) {
		abreGaveta += 0.1;
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, openGaveta, 0);
	}
}
void closeGaveta(int) {
	if (abreGaveta > 0.2) {
		abreGaveta -= 0.1;
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, closeGaveta, 0);
	}
}

// Key readers

void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'e':
	case 'E': // liga ou desliga luz
		luzFocoOn = !luzFocoOn;
		OnAndOffs();
		glutPostRedisplay();
		break;

	case 'q':
	case 'Q': // liga ou desliga luz teto
		luzTetoOn = !luzTetoOn;
		OnAndOffs();
		glutPostRedisplay();
		break;
	
	//.......................................................................... Luz
	case 'v':// menos vermelho
		if (luzFocoOn && luzFocoR > 0) {
			luzFocoR -= 0.2;
		}
		updateLuz();
		glutPostRedisplay();
		break;
	case 'V': // mais vermelho
		if (luzFocoOn && luzFocoR < 1) {
			luzFocoR += 0.2;
		}
		updateLuz();
		glutPostRedisplay();
		break;


	case 'b':// menos verde
		if (luzFocoOn && luzFocoG > 0) {
			luzFocoG -= 0.2;
		}
		updateLuz();
		glutPostRedisplay();
		break;
	case 'B': // mais verde
		if (luzFocoOn && luzFocoG < 1) {
			luzFocoG += 0.2;
		}
		updateLuz();
		glutPostRedisplay();
		break;


	case 'n':// menos azul
		if (luzFocoOn && luzFocoB > 0) {
			luzFocoB -= 0.2;
		}
		updateLuz();
		glutPostRedisplay();
		break;
	case 'N': // mais azul
		if (luzFocoOn && luzFocoB < 1) {
			luzFocoB += 0.2;
		}
		updateLuz();
		glutPostRedisplay();
		break;


	case 'c': // ceu
	case 'C':
		dia = !dia;

		if (dia) txId = 8;
		else txId = 9;

		updateLuz();
		glutPostRedisplay();
		break;

	//....................................................................................

	case 'W':
	case 'w':
		zWalk += 1;
		glutPostRedisplay();
		break;

	case 'A':
	case 'a':
		xWalk += 1;
		glutPostRedisplay();
		break;

	case 'S':
	case 's':
		zWalk -= 1;
		glutPostRedisplay();
		break;

	case 'd':
	case 'D':
		xWalk -= 1;
		glutPostRedisplay();
		break;

	//.................................................................... Animacoes objetos
	case 't':
	case 'T':
		glutTimerFunc(1000 / 60, openGaveta, 0);
		break;
	case 'y':
	case 'Y':
		glutTimerFunc(1000 / 60, closeGaveta, 0);
		break;
	case 'g':
	case 'G': // pc on
		txScreen[0] = 3;
		updateLuz();
		glutTimerFunc(1000 / 60, openComputer, 0);
		break;
	case 'h':
	case 'H': // pc off
		txScreen[0] = 5;
		updateLuz();
		glutTimerFunc(1000 / 60, closeComputer, 0);
		break;

		//------------------------------------------------------------------- Escape
	case 27:
		exit(0);
		break;
	}

}

void teclasNotAscii(int key, int x, int y) {
	//.. observador pode andar = volda da cena  (setas esquerda / direita)
	//.. observador pode andar para cima e para baixo (setas cima / baixo )

	if (key == GLUT_KEY_UP)   obsP[1] = (obsP[1] + 0.1);
	if (key == GLUT_KEY_DOWN) obsP[1] = (obsP[1] - 0.1);
	if (key == GLUT_KEY_LEFT) angle -= 2; //aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT)angle += 2; //aVisao = (aVisao - 0.1);

	if (obsP[1] > yC)   obsP[1] = yC;   // limita altura
	if (obsP[1] < -yC)  obsP[1] = -yC;

	obsP[0] = rVisao * cos(aVisao);      // actualiza posicao (X,Z)
	obsP[2] = rVisao * sin(aVisao);

	glutPostRedisplay();
}

// ================= Main ==================
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("lamas@student.dei.uc.pt");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
