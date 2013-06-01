# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	sratom
PORTVERSION=	0.4.2
CATEGORIES=	audio
MASTER_SITES=	http://download.drobilla.net/

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	A library for serialising LV2 atoms to/from RDF

LICENSE=	ISCL

BUILD_DEPENDS=	${LOCALBASE}/lib/lv2/lv2core.lv2/lv2.h:${PORTSDIR}/audio/lv2
LIB_DEPENDS=	sord-0:${PORTSDIR}/textproc/sord
RUN_DEPENDS=	${LOCALBASE}/lib/lv2/lv2core.lv2/lv2.h:${PORTSDIR}/audio/lv2

USE_PYTHON_BUILD=	yes
USE_BZIP2=	yes
USES=		pkgconfig
MAKE_JOBS_SAFE=	yes

OPTIONS_DEFINE=		DOCS

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MDOCS}
BUILD_DEPENDS=	doxygen:${PORTSDIR}/devel/doxygen
BUILD_DEPENDS+=	dot:${PORTSDIR}/graphics/graphviz
DOCOPTION=	--docs
.else
DOCOPTION=
.endif

CONFIGURE_ENV+= CC="${CC}"
CONFIGURE_ENV+= CXX="${CXX}"
CONFIGURE_ENV+= PKG_CONFIG_PATH="${LOCALBASE}/lib/pkgconfig:${LOCALBASE}/libdata/pkgconfig"

do-configure:
	@cd ${WRKSRC} && ${CONFIGURE_ENV} ${PYTHON_CMD} waf configure \
		${DOCOPTION} --mandir=${MANPREFIX}/man --prefix=${PREFIX}

do-build:
	@cd ${WRKSRC} && ${PYTHON_CMD} waf

do-install:
	@cd ${WRKSRC} && ${PYTHON_CMD} waf install

.include <bsd.port.mk>
