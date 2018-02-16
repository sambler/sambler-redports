# $FreeBSD$

PORTNAME=	fantasymapgenerator
PORTVERSION=	0.0.1
CATEGORIES=	graphics

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Generate maps with a fantasy theme

LICENSE=	BSD3CLAUSE BSL ZLIB
LICENSE_COMB=	multi
LICENSE_FILE=	${WRKSRC}/LICENSE.md

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}cairo>=0:graphics/py-cairo@${PY_FLAVOR}
RUN_DEPENDS=	${BUILD_DEPENDS}

USES=		cmake python

USE_GITHUB=	yes
GH_ACCOUNT=	rlguy
GH_PROJECT=	FantasyMapGenerator
GH_TAGNAME=	8539eab56b18

post-patch:
	${REINPLACE_CMD} -e 's|%%BINDIR%%|${DATADIR}|g' \
		-e 's|%%FONTDATA%%|${DATADIR}/fontdata|g' \
		-e 's|%%CITYDATA%%|${DATADIR}/citydata|g' \
		${WRKSRC}/CMakeLists.txt

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/map_generation ${STAGEDIR}${PREFIX}/bin/
	@(cd ${WRKSRC} && ${COPYTREE_SHARE} fontdata ${STAGEDIR}${DATADIR} && \
		${COPYTREE_SHARE} citydata ${STAGEDIR}${DATADIR} && \
		${COPYTREE_SHARE} render ${STAGEDIR}${DATADIR})

.include <bsd.port.mk>
