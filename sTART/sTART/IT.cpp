#include "pch.h"
#include "IT.h"
#include "Error.h"
#include "LT.h"

namespace IT {
	IdTable* IT::Create(int size) {
		IdTable* newIdTable = new IdTable;
		newIdTable->maxsize = size;
		newIdTable->table = new Entry[size];
		newIdTable->size = 0;
		return newIdTable;
	}

	int IT::Add(IdTable * idtable, Entry newEntry)
	{
		if (idtable->size > idtable->maxsize)
			throw ERROR_THROW(10)
			idtable->table[idtable->size] = newEntry;
		return idtable->size++;
	}

	int IT::GetIndxLastElement(IdTable * idtable)
	{
		return (idtable->size - 1);
	}

	void IT::Delete(IdTable* idtable)
	{
		delete idtable->table;
		delete idtable;
	}

	int IT::isInIdTable(IdTable idTable, Entry entry)
	{
		int cuurentNumberSpace;
		std::string compare;
		std::list<int> listRet;
		for (int i = 0; i < idTable.size; i++)//перебираем все области видимости
		{
			if (!strcmp(idTable.table[i].id, entry.id))//&& ((idTable.table[i].idType==entry.idType)))
			{

				for (int j = 0; j < entry.view.length(); j++)
				{
					compare = compare + entry.view[j];
					if (entry.view[j] == ' ')
					{
						if (compare == idTable.table[i].view) listRet.push_back(i);
					}
				}
				compare.clear();
			}

		}
		int maxLength = INT_MIN;
		int indViewMaxLength = -1;
		if (listRet.empty())
		{
			return -1;
		}
		else
		{
			for (auto i : listRet)
			{
				//std::cout << idTable.table[i].view << std::endl;
				if (maxLength < (int)idTable.table[i].view.length())
				{
					indViewMaxLength = i;
					maxLength = idTable.table[i].view.length();
				}
			}
			return
				indViewMaxLength;
		}
	}
	IT::Entry::Entry()
	{

		this->iddatatype = IT::IDDATATYPE::UNDEF;
		this->idtype = IT::IDTYPE::UNDE;
		this->idxfirstLE = NULL;
		this->view = "";
	}


	IT::Entry::Entry(int NumberString, char id[ID_MAXSIZE], IDDATATYPE idDataType, IDTYPE idType, uValue value, std::string view, int numberSystem)
	{
		this->idxfirstLE = NumberString;
		strcpy_s(this->id, id);
		this->iddatatype = idDataType;
		this->idtype = idType;
		this->numberSystem = numberSystem;
		this->value = value;
		this->view = view;
	}
}