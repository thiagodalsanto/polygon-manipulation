//---------------------------------------------------------------------------

#ifndef Cordenadas3DH
#define Cordenadas3DH
#include <vector>
#include "uPonto.h"


//---------------------------------------------------------------------------


class Cordenadas3D : public Ponto{
	public:
		std::vector <Cordenadas3D> cordenadas3d;
		double z;

		Cordenadas3D();
		Cordenadas3D(double nx, double ny ,double nz);

		UnicodeString toString();




};
#endif
