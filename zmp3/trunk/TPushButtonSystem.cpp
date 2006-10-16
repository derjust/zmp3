#include "TPushButtonSystem.h"

TPushButtonSystem::TPushButtonSystem() : QThread() {
	this->start();
}

void TPushButtonSystem::run() {
	while (true) {
		QThread::usleep(250000); // Viertelsekunde
		//Hier muss noch polling hin
	}
}
