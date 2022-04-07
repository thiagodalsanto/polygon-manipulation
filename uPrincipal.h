//---------------------------------------------------------------------------

#ifndef uPrincipalH
#define uPrincipalH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *btnCreatePolygon;
	TPanel *Panel1;
	TImage *Image1;
	TLabel *lbVp;
	TLabel *lbMundo;
	TListBox *lbPontos;
	TListBox *lbPoligonos;
	TEdit *edXWMin;
	TEdit *edYWMin;
	TEdit *edXWMax;
	TEdit *edYWMax;
	TLabel *Label3;
	TButton *btnUpdate;
	TButton *btnUp;
	TButton *btnLeft;
	TButton *btnRigth;
	TButton *btnDown;
	TButton *btnZoomMais;
	TButton *btnZoomMenos;
	TRadioGroup *rgTipoReta;
	TButton *btRotacionar;
	TEdit *edtAngulo;
	TEdit *edTransladarX;
	TEdit *edTransladarY;
	TButton *btTransladar;
	TButton *btEscalonar;
	TEdit *edEscalonarY;
	TEdit *edEscalonarX;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label5;
	TLabel *Label4;
	TGroupBox *GroupBox4;
	TGroupBox *GroupBox5;
	TLabel *Pontos;
	TLabel *Poligonos;
	TButton *btnRefleteV;
	TButton *btnRefleteH;
	TGroupBox *GroupBox6;
	void __fastcall btnCreatePolygonClick(TObject *Sender);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall lbPoligonosMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnUpdateClick(TObject *Sender);
	void __fastcall btnUpClick(TObject *Sender);
	void __fastcall btnZoomMaisClick(TObject *Sender);
	void __fastcall btnZoomMenosClick(TObject *Sender);
	void __fastcall btnDownClick(TObject *Sender);
	void __fastcall btnLeftClick(TObject *Sender);
	void __fastcall btnRigthClick(TObject *Sender);
	void __fastcall rgTipoRetaClick(TObject *Sender);
	void __fastcall btRotacionarClick(TObject *Sender);
	void __fastcall btTransladarClick(TObject *Sender);
	void __fastcall btEscalonarClick(TObject *Sender);
	void __fastcall btnRefleteHClick(TObject *Sender);
	void __fastcall btnRefleteVClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    void AtualizaMundo();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
