# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	suil
PORTVERSION=	0.6.12
CATEGORIES=	audio
MASTER_SITES=	http://download.drobilla.net/

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	A wrapper for LV2 plugin UIs

LICENSE=	ISCL

BUILD_DEPENDS=	${LOCALBASE}/lib/lv2/lv2core.lv2/lv2.h:${PORTSDIR}/audio/lv2
RUN_DEPENDS=	${LOCALBASE}/lib/lv2/lv2core.lv2/lv2.h:${PORTSDIR}/audio/lv2

USE_PYTHON_BUILD=	yes
USE_BZIP2=	yes
USE_GNOME=	gtk20
USE_QT4=	gui
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
