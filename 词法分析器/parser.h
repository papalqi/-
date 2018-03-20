#pragma once
#include<string>
using namespace std;
int getRowNum(string name)
{
	// Return a row number in parse matrix for the non-terminal
	if (name == "Pgm")
		return 0;
	else if (name == "Stmts")
		return 1;
	else if (name == "Stmt")
		return 2;
	else if (name == "Astmt")
		return 3;
	else if (name == "Wstmt")
		return 4;
	else if (name == "Fstmt")
		return 5;
	else if (name == "Y")
		return 6;
	else if (name == "Pexpr")
		return 7;
	else if (name == "Else2")
		return 8;
	else if (name == "E'")
		return 9;
	else if (name == "E")
		return 10;
	else if (name == "T'")
		return 11;
	else if (name == "T")
		return 12;
	else if (name == "F")
		return 13;
	else if (name == "Fatom")
		return 14;
	else if (name == "Opadd")
		return 15;
	else if (name == "Opmul")
		return 16;
}
int getColNum(string name)
{
	// Return a column number in parse matrix for the token
	if (name == "huanhang")
		return 0;
	else if (name == "ID")
		return 1;
	else if (name == "INT")
		return 2;
	else if (name == "STRING")
		return 3;
	else if (name == "+")
		return 4;
	else if (name == "$")
		return 5;
	else if (name == "-")
		return 6;
	else if (name == "*")
		return 7;
	else if (name == "/")
		return 8;
	else if (name == "if")
		return 9;
	else if (name == "while")
		return 10;
	else if (name == "else")
		return 11;
	else if (name == "=")
		return 12;
	else if (name == "(")
		return 13;
	else if (name == ")")
		return 14;
	else if (name == "elseif")
		return 15;

}
