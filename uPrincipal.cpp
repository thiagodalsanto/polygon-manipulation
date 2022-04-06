// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPrincipal.h"
#include "uPonto.h"
#include "uJanela.h"
#include "uPoligono.h"
#include "uDisplayFile.h"
#include "uDDA.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1*Form1;

Ponto aux;
Janela vp(0, 0, 500, 500);
Janela mundo(-250, -250, 250, 250);
Poligono pol;
DisplayFile display;

bool incluir = false;
int contaId = 0;
// ---------------------------------------------------------------------------

double xVp2W(int x, Janela mundo, Janela vp) {
	return ((x - vp.xmin) / (vp.xmax - vp.xmin)) *
		(mundo.xmax - mundo.xmin) + mundo.xmin;
}

double yVp2W(int y, Janela mundo, Janela vp) {
	return (1 - (y - vp.ymin) / (vp.ymax - vp.ymin)) *
		(mundo.ymax - mundo.ymin) + mundo.ymin;
}

__fastcall TForm1::TForm1(TComponent*Owner)
	:TForm(Owner){
	Image1->Canvas->Brush->Color = clWhite;
	Image1->Canvas->FillRect(Rect(0, 0, 500, 500));

	Image1->Canvas->Pen->Color = clBlack;
	Image1->Canvas->Pen->Width = 1;

	pol.pontos.push_back(Ponto(0, mundo.ymax));
	pol.pontos.push_back(Ponto(0, mundo.ymin));

	pol.id = contaId++;
	pol.tipo = 'E';
	display.poligonos.push_back(pol);
	pol.pontos.clear();

	pol.pontos.push_back(Ponto(mundo.xmin, 0));
	pol.pontos.push_back(Ponto(mundo.xmax, 0));

	pol.id = contaId++;
	pol.tipo = 'E';
	display.poligonos.push_back(pol);
	pol.pontos.clear();
	pol.tipo = 'N';

	display.toString(lbPoligonos);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::btnCreatePolygonClick(TObject*Sender){
	incluir = true;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
   double nx, ny;

   nx = xVp2W(X, mundo, vp);
   ny = yVp2W(Y, mundo, vp);

   lbVp->Caption = "(" + IntToStr(X) + "," +
						 IntToStr(Y) + ")";
   lbMundo->Caption = "(" + FloatToStr(nx) + "," +
							FloatToStr(ny) + ")";

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(TObject*Sender, TMouseButton Button,
	TShiftState Shift,
	int X, int Y){

	if (Button == mbLeft) {
			if (incluir) {
					double xw, yw;
					xw = xVp2W(X, mundo, vp);
					yw = yVp2W(Y, mundo, vp);
					aux = Ponto(xw, yw);
					pol.pontos.push_back(aux);
					pol.toString(lbPontos);
					pol.desenha(Image1->Canvas, mundo, vp,
						rgTipoReta->ItemIndex);
				}
			else
				ShowMessage(
				"Clique no botao para incluir pontos e um poligono.");
		}
	else
		if (Button == mbRight) {
			incluir = false;
			if (pol.pontos.size() > 0) {
					pol.id = contaId++;
					pol.tipo = 'N';
					display.poligonos.push_back(pol);
					display.toString(lbPoligonos);
					pol.pontos.clear();
				}
		}
}
// ---------------------------------------------------------------------------


void __fastcall TForm1::lbPoligonosMouseDown(TObject*Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y){
	display.poligonos[lbPoligonos->ItemIndex].toString(lbPontos);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btnUpdateClick(TObject*Sender){
	mundo.xmin = StrToFloat(edXWMin->Text);
	mundo.ymin = StrToFloat(edYWMin->Text);
	mundo.xmax = StrToFloat(edXWMax->Text);
	mundo.ymax = StrToFloat(edYWMax->Text);

	AtualizaMundo();
}
// ---------------------------------------------------------------------------

void TForm1::AtualizaMundo() {
	edXWMin->Text = FloatToStr(mundo.ymin);
	edXWMax->Text = FloatToStr(mundo.ymax);

	edYWMin->Text = FloatToStr(mundo.ymin);
	edYWMax->Text = FloatToStr(mundo.ymax);

	display.poligonos[0].pontos[0].y = mundo.ymax;
	display.poligonos[0].pontos[1].y = mundo.ymin;

	display.poligonos[1].pontos[0].x = mundo.xmin;
	display.poligonos[1].pontos[1].x = mundo.xmax;

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::btnUpClick(TObject*Sender){
	mundo.ymin += 10;
	mundo.ymax += 10;
	AtualizaMundo();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::btnDownClick(TObject*Sender){
	mundo.ymin -= 10;
	mundo.ymax -= 10;
	AtualizaMundo();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::btnLeftClick(TObject*Sender){
	mundo.xmin -= 10;
	mundo.xmax -= 10;
	AtualizaMundo();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btnRigthClick(TObject*Sender){
	mundo.xmin += 10;
	mundo.xmax += 10;
	AtualizaMundo();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::btnZoomMaisClick(TObject*Sender){
	mundo.xmin += 10;
	mundo.xmax -= 10;
	mundo.ymin += 10;
	mundo.ymax -= 10;
	AtualizaMundo();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::btnZoomMenosClick(TObject*Sender){
	mundo.xmin -= 10;
	mundo.xmax += 10;
	mundo.ymin -= 10;
	mundo.ymax += 10;
	AtualizaMundo();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::rgTipoRetaClick(TObject*Sender){
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btRotacionarClick(TObject*Sender){
	display.poligonos[lbPoligonos->ItemIndex].rotacao
		((double)(StrToFloat(edtAngulo->Text)));
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
// ---------------------------------------------------------------------------
void __fastcall TForm1::btTransladarClick(TObject *Sender){
	float dx, dy;

	dx = StrToFloat(edTransladarX->Text);
	dy = StrToFloat(edTransladarY->Text);
	display.poligonos[lbPoligonos->ItemIndex].transladar(dx, dy);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btEscalonarClick(TObject *Sender){
	double dx, dy;

	dx = StrToFloat(edEscalonarX->Text);
	dy = StrToFloat(edEscalonarY->Text);
	display.poligonos[lbPoligonos->ItemIndex].escalonar(dx, dy);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
//---------------------------------------------------------------------------



