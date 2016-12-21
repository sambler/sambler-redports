# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage-dev
PORTVERSION=	1.8.2
DISTVERSIONPREFIX=	Release-
DISTVERSIONSUFFIX=	dev
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS=	llvm-config36:devel/llvm36 \
		clang36:lang/clang36
LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libtinfo.so:devel/ncurses \
		libImath-2_2.so:graphics/ilmbase \
		libIlmImf.so:graphics/OpenEXR \
		libOpenImageIO.so:graphics/openimageio
RUN_DEPENDS=	llvm-config36:devel/llvm36

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenShadingLanguage

CMAKE_ARGS=	-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config36" \
		-DENABLERTTI:BOOL=ON -DOSL_BUILD_CPP11:BOOL=OFF \
		-DOSL_BUILD_CPP14:BOOL=OFF 
USE_LDCONFIG=	yes
USES=		bison cmake:outsource compiler:c++11-lang

.include <bsd.port.options.mk>

.if ${ARCH} == powerpc
USE_GCC=	yes
.endif

.if ${OSVERSION} < 1000033
BUILD_DEPENDS+=	flex>=2.5.37:textproc/flex
CMAKE_ARGS+=	-DFLEX_EXECUTABLE:STRING=${LOCALBASE}/bin/flex
CXXFLAGS+=	-I${LOCALBASE}/include/flex -I${LOCALBASE}/include/c++/v1
LIB_DEPENDS+=	libc++.so.1:devel/libc++
.endif

post-patch:
	@${REINPLACE_CMD} -e 's,/bin/bash,/bin/sh,' \
		${WRKSRC}/src/liboslexec/serialize-bc.bash

.include <bsd.port.mk>
