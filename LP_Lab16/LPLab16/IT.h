#pragma once
#define ID_MAXSIZE		8			//макс число символов идентификатора
#define TI_MAXSIZE		4096		//макс число количество строк в таблице идентификаторов
#define TI_INT_DEFAULT	NULL		//значение по умолчанию для int
#define TI_STR_DEFAULT	NULL		//значение по умолчанию для sting
#define TI_NULLIDX		0xffffffff	//нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	255

namespace IT
{
	enum IDDATATYPE { NUM = 1, STR = 2 };			        //типы данных идентификаторов
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, S = 5 };		//типы идентификаторов: переменная, функция, параметр, литерал,стандарт.библ.
	struct Entry
	{
		int			idxfirstLE;						//индекс в таблице лексем	
		int         line;                           //индекс строки в исходном коде
		char		id[ID_MAXSIZE];					//идентификатор, автоматом усекается до ID_MAXSIZE
		IDDATATYPE	iddatatype;						//тип данных
		IDTYPE		idtype;							//тип идентификатора
		char		obolv[ID_MAXSIZE];				//область видимости
		union
		{
			int	vint;								//значение integer
			struct
			{
				int len;							//количество символов в string
				char str[TI_STR_MAXSIZE - 1];		//символы string
			}vstr;									//значение string
		}value;										//значение идентификатора
		Entry()
		{
			this->value.vint = TI_INT_DEFAULT;
			this->value.vstr.len = NULL;
		}
		Entry(char* id, int idxLT, IDDATATYPE datatype, IDTYPE idtype, char* oblv);
	};
	struct IdTable									//экземпляр таблицы идентификаторов
	{
		int maxsize;								//ёмкость таблицы идентификаторов < TI_MAXSIZE
		int size;									//текущий размер таблицы идентификаторов < maxsize
		Entry* table;								//массив строк таблицы идентификаторов
	};
	IdTable Create(int size = NULL);				//ёмкость таблицы идентификаторов < TI_MAXSIZE
	void Add(										//добавить строку в таблицу идентификаторов
		IdTable &idtable,							//экземпляр таблицы идентификаторов
		Entry entry);								//строка таблицы идентификаторов 
	Entry GetEntry(									//получить строку таблицы идентификаторов
		IdTable &idtable,							//экземпляр таблицы идентификаторов
		int n);										//номер получаемой строки
	int IsId(										//возврат: номер строки(если есть), TI_NULLIDX(если есть)
		IdTable& idtable,							//экземпляр таблицы идентификаторов
		char id[ID_MAXSIZE],
		char oblv[ID_MAXSIZE]);			//область видимости);						//идентификатор
	 
	int GetSize(IdTable &idtable);					//получить размер
	void SetValue(IdTable &idtable, int, char*);	//задать значение идентификатора

}