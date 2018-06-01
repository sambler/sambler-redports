# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage18
PORTVERSION=	1.8.14
DISTVERSIONPREFIX=	Release-
PORTREVISION=	0
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS=	llvm-config40:devel/llvm40
LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libIlmImf.so:graphics/OpenEXR \
		libImath.so:graphics/ilmbase \
		libOpenImageIO.so:graphics/openimageio
RUN_DEPENDS=	llvm-config40:devel/llvm40

USES=		bison cmake:outsource compiler:c++11-lang ncurses
USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenShadingLanguage

CMAKE_ON=	ENABLERTTI
CMAKE_OFF=	USE_BOOST_WAVE
CMAKE_ARGS=	-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config40"
USE_LDCONFIG=	yes

PLIST_SUB+=	LIBVERS=${PORTVERSION}

post-patch:
	@${REINPLACE_CMD} -e 's,/bin/bash,/bin/sh,' \
		${WRKSRC}/src/liboslexec/serialize-bc.bash

post-install:
	@${FIND} ${STAGEDIR} -name "*.h" | \
		${XARGS} ${REINPLACE_CMD} -e 's|OSL/|OSL18/|g'
	@${FIND} ${STAGEDIR} -name "*.bak" -delete

.include <bsd.port.mk>