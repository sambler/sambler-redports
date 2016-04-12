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

BUILD_DEPENDS=	eigen>0:math/eigen3 \
		${PYTHON_PKGNAMEPREFIX}matplotlib>=0:math/py-matplotlib \
		swig2.0:devel/swig20 \
		doxygen:devel/doxygen
LIB_DEPENDS=	libTKernel.so:cad/opencascade \
		libboost_thread.so:devel/boost-libs \
		libfreetype.so:print/freetype2 \
		libxerces-c.so:textproc/xerces-c3 \
		libCoin.so:graphics/Coin \
		libsysinfo.so:devel/libsysinfo \
		libSoQt.so:x11-toolkits/soqt
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}matplotlib>=0:math/py-matplotlib

USES=		cmake:outsource fortran python
USE_QT4=	gui opengl qmake
USE_XORG=	x11 ice
USE_GL=		glu
CMAKE_ARGS=	-DOCC_INCLUDE_DIR:STRING=${LOCALBASE}/include/OpenCASCADE
CFLAGS+=	-fPIC
CXXFLAGS+=	-fPIC
LDFLAGS+= -lc
#CMAKE_VERBOSE=yes
OPTIONS_DEFINE=	DOCS
#USE_GCC=yes

.include <bsd.port.mk>
