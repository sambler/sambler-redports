# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openimageio14
PORTVERSION=	1.4.16
DISTVERSIONPREFIX=	Release-
PORTREVISION=	3
CATEGORIES=	graphics multimedia

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	OpenImageIO graphics library

LICENSE=	BSD3CLAUSE

LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libfreetype.so:print/freetype2 \
		libhdf5.so:science/hdf5 \
		libImath.so:graphics/ilmbase \
		libIlmImf.so:graphics/openexr \
		libopenjpeg.so:graphics/openjpeg15 \
		libpng16.so:graphics/png \
		libtiff.so:graphics/tiff \
		libhdf5.so:science/hdf5 \
		libwebp.so:graphics/webp
# take out to fix build with clang6
#		libopencv_highgui.so:graphics/opencv \
#		libopencv_core.so:graphics/opencv-core \

USE_GITHUB=	yes
GH_ACCOUNT=	OpenImageIO
GH_PROJECT=	oiio
PORTSCOUT=	ignore:1

USES=		cmake compiler:c++11-lib jpeg
CMAKE_ON=	OIIO_BUILD_TOOLS
CMAKE_OFF=	BUILDSTATIC LINKSTATIC NOTHREADS STOP_ON_WARNING \
		USE_OPENCV USE_OPENSSL USE_PYTHON
USE_LDCONFIG=	yes

OPTIONS_DEFINE=		DOCS GIF OCIO RAW TEST
#IMAGEVIEWER
OPTIONS_DEFAULT=	OCIO GIF
OPTIONS_SUB=		yes

GIF_DESC=		Use libgif
#IMAGEVIEWER_DESC=	Build image viewer
OCIO_DESC=		Colour management support
RAW_DESC=		Use libraw

DOCS_CMAKE_BOOL=	INSTALL_DOCS

GIF_CMAKE_BOOL=		USE_GIF
GIF_LIB_DEPENDS=	libgif.so:graphics/giflib

#IMAGEVIEWER_CMAKE_BOOL=	USE_QT USE_OPENGL
#IMAGEVIEWER_USES=	qt:4
#IMAGEVIEWER_USE=	GL=gl,glu,glew \
#			QT=corelib,gui,opengl,qmake_build,moc_build,rcc_build,uic_build

OCIO_CMAKE_BOOL=	USE_OCIO
OCIO_LIB_DEPENDS=	libOpenColorIO.so:graphics/opencolorio

RAW_CMAKE_BOOL=		USE_LIBRAW
RAW_LIB_DEPENDS=	libraw_r.so:graphics/libraw

TEST_CMAKE_BOOL=	OIIO_BUILD_TESTS

PLIST_SUB+=		LIBVERS=${PORTVERSION}

post-patch:
	@${REINPLACE_CMD} -e 's|share/doc/OpenImageIO|${DOCSDIR}|g' \
		${WRKSRC}/CMakeLists.txt

post-install:
	@${REINPLACE_CMD} -e 's|OpenImageIO/|OpenImageIO14/|g' \
		${STAGEDIR}/${PREFIX}/include/OpenImageIO14/imagecache.h
	${LN} -sf libOpenImageIO14.so.1.4 ${STAGEDIR}${PREFIX}/lib/libOpenImageIO14.so.1
	${LN} -sf libOpenImageIO_Util14.so.1.4 ${STAGEDIR}${PREFIX}/lib/libOpenImageIO_Util14.so.1

.include <bsd.port.mk>

