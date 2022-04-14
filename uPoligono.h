// ---------------------------------------------------------------------------

#ifndef uPoligonoH
#define uPoligonoH

#include <vector>
#include <Vcl.StdCtrls.hpp>
#include "uPonto.h"
#include "uJanela.h"

#define SIGN(x)   ((x) < 0 ? (-1) : (1))
#define ABS(x)    ((x) < 0 ? (-x) : (x))
#define FLOOR(x)  ((x) < 0 ? ( (x) - (int)(x) != 0 ? ((int)(x) - 1) : ((int)(x))) : (int)(x))
#define FALSE 0
#define TRUE 1

// ---------------------------------------------------------------------------
class Poligono {
	public:
		std::vector<Ponto>pontos;
		int id;
		char tipo;

		void toString(TListBox*local);
		UnicodeString toString();

		void desenha(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta);

		void lineTo(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta);
		void DDA(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta);
		void bresenham(TCanvas*canvas, Janela mundo, Janela vp, int linha);

		void transladar(float dx, float dy);
		void escalonar(double dx, double dy);
		void rotacao(double angulo);
		void reflexao(double dx, double dy);

		void rotacaoHomogenea(double angulo);
		void multiplicacaoMatriz(double matrizAuxiliar[1][3], double matrizUm[1][3], double matrizDois[3][3]);
		Ponto centro();

		void casteljau(Poligono *pol);
		void casteljau3p(Ponto p0, Ponto p1, Ponto p2);
		double calculaDistancia(double x1, double y1, double x2, double y2);
		void hermite(Poligono *pol);
		void bezier(Poligono *pol);
		void Bspline(Poligono *pol);
		void forward(Poligono *pol);
};

#endif
