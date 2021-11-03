#include "stdafx.h"




namespace LeX
{
	Graph graph[] =
	{
		{ LEX_DECLARE, FST::FST(GRAPH_DECLARE) },
		{ LEX_NUM, FST::FST(GRAPH_INT) },
		{ LEX_ID, FST::FST(GRAPH_STRLEN) },
		{ LEX_ID, FST::FST(GRAPH_SUBSTR) },
		{ LEX_ID, FST::FST(GRAPH_STEPEN) },
		{ LEX_CHAR, FST::FST(GRAPH_CHAR) },
		{ LEX_FUNCTION, FST::FST(GRAPH_FUNCTION) },
		{ LEX_RETURN, FST::FST(GRAPH_RETURN) },
		{ LEX_OUT, FST::FST(GRAPH_PRINT) },
		//{ LEX_STANDART, FST::FST(GRAPH_STANDART) },
		{ LEX_MAIN, FST::FST(GRAPH_MAIN) },
		{ LEX_LITERAL, FST::FST(GRAPH_NUM_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_STR_LITERAL) },
		{ LEX_ID, FST::FST(GRAPH_ID) },
		{ LEX_SEPARATOR, FST::FST(GRAPH_SEPARATOR) },
		{ LEX_COMMA, FST::FST(GRAPH_COMMA) },
		{ LEX_LEFTBRACE, FST::FST(GRAPH_LEFT_CURLY_BRACE) },
		{ LEX_BRACELET, FST::FST(GRAPH_RIGHT_CURLY_BRACE) },
		{ LEX_LEFTBRACK, FST::FST(GRAPH_LEFT_SQUARE_BRACK) },
		{ LEX_RIGHTBRACK, FST::FST(GRAPH_RIGHT_SQUARE_BRACK) },
		{ LEX_LEFTHESIS, FST::FST(GRAPH_OPEN_PARENTHESIS) },
		{ LEX_RIGHTTHESIS, FST::FST(GRAPH_CLOSE_PARENTHESIS) },
		{ LEX_PLUS, FST::FST(GRAPH_PLUS) },
		{ LEX_MINUS, FST::FST(GRAPH_MINUS) },
		{ LEX_STAR, FST::FST(GRAPH_ASTERISK) },
		{ LEX_TILDE, FST::FST(GRAPH_TILDE) },
		{ LEX_LOGICAND, FST::FST(GRAPH_AND) },
		{ LEX_LEXCLUSVEOR, FST::FST(GRAPH_OR) },
		{ LEX_DIRSLASH, FST::FST(GRAPH_FORWARD_SLASH) },
		{ LEX_EQUAL, FST::FST(GRAPH_EQUALS)},
	};
	LEX INITLEX(In::IN InStruct, Log::LOG &log)
	{
		LEX Tables;
		Tables.Lextable = LT::Create(InStruct.TokenCount);
		Tables.IDtable = IT::Create(65536);
		bool isDeclare, isParam, isMainFunc, isExecuted, isLiteral;
		isDeclare = isParam = isMainFunc = isExecuted = isLiteral = false;
		IT::IDDATATYPE funcType = IT::NUM;
		char oblv[ID_MAXSIZE] = "Global";
		char fun[ID_MAXSIZE] = "Func";
		int key = 0;

		for (int i = 0; i < InStruct.TokenCount; i++)
		{
			for (int j = 0; j < LENGTH(graph); j++)
			{
				FST::FST fstex(InStruct.tokens[i].token, graph[j].graph);
				if (FST::execute(fstex))
				{
					isExecuted = true;
					switch (graph[j].Lexema)
					{
					case LEX_STRLEN:
					{
						if (IT::IsId(Tables.IDtable, InStruct.tokens[i].token, oblv) == -1)
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_NUM)
							{
								IT::Entry entryit(InStruct.tokens[i].token, i, funcType = IT::NUM, IT::S, oblv);
								IT::Add(Tables.IDtable, entryit);
							}
						}
					}
					case LEX_SUBSTR:
					{
						if (IT::IsId(Tables.IDtable, InStruct.tokens[i].token, oblv) == -1)
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION)
							{
								if (!strcmp(InStruct.tokens[i - 2].token, LEX_TYPE_CHAR))
								{
									IT::Entry entryit(InStruct.tokens[i].token, i, funcType = IT::STR, IT::S, oblv);
									IT::Add(Tables.IDtable, entryit);
								}
								LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1);
								entrylt.tokenId = i;
								LT::Add(Tables.Lextable, entrylt);
								isParam = true;
								break;
							}
						}
					}
					case LEX_ID:
					{
						if (IT::IsId(Tables.IDtable, InStruct.tokens[i].token, oblv) == -1)
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION)
							{
								if (!strcmp(InStruct.tokens[i - 2].token, LEX_TYPE_INT))
								{
									IT::Entry entryit(InStruct.tokens[i].token, i, funcType = IT::NUM, IT::F, oblv);
									IT::Add(Tables.IDtable, entryit);
								}
								else
									if (!strcmp(InStruct.tokens[i - 2].token, LEX_TYPE_CHAR))
									{
										IT::Entry entryit(InStruct.tokens[i].token, i, funcType = IT::STR, IT::F, oblv);
										IT::Add(Tables.IDtable, entryit);
									}
								LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1);
								entrylt.tokenId = i;
								LT::Add(Tables.Lextable, entrylt);
								isParam = true;
								break;
							}
							else
							{
								LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token, oblv));
								entrylt.tokenId = i;
								LT::Add(Tables.Lextable, entrylt);
								break;
							}
						}
					case LEX_LITERAL:
					{for (int k = 0; k < Tables.IDtable.size; k++)
					{
						if (!strcmp(InStruct.tokens[i].token, Tables.IDtable.table[k].id) && ((Tables.IDtable.table[k].idtype == 2) || (Tables.IDtable.table[k].idtype == 1) || (Tables.IDtable.table[k].idtype == 3)))
						{
							LT::Entry entrylt(LEX_ID, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
							LT::Add(Tables.Lextable, entrylt);
							isLiteral = false;
							break;
						}
						else
						{
							isLiteral = true;

						}
					}
					break;
					}
					case LEX_LEFTBRACE:
					{
						if (!strcmp(InStruct.tokens[i - 2].token, "("))
						{
							key++;
						}
						//strncpy_s(oblv, ID_MAXSIZE, "non global", ID_MAXSIZE - 1);
						if (Tables.Lextable.table[i - 1].lexema == LEX_MAIN)
							strncpy_s(oblv, ID_MAXSIZE, "Main", ID_MAXSIZE - 1);
						else
						{
							std::stringstream view;
							view << fun << key;
							string paramv = view.str();
							strncpy_s(oblv, ID_MAXSIZE, paramv.c_str(), ID_MAXSIZE - 1);
						}
						LT::Entry entrylt(LEX_LEFTBRACE, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_BRACELET:
					{

						strncpy_s(oblv, ID_MAXSIZE, "Global", ID_MAXSIZE - 1);
						LT::Entry entrylt(LEX_BRACELET, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}


					case LEX_PLUS:
					{
						LT::Entry entrylt(LEX_PLUS, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_MINUS:
					{
						LT::Entry entrylt(LEX_STAR, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_STAR:
					{
						LT::Entry entrylt(LEX_STAR, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_DIRSLASH:
					{
						LT::Entry entrylt(LEX_DIRSLASH, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_LOGICAND:
					{
						LT::Entry entrylt(LEX_LOGICAND, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_LEXCLUSVEOR:
					{
						LT::Entry entrylt(LEX_LEXCLUSVEOR, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_TILDE:
					{
						LT::Entry entrylt(LEX_TILDE, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_SEPARATOR:
					{
						InStruct.tokens[i].isLiteral = false;
						LT::Entry entrylt(InStruct.tokens[i].token[0], InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_MAIN:
					{
						isMainFunc = true;
						funcType = IT::NUM;
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_DECLARE:
					{
						isDeclare = true;
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_OUT:
					{
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					default:
					{
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					}
					break;
					}
				}
				if (!isExecuted || isLiteral)
				{
					if (InStruct.tokens[i].isLiteral || isLiteral)
					{
						switch (Tables.Lextable.table[i - 1].lexema)
						{
						case LEX_EQUAL:
						{
							if (Tables.Lextable.table[i - 2].lexema == LEX_ID)

							{
								InStruct.tokens[i].isLiteral = true;
								LT::Entry entrylt(LEX_LITERAL, InStruct.tokens[i].line, Tables.IDtable.size);
								LT::Add(Tables.Lextable, entrylt);
								if (IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token, oblv) != -1)
									if ((Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token, oblv)].idtype == IT::V ||
										Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token, oblv)].idtype == IT::P))
										if (Tables.Lextable.table[i - 4].lexema == LEX_DECLARE)
										{
											IT::SetValue(Tables.IDtable, IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token, oblv), InStruct.tokens[i].token);
										}
								break;
							}
						}
						case LEX_OUT:
						{
							LT::Entry entrylt(LEX_LITERAL, InStruct.tokens[i].line, Tables.IDtable.size - 1);
							entrylt.tokenId = i;
							LT::Add(Tables.Lextable, entrylt);
							break;
						}
						case LEX_RETURN:
						{
							LT::Entry entrylt(LEX_LITERAL, InStruct.tokens[i].line, Tables.IDtable.size - 1);
							entrylt.tokenId = i;
							LT::Add(Tables.Lextable, entrylt);
							break;
						}
						default:
							LT::Entry entrylt(LEX_ID, InStruct.tokens[i].line, Tables.IDtable.size);
							entrylt.tokenId = i;
							LT::Add(Tables.Lextable, entrylt);
							break;
						}
					}
					else
						throw ERROR_THROW_IN(124, Tables.Lextable.table[i - 2].sn, NULL);
				}
				isExecuted = false;
				isLiteral = false;
			}
			return Tables;
		}
	}
}
