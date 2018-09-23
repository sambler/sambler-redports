# $FreeBSD$

PORTNAME=	opencollada
DISTVERSIONPREFIX=	v
DISTVERSION=	1.6.63
PORTREVISION=	1
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@ShaneWare.Biz
COMMENT=	Library for reading and writing COLLADA files

LICENSE=	MIT

BROKEN_sparc64=	cannot build: runaway process

LIB_DEPENDS=	libpcre.so:devel/pcre

USES=		cmake:outsource compiler:c++11-lib  dos2unix iconv pkgconfig

USE_GITHUB=	yes
GH_ACCOUNT=	KhronosGroup
GH_PROJECT=	OpenCOLLADA

USE_GNOME=	libxml2
USE_LDCONFIG=	${PREFIX}/lib/opencollada
CFLAGS+=	-I/${LOCALBASE}/include -Wno-narrowing
CMAKE_ON=	USE_SHARED
CMAKE_OFF=	USE_STATIC

post-patch:
	@${REINPLACE_CMD} -e 's|$${OPENCOLLADA_INST_LIBRARY}/cmake|${PREFIX}/share/cmake/Modules|' \
		${WRKSRC}/CMakeLists.txt
	@${REINPLACE_CMD} -e 's|real_pcre|real_pcre8_or_16|' \
		${WRKSRC}/COLLADABaseUtils/include/COLLADABUPcreCompiledPattern.h

.include <bsd.port.mk>
