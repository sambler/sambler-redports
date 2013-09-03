# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	sratom
PORTVERSION=	0.4.2
CATEGORIES=	audio
MASTER_SITES=	http://download.drobilla.net/

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	A library for serialising LV2 atoms to/from RDF

LICENSE=	ISCL

BUILD_DEPENDS=	lv2>=0:${PORTSDIR}/audio/lv2
LIB_DEPENDS=	libsord-0.so:${PORTSDIR}/textproc/sord
RUN_DEPENDS=	lv2>=0:${PORTSDIR}/audio/lv2

USE_PYTHON_BUILD=	yes
USE_BZIP2=	yes
USES=		pkgconfig

OPTIONS_DEFINE=		DOCS

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MDOCS}
BUILD_DEPENDS+=	doxygen:${PORTSDIR}/devel/doxygen
BUILD_DEPENDS+=	dot:${PORTSDIR}/graphics/graphviz
DOCOPTION=	--docs --docdir=${DOCSDIR}
MAN3=		sratom.3
.else
DOCOPTION=
.endif

CONFIGURE_ENV+= CC="${CC}"
CONFIGURE_ENV+= CXX="${CXX}"

do-configure:
	@cd ${WRKSRC} && ${CONFIGURE_ENV} ${PYTHON_CMD} waf configure \
		${DOCOPTION} --mandir=${MANPREFIX}/man --prefix=${PREFIX}

do-build:
	@cd ${WRKSRC} && ${PYTHON_CMD} waf

pre-install:
	@${FIND} ${WRKSRC} -name autowaf.py -or -name TaskGen.py | \
		${XARGS} ${REINPLACE_CMD} -e "s|pkgconfig|../libdata/pkgconfig|" \
		-e "s|%s-%d'%(name.lower(),major),outdir,'html||"

do-install:
	@cd ${WRKSRC} && ${PYTHON_CMD} waf install

.include <bsd.port.mk>
