# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage
PORTVERSION=	1.9.8
DISTVERSIONPREFIX=	Release-
PORTREVISION=	0
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS=	llvm-config40:devel/llvm40
LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libtinfo.so:devel/ncurses \
		libImath-2_2.so:graphics/ilmbase \
		libIlmImf.so:graphics/OpenEXR \
		libOpenImageIO.so:graphics/openimageio \
		libpugixml.so:textproc/pugixml
RUN_DEPENDS=	llvm-config40:devel/llvm40

USES=		bison cmake:outsource compiler:c++11-lib ncurses python:build
USE_LDCONFIG=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenShadingLanguage

CMAKE_ON=	ENABLERTTI OSL_BUILD_TESTS USE_LLVM_BITCODE USE_LIBCPLUSPLUS
CMAKE_OFF=	USE_BOOST_WAVE #LLVM_FIND_QUIETLY BUILDSTATIC LINKSTATIC
CMAKE_ARGS=	-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config40" \
		-DCMAKE_INSTALL_DOCDIR:STRING=${DOCSDIR} \
		-DUSE_CPP:STRING=11

CXXFLAGS+=	-I${STAGEDIR}/include

PLIST_SUB+=	LIBVERS=${PORTVERSION}

post-patch:
	@${REINPLACE_CMD} -e 's,/bin/bash,/bin/sh,' \
		${WRKSRC}/src/liboslexec/serialize-bc.bash
	@${REINPLACE_CMD} -e 's,%%DATADIR%%,${DATADIR},' \
		-e 's,%%PYCMD%%,${PYTHON_CMD},' \
		${WRKSRC}/src/shaders/CMakeLists.txt \
		${WRKSRC}/src/shaders/MaterialX/CMakeLists.txt

.include <bsd.port.mk>
