# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD: ports/graphics/opencolorio/Makefile,v 1.1 2012/09/19 15:19:59 pawel Exp $

PORTNAME=	opencolorio
PORTVERSION=	1.0.7
PORTREVISION=	2
CATEGORIES=	graphics multimedia
MASTER_SITES=	https://github.com/imageworks/OpenColorIO/tarball/
DISTNAME=	v${PORTVERSION}
EXTRACT_SUFX=	# empty
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Complete color management solution

LICENSE=	BSD

LIB_DEPENDS=	OpenImageIO:${PORTSDIR}/graphics/openimageio

FETCH_ARGS=	-pRr
USE_CMAKE=	yes
CMAKE_VERBOSE=	yes
CMAKE_OUTSOURCE=	yes
CMAKE_ARGS=	-DOCIO_BUILD_JNIGLUE:BOOL=OFF \
		-DOCIO_BUILD_PYGLUE:BOOL=ON
USE_LDCONFIG=	yes
USE_PYTHON=	2.6+
WRKSRC=		${WRKDIR}/imageworks-OpenColorIO-b3cb224
MAKE_JOBS_SAFE=	yes

OPTIONS_DEFINE=		DOCS CLIAPPS SSE
OPTIONS_DEFAULT=	DOCS CLIAPPS SSE

CLIAPPS_DESC=	Build cli apps
SSE_DESC=	Enable sse optimizations

.include <bsd.port.options.mk>

.if empty(PORT_OPTIONS:MDOCS)
CMAKE_ARGS+=	-DOCIO_BUILD_DOCS:BOOL=OFF
.else
BUILD_DEPENDS+=	sphinx-build:${PORTSDIR}/textproc/py-sphinx
CMAKE_ARGS+=	-DOCIO_BUILD_DOCS:BOOL=ON
.endif

.if ${PORT_OPTIONS:MCLIAPPS}
USE_GL=		glew glut
CMAKE_ARGS+=	-DOCIO_BUILD_APPS:BOOL=ON
PLIST_SUB+=	CLIAPPS=""
.else
CMAKE_ARGS+=	-DOCIO_BUILD_APPS:BOOL=OFF
PLIST_SUB+=	CLIAPPS="@comment "
.endif

.if ${PORT_OPTIONS:MSSE}
CMAKE_ARGS+=	-DOCIO_USE_SSE:BOOL=ON
.else
CMAKE_ARGS+=	-DOCIO_USE_SSE:BOOL=OFF
.endif

.include <bsd.port.pre.mk>

.if ${CC:T} == "clang" && ${ARCH} == "i386"
# workaround for pr/165968
# may need to test osversion after fix is applied
CFLAGS+=	-march=pentium2
.endif

SPIDIR=${WRKSRC}/docs/configurations/images/spi-vfx
post-patch:
	${MV} ${SPIDIR}/gn10_to_linear_light.jpeg ${SPIDIR}/gn10_to_linear_light.jpg
	${MV} ${SPIDIR}/gnf_to_linear_light.jpeg ${SPIDIR}/gnf_to_linear_light.jpg
	${MV} ${SPIDIR}/lg10_to_linear_light.jpeg ${SPIDIR}/lg10_to_linear_light.jpg
	${MV} ${SPIDIR}/lg8_to_vd8.jpeg ${SPIDIR}/lg8_to_vd8.jpg
	${MV} ${SPIDIR}/lgf_to_linear_light.jpeg ${SPIDIR}/lgf_to_linear_light.jpg

post-install:
	cd ${PREFIX}/lib && ${LN} -sf libOpenColorIO.so.1.0.7 libOpenColorIO.so.1.0
	cd ${PYTHON_SITELIBDIR} && ${LN} -sf PyOpenColorIO.so.1.0.7 PyOpenColorIO.so.1.0

.include <bsd.port.post.mk>
