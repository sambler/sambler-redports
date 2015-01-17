# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage14
PORTVERSION=	1.4.2
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers (v1.4)

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS=	llvm-config33:${PORTSDIR}/devel/llvm33 \
		clang33>=3.3_3:${PORTSDIR}/lang/clang33
LIB_DEPENDS=	libboost_thread.so:${PORTSDIR}/devel/boost-libs \
		libIlmImf.so:${PORTSDIR}/graphics/OpenEXR \
		libOpenImageIO14.so:${PORTSDIR}/graphics/openimageio14
RUN_DEPENDS=	llvm-config33:${PORTSDIR}/devel/llvm33

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenShadingLanguage
GH_TAGNAME=	Release-${PORTVERSION}
GH_COMMIT=	2c3574d

CMAKE_ARGS=	-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config33"
USE_LDCONFIG=	yes
USES=		bison cmake:outsource

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

.include <bsd.port.mk>
