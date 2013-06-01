# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	lv2
PORTVERSION=	1.4.0
CATEGORIES=	audio
MASTER_SITES=	http://lv2plug.in/spec/

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	LV2 plugin libraries

LICENSE=	ISCL

CONFLICTS=	lv2core-6.*

LIB_DEPENDS=	sndfile:${PORTSDIR}/audio/libsndfile

USE_PYTHON_BUILD=	yes
USE_BZIP2=	yes
USES=		pkgconfig
USE_GNOME=	gtk20
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
