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
		Poligono circunferencia(double xc, double yc, int radio);

		void lineTo(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta);
		void DDA(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta);
		void bresenham(TCanvas*canvas, Janela mundo, Janela vp, int linha);

		void desenhaCirculo(TCanvas*canvas, Janela mundo, Janela vp, int linha);
		void desenhaPonto(Ponto ponto, TCanvas*canvas, Janela mundo, Janela vp, int tipoReta, int linha);

        void escalonar(float sx, float sy);
        void transladar(float dx, float dy);
		void rotacao2D(double angulo);
};

#endif
