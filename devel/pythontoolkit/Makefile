# Created by: Shane Ambler <FreeBSD@ShaneWare.Biz>
# $FreeBSD$

PORTNAME=	pythontoolkit
PORTVERSION=	14.04.04
CATEGORIES=	devel
MASTER_SITES=	SF/pythontoolkit/Python%20Toolkit/ptk%20v14.04
DISTFILES=	PythonToolkit-${PORTVERSION}${EXTRACT_SUFX}
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	FreeBSD@ShaneWare.Biz
COMMENT=	An interactive environment for python

LICENSE=	MIT

USES=		zip python
USE_PYTHON=	distutils autoplist concurrent
USE_WX=		3.0
WX_COMPS=	python:run
WRKSRC=		${WRKDIR}/PythonToolkit-${PORTVERSION}

post-patch:
	@${REINPLACE_CMD} -e 's|%%LOCALBASE%%|${LOCALBASE}|g' \
		-e 's|%%SUFFIX%%|${UNIQUE_SUFFIX}|g' \
		${WRKSRC}/setup.py ${WRKSRC}/linux/PTK.desktop
	@${MV} ${WRKSRC}/linux/PTK.desktop \
		${WRKSRC}/linux/PTK${UNIQUE_SUFFIX}.desktop
	@${MV} ${WRKSRC}/ptk_lib/resources/ptkicon.svg \
		${WRKSRC}/ptk_lib/resources/ptkicon${UNIQUE_SUFFIX}.svg

.include <bsd.port.mk>
