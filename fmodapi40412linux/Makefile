VERSION = 4.04.12
LIBDIR     = api/lib
HDRDIR     = api/inc
DESTLIBDIR = /usr/local/lib
DESTHDRDIR = /usr/local/include/fmodex

all:
	@echo "Possible targets:"
	@echo "'make fmod_examples'  - Build all examples"
	@echo "'make install'        - Install FMOD Ex libraries and headers"
	@echo "'make uninstall'      - Uninstall FMOD Ex libraries and headers"

fmod_examples:
	cd examples/3d && make
	cd examples/cdplayer && make
	cd examples/channelgroups && make
	cd examples/dsp_effectperspeaker && make
	cd examples/realtimestitching && make
	cd examples/submixing && make
	cd examples/useplugins && make
	cd examples/generatetone && make
	cd examples/loadfrommemory && make
	cd examples/playsound && make
	cd examples/playlist && make
	cd examples/plugin_dev/codec_raw && make
	cd examples/plugin_dev/dsp_gain && make
	cd examples/ripnetstream && make
	cd examples/netstream && make
	cd examples/recording && make
	cd examples/usercreatedsound && make
	cd examples/playstream && make
	cd examples/pitchdetection && make
	cd examples/multispeakeroutput && make
	cd examples/multiplesoundcard && make
	cd examples/effects && make
	cd examples/readtags && make
	
install:
	@echo "Installing FMOD Ex libraries and headers..."
	cp -f ${LIBDIR}/libfmodex.so.${VERSION} ${DESTLIBDIR}
	cp -f ${LIBDIR}/libfmodexp.so.${VERSION} ${DESTLIBDIR}
	ln -s ${DESTLIBDIR}/libfmodex.so.${VERSION} ${DESTLIBDIR}/libfmodex.so
	ln -s ${DESTLIBDIR}/libfmodexp.so.${VERSION} ${DESTLIBDIR}/libfmodexp.so
	ldconfig -n ${DESTLIBDIR}
	mkdir -p ${DESTHDRDIR}
	cp -f ${HDRDIR}/*.h* ${DESTHDRDIR}
	@echo "done."

uninstall:
	@echo "Uninstalling FMOD Ex libraries..."
	/bin/rm -f ${DESTLIBDIR}/libfmodex.so ${DESTLIBDIR}/libfmodex.so.${VERSION}
	/bin/rm -f ${DESTLIBDIR}/libfmodexp.so ${DESTLIBDIR}/libfmodexp.so.${VERSION}
	ldconfig -n ${DESTLIBDIR}
	/bin/rm -rf ${DESTHDRDIR}
	@echo "done."
