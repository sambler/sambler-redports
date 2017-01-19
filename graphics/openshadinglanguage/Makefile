# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage
PORTVERSION=	1.7.5
DISTVERSIONPREFIX=	Release-
PORTREVISION=	0
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS=	llvm-config34:devel/llvm34
LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libtinfo.so:devel/ncurses \
		libImath-2_2.so:graphics/ilmbase \
		libIlmImf.so:graphics/OpenEXR \
		libOpenImageIO.so:graphics/openimageio
RUN_DEPENDS=	llvm-config34:devel/llvm34

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenShadingLanguage

CMAKE_ARGS=	-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config34" \
		-DENABLERTTI:BOOL=ON -DOSL_BUILD_CPP11:BOOL=OFF \
		-DOSL_BUILD_CPP14:BOOL=OFF
USE_LDCONFIG=	yes
USES=		bison cmake:outsource

.include <bsd.port.options.mk>

.if ${ARCH} == powerpc
USE_GCC=	yes
.endif

.if ${OSVERSION} > 1200000
# llvm-as34 fails to build llvm_ops after clang 4 import
# disabling this option uses clang instead of llvm-as
CMAKE_ARGS+=  -DUSE_LLVM_BITCODE:BOOL=OFF
.endif

post-patch:
	@${REINPLACE_CMD} -e 's,/bin/bash,/bin/sh,' \
		${WRKSRC}/src/liboslexec/serialize-bc.bash

.include <bsd.port.mk>
