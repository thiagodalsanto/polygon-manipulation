//---------------------------------------------------------------------------

#pragma hdrstop

#include "uDDA.h"
#include <Vcl.ExtCtrls.hpp>
#include <math.h>

#define _ABS_(x) ((x < 0) ? -x : x)
#define _SIGN_(x) ((x < 0) ? -1 : 1)
//---------------------------------------------------------------------------
#pragma package(smart_init)

DDA::DDA() {
		px0 = px1 = py0 = py1 = 0;
	}

DDA::DDA(double x0, double y0, double x1, double y1) {
		px0 = x0;
		px1 = x1;
		py0 = y0;
		py1 = y1;
	}

void DDA::desenhaDDA(TCanvas*canvas) {
		double x, y, xs, ys;
		double dx, dy, steps;
		xs = abs(px1 - px0);
		ys = abs(py1 - py0);

		steps = (xs >= ys) ? xs : ys;

		dx = (xs > 0) ? (double)(px1 - px0) / steps : (double)(px1 - px0);
		dy = (ys > 0) ? (double)(py1 - py0) / steps : (double)(py1 - py0);

		x = px0 + 0.5 * _SIGN_(dx);
		y = py0 + 0.5 * _SIGN_(dy);

		int i = 0;
		canvas->Pixels[floor(x)][floor(y)] = clRed;
		while (i < steps) {
				canvas->Pixels[floor(x)][floor(y)] = clRed;
				x += dx;
				y += dy;
				i++;
			}
	}
