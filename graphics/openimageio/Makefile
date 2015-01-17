# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openimageio
PORTVERSION=	1.5.8
PORTREVISION?=	0
CATEGORIES?=	graphics multimedia

MAINTAINER?=	FreeBSD@Shaneware.biz
COMMENT?=	OpenImageIO graphics library

LICENSE=	BSD3CLAUSE

USE_GITHUB=	yes
GH_ACCOUNT=	OpenImageIO
GH_PROJECT=	oiio
GH_TAGNAME=	Release-${PORTVERSION}beta1
GH_COMMIT=	7aace95

# fbm also installs bin/idiff
CONFLICTS=	fbm-[0-9]*

USES=		cmake:outsource
CMAKE_ARGS=	-DBUILDSTATIC:BOOL=OFF \
		-DLINKSTATIC:BOOL=OFF \
		-DNOTHREADS:BOOL=OFF \
		-DSTOP_ON_WARNING:BOOL=OFF \
		-DUSE_CPP11:BOOL=OFF
CXXFLAGS+=	-D__STDC_CONSTANT_MACROS

OPTIONS_DEFINE=		DOCS FFMPEG IMAGEVIEWER OCIO TEST
OPTIONS_DEFAULT=	OCIO FFMPEG DOCS IMAGEVIEWER  TEST
OPTIONS_SUB=		yes

IMAGEVIEWER_DESC=	Build image viewer
OCIO_DESC=		Colour management support
FFMPEG_DESC=		Use ffmpeg to support extra file types

DOCS_CMAKE_ON=		-DINSTALL_DOCS:BOOL=ON
DOCS_CMAKE_OFF=		-DINSTALL_DOCS:BOOL=OFF

FFMPEG_CMAKE_ON=	-DUSE_FFMPEG:BOOL=ON
FFMPEG_CMAKE_OFF=	-DUSE_FFMPEG:BOOL=OFF
FFMPEG_LIB_DEPENDS=	libavutil.so:${PORTSDIR}/multimedia/ffmpeg

OCIO_CMAKE_ON=		-DUSE_OCIO:BOOL=ON
OCIO_CMAKE_OFF=		-DUSE_OCIO:BOOL=OFF
OCIO_LIB_DEPENDS=	libOpenColorIO.so:${PORTSDIR}/graphics/opencolorio

TEST_CMAKE_ON=		-DOIIO_BUILD_TESTS:BOOL=ON
TEST_CMAKE_OFF=		-DOIIO_BUILD_TESTS:BOOL=OFF

.include <bsd.port.options.mk>

.if ${SLAVE_PORT} == no
LIB_DEPENDS=	libIlmImf.so:${PORTSDIR}/graphics/OpenEXR \
		libboost_thread.so:${PORTSDIR}/devel/boost-libs \
		libhdf5.so:${PORTSDIR}/science/hdf5 \
		libopencv_legacy.so:${PORTSDIR}/graphics/opencv \
		libopenjpeg.so:${PORTSDIR}/graphics/openjpeg15 \
		libwebp.so:${PORTSDIR}/graphics/webp
USE_LDCONFIG=	yes
CMAKE_ARGS+=	-DUSE_PYTHON:BOOL=OFF -DOIIO_BUILD_TOOLS:BOOL=ON
CMAKE_ARGS+=	-DUSE_PYTHON3:BOOL=OFF
.else
LIB_DEPENDS=	libOpenImageIO.so:${PORTSDIR}/graphics/openimageio \
		libboost_python.so:${PORTSDIR}/devel/boost-python-libs
USES+=		python
PLIST=		${PKGDIR}/pkg-plist-pybind
CMAKE_ARGS+=	-DUSE_PYTHON:BOOL=ON -DOIIO_BUILD_TOOLS:BOOL=OFF
CMAKE_ARGS+=	-DUSE_PYTHON3:BOOL=ON
.endif

.if ${PORT_OPTIONS:MIMAGEVIEWER}
USE_GL=		glew
USE_QT4=	corelib gui opengl qmake_build moc_build rcc_build uic_build
CMAKE_ARGS+=	-DUSE_QT:BOOL=ON -DUSE_OPENGL:BOOL=ON
CMAKE_ENV+=	QTDIR=${QT_PREFIX} QT_INCLUDES=${QT_INCDIR}
.else
CMAKE_ARGS+=	-DUSE_OPENGL:BOOL=OFF -DUSE_QT:BOOL=OFF
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|share/doc/OpenImageIO|${DOCSDIR}|g' \
		${WRKSRC}/CMakeLists.txt

post-install:
.if ${SLAVE_PORT} == no
	${LN} -sf libOpenImageIO.so.1.5 ${STAGEDIR}${PREFIX}/lib/libOpenImageIO.so.1
	${LN} -sf libOpenImageIO_Util.so.1.5 ${STAGEDIR}${PREFIX}/lib/libOpenImageIO_Util.so.1
.endif

.include <bsd.port.mk>
