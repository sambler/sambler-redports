# Created by: Mario Sergio Fujikawa Ferreira <lioux@FreeBSD.org>
# $FreeBSD$

PORTNAME=	elsamuko
DISTVERSION=	20170116
PORTREVISION=	0
CATEGORIES=	graphics
PKGNAMEPREFIX=	gimp-
PKGNAMESUFFIX=	-script

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Gimp scripts by elsamuko

LICENSE=	GPLv3

RUN_DEPENDS=	${LOCALBASE}/bin/gimp:graphics/gimp-app

USE_GITHUB=	yes
GH_PROJECT=	gimp-elsamuko
GH_TAGNAME=	b3f4e3e7c3

OPTIONS_DEFINE=	DOCS

USES=		tar:tgz
NO_BUILD=	yes
NO_ARCH=	yes

GIMP_SCRIPTS_DIR?=	share/gimp/scripts

# installation dir
PLIST_SUB=	GIMP_SCRIPTS_DIR=${GIMP_SCRIPTS_DIR}

# installed docs
PORTDOCS=	*

do-install:
	(cd ${WRKSRC}/scripts && ${COPYTREE_SHARE} \*.scm \
		${STAGEDIR}${PREFIX}/${GIMP_SCRIPTS_DIR})

# install docs
do-install-DOCS-on:
	${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README.md ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
