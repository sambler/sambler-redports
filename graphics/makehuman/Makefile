# Created by: Dmitry Marakasov <amdmi3@amdmi3.ru>
# $FreeBSD$

PORTNAME=	makehuman
DISTVERSION=	1.1.0
CATEGORIES=	graphics
MASTER_SITES=	https://bitbucket.org/MakeHuman/makehuman/get/${PORTVERSION}.tar.gz?dummy=/

MAINTAINER=	amdmi3@FreeBSD.org
COMMENT=	Application for parametrical modeling of 3D humanoid characters

LICENSE=	AGPLv3 CC0-1.0
LICENSE_COMB=	dual

RUN_DEPENDS=	${PYNUMPY} \
		${PYTHON_PKGNAMEPREFIX}qt4-gui>=0:x11-toolkits/py-qt4-gui \
		${PYTHON_PKGNAMEPREFIX}opengl>0:graphics/py-opengl

USES=		python:2 shebangfix
NO_BUILD=	yes
NO_ARCH=	yes

WRKSRC=		${WRKDIR}/MakeHuman-makehuman-38e6e33b59ee
python_OLD_CMD=	/usr/bin/python2.7
SHEBANG_FILES=	${WRKSRC}/makehuman/*/*.py ${WRKSRC}/makehuman/*/*/*.py
SUB_FILES=	makehuman
SUB_LIST=	PYTHON_CMD=${PYTHON_CMD}
PLIST_FILES=	bin/makehuman

PORTDATA=	*
PORTDOCS=	README

do-install:
	@${MKDIR} ${STAGEDIR}${DATADIR}
	@cd ${WRKSRC}/makehuman && ${COPYTREE_SHARE} . ${STAGEDIR}${DATADIR}
	${INSTALL_SCRIPT} ${WRKDIR}/makehuman ${STAGEDIR}${PREFIX}/bin/makehuman
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
