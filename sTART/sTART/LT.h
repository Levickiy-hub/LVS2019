#pragma once
#include "pch.h"
#include "Error.h"
#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0xffffff
#define LEX_SHORT 't'
#define LEX_STRING 't'
#define LEX_CHAR 't'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_DECLARE 'd'
#define LEX_RETURN 'r'
#define LEX_PRINT 'p'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_PLUS 'v'
#define LEX_MINUS 'v'
#define LEX_STAR 'v'
#define LEX_DIRSLASH 'v'
#define LEX_MOD 'v'
#define LEX_EQUAL '='
#define LEX_MAIN 'm'
#define LEX_RANDOM 'g'
#define LEX_CYCLE 'c'
#define LEX_ABS 'a'
#define LEX_POW 'w'
#define LEX_LEFTHESIS_POLISH_NOTATION '!'
#define LEX_RIGHTHESIS_POLISH_NOTATION '?'

namespace LT {
	struct Entry {
		char lexema;
		int sn;
		int idxTI;
		char vType = '`';
		Entry();
		Entry(char lex, int stringNumber, char vType = '`', int numberInIdTable = -1);
	};
	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
		unsigned char* LexemText;
		int countEnd = 0;
	};

	LexTable* Create(int size);
	void Add(LexTable* lextable, Entry entry);
	Entry GetEntry(LexTable* lextable, int n);
	void Delete(LexTable* lextable);

}