// ---------------------------------------------------------------------------

#ifndef uPontoH
#define uPontoH
#include <Vcl.StdCtrls.hpp>
#include "uJanela.h"
// ---------------------------------------------------------------------------

class Ponto {
	public:
		double x;
		double y;

		Ponto();
		Ponto(double, double);

		UnicodeString toString();
		int xW2Vp(Janela mundo, Janela vp);
		int yW2Vp(Janela mundo, Janela vp);

        void escalonar(double dx, double dy);
        void transladar(float dx, float dy);
		void rotacao(double angulo);
	};

#endif
