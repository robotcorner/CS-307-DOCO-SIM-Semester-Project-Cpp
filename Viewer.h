#pragma once
#include <string>

// the viewer class is just to hold some data for what will be output to the console.

class Viewer
{
private:
	std::string header_message; // holds the start message at the top of the console.
	int line_count_world = 0; // keeps the total line count, basically number of matrix rows.
	int separator_length = 49;
	char separator_char = '=';
	std::string separator_line;
	std::string footer_message; // text at bottom of console.
	std::string program_state_message; // paused / play state

public:
	Viewer(); // create a viewer object
	~Viewer(); // destroy the the viewer object
	
	void setHeaderMessage(std::string); // update header_message
	void setFooterMessage(std::string); // update footer_message
	void setProgramStateMessage(std::string);	// update paused / play message
	void setLineCountWorld(int); // update line_count_range
	void setSeparatorLength(int); // set length of the separator
	void setSeparatorChar(char); // set the separator character
	void setNewSeparatorLine(void); // create new separator based off new settings

	std::string getHeaderMessage(void); // return header message
	std::string getFooterMessage(void);	// return footer message
	std::string getProgramStateMessage(void);	// get paused / play mesage
	std::string getNewSeparatorLine(void); // get separator string
	void printSeparator(void); // print separator string to console with new line
	int getLineCountWorld(void); // get line count
	int getSeparatorLength(void); // get separator length
	char getSeparatorChar(void); // get the char used in the separator
};

