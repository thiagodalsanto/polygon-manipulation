// ---------------------------------------------------------------------------
#pragma hdrstop

#define SIGN(x) ((x) < 0 ? (-1): (1))
#define ABS(x) ((x) < 0 ? (-x) : (x))
#define FLOOR(x) ((x) < 0 ? ( (x) - (double)(x) != 0 ? ((double)(x) - 1) : ((int)(x))) : (double)(x))

#include "uPoligono.h"
#include "uJanela.h"
#include <math.h>
// ---------------------------------------------------------------------------
#pragma package(smart_init)

double xVp2W(int x, Janela mundo, Janela vp) {
	return ((x - vp.xmin) / (vp.xmax - vp.xmin)) *
		(mundo.xmax - mundo.xmin) + mundo.xmin;
}

double yVp2W(int y, Janela mundo, Janela vp) {
	return (1 - (y - vp.ymin) / (vp.ymax - vp.ymin)) *
		(mundo.ymax - mundo.ymin) + mundo.ymin;
}

void Poligono::toString(TListBox*local) {
	local->Items->Clear();
	for (int x = 0; x < pontos.size(); x++) {
			local->Items->Add(pontos[x].toString());
		}
}

UnicodeString Poligono::toString() {
	return IntToStr(id) + " - " + tipo + " - " +
		IntToStr((int)pontos.size()) + " Pontos";
}

void Poligono::desenha(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta) {
	int xVp, yVp;

    if(tipo == 'O' || tipo ==  'W'){

		for(int x = 0; x < pontos.size() - 1; x++) {
			canvas->Pixels[pontos[x].xW2Vp(mundo, vp)][pontos[x].yW2Vp(mundo, vp)]
           = (tipo == 'O')? clMaroon : clWhite;
		}

	} else

	switch (tipoReta) {
		case 0:
			lineTo(canvas, mundo, vp, tipoReta);
			break;

		case 1:
			for(float x = 0; x < pontos.size() - 1; x++) {
				DDA(pontos[x], pontos[x+1], canvas, mundo, vp, tipo);
			}
			break;

		case 2:
			for(int x = 0; x < pontos.size() - 1; x++) {
				Bresenham(pontos[x], pontos[x+1], canvas, mundo, vp);
			}
			break;
    }
}


void Poligono::lineTo(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta) {

	int xVp, yVp;

	for (int i = 0; i < pontos.size(); i++) {

        if (i == 0) {
			canvas->MoveTo(pontos[i].xW2Vp(mundo, vp),
						 pontos[i].yW2Vp(mundo, vp));
		}

		else {
			if (tipo == 'R')
				canvas->Pen->Color = clTeal;
			else
				canvas->Pen->Color = clRed;
				canvas->LineTo(pontos[i].xW2Vp(mundo, vp),
							pontos[i].yW2Vp(mundo, vp));
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

	for (int i = 0; i < lenght; i++) {
		if(tipo == 'R') {
			canvas->Pixels[FLOOR(x)][FLOOR(y)] = clTeal;
		} else {
			canvas->Pixels[FLOOR(x)][FLOOR(y)] = clYellow;
        }
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

void Poligono::transladar(float dx, float dy) {
	for (int x = 0; x < pontos.size(); x++) {
		pontos[x].transladar(dx, dy);
	}
}

void Poligono::escalonar(double dx, double dy) {
	for (int x = 0; x < pontos.size(); x++) {
		pontos[x].escalonar(dx, dy);
	}
}

void Poligono::rotacao(double angulo) {
	for (int x = 0; x < pontos.size(); x++) {
		pontos[x].rotacao(angulo);
	}
}

void Poligono::reflexao(double dx, double dy) {
		for (int x = 0; x < pontos.size(); x++) {
			pontos[x].transladar(dx, dy);
		}
}

void Poligono::ComHomo(float dx, float dy,float sx, float sy,double angulo,int tipo){
	float matrix[3][3]={0,0,0,0,0,0,0,0,0};
    float aux[1][3] = {0,0,0};
	float px,py;
	float poli[1][3] = {1,1 , 1};

	switch (tipo){


	case 0:
		matrix[0][0] = 1; matrix[1][1] = 1; matrix[2][2] = 1;
		matrix[2][0]=dx;matrix[2][1]=dy;
		break;

	case 1:
		matrix[0][0] = sx; matrix[1][1] = sy; matrix[2][2] = 1;
		break;

	case 2:
        matrix[0][0] = (cos(angulo));matrix[0][1] = (sin(angulo));
		matrix[1][1] = (cos(angulo));matrix[2][2] = 1;matrix[1][0] = -sin(angulo);
		break;

	case 3:
		matrix[0][0] = 1; matrix[1][1] = -1; matrix[2][2] = 1;
		break;

	case 4:
		matrix[0][0] = -1;matrix[1][1] = 1; matrix[2][2] = 1;
		break;
	case 5:
		matrix[0][0] = -1;matrix[1][1] = -1; matrix[2][2] = 1;
		break;

	}


	for(int x = 0; x < pontos.size(); x++){

		px=pontos[x].x;
		py=pontos[x].y;
		poli[0][0] = px;
		poli[0][1] = py;

		for(int i = 0 ; i < 1 ; i++){
			for(int j = 0; j < 3 ; j++){

				aux[i][j] = 0;

				for(int k = 0; k<3 ; k++){

					aux[i][j] = aux[i][j] + poli[i][k] * matrix[k][j] ;

				}

			}

		}

		 pontos[x].x = aux[0][0];
		 pontos[x].y = aux[0][1];
	}


}

void Poligono::Circunferencia( double xc, double yc, double r, Poligono *aux) {
	double x, y, p;
	x  = 0;
	y = r;

	DesenhaCircunferencia(xc, yc, x, y, aux);
	p = 1 - r;

	while(x < y) {
		if(p < 0) {
			x++;
		}
		else {
			x++;
			y--;
		}
		if(p < 0) {
			p = p + 2 * x + 1;
		}
		else {
			p = p + 2 * (x - y) + 1;
		}
		DesenhaCircunferencia(xc, yc, x, y, aux);
	}
}

void Poligono::DesenhaCircunferencia(double xc, double yc, double x, double y, Poligono *aux) {

	aux->pontos.push_back(Ponto(xc + x, yc + y));
	aux->pontos.push_back(Ponto(xc - x, yc + y));
	aux->pontos.push_back(Ponto(xc - y ,yc + x));
	aux->pontos.push_back(Ponto(xc - y, yc - x));
	aux->pontos.push_back(Ponto(xc - x, yc - y));
	aux->pontos.push_back(Ponto(xc + x, yc - y));
	aux->pontos.push_back(Ponto(xc + y, yc - x));
	aux->pontos.push_back(Ponto(xc + y, yc + x));
}

int Poligono::Cohen(Janela clipping, double x, double y) {
	int cohem = 0;

	cohem |= (x < clipping.xmin) ?  1 : 0 ;

	cohem |= (x > clipping.xmax) ?  2 : 0;

	cohem |= (y < clipping.ymin) ?  4 : 0;

	cohem |= (y > clipping.ymax) ? 8 : 0;

	return cohem;
}

Poligono Poligono::Clip(Janela clipping, Poligono pol)
{
	Poligono aux;
	Ponto p1, p2;
	int code1, code2, code_out; ;
	for (int i = 1; i < pol.pontos.size(); i++) {
			p1 = pol.pontos[i - 1];
			p2 = pol.pontos[i];
			code1 = Cohen(clipping, p1.x, p1.y);
			code2 = Cohen(clipping, p2.x, p2.y);

			bool accept = false;




			while (accept == false) {
				if ((code1 == 0) && (code2 == 0)) {
							accept = true;

				}
				else
				if (code1 & code2) {
					break;
				}
				else {

						int code_out;
						double x, y;

						code_out = (code1 != 0) ? code1 : code2;

						if (code_out & 8) {

								x = p1.x + (p2.x - p1.x) *
								(clipping.ymax - p1.y) /
								(p2.y - p1.y);
								y = clipping.ymax;
							}
						else if (code_out & 4) {
								x = p1.x + (p2.x - p1.x) *
								(clipping.ymin - p1.y) /
								(p2.y - p1.y);
								y = clipping.ymin;
							}
						else if (code_out & 2) {
								y = p1.y + (p2.y - p1.y) *
								(clipping.xmax - p1.x) /
								(p2.x - p1.x);
								x = clipping.xmax;
							}
						else if (code_out & 1) {
								y = p1.y + (p2.y - p1.y) *
								(clipping.xmin - p1.x) /
								(p2.x - p1.x);
								x = clipping.xmin;
							}
						if (code_out == code1) {
								p1.x = x;
								p1.y = y;
								code1 = Cohen(clipping,
								p1.x, p1.y);
							}
						else {
								p2.x = x;
								p2.y = y;
								code2 = Cohen(clipping,
								p2.x, p2.y);
							}
					}
			}

			if(accept){
				aux.pontos.push_back(p1);
				aux.pontos.push_back(p2);
			}


		}
	return aux;

}

void Poligono::casteljau(Poligono *pol) {
	pol->pontos.push_back(this->pontos[0]);

	if (this->pontos.size() == 3) {
		pol->pontosMediosCasteljau(this->pontos[0], this->pontos[1], this->pontos[2]);
    }

	if (this->pontos.size() == 4) {
		pol->pontosMediosCasteljau(this->pontos[0],
			Ponto((this->pontos[1].x +this->pontos[2].x) / 2,
			(this->pontos[1].y + this->pontos[2].y) / 2), this->pontos[3]);
    }
}

void Poligono::pontosMediosCasteljau(Ponto p0, Ponto p1, Ponto p2) {

    //Maior que 5 perde muita curvatura
	if (calcDistEuclidiana(p0.x, p0.y, p1.x, p1.y) < 5) {

		this->pontos.push_back(p2);

	}

	else {

		Ponto pMedio01, pMedio12, pMedio01_12;

		pMedio01 = Ponto( (p0.x + p1.x) / 2, (p0.y + p1.y) / 2 );
		pMedio12 = Ponto( (p1.x + p2.x) / 2, (p1.y + p2.y) / 2 );
		pMedio01_12 = Ponto( (pMedio01.x + pMedio12.x) / 2, (pMedio01.y + pMedio12.y) / 2 );

		this->pontosMediosCasteljau(p0, pMedio01, pMedio01_12); //Lado Esquerdo
		this->pontosMediosCasteljau(pMedio01_12, pMedio12, p2); //Lado Direito

	}
}

double Poligono::calcDistEuclidiana(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)) / 2;
}

void Poligono::hermite(Poligono *pol) {
	double ghX[4], ghY[4];
	int mH[4][4] = {2, -2, 1, 1, -3, 3, -2, -1, 0, 0, 1, 0, 1, 0, 0, 0};

	ghX[0] = pontos[0].x; //P1
	ghX[1] = pontos[3].x; //P4
	ghX[2] = pontos[1].x - pontos[0].x; //R1
	ghX[3] = pontos[3].x - pontos[2].x; //R4

	ghY[0] = pontos[0].y;
	ghY[1] = pontos[3].y;
	ghY[2] = pontos[1].y - pontos[0].y;
	ghY[3] = pontos[3].y - pontos[2].y;

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
	for (float tempo = 0; tempo <= 1; tempo += 0.01) {
		pol->pontos.push_back(Ponto(
			(pow(tempo, 3) * coefHermiteX[0])
			+ (pow(tempo, 2) * coefHermiteX[1])
			+ (tempo * coefHermiteX[2]) + coefHermiteX[3],
			(pow(tempo, 3) * coefHermiteY[0])
			+ (pow(tempo, 2) * coefHermiteY[1])
			+ (tempo * coefHermiteY[2]) + coefHermiteY[3])
		);
	}
}

void Poligono::bezier(Poligono *pol) {
	double gbX[4], gbY[4];
	//Matriz Hermite
	int mH[4][4] = {2, -2, 1, 1, -3, 3, -2, -1, 0, 0, 1, 0, 1, 0, 0, 0};

	gbX[0] = pontos[0].x; //P1
	gbX[1] = pontos[3].x; //P4
	gbX[2] = 3 * (pontos[1].x - pontos[0].x); //R1
	gbX[3] = 3 * (pontos[3].x - pontos[2].x); //R4

	gbY[0] = pontos[0].y;
	gbY[1] = pontos[3].y;
	gbY[2] = 3 * (pontos[1].y - pontos[0].y);
	gbY[3] = 3 * (pontos[3].y - pontos[2].y);

	double coefBezierX[4] =
		{
		gbX[0] * mH[0][0] + gbX[1] * mH[0][1] + gbX[2] * mH[0][2] + gbX[3] * mH[0][3],
		gbX[0] * mH[1][0] + gbX[1] * mH[1][1] + gbX[2] * mH[1][2] + gbX[3] * mH[1][3],
		gbX[0] * mH[2][0] + gbX[1] * mH[2][1] + gbX[2] * mH[2][2] + gbX[3] * mH[2][3],
		gbX[0] * mH[3][0] + gbX[1] * mH[3][1] + gbX[2] * mH[3][2] + gbX[3] * mH[3][3]
		};

	double coefBezierY[4] =
		{
		gbY[0] * mH[0][0] + gbY[1] * mH[0][1] + gbY[2] * mH[0][2] + gbY[3] * mH[0][3],
		gbY[0] * mH[1][0] + gbY[1] * mH[1][1] + gbY[2] * mH[1][2] + gbY[3] * mH[1][3],
		gbY[0] * mH[2][0] + gbY[1] * mH[2][1] + gbY[2] * mH[2][2] + gbY[3] * mH[2][3],
		gbY[0] * mH[3][0] + gbY[1] * mH[3][1] + gbY[2] * mH[3][2] + gbY[3] * mH[3][3]
		};

	//tempo, coefBezierX && tempo, coefBezierY
	for (float tempo = 0; tempo <= 1; tempo += 0.01) {
		pol->pontos.push_back(Ponto(
			(pow(tempo, 3)*coefBezierX[0])
			+ (pow(tempo, 2)*coefBezierX[1])
			+ (tempo*coefBezierX[2]) + coefBezierX[3],
			(pow(tempo, 3)*coefBezierY[0])
			+ (pow(tempo, 2)*coefBezierY[1])
			+ (tempo*coefBezierY[2]) + coefBezierY[3])
			);
	}
}

void Poligono::Bspline(Poligono *pol) {
	double xt, yt;

	//Começar no ponto 3
	for (int i = 3; i < pontos.size(); i++) {

		for (double tempo = 0; tempo <= 1; tempo += 0.01) {

			//calcula x da interpolação
			xt = (pontos[i - 3].x * pow((1 - tempo), 3)) / 6 +
				(pontos[i - 2].x * (3 * pow(tempo, 3) - 6 * pow(tempo, 2) + 4)) / 6 +
				(pontos[i - 1].x * (3 * (-1 * pow(tempo, 3) + pow(tempo, 2) + tempo) + 1))
				/ 6 + (pontos[i].x * pow(tempo, 3)) / 6;

			//calcula y da interpolação
			yt = (pontos[i - 3].y * pow((1 - tempo), 3)) / 6
				+ (pontos[i - 2].y * (3 * pow(tempo, 3) - 6 * pow(tempo, 2) + 4)) / 6
				+ (pontos[i - 1].y * (3 * (-1 * pow(tempo, 3) + pow(tempo, 2) + tempo) + 1))
				/ 6 + (pontos[i].y * pow(tempo, 3)) / 6;

			pol->pontos.push_back(Ponto(xt, yt));

		}
	}
}

void Poligono::forward(Poligono *pol) {
	double xt, yt;
	float pontoAx, pontoAy, pontoBx, pontoBy, pontoCx, pontoCy;

    //calcula pontos a, b, c
	pontoCx = 3 * (pontos[1].x - pontos[0].x);
	pontoCy = 3 * (pontos[1].y - pontos[0].y);

	pontoBx = 3 * (pontos[2].x - pontos[1].x) - pontoCx;
	pontoBy = 3 * (pontos[2].y - pontos[1].y) - pontoCy;

	pontoAx = pontos[3].x - pontos[0].x - pontoCx - pontoBx;
	pontoAy = pontos[3].y - pontos[0].y - pontoCy - pontoBy;

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
	float xAtual = pontos[0].x, yAtual = pontos[0].y;

    //Printar os Pontos
	for (int i = 1; i < 1000; i++) {

		xAtual += deltaf0X;
		yAtual += deltaf0Y;

		deltaf0X += deltaF0XQuad;
		deltaf0Y += deltaF0YQuad;

		deltaF0XQuad += deltaF0XCubo;
		deltaF0YQuad += deltaF0YCubo;

		pol->pontos.push_back(Ponto(xAtual, yAtual));

	}

	pol->pontos.push_back(pontos[3]);

}
