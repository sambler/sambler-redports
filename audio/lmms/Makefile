# Created by: Jean-Yves Lefort <jylefort@FreeBSD.org>
# $FreeBSD$

PORTNAME=	lmms
PORTVERSION=	1.1.3
CATEGORIES=	audio
MASTER_SITES=	GH

MAINTAINER=	rodrigo@FreeBSD.org
COMMENT=	All-in-one sequencer, drum machine, sampler, and more

LICENSE=	GPLv2

BUILD_DEPENDS=	${LOCALBASE}/include/ladspa.h:${PORTSDIR}/audio/ladspa
LIB_DEPENDS=	libFLAC.so:${PORTSDIR}/audio/flac \
		libfluidsynth.so:${PORTSDIR}/audio/fluidsynth \
		libsamplerate.so:${PORTSDIR}/audio/libsamplerate \
		libsndfile.so:${PORTSDIR}/audio/libsndfile \
		libvorbis.so:${PORTSDIR}/audio/libvorbis \
		libfftw3.so:${PORTSDIR}/math/fftw3 \
		libfftw3f.so:${PORTSDIR}/math/fftw3-float \
		libfltk.so:${PORTSDIR}/x11-toolkits/fltk
RUN_DEPENDS=	${LOCALBASE}/share/ladspa/rdf/caps.rdf:${PORTSDIR}/audio/caps-plugins \
		${LOCALBASE}/lib/ladspa/cmt.so:${PORTSDIR}/audio/cmt \
		${LOCALBASE}/share/ladspa/rdf/swh-plugins.rdf:${PORTSDIR}/audio/swhplugins \
		${LOCALBASE}/share/ladspa/rdf/tap-plugins.rdf:${PORTSDIR}/audio/tap-plugins

USE_GITHUB=	yes
GH_ACCOUNT=	lmms
GH_PROJECT=	lmms
GH_TAGNAME=	v${PORTVERSION}

USE_LDCONFIG=	yes
USE_XORG=	xft
USE_QT4=	corelib gui xml moc_build uic_build rcc_build \
		qmake_build
USES=		cmake pkgconfig tar:bzip2 desktop-file-utils shared-mime-info \
		compiler:c++0x

CMAKE_ARGS=	-DWANT_ALSA:BOOL=OFF \
		-DWANT_CAPS:BOOL=ON \
		-DWANT_CMT:BOOL=ON \
		-DWANT_SF2:BOOL=ON \
		-DWANT_STK:BOOL=OFF \
		-DWANT_SWH:BOOL=ON \
		-DWANT_TAP:BOOL=ON \
		-DWANT_VST:BOOL=OFF

OPTIONS_DEFINE=	JACK PORTAUDIO PULSEAUDIO SDL

JACK_LIB_DEPENDS=	libjack.so:${PORTSDIR}/audio/jack
JACK_CMAKE_ON=		-DWANT_JACK:BOOL=ON
JACK_CMAKE_OFF=		-DWANT_JACK:BOOL=OFF

PORTAUDIO_LIB_DEPENDS=	libportaudio.so:${PORTSDIR}/audio/portaudio
PORTAUDIO_CMAKE_ON=	-DWANT_PORTAUDIO:BOOL=ON
PORTAUDIO_CMAKE_OFF=	-DWANT_PORTAUDIO:BOOL=OFF

PULSEAUDIO_LIB_DEPENDS=	libpulse.so:${PORTSDIR}/audio/pulseaudio
PULSEAUDIO_CMAKE_ON=	-DWANT_PULSEAUDIO:BOOL=ON
PULSEAUDIO_CMAKE_OFF=	-DWANT_PULSEAUDIO:BOOL=OFF

SDL_USE=		SDL=sdl
SDL_CMAKE_ON=		-DWANT_SDL:BOOL=ON
SDL_CMAKE_OFF=		-DWANT_SDL:BOOL=OFF

.include <bsd.port.options.mk>

.if ${ARCH} == amd64
# calf fails on x86, other working arches may be added to this
CMAKE_ARGS+=	-DWANT_CALF:BOOL=ON
PLIST_SUB+=	CALF=""
.else
CMAKE_ARGS+=	-DWANT_CALF:BOOL=OFF
PLIST_SUB+=	CALF="@comment "
.endif

post-patch:
.for file in data/lmms.desktop
	@${REINPLACE_CMD} -e \
		'/^Icon/s|=.*$$|=lmms|g ; \
		 /^Exec/s|=.*$$|=lmms|g ; \
		 /^Categories/s|$$|;|g ; \
		 /^MimeType/s|$$|;|g' ${WRKSRC}/${file}
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
	# make it setuid-root to be able to set realtime priority
	# (root privileges are dropped in the main routine)
	${CHMOD} u+s ${STAGEDIR}${PREFIX}/bin/lmms

.include <bsd.port.mk>
