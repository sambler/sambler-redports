# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD: ports/graphics/opencolorio/Makefile,v 1.2 2012/11/17 05:58:15 svnexp Exp $

PORTNAME?=	opencolorio
PORTVERSION=	1.0.7
PORTREVISION?=	1
CATEGORIES=	graphics multimedia

MAINTAINER?=	FreeBSD@Shaneware.biz
COMMENT?=	Complete color management solution

LICENSE?=	BSD

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenColorIO
GH_TAGNAME=	v${PORTVERSION}
GH_COMMIT=	b3cb224

.if !defined(OCIO_TOOLS)
USE_PYTHON=	2.6+
USE_LDCONFIG=	yes
.endif
USE_CMAKE=	yes
CMAKE_VERBOSE=	yes
CMAKE_OUTSOURCE=	yes
CMAKE_ARGS?=	-DOCIO_BUILD_APPS:BOOL=OFF \
		-DOCIO_BUILD_JNIGLUE:BOOL=OFF \
		-DOCIO_BUILD_NUKE:BOOL=OFF \
		-DOCIO_BUILD_STATIC:BOOL=OFF \
		-DOCIO_BUILD_PYGLUE:BOOL=ON

MAKE_JOBS_SAFE?=	yes

PLIST=		${PKGDIR}/pkg-plist${PKGNAMESUFFIX}

.if !defined(OCIO_TOOLS)
OPTIONS_DEFINE=		DOCS SSE
OPTIONS_DEFAULT=	SSE
.endif

.include <bsd.port.options.mk>

.if empty(PORT_OPTIONS:MDOCS) || defined(OCIO_TOOLS)
CMAKE_ARGS+=	-DOCIO_BUILD_DOCS:BOOL=OFF
.else
CMAKE_ARGS+=	-DOCIO_BUILD_DOCS:BOOL=ON
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

.include <bsd.port.post.mk>
