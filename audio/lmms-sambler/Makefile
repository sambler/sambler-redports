# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	lmms-sambler
PORTVERSION=	1.2.0
DISTVERSIONPREFIX= v
DISTVERSIONSUFFIX= -rc5
CATEGORIES=	audio
MASTER_SITES=	GH

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	LMMS with my patches

LICENSE=	GPLv2

BUILD_DEPENDS=	${LOCALBASE}/include/ladspa.h:audio/ladspa \
		${LOCALBASE}/lib/carla/libcarla_standalone2.so:audio/carla \
		kf5-extra-cmake-modules>0:devel/kf5-extra-cmake-modules
LIB_DEPENDS=	libFLAC.so:audio/flac \
		libfluidsynth.so:audio/fluidsynth \
		libfontconfig.so:x11-fonts/fontconfig \
		libjack.so:audio/jack \
		libmp3lame.so:audio/lame \
		libgig.so:audio/libgig \
		libogg.so:audio/libogg \
		libportaudio.so:audio/portaudio \
		libpulse.so:audio/pulseaudio \
		libsamplerate.so:audio/libsamplerate \
		libsndfile.so:audio/libsndfile \
		libstk.so:audio/stk \
		libvorbis.so:audio/libvorbis \
		libfftw3.so:math/fftw3 \
		libfftw3f.so:math/fftw3-float \
		libfltk.so:x11-toolkits/fltk
RUN_DEPENDS=	${LOCALBASE}/share/ladspa/rdf/caps.rdf:audio/caps-plugins \
		${LOCALBASE}/lib/carla/libcarla_standalone2.so:audio/carla \
		${LOCALBASE}/lib/ladspa/cmt.so:audio/cmt \
		${LOCALBASE}/share/ladspa/rdf/swh-plugins.rdf:audio/swhplugins \
		${LOCALBASE}/share/ladspa/rdf/tap-plugins.rdf:audio/tap-plugins

CONFLICTS_INSTALL=	lmms-[01].*

USES=		cmake pkgconfig desktop-file-utils shared-mime-info \
		compiler:c++0x qt:5
USE_LDCONFIG=	yes
USE_XORG=	xcb xcursor xext xfixes xft xinerama xrender
USE_SDL=	sdl
USE_QT=		buildtools core gui linguisttools xml qmake widgets x11extras

USE_GITHUB=	yes
GH_ACCOUNT=	lmms \
		Lukas-W:qt5embed \
		rampantpixels:rpmal
GH_PROJECT=	lmms \
		qt5-x11embed:qt5embed \
		rpmalloc:rpmal
GH_TAGNAME=	022b39a1d496:qt5embed \
		2e0479192b8d:rpmal

CMAKE_ON=	WANT_CALF WANT_CAPS WANT_CARLA WANT_CMT WANT_GIG \
		WANT_JACK WANT_MP3LAME WANT_OGGVORBIS \
		WANT_PULSEAUDIO WANT_PORTAUDIO WANT_QT5 WANT_SDL \
		WANT_SF2 WANT_STK WANT_SWH WANT_TAP 
CMAKE_OFF=	WANT_ALSA WANT_SOUNDIO  WANT_VST WANT_VST_NOWINE WANT_WEAKJACK WANT_WINMM

DATADIR=	${LOCALBASE}/share/lmms

post-extract:
# qt5-x11embed
	@${MV} ${WRKSRC_qt5embed}/* ${WRKSRC}/src/3rdparty/qt5-x11embed
# rpmalloc
	@${MV} ${WRKSRC_rpmal}/* ${WRKSRC}/src/3rdparty/rpmalloc/rpmalloc

post-patch:
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
