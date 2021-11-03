#include "stdafx.h"

namespace IT
{

	Entry::Entry(char* id, int idxLT, IDDATATYPE datatype, IDTYPE idtype, char* oblv)
	{
		strncpy_s(this->id, ID_MAXSIZE, id, ID_MAXSIZE - 1);
		this->idxfirstLE = idxLT;
		this->iddatatype = datatype;
		this->idtype = idtype;
		this->value.vint = TI_INT_DEFAULT;
		this->value.vstr.len = NULL;
		strncpy_s(this->obolv, ID_MAXSIZE, oblv, ID_MAXSIZE - 1);

	}
	IdTable Create(int size)
	{
		IdTable idtable;
		idtable.table = new Entry[size];
		idtable.size = NULL;
		return idtable;
	}
	void Add(IdTable &idtable, Entry entry)
	{
		strncpy_s(idtable.table[idtable.size].id, entry.id, ID_MAXSIZE - 1);
		idtable.table[idtable.size].line = entry.line;
		idtable.table[idtable.size].idxfirstLE = entry.idxfirstLE;
		idtable.table[idtable.size].iddatatype = entry.iddatatype;
		idtable.table[idtable.size].idtype = entry.idtype;
		idtable.table[idtable.size].value.vint = TI_INT_DEFAULT;
		idtable.table[idtable.size].value.vstr.len = NULL;
		idtable.table[idtable.size].value.vstr.str[0] = TI_STR_DEFAULT;
		strncpy_s(idtable.table[idtable.size].obolv, entry.obolv, ID_MAXSIZE);
		idtable.size++;
	}
	Entry GetEntry(IdTable &idtable, int n)
	{
		return idtable.table[n];
	}
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char oblv[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == NULL)
				if (strcmp(idtable.table[i].obolv, oblv) == NULL)
					//		if(idtable.table[i].idtype == idtype)
					return i;
		}
		return -1;
	}
	int GetSize(IdTable &idtable)
	{
		return idtable.size;
	}
	void SetValue(IdTable &idtable, int indTI, char* token)
	{
		if (idtable.table[indTI].iddatatype == NUM)
		{
			int tempInt = atoi(token);
			if (tempInt > INT_MAX)
				tempInt = INT_MAX;
			else if (tempInt < INT_MIN)
				tempInt = INT_MIN;
			idtable.table[indTI].value.vint = tempInt;
		}
		else
		{
			idtable.table[indTI].value.vstr.len = strlen(token);
			strcpy_s(idtable.table[indTI].value.vstr.str, TI_STR_MAXSIZE, token);
		}
	}
}
