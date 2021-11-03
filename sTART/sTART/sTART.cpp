
#include "pch.h"
#include "Log.h"
#include "Error.h"
#include "CreatingTables.h"
#include "FST.h"
#include "In.h"
#include "IT.h"
#include "LT.h"
#include "Parm.h"
#include "out.h"
#include "PN.h"
#include "MFST.h"
#include "Greibah.h"
//#include "Debug_MFST.h"
//#include "SematicCheck.h"
//#include "CodeGeneration.h"
int _tmain(int argc, _TCHAR *argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{

		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		log = Log::getlog(parm.log);
		//Log::WriteLine(log, L"Тест", L" Без ошибок", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);
		Tables tables = createTables(in);
		MFST_TRACE_START
			MFST::Mfst mfst(tables, GRB::getGreibach());
		mfst.start();
		semantic::CheckSemantic(tables);

		printOut(in, parm, tables);
		codeGeneration::GenerationCode(tables, parm);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	//system("pause");
	return 0;
}