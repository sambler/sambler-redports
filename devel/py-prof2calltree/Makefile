# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	prof2calltree
PORTVERSION=	1.3.2
CATEGORIES=	devel python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTNAME=	pyprof2calltree-${PORTVERSION}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Script to help visualize profile data

LICENSE=	BSD3CLAUSE

USES=		python shebangfix
USE_PYTHON=	autoplist concurrent distutils

python_OLD_CMD=	"/usr/bin/env\ python"
SHEBANG_FILES=	${WRKSRC}/pyprof2calltree.py
PLIST_FILES=	bin/prof2calltree

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/pyprof2calltree.py ${STAGEDIR}${PREFIX}/bin/prof2calltree

.include <bsd.port.mk>
