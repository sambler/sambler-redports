# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	lmms-sambler
PORTVERSION=	1.0.93
CATEGORIES=	audio
MASTER_SITES=	GH

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	LMMS with my patches.

LICENSE=	GPLv2
CONFLICTS=	lmms-[01].* lmms-sambler-[01].*

BUILD_DEPENDS=	${LOCALBASE}/include/ladspa.h:${PORTSDIR}/audio/ladspa
LIB_DEPENDS=	libFLAC.so:${PORTSDIR}/audio/flac \
		libfluidsynth.so:${PORTSDIR}/audio/fluidsynth \
		libsamplerate.so:${PORTSDIR}/audio/libsamplerate \
		libsndfile.so:${PORTSDIR}/audio/libsndfile \
		libvorbis.so:${PORTSDIR}/audio/libvorbis \
		libfftw3.so:${PORTSDIR}/math/fftw3 \
		libfftw3f.so:${PORTSDIR}/math/fftw3-float \
		libjack.so:${PORTSDIR}/audio/jack \
		libportaudio.so.2:${PORTSDIR}/audio/portaudio2 \
		libpulse.so:${PORTSDIR}/audio/pulseaudio
RUN_DEPENDS=	${LOCALBASE}/share/ladspa/rdf/caps.rdf:${PORTSDIR}/audio/caps-plugins \
		${LOCALBASE}/lib/ladspa/cmt.so:${PORTSDIR}/audio/cmt \
		${LOCALBASE}/share/ladspa/rdf/swh-plugins.rdf:${PORTSDIR}/audio/swhplugins \
		${LOCALBASE}/share/ladspa/rdf/tap-plugins.rdf:${PORTSDIR}/audio/tap-plugins \
		update-mime-database:${PORTSDIR}/misc/shared-mime-info

USE_GITHUB=	yes
GH_ACCOUNT=	lmms
GH_PROJECT=	lmms
GH_TAGNAME=	v1.0.93
GH_COMMIT=	1b4b34d

USE_LDCONFIG=	yes
USE_XORG=	xft
USE_SDL=	sdl
USE_QT4=	corelib gui xml moc_build uic_build rcc_build qmake_build
USES=		cmake pkgconfig tar:bzip2 desktop-file-utils shared-mime-info dos2unix
DOS2UNIX_FILES=	plugins/midi_import/portsmf/allegrowr.cpp plugins/midi_import/portsmf/mfmidi.cpp
CMAKE_ARGS=	-DWANT_ALSA:BOOL=OFF \
		-DWANT_CALF:BOOL=ON \
		-DWANT_CAPS:BOOL=ON \
		-DWANT_CMT:BOOL=ON \
		-DWANT_SWH:BOOL=ON \
		-DWANT_SF2:BOOL=ON \
		-DWANT_STK:BOOL=OFF \
		-DWANT_SWH:BOOL=ON \
		-DWANT_TAP:BOOL=ON \
		-DWANT_VST:BOOL=OFF \
		-DWANT_JACK:BOOL=ON \
		-DWANT_PORTAUDIO:BOOL=ON \
		-DWANT_PULSEAUDIO:BOOL=ON \
		-DWANT_SDL:BOOL=ON
LDFLAGS=	-L${LOCALBASE}/lib/portaudio2

WRKSRC=		${WRKDIR}/LMMS-lmms-${GH_COMMIT}
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
