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
BUILD_DEPENDS+=	${PYTHON_SITELIBDIR}/rdflib/__init__.py:${PORTSDIR}/textproc/py-rdflib
DOCOPTION=	--docs --docdir=${DOCSDIR}
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
	@${FIND} ${WRKSRC} -name autowaf.py -or -name TaskGen.py \
		-or -name wscript | ${XARGS} ${REINPLACE_CMD} \
		-e "s|pkgconfig|../libdata/pkgconfig|"

do-install:
	@cd ${WRKSRC} && ${PYTHON_CMD} waf install

.include <bsd.port.mk>
