#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/cdrom.h>
#include <signal.h>

#ifndef listen_h
  #define listen_h listen_h
    #include "listen.h"
#endif

using namespace std;

void *AktionenSammeln( void *ptr);
