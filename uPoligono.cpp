// ---------------------------------------------------------------------------

#pragma hdrstop

#include "uPoligono.h"
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

	for (unsigned int k = 0; k < pontos.size() - 1; k++) {
		x1 = (pontos[k].x);
		x2 = (pontos[k + 1].x);
		y1 = (pontos[k].y);
		y2 = (pontos[k + 1].y);

		if (ABS((x2 - x1)) >= ABS((y2 - y1)))
			length = ABS((x2 - x1));
		else
			length = ABS((y2 - y1));

		deltax = (float)(x2 - x1) / (float) length;
		deltay = (float)(y2 - y1) / (float) length;

		x = pontos[k].x + 0.5 + SIGN(deltax);
		y = pontos[k].y + 0.5 + SIGN(deltay);

		for (int i = 0; i < length; i++) {
				desenhaPonto(Ponto(FLOOR(x), FLOOR(y)), canvas, mundo,
					vp, 0, linha);
				x += deltax;
				y += deltay;
			}
	}
}

void Poligono::desenhaPonto(Ponto ponto, TCanvas*canvas, Janela mundo,
Janela vp, int tipoReta, int linha) {
	if (tipoReta) {
		if (tipoReta == 'E') {
				canvas->Pen->Color = clBlack;
		}
		else {
				canvas->Pen->Color = clBlue;
				canvas->Pen->Width = 1;
		}

		canvas->Ellipse(Rect(ponto.xW2Vp(mundo, vp) - 1,
			ponto.yW2Vp(mundo, vp) - 1, ponto.xW2Vp(mundo, vp) + 1,
			ponto.yW2Vp(mundo, vp) + 1));
	}

	else {
		canvas->Pen->Width = 1;
		canvas->Pixels[ponto.xW2Vp(mundo, vp)][ponto.yW2Vp(mundo, vp)] =
			clBlue;
	}
}

void Poligono::bresenham(TCanvas*canvas, Janela mundo, Janela vp, int linha) {
	float x, y, y1, y2, x1, x2, deltax, deltay, erro, signalx, signaly, tmp;
	int interchange;

	for (int unsigned k = 0; k < pontos.size() - 1; k++) {
		x1 = (pontos[k].x);
		x2 = (pontos[k + 1].x);
		y1 = (pontos[k].y);
		y2 = (pontos[k + 1].y);

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
				desenhaPonto(Ponto(x, y), canvas, mundo, vp, 2, linha);
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
