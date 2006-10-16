#include <QString>
#include <QFileInfo>
#include <id3/tag.h>
#include <id3/misc_support.h>

class TSong {
   private:
	QString fileName;
	QString title;
	QString artist;
   public:
	TSong(QString fileName);
	QString getFileName();
	QString getTitle();
	QString getArtist();
};

