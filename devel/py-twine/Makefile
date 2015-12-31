# Created by: Shane Ambler
# $FreeBSD$

PORTNAME=	twine
PORTVERSION=	1.6.4
CATEGORIES=	devel python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Collection of utilities for interacting with PyPI

LICENSE=	APACHE20

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}requests>0:${PORTSDIR}/www/py-requests \
		${PYTHON_PKGNAMEPREFIX}requests-toolbelt>0:${PORTSDIR}/www/py-requests-toolbelt \
		${PYTHON_PKGNAMEPREFIX}pkginfo>0:${PORTSDIR}/sysutils/py-pkginfo

USES=		python
USE_PYTHON=	autoplist concurrent distutils
SUB_FILES=	twine

.include <bsd.port.pre.mk>

.if ${PYTHON_MAJOR_VER} == 2
PLIST_FILES=	bin/twine
.endif

post-install:
.if ${PYTHON_MAJOR_VER} == 2
	${INSTALL_SCRIPT} ${WRKDIR}/twine ${STAGEDIR}${PREFIX}/bin/twine
.endif

.include <bsd.port.post.mk>
