#pragma once
#include<iostream>
#include<string>

using namespace std;
class ErrorNote
{
public:
	ErrorNote(int row,int column, string err)
	{
		line = row;
		col = column;
		error = err;
	}
private:
	int line;
	int col;
	string error;
	friend ostream& operator<<(ostream & os, const ErrorNote &eok)
	{
		os << "ERROR: "  << eok.error << " in line " << eok.line << " at "<< eok.col <<" column"<< endl;

		return os;
	}
};