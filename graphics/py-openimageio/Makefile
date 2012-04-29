# New ports collection makefile for:	py-openimageio
# Date created:			28 April 2012
# Whom:					Shane Ambler
#
# $FreeBSD$
#

PORTNAME=	openimageio
PORTVERSION=	1.0.3
CATEGORIES=	graphics multimedia
MASTER_SITES=	https://github.com/OpenImageIO/oiio/tarball/
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTNAME=	Release-${PORTVERSION}
EXTRACT_SUFX=
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	OpenImageIO python bindings

LICENSE=	BSD

LIB_DEPENDS=	OpenImageIO.1:${PORTSDIR}/graphics/openimageio \
		boost_python:${PORTSDIR}/devel/boost-python-libs

FETCH_ARGS=	-pRr
USE_CMAKE=	yes
CMAKE_VERBOSE=	yes
CMAKE_OUTSOURCE=	yes
CMAKE_ARGS=	-DBUILDSTATIC:BOOL=OFF \
		-DLINKSTATIC:BOOL=OFF -DUSE_TBB:BOOL=ON \
		-DUSE_OPENGL:BOOL=OFF -DUSE_QT:BOOL=OFF \
		-DUSE_PYTHON:BOOL=ON
USE_PYTHON=	2.6+
LDFLAGS+=	-ltbb
USE_LDCONFIG=	yes
WRKSRC=		${WRKDIR}/OpenImageIO-oiio-2388ebf/src
MAKE_JOBS_SAFE=	yes

.include <bsd.port.pre.mk>

.if ${ARCH} == "i386" || ${OSVERSION} < 803000
USE_GCC=	4.6+
.endif

.if ${OSVERSION} < 800000
IGNORE=	requires FreeBSD 8.0 or higher
.endif

PLIST_FILES=	%%PYTHON_SITELIBDIR%%/OpenImageIO.so

post-patch:
	@${REINPLACE_CMD} 's|lib/python|lib/${PYTHON_VERSION}|' \
		${WRKSRC}/CMakeLists.txt

do-install:
	@${INSTALL_LIB}  ${BUILD_WRKSRC}/python/OpenImageIO.so ${PYTHON_SITELIBDIR}

.include <bsd.port.post.mk>
