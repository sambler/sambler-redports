# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	opensubdiv
PORTVERSION=	2.6.1
CATEGORIES?=	graphics

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	OpenSubdiv graphics library

LICENSE=	APACHE20

BUILD_DEPENDS=	glfw>2.7.0:${PORTSDIR}/graphics/glfw
LIB_DEPENDS=	libtbb.so:${PORTSDIR}/devel/tbb

USE_GITHUB=	yes
GH_ACCOUNT=	PixarAnimationStudios
GH_PROJECT=	OpenSubdiv
GH_TAGNAME=	v2_6_1
GH_COMMIT=	c042af6

# use gcc for openmp
USE_GCC=	yes
USE_GL=		glew
USE_XORG=	x11 xext xi ice
USE_LDCONFIG=	yes
USES=		cmake:outsource
CMAKE_ARGS+=	-DNO_CUDA:BOOL=ON \
		-DNO_OPENCL:BOOL=ON \
		-DNO_CLEW:BOOL=ON

OPTIONS_DEFINE=		DOCS EXAMPLES PYTHON TEST
OPTIONS_DEFAULT=	PYTHON
OPTIONS_SUB=		yes

DOCS_CMAKE_ON=		-DNO_DOC:BOOL=OFF
DOCS_CMAKE_OFF=		-DNO_DOC:BOOL=ON
DOCS_BUILD_DEPENDS=	rst2html.py:${PORTSDIR}/textproc/py-docutils \
			doxygen>=1.8.4:${PORTSDIR}/devel/doxygen

EXAMPLES_CMAKE_ON=	-DNO_EXAMPLES:BOOL=OFF
EXAMPLES_CMAKE_OFF=	-DNO_EXAMPLES:BOOL=ON

PYTHON_CMAKE_ON=	-DNO_PYTHON:BOOL=OFF
PYTHON_CMAKE_OFF=	-DNO_PYTHON:BOOL=ON
PYTHON_USES=		python:2.7
PYTHON_BUILD_DEPENDS=	swig:${PORTSDIR}/devel/swig13 \
			${PYTHON_PKGNAMEPREFIX}numpy>=0:${PORTSDIR}/math/py-numpy
PYTHON_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}numpy>=0:${PORTSDIR}/math/py-numpy

TEST_CMAKE_ON=		-DNO_REGRESSION:BOOL=OFF
TEST_CMAKE_OFF=		-DNO_REGRESSION:BOOL=ON

PYSCRIPTS=__init__.py adapters.py common.py shim.py subdivider.py topology.py

.include <bsd.port.options.mk>

post-install:
.if ${PORT_OPTIONS:MPYTHON}
	@${MKDIR} ${STAGEDIR}${PYTHON_SITELIBDIR}/osd
.for SN in ${PYSCRIPTS}
	${INSTALL_DATA} ${BUILD_WRKSRC}/python/osd/${SN} \
		${STAGEDIR}${PYTHON_SITELIBDIR}/osd
.endfor
	${INSTALL_LIB} ${BUILD_WRKSRC}/python/osd/_shim.so \
		${STAGEDIR}${PYTHON_SITELIBDIR}/osd
.endif

.include <bsd.port.mk>
