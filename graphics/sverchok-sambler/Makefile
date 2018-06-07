# $FreeBSD: head/graphics/sverchok-blender/Makefile 466067 2018-03-31 17:00:49Z yuri $

PORTNAME=	sverchok
DISTVERSION=	0.5.9.6.3
CATEGORIES=	graphics
PKGNAMESUFFIX=	-blender

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Add-on for Blender: parametric tool for architects and designers

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PYNUMPY} \
		${PYTHON_PKGNAMEPREFIX}requests>0:www/py-requests@${PY_FLAVOR}

.include "../blender/Makefile.versions"

USES=		python:${BLENDER_PY_VERSION}
USE_GITHUB=	yes
GH_ACCOUNT=	nortikin
NO_BUILD=	yes
NO_ARCH=	yes

PLIST_SUB+=	${BLVERS}=${BLENDER_BL_VERSION}

do-install:
	@${RM} ${WRKSRC}/node_scripts/templates/polyvox  # stray link
	@${MKDIR} ${STAGEDIR}${PREFIX}/share/blender/${BLENDER_BL_VERSION}/scripts/addons/${PORTNAME}
	cd ${WRKSRC} && ${COPYTREE_SHARE} . ${STAGEDIR}${PREFIX}/share/blender/${BLENDER_BL_VERSION}/scripts/addons/${PORTNAME}

.include <bsd.port.mk>
