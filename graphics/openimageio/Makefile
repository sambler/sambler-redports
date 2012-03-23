# New ports collection makefile for:	OpenImageIO
# Date created:			21 March 2012
# Whom:					Shane Ambler
#
# $FreeBSD$
#

PORTNAME=	openimageio
PORTVERSION=	1.0.2
CATEGORIES=	graphics multimedia
MASTER_SITES=	https://github.com/OpenImageIO/oiio/tarball/
DISTFILES=	Release-${PORTVERSION}
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	OpenImageIO graphics library

FETCH_ARGS=	-pRr

LICENSE=	BSD

LIB_DEPENDS=	openjpeg:${PORTSDIR}/graphics/openjpeg \
				opencv_legacy.2:${PORTSDIR}/graphics/opencv \
				boost_thread.4:${PORTSDIR}/devel/boost-libs

USE_CMAKE=	yes
CMAKE_VERBOSE=	yes
CMAKE_OUTSOURCE=	yes
CMAKE_ARGS=	-DBUILDSTATIC:BOOL=OFF \
			-DLINKSTATIC:BOOL=OFF \
			-DUSE_TBB:BOOL=OFF
# TBB included is too old - maybe patch for port version?

WRKSRC=		${WRKDIR}/OpenImageIO-oiio-1595432/src
MAKE_JOBS_SAFE=	yes

OPTIONS=	OPENGL "Include OpenGL support" on \
			PYTHON "Python bindings"  on \
			QT "Include QT Support" on \
			NOTHREADS "Disable thread support" off

#.include <bsd.port.options.mk>

.if defined(WITH_OPENGL)
CMAKE_ARGS+=	-DUSE_OPENGL:BOOL=ON
USE_GL=		gl
.else
CMAKE_ARGS+=	-DUSE_OPENGL:BOOL=OFF
.endif

.if defined(WITH_PYTHON)
CMAKE_ARGS+=	-DUSE_PYTHON:BOOL=ON
USE_PYTHON=	2.6+
.else
CMAKE_ARGS+=	-DUSE_PYTHON:BOOL=OFF
.endif

.if defined(WITH_QT)
CMAKE_ARGS+=	-DUSE_QT:BOOL=ON
USE_QT_VER=	4
QT_COMPONENTS=	moc_build corelib 
.else
CMAKE_ARGS+=	-DUSE_QT:BOOL=OFF
.endif

.if defined(WITH_NOTHREADS)
CMAKE_ARGS+=	-DNOTHREADS:BOOL=ON
.else
CMAKE_ARGS+=	-DNOTHREADS:BOOL=OFF
.endif

#.include <bsd.port.pre.mk>

#.include <bsd.port.post.mk>
.include <bsd.port.mk>
