# $FreeBSD$

PORTNAME=	lesscpy
DISTVERSION=	0.11.2
CATEGORIES=	www python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
# when port was created v0.12.0 was listed on pypi
# this appears to have come from the lxrave fork
# which has now been replaced by the official 0.11.2
PORTEPOCH=	1

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Python LESS compiler

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}six>0:devel/py-six@${FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}ply>0:devel/py-ply@${FLAVOR}

USES=		python
USE_PYTHON=	autoplist concurrent distutils
NO_ARCH=	yes

do-test: build
	@cd ${WRKSRC} && ${PYTHON_CMD} ${PYSETUP} test

.include <bsd.port.mk>
