# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	alembic
PORTVERSION=	1.5.8
CATEGORIES?=	graphics devel
MASTER_SITES=	http://alembic.googlecode.com/archive/
DISTNAME=	1_05_08
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Open computer graphics interchange framework

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS=	/usr/local/lib/libboost_python.a:${PORTSDIR}/devel/boost-python-libs
LIB_DEPENDS=	libboost_thread.so:${PORTSDIR}/devel/boost-libs \
		libIlmImf.so:${PORTSDIR}/graphics/OpenEXR \
		libhdf5.so:${PORTSDIR}/science/hdf5

WRKSRC=		${WRKDIR}/${PORTNAME}-${DISTNAME}

USES=		cmake:outsource python:build shebangfix compiler:c++11-lib
USE_XORG=	x11 xext
USE_GL=		glew glut
LDFLAGS=	-L${LOCALBASE}/lib

CMAKE_ARGS+=	-DUSE_PYALEMBIC:BOOL=OFF
SHEBANG_FILES=	build/CopyScriptFile.py build/bootstrap/alembic_bootstrap.py \
		lib/python/abcutils/CMakeCache.py lib/python/abcutils/Path.py

#OPTIONS_DEFINE=		PYTHON

#PYTHON_CMAKE_ON=	-DUSE_PYALEMBIC:BOOL=ON
#PYTHON_CMAKE_OFF=	-DUSE_PYALEMBIC:BOOL=OFF
#PYTHON_BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}openexr>0:${PORTSDIR}/graphics/py-openexr
#PYTHON_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}openexr>0:${PORTSDIR}/graphics/py-openexr

.include <bsd.port.pre.mk>

.if ${ARCH} == i386
CFLAGS+= -march=i586
.endif

post-install:
	@${MV} ${STAGEDIR}/${PREFIX}/lib/static/* ${STAGEDIR}/${PREFIX}/lib/
	@${RMDIR} ${STAGEDIR}/${PREFIX}/lib/static

.include <bsd.port.post.mk>
