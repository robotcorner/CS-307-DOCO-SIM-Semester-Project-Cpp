																						#include "Viewer.h"
#include <iostream>

Viewer::Viewer()
{
	this->header_message = "============= DOCO World Simulation =============";
	this->footer_message = "Created by: Stephen Stammen\n";
	this->separator_line = std::string(this->separator_length, this->separator_char);
	this->program_state_message = "running";
}

Viewer::~Viewer()
{

}

void Viewer::setHeaderMessage(std::string newHeader)
{
	if (newHeader.length() < 100) {
		this->header_message = newHeader;
	}
	else
	{
		this->header_message = "Too Long Header Message Attempted";
	}
}

void Viewer::setFooterMessage(std::string newFooter)
{
	if (newFooter.length() < 100) {
		this->footer_message = newFooter;
	}
	else
	{
		this->footer_message = "Too Long Footer Message Attempted";
	}
}

void Viewer::setProgramStateMessage(std::string newState)
{
	this->program_state_message = newState;
}

void Viewer::setLineCountWorld(int lineCount)
{
	this->line_count_world = lineCount;
}

void Viewer::setSeparatorChar(char myChar)
{
	this->separator_char = myChar;
}

void Viewer::setSeparatorLength(int newLength)
{
	if (newLength < 100) // prevent more than 150 characters for separation
	{
		this->separator_length = newLength;
	}
	else
	{
		this->separator_length = 100;
	}
}

void Viewer::setNewSeparatorLine(void)
{
	this->separator_line = std::string(this->separator_length, this->separator_char);
}

std::string Viewer::getHeaderMessage(void)
{
	return this->header_message;
}

std::string Viewer::getFooterMessage(void)
{
	return this->footer_message;
}

std::string Viewer::getProgramStateMessage(void)
{
	return this->program_state_message;
}

std::string Viewer::getNewSeparatorLine(void)
{
	return this->separator_line;
}

void Viewer::printSeparator(void)
{
	std::cout << this->separator_line << "\n";
}

int Viewer::getLineCountWorld(void) 
{
	return this->line_count_world;
}

int Viewer::getSeparatorLength(void) 
{
	return this->separator_length;
}

char Viewer::getSeparatorChar(void)
{
	return this->separator_char;
}
