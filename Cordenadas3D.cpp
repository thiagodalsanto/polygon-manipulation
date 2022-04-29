//---------------------------------------------------------------------------

#pragma hdrstop
#include "uPonto.h"
#include "Cordenadas3D.h"
#include "uJanela.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


Cordenadas3D::Cordenadas3D(double nx, double ny, double nz){

  x = nx;
  y = ny;
  z = nz;


}

Cordenadas3D::Cordenadas3D(){

  x = y =  0;
  z = 1;
}

UnicodeString Cordenadas3D::toString(){
  return "(" + FloatToStr(x) + ";" +
			   FloatToStr(y) + ";" + FloatToStr(z) + ")";
}

