# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	sord
PORTVERSION=	0.12.0
CATEGORIES=	textproc
MASTER_SITES=	http://download.drobilla.net/

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	A lightweight library for storing RDF data in memory

LICENSE=	ISCL

LIB_DEPENDS+=	libserd-0.so:${PORTSDIR}/textproc/serd

USE_BZIP2=	yes
USE_PYTHON_BUILD=	yes
USES=		pkgconfig
MAN1=		sordi.1 sord_validate.1

OPTIONS_DEFINE=		DOCS

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MDOCS}
BUILD_DEPENDS=	doxygen:${PORTSDIR}/devel/doxygen
BUILD_DEPENDS+=	dot:${PORTSDIR}/graphics/graphviz
DOCOPTION=	--docs --docdir=${STAGEDIR}${DOCSDIR}
MAN3=		sord.3
.else
DOCOPTION=
.endif

CONFIGURE_ENV+= CC="${CC}"
CONFIGURE_ENV+= CXX="${CXX}"

do-configure:
	@cd ${WRKSRC} && ${CONFIGURE_ENV} ${PYTHON_CMD} waf configure \
		${DOCOPTION} --mandir=${STAGEDIR}${MANPREFIX}/man --prefix=${STAGEDIR}${PREFIX}

do-build:
	@cd ${WRKSRC} && ${PYTHON_CMD} waf

pre-install:
	@${FIND} ${WRKSRC} -name autowaf.py -or -name TaskGen.py | \
		${XARGS} ${REINPLACE_CMD} -e "s|pkgconfig|../libdata/pkgconfig|" \
		-e "s|%s-%d'%(name.lower(),major),outdir,'html||"

do-install:
	@cd ${WRKSRC} && ${PYTHON_CMD} waf install

.include <bsd.port.mk>
