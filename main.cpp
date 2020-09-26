
#include <iostream>
#include "DataParser.h"

#define DEBUG_1

int main() {
	char inFile[] = "DOCOData01.xml";
	DataParser* myParser = new DataParser(inFile);
	cout << "Sensor count is " << myParser->getDOCOCount() << endl;


	#ifdef DEBUG_1
	std::cout << "Hi";
	#endif	

	return 0;
}