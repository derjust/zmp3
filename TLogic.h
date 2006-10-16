#include <QObject>
#include <QDir>
#include <QStringList>

#include "TLCDController.h"
#include "TPushButtonSystem.h"
#include "TSoundSystem.h"


class TLogic : QObject {
Q_OBJECT
   private:
	TLCDController* myLCDController;
	TPushButtonSystem* myPushButtonSystem;
	TSoundSystem* mySoundSystem;

	QList<TSong> allSongs;

   public:
	TLogic();

   public slots:

};
