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

		void desenhaPonto(Ponto ponto, TCanvas*canvas, Janela mundo, Janela vp, int tipoReta, int linha);

		void reflexao(double dx, double dy);
		void transladar(float dx, float dy);
		void escalonar(double dx, double dy);
		void rotacao(double angulo);

		void rotacaoHomogenea(double angulo);
		void multiplicacaoMatriz(double matrizAuxiliar[1][3],
			double matrizUm[1][3], double matrizDois[3][3]);
		Ponto centro();

};

#endif
