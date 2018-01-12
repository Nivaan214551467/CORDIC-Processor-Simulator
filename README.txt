**NB. Moodle only allows a maximum of 3 files thus I have zipped my two source files into 1 file.
*	One source file file is the CORDIC class
*	The other source is the driver class that uses the CORDIC class

The code models the behaviour of a CORDIC processing unit. It is able to determine trignometric functions 
using only addition, subtraction, multiplicaction and shift operations.

The CORDIC has 8 modes of operation, each producing two outputs.

The following codes are used to determine the mode of operation. Also included are the outputs of each mode.
Inputs are x, y and z. Outputs are xn, yn and zn.
____________________________________________________________________________________________________________

000 - Rotation mode (m = 1)
	xn = K1(n)*(x*cos(z) - y*sin(z))
	yn = K1(n)*(y*cos(z) + x*sin(z))
	zn = 0
____________________________________________________________________________________________________________

001 - Rotation mode (m = 1)  (x and y inputs are not required)
	xn = cos(z)
	yn = sin(z)
	zn = 0
____________________________________________________________________________________________________________

010 - Vector mode (m = 1)
	xn = K(n)*(sign(x))*(((x^2) + (y^2)) ^ 0.5)
	yn = 0
	zn = z + arctan(y/x)
____________________________________________________________________________________________________________

011 - ROtation mode (m = 0)
	xn = x
	yn = y + z*x
	zn = 0
____________________________________________________________________________________________________________

100 - Vector mode (m = 0)
	xn = x
	yn = 0
	zn = z + (y/x)
____________________________________________________________________________________________________________

101 - Rotation mode (m = -1)
	xn = K-1(n)*(x*cosh(z) + y*sinh(z))
	yn = K-1(n)*(y*cosh(z) + x*sinh(z))
	zn = 0
____________________________________________________________________________________________________________

110 - Rotation mode (m = -1)  (x and y inputs are not required)
	xn = cosh(z)
	yn = sinh(z)
	zn = 0
____________________________________________________________________________________________________________

111 - Vector mode (m = -1)
	xn = K-1(n)*(sign(x))*(((x^2) - (y^2)) ^ 0.5)
	yn = 0
	zn = z + arctanh(y/x)
_________________________________________________________________________________________
