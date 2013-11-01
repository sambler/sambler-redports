# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	suil
PORTVERSION=	0.6.14
CATEGORIES=	audio
MASTER_SITES=	http://download.drobilla.net/

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	A wrapper for LV2 plugin UIs

LICENSE=	ISCL

BUILD_DEPENDS=	lv2>=0:${PORTSDIR}/audio/lv2
RUN_DEPENDS=	lv2>=0:${PORTSDIR}/audio/lv2

USE_PYTHON_BUILD=	yes
USE_BZIP2=	yes
USE_GNOME=	gtk20
USE_QT4=	gui
USES=		pkgconfig

OPTIONS_DEFINE=		DOCS

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MDOCS}
BUILD_DEPENDS+=	doxygen:${PORTSDIR}/devel/doxygen
BUILD_DEPENDS+=	dot:${PORTSDIR}/graphics/graphviz
DOCOPTION=	--docs --docdir=${STAGEDIR}${DOCSDIR}
MAN3=		suil.3
.else
DOCOPTION=
.endif

CONFIGURE_ENV+= CC="${CC}"
CONFIGURE_ENV+= CXX="${CXX}"

do-configure:
	@cd ${WRKSRC} && ${CONFIGURE_ENV} ${PYTHON_CMD} waf configure \
		${DOCOPTION} --mandir=${STAGEDIR}${MANPREFIX}/man --docdir=${STAGEDIR}${DOCSDIR} --prefix=${STAGEDIR}${PREFIX}

do-build:
	@cd ${WRKSRC} && ${PYTHON_CMD} waf

pre-install:
	@${FIND} ${WRKSRC} -name autowaf.py -or -name TaskGen.py | \
		${XARGS} ${REINPLACE_CMD} -e "s|pkgconfig|../libdata/pkgconfig|" \
		-e "s|versioned=True|versioned=False|" \
		-e "s|,outname,outdir,'html'|''|"

do-install:
	@cd ${WRKSRC} && ${PYTHON_CMD} waf install

.include <bsd.port.mk>
