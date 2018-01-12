//***************************************************************************************************
//																									*
//								Full Name		:		Nivaan Krishundutt							*
//								Student No.		:		214551467									*	
//																									*
//										ENEL4CO PROJECT PART 2										*
//								DESIGNING A CORDIC PROCESSING ELEMENT								*
//																									*
//											10 MAY 2017												*
//																									*
//***************************************************************************************************

#include <iostream>
#include <math.h>
#include <iomanip>
#include "CORDIC_214551467.cpp"
#include <fstream>
#include <string>

#define MEM_SIZE 20			//20 memory addresses in Program Memory
#define BITS 20				//Program memory is 20 bits long

class CORDIC_PE{

private:
	CORDIC PU;						//CORDIC Processing Unit Object
	int memory[MEM_SIZE][BITS];		//20 memory addresses that are 20-bits in size
	int PC;							//Program counter

	void loadMemory(){				//Function reads instructions from text file and stores in array
		string line;
		ifstream file;

		file.open("Instructions.txt");
		short memLoc = 0;								//Controls which memory address is accessed

		while (!(file.eof()))							//Stops when end of file is reached
		{
			getline(file, line);						//Reads line
			if (line.length() == BITS)					//If length of instruction is less than BITS, it is not a valid instruction
			{
				for (int i = 0; i < BITS; i++)
					memory[memLoc][i] = line[i] - '0';	//Stores bit by bit into 2D array called memory
				memLoc++;								//Increment control variable
			}
		}
		file.close();

		for (int i = 0; i < BITS; i++)			//Adds "End Of Instructions" instruction to Program memory after all the instructions
			memory[memLoc][i] = 1;
	}

	void print(){											//Writes output data to text file
		ofstream outfile;
		outfile.open("Outputs.txt", std::ios_base::app);	//Open text file in Append mode
		int i;

		for (i = 4; i < 9; i++)								//Writes destination information of X
			outfile << memory[PC][i];
		outfile << fixed << setw(16) << setprecision(8) << setfill('0') << internal << PU.get_x();	//Outputs X value

		for (i = 9; i < 14; i++)							//Writes destination information of Y
			outfile << memory[PC][i];
		outfile << fixed << setw(16) << setprecision(8) << setfill('0') << internal << PU.get_y();	//Outputs Y value

		for (i = 14; i < 19; i++)							//Writes destination information of Z
			outfile << memory[PC][i];
		outfile << fixed << setw(16) << setprecision(8) << setfill('0') << internal << PU.get_z() << "\n";	//Outputs Z value

		outfile.close();
		cout << "\nWrite complete." << endl;
	}

public:
	CORDIC_PE(){								//Default constructor
		for (int i = 0; i < MEM_SIZE; i++)		//Initializes all memory locations to 0x00000
			for (int j = 0; j < BITS; j++)
				memory[i][j] = 0;

		loadMemory();							//Reads instructions from text file and stores in memory[][]
		PC = 0;									//Initializes Program Counter to 0

		ofstream outfile;						//Erases all the text in the output text file
		outfile.open("Outputs.txt");
		outfile << "";
		outfile.close();
	}

	void program_control(){
		if (PC >= MEM_SIZE)				//If PC reaches end of Program Memory, do nothing
			return;
		
		//Gets opcode (first 4 bits) from Program Memory and stores as integer
		int opcode = (memory[PC][0] * 1000) + (memory[PC][1] * 100) + (memory[PC][2] * 10) + (memory[PC][3]);

		switch (opcode){
		case 0:
			break;							//Do nothing
		case 1:
			PC = 0;							//Reset PC to 0
			break;
		case 10:
			PU.set_m_mode(1.0, 0);			//Rotation, m = 1
			PU.calculate();
			print();						//Print output on text file
			break;
		case 11:
			PU.set_m_mode(1.0, 1);			//Vectoring, m = 1
			PU.calculate();
			print();						//Print output on text file
			break;
		case 100:
			PU.set_m_mode(0.0, 0);			//Rotation, m = 0
			PU.calculate();
			print();						//Print output on text file
			break;
		case 101:
			PU.set_m_mode(0.0, 1);			//Vectoring, m = 0
			PU.calculate();
			print();						//Print output on text file
			break;
		case 110:
			PU.set_m_mode(-1.0, 0);			//Rotation, m = -1
			PU.calculate();
			print();						//Print output on text file
			break;
		case 111:
			PU.set_m_mode(-1.0, 1);			//Vectoring, m = -1
			PU.calculate();
			print();						//Print output on text file
			break;
		case 1111:							//When "End of Instructions" reached, PC is set to the end of the Program Memory, thus
			PC = MEM_SIZE;					//when called again, it will do nothing
		}		

		PC++;								//Point PC to next Memory address in Program Memory
	}
};