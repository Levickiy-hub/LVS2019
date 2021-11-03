#include "pch.h"

namespace In
{
	void add_token(IN &StrIn, char* &buffer, int &posbuf, bool &isLiteral)
	{
		buffer[posbuf] = 0x00;
		strcpy_s((StrIn.tokens[StrIn.TokenCount].token), (posbuf + 1), buffer);
		StrIn.tokens[StrIn.TokenCount].line = StrIn.lines;
		StrIn.tokens[StrIn.TokenCount].isLiteral = isLiteral;
		StrIn.TokenCount++;
		buffer[0] = posbuf = NULL;
	}

	IN getin(wchar_t infile[], wchar_t logfile[])
	{
		Log::LOG log = Log::getlog(logfile);
		std::ifstream txtfile(infile);
		if (!txtfile.is_open())
			throw ERROR_THROW(110);

		IN StrIn = { IN_CODE_TABLE, NULL, NULL, NULL, NULL };
		StrIn.text = new unsigned char[IN_MAX_LEN_TEXT];
		StrIn.tokens = new StToken[1024];

		bool isLiteral = false;
		unsigned char p;
		char *buffer = new char[IN_MAX_LEN_TEXT];
		int posbuf = NULL;
		while ((p = txtfile.get()) && (!txtfile.eof()))
		{
			switch (StrIn.code[p])
			{
			case IN::STAB:
			{
				if (strlen(buffer))	add_token(StrIn, buffer, posbuf, isLiteral);
				if (p == IN_CODE_ENDL) StrIn.lines++;
				StrIn.size++;
				isLiteral = false;
				break;
			}
			case IN::SEP:
			{
				if (strlen(buffer))	add_token(StrIn, buffer, posbuf, isLiteral);
				buffer[posbuf] = p;
				posbuf++;
				add_token(StrIn, buffer, posbuf, isLiteral);
				StrIn.size++;
				isLiteral = false;
				break;
			}
			case IN::QUOTE:
			case IN::T:
			{
				buffer[posbuf] = p;
				posbuf++;
				StrIn.size++;
				if (p == '\"')
				{
					while ((StrIn.code[p = txtfile.get()] != IN::QUOTE) && !txtfile.eof())
					{
						buffer[posbuf] = p;
						posbuf++;
						StrIn.size++;
					}
					buffer[posbuf] = p;
					posbuf++;
					StrIn.size++;
					isLiteral = true;
					break;
				}
				break;
			}
			case IN::F:
			{
				ERROR_THROW_IN(111, StrIn.lines, StrIn.size);
				break;
			}
			case IN::I:
			{
				StrIn.ignor++;
				StrIn.size++;
				break;
			}
			}

		}
		return StrIn;
	}
}
