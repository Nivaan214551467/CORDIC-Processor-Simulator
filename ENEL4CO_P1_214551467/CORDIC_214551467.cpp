#include <iostream>
#include <math.h>
#define TBL_SIZE 100				//Number of values in the lookup table of arctan(2^(-i))

using namespace std;

class CORDIC{

private:
	float tanTbl[TBL_SIZE];				//Array for lookup table values
	float x;
	float y;
	float z;
	float m;
	int mode;

	void populateTanTbl()
	{
		if (m == 1)
			for (int j = 0; j < TBL_SIZE; j++)							//If m=1, iterations start from 0 to n.
				tanTbl[j] = (atan(pow(2, -j)))*(180.0 / 3.141592654);	//Result in radians converted to Degrees
		else if (m == 0)												//If m=0, iterations start from 1 to (n-1)
			for (int j = 1; j < (TBL_SIZE - 1); j++)
				tanTbl[j] = pow(2, -j);									// tanTbl[i] = 2^(-i) for m = 0
		else
			for (int j = 1; j < (TBL_SIZE - 1); j++)					//If m=-1, iterations start from 1 to (n-1)
				tanTbl[j] = atanh(pow(2, -j));							// tanTbl[i] = arctanh(2^(-i)) for m = -1
	}

	void rotation()								//Performs the CORDIC algorithm with Rotation control scheme
	{
		float xi = 0.0;							//Used to store previous values
		float yi = 0.0;
		float u = 1.0;
		int i = 1;

		if (m == 1.0)							//Iterations start from 0 when m = 1
			i = 0;

		while (abs(z) > 0.0000000001 || i == 1)			//Iterations stop when z is near zero
		{
			xi = x;
			yi = y;
			u = (z >= 0) ? 1 : -1;//signz(z);						//Condition for Rotation mode. Guarentees convergence 

			x = xi - (m*u*yi*(pow(2, -i)));		//Equations for Rotation mode
			y = yi + (u*xi*(pow(2, -i)));
			z = z - u*tanTbl[i];
			i++;
		}

		cout << "Rot m = " << m << endl;
	}

	void vectoring()
	{
		float xi = 0.0;
		float yi = 0.0;
		float u = 1.0;
		int i = 1;

		if (m == 1.0)							//Iterations start from 0 when m = 1
			i = 0;

		while (abs(y) > 0.0000000001)			//Iterations stop when y is near zero
		{
			xi = x;
			yi = y;
			u = -(((x >= 0) ? 1 : -1)*(y >= 0) ? 1 : -1);//(signz(x)*signz(y));			//Condition for Vectoring mode. Guarentees convergence 

			x = xi - (m*u*yi*(pow(2, -i)));		//Equations for Vectoring mode
			y = yi + (u*xi*(pow(2, -i)));
			z = z - u*tanTbl[i];
			i++;
		}

		cout << "Vec m = " << m << endl;
	}

public:	
	CORDIC(){
		x = 0.8;
		y = 0.5;
		z = 0.2;
		m = 1.0;
		mode = 0.0;
		populateTanTbl();
	}

	~CORDIC(){
	}

	void set_x(float x_in){ x = x_in; }
	void set_y(float y_in){ y = y_in; }
	void set_z(float z_in){ z = z_in; }
	void set_m_mode(float m_in, int mode_in){ 
		mode = mode_in;
		m = m_in; 
		populateTanTbl();
	}

	float get_x(){ return x; }
	float get_y(){ return y; }
	float get_z(){ return z; }

	
	void calculate()
	{
		if (mode == 0.0)
			rotation();
		else
			vectoring();
	}
};