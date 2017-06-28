# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	py35-blender
PORTVERSION=	2.78c
PORTREVISION=	0
CATEGORIES=	graphics multimedia
MASTER_SITES=	http://download.blender.org/source/ \
		http://mirror.cs.umn.edu/blender.org/source/
DISTFILES=	blender-${PORTVERSION}.tar.gz

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	blender built as a python module

LICENSE=	GPLv2

LIB_DEPENDS=	liblzo2.so:archivers/lzo2 \
		libsamplerate.so:audio/libsamplerate \
		libsndfile.so:audio/libsndfile \
		libboost_thread.so:devel/boost-libs \
		libexecinfo.so:devel/libexecinfo \
		libunwind.so:devel/libunwind \
		libpcre.so:devel/pcre \
		libyaml-cpp03.so:devel/yaml-cpp03 \
		libOpenColorIO.so:graphics/opencolorio \
		libOpenImageIO.so:graphics/openimageio \
		libIlmImf.so:graphics/OpenEXR \
		libHalf.so:graphics/ilmbase \
		libopenjpeg.so:graphics/openjpeg15 \
		libpng.so:graphics/png \
		libtiff.so:graphics/tiff \
		libfftw3.so:math/fftw3 \
		libavutil.so:multimedia/ffmpeg \
		libfreetype.so:print/freetype2 \
		libtinyxml.so:textproc/tinyxml

USES=		cmake:outsource compiler:c++11-lib shebangfix
USES+=		python:3.5 openal:al,alut jpeg
USES+=		imake:noman
USE_GL=		gl glu glew
USE_GNOME=	libxml2
WRKSRC=		${WRKDIR}/blender-${PORTVERSION}
LICDIR=		${PREFIX}/share/licenses/${PKGNAME}
VERS_TAG=	${PORTVERSION:C/[.abcd]//g}
PLIST_SUB+=	VERSTAG=${VERS_TAG}
PORTSCOUT=	ignore:1

USE_SDL=	sdl2

LDFLAGS+=	-L${LOCALBASE}/lib -lexecinfo

CMAKE_ARGS+=	-DWITH_BUILDINFO:BOOL=ON -DWITH_AUDASPACE:BOOL=ON \
		-DWITH_BLENDER:BOOL=ON \
		-DWITH_BOOST_ICU:BOOL=OFF -DWITH_BULLET:BOOL=ON \
		-DWITH_CODEC_FFMPEG:BOOL=ON -DWITH_CODEC_SNDFILE:BOOL=ON \
		-DFFMPEG:STRING="${LOCALBASE}" -DWITH_COMPOSITOR:BOOL=ON \
		-DWITH_CYCLES:BOOL=ON -DWITH_CYCLES_CUDA_BINARIES:BOOL=OFF \
		-DCYCLES_OPENCL_DEBUG:BOOL=OFF -DWITH_CYCLES_STANDALONE:BOOL=OFF \
		-DWITH_CYCLES_STANDALONE_GUI:BOOL=OFF -DWITH_DOC_MANPAGE:BOOL=OFF \
		-DWITH_FFTW3:BOOL=ON -DWITH_FREESTYLE:BOOL=ON \
		-DWITH_GAMEENGINE:BOOL=ON -DWITH_GUARDEDALLOC:BOOL=ON \
		-DWITH_HEADLESS:BOOL=ON -DWITH_IK_ITASC:BOOL=ON \
		-DWITH_IK_SOLVER:BOOL=ON -DWITH_IMAGE_CINEON:BOOL=ON \
		-DWITH_IMAGE_DDS:BOOL=ON -DWITH_IMAGE_FRAMESERVER:BOOL=ON \
		-DWITH_IMAGE_HDR:BOOL=ON -DWITH_IMAGE_OPENEXR:BOOL=ON \
		-DWITH_IMAGE_OPENJPEG:BOOL=ON -DWITH_IMAGE_REDCODE:BOOL=ON \
		-DWITH_IMAGE_TIFF:BOOL=ON -DWITH_INSTALL_PORTABLE:BOOL=ON \
		-DWITH_LIBMV:BOOL=ON -DWITH_LZMA:BOOL=ON -DWITH_LZO:BOOL=ON \
		-DWITH_MEM_JEMALLOC:BOOL=OFF -DWITH_MOD_BOOLEAN:BOOL=ON \
		-DWITH_MOD_FLUID:BOOL=ON \
		-DWITH_MOD_OCEANSIM:BOOL=ON -DWITH_MOD_REMESH:BOOL=ON \
		-DWITH_MOD_SMOKE:BOOL=ON -DWITH_GCC_MUDFLAP:BOOL=OFF \
		-DWITH_OPENAL:BOOL=ON -DWITH_OPENCOLORIO:BOOL=ON \
		-DWITH_PLAYER:BOOL=OFF \
		-DWITH_PYTHON:BOOL=ON -DWITH_PYTHON_INSTALL:BOOL=OFF \
		-DWITH_PYTHON_MODULE:BOOL=ON -DWITH_PYTHON_SAFETY:BOOL=OFF \
		-DWITH_PYTHON_INSTALL_REQUESTS:BOOL=OFF \
		-DWITH_PYTHON_INSTALL_NUMPY:BOOL=OFF \
		-DWITH_RAYOPTIMIZATION:BOOL=ON -DWITH_SDL:BOOL=ON \
		-DWITH_STATIC_LIBS:BOOL=OFF -DWITH_SYSTEM_BULLET:BOOL=OFF \
		-DWITH_SYSTEM_GLEW:BOOL=ON -DWITH_SYSTEM_OPENJPEG:BOOL=ON \
		-DWITH_X11_XF86VMODE:BOOL=ON -DWITH_X11_XINPUT:BOOL=ON

CMAKE_INSTALL_PREFIX=	${PYTHON_SITELIBDIR}

OPTIONS_DEFINE=	COLLADA CYCLES JACK NLS OSD OSL SECURITY
OPTIONS_DEFAULT=	COLLADA CYCLES JACK NLS OSD OSL SECURITY

OPTIONS_SUB=	yes
COLLADA_DESC=	Include collada import
CYCLES_DESC=	Build cycles render engine
JACK_DESC=	Audio support using JackAudio
NLS_DESC=	Include translations
OSD_DESC=	Opensubdiv support
OSL_DESC=	OSL shading support
SECURITY_DESC=	Disable scripts auto-run

COLLADA_CMAKE_ON=	-DWITH_OPENCOLLADA:BOOL=ON
COLLADA_CMAKE_OFF=	-DWITH_OPENCOLLADA:BOOL=OFF
COLLADA_LIB_DEPENDS=	libOpenCOLLADABaseUtils.so:graphics/opencollada

CYCLES_CMAKE_ON=	-DWITH_CYCLES:BOOL=ON
CYCLES_CMAKE_OFF=	-DWITH_CYCLES:BOOL=OFF

JACK_CMAKE_ON=		-DWITH_JACK:BOOL=ON \
			-DWITH_JACK_DYNLOAD:BOOL=ON
JACK_CMAKE_OFF=		-DWITH_JACK:BOOL=OFF
JACK_LIB_DEPENDS=	libjack.so:audio/jack

NLS_CMAKE_ON=		-DWITH_INTERNATIONAL:BOOL=ON
NLS_CMAKE_OFF=		-DWITH_INTERNATIONAL:BOOL=OFF
# Use iconv:wchar_t to force the usage of iconv from ports.
# libboost_locale.so uses libiconv_open, while we only provide
# iconv_open in 10.x+
NLS_USES=		gettext iconv:lib,wchar_t
NLS_LDFLAGS=		-L${LOCALBASE}/lib -lintl

OSD_CMAKE_ON=		-DWITH_OPENSUBDIV:BOOL=ON
OSD_CMAKE_OFF=		-DWITH_OPENSUBDIV:BOOL=OFF
OSD_LIB_DEPENDS=	libosdCPU.so:graphics/opensubdiv

OSL_IMPLIES=		CYCLES
OSL_CMAKE_ON=		-DWITH_CYCLES_OSL:BOOL=ON \
			-DWITH_CXX11:BOOL=ON \
			-DWITH_LLVM:BOOL=ON \
			-DLLVM_STATIC:BOOL=OFF \
			-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config40"
OSL_CMAKE_OFF=		-DWITH_CYCLES_OSL:BOOL=OFF
OSL_LIB_DEPENDS=	liboslcomp.so:graphics/openshadinglanguage
OSL_BUILD_DEPENDS=	llvm-config40:devel/llvm40
OSL_RUN_DEPENDS=	llvm-config40:devel/llvm40

SECURITY_CMAKE_ON=	-DWITH_PYTHON_SECURITY:BOOL=ON
SECURITY_CMAKE_OFF=	-DWITH_PYTHON_SECURITY:BOOL=OFF

.include <bsd.port.options.mk>

post-patch:
	@${REINPLACE_CMD} -e 's|yaml-cpp|&03|' \
		${PATCH_WRKSRC}/build_files/cmake/Modules/FindOpenColorIO.cmake

.include <bsd.port.mk>
