//---------------------------------------------------------------------------

#ifndef uDisplayFileH
#define uDisplayFileH
#include <vector>
#include "uPoligono.h"
#include <Vcl.ExtCtrls.hpp>
#include "ujanela.h"
#include "Cordenadas3D.h"
//---------------------------------------------------------------------------
class DisplayFile{
	public:
		std::vector <Poligono> poligonos;

		void desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta);

		void mostra(TListBox *lb);
};
#endif
