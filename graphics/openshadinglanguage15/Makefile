# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage15
PORTVERSION=	1.5.12
DISTVERSIONPREFIX=	Release-
PORTREVISION=	1
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers (v1.5)

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS=	llvm-config34:${PORTSDIR}/devel/llvm34 \
		clang34>=3.4_1:${PORTSDIR}/lang/clang34
LIB_DEPENDS=	libboost_thread.so:${PORTSDIR}/devel/boost-libs \
		libIlmImf.so:${PORTSDIR}/graphics/OpenEXR \
		libOpenImageIO14.so:${PORTSDIR}/graphics/openimageio14
RUN_DEPENDS=	llvm-config34:${PORTSDIR}/devel/llvm34

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenShadingLanguage

CMAKE_ARGS=	-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config34" \
		-DENABLERTTI:BOOL=ON
USE_LDCONFIG=	yes
USES=		bison cmake:outsource compiler:c++11-lib

.include <bsd.port.options.mk>

.if ${OSVERSION} < 1000033
BUILD_DEPENDS+=	flex>=2.5.37:${PORTSDIR}/textproc/flex
CMAKE_ARGS+=	-DFLEX_EXECUTABLE:STRING=${LOCALBASE}/bin/flex
CXXFLAGS+=	-I${LOCALBASE}/include/flex
.endif

post-patch:
	@${REINPLACE_CMD} -e 's,/bin/bash,/bin/sh,' \
		${WRKSRC}/src/liboslexec/serialize-bc.bash
	@${FIND} ${WRKSRC} -name "*.cpp" -or -name "*.h" -or -name "*.l" | \
		${XARGS} ${REINPLACE_CMD} -e 's|OpenImageIO/|OpenImageIO14/|g'

post-install:
	@${REINPLACE_CMD} -e 's|OSL/|OSL15/|g' ${STAGEDIR}/${PREFIX}/include/OSL15/oslexec.h
	@${FIND} ${STAGEDIR}/${PREFIX}/include/OSL15/ -name "*.bak" -delete

.include <bsd.port.mk>
