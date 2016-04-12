# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	lmms-sambler
PORTVERSION=	1.0.93
CATEGORIES=	audio
MASTER_SITES=	GH

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	LMMS with my patches.

LICENSE=	GPLv2
CONFLICTS=	lmms-[01].*

BUILD_DEPENDS=	${LOCALBASE}/include/ladspa.h:audio/ladspa
LIB_DEPENDS=	libFLAC.so:audio/flac \
		libfluidsynth.so:audio/fluidsynth \
		libjack.so:audio/jack \
		libsamplerate.so:audio/libsamplerate \
		libsndfile.so:audio/libsndfile \
		libvorbis.so:audio/libvorbis \
		libportaudio.so:audio/portaudio \
		libpulse.so:audio/pulseaudio \
		libstk.so:audio/stk \
		libfftw3.so:math/fftw3 \
		libfftw3f.so:math/fftw3-float \
		libfltk.so:x11-toolkits/fltk
RUN_DEPENDS=	${LOCALBASE}/share/ladspa/rdf/caps.rdf:audio/caps-plugins \
		${LOCALBASE}/lib/ladspa/cmt.so:audio/cmt \
		${LOCALBASE}/share/ladspa/rdf/swh-plugins.rdf:audio/swhplugins \
		${LOCALBASE}/share/ladspa/rdf/tap-plugins.rdf:audio/tap-plugins

USE_GITHUB=	yes
GH_ACCOUNT=	lmms
GH_PROJECT=	lmms
GH_TAGNAME=	v1.0.93

USE_LDCONFIG=	yes
USE_XORG=	xft
USE_SDL=	sdl
USE_QT4=	corelib gui xml moc_build uic_build rcc_build qmake_build
USES=		cmake pkgconfig tar:bzip2 desktop-file-utils shared-mime-info \
		dos2unix compiler:c++0x
DOS2UNIX_FILES=	plugins/midi_import/portsmf/allegrowr.cpp plugins/midi_import/portsmf/mfmidi.cpp
# calf only compiles under some configurations
# disable until we can get consistancy 
CMAKE_ARGS=	-DWANT_ALSA:BOOL=OFF \
		-DWANT_CALF:BOOL=OFF \
		-DWANT_CAPS:BOOL=ON \
		-DWANT_CMT:BOOL=ON \
		-DWANT_SF2:BOOL=ON \
		-DWANT_STK:BOOL=ON \
		-DWANT_SWH:BOOL=ON \
		-DWANT_TAP:BOOL=ON \
		-DWANT_VST:BOOL=OFF \
		-DWANT_JACK:BOOL=ON \
		-DWANT_PORTAUDIO:BOOL=ON \
		-DWANT_PULSEAUDIO:BOOL=ON \
		-DWANT_SDL:BOOL=ON

DATADIR=	${LOCALBASE}/share/lmms

post-patch:
.for file in data/lmms.desktop
	@${REINPLACE_CMD} -e \
		'/^Icon/s|=.*$$|=lmms|g ; \
		 /^Exec/s|=.*$$|=lmms|g' ${WRKSRC}/${file}
.endfor
.for filename in data/lmms src/core/config_mgr.cpp
	@${REINPLACE_CMD} -e \
		's|/usr|${PREFIX}|g' ${WRKSRC}/${filename}
.endfor
.for filename in src/core/ladspa_manager.cpp
	@${REINPLACE_CMD} -e \
		'/\/usr\/lib/d ; \
		 s|/usr/local|${PREFIX}|g' ${WRKSRC}/${filename}
.endfor

post-install:
	@${LN} -sf ${DATADIR}/themes/default/icon.png \
		${STAGEDIR}${PREFIX}/share/pixmaps/lmms.png
	@-update-mime-database ${STAGEDIR}${PREFIX}/share/mime
	# make it setuid-root to be able to set realtime priority
	# (root privileges are dropped in the main routine)
	#${CHMOD} u+s ${STAGEDIR}${PREFIX}/bin/lmms

.include <bsd.port.mk>
