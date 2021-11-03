#include "pch.h"
#include "LT.h"
#include "FST.h"
#include "Error.h"
using namespace std;
namespace LT {
	LexTable* Create(int size)
	{
		LexTable* newTable = new LexTable;
		newTable->table = new Entry[size];
		newTable->size = 0;
		newTable->maxsize = size;

		return newTable;
	}
	LT::Entry::Entry()
	{
		char lexema = '`';
		sn = -1;
		int idxTI = -1;
		vType = '`';
	}
	LT::Entry::Entry(char lex, int stringNumber, char vType, int numberInIdTable)
	{
		this->lexema = lex;
		this->sn = stringNumber;
		this->vType = vType;
		this->idxTI = numberInIdTable;
	}
	void Add(LexTable* lextable, Entry entry)
	{
		if (lextable->size > lextable->maxsize) throw ERROR_THROW(2);
		lextable->table[lextable->size] = entry;
		lextable->size++;
	}

	Entry GetEntry(LexTable* lextable, int n)
	{
		return lextable->table[n - 1];
	}

	void Delete(LexTable* lextable)
	{
		delete lextable->LexemText;
		delete lextable->table;
		delete lextable;
	}

}
