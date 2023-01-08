#include <iostream>
#include "Report.h"

// 检查内存泄漏
#define CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#ifdef _DEBUG
#define new   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

inline void EnableMemLeakCheck()
{
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}

// 成绩单：节选自《设计模式之禅》

int main()
{
    //_CrtSetBreakAlloc(152);
    //_CrtSetBreakAlloc(153);

    EnableMemLeakCheck();

    SchoolReport* sr = new FourthGradeReport;

    sr = new HighScoreDecorator(sr);
    sr = new SortDecorator(sr);

    sr->report();

    delete sr;


    //_CrtDumpMemoryLeaks();
    return 0;
}