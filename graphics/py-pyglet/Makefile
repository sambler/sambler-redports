# Created by: Dmitry Marakasov <amdmi3@FreeBSD.org>
# $FreeBSD$

PORTNAME=	pyglet
PORTVERSION=	1.2.4
PORTREVISION=	0
CATEGORIES=	graphics multimedia x11-toolkits python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	amdmi3@FreeBSD.org
COMMENT=	Cross-platform windowing and multimedia library for Python

LICENSE=	BSD3CLAUSE

LIB_DEPENDS=	libfreetype.so:print/freetype2 \
		libfontconfig.so:x11-fonts/fontconfig
RUN_DEPENDS=	${LOCALBASE}/lib/libavbin.so:multimedia/avbin

USES=		openal:al python
USE_PYTHON=	distutils autoplist concurrent
USE_GL=		gl glu

PORTEXAMPLES=	*

OPTIONS_DEFINE=	EXAMPLES

.include <bsd.port.options.mk>

post-install:
.if ${PORT_OPTIONS:MEXAMPLES}
	cd ${WRKSRC}/examples && ${COPYTREE_SHARE} . ${STAGEDIR}${EXAMPLESDIR}/
.endif

.include <bsd.port.mk>
