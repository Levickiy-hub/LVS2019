#include "pch.h"
#include "Error.h"
namespace Error
{
	// 0-99 системные ошибки
	// 100-109 ошибки параметров
	// 110-119 ошибки открытия файлов
	ERROR errors[ERROR_MAX_ENTRY]
	{
		ERROR_ENTRY(0,"Недопустимый код ошибки"),
		ERROR_ENTRY(1,"Системный сбой"),
		ERROR_ENTRY(2,"Вы пытаетесь превысить размер таблицы лексем"),
		ERROR_ENTRY(3,"Вы пытаетесь превысить размер таблицы идентификаторов"),ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY(5,"Не найдена парная скобка"),
		ERROR_ENTRY(6,"Найдено более 1 main"),ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY(8,"Отсутствует main"),
		ERROR_ENTRY(9,"Нераспознанная лексема"),
		ERROR_ENTRY(10,"Превышен размер таблицы"),
		ERROR_ENTRY(11,"Неопределенный тип идентификатора"),
		ERROR_ENTRY(12,"Присутствует повторение функции"),
		ERROR_ENTRY(13,"Присутствует повтороение функции main"),
		ERROR_ENTRY(14,"Отсутствует функция main"),
		ERROR_ENTRY(15,"Код недопустимого символа"),
		ERROR_ENTRY_NODEF(16),
		ERROR_ENTRY_NODEF(17),ERROR_ENTRY_NODEF(18),
		ERROR_ENTRY_NODEF(19),ERROR_ENTRY_NODEF10(20),
		ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50),ERROR_ENTRY_NODEF10(60),
		ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),
		ERROR_ENTRY_NODEF10(90),ERROR_ENTRY(100,"Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Ошибка при открытии файла с иходным кодом (-in)"),
		ERROR_ENTRY(111,"Недопустимый символ в исходном коде (-in)"),
		ERROR_ENTRY(112,"Ошибка при создании файла (-log)"),
		ERROR_ENTRY_NODEF(113),ERROR_ENTRY_NODEF(114),
		ERROR_ENTRY_NODEF(115),ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),
		ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200,"Неверный тип параметра return : "),
		ERROR_ENTRY_NODEF(201,"Функция не найдена: "),
		ERROR_ENTRY_NODEF(202,"Превышено количество параметров: "),
		ERROR_ENTRY_NODEF(203,"Несоответствие типов левой и правой части выражения: "),
		ERROR_ENTRY_NODEF(204,"Ошибка в операторе ABS: "),
		ERROR_ENTRY_NODEF(205,"Ошибка в операторе POW: "),
		ERROR_ENTRY_NODEF(206),ERROR_ENTRY_NODEF(207),
		ERROR_ENTRY_NODEF(208),ERROR_ENTRY_NODEF(209),
		ERROR_ENTRY_NODEF10(210),ERROR_ENTRY_NODEF10(220),
		ERROR_ENTRY_NODEF10(230),ERROR_ENTRY_NODEF10(240),
		ERROR_ENTRY_NODEF10(250),ERROR_ENTRY_NODEF10(260),
		ERROR_ENTRY_NODEF10(270),ERROR_ENTRY_NODEF10(280),
		ERROR_ENTRY_NODEF10(290),ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600,"Неверная структура программы"),
		ERROR_ENTRY(601,"Ошибочный оператор"),
		ERROR_ENTRY(602,"Ошибка в выражении"),
		ERROR_ENTRY(603,"Ошибка в параметрах функции"),
		ERROR_ENTRY(604,"Ошибка программной конструкции"),
		ERROR_ENTRY(605,"Ошибка, неверная структура параметров функции"),
		ERROR_ENTRY_NODEF(606),
		ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),
		ERROR_ENTRY_NODEF(609),ERROR_ENTRY_NODEF10(610),
		ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),
		ERROR_ENTRY_NODEF10(640),ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),
		ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900),
	};
	ERROR geterror(int id)
	{
		if (0 < id && id < ERROR_MAX_ENTRY)
		{
			return errors[id];
		}
		else return errors[0];

	}
	ERROR geterrorin(int id, int line, int col)
	{
		if (0 < id && id < ERROR_MAX_ENTRY)
		{
			errors[id].inext.line = line;
			errors[id].inext.col = col;
			return errors[id];
		}
		else return errors[0];
	}
	ERROR getSemanticError(int id, int line, std::string idName)
	{

		if (0 < id && id < ERROR_MAX_ENTRY)
		{
			errors[id].inext.line = line;
			strcat_s(errors[id].message, idName.c_str());
			return errors[id];
		}
		else return errors[0];
	}
};