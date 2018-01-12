#include <iostream>
#include <math.h>
#include "CORDIC_PE.cpp"

using namespace std;

int main()
{
	CORDIC_PE PROCESS;

	for (int i = 0; i < 20; i++)
		PROCESS.program_control();
	
	system("Outputs.txt");
	system("pause");
	return 0;
}