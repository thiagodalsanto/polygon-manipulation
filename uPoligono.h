// ---------------------------------------------------------------------------

#ifndef uPoligonoH
#define uPoligonoH

#include <vector>
#include <Vcl.StdCtrls.hpp>
#include "uPonto.h"

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
		void DDA(Ponto P1, Ponto P2, TCanvas *canvas, Janela mundo, Janela vp, char tipo);
		void Bresenham(Ponto P1, Ponto P2, TCanvas *canvas, Janela mundo, Janela vp);

		void Circunferencia(double xc, double yc, double r, Poligono *aux);
	  	void DesenhaCircunferencia(double xc, double yc, double x, double y, Poligono *aux);

		void transladar(float dx, float dy);
		void escalonar(double dx, double dy);
		void rotacao(double angulo);
		void reflexao(double dx, double dy);
        void ComHomo(float dx, float dy,float sx, float sy,double angulo,int tipo);

        int Cohen(Janela clipping, double x, double y);
	  	Poligono Clip(Janela clipping, Poligono pol);

		void casteljau(Poligono *pol);
		void pontosMediosCasteljau(Ponto p0, Ponto p1, Ponto p2);
		double calcDistEuclidiana(double x1, double y1, double x2, double y2);
		void hermite(Poligono *pol);
		void bezier(Poligono *pol);
		void Bspline(Poligono *pol);
		void forward(Poligono *pol);
};

#endif
