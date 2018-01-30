# Created by: Shane Ambler <FreeBSD@ShaneWare.Biz>
# $FreeBSD$

PORTNAME=	hydrogen
PORTVERSION=	1.0.0
CATEGORIES=	audio
PKGNAMESUFFIX=	-devel

MAINTAINER=	FreeBSD@ShaneWare.Biz
COMMENT=	Advanced drum machine

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/COPYING

BROKEN_powerpc64=	fails to link: libicuuc.so. undefined reference to __cxa_throw_bad_array_new_length

LIB_DEPENDS=	libsndfile.so:audio/libsndfile \
		liblo.so:audio/liblo

CONFLICTS=	hydrogen-0.*

USE_GITHUB=	yes
GH_ACCOUNT=	hydrogen-music
GH_TAGNAME=	f0d0e8cf2498ae

USES=		cmake desktop-file-utils pkgconfig localbase
USE_QT5=	qmake buildtools core gui network widgets xml xmlpatterns

OPTIONS_SINGLE=		EXPORT
OPTIONS_SINGLE_EXPORT=	LIBARCHIVE LIBTAR
OPTIONS_DEFINE=		ALSA DEBUG JACK LADSPA LASH OSS PORTAUDIO \
			PULSEAUDIO RDF RUBBERBAND TEST
OPTIONS_DEFAULT=	JACK LADSPA LIBTAR OSS RDF

EXPORT_DESC=		Export support for drumkit

ALSA_CMAKE_BOOL=	WANT_ALSA
ALSA_LIB_DEPENDS=	libasound.so:audio/alsa-lib
ALSA_RUN_DEPENDS=	alsa-plugins>=0:audio/alsa-plugins

DEBUG_CMAKE_BOOL=	WANT_DEBUG

JACK_CMAKE_BOOL=	WANT_JACK WANT_JACKSESSION
JACK_LIB_DEPENDS=	libjack.so:audio/jack

LADSPA_CMAKE_BOOL=	WANT_LADSPA
LADSPA_CMAKE_ON=	-DLADSPA_LIBRARIES:STRING=${LOCALBASE}/lib/ladspa
LADSPA_BUILD_DEPENDS=	ladspa>=0:audio/ladspa
LADSPA_RUN_DEPENDS=	analyseplugin:audio/ladspa

LASH_CMAKE_BOOL=	WANT_LASH
LASH_LIB_DEPENDS=	liblash.so:audio/lash

LIBARCHIVE_DESC=	LibArchive support
LIBARCHIVE_CMAKE_BOOL=	WANT_LIBARCHIVE
LIBARCHIVE_USES=	libarchive

LIBTAR_DESC=		Libtar support
LIBTAR_CMAKE_BOOL=	WANT_LIBTAR
LIBTAR_CMAKE_ON=	-DCMAKE_REQUIRED_INCLUDES:STRING=${LOCALBASE}/include/
LIBTAR_LIB_DEPENDS=	libtar.so:devel/libtar

OSS_CMAKE_BOOL=		WANT_OSS

PORTAUDIO_CMAKE_BOOL=	WANT_PORTAUDIO
PORTAUDIO_LIB_DEPENDS=	libportaudio.so:audio/portaudio

PULSEAUDIO_CMAKE_BOOL=	WANT_PULSEAUDIO
PULSEAUDIO_LIB_DEPENDS=	libpulse.so:audio/pulseaudio

RDF_DESC=		RDF File support
RDF_CMAKE_BOOL=		WANT_LRDF
RDF_CMAKE_ON=		-DLRDF_INCLUDE_DIR:STRING=${LOCALBASE}/include/raptor2
RDF_LIB_DEPENDS=	liblrdf.so:textproc/liblrdf

# using librubberband is experimental and current versions have bad timing
# installing the rubberband cli tool still works as before
RUBBERBAND_DESC=	librubberband for time stretching
RUBBERBAND_CMAKE_BOOL=	WANT_RUBBERBAND
RUBBERBAND_CMAKE_ON=	-DRUBBERBAND_INCLUDE_DIR:STRING=${LOCALBASE}/include/rubberband
RUBBERBAND_LIB_DEPENDS=	librubberband.so:audio/rubberband

TEST_CMAKE_BOOL=	WANT_CPPUNIT
TEST_BUILD_DEPENDS=	${LOCALBASE}/libdata/pkgconfig/cppunit.pc:devel/cppunit

post-patch:
	@${REINPLACE_CMD} 's|EXISTS(tar|EXISTS(${LOCALBASE}/lib/libtar.so|g' \
		${WRKSRC}/CMakeLists.txt

do-test:
	cd ${WRKSRC} && ./src/tests/tests

.include <bsd.port.mk>
