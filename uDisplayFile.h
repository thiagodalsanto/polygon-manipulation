//---------------------------------------------------------------------------

#ifndef uDisplayFileH
#define uDisplayFileH

#include <vector>
#include "uPoligono.h"
#include "uJanela.h"
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
class DisplayFile{
	public:
	std::vector<Poligono> poligonos;

	void toString(TListBox *local);
	void desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta);
};

#endif
