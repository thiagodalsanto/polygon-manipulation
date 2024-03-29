﻿//---------------------------------------------------------------------------

#pragma hdrstop
#define SIGN(x) ((x) < 0 ? (-1): (1))
#define ABS(x) ((x) < 0 ? (-x) : (x))
#define FLOOR(x) ((x) < 0 ? ( (x) - (double)(x) != 0 ? ((double)(x) - 1) : ((int)(x))) : (double)(x))
#include <math.h>
#include "uPoligono.h"
#include "uJanela.h"
#include "Cordenadas3D.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)

void Poligono::desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta) {

	if(tipo == 'O' || tipo == 'W'){
	   for(int x = 0; x < cordenadas3d.size() - 1; x++) {
		   canvas->Pixels[cordenadas3d[x].xW2Vp(mundo, vp)][cordenadas3d[x].yW2Vp(mundo, vp)]
		   = (tipo == 'O')? clMaroon : clWhite;
		}
	} else
	{
		switch (tipoReta){

			case 0:moveTo(canvas,mundo,vp);
			break;

			case 1:
			for(float x = 0; x < cordenadas3d.size() - 1; x++) {
				DDA(cordenadas3d[x], cordenadas3d[x+1], canvas, mundo, vp, tipo);
			}
			break;

			case 2:
			for(int x = 0; x < cordenadas3d.size() - 1; x++) {
				Bresenham(cordenadas3d[x], cordenadas3d[x+1], canvas, mundo, vp);
			}
			break;
		}

	}

}

void Poligono::moveTo(TCanvas *canvas, Janela mundo, Janela vp){

	for (int x = 0; x < cordenadas3d.size(); x++){
		if (x==0)
		  canvas->MoveTo(cordenadas3d[x].xW2Vp(mundo, vp),
						 cordenadas3d[x].yW2Vp(mundo, vp));
		 else{

			if(tipo == 'R')
				canvas->Pen->Color = clTeal;
			else
				canvas->Pen->Color = clRed;
			canvas->LineTo(cordenadas3d[x].xW2Vp(mundo, vp),cordenadas3d[x].yW2Vp(mundo, vp));
		 }
	}
}

void Poligono::DDA(Ponto P1, Ponto P2, TCanvas *canvas, Janela mundo, Janela vp, char tipo) {

	double x, x1, x2, y, y1, y2, lenght, deltax, deltay;
	x1 = P1.xW2Vp(mundo,vp);
	x2 = P2.xW2Vp(mundo,vp);
	y1 = P1.yW2Vp(mundo,vp);
	y2 = P2.yW2Vp(mundo,vp);

	if(ABS((x2 - x1)) >= ABS((y2 - y1))) {
		lenght = ABS((x2 - x1));
	}
	else {
		lenght = ABS((y2 - y1));
	}

	deltax = (x2-x1 != 0 )? (x2 -x1) / lenght : 0 ;
	deltay = (y2-y1 != 0 )? (y2 - y1) / lenght: 0 ;
	x = x1 + 0.5 * SIGN(deltax);
	y = y1 + 0.5 * SIGN(deltay);

	for ( int i = 0; i < lenght; i++) {
		if(tipo == 'R')
			canvas->Pixels[FLOOR(x)][FLOOR(y)] = clTeal;
		else
			canvas->Pixels[FLOOR(x)][FLOOR(y)] = clBlack;
		x = x + deltax;
		y = y + deltay;
	}

}

void Poligono:: Bresenham(Ponto P1, Ponto P2, TCanvas *canvas, Janela mundo, Janela vp){

	float x, x1, x2, y, y1, y2, tmp, erro;
	double deltax, deltay, signalx, signaly;
	int interchange;

	x1 = P1.xW2Vp(mundo,vp);
	x2 = P2.xW2Vp(mundo,vp);
	y1 = P1.yW2Vp(mundo,vp);
	y2 = P2.yW2Vp(mundo,vp);

	deltax = ABS((x2 - x1));
	deltay = ABS((y2 - y1));
	signalx = SIGN((x2 - x1));
	signaly = SIGN((y2 - y1));
	x = x1;
	y = y1;

	if (signalx < 0) {
		x = x - 1;
	}
	if(signaly < 0) {
		y = y - 1;
	}

	interchange = false;
	if (deltay > deltax) {
		tmp = deltax;
		deltax = deltay;
		deltay = tmp;
		interchange = true;
	}

	erro = 2 * deltay - deltax;

	for(int i = 0; i < deltax; i++) {
		if(tipo == 'R')
			canvas->Pixels[FLOOR(x)][FLOOR(y)] = clTeal;
		else
			canvas->Pixels[FLOOR(x)][FLOOR(y)] = clFuchsia;
		while (erro >= 0) {
			if (interchange) {
				x = x + signalx;
			}
			else  {
				y = y + signaly;
			}

			erro = erro - 2 * deltax;
		}
		if(interchange) {
			y = y + signaly;
		}
		else  {
			x = x + signalx;
		}

		erro = erro + 2 * deltay;
	}

}

UnicodeString Poligono::toString(){
  return IntToStr(id) + " - " + tipo + " - " + IntToStr((int)cordenadas3d.size()) + " Pontos";
}

void Poligono::mostra(TListBox *lb) {

	lb->Items->Clear();

	for (int x = 0; x < cordenadas3d.size(); x++)
	{
		lb->Items->Add(cordenadas3d[x].toString());
	}
}

void Poligono::transladar(float dx, float dy) {

	for (int x = 0; x < cordenadas3d.size(); x++) {
		cordenadas3d[x].transladar(dx, dy);
	}

}

void Poligono::escalonar(double dx, double dy) {

	for (int x = 0; x < cordenadas3d.size(); x++) {
		cordenadas3d[x].escalonar(dx, dy);
	}

}

void Poligono::rotacao(double angulo) {

	for (int x = 0; x < cordenadas3d.size(); x++) {
		cordenadas3d[x].rotacao(angulo);
	}

}

void Poligono::reflexao(double dx, double dy) {

	for (int x = 0; x < cordenadas3d.size(); x++) {
		cordenadas3d[x].transladar(dx, dy);
	}

}

Ponto Poligono::pontoMedio(){

	double somaX = 0;
	double somaY = 0;

	for (int i = 0; i < cordenadas3d.size(); i++) {

		somaX += cordenadas3d[i].x;
		somaY += cordenadas3d[i].y;

	}

	somaX = somaX / cordenadas3d.size();
	somaY = somaY / cordenadas3d.size();

	return Cordenadas3D(somaX, somaY, 0);

}

Cordenadas3D Poligono::pontoMedioZ(){

	double somaX = 0;
	double somaY = 0;
	double somaZ = 0;

	for (int i = 0; i < cordenadas3d.size(); i++) {

		somaX += cordenadas3d[i].x;
		somaY += cordenadas3d[i].y;
		somaZ += cordenadas3d[i].z;

	}

	somaX = somaX / cordenadas3d.size();
	somaY = somaY / cordenadas3d.size();
	somaZ = somaZ / cordenadas3d.size();

	return Cordenadas3D(somaX, somaY, somaZ);

}

//Homogenea para 2D
void Poligono::ComHomogenea(float dx, float dy,float sx, float sy,double angulo,int tipo){

	float matrix[3][3]={0,0,0,0,0,0,0,0,0};
	float aux[1][3] = {0,0,0};
	float px,py;
	float poli[1][3] = {1,1 , 1};
	Ponto centro;
	double grau;

	grau = (angulo * 3.14) / 180;

	switch (tipo){

	//Se Transladar
	case 0:
		matrix[0][0] = 1;
		matrix[1][1] = 1;
		matrix[2][2] = 1;
		matrix[2][0]=dx;
		matrix[2][1]=dy;
		break;

	//Se Escalonar
	case 1:
		matrix[0][0] = sx;
		matrix[1][1] = sy;
		matrix[2][2] = 1;
		break;

	//Se Rotacionar
	case 2:
		centro = pontoMedio();
		ComHomogenea(-centro.x,-centro.y, 0,0,0,0);
		matrix[0][0] = (cos(grau));
		matrix[0][1] = (sin(grau));
		matrix[1][1] = (cos(grau));
		matrix[2][2] = 1;
		matrix[1][0] = -sin(grau);
		break;

    //Reflexões Horizontal, Vertical e Diagonal
	case 3:
		matrix[0][0] = 1;
		matrix[1][1] = -1;
		matrix[2][2] = 1;
		break;

	case 4:
		matrix[0][0] = -1;
		matrix[1][1] = 1;
		matrix[2][2] = 1;
		break;
	case 5:
		matrix[0][0] = -1;
		matrix[1][1] = -1;
		matrix[2][2] = 1;
		break;

	}

    //Muda o Poligono
	for(int x = 0; x < cordenadas3d.size(); x++ ){

		px=cordenadas3d[x].x;
		py=cordenadas3d[x].y;
		poli[0][0] = px;
		poli[0][1] = py;

		for(int i = 0 ; i < 1 ; i++){
			for(int j=0; j<3 ; j++){

				aux[i][j] = 0;

				for(int k = 0; k<3 ; k++){

					aux[i][j] = aux[i][j] + poli[i][k] * matrix[k][j] ;

				}

			}

		}

		 cordenadas3d[x].x = aux[0][0];
		 cordenadas3d[x].y = aux[0][1];
	}


	if(tipo == 2){
		ComHomogenea(centro.x,centro.y, 0,0,0,0);
	}


}

//Homogenea para 3D
void Poligono::ComHomogenea(float dx, float dy, float dz,float sx, float sy,float sz,double angulo,int tipo){

	float matrix[4][4]={0,0,0,0,0,0,0,0,0,0,0,0,0};
	float aux[1][4] = {0,0,0,0};
	float px,py,pz;
	float poli[1][4] = {1,1,1,1};
	Cordenadas3D centro;
	double grau;

    grau = (angulo * 3.14) / 180;

	switch (tipo){

		//Se Transladar
		case 0:
			matrix[0][0] = 1;
			matrix[1][1] = 1;
			matrix[2][2] = 1;
			matrix[3][3] = 1;
			matrix[3][0]=dx;
			matrix[3][1]=dy;
			matrix[3][2]=dz;
			break;

		//Se Escalonar
		case 1:
			matrix[0][0] = sx;
			matrix[1][1] = sy;
			matrix[2][2] = sz;
			matrix[3][3] = sz;
			matrix[4][4] = 1;
			break;

		//Se Rotacionar
		case 2:
			centro = pontoMedioZ();
			ComHomogenea(-centro.x,-centro.y,-centro.z,0,0,0,0,0);

			matrix[2][2] = (cos(grau));
			matrix[1][2] = (sin(grau));
			matrix[0][0] = 1;
			matrix[1][1] = (cos(grau));
			matrix[3][3] = 1; matrix[2][1] = (-sin(grau));
			break;

        //Se Rotacionar tbm
		case 3:
			centro = pontoMedioZ();
			ComHomogenea(-centro.x,-centro.y,-centro.z,0,0,0,0,0);

			matrix[0][0] = (cos(grau));
			matrix[2][0] = (sin(grau));
			matrix[3][3] = 1;
			matrix[2][2] = (cos(grau));
			matrix[1][1] = 1;
			matrix[0][2] = (-sin(grau));
			break;


	}

	//Muda o Poligono
	for(int x=0; x < cordenadas3d.size(); x++ ){

		px=cordenadas3d[x].x;
		py=cordenadas3d[x].y;
		pz=cordenadas3d[x].z;
		poli[0][0] = px;
		poli[0][1] = py;
		poli[0][2] = pz;

		for(int i = 0 ; i < 1 ; i++){
			for(int j=0; j<4 ; j++){

				aux[i][j] = 0;

				for(int k = 0; k<4 ; k++){

					aux[i][j] = aux[i][j] + poli[i][k] * matrix[k][j] ;

				}

			}

		}

		 cordenadas3d[x].x = aux[0][0];
		 cordenadas3d[x].y = aux[0][1];
		 cordenadas3d[x].z = aux[0][2];
	}


	if(tipo == 2 || tipo == 3){
		ComHomogenea(centro.x,centro.y,centro.z,0,0,0,0,0);
	}

}

void Poligono::Circunferencia( double xCentral, double yCentral, double raio, Poligono *aux) {
	double x, y, p;
	x  = 0;
	y = raio;

	DesenhaCircunferencia(xCentral, yCentral, x, y, aux);
	p = 1 - raio;

	while(x < y) {
        //Calcula X e Y
		x++;
		if(p >= 0) {
            y--;
		}

		//Decide se é cima ou baixo
		if(p < 0) {
			p = p + 2 * x + 1;
		}

		else {
			p = p + 2 * (x - y) + 1;
		}
		DesenhaCircunferencia(xCentral, yCentral, x, y, aux);
	}

}

void Poligono::DesenhaCircunferencia(double xCentral, double yCentral, double x, double y, Poligono *aux) {

	aux->cordenadas3d.push_back(Cordenadas3D(xCentral + x, yCentral + y,0));
	aux->cordenadas3d.push_back(Cordenadas3D(xCentral - x, yCentral + y,0));
	aux->cordenadas3d.push_back(Cordenadas3D(xCentral - y ,yCentral + x,0));
	aux->cordenadas3d.push_back(Cordenadas3D(xCentral - y, yCentral - x,0));
	aux->cordenadas3d.push_back(Cordenadas3D(xCentral - x, yCentral - y,0));
	aux->cordenadas3d.push_back(Cordenadas3D(xCentral + x, yCentral - y,0));
	aux->cordenadas3d.push_back(Cordenadas3D(xCentral + y, yCentral - x,0));
	aux->cordenadas3d.push_back(Cordenadas3D(xCentral + y, yCentral + x,0));

}

int Poligono::Cohen(Janela clipping, double x, double y) {

	int retorno = 0;

	if(x < clipping.xmin) //Ponto 0001 (<)
		retorno += 1;
	else
		if(x > clipping.xmax) //Ponto 0010 (>)
			retorno += 2;

	if(y < clipping.ymin) //Ponto 0100 (\/)
		retorno += 4;
	else
		if(y > clipping.ymax) //Ponto 1000 (/\)
			retorno += 8;

	return retorno;

}

Poligono Poligono::Clip(Janela clipping, Poligono pol){

	Poligono aux;
	Cordenadas3D p1, p2;
	int codClippingUm, codClippingDois;

	for (int i = 0; i < pol.cordenadas3d.size() - 1; i++) {
		p1 = pol.cordenadas3d[i];
		p2 = pol.cordenadas3d[i + 1];

		//Clipping de P1 e P2
		codClippingUm = Cohen(clipping, p1.x, p1.y);
		codClippingDois = Cohen(clipping, p2.x, p2.y);

		bool temCondicoes = false;

		//Condicoes
		while (temCondicoes == false) {
			if ((codClippingUm == 0) && (codClippingDois == 0)) { //Tudo dentro
				temCondicoes = true;

			}
			else
			if (codClippingUm & codClippingDois) {
				break;
			}
			else {
				int codFora;
				double x, y;

				codFora = (codClippingUm != 0) ? codClippingUm : codClippingDois;

				if (codFora & 8) {

					x = p1.x + (p2.x - p1.x) * (clipping.ymax - p1.y) / (p2.y - p1.y);
					y = clipping.ymax;

				}
				else if (codFora & 4) {

					x = p1.x + (p2.x - p1.x) * (clipping.ymin - p1.y) / (p2.y - p1.y);
					y = clipping.ymin;

				}
				else if (codFora & 2) {

					y = p1.y + (p2.y - p1.y) * (clipping.xmax - p1.x) / (p2.x - p1.x);
					x = clipping.xmax;

				}
				else if (codFora & 1) {

					y = p1.y + (p2.y - p1.y) * (clipping.xmin - p1.x) / (p2.x - p1.x);
					x = clipping.xmin;

				}
				if (codFora == codClippingUm) {

					p1.x = x;
					p1.y = y;
					codClippingUm = Cohen(clipping, p1.x, p1.y);

				}
				else {

					p2.x = x;
					p2.y = y;
					codClippingDois = Cohen(clipping, p2.x, p2.y);

				}
			}
		}

		if(temCondicoes){
			aux.cordenadas3d.push_back(p1);
			aux.cordenadas3d.push_back(p2);
		}


	}
	return aux;

}

//Faz Casteljau
Poligono Poligono::casteljau(Poligono *pol){

		Poligono curva;
		Poligono aux;

		aux.cordenadas3d.push_back(pol->cordenadas3d[0]);
		aux.cordenadas3d.push_back(pol->cordenadas3d[1]);
		aux.cordenadas3d.push_back(pol->cordenadas3d[2]);
		curva.cordenadas3d.push_back(pol->cordenadas3d[0]);
		desenhaCasteljauRec(&curva, aux);

		return curva;

}

//Desenha
void Poligono::desenhaCasteljauRec(Poligono*curva, Poligono aux) {

	Poligono curvaEsquerda;
	Poligono curvaDireita;

	if (distanciaPontos(aux.cordenadas3d[0], aux.cordenadas3d[2]) < 1) {
			curva->cordenadas3d.push_back(aux.cordenadas3d[0]);
	}

	else {
			subdividirCurva(aux, &curvaEsquerda, &curvaDireita);
			desenhaCasteljauRec(curva, curvaEsquerda);
			desenhaCasteljauRec(curva, curvaDireita);
	}
}

//Distancia Euclidiana
double Poligono::distanciaPontos(Ponto p1, Ponto p2) {

	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));

}

//Calcula Pontos Medios
void Poligono::subdividirCurva(Poligono aux, Poligono*curvaEsquerda, Poligono*curvaDireita) {

	Cordenadas3D pontoMedio1 = pontoMedio(aux.cordenadas3d[0], aux.cordenadas3d[1]);
	Cordenadas3D pontoMedio2 = pontoMedio(aux.cordenadas3d[1], aux.cordenadas3d[2]);
	Cordenadas3D pontoMedio3 = pontoMedio(pontoMedio1, pontoMedio2);

	//Pontos medios a Esquerda
	curvaEsquerda->cordenadas3d.push_back(aux.cordenadas3d[0]);
	curvaEsquerda->cordenadas3d.push_back(pontoMedio1);
	curvaEsquerda->cordenadas3d.push_back(pontoMedio3);

	//Pontos medios a Direita
	curvaDireita->cordenadas3d.push_back(pontoMedio3);
	curvaDireita->cordenadas3d.push_back(pontoMedio2);
	curvaDireita->cordenadas3d.push_back(aux.cordenadas3d[2]);
}

//Calculo de Ponto Medio
Cordenadas3D Poligono::pontoMedio(Ponto p1, Ponto p2) {

	Cordenadas3D medio;
	medio.x = (p1.x + p2.x) / 2;
	medio.y = (p1.y + p2.y) / 2;
	return medio;

}

void Poligono::hermite(Poligono *pol) {

	double ghX[4], ghY[4];
	int mH[4][4] = {2, -2, 1, 1, -3, 3, -2, -1, 0, 0, 1, 0, 1, 0, 0, 0};

	ghX[0] = cordenadas3d[0].x; //P1
	ghX[1] = cordenadas3d[3].x; //P4
	ghX[2] = cordenadas3d[1].x - cordenadas3d[0].x; //R1
	ghX[3] = cordenadas3d[3].x - cordenadas3d[2].x; //R4

	ghY[0] = cordenadas3d[0].y; //P1
	ghY[1] = cordenadas3d[3].y; //P4
	ghY[2] = cordenadas3d[1].y - cordenadas3d[0].y; //R1
	ghY[3] = cordenadas3d[3].y - cordenadas3d[2].y; //R4

	double coefHermiteX[4] =
		{
		ghX[0] * mH[0][0] + ghX[1] * mH[0][1] + ghX[2] * mH[0][2] + ghX[3] * mH[0][3],
		ghX[0] * mH[1][0] + ghX[1] * mH[1][1] + ghX[2] * mH[1][2] + ghX[3] * mH[1][3],
		ghX[0] * mH[2][0] + ghX[1] * mH[2][1] + ghX[2] * mH[2][2] + ghX[3] * mH[2][3],
		ghX[0] * mH[3][0] + ghX[1] * mH[3][1] + ghX[2] * mH[3][2] + ghX[3] * mH[3][3]
		};

	double coefHermiteY[4] =
		{
		ghY[0] * mH[0][0] + ghY[1] * mH[0][1] + ghY[2] * mH[0][2] + ghY[3] * mH[0][3],
		ghY[0] * mH[1][0] + ghY[1] * mH[1][1] + ghY[2] * mH[1][2] + ghY[3] * mH[1][3],
		ghY[0] * mH[2][0] + ghY[1] * mH[2][1] + ghY[2] * mH[2][2] + ghY[3] * mH[2][3],
		ghY[0] * mH[3][0] + ghY[1] * mH[3][1] + ghY[2] * mH[3][2] + ghY[3] * mH[3][3]
		};

	//tempo, coefHermiteX && tempo, coefHermiteY
	for (float tempo = 0; tempo <= 1; tempo += 0.001) {

		pol->cordenadas3d.push_back(Cordenadas3D((pow(tempo, 3)*coefHermiteX[0])
		+ (pow(tempo, 2)*coefHermiteX[1])
		+ (tempo*coefHermiteX[2]) + coefHermiteX[3], (pow(tempo, 3)*coefHermiteY[0])
		+ (pow(tempo, 2)*coefHermiteY[1])
		+ (tempo*coefHermiteY[2]) + coefHermiteY[3],0));

	}

}

void Poligono::bezier(Poligono *pol) {

	double gbX[4], gbY[4];
	//Matriz Hermite
	int mH[4][4] = {2, -2, 1, 1, -3, 3, -2, -1, 0, 0, 1, 0, 1, 0, 0, 0};

	gbX[0] = cordenadas3d[0].x; //P1
	gbX[1] = cordenadas3d[3].x; //P4
	gbX[2] = 3 * (cordenadas3d[1].x - cordenadas3d[0].x); //R1
	gbX[3] = 3 * (cordenadas3d[3].x - cordenadas3d[2].x); //R4

	gbY[0] = cordenadas3d[0].y;
	gbY[1] = cordenadas3d[3].y;
	gbY[2] = 3 * (cordenadas3d[1].y - cordenadas3d[0].y);
	gbY[3] = 3 * (cordenadas3d[3].y - cordenadas3d[2].y);

	double coefHermiteX[4] =
		{
		gbX[0] * mH[0][0] + gbX[1] * mH[0][1] + gbX[2] * mH[0][2] + gbX[3] * mH[0][3],
		gbX[0] * mH[1][0] + gbX[1] * mH[1][1] + gbX[2] * mH[1][2] + gbX[3] * mH[1][3],
		gbX[0] * mH[2][0] + gbX[1] * mH[2][1] + gbX[2] * mH[2][2] + gbX[3] * mH[2][3],
		gbX[0] * mH[3][0] + gbX[1] * mH[3][1] + gbX[2] * mH[3][2] + gbX[3] * mH[3][3]
		};

	double coefHermiteY[4] =
		{
		gbY[0] * mH[0][0] + gbY[1] * mH[0][1] + gbY[2] * mH[0][2] + gbY[3] * mH[0][3],
		gbY[0] * mH[1][0] + gbY[1] * mH[1][1] + gbY[2] * mH[1][2] + gbY[3] * mH[1][3],
		gbY[0] * mH[2][0] + gbY[1] * mH[2][1] + gbY[2] * mH[2][2] + gbY[3] * mH[2][3],
		gbY[0] * mH[3][0] + gbY[1] * mH[3][1] + gbY[2] * mH[3][2] + gbY[3] * mH[3][3]
		};

	//tempo, coefBezierX && tempo, coefBezierY
	for (float tempo = 0; tempo <= 1; tempo += 0.001) {

		pol->cordenadas3d.push_back(Cordenadas3D((pow(tempo, 3)*coefHermiteX[0])
		+ (pow(tempo, 2)*coefHermiteX[1])
		+ (tempo*coefHermiteX[2]) + coefHermiteX[3], (pow(tempo, 3)*coefHermiteY[0])
		+ (pow(tempo, 2)*coefHermiteY[1])
		+ (tempo*coefHermiteY[2]) + coefHermiteY[3],0));

	}
}

void Poligono::Bspline(Poligono *pol) {

	double xt, yt;

	//Começa no ponto 3
	for (int i = 3; i < cordenadas3d.size(); i++)
		for (double t = 0; t <= 1; t += 0.01) {

			//Calcula x da interpolacao
			xt = (cordenadas3d[i - 3].x * pow((1 - t), 3)) / 6 +
				(cordenadas3d[i - 2].x * (3 * pow(t, 3) - 6 * pow(t, 2) + 4)) / 6 +
				(cordenadas3d[i - 1].x * (3 * (-1 * pow(t, 3) + pow(t, 2) + t) + 1))
				/ 6 + (cordenadas3d[i].x * pow(t, 3)) / 6;

			//Calcula y da interpolacao
			yt = (cordenadas3d[i - 3].y * pow((1 - t), 3)) / 6 +
				(cordenadas3d[i - 2].y * (3 * pow(t, 3) - 6 * pow(t, 2) + 4)) / 6 +
				(cordenadas3d[i - 1].y * (3 * (-1 * pow(t, 3) + pow(t, 2) + t) + 1))
				/ 6 + (cordenadas3d[i].y * pow(t, 3)) / 6;
			pol->cordenadas3d.push_back(Cordenadas3D(xt, yt,0));

		}
}

void Poligono::forward(Poligono *pol) {

	double xt, yt;
	float pontoAx, pontoAy, pontoBx, pontoBy, pontoCx, pontoCy;

	//calcula cordenadas3d a, b, c
	pontoCx = 3 * (cordenadas3d[1].x - cordenadas3d[0].x);
	pontoCy = 3 * (cordenadas3d[1].y - cordenadas3d[0].y);

	pontoBx = 3 * (cordenadas3d[2].x - cordenadas3d[1].x) - pontoCx;
	pontoBy = 3 * (cordenadas3d[2].y - cordenadas3d[1].y) - pontoCy;

	pontoAx = cordenadas3d[3].x - cordenadas3d[0].x - pontoCx - pontoBx;
	pontoAy = cordenadas3d[3].y - cordenadas3d[0].y - pontoCy - pontoBy;

	//Delta, Delta ao Quadrado, Delta ao Cubo e Delta's F0
	float delta = 1.0f / 1000, deltaQuadrado = delta * delta, deltaCubo = deltaQuadrado * delta;
	float deltaf0X, deltaf0Y, deltaF0XQuad, deltaF0YQuad, deltaF0XCubo, deltaF0YCubo;

	//DeltaF0
	deltaf0X = pontoAx * deltaCubo + pontoBx * deltaQuadrado + pontoCx * delta;
	deltaf0Y = pontoAy * deltaCubo + pontoBy * deltaQuadrado + pontoCy * delta;

	//DeltaF0 ao Quadrado
	deltaF0XQuad = 6 * pontoAx * deltaCubo + 2 * pontoBx * deltaQuadrado;
	deltaF0YQuad = 6 * pontoAy * deltaCubo + 2 * pontoBy * deltaQuadrado;

	//DeltaF0 ao Cubo
	deltaF0XCubo = 6 * pontoAx * deltaCubo;
	deltaF0YCubo = 6 * pontoAy * deltaCubo;

	//X e Y Atual
	float xAtual = cordenadas3d[0].x, yAtual = cordenadas3d[0].y;

	//Printar os cordenadas3d
	for (int i = 1; i < 1000; i++) {

		xAtual += deltaf0X;
		yAtual += deltaf0Y;

		deltaf0X += deltaF0XQuad;
		deltaf0Y += deltaF0YQuad;

		deltaF0XQuad += deltaF0XCubo;
		deltaF0YQuad += deltaF0YCubo;

		pol->cordenadas3d.push_back(Cordenadas3D(xAtual, yAtual, 0));

	}

	pol->cordenadas3d.push_back(cordenadas3d[3]);

}
