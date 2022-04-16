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
		void bresenham(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta);

		void transladar(float dx, float dy);
		void escalonar(double dx, double dy);
		void rotacao(double angulo);
		void reflexao(double dx, double dy);
        void ComHomo(float dx, float dy,float sx, float sy,double angulo,int tipo);

        int Cohen(Janela clipping, double x, double y);
	  	Poligono Clip(Janela clipping, Poligono pol);

		void casteljau(Poligono *pol);
		void pontosCasteljau(Ponto p0, Ponto p1, Ponto p2);
		double calculaDistancia(double x1, double y1, double x2, double y2);
		void hermite(Poligono *pol);
		void bezier(Poligono *pol);
		void Bspline(Poligono *pol);
		void forward(Poligono *pol);
};

#endif
