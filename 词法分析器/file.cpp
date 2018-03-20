#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include"ErrorPrint.h"
#include"scaner.h"
#include<vector>
#include <queue>
#include <stack>
#include <list>
#include"parser.h"
//#include"KeyWord.h"
using namespace std;
vector<ErrorNote>errorNote;

void lineSort(string line, int linenumber);
vector<token>tokens;
queue<token>tokenss;
struct Syms {
	string name;	// name of symbol
	bool isTerm;	// is symbol term or not
					//vector<Syms> kids;	// kids
					//int kidCount;	// number of kids
};

struct Node {
	int id = 0;
	Syms symbol;
	int ruleNum = 0;
	Node* pMom;
	Syms* pKids[4];
	int kidCount = 0;
	int position = 0;

};
stack<Syms> LLStack;
int ParseMatrix[17][16] =
{
	{0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0},
	{ 0,2,0,0,0,22,0,0,0,2,2,0,0,0,0,0 },
	{ 0,31,0,0,0,0,0,0,0,33,32,0,0,0,0,0 },
	{ 0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0 },
	{ 0,8,8,8,0,0,0,0,0,0,0,0,0,8,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0 },
	{ 112,0,0,0,0,0,0,0,0,0,0,11,0,0,0,10 },
	{ 122,0,0,0,121,0,122,0,0,0,0,0,0,0,122,0 },
	{ 0,13,13,13,0,0,0,0,0,0,0,0,0,0,13,0 },
	{ 142,0,0,0,142,0,142,141,141,0,0,0,0,0,142,0 },
	{ 0,15,15,15,0,0,0,0,0,0,0,0,0,15,0,0 },
	{ 0,161,161,161,0,0,0,0,0,0,0,0,0,162,0,0 },
	{ 0,171,172,173,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,181,0,182,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,191,192,0,0,0,0,0,0,0 },
};
void performRule(int rule);
void parseMachine()
{
	while (!LLStack.empty())
	{

		// If end of file, pop off stack and done
		if (LLStack.top().name == "$" && tokenss.empty())
		{
			LLStack.pop();
		}
		else if (LLStack.top().isTerm == true)
		{
			if (LLStack.top().name == tokenss.front().name)
			{
				LLStack.pop();
				tokenss.pop();
			}
			else
			{

				cout << "Error on line number: " << tokenss.front().lineNum << " with token:  " << tokenss.front().name<< tokenss.front().value << endl;
				system("pause");
				//exit(-1);
			}
		}

		else
		{
			auto s = ParseMatrix[getRowNum(LLStack.top().name)][getColNum(tokens.front().name)];
			cout << getRowNum(LLStack.top().name)<<"|" << getColNum(tokens.front().name )<<" ";
			performRule(s);
			

		}
		
	}
	cout << "No issues found with input" << endl;
}

int main(int argc ,char *argv)
{

	ifstream fin;
	//打开文件并检查succeed
	fin.open("text.txt");
	if (!fin.is_open())
	{
		cout << "file is not open succeed";
		system("pause");
		return 0;
	}
	string line;
	int lineNumber=0;
	
	//调用linesort逐行处理信息
	while(!fin.eof())
	{
		getline(fin, line);
		cout << lineNumber++ << ":";
		lineSort(line, lineNumber);
		
		cout << endl;
	}
	//输出错误信息
	for (auto tem : errorNote)
	{
		cout << tem;
	}

	fin.close();

	//语法分析器
	for (auto s : tokens)
	{ 
		cout << s;
		tokenss.push(s);
	}
	
	Syms eof{ "$", true };
	LLStack.push(eof);

	Syms pgm{ "Pgm", false };
	LLStack.push(pgm);

	parseMachine();
	system("pause");
	return 0;
}

void lineSort(string line,int linenumber)
{

	int maxColumn = line.length();
	if (maxColumn == 0)
		return;
	int curColumn = 0;
	cout << maxColumn<<endl;
	while (curColumn < maxColumn)
	{
		if (line[curColumn] == ' ')
		{
			curColumn++;

		}
		else if ((line[curColumn] >= 'a'&&line[curColumn] <= 'z') || (line[curColumn] >= 'A'&&line[curColumn] <= 'Z'))
		{
			int start = curColumn;
			while ((line[curColumn] >= '0'&&line[curColumn] <= '9') || (line[curColumn] >= 'a'&&line[curColumn] <= 'z') ||
				(line[curColumn] >= 'A'&&line[curColumn] <= 'Z'))
			{
				curColumn++;
			}
			string curString = line.substr(start, curColumn - start);
			//curColumn++;					
			tokens.push_back(token(tokenClass::ABC, curString, linenumber));
		}
		else if (line[curColumn] >= '0'&&line[curColumn] <= '9')
		{
			int start = curColumn;
			while ((line[curColumn] >= '0'&&line[curColumn] <= '9'))
			{
				curColumn++;
			}
			string curString = line.substr(start, curColumn - start);
			curColumn++;
			tokens.push_back(token(tokenClass::intConstant, curString, linenumber));
		}
		else

		{
			int start = curColumn;		
			switch (line[curColumn])
			{

			case'>':
				tokens.push_back(token(tokenClass::delimiter, ">", linenumber));
				curColumn++;
				break;
			case'=':
				tokens.push_back(token(tokenClass::delimiter, "=", linenumber));
				curColumn++;
				break;
			case'*':
				tokens.push_back(token(tokenClass::delimiter, "*", linenumber));
				curColumn++;
				break;
			case'/':
				tokens.push_back(token(tokenClass::delimiter, "/", linenumber));
				curColumn++;
				break;
			case'+':
				tokens.push_back(token(tokenClass::delimiter, "+", linenumber));
				curColumn++;
				break;
			case'-':
				if (line[curColumn++] = '-')
				{

					curColumn = maxColumn;

				}
				else
					tokens.push_back(token(tokenClass::delimiter, "-", linenumber));
				break;
			case';':
				tokens.push_back(token(tokenClass::delimiter, ";", linenumber));
				curColumn++;
				break;
			case'(':
				tokens.push_back(token(tokenClass::delimiter, "(", linenumber));
				curColumn++;
				break;
			case')':
				tokens.push_back(token(tokenClass::delimiter, ")", linenumber));
				curColumn++;
				break;
			case'#':
				tokens.push_back(token(tokenClass::delimiter, "#", linenumber));
				curColumn++;
				break;
			case'{':
				tokens.push_back(token(tokenClass::delimiter, "{", linenumber));
				curColumn++;
				break;
			case'}':
				tokens.push_back(token(tokenClass::delimiter, "}", linenumber));
				curColumn++;
			case'[':
				tokens.push_back(token(tokenClass::delimiter, "[", linenumber));
				curColumn++;
			case']':
				tokens.push_back(token(tokenClass::delimiter, "]", linenumber));
				curColumn++;
			case'\"':

				curColumn++;
				while (line[curColumn] != '\"'&&curColumn <maxColumn)
				{
					curColumn++;
				}
				if (line[curColumn] != '\"')
				{
					errorNote.push_back(ErrorNote(linenumber, curColumn, "there is a no \"   "));
				}
				else
				{
					curColumn++;
					string curString = line.substr(start, curColumn - start);
					tokens.push_back(token(tokenClass::String, curString, linenumber));

				}
				curColumn++;
				break;
			default:

				errorNote.push_back(ErrorNote(linenumber, curColumn, "This is a illegal char"));
				curColumn++;
				break;
			}

		}

	}

	tokens.push_back(token(tokenClass::huanhang, "huanhang", linenumber));
}
void performRule(int rule)
{

	switch (rule)
	{
	case 0: // Cell is empty
	{
		cout << "Error on line number: " << tokens.front().lineNum << " with token:  " << tokens.front().name<< tokenss.front().value << endl;
		system("pause");
		exit(-1);
		break;
	}
	case 1: 
	{
		Syms Block = { "Stmts", false };
		LLStack.pop();
		LLStack.push(Block);
		break;
	}

	case 22: // Stmts = eps
	{
		LLStack.pop();
		break;
	}
	case 2: // Stmts = Stmt semi Stmt
	{
		Syms Stmt = { "Stmt", false };
		Syms semi = { "huanhang", true };
		Syms Stmts = { "Stmts", false };

		LLStack.pop();
		LLStack.push(Stmts);
		LLStack.push(semi);
		LLStack.push(Stmt);
		break;
	}
	case 31: // Stmt = Astmt
	{
		Syms Astmt = { "Astmt", false };

		LLStack.pop();
		LLStack.push(Astmt);
		break;
	}
	case 32: // Stmt = Wstmt
	{
		Syms Wstmt = { "Wstmt", false };

		LLStack.pop();
		LLStack.push(Wstmt);
		break;
	}
	case 33: // Stmt = Fstmt
	{
		Syms Fstmt = { "Fstmt", false };

		LLStack.pop();
		LLStack.push(Fstmt);
		break;
	}
	case 4: // Astmt = id equal Y
	{
		Syms id = { "ID", true };
		Syms equal = { "=", true };
		Syms Y = { "Y", false };

		LLStack.pop();
		LLStack.push(Y);
		LLStack.push(equal);
		LLStack.push(id);
		break;
	}
	case 8: // Y = E
	{
		Syms E = { "E", false };

		LLStack.pop();
		LLStack.push(E);
		break;
	}
	case 7: // Y = kwdinput
	{
		Syms kwdinput = { "kwdinput", true };
		LLStack.pop();
		LLStack.push(kwdinput);
		break;
	}

	case 5: 
	{
		Syms kwdwhile = { "while", true };
		Syms Pexpr = { "Pexpr", false };
		Syms Stmts = { "Stmts", false };

		LLStack.pop();
		LLStack.push(Stmts);
		LLStack.push(Pexpr);
		LLStack.push(kwdwhile);
		break;
	}
	case 6: // Fstmt = kwdif Pexpr Block Else2
	{
		Syms kwdif = { "if", true };
		Syms Pexpr = { "Pexpr", false };
		Syms Stmts = { "Stmts", false };
		Syms Else2 = { "Else2", false };

		LLStack.pop();
		LLStack.push(Else2);
		LLStack.push(Stmts);
		LLStack.push(Pexpr);
		LLStack.push(kwdif);
		break;
	}
	case 112: // Else2 = eps
	{
		LLStack.pop();
		break;
	}
	case 10: //Else2 = kwdelseif Pexpr Block Else2
	{
		Syms kwdelseif = { "elseif", true };
		Syms Pexpr = { "Pexpr", false };
		Syms Stmts = { "Stmts", false };
		Syms Else2 = { "Else2", false };

		LLStack.pop();
		LLStack.push(Else2);
		LLStack.push(Stmts);
		LLStack.push(Pexpr);
		LLStack.push(kwdelseif);
		break;
	}
	case 11: //Else2 = kwdelse Block
	{
		Syms kwdelse = { "else", true };
		Syms Stmts = { "Stmts", false };

		LLStack.pop();
		LLStack.push(Stmts);
		LLStack.push(kwdelse);
		break;
	}


	case 122: // E'= eps
	{
		LLStack.pop();
		break;
	}
	case 121: // E' = Opadd T E'
	{
		Syms Opadd = { "Opadd", false };
		Syms T = { "T", false };
		Syms Eprime = { "E'", false };

		LLStack.pop();
		LLStack.push(Eprime);
		LLStack.push(T);
		LLStack.push(Opadd);
		break;
	}
	case 13: // E = T E'
	{
		Syms T = { "T", false };
		Syms Eprime = { "E'", false };

		LLStack.pop();
		LLStack.push(Eprime);
		LLStack.push(T);
		break;
	}
	case 142: // T'= eps
	{
		LLStack.pop();
		break;
	}
	case 141: // T'= Opmul F T'
	{
		Syms Opmul = { "Opmul", false };
		Syms F = { "F", false };
		Syms Tprime{ "T'", false };

		LLStack.pop();
		LLStack.push(Tprime);
		LLStack.push(F);
		LLStack.push(Opmul);
		break;
	}
	case 15: 
	{
		Syms F = { "F", false };
		Syms Tprime{ "T'", false };

		LLStack.pop();
		LLStack.push(Tprime);
		LLStack.push(F);
		break;
	}
	case 161: //F = Fatom
	{
		Syms Fatom = { "Fatom", false };

		LLStack.pop();
		LLStack.push(Fatom);
		break;
	}
	case 162: // F = Pexpr
	{
		Syms Pexpr = { "Pexpr", false };

		LLStack.pop();
		LLStack.push(Pexpr);
		break;
	}
	case 9: // Pexpr = ( E )
	{
		Syms paren1 = { "(", true };
		Syms E{ "E", false };
		Syms paren2 = { ")", true };

		LLStack.pop();
		LLStack.push(paren2);
		LLStack.push(E);
		LLStack.push(paren1);
		break;
	}
	case 171:
	{
		Syms id = { "ID", true };

		LLStack.pop();
		LLStack.push(id);
		break;
	}
	case 172: 
	{
		Syms integer = { "INT", true };

		LLStack.pop();
		LLStack.push(integer);
		break;
	}

	case 173: 
	{
		Syms stringl = { "STRING", true };

		LLStack.pop();
		LLStack.push(stringl);
		break;
	}
	case 181: 
	{
		Syms plus = { "+", true };

		LLStack.pop();
		LLStack.push(plus);
		break;
	}
	case 182: 
	{
		Syms minus = { "-", true };

		LLStack.pop();
		LLStack.push(minus);
		break;
	}

	case 192: 
	{
		Syms slash = { "/", true };

		LLStack.pop();
		LLStack.push(slash);
		break;
	}
	case 191: 
	{
		Syms caret = { "*", true };

		LLStack.pop();
		LLStack.push(caret);
		break;
	}


	}
}