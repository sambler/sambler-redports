# New ports collection makefile for:	LuxRender
# Date created:			29 November 2011
# Whom:					Shane Ambler
#
# $FreeBSD$
#

PORTNAME=	luxrender
PORTVERSION=	1.0.0.RC1.20120418
CATEGORIES=	graphics
MASTER_SITES=	http://src.luxrender.net/lux/archive/ \
				http://bitbucket.org/luxrender/lux/get/
DISTNAME=	${HG_NODEID}
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	FreeBSD@ShaneWare.Biz
COMMENT=	A physically based and unbiased rendering system

LICENSE=	GPLv3

BUILD_DEPENDS=	${LOCALBASE}/lib/libfreeimage.a:${PORTSDIR}/graphics/freeimage \
				${LOCALBASE}/lib/libluxrays.a:${PORTSDIR}/graphics/luxrays \
				bison:${PORTSDIR}/devel/bison \
				flex:${PORTSDIR}/textproc/flex
LIB_DEPENDS=	boost_thread.4:${PORTSDIR}/devel/boost-libs \
				boost_python.4:${PORTSDIR}/devel/boost-python-libs \
				IlmImf.6:${PORTSDIR}/graphics/OpenEXR

# recent snapshot - 2012-04-18
HG_NODEID=	d6255950ebd0

USE_BZIP2=	yes
USE_BISON=	build
USE_CMAKE=	yes
USE_GL=		gl
CMAKE_VERBOSE=	yes
CMAKE_OUTSOURCE=	yes
CMAKE_ARGS=	-DLUXRAYS_DISABLE_OPENCL:BOOL=ON
CMAKE_ARGS+=	-DLUX_NO_LIBPNG:BOOL=ON
.if defined(PREFIX) && ${PREFIX} != ""
CMAKE_ARGS+=	-DTARGETROOT:STRING=${PREFIX}
.else
CMAKE_ARGS+=	-DTARGETROOT:STRING=${LOCALBASE}
.endif
WRKSRC=		${WRKDIR}/lux-${HG_NODEID}
MAKE_JOBS_SAFE=	yes

OPTIONS=	DOCS "Build API docs"                 off

# There no longer appears to be a configure option to prevent the qt gui building
# QT4	"Build Qt4 GUI executable"          on \

# while the source for the wx gui appears to still exist
# there is no longer an option to configure it to be built
# WX	"Build wxWidgets GUI executable"    off \

.include <bsd.port.options.mk>

.if defined(WITH_DOCS)
PLIST_SUB+=	LUXDOCS=""
CMAKE_ARGS+=	-DLUX_DOCUMENTATION=ON
.else
PLIST_SUB+=	LUXDOCS="@comment "
CMAKE_ARGS+=	-DLUX_DOCUMENTATION=OFF
.endif

USE_QT_VER=	4
QT_COMPONENTS=	moc_build qmake_build rcc_build uic_build corelib gui

post-patch:
# Prevent appending `64' suffix to `lib' directory on amd64
# do not install vendor .desktop file
	@${REINPLACE_CMD} -e '/LIB_SUFFIX 64/d ; /luxrender\.desktop/d' ${WRKSRC}/CMakeLists.txt

.if ${CC:T} == "clang"
# remove some flags that clang doesn't use
# just removes warnings
	@${REINPLACE_CMD} -e '/-mfpmath=sse/d ; /-ftree-vectorize/d' ${WRKSRC}/CMakeLists.txt
.endif

.include <bsd.port.pre.mk>

# this is carried over from luxrender 0.7 - still applies??
# the CMakeLists.txt appears to recognise ppc but not used elsewhere
.if ${ARCH} == "ia64" || ${ARCH} == "powerpc" || ${ARCH} == "sparc64"
BROKEN=		Does not compile4: uses i386-specific options
.endif

.include <bsd.port.post.mk>
