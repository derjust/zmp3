#include <QThread>

class TPushButtonSystem : QThread {
Q_OBJECT
   private:
	void run();

   signals:
	void moveDown();
	void moveUp();
	void moveLeft();
	void moveRight();

   public:
	TPushButtonSystem();

   public slots:

};
