# Created by: Shane Ambler <FreeBSD@ShaneWare.Biz>
# $FreeBSD$

PORTNAME=	pythontoolkit
PORTVERSION=	14.04.04
CATEGORIES=	devel
MASTER_SITES=	SF/pythontoolkit/Python%20Toolkit/ptk%20v14.04
DISTFILES=	PythonToolkit-${PORTVERSION}${EXTRACT_SUFX}

MAINTAINER=	FreeBSD@ShaneWare.Biz
COMMENT=	An interactive environment for python

LICENSE=	MIT

USES=		zip python
PYTHON_FEATURES= distutils autoplist
USE_WX=		2.8+
WX_COMPS=	python:run
WRKSRC=		${WRKDIR}/PythonToolkit-${PORTVERSION}

post-patch:
	@${REINPLACE_CMD} -e 's|%%LOCALBASE%%|${LOCALBASE}|g' ${WRKSRC}/setup.py

.include <bsd.port.mk>
