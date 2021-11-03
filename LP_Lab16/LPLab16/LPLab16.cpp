#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "");
	Log::LOG log = Log::INITLOG;
	PN Polish;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);					// Получение аргументов		
		log = Log::getlog(parm.log);									// Создание log				
		Log::LOG out = Log::INITLOG;									// Инициализация log файла	
		out = Log::getlog(parm.out);									// Создаие out файла		
		Log::writeLog(log);												// Запись протокола			
		Log::writeParm(log, parm);										// Запись параметров		
		In::IN in = In::getin(parm.in, parm.out);						// Получение входящих параметров
		Log::writeIn(log, in);											// Запись входящих параметров	
		LeX::LEX tables = LeX::INITLEX(in, log);				     	// Получение таблицы лексем		
		Log::writeAllTokens(log, in);									// Запись всех фраз			
		Log::writeLexicalTable(log, tables.Lextable);	             	// Запись таблицы лекс.		
		Log::writeIDtable(log, tables.IDtable);	                     	// Запись таблицы индент.	
		Log::writeLiterals(log, in);                                    // Запись таблицы литералов
		Log::writeIntermediateCode(log, tables.Lextable);               // Запись промежуточного кода
		MFST::Mfst mfst(tables, GRB::getGreibach());                    // инициализация для синтаксического анализатора
		MFST_TRACE_START(log);                                          // шапка
		mfst.start(log);                                                // старт синтаксического анализа 
		mfst.savededucation();                                          // сохранить правила вывода
		mfst.printrules(log);                                           // печать дерева разбора
			if (Polish.CreatePolishNotation(&tables))
			{
				*log.stream << "\n-------Polish Notation completed!-------------------";
				Log::writeIntermediateCode(log, tables.Lextable);
			}
			
		Log::Close(log);												// Закрытие log файла		
		Log::Close(out);												// Закрытие out файла
	}
	catch (Error::ERROR e)
	{
		Log::writeError(log, e);
	}
	return 0;
}

