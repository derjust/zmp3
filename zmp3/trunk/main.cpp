#include <QApplication>
#include "TLogic.h"

int main(int argc, char* argv[]) {
	QApplication zmp3( argc, argv );
	TLogic* myLogic = new TLogic();
	return zmp3.exec();
}

