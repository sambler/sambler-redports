# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	opensubdiv
PORTVERSION=	3.0.2
CATEGORIES?=	graphics

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	OpenSubdiv graphics library

LICENSE=	APACHE20

BUILD_DEPENDS=	glfw>2.7.0:${PORTSDIR}/graphics/glfw
LIB_DEPENDS=	libtbb.so:${PORTSDIR}/devel/tbb

USE_GITHUB=	yes
GH_ACCOUNT=	PixarAnimationStudios
GH_PROJECT=	OpenSubdiv
GH_TAGNAME=	v3_0_2

USE_GL=		glew
USE_XORG=	x11 xext xi xrandr ice xcursor xinerama
# gcc works while clang needs ldflags added
LDFLAGS+=	-L${LOCALBASE}/lib -lX11

USE_LDCONFIG=	yes
USES=		cmake:outsource
CMAKE_ARGS+=	-DNO_CUDA:BOOL=ON \
		-DNO_OPENCL:BOOL=ON

OPTIONS_DEFINE=		DOCS EXAMPLES OPENMP PTEX TEST
OPTIONS_DEFAULT=	PTEX
OPTIONS_SUB=		yes

DOCS_CMAKE_ON=		-DNO_DOC:BOOL=OFF
DOCS_CMAKE_OFF=		-DNO_DOC:BOOL=ON
DOCS_BUILD_DEPENDS=	rst2html.py:${PORTSDIR}/textproc/py-docutils \
			doxygen>=1.8.4:${PORTSDIR}/devel/doxygen

EXAMPLES_CMAKE_ON=	-DNO_EXAMPLES:BOOL=OFF
EXAMPLES_CMAKE_OFF=	-DNO_EXAMPLES:BOOL=ON

OPENMP_CMAKE_ON=	-DNO_OMP:BOOL=OFF
OPENMP_CMAKE_OFF=	-DNO_OMP:BOOL=ON
OPENMP_USES=		compiler:openmp

PTEX_DESC=		ptex support
PTEX_CMAKE_ON=		-DPTEX_LOCATION:STRING=/usr/local \
			-DPTEX_INCLUDE_DIR:STRING=/usr/local/include/ptex
PTEX_LIB_DEPENDS=	libPtex.so:${PORTSDIR}/graphics/ptex
PTEX_LDFLAGS=		-L${LOCALBASE}/lib -lPtex

TEST_CMAKE_ON=		-DNO_REGRESSION:BOOL=OFF
TEST_CMAKE_OFF=		-DNO_REGRESSION:BOOL=ON

PLIST_SUB+=		LIBVERS=${PORTVERSION}

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MPTEX} && ${PORT_OPTIONS:MOPENMP}
# ptex and opensubdiv need to both be compiled with the same compiler
# By default on 10.0+ ptex will be compiled with clang
# so far gcc is needed to enable openmp
BROKEN= openmp and ptex fail to link together.
.endif

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
