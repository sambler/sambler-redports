# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	mantaflow
PORTVERSION=	0.6
CATEGORIES=	devel math
MASTER_SITES=	http://mantaflow.com/download/
DISTFILES=	manta-src-0.6.tar

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	A framework targeted at fluid simulation research

LICENSE=	GPLv3

USES=		cmake:outsource shebangfix
SHEBANG_FILES=	tools/makeHgVersion.py
WRKSRC=		${WRKDIR}/${PORTNAME}
USE_PYTHON=	3.4
CMAKE_ARGS=	-DCUDA:BOOL=OFF -DDOUBLEPRECISION:BOOL=OFF
CMAKE_ARGS+=	-DPYTHON_INCLUDE_DIR:STRING=${PYTHON_INCLUDEDIR}
CMAKE_ARGS+=	-DPYTHON_LIBRARY:STRING=${PYTHONBASE}/lib/libpython3.4m.so
CXXFLAGS+=	-I${LOCALBASE}/include

OPTIONS_DEFINE=	DOCS GUI
OPTIONS_RADIO=	PARALLEL
OPTIONS_RADIO_PARALLEL=	OPENMP TBB 
OPTIONS_DEFAULT= DOCS TBB

OPTIONS_SUB=	yes
GUI_DESC=	Build qt4 interface
PARALLEL_DESC=	Parallel Processing
TBB_DESC=		Parallel processing support via Intels TBB

DOCS_BUILD_DEPENDS=	doxygen:${PORTSDIR}/devel/doxygen

OPENMP_CMAKE_ON=	-DOPENMP:BOOL=ON
OPENMP_CMAKE_OFF=	-DOPENMP:BOOL=OFF
OPENMP_USES=		compiler:openmp

TBB_CMAKE_ON=		-DTBB:BOOL=ON
TBB_CMAKE_OFF=		-DTBB:BOOL=OFF
TBB_LIB_DEPENDS=	libtbb.so:${PORTSDIR}/devel/tbb
TBB_LDFLAGS=		-L${LOCALBASE}/lib

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MGUI}
USE_QT4=	corelib gui
# opengl qmake_build moc_build rcc_build uic_build
CMAKE_ARGS+=	-DGUI:BOOL=ON
.else
CMAKE_ARGS+=	-DGUI:BOOL=OFF
.endif

.include <bsd.port.pre.mk>

.if ${ARCH} != amd64
# should this test include other 64bit arches?
CMAKE_ARGS+= -DUSE64:BOOL=OFF
.endif

post-patch:
	${FIND} ${WRKSRC} -name "\._*" -delete

do-install:
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/manta \
		${STAGEDIR}/${PREFIX}/bin/

.include <bsd.port.post.mk>