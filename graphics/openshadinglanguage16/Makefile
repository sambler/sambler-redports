# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage16
PORTVERSION=	1.6.9
PORTREVISION=	2
DISTVERSIONPREFIX=	Release-
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS=	llvm-config35:devel/llvm35 \
		clang35>=3.5:lang/clang35
LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libImath.so:graphics/ilmbase \
		libIlmImf.so:graphics/openexr \
		libOpenImageIO16.so:graphics/openimageio16
RUN_DEPENDS=	llvm-config35:devel/llvm35

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenShadingLanguage
PORTSCOUT=	ignore:1

CMAKE_ARGS=	-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config35" \
		-DENABLERTTI:BOOL=ON -DOSL_BUILD_CPP11:BOOL=ON \
		-DOSL_BUILD_LIBCPLUSPLUS:BOOL=ON
USE_LDCONFIG=	yes
USES=		bison cmake:outsource compiler:c++11-lang

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
		${XARGS} ${REINPLACE_CMD} -e 's|OpenImageIO/|OpenImageIO16/|g'

post-install:
	@${REINPLACE_CMD} -e 's|OSL/|OSL16/|g' ${STAGEDIR}/${PREFIX}/include/OSL16/oslexec.h
	@${FIND} ${STAGEDIR}/${PREFIX}/include/OSL16/ -name "*.bak" -delete

.include <bsd.port.mk>
