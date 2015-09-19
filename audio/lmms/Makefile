# Created by: Jean-Yves Lefort <jylefort@FreeBSD.org>
# $FreeBSD$

PORTNAME=	lmms
PORTVERSION=	1.1.3
DISTVERSIONPREFIX= v
CATEGORIES=	audio

MAINTAINER=	rodrigo@FreeBSD.org
COMMENT=	All-in-one sequencer, drum machine, sampler, and more

LICENSE=	GPLv2

BUILD_DEPENDS=	${LOCALBASE}/include/ladspa.h:${PORTSDIR}/audio/ladspa
LIB_DEPENDS=	libFLAC.so:${PORTSDIR}/audio/flac \
		libfluidsynth.so:${PORTSDIR}/audio/fluidsynth \
		libsamplerate.so:${PORTSDIR}/audio/libsamplerate \
		libsndfile.so:${PORTSDIR}/audio/libsndfile \
		libfftw3.so:${PORTSDIR}/math/fftw3 \
		libfftw3f.so:${PORTSDIR}/math/fftw3-float \
		libfltk.so:${PORTSDIR}/x11-toolkits/fltk

USE_GITHUB=	yes
GH_ACCOUNT=	lmms

USE_LDCONFIG=	yes
USE_XORG=	xft
USE_QT4=	corelib gui xml moc_build uic_build rcc_build \
		qmake_build
USES=		cmake pkgconfig tar:bzip2 desktop-file-utils shared-mime-info \
		compiler:c++0x

CMAKE_ARGS=	-DWANT_VST:BOOL=OFF

OPTIONS_DEFINE=	ALSA CALF CAPS CMT JACK JACKMIDI OGG PORTAUDIO \
		PULSEAUDIO SDL SF2 STK SWH TAP
OPTIONS_DEFAULT= CAPS CMT JACK JACKMIDI OGG PORTAUDIO PULSEAUDIO \
		SDL SF2 STK SWH TAP
OPTIONS_SUB=	yes

ALSA_CMAKE_ON=		-DWANT_ALSA:BOOL=ON
ALSA_CMAKE_OFF=		-DWANT_ALSA:BOOL=OFF
ALSA_LIB_DEPENDS=	libasound.so:${PORTSDIR}/audio/alsa-lib

# calf fails on i386
CALF_DESC=		CALF LADSPA plugins
CALF_CMAKE_ON=		-DWANT_CALF:BOOL=ON
CALF_CMAKE_OFF=		-DWANT_CALF:BOOL=OFF

CAPS_DESC=		C* Audio Plugin suite
CAPS_CMAKE_ON=		-DWANT_CAPS:BOOL=ON
CAPS_CMAKE_OFF=		-DWANT_CAPS:BOOL=OFF
CAPS_RUN_DEPENDS=	${LOCALBASE}/share/ladspa/rdf/caps.rdf:${PORTSDIR}/audio/caps-plugins

CMT_DESC=		Computer Music Toolbox LADSPA plugins
CMT_CMAKE_ON=		-DWANT_CMT:BOOL=ON
CMT_CMAKE_OFF=		-DWANT_CMT:BOOL=OFF
CMT_RUN_DEPENDS=	${LOCALBASE}/lib/ladspa/cmt.so:${PORTSDIR}/audio/cmt

JACK_CMAKE_ON=		-DWANT_JACK:BOOL=ON
JACK_CMAKE_OFF=		-DWANT_JACK:BOOL=OFF
JACK_LIB_DEPENDS=	libjack.so:${PORTSDIR}/audio/jack

JACKMIDI_DESC=		Enable Jack midi input
JACKMIDI_EXTRA_PATCHES=	${FILESDIR}/extra-patch-include_MidiJack.h \
			${FILESDIR}/extra-patch-src_core_Mixer.cpp \
			${FILESDIR}/extra-patch-src_core_midi_MidiJack.cpp \
			${FILESDIR}/extra-patch-src_gui_setup__dialog.cpp
JACKMIDI_IMPLIES=	JACK

OGG_CMAKE_ON=		-DWANT_OGGVORBIS:BOOL=ON
OGG_CMAKE_OFF=		-DWANT_OGGVORBIS:BOOL=OFF
OGG_LIB_DEPENDS=	libvorbis.so:${PORTSDIR}/audio/libvorbis

PORTAUDIO_CMAKE_ON=	-DWANT_PORTAUDIO:BOOL=ON
PORTAUDIO_CMAKE_OFF=	-DWANT_PORTAUDIO:BOOL=OFF
PORTAUDIO_LIB_DEPENDS=	libportaudio.so:${PORTSDIR}/audio/portaudio

PULSEAUDIO_CMAKE_ON=	-DWANT_PULSEAUDIO:BOOL=ON
PULSEAUDIO_CMAKE_OFF=	-DWANT_PULSEAUDIO:BOOL=OFF
PULSEAUDIO_LIB_DEPENDS=	libpulse.so:${PORTSDIR}/audio/pulseaudio

SDL_USE=		SDL=sdl
SDL_CMAKE_ON=		-DWANT_SDL:BOOL=ON
SDL_CMAKE_OFF=		-DWANT_SDL:BOOL=OFF

SF2_DESC=		Soundfont2 player plugin
SF2_CMAKE_ON=		-DWANT_SF2:BOOL=ON
SF2_CMAKE_OFF=		-DWANT_SF2:BOOL=OFF

STK_DESC=		Synthesis Toolkit support
STK_CMAKE_ON=		-DWANT_STK:BOOL=ON
STK_CMAKE_OFF=		-DWANT_STK:BOOL=OFF
STK_LIB_DEPENDS=	libstk.so:${PORTSDIR}/audio/stk

SWH_DESC=		Steve Harris's LADSPA plugins
SWH_CMAKE_ON=		-DWANT_SWH:BOOL=ON
SWH_CMAKE_OFF=		-DWANT_SWH:BOOL=OFF
SWH_RUN_DEPENDS=	${LOCALBASE}/share/ladspa/rdf/swh-plugins.rdf:${PORTSDIR}/audio/swhplugins

TAP_DESC=		Tom's Audio Processing LADSPA plugins
TAP_CMAKE_ON=		-DWANT_TAP:BOOL=ON
TAP_CMAKE_OFF=		-DWANT_TAP:BOOL=OFF
TAP_RUN_DEPENDS=	${LOCALBASE}/share/ladspa/rdf/tap-plugins.rdf:${PORTSDIR}/audio/tap-plugins

.include <bsd.port.options.mk>

.if ${ARCH} == i386 && ${PORT_OPTIONS:MCALF}
BROKEN= Calf plugins fail to build on i386
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
