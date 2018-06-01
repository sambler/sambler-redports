# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openimageio_dev
PORTVERSION=	1.9.3
DISTVERSIONPREFIX=	Release-
DISTVERSIONSUFFIX=	dev
PORTREVISION?=	0
CATEGORIES?=	graphics multimedia

MAINTAINER?=	FreeBSD@Shaneware.biz
COMMENT?=	OpenImageIO graphics library

LICENSE=	BSD3CLAUSE

USE_GITHUB=	yes
GH_ACCOUNT=	OpenImageIO
GH_PROJECT=	oiio
PORTSCOUT=	ignore:1

# fbm also installs bin/idiff
CONFLICTS=	fbm-[0-9]*

LIB_DEPENDS+=	libboost_thread.so:devel/boost-libs \
		libImath.so:graphics/ilmbase \
		libIlmImf.so:graphics/OpenEXR \
		libpng16.so:graphics/png \
		libtiff.so:graphics/tiff \
		libwebp.so:graphics/webp \
		libhdf5.so:science/hdf5
USES=		cmake:outsource jpeg
CMAKE_ARGS=	USE_CPP:STRING=11
CMAKE_OFF=	BUILDSTATIC LINKSTATIC NOTHREADS STOP_ON_WARNING USE_OPENSSL

OPTIONS_DEFINE=		DOCS FFMPEG FREETYPE GIF IMAGEVIEWER OCIO OPENCV \
			OPENJPEG RAW TEST
OPTIONS_DEFAULT=	FREETYPE GIF OCIO OPENJPEG
OPTIONS_SUB=		yes

DOCS_CMAKE_BOOL=	BUILD_DOCS INSTALL_DOCS
DOCS_CMAKE_ON=		-DCMAKE_INSTALL_DOCDIR:STRING=${DOCSDIR}

FFMPEG_DESC=		Use FFmpeg to support extra file types
FFMPEG_CMAKE_BOOL=	USE_FFMPEG
FFMPEG_LIB_DEPENDS=	libavutil.so:multimedia/ffmpeg

FREETYPE_CMAKE_BOOL=	USE_FREETYPE
FREETYPE_LIB_DEPENDS=	libfreetype.so:print/freetype2

GIF_CMAKE_BOOL=		USE_GIF
GIF_LIB_DEPENDS=	libgif.so:graphics/giflib

IMAGEVIEWER_DESC=	Build image viewer (requires Qt)
IMAGEVIEWER_CMAKE_BOOL=	USE_QT USE_OPENGL
IMAGEVIEWER_USE=	GL=gl,glu,glew \
			QT5=buildtools,core,gui,opengl,qmake_build,widgets

OCIO_DESC=		Color management support
OCIO_CMAKE_BOOL=	USE_OCIO
OCIO_LIB_DEPENDS=	libOpenColorIO.so:graphics/opencolorio

OPENCV_CMAKE_BOOL=	USE_OPENCV
OPENCV_LIB_DEPENDS=	libopencv_highgui.so:graphics/opencv \
			libopencv_core.so:graphics/opencv-core \
			libopenjpeg.so:graphics/openjpeg15

OPENJPEG_CMAKE_BOOL=	USE_OPENJPEG
OPENJPEG_LIB_DEPENDS=	libopenjp2.so:graphics/openjpeg

RAW_CMAKE_BOOL=		USE_LIBRAW
RAW_LIB_DEPENDS=	libraw_r.so:graphics/libraw

TEST_CMAKE_BOOL=	OIIO_BUILD_TESTS

DOCSDIR=		${PREFIX}/share/doc/${PORTNAME}${PKGNAMESUFFIX}

PLIST_SUB+=		LIBVERS=${PORTVERSION}

.include <bsd.port.options.mk>

.if ${ARCH} == powerpc
USE_GCC=	yes
.endif

.if ${SLAVE_PORT} == no
USE_LDCONFIG=	yes
CMAKE_ON+=	DOIIO_BUILD_TOOLS
CMAKE_OFF+=	USE_PYTHON
.else
BUILD_DEPENDS+=	${PYNUMPY} \
		${PYTHON_PKGNAMEPREFIX}pybind11:devel/py-pybind11
LIB_DEPENDS+=	libOpenImageIO.so:graphics/openimageio
RUN_DEPENDS+=	${PYNUMPY}
PLIST=		${PKGDIR}/pkg-plist-pybind
USES+=		python
USE_PYTHON=	flavors
CMAKE_ON+=	USE_PYTHON
CMAKE_OFF+=	OIIO_BUILD_TOOLS USE_FFMPEG
CMAKE_ARGS+=	PYTHON_VERSION:STRING=${PYTHON_VER}
.endif

.include <bsd.port.pre.mk>

.if ${SLAVE_PORT} == yes
# we need to do this here to get PYTHON_MAJOR_VER
# this is related to adding USES+=python in the first slave test
.if ${PYTHON_MAJOR_VER} == 2
do-install:
	@${MKDIR} ${STAGEDIR}${PYTHON_SITELIBDIR}
	${INSTALL_LIB} ${BUILD_WRKSRC}/src/python/OpenImageIO.so ${STAGEDIR}${PYTHON_SITELIBDIR}
.else
do-install:
	@${MKDIR} ${STAGEDIR}${PYTHON_SITELIBDIR}
	${INSTALL_LIB} ${BUILD_WRKSRC}/src/python3/OpenImageIO.so ${STAGEDIR}${PYTHON_SITELIBDIR}
.endif
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|share/doc/OpenImageIO|${DOCSDIR}|g' \
		${WRKSRC}/CMakeLists.txt

post-install:
.if ${SLAVE_PORT} == no
	${LN} -sf libOpenImageIO_dev.so.1.9 \
		${STAGEDIR}${PREFIX}/lib/libOpenImageIO_dev.so.1
	${LN} -sf libOpenImageIO_Util_dev.so.1.9 \
		${STAGEDIR}${PREFIX}/lib/libOpenImageIO_Util_dev.so.1
.endif

do-test-TEST-on:
	@cd ${BUILD_WRKSRC} && ${MAKE_CMD} ARGS=-V test

.include <bsd.port.post.mk>
