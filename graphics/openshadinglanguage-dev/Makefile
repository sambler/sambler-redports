# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage_dev
PORTVERSION=	1.10.0
DISTVERSIONPREFIX=	Release-
DISTVERSIONSUFFIX=	dev
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS=	llvm-config60:devel/llvm60
LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libtinfo.so:devel/ncurses \
		libImath-2_2.so:graphics/ilmbase \
		libIlmImf.so:graphics/OpenEXR \
		libOpenImageIO.so:graphics/openimageio \
		libpugixml.so:textproc/pugixml
RUN_DEPENDS=	llvm-config60:devel/llvm60

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenShadingLanguage
GH_TAGNAME=	d5953937281e  # 30/5
PORTSCOUT=	ignore:1

CMAKE_ON=	ENABLERTTI USE_LIBCPLUSPLUS USE_LLVM_BITCODE \
		OSL_BUILD_TESTS OSL_BUILD_PLUGINS
CMAKE_OFF=	USE_BOOST_WAVE 
CMAKE_ARGS=	-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config60" \
		-DCMAKE_INSTALL_DOCDIR:STRING=${DOCSDIR} \
		-DUSE_CPP:STRING=11

USE_LDCONFIG=	yes
USES=		bison cmake:outsource compiler:c++11-lib ncurses

CXXFLAGS=	-I${STAGEDIR}/include

OPTIONS_DEFINE=		OSLTOY
OPTIONS_SUB=		yes
OSLTOY_DESC=		Interactive shader edit and visualize tool
OSLTOY_CMAKE_BOOL=	USE_QT
OSLTOY_USES=		qt:5
OSLTOY_USE=		QT=buildtools,core,gui,opengl,qmake_build,widgets

PLIST_SUB+=		LIBVERS=${PORTVERSION}

post-patch:
	@${REINPLACE_CMD} -e 's,/bin/bash,/bin/sh,' \
		${WRKSRC}/src/liboslexec/serialize-bc.bash

post-install:
	@${FIND} ${STAGEDIR} -name "*.h" | \
		${XARGS} ${REINPLACE_CMD} -e 's|OSL/|OSL_dev/|g'
	@${FIND} ${STAGEDIR} -name "*.bak" -delete

.include <bsd.port.mk>
