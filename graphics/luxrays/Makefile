# New ports collection makefile for:	LuxRays
# Date created:			29 November 2011
# Whom:					Shane Ambler
#
# $FreeBSD$
#

PORTNAME=	luxrays
PORTVERSION=	0.9.0.20120225
CATEGORIES=	graphics
MASTER_SITES=	http://src.luxrender.net/luxrays/archive/ \
				http://bitbucket.org/luxrender/luxrays/get/
DISTNAME=	${HG_NODEID}
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Library part of the LuxRender system

LICENSE=	GPLv3

BUILD_DEPENDS=	${LOCALBASE}/lib/libfreeimage.a:${PORTSDIR}/graphics/freeimage
LIB_DEPENDS=	boost_thread.4:${PORTSDIR}/devel/boost-libs \
				execinfo.1:${PORTSDIR}/devel/libexecinfo

# libexecinfo for backtrace - seems popular port so depend it instead of patching out

# recent snapshot - 2012-02-25
HG_NODEID=	ebf26469123e

USE_BZIP2=	yes
USE_CMAKE=	yes
CMAKE_VERBOSE=	yes
CMAKE_OUTSOURCE=	yes
# no opencl support on freebsd??
CMAKE_ARGS=	-DLUXRAYS_DISABLE_OPENCL:BOOL=ON
.if defined(PREFIX) && ${PREFIX} != ""
CMAKE_ARGS+=	-DTARGETROOT:STRING=${PREFIX}
.else
CMAKE_ARGS+=	-DTARGETROOT:STRING=${LOCALBASE}
.endif

WRKSRC=	${WRKDIR}/luxrays-${HG_NODEID}
MAKE_JOBS_SAFE=	yes

OPTIONS=	SSSE3 "Enable SSSE3 optimisation"   on

.include <bsd.port.options.mk>

# luxrays standard setup has dev specified optimisations
# this change is to allow build on x86 machines without ssse3
# this replaces settings removed by patch-cmake-PlatformSpecific.cmake
.if defined(WITH_DEBUG)
CFLAGS+=	-Wall -msse -msse2 -msse3 -fPIC -O0 -g
CXXFLAGS+=	-Wall -msse -msse2 -msse3 -fPIC -O0 -g
.else
CFLAGS+=	-DNDEBUG -Wall -fPIC -O3 -ftree-vectorize -msse -msse2 -msse3 -fvariable-expansion-in-unroller
CXXFLAGS+=	-DNDEBUG -Wall -fPIC -O3 -ftree-vectorize -msse -msse2 -msse3 -fvariable-expansion-in-unroller
.endif

.if defined(WITH_SSSE3)
CFLAGS+=	-mssse3
CXXFLAGS+=	-mssse3
.endif

LDFLAGS+=	-lpthread -lexecinfo

post-patch:
# cmake is set to copy entire folder - remove patched orig
# - instead of adjusting cmake to list files
	@${RM} -f ${WRKSRC}/include/luxrays/core/utils.h.orig

.include <bsd.port.pre.mk>

# this is carried over from luxrender 0.7 - still applies??
.if ${ARCH} == "ia64" || ${ARCH} == "powerpc" || ${ARCH} == "sparc64"
BROKEN=		Does not compile4: uses i386-specific options
.endif

.include <bsd.port.post.mk>
