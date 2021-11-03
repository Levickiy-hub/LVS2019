#include "pch.h"
#include "Error.h"
#include "In.h"
using namespace std;
namespace In
{
	IN getin(wchar_t infile[])
	{
		ifstream fin(infile);
		IN newIn;
		if (!fin.is_open())
			throw ERROR_THROW(110);
		string text;
		int line = 1;
		int column = 1;
		while (!fin.eof())
		{
			string textLine;
			textLine.clear();
			getline(fin, textLine);
			char symb;
			for (int i = 0; i < textLine.length(); i++)
			{
				symb = textLine[i];
				if (newIn.code[(int)((unsigned char)symb)] == IN::T) text += symb;
				else
				{
					if (newIn.code[(int)((unsigned char)symb)] == IN::F)
					{
						cout << (char)symb << endl;
						throw ERROR_THROW(15);

					}
					else if (newIn.code[(int)((unsigned char)symb)] == IN::I)
					{
						newIn.ignor++;
					}
					else
						text += (unsigned char)(newIn.code[(int)((unsigned char)symb)]);
				}
				column++;

			}
			text += '\n';
			line++;
			column = 1;
		}
		string textFormated;
		bool quote = false;
		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] == '"')
			{
				if (!quote) quote = true;
				else quote = false;
			}
			if ((text[i] == '{' || text[i] == '}' || text[i] == '(' || text[i] == ')' || text[i] == '[' || text[i] == ']' ||
				text[i] == ';' || text[i] == ',' || text[i] == '+' || text[i] == '*' ||
				text[i] == '=' || text[i] == '-' || text[i] == '/' || text[i] == '%') && !quote)
			{
				textFormated = textFormated + ' ' + text[i] + ' ';
			}
			else
			{
				textFormated += text[i];
			}
		}
		newIn.textFormated = new unsigned char[textFormated.length()];
		int indNewInTextFormated = 0;
		bool spaceAdded = false;
		newIn.counterLexem = 10;
		for (int i = 0; i < textFormated.length(); i++)
		{
			if (textFormated[i] == ' ')
			{
				if (!spaceAdded)
				{
					newIn.counterLexem++;
					newIn.textFormated[indNewInTextFormated++] = textFormated[i];
					spaceAdded = true;
				}

			}
			else
			{
				newIn.textFormated[indNewInTextFormated++] = textFormated[i];
				spaceAdded = false;
			}
		}
		newIn.textFormated[indNewInTextFormated] = '\0';
		cout << newIn.textFormated;
		cout << endl << endl << endl;
		newIn.size = strlen((char*)newIn.textFormated);
		return newIn;
	}
}
