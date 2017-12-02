# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	lmms-sambler
PORTVERSION=	1.2.0
DISTVERSIONPREFIX= v
DISTVERSIONSUFFIX= -rc4
CATEGORIES=	audio
MASTER_SITES=	GH

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	LMMS with my patches

LICENSE=	GPLv2

BUILD_DEPENDS=	${LOCALBASE}/include/ladspa.h:audio/ladspa
LIB_DEPENDS=	libFLAC.so:audio/flac \
		libfluidsynth.so:audio/fluidsynth \
		libfontconfig.so:x11-fonts/fontconfig \
		libjack.so:audio/jack \
		libmp3lame.so:audio/lame \
		libogg.so:audio/libogg \
		libsamplerate.so:audio/libsamplerate \
		libsndfile.so:audio/libsndfile \
		libvorbis.so:audio/libvorbis \
		libportaudio.so:audio/portaudio \
		libpulse.so:audio/pulseaudio \
		libstk.so:audio/stk \
		libfftw3.so:math/fftw3 \
		libfftw3f.so:math/fftw3-float \
		libfltk.so:x11-toolkits/fltk
# 		libgig.so:audio/libgig \
RUN_DEPENDS=	${LOCALBASE}/share/ladspa/rdf/caps.rdf:audio/caps-plugins \
		${LOCALBASE}/lib/ladspa/cmt.so:audio/cmt \
		${LOCALBASE}/share/ladspa/rdf/swh-plugins.rdf:audio/swhplugins \
		${LOCALBASE}/share/ladspa/rdf/tap-plugins.rdf:audio/tap-plugins

CONFLICTS=	lmms-[01].*

USES=		cmake pkgconfig desktop-file-utils shared-mime-info \
		compiler:c++0x
USE_LDCONFIG=	yes
USE_XORG=	xcursor xext xfixes xft xinerama
USE_SDL=	sdl
USE_QT5=	buildtools core gui linguisttools xml qmake widgets

USE_GITHUB=	yes
GH_ACCOUNT=	lmms
GH_PROJECT=	lmms

# calf only compiles under some configurations
# disable until we can get consistancy
CMAKE_ARGS=	-DWANT_ALSA:BOOL=OFF \
		-DWANT_CALF:BOOL=OFF \
		-DWANT_CAPS:BOOL=ON \
		-DWANT_CARLA:BOOL=OFF \
		-DWANT_CMT:BOOL=ON \
		-DWANT_JACK:BOOL=ON \
		-DWANT_MP3LAME:BOOL=ON \
		-DWANT_OGGVORBIS:BOOL=ON \
		-DWANT_PULSEAUDIO:BOOL=ON \
		-DWANT_PORTAUDIO:BOOL=ON \
		-DWANT_SOUNDIO:BOOL=OFF \
		-DWANT_SDL:BOOL=ON \
		-DWANT_SF2:BOOL=ON \
		-DWANT_GIG:BOOL=OFF \
		-DWANT_STK:BOOL=ON \
		-DWANT_SWH:BOOL=ON \
		-DWANT_TAP:BOOL=ON \
		-DWANT_VST:BOOL=OFF \
		-DWANT_VST_NOWINE:BOOL=OFF \
		-DWANT_WINMM:BOOL=OFF \
		-DWANT_QT5:BOOL=ON
# https://github.com/falkTX/Carla

DATADIR=	${LOCALBASE}/share/lmms

post-patch:
#	@${REINPLACE_CMD} -e \
#		'/^Icon/s|=.*$$|=lmms|g ; \
#		 /^Exec/s|=.*$$|=lmms|g' ${WRKSRC}/cmake/linux/lmms.desktop
	@${REINPLACE_CMD} -e \
		's|/usr|${PREFIX}|g' ${WRKSRC}/src/core/ConfigManager.cpp
	@${REINPLACE_CMD} -e \
		'/\/usr\/lib/d ; \
		 s|/usr/local|${PREFIX}|g' ${WRKSRC}/src/core/LadspaManager.cpp

post-install:
	@${LN} -sf ${DATADIR}/themes/default/icon.png \
		${STAGEDIR}${PREFIX}/share/pixmaps/lmms.png
	@-update-mime-database ${STAGEDIR}${PREFIX}/share/mime
	# make it setuid-root to be able to set realtime priority
	# (root privileges are dropped in the main routine)
	#${CHMOD} u+s ${STAGEDIR}${PREFIX}/bin/lmms
	# move a common name dir to port named dir
	@${MV} ${STAGEDIR}${PREFIX}/share/mime ${STAGEDIR}${DATADIR}/mime

.include <bsd.port.mk>
