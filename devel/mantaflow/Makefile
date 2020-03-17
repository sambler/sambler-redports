# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	mantaflow
PORTVERSION=	0.12
CATEGORIES=	devel math
MASTER_SITES=	http://mantaflow.com/download/
DISTNAME=	manta-src-0.12

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Framework targeted at fluid simulation research

LICENSE=	GPLv3

USES=		cmake gl python:3.6
USE_GL=		gl glu

WRKSRC=		${WRKDIR}/manta_0_12

CMAKE_OFF=	OPENVDB

OPTIONS_DEFINE=	DBLPRES GUI NUMPY
OPTIONS_RADIO=	PARALLEL
OPTIONS_RADIO_PARALLEL=	OPENMP TBB
OPTIONS_DEFAULT= GUI NUMPY TBB

OPTIONS_SUB=	yes
DBLPRES_DESC=	Enable double precision (experimental)
GUI_DESC=	Build Qt GUI
PARALLEL_DESC=	Parallel Processing
TBB_DESC=	Parallel processing support via Intels TBB

DBLPRES_CMAKE_BOOL=	DOUBLEPRECISION

GUI_CMAKE_BOOL=		GUI
GUI_USES=		qt:5
GUI_USE=		QT=buildtools,core,gui,opengl,qmake_build,widgets

OPENMP_CMAKE_BOOL=	OPENMP
OPENMP_USES=		compiler:openmp

NUMPY_CMAKE_BOOL=	NUMPY
NUMPY_BUILD_DEPENDS=	${PYNUMPY}
NUMPY_RUN_DEPENDS=	${PYNUMPY}

TBB_CMAKE_BOOL=		TBB
TBB_LIB_DEPENDS=	libtbb.so:devel/tbb
TBB_USES=		localbase:ldflags

PLIST_FILES=		bin/manta

.include <bsd.port.pre.mk>

CMAKE_ARGS+=	-DPYTHON_VERSION=${PYTHON_VER}

post-patch:
	${FIND} ${WRKSRC} -name "\._*" -delete

do-install:
	${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/manta \
		${STAGEDIR}/${PREFIX}/bin/

.include <bsd.port.post.mk>
