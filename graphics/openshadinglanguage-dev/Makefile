# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage-dev
DISTVERSIONPREFIX=	Release-
DISTVERSION=	1.11.3.0
DISTVERSIONSUFFIX=	dev
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS=	llvm-config${LLVM_VER}:devel/llvm${LLVM_VER}
LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libtinfo.so:devel/ncurses \
		libImath.so:graphics/ilmbase \
		libIlmImf.so:graphics/openexr \
		libOpenImageIO.so:graphics/openimageio \
		libpugixml.so:textproc/pugixml
RUN_DEPENDS=	llvm-config${LLVM_VER}:devel/llvm${LLVM_VER}

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenShadingLanguage
## master commits
GH_TAGNAME=	be720a31ea73  # 7/1 -X pugi
#GH_TAGNAME=	7b12e92eb97c  # 19/11 -X pugi
#GH_TAGNAME=	220b05cb43f3  # 9/11 -X pugi
#GH_TAGNAME=	3a06e88f6f52  # 8/11 ??
#GH_TAGNAME=	d3206b99ebda  # 7/11 -X pugi
#GH_TAGNAME=	c042d24cfd0b  # 30/10 - GOOD
#GH_TAGNAME=	30f64c07c28f  # 17/10
#GH_TAGNAME=	55bd37b0985c  # 2/10
#GH_TAGNAME=	00984c339f52  # 13/9
#GH_TAGNAME=	f0a0039ca967  # 7/9
#GH_TAGNAME=	3f7a13ba5ef1  # 6/8
#GH_TAGNAME=	a5d8381afbe1  # 3/7
PORTSCOUT=	ignore:1

#MYCLANGVER=	90
#BUILD_DEPENDS+=	${LOCALBASE}/bin/clang${MYCLANGVER}:devel/llvm${MYCLANGVER}
#CPP=	${LOCALBASE}/bin/clang-cpp${MYCLANGVER}
#CC=	${LOCALBASE}/bin/clang${MYCLANGVER}
#CXX=	${LOCALBASE}/bin/clang++${MYCLANGVER}
#LD=	${LOCALBASE}/bin/ld.lld${MYCLANGVER}

#DISABLE_MAKE_JOBS=	yes

LLVM_VER=	90
CMAKE_ON=	ENABLE_RTTI USE_LIBCPLUSPLUS USE_LLVM_BITCODE \
		OSL_BUILD_TESTS OSL_BUILD_PLUGINS
CMAKE_OFF=	USE_BOOST_WAVE
# OSL_BUILD_MATERIALX
CMAKE_ARGS=	-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config${LLVM_VER}" \
		-DCMAKE_INSTALL_DOCDIR:STRING=${DOCSDIR} \
		-DUSE_CPP:STRING=11 
		#-DOSL_LIBNAME_SUFFIX:STRING="-dev"
# This flag fixes linking with clang 9.0 ??
CXXFLAGS=	-DNDEBUG

USE_LDCONFIG=	yes
USES=		bison cmake compiler:c++11-lang ncurses python:build

OPTIONS_DEFINE=		OSLTOY
OPTIONS_SUB=		yes
OSLTOY_DESC=		Interactive shader edit and visualize tool
OSLTOY_CMAKE_BOOL=	USE_QT
OSLTOY_USES=		qt:5
OSLTOY_USE=		QT=buildtools,core,gui,opengl,qmake_build,widgets

# for LIBVERS we want the first three digits
PLIST_SUB+=		LIBVERS=${DISTVERSION:C/([0-9]*)\.([0-9]*)\.([0-9]*)(.*)/\1.\2.\3/}

post-patch:
	@${REINPLACE_CMD} -e 's,%%DATADIR%%,${DATADIR},' \
		-e 's,%%PYCMD%%,${PYTHON_CMD},' \
		${WRKSRC}/CMakeLists.txt \
		${WRKSRC}/src/liboslexec/CMakeLists.txt \
		${WRKSRC}/src/shaders/CMakeLists.txt \
		${WRKSRC}/src/shaders/MaterialX/CMakeLists.txt \
		${WRKSRC}/src/doc/CMakeLists.txt

post-install:
	@${FIND} ${STAGEDIR} -name "*.h" | \
		${XARGS} ${REINPLACE_CMD} -e 's|OSL/|OSL-dev/|g'
	@${FIND} ${STAGEDIR} -name "*.bak" -delete

.include <bsd.port.mk>
