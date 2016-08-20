# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	ptex
PORTVERSION=	2.1.28
CATEGORIES?=	graphics

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Per face texture library

LICENSE=	BSD3CLAUSE

USE_GITHUB=	yes
GH_ACCOUNT=	wdas
GH_PROJECT=	ptex
GH_TAGNAME=	v${PORTVERSION}
#WRKSRC=		${WRKDIR}/${GH_PROJECT}-${PORTVERSION}/src

USE_LDCONFIG=	yes
USES=		cmake

OPTIONS_DEFINE=		DOCS

DOCS_BUILD_DEPENDS=	doxygen:devel/doxygen

.include <bsd.port.options.mk>

post-build:
.if ${PORT_OPTIONS:MDOCS}
	@(cd ${WRKSRC}/src/doc && doxygen Doxyfile)
.endif

do-install:
	${INSTALL_LIB} ${BUILD_WRKSRC}/src/ptex/libPtex.so \
		${STAGEDIR}${PREFIX}/lib
	${INSTALL_LIB} ${BUILD_WRKSRC}/src/ptex/libPtex.a \
		${STAGEDIR}${PREFIX}/lib
	${INSTALL_PROGRAM} ${BUILD_WRKSRC}/src/utils/ptxinfo \
		${STAGEDIR}${PREFIX}/bin
	${MKDIR} ${STAGEDIR}/${PREFIX}/include/ptex
	${INSTALL_DATA} ${BUILD_WRKSRC}/src/ptex/*.h ${STAGEDIR}/${PREFIX}/include/ptex
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	@cd ${BUILD_WRKSRC}/src/doc/ptex/ && \
		${INSTALL_DATA} * ${STAGEDIR}${DOCSDIR}
.endif

.include <bsd.port.mk>
