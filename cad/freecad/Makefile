# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	freecad
PORTVERSION=	0.14.3702
CATEGORIES=	cad
MASTER_SITES=	SF/free-cad/FreeCAD%20Source/:source \
		SF/free-cad/FreeCAD%20Documentation/:docs
DISTFILES=	${PORTNAME}-${PORTVERSION}${EXTRACT_SUFX}:source \
		FreeCAD-014.pdf:docs
EXTRACT_ONLY=	${PORTNAME}-${PORTVERSION}${EXTRACT_SUFX}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Parametric 3D modeler

LICENSE=	LGPL20

BUILD_DEPENDS=	eigen>0:${PORTSDIR}/math/eigen3 \
		${PYTHON_PKGNAMEPREFIX}matplotlib>=0:${PORTSDIR}/math/py-matplotlib \
		swig2.0:${PORTSDIR}/devel/swig20 \
		doxygen:${PORTSDIR}/devel/doxygen
LIB_DEPENDS=	libTKernel.so:${PORTSDIR}/cad/opencascade \
		libboost_thread.so:${PORTSDIR}/devel/boost-libs \
		libfreetype.so:${PORTSDIR}/print/freetype2 \
		libxerces-c.so:${PORTSDIR}/textproc/xerces-c3 \
		libCoin.so:${PORTSDIR}/graphics/Coin \
		libsysinfo.so:${PORTSDIR}/devel/libsysinfo \
		libSoQt.so:${PORTSDIR}/x11-toolkits/soqt
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}matplotlib>=0:${PORTSDIR}/math/py-matplotlib

USES=		cmake:outsource fortran
USE_PYTHON=	yes
USE_QT4=	gui opengl qmake
USE_XORG=	x11 ice
USE_GL=		glu
CMAKE_ARGS=	-DOCC_INCLUDE_DIR:STRING=${LOCALBASE}/include/OpenCASCADE
CFLAGS+=	-fPIC
CXXFLAGS+=	-fPIC
#CMAKE_VERBOSE=yes
OPTIONS_DEFINE=	DOCS

.include <bsd.port.mk>
