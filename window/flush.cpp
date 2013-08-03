#include "flush.h"
#include <stdlib.h> //random function
// #include "draw.h"

#include "direct3D.h"

namespace _flush{

	int flushscreen(){

		for(int i = 0; i < 100; ++i)
			_direct3D::DrawPixel(100, i, 0);
		return 0;
	}
	
}
