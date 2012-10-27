# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openshadinglanguage
PORTVERSION=	1.2.0
CATEGORIES=	graphics devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Advanced shading language for production GI renderers

LICENSE=	BSD

BUILD_DEPENDS=	llvm>=3.1:${PORTSDIR}/devel/llvm
BUILD_DEPENDS+=	flex>=2.5.37:${PORTSDIR}/textproc/flex
LIB_DEPENDS=	boost_thread:${PORTSDIR}/devel/boost-libs
LIB_DEPENDS+=	IlmImf:${PORTSDIR}/graphics/OpenEXR
LIB_DEPENDS+=	OpenImageIO:${PORTSDIR}/graphics/openimageio
RUN_DEPENDS=	llvm>=3.1:${PORTSDIR}/devel/llvm

USE_GITHUB=	yes
GH_ACCOUNT=	imageworks
GH_PROJECT=	OpenShadingLanguage
GH_TAGNAME=	Release-${PORTVERSION}
GH_COMMIT=	b0673b8

WRKSRC+=	${WRKDIR}/imageworks-OpenShadingLanguage-${GH_COMMIT}/src

USE_CMAKE=	yes
CMAKE_VERBOSE=	yes
CMAKE_OUTSOURCE=	yes
CMAKE_ARGS=	-DFLEX_EXECUTABLE:STRING=/usr/local/bin/flex
CMAKE_ARGS+=	-DUSE_TBB:BOOL=OFF
CXXFLAGS+=	-I/usr/local/include/flex
USE_LDCONFIG=	yes
USE_BISON=	build
MAKE_JOBS_SAFE=	yes

.include <bsd.port.pre.mk>

.if ${OSVERSION} < 900000
BUILD_DEPENDS+=	clang:${PORTSDIR}/lang/clang
.endif

.if ${ARCH} == i386
CFLAGS+=	-march=i586
.endif

.include <bsd.port.post.mk>
