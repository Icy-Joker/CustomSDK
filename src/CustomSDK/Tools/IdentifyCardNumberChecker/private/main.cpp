#include "stdafx.h"

#include "IdentifyCardNumberChecker.h"

#include <QApplication>

int main(int argc,char* argv[])
{
    int result = 0;

    QApplication app(argc,argv);

    IdentifyCardNumberChecker main_window;
    main_window.show();

    result = app.exec();

    return  result;
}