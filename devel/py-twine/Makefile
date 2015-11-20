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
USE_PYTHON=	autoplist distutils

.include <bsd.port.mk>
