# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	py35-blender
PORTVERSION=	2.79b
PORTREVISION=	4
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
		libunwind.so:devel/libunwind \
		libpcre.so:devel/pcre \
		libyaml-cpp03.so:devel/yaml-cpp03 \
		libOpenColorIO.so:graphics/opencolorio \
		libOpenImageIO.so:graphics/openimageio \
		libIlmImf.so:graphics/openexr \
		libHalf.so:graphics/ilmbase \
		libopenjpeg.so:graphics/openjpeg15 \
		libpng.so:graphics/png \
		libtiff.so:graphics/tiff \
		libfftw3.so:math/fftw3 \
		libavutil.so:multimedia/ffmpeg \
		libfreetype.so:print/freetype2 \
		libtinyxml.so:textproc/tinyxml

USES=		cmake:outsource compiler:c++11-lang shebangfix
USES+=		python:3.5 openal:al,alut jpeg
USES+=		imake:noman
USE_GL=		gl glu glew
USE_GNOME=	libxml2
WRKSRC=		${WRKDIR}/blender-${PORTVERSION}
LICDIR=		${PREFIX}/share/licenses/${PKGNAME}
PORTSCOUT=	ignore:1

USE_SDL=	sdl2

LDFLAGS+=	-L${LOCALBASE}/lib -lexecinfo

CMAKE_ON=	WITH_BUILDINFO WITH_AUDASPACE WITH_BLENDER WITH_BULLET \
		WITH_CODEC_FFMPEG WITH_CODEC_SNDFILE WITH_COMPOSITOR \
		WITH_CYCLES WITH_CXX11 WITH_FFTW3 WITH_FREESTYLE \
		WITH_GAMEENGINE WITH_GUARDEDALLOC WITH_HEADLESS \
		WITH_IK_ITASC WITH_IK_SOLVER WITH_IMAGE_CINEON \
		WITH_IMAGE_DDS WITH_IMAGE_FRAMESERVER WITH_IMAGE_HDR \
		WITH_IMAGE_OPENEXR WITH_IMAGE_OPENJPEG WITH_IMAGE_REDCODE \
		WITH_IMAGE_TIFF WITH_INSTALL_PORTABLE WITH_LIBMV \
		WITH_LZMA WITH_LZO WITH_MOD_BOOLEAN WITH_MOD_FLUID \
		WITH_MOD_OCEANSIM WITH_MOD_REMESH WITH_MOD_SMOKE \
		WITH_OPENAL WITH_OPENCOLORIO WITH_PYTHON  \
		WITH_PYTHON_MODULE WITH_RAYOPTIMIZATION WITH_SDL \
		WITH_SYSTEM_GLEW WITH_SYSTEM_OPENJPEG WITH_X11_XF86VMODE \
		WITH_X11_XINPUT
CMAKE_OFF=	WITH_BOOST_ICU WITH_CYCLES_CUDA_BINARIES  \
		CYCLES_OPENCL_DEBUG WITH_CYCLES_STANDALONE  \
		WITH_CYCLES_LOGGING WITH_CYCLES_STANDALONE_GUI  \
		WITH_DOC_MANPAGE WITH_MEM_JEMALLOC WITH_GCC_MUDFLAP \
		WITH_PLAYER WITH_PYTHON_INSTALL WITH_PYTHON_SAFETY  \
		WITH_PYTHON_INSTALL_REQUESTS WITH_PYTHON_INSTALL_NUMPY \
		WITH_STATIC_LIBS WITH_SYSTEM_BULLET

CMAKE_ARGS=	-DFFMPEG:STRING="${LOCALBASE}"

CMAKE_INSTALL_PREFIX=	${PYTHON_SITELIBDIR}

OPTIONS_DEFINE=	ALEMBIC ALEMBIC_HDF5 COLLADA CYCLES JACK NLS OSD OSL SECURITY
OPTIONS_DEFAULT=	ALEMBIC ALEMBIC_HDF5 COLLADA CYCLES JACK NLS OSL SECURITY

OPTIONS_SUB=	yes
ALEMBIC_DESC=		Enable Alembic file support
ALEMBIC_HDF5_DESC=	Enable Alembic hdf5 file support
COLLADA_DESC=		Include collada import
CYCLES_DESC=		Build cycles render engine
JACK_DESC=		Audio support using JackAudio
NLS_DESC=		Include translations
OSD_DESC=		Opensubdiv support
OSL_DESC=		OSL shading support
SECURITY_DESC=		Disable scripts auto-run

ALEMBIC_CMAKE_BOOL=	WITH_ALEMBIC
ALEMBIC_LIB_DEPENDS=	libAlembic.so:graphics/alembic
# note that this needs to be set to match alembics hdf5 option
ALEMBIC_HDF5_REQUIRES=	ALEMBIC
ALEMBIC_HDF5_CMAKE_BOOL= WITH_ALEMBIC_HDF5
ALEMBIC_HDF5_LIB_DEPENDS= libhdf5.so:science/hdf5

COLLADA_CMAKE_BOOL=	WITH_OPENCOLLADA
COLLADA_LIB_DEPENDS=	libOpenCOLLADABaseUtils.so:graphics/opencollada

CYCLES_CMAKE_BOOL=	WITH_CYCLES

JACK_CMAKE_BOOL=	WITH_JACK WITH_JACK_DYNLOAD
JACK_LIB_DEPENDS=	libjack.so:audio/jack

NLS_CMAKE_BOOL=		WITH_INTERNATIONAL
# Use iconv:wchar_t to force the usage of iconv from ports.
# libboost_locale.so uses libiconv_open, while we only provide
# iconv_open in 10.x+
NLS_USES=		gettext iconv:lib,wchar_t
NLS_LDFLAGS=		-L${LOCALBASE}/lib -lintl

OSD_CMAKE_BOOL=		WITH_OPENSUBDIV
OSD_LIB_DEPENDS=	libosdCPU.so:graphics/opensubdiv

OSL_IMPLIES=		CYCLES
OSL_CMAKE_BOOL=		WITH_CYCLES_OSL WITH_LLVM
OSL_CMAKE_ON=		-DLLVM_STATIC:BOOL=OFF \
			-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config40"
OSL_BUILD_DEPENDS=	llvm-config40:devel/llvm40
OSL_LIB_DEPENDS=	liboslcomp.so:graphics/openshadinglanguage
OSL_RUN_DEPENDS=	llvm-config40:devel/llvm40

SECURITY_CMAKE_BOOL=	WITH_PYTHON_SECURITY

.include <bsd.port.options.mk>

post-patch:
	@${REINPLACE_CMD} -e 's|yaml-cpp|&03|' \
		${PATCH_WRKSRC}/build_files/cmake/Modules/FindOpenColorIO.cmake

.include <bsd.port.mk>
