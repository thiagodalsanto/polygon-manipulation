//---------------------------------------------------------------------------

#ifndef uDDAH
#define uDDAH
//---------------------------------------------------------------------------

class DDA {
public:

	double px0, px1, py0, py1;
	double x, y;

	DDA();

	DDA(double x0, double y0, double x1, double y1);

	void desenhaDDA(TCanvas *canvas);

};
#endif
