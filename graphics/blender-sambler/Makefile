# New ports collection makefile for:    blender-sambler
# Date created:         2 April 2012
# Whom:                 Shane Ambler
#
# $FreeBSD$

PORTNAME=	blender-sambler
PORTVERSION=	2.65
PORTREVISION=	1
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

LIB_DEPENDS=	samplerate:${PORTSDIR}/audio/libsamplerate
LIB_DEPENDS+=	sndfile:${PORTSDIR}/audio/libsndfile
LIB_DEPENDS+=	boost_thread:${PORTSDIR}/devel/boost-libs
LIB_DEPENDS+=	jpeg:${PORTSDIR}/graphics/jpeg
LIB_DEPENDS+=	OpenColorIO:${PORTSDIR}/graphics/opencolorio
LIB_DEPENDS+=	IlmImf:${PORTSDIR}/graphics/OpenEXR
LIB_DEPENDS+=	openjpeg:${PORTSDIR}/graphics/openjpeg
LIB_DEPENDS+=	png15:${PORTSDIR}/graphics/png
LIB_DEPENDS+=	tiff:${PORTSDIR}/graphics/tiff
LIB_DEPENDS+=	fftw3:${PORTSDIR}/math/fftw3
LIB_DEPENDS+=	avutil:${PORTSDIR}/multimedia/ffmpeg
LIB_DEPENDS+=	freetype:${PORTSDIR}/print/freetype2
RUN_DEPENDS=	xdg-mime:${PORTSDIR}/devel/xdg-utils
.if exists(${PORTSDIR}/math/py-numpy32)
# PYTHON_SITELIBDIR most likely points to python2.7/site-packages
# we specifically want a 3.2 version installed
RUN_DEPENDS+=	${LOCALBASE}/lib/python3.2/site-packages/numpy/__init__.py:${PORTSDIR}/math/py-numpy32
CMAKE_ARGS+=	-DPYTHON_NUMPY_PATH:STRING=${LOCALBASE}/lib/python3.2/site-packages
.endif

#USE_GITHUB=	yes
#GH_ACCOUNT=	sambler:base \
#		sambler:addons \
#		sambler:contrib \
#		sambler:trans
#GH_PROJECT=	myblender
#GH_PROJECT=	myblender:base \
#		myblenderaddons:addons \
#		myblendercontrib:contrib \
#		myblendertranslations:trans
#GH_TAGNAME=	sambler-${PORTVERSION}.${PORTREVISION}
#GH_TAGNAME=	sambler-${PORTVERSION}.${PORTREVISION}:base \
#		addons-${PORTVERSION}.${PORTREVISION}:addons \
#		contrib-${PORTVERSION}.${PORTREVISION}:contrib \
#		translate-${PORTVERSION}.${PORTREVISION}:trans
GH_COMMIT=	15cd81f

FETCH_ARGS=     -pRr
CONFLICTS=	blender-2.*

USE_CMAKE=	yes
CMAKE_OUTSOURCE=	yes
MAKE_JOBS_SAFE=	yes
WRKSRC=         ${WRKDIR}/sambler-myblender-${GH_COMMIT}

USE_PYTHON=	3.2
# blender looks for py3.3 by default - we need to specify 3.2 for now
CMAKE_ARGS+=	-DPYTHON_VERSION:STRING=3.2
WANT_GNOME=	yes
USE_GNOME=	desktopfileutils
USE_OPENAL=	al alut
USE_SDL=	sdl
USE_XORG=	x11 xext xmu
USE_GL=		glew

CMAKE_ARGS+=	-DWITH_BUILDINFO:BOOL=ON -DWITH_AUDASPACE:BOOL=ON
CMAKE_ARGS+=	-DWITH_BLENDER:BOOL=ON -DWITH_BULLET:BOOL=ON
CMAKE_ARGS+=	-DWITH_CODEC_FFMPEG:BOOL=ON -DWITH_CODEC_SNDFILE:BOOL=ON
CMAKE_ARGS+=	-DWITH_COMPOSITOR:BOOL=ON -DWITH_COMPOSITOR_LEGACY:BOOL=OFF
CMAKE_ARGS+=	-DWITH_FFTW3:BOOL=ON -DWITH_GAMEENGINE:BOOL=ON
CMAKE_ARGS+=	-DWITH_IK_ITASC:BOOL=ON -DWITH_IK_SOLVER:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_CINEON:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_DDS:BOOL=ON -DWITH_IMAGE_FRAMESERVER:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_HDR:BOOL=ON -DWITH_IMAGE_OPENEXR:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_OPENJPEG:BOOL=ON -DWITH_IMAGE_REDCODE:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_TIFF:BOOL=ON -DWITH_INSTALL_PORTABLE:BOOL=ON
CMAKE_ARGS+=	-DWITH_LIBMV:BOOL=ON -DWITH_LZMA:BOOL=ON -DWITH_LZO:BOOL=ON
CMAKE_ARGS+=	-DWITH_MEM_JEMALLOC:BOOL=OFF -DWITH_MOD_BOOLEAN:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_CLOTH_ELTOPO:BOOL=ON -DWITH_MOD_FLUID:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_OCEANSIM:BOOL=ON -DWITH_MOD_REMESH:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_SMOKE:BOOL=ON -DWITH_OPENAL:BOOL=ON
CMAKE_ARGS+=	-DWITH_OPENCOLORIO:BOOL=ON
CMAKE_ARGS+=	-DWITH_PYTHON:BOOL=ON -DWITH_PYTHON_INSTALL:BOOL=OFF
CMAKE_ARGS+=	-DWITH_PYTHON_MODULE:BOOL=OFF -DWITH_PYTHON_SAFETY:BOOL=OFF
CMAKE_ARGS+=	-DWITH_PYTHON_INSTALL_NUMPY:BOOL=OFF
CMAKE_ARGS+=	-DWITH_RAYOPTIMIZATION:BOOL=ON -DWITH_SDL:BOOL=ON
CMAKE_ARGS+=	-DWITH_SYSTEM_GLEW:BOOL=ON -DWITH_SYSTEM_OPENJPEG:BOOL=ON
CMAKE_ARGS+=	-DWITH_X11_XF86VMODE:BOOL=ON -DWITH_X11_XINPUT:BOOL=ON

SUB_FILES=	blender blenderplayer
MAN1=		blender.1

OUTDIR=		${INSTALL_WRKSRC}/bin/${PORTVERSION}

LANG=		ar cs de es es_ES fa fr hr id it ja ky pt \
		ru sr sr@latin sv tr uk zh_CN zh_TW

OPTIONS_DEFINE=	HEADLESS SECURITY PLAYER JACK NLS OSL
## COLLADA NDOF
OPTIONS_SINGLE=	COMPILER
OPTIONS_SINGLE_COMPILER=	CC_GCC46 CC_CLANG
OPTIONS_DEFAULT=	CC_GCC46 SECURITY NLS OSL

CC_GCC46_DESC=	"Build with gcc46"
CC_CLANG_DESC=	"Build with clang"
HEADLESS_DESC=	"Disable user interface"
SECURITY_DESC=	"Disable scripts auto-run"
PLAYER_DESC=	"Build blender player"
JACK_DESC=	"Audio support using JackAudio"
#COLLADA_DESC=	"Include collada import"
#NDOF_DESC=	"NDOF Support"
NLS_DESC=	"Include translations"
OSL_DESC=	"OSL shading support"

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MCC_CLANG}
CC=clang
CXX=clang++
CPP=clang-cpp
CMAKE_ARGS+=	-DWITH_OPENMP:BOOL=OFF

.if ${OSVERSION} < 900033
BUILD_DEPENDS+=	clang:${PORTSDIR}/lang/clang
.endif
.endif # CC_CLANG

.if ${PORT_OPTIONS:MCC_GCC46}
CMAKE_ARGS+=	-DWITH_OPENMP:BOOL=ON
USE_GCC=	4.6+
LDFLAGS+=	-rpath ${LOCALBASE}/lib/gcc46
.endif

.if ${OSVERSION} >= 800000
CMAKE_ARGS+=	-DWITH_CYCLES:BOOL=ON
CMAKE_ARGS+=	-DWITH_CYCLES_CUDA_BINARIES:BOOL=OFF
CMAKE_ARGS+=	-DWITH_CYCLES_TEST:BOOL=OFF
LIB_DEPENDS+=	OpenImageIO:${PORTSDIR}/graphics/openimageio
PLIST_SUB+=	CYCLES=""

.if ${PORT_OPTIONS:MOSL}
.if exists(${PORTSDIR}/devel/boost-python3-libs)
LIB_DEPENDS+=	boost_python3:${PORTSDIR}/devel/boost-python3-libs
.endif
LIB_DEPENDS+=	oslcomp:${PORTSDIR}/graphics/openshadinglanguage
CMAKE_ARGS+=	-DWITH_CYCLES_OSL:BOOL=ON
PLIST_SUB+=	OSL=""
.else
CMAKE_ARGS+=	-DWITH_CYCLES_OSL:BOOL=OFF
PLIST_SUB+=	OSL="@comment "
.endif # OSL

.else # ${OSVERSION} 
# openimageio doesn't build on 7.x so can't enable cycles
CMAKE_ARGS+=	-DWITH_CYCLES:BOOL=OFF
CMAKE_ARGS+=	-DWITH_CYCLES_CUDA_BINARIES:BOOL=OFF
CMAKE_ARGS+=	-DWITH_CYCLES_OSL:BOOL=OFF
CMAKE_ARGS+=	-DWITH_CYCLES_TEST:BOOL=OFF
PLIST_SUB+=	CYCLES="@comment "
PLIST_SUB+=	OSL="@comment "
.endif # ${OSVERSION}

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
USE_ICONV=	yes
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
