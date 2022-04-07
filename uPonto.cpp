// ---------------------------------------------------------------------------

#pragma hdrstop

#include "uPonto.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

Ponto::Ponto() {
	x = y = 0;
}

Ponto::Ponto(double nx, double ny) {
	x = nx;
	y = ny;
}

UnicodeString Ponto::toString() {
	return "(" + FloatToStr(x) + ", " + FloatToStr(y) + ")";
}

int Ponto::xW2Vp(Janela mundo, Janela vp) {
	return (x - mundo.xmin) / (mundo.xmax - mundo.xmin) * (vp.xmax - vp.xmin);
}

int Ponto::yW2Vp(Janela mundo, Janela vp) {
	return (1 - (y - mundo.ymin) / (mundo.ymax - mundo.ymin)) * (vp.ymax - vp.ymin);
}

void Ponto::transladar(float dx, float dy) {
	x += dx;
	y += dy;
}

void Ponto::escalonar(double dx, double dy) {
	x *= dx;
	y *= dy;
}

void Ponto::rotacao(double angulo) {
	double coseno = cos(angulo * 3.14 / 180);
	double seno = sin(angulo * 3.14 / 180);
	double nx = x * coseno - y * seno;
	double ny = x * seno + y * coseno;
	x = nx;
	y = ny;
}

void Ponto::reflexao(double dx, double dy) {
		if (dx < 0)
			x *= dx;
		if (dy < 0)
			y *= dy;
		if (dx < 0 && dy < 0) {
			x *= dx;
			y *= dy;
		}
}

/*
void __fastcall TForm1::btnRefleteVClick(TObject *Sender)
{
	display.poligonos[lbPoligonos->ItemIndex].escalonar(1, -1);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
*/
