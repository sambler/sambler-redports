# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	ptex
PORTVERSION=	2.0.62
CATEGORIES?=	graphics

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Per face texture library

LICENSE=	BSD3CLAUSE

USE_GITHUB=	yes
GH_ACCOUNT=	wdas
GH_PROJECT=	ptex
GH_TAGNAME=	v${PORTVERSION}
GH_COMMIT=	961e40e
WRKSRC=		${WRKDIR}/${GH_ACCOUNT}-${GH_PROJECT}-${GH_COMMIT}/src

USE_LDCONFIG=	yes
USES=		cmake

OPTIONS_DEFINE=		DOCS

DOCS_BUILD_DEPENDS=	doxygen:${PORTSDIR}/devel/doxygen

.include <bsd.port.options.mk>

post-build:
.if ${PORT_OPTIONS:MDOCS}
	@(cd ${WRKSRC}/doc && doxygen Doxyfile)
.endif

do-install:
	${INSTALL_LIB} ${BUILD_WRKSRC}/ptex/libPtex.so \
		${STAGEDIR}${PREFIX}/lib
	${INSTALL_PROGRAM} ${BUILD_WRKSRC}/utils/ptxinfo \
		${STAGEDIR}${PREFIX}/bin
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	@cd ${BUILD_WRKSRC}/../install/doc/ptex/ && \
		${INSTALL_DATA} * ${STAGEDIR}${DOCSDIR}
.endif

.include <bsd.port.mk>
