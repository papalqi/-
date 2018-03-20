#pragma once

#include<string>
#include<array>
using namespace std;
enum tokenClass
{
	ABC, keyWord, identifier, intConstant, floatConstant, delimiter, String,huanhang
};
class token
{
public:
	token(enum tokenClass cal,string str,int num)
	{
		lineNum = num;
		value = str;
		if (cal == ABC)
		{
			for (auto temClass :KeyWord)
			{
				if (temClass == str)
				{
					tokenEn = keyWord;
					break;
				}
				else
					tokenEn = identifier;
			}
		}
		else if (cal == intConstant)
		{
			tokenEn = intConstant;
		}
		else if (cal == floatConstant)
		{
			tokenEn = floatConstant;
		}
		else if (cal == delimiter)
		{
			tokenEn = delimiter;
		}
		else if (cal == String)
		{
			tokenEn = String;
		}
		else if(cal = huanhang)
		{
			ID = 2000;
			value = name = str;
			tokenEn = huanhang;
			return;
		}
		id_q();
	}
	array<string, 22> KeyWord = { "and","or","not","function","table","nil",
		"for","while","do","break","in","return",
		"until","true","false","repeat","if"
		"then", "else","elseif","local" ,"end"};
	array<string, 20 >Delimiter = {"'", "(", ")","*","+",",","-","/","=","<",">","<=",">=","[","]","==","<>","{","}","\""};

 	friend ostream& operator<<(ostream & os, const token &tok)
	{
		
		os << "<" << "ID:" << tok.ID << "  ," << " value:" << tok.value << ">" << endl;

		return os;

	}
	int lineNum;
	string value;
	string name;
private:
	int ID;
	
	tokenClass tokenEn;
	
	void id_q()
	{
		if (tokenEn == keyWord)
		{
			for (int i = 0; i < KeyWord.size(); i++)
			{
				if (value == KeyWord[i])
				{
					name = value;
					ID = i + 1;
					break;
				}
			}
		}
		else if(tokenEn == identifier)
		{
			name = "ID";
			ID = 23;
		}
		else if (tokenEn == intConstant)
		{
			name = "INT";
			ID = 24;
		}
		else if (tokenEn == floatConstant)
		{
			ID = 25;
		}
		else if (tokenEn == String)
		{
			name = "STRING";
			ID = 26;
		}
		else if (tokenEn == delimiter)
		{
			for (int i = 0; i < Delimiter.size(); i++)
			{
				if (value == Delimiter[i])
				{
					name = value;
					
					ID = i + 27;
					break;
				}
			}
		}
	}
};