//*********************************************************************
//  Minicurso: Computacao Grafica usando OpenGL
//  Autor: Prof. Laurindo de Sousa Britto Neto
//*********************************************************************

/* Inclui os headers do OpenGL, GLU, e GLUT */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "stb_image.h"
#include <math.h>
#include "glm.h"
#define ESC 27
char nome[100];
GLMmodel * pmodelS = NULL;
GLMmodel * pmodelC = NULL;
GLMmodel * pmodelW = NULL;
GLMmodel * pmodelCm = NULL;
//Objetos
char wood[100] = "objs/simple_wood.obj";
char carro2[100] = "objs/car.obj";
char sapo[100] = "objs/12270_Frog_v1_L3.obj";
//Criar Objetos
void drawModelS()
{
	if (!pmodelS)
	{
		pmodelS = glmReadOBJ("objs/12270_Frog_v1_L3.obj");
		if (!pmodelS)
			exit(0);
		glmUnitize(pmodelS);
		glmFacetNormals(pmodelS);//normal do obejeto
		glmVertexNormals(pmodelS, 10);
	}
	glmDraw(pmodelS, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();

}
void drawModelC()
{
	glColor3f(1.0, 0.0, 0.0);
	if (!pmodelC)
	{
		pmodelC = glmReadOBJ("objs/car.obj");
		if (!pmodelC)
			exit(0);
		glmUnitize(pmodelC);
		glmFacetNormals(pmodelC);//normal do obejeto
		glmVertexNormals(pmodelC, 10);
	}
	glmDraw(pmodelC, GLM_SMOOTH | GLM_MATERIAL);

	;
}
void drawModelCm()
{
	glColor3f(0.7, 0.7, 0.7);
	if (!pmodelCm)
	{
		pmodelCm = glmReadOBJ("objs/tuck.obj");
		if (!pmodelCm)
			exit(0);
		glmUnitize(pmodelCm);
		glmFacetNormals(pmodelCm);//normal do obejeto
		glmVertexNormals(pmodelCm, 10);
	}
	glmDraw(pmodelCm, GLM_SMOOTH | GLM_MATERIAL);

	;
}
void drawModelW()
{
	glColor3f(0.5, 0.3, 0.0);
	if (!pmodelW)
	{
		pmodelW = glmReadOBJ("objs/simple_wood.obj");
		if (!pmodelW)
			exit(0);
		glmUnitize(pmodelW);
		glmFacetNormals(pmodelW);//normal do obejeto
		glmVertexNormals(pmodelW, 10);
	}
	glmDraw(pmodelW, GLM_SMOOTH | GLM_MATERIAL);

}
//Variaveis
static float sapo_x = 0, sapo_y = 0;
static float carro1_x = 0, carro2_x = 0, carro3_x = 0,  carro4_x = 0;
static float tronco2_x = 0, tronco3_x = 0,  tronco4_x = 0, tronco5_x = 0, tronco6_x = 0;
static float caminhao_x = 0;
static int direcao_carro1 = -2, direcao_carro2 = -2, direcao_carro3 = -2, direcao_carro4 = -2, direcao_caminhao = -2;
static int direcao_tronco2 = -2, direcao_tronco3 = -2, direcao_tronco4 = -2, direcao_tronco5 = -2, direcao_tronco6 = -2;
int mseg = 30;
int colisao = 0;
int vida = 1;
int colisao_tronco = 0;
int colisao_tronco2 = 0, colisao_tronco3 = 0, colisao_tronco4 = 0, colisao_tronco5 = 0, colisao_tronco6 = 0;
int ganhou = 0;
//funcoes
void init(void);
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);
void timer_callback(int value);
void DefineIluminacao();
int main(int argc, char** argv)
{
	/* inicia o GLUT */
	glutInit(&argc, argv);

	/* inicia o display usando RGB e double-buffering */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 512);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Frogger3D");
	glutTimerFunc(mseg, timer_callback, mseg);
	srand(time(NULL));

	/* Funcao com alguns comandos para a inicializacao do OpenGL; */
	init ();

	/* define as funcões de callback */
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}

/* Funcao com alguns comandos para a inicializacao do OpenGL; */
void init(void)
{

// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Habilita a definição da cor do material a partir da cor corrente
//	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
//	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
//	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de colorização de Gouraud
//	glShadeModel(GL_SMOOTH);;



}

void reshape (int w, int h)
{

	/* muda para o modo GL_PROJECTION e reinicia a projecção */
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	/* define a zona da janela onde se vai desenhar */
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	/* Define a forma do "viewing volume" para termos               *
	 * uma projecção de perspectiva (3D).                           *
	 * gluPerpective(angulo,aspecto,ponto_proximo, ponto distante); */
	gluPerspective(60, (float)w / (float)h, 1.0, 20.0);
	gluLookAt(0.0, 0.0, 5.0, 	// posição da câmera (olho)
			  0.0, 0.0, 0.0, 	// centro da cena
			  0.0, 1.0, 0.0); // direção de cima
	/* muda para o modo GL_MODELVIEW (não pretendemos alterar a projecção
	 * quando estivermos a desenhar a tela) */
	glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y)
{
	// Controla a movimentação do sapo, o sapo anda 0.25 em cada direcao, acho que ainda n e o ideal.
	switch (key)
	{

	case 'w':
	case 'W':
		if(colisao == 1) break;
		sapo_y += 0.25;
		glutPostRedisplay();
		break;

	case 's':
	case 'S':
		if(colisao == 1) break;
		sapo_y -= 0.25;
		glutPostRedisplay();
		break;

	case 'a':
	case 'A':
		if(colisao == 1) break;
		sapo_x -= 0.25;
		glutPostRedisplay();
		break;

	case 'd':
	case 'D':
		if(colisao == 1) break;
		sapo_x += 0.25;
		glutPostRedisplay();
		break;

	default:
		break;
	}
}
void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};
	GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0};     // "cor"
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"
	GLfloat posicaoLuz[4] = { -200.0, 500.0, 500.0, 10.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
	GLint especMaterial = 60;

	// Define a refletância do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
}
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa o Buffer de Cores

	glLoadIdentity();
//	DefineIluminacao();
	//essas distancias e raio e pra ver se ta tendo colisao entre o sapo e os objetos
	double raio_sapo_carro = 0.1414;
	double raio_tronco = 0.1828;
	double distanciaCarro1 = sqrtf(pow(sapo_x - carro1_x + 3 * direcao_carro1, 2) + pow(sapo_y - 2.74 + 2.4, 2 ) );
	double distanciaCarro2 = sqrtf(pow(sapo_x - carro2_x + 3 * direcao_carro2, 2) + pow(sapo_y - 2.74 + 1.8, 2 ) );
	double distanciaCarro3 = sqrtf(pow(sapo_x - carro3_x + 3 * direcao_carro3, 2) + pow(sapo_y - 2.74 + 1.4, 2 ) );
	double distanciaCarro4 = sqrtf(pow(sapo_x - carro4_x + 3 * direcao_carro4, 2) + pow(sapo_y - 2.74 + 1.1, 2 ) );
	double distanciaCaminhao = sqrtf(pow(sapo_x - caminhao_x + 3 * direcao_caminhao, 2) + pow(sapo_y - 2.74 + 2.1, 2 ) );

	double distanciaTronco2 = sqrtf(pow(sapo_x - tronco2_x + 3 * direcao_tronco2, 2) + pow(sapo_y - 2.74 - 2.2, 2 ) );
	double distanciaTronco3 = sqrtf(pow(sapo_x - tronco3_x + 3 * direcao_tronco3, 2) + pow(sapo_y - 2.74 - 1.7, 2 ) );
	double distanciaTronco4 = sqrtf(pow(sapo_x - tronco4_x + 3 * direcao_tronco4, 2) + pow(sapo_y - 2.74 - 1.2, 2 ) );
	double distanciaTronco5 = sqrtf(pow(sapo_x - tronco5_x + 3 * direcao_tronco5, 2) + pow(sapo_y - 2.74 - 0.7, 2 ) );
	double distanciaTronco6 = sqrtf(pow(sapo_x - tronco6_x + 3 * direcao_tronco6, 2) + pow(sapo_y - 2.74 - 0.2, 2 ) );
	colisao_tronco2 = 0;
	colisao_tronco3 = 0;
	colisao_tronco4 = 0;
	colisao_tronco5 = 0;
	colisao_tronco6 = 0;
	// se estiver tendo colisao com o carro, a variavel colisao recebe um,  que e game over
	if(distanciaCarro1 < 2 * raio_sapo_carro)
	{
		colisao = 1;
	}

	if(distanciaCarro2 < 2 * raio_sapo_carro)
	{
		colisao = 1;
	}

	if(distanciaCarro3 < 2 * raio_sapo_carro)
	{
		colisao = 1;
	}

	if(distanciaCarro4 < 2 * raio_sapo_carro)
	{
		colisao = 1;
	}

	if(distanciaCaminhao < 2 * raio_sapo_carro)
	{
		colisao = 1;
	}

	// se etiver tendo colisao com um tronco, eu boto um na variavel que especifica qual dos troncos
	//ta tendo colisao, alem de colocar a direcao do tronco na variavel colisao_tronco, pq o sapo
	// vai passar a transladar naquela direcao passivamente
	if(distanciaTronco2 < (raio_tronco + raio_sapo_carro))
	{
		colisao_tronco = direcao_tronco2;
		colisao_tronco2 = 1;
	}
	if(distanciaTronco3 < (raio_tronco + raio_sapo_carro))
	{
		colisao_tronco = direcao_tronco3;
		colisao_tronco3 = 1;
	}
	if(distanciaTronco4 < (raio_tronco + raio_sapo_carro))
	{
		colisao_tronco = direcao_tronco4;
		colisao_tronco4 = 1;
	}
	if(distanciaTronco5 < (raio_tronco + raio_sapo_carro))
	{
		colisao_tronco = direcao_tronco5;
		colisao_tronco5 = 1;
	}
	if(distanciaTronco6 < (raio_tronco + raio_sapo_carro))
	{
		colisao_tronco = direcao_tronco6;
		colisao_tronco6 = 1;
	}










	//Aqui e pra quando os carros e troncos sairem da tela, entao eles surguem da esquerda ou da direita
	// de maneira aleatoria
	// Com os troncos e diferente pois se o tronco sair da tela e o sapo estiver encima dele,
	// coloquei pro sapo ir junto com o tronco pra nova posicao dele
	// essa parte vai ate a linha 382
	if((direcao_carro1 == -2) ||  (carro1_x > 7 || carro1_x < -7) )
	{
		if((rand() % 2) == 1)
		{
			direcao_carro1 = -1;
		}
		else
		{
			direcao_carro1 = 1;
		}
		carro1_x = -1 * direcao_carro1 * 4;
	}
	carro1_x +=  direcao_carro1 * 0.1;


	if((direcao_carro2 == -2) ||  (carro2_x > 9 || carro2_x < -9) )
	{
		if((rand() % 2) == 1)
		{
			direcao_carro2 = -1;
		}
		else
		{
			direcao_carro2 = 1;
		}
		carro2_x = -1 * direcao_carro2 * 7;
	}
	carro2_x +=  direcao_carro2 * 0.1;


	if((direcao_carro3 == -2) ||  (carro3_x > 8 || carro3_x < -8) )
	{
		if((rand() % 2) == 1)
		{
			direcao_carro3 = -1;
		}
		else
		{
			direcao_carro3 = 1;
		}
		carro3_x = -1 * direcao_carro3 * 6;
	}
	carro3_x +=  direcao_carro3 * 0.1;

	if((direcao_carro4 == -2) ||  (carro4_x > 8 || carro4_x < -8) )
	{
		if((rand() % 2) == 1)
		{
			direcao_carro4 = -1;
		}
		else
		{
			direcao_carro4 = 1;
		}
		carro4_x = -1 * direcao_carro4 * 6;
	}
	carro4_x +=  direcao_carro4 * 0.1;

	if((direcao_caminhao == -2) ||  (caminhao_x > 8 || caminhao_x < -8) )
	{
		if((rand() % 2) == 1)
		{
			direcao_caminhao = -1;
		}
		else
		{
			direcao_caminhao = 1;
		}
		caminhao_x = -1 * direcao_caminhao * 6;
	}
	caminhao_x +=  direcao_caminhao * 0.05;




//    if((direcao_tronco1 == -2) ||  (tronco1_x > 7 || tronco1_x < -7) )
	// {
	// 	if((rand() % 2) == 1)
	// 	{
	// 		direcao_tronco1 = -1;
	// 	}
	// 	else
	// 	{
	// 		direcao_tronco1 = 1;
	// 	}
//    		tronco1_x = -1*direcao_tronco1 * 4;
	// }
//    tronco1_x+=  direcao_tronco1 * 0.05;


	if((direcao_tronco2 == -2) ||  (tronco2_x > 9 || tronco2_x < -9) )
	{
		if((rand() % 2) == 1)
		{
			direcao_tronco2 = -1;
		}
		else
		{
			direcao_tronco2 = 1;
		}
		tronco2_x = -1 * direcao_tronco2 * 7;
		if(colisao_tronco2 == 1) sapo_x = tronco2_x - 3 * direcao_tronco2 + direcao_tronco2 * 0.025 ;
	}
	tronco2_x +=  direcao_tronco2 * 0.025;


	if((direcao_tronco3 == -2) ||  (tronco3_x > 8 || tronco3_x < -8) )
	{
		if((rand() % 2) == 1)
		{
			direcao_tronco3 = -1;
		}
		else
		{
			direcao_tronco3 = 1;
		}
		tronco3_x = -1 * direcao_tronco3 * 6;
		if(colisao_tronco3 == 1) sapo_x = tronco3_x + direcao_tronco3 * 0.025 - 3 * direcao_tronco3 ;
	}
	tronco3_x +=  direcao_tronco3 * 0.025;

	if((direcao_tronco4 == -2) ||  (tronco4_x > 8 || tronco4_x < -8) )
	{
		if((rand() % 2) == 1)
		{
			direcao_tronco4 = -1;
		}
		else
		{
			direcao_tronco4 = 1;
		}
		tronco4_x = -1 * direcao_tronco4 * 6;
		if(colisao_tronco4 == 1) sapo_x = tronco4_x + direcao_tronco4 * 0.025 - 3 * direcao_tronco4 ;
	}
	tronco4_x +=  direcao_tronco4 * 0.025;

	if((direcao_tronco5 == -2) ||  (tronco5_x > 8 || tronco5_x < -8) )
	{
		if((rand() % 2) == 1)
		{
			direcao_tronco5 = -1;
		}
		else
		{
			direcao_tronco5 = 1;
		}
		tronco5_x = -1 * direcao_tronco5 * 6;
		if(colisao_tronco5 == 1) sapo_x = tronco5_x + direcao_tronco5 * 0.025 - 3 * direcao_tronco5 ;
	}
	tronco5_x +=  direcao_tronco5 * 0.025;

	if((direcao_tronco6 == -2) ||  (tronco6_x > 8 || tronco6_x < -8) )
	{
		if((rand() % 2) == 1)
		{
			direcao_tronco6 = -1;
		}
		else
		{
			direcao_tronco6 = 1;
		}
		tronco6_x = -1 * direcao_tronco6 * 6;
		if(colisao_tronco6 == 1) sapo_x = tronco6_x + direcao_tronco6 * 0.025 - 3 * direcao_tronco6 ;
	}
	tronco6_x +=  direcao_tronco6 * 0.025;


	// aqui e so o desenho dos objetos
	// a colisao com a agua n foi feita usando esferas, se o sapo tiver entre certo valor de Y(entre a
	//segunda calcada e o mato), e nao estiver colidindo com algum tronco, entao quer dizer que ele
	// esta afodago
	// CALCADA1
	glPushMatrix();
	glTranslatef(0.0, -3.3, -1.0);
	glPushMatrix();
	glScalef (2.0, 0.05, 0.0125);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidCube (8.0);
	glPopMatrix();
	glPopMatrix();

	//RUA
	glPushMatrix();
	glTranslatef(0.0, -2.5, -1.0);
	glPushMatrix();
	glScalef (2.0, 0.5, 0.0125);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidCube (8.0);
	glPopMatrix();
	glPopMatrix();

	//CALCADA2
	glPushMatrix();
	glTranslatef(0.0, -0.3, -1.0);
	glPushMatrix();
	glScalef (2.0, 0.07, 0.0125);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidCube (8.0);
	glPopMatrix();
	glPopMatrix();

	// LAGO
	glPushMatrix();
	glTranslatef(0.0, 1.0, -1.0);
	glPushMatrix();
	glScalef (2.0, 0.5, 0.0125);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube (8.0);
	glPopMatrix();
	glPopMatrix();

	//MATO
	glPushMatrix();
	glTranslatef(0.0, 3.0, -1.0);
	glPushMatrix();
	glScalef (2.0, 0.125, 0.0125);
	glColor3f(0.5, 1.0, 0.0);
	glutSolidCube (8.0);
	glPopMatrix();
	glPopMatrix();




	// CARRO1
	glPushMatrix();
	glTranslatef( direcao_carro1 * -3.0, -2.4, 0.0);
	glPushMatrix();
	glTranslatef (carro1_x, 0.0, 0.0);
	glScalef (0.2, 0.20, 0.1);
	glRotatef ((GLfloat) 90, 0.0, 0.0, 0.0);
	drawModelC();
	glPopMatrix();
	glPopMatrix();

	// CARRO2
	glPushMatrix();
	glTranslatef(direcao_carro2 * -3.0, -1.8, 0.0);
	glPushMatrix();
	glTranslatef (carro2_x, 0.0, 0.0);
	glScalef (0.2, 0.20, 0.1);
	drawModelC();
	glPopMatrix();
	glPopMatrix();

	// CARRO3
	glPushMatrix();
	glTranslatef(direcao_carro3 * -3.0, -1.4, 0.0);
	glPushMatrix();
	glTranslatef (carro3_x, 0.0, 0.0);
	glScalef (0.2, 0.20, 0.1);
	drawModelC();
	glPopMatrix();
	glPopMatrix();


	// CARRO4
	glPushMatrix();
	glTranslatef(direcao_carro4 * -3.0, -1.1, 0.0);
	glPushMatrix();
	glTranslatef (carro4_x, 0.0, 0.0);
	glScalef (0.2, 0.20, 0.1);

	drawModelC();

	glPopMatrix();
	glPopMatrix();

	// CAMINHAO
	glPushMatrix();
	glTranslatef(direcao_caminhao * -3.0, -2.1, 0.0);
	glPushMatrix();
	glTranslatef (caminhao_x, 0.0, 0.0);
	glScalef (0.6, 0.60, 0.1);
	glRotatef ((GLfloat) 90, 1.0, 0.0, 0.0);
	drawModelCm();
	glPopMatrix();
	glPopMatrix();


	// TRONCO1
//    glPushMatrix();
	// glTranslatef( direcao_tronco1 * -3.0, 2.7, 0.0);
	// 	glPushMatrix();
	// 	glTranslatef (tronco1_x, 0.0, 0.0);
	// 	glScalef (1.0, 0.40, 0.1);
	// 	glColor3f(0.4,0.0,0.0);

	// 	glPopMatrix();
	// glPopMatrix();

	// TRONCO2
	glPushMatrix();
	glTranslatef(direcao_tronco2 * -3.0, 2.2, 0.0);
	glPushMatrix();
	glTranslatef (tronco2_x, 0.0, 0.0);
	glScalef (0.8, 0.80, 0.1);
	drawModelW();

	glPopMatrix();
	glPopMatrix();

	// TRONCO3

	glPushMatrix();
	glTranslatef(direcao_tronco3 * -3.0, 1.7, 0.0);
	glPushMatrix();
	glTranslatef (tronco3_x, 0.0, 0.0);
	glScalef (0.8, 0.80, 0.1);
	drawModelW();
	glPopMatrix();
	glPopMatrix();


	// TRONCO4
	glPushMatrix();
	glTranslatef(direcao_tronco4 * -3.0, 1.2, 0.0);
	glPushMatrix();
	glTranslatef (tronco4_x, 0.0, 0.0);
	glScalef (0.8, 0.80, 0.1);
	drawModelW();
	glPopMatrix();
	glPopMatrix();

	// TRONCO5
	glPushMatrix();
	glTranslatef(direcao_tronco5 * -3.0, 0.7, 0.0);
	glPushMatrix();
	glTranslatef (tronco5_x, 0.0, 0.0);
	glScalef (0.8, 0.80, 0.1);
	drawModelW();
	glPopMatrix();
	glPopMatrix();


	// TRONCO6
	glPushMatrix();
	glTranslatef(direcao_tronco6 * -3.0, 0.2, 0.0);
	glPushMatrix();
	glTranslatef (tronco6_x, 0.0, 0.0);
	glScalef (0.8, 0.80, 0.1);
	drawModelW();
	glPopMatrix();
	glPopMatrix();


	// SAPO
	glPushMatrix();
	glTranslatef(0.0, -2.74, 0.0);
	glPushMatrix();
	if(colisao_tronco == 0 && (sapo_y - 2.4) > 0.58 && (sapo_y - 2.4 < 2.75) ) colisao = 1;
	if(colisao_tronco != 0)
	{
		sapo_x += colisao_tronco * 0.025;
		printf("aconteceu colisao com o tronco\n");
	}
	glTranslatef (sapo_x, sapo_y, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glScalef (0.2, 0.2, 0.2);
	glRotatef ((GLfloat) 90, 0.0, 0.0, 1.0);
	if(colisao == 1 && ganhou == 0)
	{
		glColor3f(1.0, 0.0, 0.0);
		if(vida == 1) printf(" GAME OVER!");
		vida = 0;
	}
	if((sapo_y - 2.4) > 3){
		printf("VOCE GANHOU! PARABENS !!!!!\n");
		colisao = 1;
		ganhou = 1;
	}
	drawModelS();
	colisao_tronco = 0;
	/* Troca os buffers, mostrando o que acabou de ser desenhado */

}


void timer_callback(int value)
{
	glutTimerFunc(value, timer_callback, value);
	glutPostRedisplay(); // Manda redesenhar a tela em cada frame
}

