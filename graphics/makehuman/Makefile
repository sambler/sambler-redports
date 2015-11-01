# Created by: Dmitry Marakasov <amdmi3@amdmi3.ru>
# $FreeBSD$

PORTNAME=	makehuman
DISTVERSION=	1.0.2
CATEGORIES=	graphics
MASTER_SITES=	https://bitbucket.org/MakeHuman/makehuman/get/${PORTVERSION}.tar.gz?dummy=/

MAINTAINER=	amdmi3@FreeBSD.org
COMMENT=	Application for parametrical modeling of 3D humanoid characters

LICENSE=	AGPLv3 CC0-1.0
LICENSE_COMB=	dual

RUN_DEPENDS=	${PYNUMPY} \
		${PYTHON_PKGNAMEPREFIX}qt4-gui>=0:${PORTSDIR}/x11-toolkits/py-qt4-gui \
		${PYTHON_PKGNAMEPREFIX}opengl>0:${PORTSDIR}/graphics/py-opengl

USES=		python:2 shebangfix
NO_BUILD=	yes

WRKSRC=		${WRKDIR}/MakeHuman-makehuman-47eda58327ee
python_OLD_CMD=	/usr/bin/python2.7
SHEBANG_FILES=	${WRKSRC}/makehuman/*/*.py ${WRKSRC}/makehuman/*/*/*.py
SUB_FILES=	makehuman
SUB_LIST=	PYTHON_CMD=${PYTHON_CMD}

post-extract:
	# one file doesn't have python2.7 which prevents shebangfix adjusting it
	@${REINPLACE_CMD} -e 's|usr/bin/python|usr/bin/python2.7|' \
		${WRKSRC}/makehuman/core/managed_file.py

do-install:
	@${MKDIR} ${STAGEDIR}${DATADIR}
	@cd ${WRKSRC}/makehuman && ${COPYTREE_SHARE} . ${STAGEDIR}${DATADIR}
	${INSTALL_SCRIPT} ${WRKDIR}/makehuman ${STAGEDIR}${PREFIX}/bin/makehuman
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
