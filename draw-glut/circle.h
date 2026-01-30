//*********************************************************************
//  Computacao Grafica usando OpenGL
//  Codigo Exemplo - 05/2008 - atualizado 10/2016
//
//  Autor: Prof. Laurindo de Sousa Britto Neto
//*********************************************************************

// Bibliotecas utilizadas pelo OpenGL

#include <math.h>

void desenhaCirculo(float raio, int num_linhas, bool preenchido, float trans_x, float trans_y)
{
	int i;
	GLfloat angulo;
	glTranslatef(trans_x, trans_y, 0);
	angulo = 2 * M_PI / num_linhas; //divide 360� pela quantidade de linhas que serao desenhadas

	if(preenchido)
		glBegin(GL_TRIANGLE_FAN); // Primitiva que liga os pontos gerando segmentos de reta em um loop

	else glBegin(GL_LINE_LOOP);

	for(i = -10; i <= num_linhas - 10; i++) // for usado para o calculo de cada ponto pertencente aos extremos das retas
	{
		// comando que calcula as coord. da rota��o e desenha as retas na tela
		//    glVertex2f(-raio*sin(i * angulo) , raio*cos(i * angulo) );	// centro = (0,0), x = 0 e y = raio;
		glColor3f(0, 255, 0);
		glVertex2f(raio * cos(i * angulo) , raio * sin(i * angulo));		// centro = (0,0), x = raio e y = 0;

	}
	glEnd();
}

