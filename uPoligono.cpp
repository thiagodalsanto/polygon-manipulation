// ---------------------------------------------------------------------------
#pragma hdrstop

#include "uPoligono.h"
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

	switch (tipoReta) {
		case 0:
			lineTo(canvas, mundo, vp, tipoReta);
			break;
		case 1:
			DDA(canvas, mundo, vp, tipoReta);
			break;
		case 2:
			bresenham(canvas, mundo, vp, tipoReta);
			break;
		}
}

void Poligono::lineTo(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta) {
	int xVp, yVp;
	for (int i = 0; i < pontos.size(); i++) {
		xVp = pontos[i].xW2Vp(mundo, vp);
		yVp = pontos[i].yW2Vp(mundo, vp);

		if (tipoReta == 'E') {
				canvas->Pen->Color = clBlack;
		}

		else {
				canvas->Pen->Color = clBlue;
				canvas->Pen->Width = 1;
		}

		if (i == 0) {
				canvas->MoveTo(xVp, yVp);
		}

		else {
				canvas->LineTo(xVp, yVp);
		}
	}
}

void Poligono::DDA(TCanvas*canvas, Janela mundo, Janela vp, int linha) {
	double length, deltax, deltay, x, y, k, x1, x2, y1, y2;

	for (int k = 0; k < pontos.size() - 1; k++) {
		x1 = (pontos[k].xW2Vp(mundo, vp));
		x2 = (pontos[k + 1].xW2Vp(mundo, vp));
		y1 = (pontos[k].yW2Vp(mundo, vp));
		y2 = (pontos[k + 1].yW2Vp(mundo, vp));

		if (ABS((x2 - x1)) >= ABS((y2 - y1)))
			length = ABS((x2 - x1));
		else
			length = ABS((y2 - y1));

		deltax = (float)(x2 - x1) / (float) length;
		deltay = (float)(y2 - y1) / (float) length;

		x = x1 + 0.5 + SIGN(deltax);
		y = y1 + 0.5 + SIGN(deltay);
		canvas->Pixels[FLOOR(x)][FLOOR(y)] = clBlack;
		for (int i = 0; i < length; i++) {
			canvas->Pixels[FLOOR(x)][FLOOR(y)] = clBlack;
			x += deltax;
			y += deltay;
		}
	}
}

void Poligono::bresenham(TCanvas*canvas, Janela mundo, Janela vp, int linha) {
	float x, y, y1, y2, x1, x2, deltax, deltay, erro, signalx, signaly, tmp;
	int interchange;

	for (int k = 0; k < pontos.size() - 1; k++) {
		x1 = (pontos[k].xW2Vp(mundo, vp));
		x2 = (pontos[k + 1].xW2Vp(mundo, vp));
		y1 = (pontos[k].yW2Vp(mundo, vp));
		y2 = (pontos[k + 1].yW2Vp(mundo, vp));

		x = (int) x1;
		y = (int) y1;

		deltax = ABS((x2 - x1));
		deltay = ABS((y2 - y1));
		signalx = SIGN((x2 - x1));
		signaly = SIGN((y2 - y1));

		if (signalx < 0)
			x -= 1;
		if (signaly < 0)
			y -= 1;

		interchange = FALSE;

		if (deltay > deltax) {
			tmp = deltax;
			deltax = deltay;
			deltay = tmp;
			interchange = TRUE;
		}

		erro = 2 * deltay - deltax;

		for (int i = 0; i < deltax; i++) {
			canvas->Pixels[FLOOR(x)][FLOOR(y)] = clBlack;
			while (erro >= 0.0) {
				if (interchange)
					x += signalx;
				else
					y += signaly;
				erro = erro - 2 * deltax;
			}
			if (interchange)
				y += signaly;
			else
				x += signalx;
			erro = erro + 2 * deltay;
		}
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

void Poligono::rotacaoHomogenea(double angulo) {
		double radiano = angulo * M_PI / 180;
		double deslocamentoX, deslocamentoY;
		double xAnterior;
		double matrizRotacao[3][3] =
			{
					{cos(radiano), sin(radiano), 0},
					{-sin(radiano), cos(radiano), 0},
					{0, 0, 1}
			};

		Ponto centroPoligono = centro();
		deslocamentoX = centroPoligono.x;
		deslocamentoY = centroPoligono.y;

		double matrizTranslacao[3][3] =
			{
					{1, 0, 0},
					{0, 1, 0},
					{deslocamentoX, deslocamentoY, 1}
			};

		double matrizTranslacaoNegativa[3][3] =
			{
					{1, 0, 0},
					{0, 1, 0},
					{-deslocamentoX, -deslocamentoY, 1}
			};

		double matrizXY[1][3] = {0, 0, 1};
		double matrizAuxiliar[1][3] = {0, 0, 1};

		multiplicacaoMatriz(matrizAuxiliar, matrizXY, matrizTranslacaoNegativa);
		multiplicacaoMatriz(matrizAuxiliar, matrizXY, matrizRotacao);
		multiplicacaoMatriz(matrizAuxiliar, matrizXY, matrizTranslacao);
	}

void Poligono::multiplicacaoMatriz(double matrizAuxiliar[1][3],
	double matrizUm[1][3], double matrizDois[3][3]) {

		for (int i = 0; i < pontos.size(); i++) {
				matrizUm[0][0] = pontos[i].x;
				matrizUm[0][1] = pontos[i].y;

				for (int l = 0; l < 1; l++) {
						for (int c = 0; c < 3; c++) {
								matrizAuxiliar[l][c] = 0;
								for (int w = 0; w < 3; w++) {
										matrizAuxiliar[l][c] =
										matrizAuxiliar[l][c] + matrizUm[l][w]
										* matrizDois[w][c];
								}
						}
				}
				pontos[i].x = matrizAuxiliar[0][0];
				pontos[i].y = matrizAuxiliar[0][1];
		}
}

Ponto Poligono::centro() {
		double somaX = 0;
		double somaY = 0;

		for (int i = 0; i < pontos.size(); i++) {
				somaX += pontos[i].x;
				somaY += pontos[i].y;
			}

		somaX = somaX / pontos.size();
		somaY = somaY / pontos.size();

		return Ponto(somaX, somaY);
}

void Poligono::casteljau(Poligono *pol) {
	pol->pontos.push_back(this->pontos[0]);
	if (this->pontos.size() == 3)
		pol->casteljau3p(this->pontos[0], this->pontos[1], this->pontos[2]);
	else if (this->pontos.size() == 4)
		pol->casteljau3p(this->pontos[0],
		Ponto((this->pontos[1].x +this->pontos[2].x) / 2,
		(this->pontos[1].y +this->pontos[2].y) / 2), this->pontos[3]);
}

void Poligono::casteljau3p(Ponto p0, Ponto p1, Ponto p2) {
	if (calculaDistancia(p0.x, p0.y, p1.x, p1.y) < 0.1) {
		this->pontos.push_back(p1);
		this->pontos.push_back(p2);
	}
	else {
		Ponto p01, p012, p12;
		p01 = Ponto((p0.x + p1.x) / 2, (p0.y + p1.y) / 2);
		p12 = Ponto((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
		p012 = Ponto((p01.x + p12.x) / 2, (p01.y + p12.y) / 2);
		this->casteljau3p(p0, p01, p012);
		this->casteljau3p(p012, p12, p2);
	}
}

double Poligono::calculaDistancia(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)) / 2;
}

void Poligono::hermite(Poligono *pol) {
	double Gx[4], Gy[4];
	int M[4][4] = {2, -2, 1, 1, -3, 3, -2, -1, 0, 0, 1, 0, 1, 0, 0, 0};

	Gx[0] = pontos[0].x;
	Gx[1] = pontos[3].x;
	Gx[2] = pontos[1].x - pontos[0].x;
	Gx[3] = pontos[3].x - pontos[2].x;

	Gy[0] = pontos[0].y;
	Gy[1] = pontos[3].y;
	Gy[2] = pontos[1].y - pontos[0].y;
	Gy[3] = pontos[3].y - pontos[2].y;

	double Cx[4] = {
		Gx[0] * M[0][0] + Gx[1] * M[0][1] + Gx[2] * M[0][2] + Gx[3] * M[0][3],
		Gx[0] * M[1][0] + Gx[1] * M[1][1] + Gx[2] * M[1][2] + Gx[3] * M[1][3],
		Gx[0] * M[2][0] + Gx[1] * M[2][1] + Gx[2] * M[2][2] + Gx[3] * M[2][3],
		Gx[0] * M[3][0] + Gx[1] * M[3][1] + Gx[2] * M[3][2] + Gx[3] * M[3][3]};

	double Cy[4] = {
		Gy[0] * M[0][0] + Gy[1] * M[0][1] + Gy[2] * M[0][2] + Gy[3] * M[0][3],
		Gy[0] * M[1][0] + Gy[1] * M[1][1] + Gy[2] * M[1][2] + Gy[3] * M[1][3],
		Gy[0] * M[2][0] + Gy[1] * M[2][1] + Gy[2] * M[2][2] + Gy[3] * M[2][3],
		Gy[0] * M[3][0] + Gy[1] * M[3][1] + Gy[2] * M[3][2] + Gy[3] * M[3][3]};

	for (float t = 0; t <= 1; t += 0.001) {
		pol->pontos.push_back(Ponto((pow(t, 3)*Cx[0]) + (pow(t, 2)*Cx[1]) +
			(t*Cx[2]) + Cx[3], (pow(t, 3)*Cy[0]) + (pow(t, 2)*Cy[1]) +
			(t*Cy[2]) + Cy[3]));
	}
}

void Poligono::bezier(Poligono *pol) {
	double Gx[4], Gy[4];
	int M[4][4] = {2, -2, 1, 1, -3, 3, -2, -1, 0, 0, 1, 0, 1, 0, 0, 0};

	Gx[0] = pontos[0].x;
	Gx[1] = pontos[3].x;
	Gx[2] = 3 * (pontos[1].x - pontos[0].x);
	Gx[3] = 3 * (pontos[3].x - pontos[2].x);

	Gy[0] = pontos[0].y;
	Gy[1] = pontos[3].y;
	Gy[2] = 3 * (pontos[1].y - pontos[0].y);
	Gy[3] = 3 * (pontos[3].y - pontos[2].y);

	double Cx[4] = {
		Gx[0] * M[0][0] + Gx[1] * M[0][1] + Gx[2] * M[0][2] + Gx[3] * M[0][3],
		Gx[0] * M[1][0] + Gx[1] * M[1][1] + Gx[2] * M[1][2] + Gx[3] * M[1][3],
		Gx[0] * M[2][0] + Gx[1] * M[2][1] + Gx[2] * M[2][2] + Gx[3] * M[2][3],
		Gx[0] * M[3][0] + Gx[1] * M[3][1] + Gx[2] * M[3][2] + Gx[3] * M[3][3]};

	double Cy[4] = {
		Gy[0] * M[0][0] + Gy[1] * M[0][1] + Gy[2] * M[0][2] + Gy[3] * M[0][3],
		Gy[0] * M[1][0] + Gy[1] * M[1][1] + Gy[2] * M[1][2] + Gy[3] * M[1][3],
		Gy[0] * M[2][0] + Gy[1] * M[2][1] + Gy[2] * M[2][2] + Gy[3] * M[2][3],
		Gy[0] * M[3][0] + Gy[1] * M[3][1] + Gy[2] * M[3][2] + Gy[3] * M[3][3]};

	for (float t = 0; t <= 1; t += 0.001) {
		pol->pontos.push_back(Ponto((pow(t, 3)*Cx[0]) + (pow(t, 2)*Cx[1]) +
			(t*Cx[2]) + Cx[3], (pow(t, 3)*Cy[0]) + (pow(t, 2)*Cy[1]) +
			(t*Cy[2]) + Cy[3]));
	}
}

void Poligono::Bspline(Poligono *pol) {
	double xt, yt;
	for (int i = 3; i < pontos.size(); i++)
		for (double t = 0; t <= 1; t += 0.01) {
			xt = (pontos[i - 3].x * pow((1 - t), 3)) / 6 +
				(pontos[i - 2].x * (3 * pow(t, 3) - 6 * pow(t, 2) + 4)) / 6 +
				(pontos[i - 1].x * (3 * (-1 * pow(t, 3) + pow(t, 2) + t) + 1))
				/ 6 + (pontos[i].x * pow(t, 3)) / 6;
			yt = (pontos[i - 3].y * pow((1 - t), 3)) / 6 +
				(pontos[i - 2].y * (3 * pow(t, 3) - 6 * pow(t, 2) + 4)) / 6 +
				(pontos[i - 1].y * (3 * (-1 * pow(t, 3) + pow(t, 2) + t) + 1))
				/ 6 + (pontos[i].y * pow(t, 3)) / 6;
			pol->pontos.push_back(Ponto(xt, yt));
		}
}

void Poligono::forward(Poligono *pol) {
	double xt, yt;
	float ax, ay, bx, by, cx, cy;

	cx = 3 * (pontos[1].x - pontos[0].x);
	cy = 3 * (pontos[1].y - pontos[0].y);

	bx = 3 * (pontos[2].x - pontos[1].x) - cx;
	by = 3 * (pontos[2].y - pontos[1].y) - cy;

	ax = pontos[3].x - pontos[0].x - cx - bx;
	ay = pontos[3].y - pontos[0].y - cy - by;

	float h = 1.0f / 1000, hh = h * h, hhh = hh * h;
	float d1x, d1y, d2x, d2y, d3x, d3y;

	d1x = ax * hhh + bx * hh + cx * h;
	d1y = ay * hhh + by * hh + cy * h;

	d2x = 6 * ax * hhh + 2 * bx * hh;
	d2y = 6 * ay * hhh + 2 * by * hh;

	d3x = 6 * ax * hhh;
	d3y = 6 * ay * hhh;

	float currentX = pontos[0].x, currentY = pontos[0].y;

	for (int i = 1; i < 1000; i++) {
		currentX += d1x;
		currentY += d1y;

		d1x += d2x;
		d1y += d2y;
		d2x += d3x;
		d2y += d3y;

		pol->pontos.push_back(Ponto(currentX, currentY));
	}

	pol->pontos.push_back(pontos[3]);
}
