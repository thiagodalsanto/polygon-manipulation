// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPrincipal.h"
#include "uJanela.h"
#include "uPonto.h"
#include "uDisplayFile.h"
#include <vector>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TedtHomogenea*edtHomogenea;

Poligono pol, clip1, clip2;
DisplayFile display;

int ToInt;
Ponto aux;
Janela vp(0, 0, 500, 500);
Janela mundo(-250, -250, 250, 250);
Janela clipping(-100, -100, 100, 100);

int contaId = 0;
bool incluir = false;
#include "uPoligono.h"
// ---------------------------------------------------------------------------

double xVp2W(int x, Janela mundo, Janela vp) {
	return ((x - vp.xmin) / (vp.xmax - vp.xmin)) *
		(mundo.xmax - mundo.xmin) + mundo.xmin;
}

double yVp2W(int y, Janela mundo, Janela vp) {
	return (1 - (y - vp.ymin) / (vp.ymax - vp.ymin)) *
		(mundo.ymax - mundo.ymin) + mundo.ymin;
}

__fastcall TedtHomogenea::TedtHomogenea(TComponent*Owner)
	:TForm(Owner){

	// Eixo Vertical
	pol.id = contaId++;
	pol.tipo = 'E';
	pol.pontos.push_back(Ponto(0, mundo.ymax));
	pol.pontos.push_back(Ponto(0, mundo.ymin));

	display.poligonos.push_back(pol);
	pol.pontos.clear();

	// Eixo Horizontal
	pol.id = contaId++;
	pol.tipo = 'E';
	pol.pontos.push_back(Ponto(mundo.xmin, 0));
	pol.pontos.push_back(Ponto(mundo.xmax, 0));

	display.poligonos.push_back(pol);
	pol.pontos.clear();

    // Clipping
	pol.pontos.push_back(Ponto(clipping.xmin, clipping.ymin));
	pol.pontos.push_back(Ponto(clipping.xmin, clipping.ymax));
	pol.pontos.push_back(Ponto(clipping.xmax, clipping.ymax));
	pol.pontos.push_back(Ponto(clipping.xmax, clipping.ymin));
	pol.pontos.push_back(Ponto(clipping.xmin, clipping.ymin));
	pol.id = contaId++;
	pol.tipo = 'C';
	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.toString(lbPoligonos);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}

// ---------------------------------------------------------------------------
void __fastcall TedtHomogenea::btnCreatePolygonClick(TObject*Sender){

	Circulo->Enabled = true;
	btnCreatePolygon->Enabled = false;

}

// ---------------------------------------------------------------------------
void __fastcall TedtHomogenea::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
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

void __fastcall TedtHomogenea::Image1MouseDown(TObject*Sender, TMouseButton Button,
	TShiftState Shift,
	int X, int Y){

	if(!btnCreatePolygon->Enabled){

		if((rgTipoReta->ItemIndex) >= 0) {

			if (Button == mbLeft) {

				UnicodeString a;

				aux.x = xVp2W(X, mundo, vp);
				aux.y = yVp2W(Y, mundo, vp);


				pol.pontos.push_back(aux);
				pol.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);

			} else {

				if (Button == mbRight) {
					pol.id = contaId++;
					pol.tipo = 'P';

					display.poligonos.push_back(pol);
					pol.pontos.clear();

					display.toString(lbPoligonos);

				}
			}
		}
	} else {

		pol.id = contaId++;
		pol.tipo = 'O';

		pol.Circunferencia(xVp2W(X, mundo, vp), yVp2W(Y, mundo, vp),
								StrToFloat(edRaio->Text), &pol);
		display.poligonos.push_back(pol);
		pol.pontos.clear();

		display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
		display.toString(lbPoligonos);
		pol.tipo = 'E';

	}

}
// ---------------------------------------------------------------------------


void __fastcall TedtHomogenea::lbPoligonosMouseDown(TObject*Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y){
	display.poligonos[lbPoligonos->ItemIndex].toString(lbPontos);
}
// ---------------------------------------------------------------------------

void __fastcall TedtHomogenea::btnUpdateClick(TObject*Sender){
	mundo.xmin = StrToFloat(edXWMin->Text);
	mundo.ymin = StrToFloat(edYWMin->Text);
	mundo.xmax = StrToFloat(edXWMax->Text);
	mundo.ymax = StrToFloat(edYWMax->Text);

	AtualizaMundo();
}
// ---------------------------------------------------------------------------

void TedtHomogenea::AtualizaMundo() {
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
void __fastcall TedtHomogenea::btnUpClick(TObject*Sender){
	mundo.ymin += 10;
	mundo.ymax += 10;
	AtualizaMundo();
}

// ---------------------------------------------------------------------------
void __fastcall TedtHomogenea::btnDownClick(TObject*Sender){
	mundo.ymin -= 10;
	mundo.ymax -= 10;
	AtualizaMundo();
}

// ---------------------------------------------------------------------------
void __fastcall TedtHomogenea::btnLeftClick(TObject*Sender){
	mundo.xmin -= 10;
	mundo.xmax -= 10;
	AtualizaMundo();
}
// ---------------------------------------------------------------------------

void __fastcall TedtHomogenea::btnRigthClick(TObject*Sender){
	mundo.xmin += 10;
	mundo.xmax += 10;
	AtualizaMundo();
}

// ---------------------------------------------------------------------------
void __fastcall TedtHomogenea::btnZoomMaisClick(TObject*Sender){
	mundo.xmin += 10;
	mundo.xmax -= 10;
	mundo.ymin += 10;
	mundo.ymax -= 10;
	AtualizaMundo();
}

// ---------------------------------------------------------------------------
void __fastcall TedtHomogenea::btnZoomMenosClick(TObject*Sender){
	mundo.xmin -= 10;
	mundo.xmax += 10;
	mundo.ymin -= 10;
	mundo.ymax += 10;
	AtualizaMundo();
}

// ---------------------------------------------------------------------------
void __fastcall TedtHomogenea::rgTipoRetaClick(TObject*Sender){
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
// ---------------------------------------------------------------------------

void __fastcall TedtHomogenea::btRotacionarClick(TObject*Sender){
	display.poligonos[lbPoligonos->ItemIndex].rotacao
		((double)(StrToFloat(edtAngulo->Text)));
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
// ---------------------------------------------------------------------------
void __fastcall TedtHomogenea::btTransladarClick(TObject *Sender){
	float dx, dy;

	dx = StrToFloat(edTransladarX->Text);
	dy = StrToFloat(edTransladarY->Text);
	display.poligonos[lbPoligonos->ItemIndex].transladar(dx, dy);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TedtHomogenea::btEscalonarClick(TObject *Sender){
	double dx, dy;

	dx = StrToFloat(edEscalonarX->Text);
	dy = StrToFloat(edEscalonarY->Text);
	display.poligonos[lbPoligonos->ItemIndex].escalonar(dx, dy);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TedtHomogenea::btnRefleteHClick(TObject *Sender)
{
	display.poligonos[lbPoligonos->ItemIndex].escalonar(-1, 1);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TedtHomogenea::btnRefleteVClick(TObject *Sender)
{
   	display.poligonos[lbPoligonos->ItemIndex].escalonar(1, -1);
	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TedtHomogenea::btnCriarCurvasClick(TObject *Sender)
{
	if (lbPoligonos->ItemIndex > 2)
		switch (rgCurvas->ItemIndex) {
		case 0:
			display.poligonos[lbPoligonos->ItemIndex].casteljau(&pol);
			pol.id = contaId++;
			pol.tipo = 'P';

			display.poligonos.push_back(pol);
			pol.pontos.clear();
			display.toString(lbPoligonos);
			display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
			break;

		case 1:
			display.poligonos[lbPoligonos->ItemIndex].bezier(&pol);
			pol.id = contaId++;
			pol.tipo = 'P';

			display.poligonos.push_back(pol);
			pol.pontos.clear();
			display.toString(lbPoligonos);
			display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
			break;

		case 2:
			display.poligonos[lbPoligonos->ItemIndex].hermite(&pol);
			pol.id = contaId++;
			pol.tipo = 'P';

			display.poligonos.push_back(pol);
			pol.pontos.clear();
			display.toString(lbPoligonos);
			display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
			break;

		case 3:
			display.poligonos[lbPoligonos->ItemIndex].Bspline(&pol);
			pol.id = contaId++;
			pol.tipo = 'P';

			display.poligonos.push_back(pol);
			pol.pontos.clear();
			display.toString(lbPoligonos);
			display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
			break;

		case 4:
			display.poligonos[lbPoligonos->ItemIndex].forward(&pol);
			pol.id = contaId++;
			pol.tipo = 'P';

			display.poligonos.push_back(pol);
			pol.pontos.clear();
			display.toString(lbPoligonos);
			display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
			break;
		}
}
//---------------------------------------------------------------------------

void __fastcall TedtHomogenea::btnTransladarHomoClick(TObject *Sender)
{
	float dx, dy;
	if(display.poligonos[lbPoligonos->ItemIndex].tipo != 'E'){

		dx = StrToFloat(edTransladarX->Text);
		dy = StrToFloat(edTransladarY->Text);
		display.poligonos[lbPoligonos->ItemIndex].ComHomo(dx, dy, 0,0,0,0);
		display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
    }
}
//---------------------------------------------------------------------------

void __fastcall TedtHomogenea::btnEscalonarHomoClick(TObject *Sender)
{
	float sx, sy;
	sx = StrToFloat(edEscalonarX->Text);
	sy = StrToFloat(edEscalonarY->Text);

	if((sx != 0 || sy != 0 )&& display.poligonos[lbPoligonos->ItemIndex].tipo != 'E'){

		display.poligonos[lbPoligonos->ItemIndex].ComHomo(0, 0, sx,sy,0,1);
		display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}
}
//---------------------------------------------------------------------------


void __fastcall TedtHomogenea::btnRotacionarHomoClick(TObject *Sender)
{
	float angulo, mediox = 0, medioy = 0;
	int tam;
	angulo = StrToFloat(edtAngulo->Text);
	tam =  display.poligonos[lbPoligonos->ItemIndex].pontos.size();

	if(tam != NULL && display.poligonos[lbPoligonos->ItemIndex].tipo != 'E'){

		for(int cont = 0; cont <= tam; cont++){
			mediox += display.poligonos[lbPoligonos->ItemIndex].pontos[cont].x;
			medioy += display.poligonos[lbPoligonos->ItemIndex].pontos[cont].y;
		}

		mediox = mediox / tam;
		medioy = medioy / tam;

		if(angulo != 0){

			angulo = (angulo * 3.14) / 180;

			display.poligonos[lbPoligonos->ItemIndex].ComHomo(- mediox, - medioy, 0,0,0,0);
			display.poligonos[lbPoligonos->ItemIndex].ComHomo(0, 0, 0,0,angulo,2);
			display.poligonos[lbPoligonos->ItemIndex].ComHomo(mediox, medioy, 0,0,0,0);

			display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);

		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TedtHomogenea::btnClippingClick(TObject *Sender)
{
    if (lbPoligonos->ItemIndex > 1) {
		clip1 = display.poligonos[lbPoligonos->ItemIndex];
		clip2 = display.poligonos[lbPoligonos->ItemIndex].Clip(clipping, clip1);

		if (clip2.pontos.size() > 0) {
				clip2.id = contaId++;
				clip2.tipo = (display.poligonos[lbPoligonos->ItemIndex].tipo == 'O')?
						 'r' : 'R';
				display.poligonos.push_back(clip2);
				display.toString(lbPoligonos);
				clip2.pontos.clear();

				display.desenha(Image1->Canvas, mundo, vp,rgTipoReta->ItemIndex);
				clip2.toString(lbPontos);
			}

	}
}
//---------------------------------------------------------------------------

void __fastcall TedtHomogenea::CirculoClick(TObject *Sender)
{

	btnCreatePolygon->Enabled = true;
	Circulo->Enabled = false ;

}
//---------------------------------------------------------------------------

