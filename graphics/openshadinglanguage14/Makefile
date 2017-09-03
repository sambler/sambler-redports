# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage14
PORTVERSION=	1.4.2
DISTVERSIONPREFIX=	Release-
PORTREVISION=	1
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers (v1.4)

LICENSE=	BSD3CLAUSE

BROKEN=		Doesn't support boost 1.65

BUILD_DEPENDS=	llvm-config33:devel/llvm33 \
		clang33>=3.3_3:lang/clang33
LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libImath-2_2.so:graphics/ilmbase \
		libIlmImf.so:graphics/OpenEXR \
		libOpenImageIO14.so:graphics/openimageio14
RUN_DEPENDS=	llvm-config33:devel/llvm33

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenShadingLanguage
PORTSCOUT=	ignore:1

CMAKE_ARGS=	-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config33" \
		-DENABLERTTI:BOOL=ON
USE_LDCONFIG=	yes
USES=		bison cmake:outsource compiler:c++11-lib

.include <bsd.port.options.mk>

.if ${OSVERSION} < 1000033
BUILD_DEPENDS+=	flex>=2.5.37:textproc/flex
CMAKE_ARGS+=	-DFLEX_EXECUTABLE:STRING=${LOCALBASE}/bin/flex
CXXFLAGS+=	-I${LOCALBASE}/include/flex
.endif

post-patch:
	@${REINPLACE_CMD} -e 's,/bin/bash,/bin/sh,' \
		${WRKSRC}/src/liboslexec/serialize-bc.bash
	@${FIND} ${WRKSRC} -name "*.cpp" -or -name "*.h" -or -name "*.l" | \
		${XARGS} ${REINPLACE_CMD} -e 's|OpenImageIO/|OpenImageIO14/|g'

post-install:
	@${REINPLACE_CMD} -e 's|OSL/|OSL14/|g' ${STAGEDIR}/${PREFIX}/include/OSL14/oslexec.h
	@${FIND} ${STAGEDIR}/${PREFIX}/include/OSL14/ -name "*.bak" -delete

.include <bsd.port.mk>
