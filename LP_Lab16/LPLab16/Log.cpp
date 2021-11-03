#include "stdafx.h"
#include <sstream>

namespace Log {	
	int k = 0, key = 0;
	LT::LIT lit;

	LOG getlog(wchar_t  logfile[]) {
		LOG logFile;
		logFile.stream = new std::ofstream;
		(*logFile.stream).open(logfile);
		if (!(*logFile.stream).is_open()) throw ERROR_THROW(110);
		wcscpy_s(logFile.logfile, logfile);
		return logFile;
	}

	void writeLine(LOG &log, char *c, ...) {
		char **p = &c;
		while (*p != 0x00)
			*log.stream << *p;
	}

	void writeLine(const LOG &log, wchar_t *c, ...) {
		wchar_t **p = &c;
		wchar_t *str = new wchar_t[ERROR_MAXSIZE_MESSAGE];
		wcscpy(str, *(p++));
		while (*p != L"")			wcscat(str, *(p++));
		char *conv = new char[ERROR_MAXSIZE_MESSAGE];
		wcstombs(conv, str, wcslen(str) + 1);
		*log.stream << conv;
		delete[] conv;
		delete[] str;
	}

	void writeLog(const LOG &log) {
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		char* format = "%d.%m.%Y %H:%M:%S";
		strftime(buffer, 80, format, timeinfo);
		*log.stream << "\n----- Протокол ------ Дата: "
			<< buffer << " --------";
	}

	void writeParm(const LOG &log, const Parm::PARM &parm)
	{
		char inTxt[PARM_MAX_SIZE],
			outTxt[PARM_MAX_SIZE],
			logTxt[PARM_MAX_SIZE];
		wcstombs(inTxt, parm.in, wcslen(parm.in) + 1);
		wcstombs(outTxt, parm.out, wcslen(parm.out) + 1);
		wcstombs(logTxt, parm.log, wcslen(parm.log) + 1);
		*log.stream << "\n----- Параметры --------";
		*log.stream
			<< "\n-in: " << inTxt
			<< "\n-out: " << outTxt
			<< "\n-log: " << logTxt;
	}

	void writeIn(const LOG &log, const In::IN &in) {
		*log.stream << "\n---- Исходные данные ------";
		*log.stream
			<< "\nКоличество символов: " << std::setw(3) << in.size
			<< "\nПроигнорировано	   :" << std::setw(3) << in.ignor
			<< "\nКоличество строк   :" << std::setw(3) << in.lines;
	}

	void writeError(const LOG &log, const Error::ERROR &e) {
		if (log.stream == NULL)
		{
			std::cout << "\nОшибка " << e.id << ": " << e.message
				<< ", строка " << e.inext.line << ", позиция "
				<< e.inext.col << std::endl << std::endl;
		}
		else {

			*log.stream << "\nОшибка " << e.id << ": " << e.message
				<< ", строка " << e.inext.line << ", позиция "
				<< e.inext.col << std::endl << std::endl;
		}
	}

	void writeLexicalTable(const LOG &log, LT::LexTable &Lextable)
	{
		int x = 0;
		*log.stream << "\n---- Таблица лексем ------\n";
		if (Lextable.size > 0) *log.stream << std::setw(10) << std::left << x + 1;
		for (int i = 0; i < Lextable.size; i++)
		{
			if (x < Lextable.table[i].sn)
			{
				x = Lextable.table[i].sn;
				*log.stream << std::endl << std::setw(10) << std::left << x + 1;
			}
			*log.stream << Lextable.table[i].lexema;
		}
	}

	void writeAllTokens(const LOG &log, In::IN &In)
	{
		*log.stream << "\nТаблица слов: \n" <<
			std::setw(6) << std::left << "Номер" <<
			std::setw(8) << std::left << "Строка" <<
			std::setw(10) << std::left << "Литерал?" <<
			std::setw(30) << std::left << "Значение" <<
			std::endl;
		for (int i = 0; i < In.TokenCount; i++)
		{
			key = 0;
			*log.stream <<
				std::setw(6) << std::left << i <<
				std::setw(8) << std::left << In.tokens[i].line;
			/*std::setw(10) << std::left << std::endl;*/
			if (In.tokens[i].isLiteral) 
			{
				for (int j = 0; j < k; j++)
				{
					if (In.tokens[i].token == lit.literals[j])
					{
						key = 1;
					}
				}
				if (key == 0)
				{
					lit.literals[k] = In.tokens[i].token;
					if (In.tokens[i].token[0] == '"')
						lit.typel[k] = "String";
					else
						lit.typel[k] = "int";
					k++;
				}
				*log.stream <<
					std::setw(10) << std::left << ("Да");
			}
			else {
				*log.stream <<
					std::setw(10) << std::left << ("Нет");
			}
			*log.stream << ::setw(30) << std::left << In.tokens[i].token <<
				std::endl;
		}

	}

		void writeIDtable(const LOG &log, IT::IdTable &IDtable)
		{
			*log.stream << "\nТаблица идентификаторов: \n" <<
				std::setw(5) << std::left << "#" <<
				std::setw(10) << std::left << "Имя" <<
				std::setw(13) << std::left << "Тип данных" <<
				std::setw(10) << std::left << "Тип" <<
				std::setw(7) << std::left << "Номер" <<
				std::setw(20) << std::left << "Значение" <<
				std::setw(19) << std::left << "область видимости" <<
				std::endl;
			for (int i = 0; i < IDtable.size; i++)
			{
				*log.stream << std::setw(5) << std::left << i <<
					std::setw(10) << std::left <<
					std::setw(10) << std::left << IDtable.table[i].id <<
					std::setw(13) << std::left;
				if (IDtable.table[i].iddatatype == IT::NUM)
					*log.stream << LEX_TYPE_INT;
				if (IDtable.table[i].iddatatype == IT::STR)
					*log.stream << LEX_TYPE_CHAR;
				*log.stream << std::setw(10) << std::left;
				switch (IDtable.table[i].idtype)
				{
				case IT::F:*log.stream << LEX_TYPE_FUNCTION; break;
				case IT::V:*log.stream << LEX_TYPE_VARIABLE; break;
				case IT::P:*log.stream << LEX_TYPE_PARAMETR; break;
				case IT::L:*log.stream << LEX_TYPE_LITERAL; break;
				case IT::S:*log.stream << LEX_TYPE_STANDART; break;
				}
				*log.stream << std::setw(7) << std::left;
				if (IDtable.table[i].idxfirstLE == -1) *log.stream << ("default");
				else *log.stream << IDtable.table[i].idxfirstLE;
				*log.stream << std::setw(20) << std::left;
				if (IDtable.table[i].iddatatype == IT::NUM)
					*log.stream << IDtable.table[i].value.vint;
				else
					if (IDtable.table[i].iddatatype == IT::STR)
						*log.stream << ((IDtable.table[i].value.vstr.len > 0) ? (IDtable.table[i].value.vstr.str) : (""));
				*log.stream << std::setw(19) << std::left;
				*log.stream << IDtable.table[i].obolv;
				*log.stream << std::endl;
			}
		}
	

	void writeLiterals(const LOG& log, In::IN& In)
	{
		char Name = 'L';
		*log.stream << "\nТаблица литералов: \n" <<
			std::setw(10) << std::left << "Название" <<
			std::setw(10) << std::left << "Тип" <<
			std::setw(30) << std::left << "Значение" <<
			std::endl;
		for (int i = 0; i < k; i++)
		{
			std::stringstream ss;
			ss << Name << i;
			lit.name[i] = ss.str();
			*log.stream <<
				std::setw(10) << std::left << lit.name[i];
			*log.stream <<
				std::setw(10) << std::left << lit.typel[i];
			*log.stream << std::setw(30) << std::left << lit.literals[i] <<
				std::endl;
		}
	}

	void writeIntermediateCode(LOG &log, LT::LexTable &Lextable)
	{
		int pb = NULL;
		char*buffer = new char[1024];
		*log.stream << "\n---------Промежуточный код------------------------------\n";
		for (int i = 0; i < Lextable.size; i++)
		{
			buffer[pb] = Lextable.table[i].lexema;
			pb++;
			if (Lextable.table[i + 1].sn != Lextable.table[i].sn)
			{
				buffer[pb] = '\0';
				if (Lextable.table[i].sn < 10)
				{
					*log.stream << '0';
				}

				*log.stream << Lextable.table[i].sn << ' ';
				*log.stream << buffer << std::endl;
				pb = NULL;
			}
		}
	}
	void Close(const LOG &log)
	{
		(*log.stream).close();
	};
}