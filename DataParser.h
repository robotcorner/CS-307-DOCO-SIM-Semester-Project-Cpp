//===========================================================
// DataParser.h
// Purpose: Interface file for the DataParser utility class.
// Author: Dr. Rick Coleman
//===========================================================
#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <iostream>
#include <fstream>

using namespace std;

class DataParser
{
	private:
		ifstream	*inFile;	     // DOCO world definition file
		int			m_iWorldWidth;   // Number of cells wide for the DOCO grid world
		int			m_iWorldHeight;  // Number of cells high for the DOCO grid world
		int			m_iNumDOCOs;     // Number of DOCOs in the world
		int			m_iNextDOCOIndex;// Index of next DOCO to read
		char        m_sFileName[64]; // Data file
		int			m_FoodCount;     // Number of initial food pellets

	public:
		DataParser(char *fileName);
		~DataParser();
		int getDOCOWorldWidth();
		int getDOCOWorldHeight();
		int getDOCOCount();
		bool getDOCOData(char *movement, int *xpos, int *ypos);
		int getFoodCount();
		bool getNextLine(char *buffer, int n);
};
#endif
