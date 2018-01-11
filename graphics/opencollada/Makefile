# $FreeBSD$

PORTNAME=	opencollada
DISTVERSIONPREFIX=	v
DISTVERSION=	1.6.61
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@ShaneWare.Biz
COMMENT=	Library for reading and writing COLLADA files

LICENSE=	MIT

BROKEN_powerpc64=	Does not build: c++: Internal error: Killed (program cc1plus)
BROKEN_sparc64=		cannot build: runaway process

LIB_DEPENDS=	libpcre.so:devel/pcre

USE_GITHUB=	yes
GH_ACCOUNT=	KhronosGroup
GH_PROJECT=	OpenCOLLADA

USES=		cmake:outsource iconv pkgconfig localbase
USE_GNOME=	libxml2
USE_LDCONFIG=	${PREFIX}/lib/opencollada
CMAKE_ON=	USE_SHARED
CMAKE_OFF=	USE_STATIC

post-patch:
	@${REINPLACE_CMD} -e 's|$${OPENCOLLADA_INST_LIBRARY}/cmake|${PREFIX}/share/cmake/Modules|' \
		${WRKSRC}/CMakeLists.txt

.include <bsd.port.mk>
