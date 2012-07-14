# New ports collection makefile for:    blender-sambler
# Date created:         2 April 2012
# Whom:                 Shane Ambler
#
# $FreeBSD$

PORTNAME=	blender-sambler
PORTVERSION=	2.63
PORTREVISION=	7
CATEGORIES=	graphics multimedia
MASTER_SITES=	https://github.com/sambler/myblender/tarball/:base \
				https://github.com/sambler/myblendertranslations/tarball/:trans \
				https://github.com/sambler/myblenderaddons/tarball/:addons \
				https://github.com/sambler/myblendercontrib/tarball/:contrib
DISTFILES=	sambler-${PORTVERSION}.${PORTREVISION}:base \
			translate-${PORTVERSION}.${PORTREVISION}:trans \
			addons-${PORTVERSION}.${PORTREVISION}:addons \
			contrib-${PORTVERSION}.${PORTREVISION}:contrib
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	3D modeling/rendering/animation/gaming package

LICENSE=	GPLv2

LIB_DEPENDS=	jpeg:${PORTSDIR}/graphics/jpeg
LIB_DEPENDS+=	png15:${PORTSDIR}/graphics/png
LIB_DEPENDS+=	freetype:${PORTSDIR}/print/freetype2
LIB_DEPENDS+=	avutil:${PORTSDIR}/multimedia/ffmpeg
LIB_DEPENDS+=	fftw3:${PORTSDIR}/math/fftw3
LIB_DEPENDS+=	IlmImf:${PORTSDIR}/graphics/OpenEXR
LIB_DEPENDS+=	openjpeg:${PORTSDIR}/graphics/openjpeg
LIB_DEPENDS+=	samplerate:${PORTSDIR}/audio/libsamplerate
LIB_DEPENDS+=	sndfile:${PORTSDIR}/audio/libsndfile
LIB_DEPENDS+=	tiff:${PORTSDIR}/graphics/tiff
LIB_DEPENDS+=	boost_thread:${PORTSDIR}/devel/boost-libs
RUN_DEPENDS=	xdg-mime:${PORTSDIR}/devel/xdg-utils

FETCH_ARGS=	-pRr
CONFLICTS=	blender-2.*

USE_CMAKE=	yes
CMAKE_OUTSOURCE=	yes
MAKE_JOBS_SAFE=	yes
WRKSRC=		${WRKDIR}/sambler-myblender-8612519

USE_PYTHON=	3.2
WANT_GNOME=	yes
USE_GNOME=	desktopfileutils
USE_OPENAL=	al alut
USE_SDL=	sdl
USE_XORG=	x11 xext xmu
USE_GL=		glew

CMAKE_ARGS+=	-DWITH_BUILDINFO:BOOL=ON -DWITH_AUDASPACE:BOOL=ON
CMAKE_ARGS+=	-DWITH_BLENDER:BOOL=ON 
CMAKE_ARGS+=	-DWITH_BULLET:BOOL=ON -DWITH_CARVE:BOOL=ON
CMAKE_ARGS+=	-DWITH_CODEC_FFMPEG:BOOL=ON -DWITH_CODEC_SNDFILE:BOOL=ON
CMAKE_ARGS+=	-DWITH_FFTW3:BOOL=ON -DWITH_GAMEENGINE:BOOL=ON
CMAKE_ARGS+=	-DWITH_IK_ITASC:BOOL=ON -DWITH_IMAGE_CINEON:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_DDS:BOOL=ON -DWITH_IMAGE_FRAMESERVER:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_HDR:BOOL=ON -DWITH_IMAGE_OPENEXR:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_OPENJPEG:BOOL=ON -DWITH_IMAGE_REDCODE:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_TIFF:BOOL=ON -DWITH_INSTALL_PORTABLE:BOOL=ON
CMAKE_ARGS+=	-DWITH_JACK:BOOL=ON -DWITH_LIBMV:BOOL=ON
CMAKE_ARGS+=	-DWITH_LZMA:BOOL=ON -DWITH_LZO:BOOL=ON
CMAKE_ARGS+=	-DWITH_MEM_JEMALLOC:BOOL=OFF -DWITH_MOD_BOOLEAN:BOOL=ON
# temporarily broken while upgrading
CMAKE_ARGS+=	-DWITH_MOD_CLOTH_ELTOPO:BOOL=OFF
CMAKE_ARGS+=	-DWITH_MOD_DECIMATE:BOOL=ON -DWITH_MOD_FLUID:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_OCEANSIM:BOOL=ON -DWITH_MOD_REMESH:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_SMOKE:BOOL=ON -DWITH_OPENAL:BOOL=ON
CMAKE_ARGS+=	-DWITH_PYTHON:BOOL=ON -DWITH_PYTHON_INSTALL:BOOL=OFF
CMAKE_ARGS+=	-DWITH_PYTHON_MODULE:BOOL=OFF -DWITH_PYTHON_SAFETY:BOOL=OFF
CMAKE_ARGS+=	-DWITH_RAYOPTIMIZATION:BOOL=ON -DWITH_SDL:BOOL=ON
CMAKE_ARGS+=	-DWITH_SYSTEM_GLEW:BOOL=ON -DWITH_SYSTEM_OPENJPEG:BOOL=ON
CMAKE_ARGS+=	-DWITH_X11_XF86VMODE:BOOL=ON -DWITH_X11_XINPUT:BOOL=ON

SUB_FILES=	blender blenderplayer
MAN1=		blender.1

OUTDIR=		${INSTALL_WRKSRC}/bin/${PORTVERSION}

LANG=		ar bg ca cs de el es es_ES fa fi fr hr id it ja ky ne pl pt \
		ru sr sr@latin sv tr uk zh_CN zh_TW

OPTIONS_DEFINE=	HEADLESS SECURITY PLAYER JACK NLS
## COLLADA NDOF
OPTIONS_SINGLE=	COMPILER
OPTIONS_SINGLE_COMPILER=	CC_GCC46 CC_CLANG
OPTIONS_DEFAULT=	CC_GCC46 SECURITY NLS

CC_GCC46_DESC=	"Build with gcc46"
CC_CLANG_DESC=	"Build with clang"
HEADLESS_DESC=	"Disable user interface"
SECURITY_DESC=	"Disable scripts auto-run"
PLAYER_DESC=	"Build blender player"
JACK_DESC=	"Audio support using JackAudio"
#COLLADA_DESC=	"Include collada import"
#NDOF_DESC=	"NDOF Support"
NLS_DESC=	"Include translations"

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MCC_CLANG}
CC=clang
CXX=clang++
CPP=clang-cpp
CMAKE_ARGS+=	-DWITH_OPENMP:BOOL=OFF

.if ${OSVERSION} < 900033
BUILD_DEPENDS+=	clang:${PORTSDIR}/lang/clang
.endif

.if ${ARCH} == "i386" || ${OSVERSION} < 803000
# this is needed for linking with openimageio
LDFLAGS+=	-L${LOCALBASE}/lib/gcc46 -rpath ${LOCALBASE}/lib/gcc46
.endif

.endif # CC_CLANG

.if ${PORT_OPTIONS:MCC_GCC46}
CMAKE_ARGS+=	-DWITH_OPENMP:BOOL=ON
USE_GCC?=		4.6+
LDFLAGS+=	-rpath ${LOCALBASE}/lib/gcc46
.endif

.if ${OSVERSION} >= 800000
CMAKE_ARGS+=	-DWITH_CYCLES:BOOL=ON
CMAKE_ARGS+=	-DWITH_CYCLES_CUDA_BINARIES:BOOL=OFF
CMAKE_ARGS+=	-DWITH_CYCLES_TEST:BOOL=OFF
LIB_DEPENDS+=	OpenImageIO:${PORTSDIR}/graphics/openimageio
PLIST_SUB+=	CYCLES=""
.else
# openimageio doesn't build on 7.x so can't enable cycles
CMAKE_ARGS+=	-DWITH_CYCLES:BOOL=OFF
CMAKE_ARGS+=	-DWITH_CYCLES_CUDA_BINARIES:BOOL=OFF
CMAKE_ARGS+=	-DWITH_CYCLES_TEST:BOOL=OFF
PLIST_SUB+=	CYCLES="@comment "
.endif

.if ${PORT_OPTIONS:MHEADLESS}
CMAKE_ARGS+=	-DWITH_HEADLESS:BOOL=ON
.else
CMAKE_ARGS+=	-DWITH_HEADLESS:BOOL=OFF
.endif

.if ${PORT_OPTIONS:MSECURITY}
CMAKE_ARGS+=	-DWITH_PYTHON_SECURITY:BOOL=ON
.else
CMAKE_ARGS+=	-DWITH_PYTHON_SECURITY:BOOL=OFF
.endif

.if ${PORT_OPTIONS:MPLAYER}
CMAKE_ARGS+=	-DWITH_PLAYER:BOOL=ON
PLIST_SUB+=	PLAYER=""
.else
CMAKE_ARGS+=	-DWITH_PLAYER:BOOL=OFF
PLIST_SUB+=	PLAYER="@comment "
.endif

.if ${PORT_OPTIONS:MJACK}
LIB_DEPENDS+=	jack:${PORTSDIR}/audio/jack
CMAKE_ARGS+=	-DWITH_JACK:BOOL=ON
.else
CMAKE_ARGS+=	-DWITH_JACK:BOOL=OFF
.endif

.if ${PORT_OPTIONS:MCOLLADA}
CMAKE_ARGS+=	-DWITH_OPENCOLLADA:BOOL=ON
# add collada lib to ports
.else
CMAKE_ARGS+=	-DWITH_OPENCOLLADA:BOOL=OFF
.endif

.if ${PORT_OPTIONS:MNDOF}
CMAKE_ARGS+=	-DWITH_INPUT_NDOF:BOOL=ON
# add ndof lib to ports
.else
CMAKE_ARGS+=	-DWITH_INPUT_NDOF:BOOL=OFF
.endif

.if ${PORT_OPTIONS:MNLS}
CMAKE_ARGS+=	-DWITH_INTERNATIONAL:BOOL=ON
PLIST_SUB+=	NLS=""
USE_GETTEXT=	yes
USE_ICONV=		yes
.else
CMAKE_ARGS+=	-DWITH_INTERNATIONAL:BOOL=OFF
PLIST_SUB+=	NLS="@comment "
.endif

post-extract:
# tanslations
	@${MV} ${WRKDIR}/sambler-myblendertranslations-*/* ${WRKSRC}/release/datafiles/locale/
# addons
	@${MV} ${WRKDIR}/sambler-myblenderaddons-*/* ${WRKSRC}/release/scripts/addons/
# contrib
	@${MV} ${WRKDIR}/sambler-myblendercontrib-*/* ${WRKSRC}/release/scripts/addons_contrib/

post-install:
	@${INSTALL_SCRIPT} ${WRKDIR}/blender ${PREFIX}/bin/blender
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/bin/blender \
		${PREFIX}/bin/blender-bin
	@${MKDIR} ${DATADIR}
	@${INSTALL_SCRIPT} ${INSTALL_WRKSRC}/bin/blender-thumbnailer.py \
		${PREFIX}/bin/blender-thumbnailer.py

.if ${PORT_OPTIONS:MPLAYER}
	@${INSTALL_SCRIPT} ${WRKDIR}/blenderplayer ${PREFIX}/bin/blenderplayer
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/bin/blenderplayer \
		${PREFIX}/bin/blenderplayer-bin
.endif

	@${CP} -R ${OUTDIR}/scripts ${DATADIR}
	@${INSTALL_DATA} ${INSTALL_WRKSRC}/bin/blender.svg \
		${PREFIX}/share/pixmaps/blender.svg

.if ${PORT_OPTIONS:MNLS}
.for ii in ${LANG}
	@${MKDIR} ${DATADIR}/datafiles/locale/${ii}/LC_MESSAGES
	@${INSTALL_DATA} \
		${OUTDIR}/datafiles/locale/${ii}/LC_MESSAGES/blender.mo \
		${DATADIR}/datafiles/locale/${ii}/LC_MESSAGES/blender.mo
.endfor
.endif

.if !defined(NO_INSTALL_MANPAGES)
	@${INSTALL_MAN} ${INSTALL_WRKSRC}/bin/blender.1 \
		${MAN1PREFIX}/man/man1
.endif

	@${MKDIR} ${DESKTOPDIR}
	@${INSTALL_DATA} ${INSTALL_WRKSRC}/bin/blender.desktop \
		${DESKTOPDIR}
	@-update-desktop-database -q

.include <bsd.port.mk>
