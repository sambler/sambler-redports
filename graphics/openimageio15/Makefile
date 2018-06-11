# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openimageio15
PORTVERSION=	1.5.24
DISTVERSIONPREFIX=	Release-
PORTREVISION=	3
CATEGORIES=	graphics multimedia

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	OpenImageIO graphics library

LICENSE=	BSD3CLAUSE

LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libImath.so:graphics/ilmbase \
		libIlmImf.so:graphics/OpenEXR \
		libpng16.so:graphics/png \
		libtiff.so:graphics/tiff \
		libhdf5.so:science/hdf5 \
		libwebp.so:graphics/webp

USE_GITHUB=	yes
GH_ACCOUNT=	OpenImageIO
GH_PROJECT=	oiio
PORTSCOUT=	ignore:1

# fbm also installs bin/idiff
CONFLICTS=	fbm-[0-9]*

USES=		cmake:outsource jpeg
USE_LDCONFIG=	yes
CMAKE_ON=	OIIO_BUILD_TOOLS
CMAKE_OFF=	BUILDSTATIC LINKSTATIC NOTHREADS STOP_ON_WARNING \
		USE_CPP11 USE_OPENSSL USE_PYTHON USE_PYTHON3
CXXFLAGS+=	-D__STDC_CONSTANT_MACROS

OPTIONS_DEFINE=		DOCS FFMPEG FREETYPE GIF IMAGEVIEWER OCIO OPENCV \
			OPENJPEG RAW TEST
OPTIONS_DEFAULT=	FREETYPE GIF OCIO OPENJPEG
OPTIONS_SUB=		yes

FFMPEG_DESC=		Use FFmpeg to support extra file types
IMAGEVIEWER_DESC=	Build image viewer (requires Qt)
OCIO_DESC=		Color management support

DOCS_CMAKE_BOOL=	INSTALL_DOCS

FFMPEG_CMAKE_BOOL=	USE_FFMPEG
FFMPEG_LIB_DEPENDS=	libavutil.so:multimedia/ffmpeg

FREETYPE_CMAKE_BOOL=	USE_FREETYPE
FREETYPE_LIB_DEPENDS=	libfreetype.so:print/freetype2

GIF_CMAKE_BOOL=		USE_GIF
GIF_LIB_DEPENDS=	libgif.so:graphics/giflib

IMAGEVIEWER_CMAKE_BOOL=	USE_QT USE_OPENGL
IMAGEVIEWER_USE=	GL=gl,glu,glew \
			QT4=corelib,gui,opengl,qmake_build,moc_build,rcc_build,uic_build

OCIO_CMAKE_BOOL=	USE_OCIO
OCIO_LIB_DEPENDS=	libOpenColorIO.so:graphics/opencolorio

OPENCV_CMAKE_BOOL=	USE_OPENCV
OPENCV_LIB_DEPENDS=	libopencv_highgui.so:graphics/opencv \
			libopencv_core.so:graphics/opencv-core

OPENJPEG_CMAKE_BOOL=	USE_OPENJPEG
OPENJPEG_LIB_DEPENDS=	libopenjpeg.so:graphics/openjpeg15

RAW_CMAKE_BOOL=		USE_LIBRAW
RAW_LIB_DEPENDS=	libraw_r.so:graphics/libraw

TEST_CMAKE_BOOL=	OIIO_BUILD_TESTS

PLIST_SUB+=		LIBVERS=${PORTVERSION}

post-patch:
	@${REINPLACE_CMD} -e 's|share/doc/OpenImageIO|${DOCSDIR}|g' \
		${WRKSRC}/CMakeLists.txt

post-install:
	${LN} -sf libOpenImageIO15.so.1.5 \
		${STAGEDIR}${PREFIX}/lib/libOpenImageIO15.so.1
	${LN} -sf libOpenImageIO_Util15.so.1.5 \
		${STAGEDIR}${PREFIX}/lib/libOpenImageIO_Util15.so.1

.include <bsd.port.mk>
