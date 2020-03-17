# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage17
PORTVERSION=	1.7.6
DISTVERSIONPREFIX=	Release-
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers

LICENSE=	BSD3CLAUSE

LLVM_VER=	35
BUILD_DEPENDS=	llvm-config${LLVM_VER}:devel/llvm${LLVM_VER} \
		clang${LLVM_VER}>=3.5:lang/clang${LLVM_VER}
LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libtinfo.so:devel/ncurses \
		libImath.so:graphics/ilmbase \
		libIlmImf.so:graphics/openexr \
		libOpenImageIO17.so:graphics/openimageio17
RUN_DEPENDS=	llvm-config${LLVM_VER}:devel/llvm${LLVM_VER}

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenShadingLanguage
PORTSCOUT=	ignore:1

CMAKE_ARGS=	-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config${LLVM_VER}" \
		-DENABLERTTI:BOOL=ON -DOSL_BUILD_CPP11:BOOL=ON \
		-DOSL_BUILD_CPP14:BOOL=OFF
USE_LDCONFIG=	yes
USES=		bison cmake compiler:c++11-lang

.include <bsd.port.options.mk>

.if ${ARCH} == powerpc
USE_GCC=	yes
.endif

.if ${OSVERSION} < 1000033
BUILD_DEPENDS+=	flex>=2.5.37:textproc/flex
CMAKE_ARGS+=	-DFLEX_EXECUTABLE:STRING=${LOCALBASE}/bin/flex
CXXFLAGS+=	-I${LOCALBASE}/include/flex
.endif

post-patch:
	@${REINPLACE_CMD} -e 's,/bin/bash,/bin/sh,' \
		${WRKSRC}/src/liboslexec/serialize-bc.bash
	@${FIND} ${WRKSRC} -name "*.cpp" -or -name "*.h" -or -name "*.l" | \
		${XARGS} ${REINPLACE_CMD} -e 's|OpenImageIO/|OpenImageIO17/|g'

post-install:
	@${REINPLACE_CMD} -e 's|OSL/|OSL17/|g' ${STAGEDIR}/${PREFIX}/include/OSL17/oslexec.h

.include <bsd.port.mk>
