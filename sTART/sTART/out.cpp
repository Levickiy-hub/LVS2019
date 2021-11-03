#include "pch.h"
#include "out.h"
#include "In.h"
#include "Parm.h"
#include "LT.h"
#include "IT.h"
#include "CreatingTables.h"
using namespace std;
void printOut(In::IN input, Parm::PARM parm, Tables tables)
{
	ofstream fout(parm.out);
	int numberString = 1;
	fout << "Cодержимое таблицы лексем в соответствии с образцом:" << endl;
	fout << setw(4) << '1' << "  ";
	for (int i = 0; i < tables.LEXTABLE->size; i++)
	{
		if (numberString != tables.LEXTABLE->table[i].sn)
		{
			fout << '\n';
			fout << setw(4) << ++numberString << "  ";
		}
		fout << tables.LEXTABLE->table[i].lexema;
	}
	fout << endl << endl;
	fout << setw(4) << "Cодержимое таблицы лексем в соответствии с её первоначальным представлением: " << endl << endl;
	fout << setw(4) << "Лексема:" << setw(20) << "Строка:" << setw(23) << "Значение знака:" << endl;
	for (int i = 0; i < tables.LEXTABLE->size; i++)
	{
		fout << setw(4) << tables.LEXTABLE->table[i].lexema;
		fout << setw(20) << tables.LEXTABLE->table[i].sn;
		fout << setw(20) << tables.LEXTABLE->table[i].vType;
		fout << endl;

	}
	fout << endl << endl;
	fout << setw(4) << "Cодержимое таблицы идентификаторов в соответствии с её первоначальным представлением: " << endl << endl;
	fout << "Идентификатор: " << setw(25) << "Область видимости: " << setw(40) << " Номер первого вхождения: " << setw(20) << " Тип: " << setw(25) << "Значение: " << endl;
	fout << endl;
	for (int i = 0; i < tables.IDTABLE->size; i++)
	{
		fout << setw(20) << left << tables.IDTABLE->table[i].id;
		fout << setw(35) << left << tables.IDTABLE->table[i].view;
		fout << setw(40) << left << tables.IDTABLE->table[i].idxfirstLE;
		switch (tables.IDTABLE->table[i].iddatatype)
		{
		case IT::IDDATATYPE::SHORT: fout << setw(10) << left << "short";
			break;
		case IT::IDDATATYPE::CHAR: fout << setw(10) << left << "char";
			break;
		case IT::IDDATATYPE::STR: fout << setw(10) << left << "str";
			break;
		}
		switch (tables.IDTABLE->table[i].idtype)
		{
		case IT::IDTYPE::F: fout << setw(10) << left << "FUNCTION";
			break;
		case IT::IDTYPE::L: fout << setw(10) << left << "lexema";
			break;
		case IT::IDTYPE::P: fout << setw(10) << left << "parm";
			break;
		case IT::IDTYPE::V: fout << setw(10) << left << "value";
			break;

		}

		if (tables.IDTABLE->table[i].iddatatype == 1) fout << tables.IDTABLE->table[i].value.vShort;
		else
		{

			for (int j = 0; j < tables.IDTABLE->table[i].value.vstr->len; j++)
				fout << left << tables.IDTABLE->table[i].value.vstr->str[j];
		}
		fout << endl;

	}
}




