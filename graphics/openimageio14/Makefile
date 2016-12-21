# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openimageio14
PORTVERSION=	1.4.16
DISTVERSIONPREFIX=	Release-
PORTREVISION?=	2
CATEGORIES?=	graphics multimedia

MAINTAINER?=	FreeBSD@Shaneware.biz
COMMENT?=	OpenImageIO graphics library

LICENSE=	BSD3CLAUSE

USE_GITHUB=	yes
GH_ACCOUNT=	OpenImageIO
GH_PROJECT=	oiio

USES=		cmake:outsource compiler:c++11-lib
CMAKE_ARGS=	-DBUILDSTATIC:BOOL=OFF \
		-DLINKSTATIC:BOOL=OFF \
		-DNOTHREADS:BOOL=OFF \
		-DSTOP_ON_WARNING:BOOL=OFF \
		-DUSE_OPENSSL:BOOL=OFF

OPTIONS_DEFINE=		DOCS GIF IMAGEVIEWER OCIO RAW TEST
OPTIONS_DEFAULT=	OCIO GIF
OPTIONS_SUB=		yes

GIF_DESC=		Use libgif
IMAGEVIEWER_DESC=	Build image viewer
OCIO_DESC=		Colour management support
RAW_DESC=		Use libraw

DOCS_CMAKE_ON=		-DINSTALL_DOCS:BOOL=ON
DOCS_CMAKE_OFF=		-DINSTALL_DOCS:BOOL=OFF

GIF_CMAKE_ON=		-DUSE_GIF:BOOL=ON
GIF_CMAKE_OFF=		-DUSE_GIF:BOOL=OFF
GIF_LIB_DEPENDS=	libgif.so:graphics/giflib

IMAGEVIEWER_CMAKE_ON=	-DUSE_QT:BOOL=ON -DUSE_OPENGL:BOOL=ON
IMAGEVIEWER_CMAKE_OFF=	-DUSE_OPENGL:BOOL=OFF -DUSE_QT:BOOL=OFF
IMAGEVIEWER_USE=	GL=gl,glu,glew \
			QT4=corelib,gui,opengl,qmake_build,moc_build,rcc_build,uic_build

OCIO_CMAKE_ON=		-DUSE_OCIO:BOOL=ON
OCIO_CMAKE_OFF=		-DUSE_OCIO:BOOL=OFF
OCIO_LIB_DEPENDS=	libOpenColorIO.so:graphics/opencolorio

RAW_CMAKE_ON=		-DUSE_LIBRAW:BOOL=ON
RAW_CMAKE_OFF=		-DUSE_LIBRAW:BOOL=OFF
RAW_LIB_DEPENDS=	libraw_r.so:graphics/libraw

TEST_CMAKE_ON=		-DOIIO_BUILD_TESTS:BOOL=ON
TEST_CMAKE_OFF=		-DOIIO_BUILD_TESTS:BOOL=OFF

PLIST_SUB+=		LIBVERS=${PORTVERSION}

.include <bsd.port.options.mk>

.if ${SLAVE_PORT} == no
LIB_DEPENDS+=	libboost_thread.so:devel/boost-libs \
		libfreetype.so:print/freetype2 \
		libhdf5.so:science/hdf5 \
		libImath.so:graphics/ilmbase \
		libIlmImf.so:graphics/OpenEXR \
		libopencv_highgui.so:graphics/opencv2 \
		libopencv_core.so:graphics/opencv2-core \
		libopenjpeg.so:graphics/openjpeg15 \
		libpng16.so:graphics/png \
		libtiff.so:graphics/tiff \
		libhdf5.so:science/hdf5 \
		libwebp.so:graphics/webp
USES+=		jpeg
USE_LDCONFIG=	yes
CMAKE_ARGS+=	-DUSE_PYTHON:BOOL=OFF -DOIIO_BUILD_TOOLS:BOOL=ON
.else
LIB_DEPENDS+=	libOpenImageIO14.so:graphics/openimageio14 \
		libboost_python.so:devel/boost-python-libs
USES+=		python
PLIST=		${PKGDIR}/pkg-plist-pybind
CMAKE_ARGS+=	-DUSE_PYTHON:BOOL=ON -DOIIO_BUILD_TOOLS:BOOL=OFF
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|share/doc/OpenImageIO|${DOCSDIR}|g' \
		${WRKSRC}/CMakeLists.txt

post-install:
	@${REINPLACE_CMD} -e 's|OpenImageIO/|OpenImageIO14/|g' \
		${STAGEDIR}/${PREFIX}/include/OpenImageIO14/imagecache.h
.if ${SLAVE_PORT} == no
	${LN} -sf libOpenImageIO14.so.1.4 ${STAGEDIR}${PREFIX}/lib/libOpenImageIO14.so.1
	${LN} -sf libOpenImageIO_Util14.so.1.4 ${STAGEDIR}${PREFIX}/lib/libOpenImageIO_Util14.so.1
.endif

.include <bsd.port.mk>
