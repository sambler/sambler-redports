# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD: ports/graphics/py-openimageio/Makefile,v 1.3 2012/09/17 05:24:02 rm Exp $

PORTNAME=	openimageio
CATEGORIES=	graphics multimedia python
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

COMMENT=	OpenImageIO python bindings

LICENSE=	BSD

LIB_DEPENDS=	OpenImageIO:${PORTSDIR}/graphics/openimageio \
		boost_python:${PORTSDIR}/devel/boost-python-libs

MASTERDIR=	${.CURDIR}/../openimageio

CMAKE_ARGS=	-DBUILDSTATIC:BOOL=OFF \
		-DLINKSTATIC:BOOL=OFF \
		-DNOTHREADS:BOOL=OFF \
		-DUSE_OPENGL:BOOL=OFF \
		-DUSE_PYTHON:BOOL=ON \
		-DUSE_QT:BOOL=OFF \
		-DUSE_TBB:BOOL=OFF

USE_PYTHON=	2.6+

OIIO_PYBIND=	yes

post-patch:
	@${REINPLACE_CMD} 's|lib/python|lib/${PYTHON_VERSION}|' ${WRKSRC}/CMakeLists.txt

do-install:
	${INSTALL_LIB} ${BUILD_WRKSRC}/python/OpenImageIO.so ${PYTHON_SITELIBDIR}/

.include "${MASTERDIR}/Makefile"
