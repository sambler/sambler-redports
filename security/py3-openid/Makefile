# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	openid
PORTVERSION=	3.0.2
CATEGORIES=	security python
MASTER_SITES=	GH
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Python OpenID support for python3

LICENSE=	APACHE20

USE_GITHUB=	yes
GH_ACCOUNT=	necaris
GH_PROJECT=	python3-openid
GH_TAGNAME=	v${PORTVERSION}
GH_COMMIT=	d384d34

USES+=		python:3
PYTHON_FEATURES=distutils autoplist concurrent

.include <bsd.port.mk>
