# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage-dev
PORTVERSION=	1.8.4
DISTVERSIONPREFIX=	Release-
DISTVERSIONSUFFIX=	RC1
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS=	llvm-config40:devel/llvm40
LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libtinfo.so:devel/ncurses \
		libImath-2_2.so:graphics/ilmbase \
		libIlmImf.so:graphics/OpenEXR \
		libOpenImageIO.so:graphics/openimageio
RUN_DEPENDS=	llvm-config40:devel/llvm40

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
#GH_ACCOUNT=	lgritz
GH_PROJECT=	OpenShadingLanguage
GH_TAGNAME=	7b4de291160  #1.8 head
#GH_TAGNAME=	1e9bf2870d0  # master head
#GH_TAGNAME=	660f590db96  # lgritz clang-cpp - works
PORTSCOUT=	ignore:1

CMAKE_ARGS=	-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config40" \
		-DENABLERTTI:BOOL=OFF -DOSL_BUILD_CPP11:BOOL=ON \
		-DOSL_BUILD_CPP14:BOOL=OFF -DUSE_LLVM_BITCODE:BOOL=ON \
		-DUSE_LIBCPLUSPLUS:BOOL=ON -DOSL_BUILD_TESTS:BOOL=ON \
		-DUSE_BOOST_WAVE:BOOL=OFF
USE_LDCONFIG=	yes
USES=		bison cmake:outsource compiler:c++11-lib ncurses

CXXFLAGS=	-I${STAGEDIR}/include

post-patch:
	@${REINPLACE_CMD} -e 's,/bin/bash,/bin/sh,' \
		${WRKSRC}/src/liboslexec/serialize-bc.bash

post-install:
	@${FIND} ${STAGEDIR} -name "*.h" | \
		${XARGS} ${REINPLACE_CMD} -e 's|OSL/|OSL-dev/|g'
	@${FIND} ${STAGEDIR} -name "*.bak" -delete

.include <bsd.port.mk>
