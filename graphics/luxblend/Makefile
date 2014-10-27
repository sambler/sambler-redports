# New ports collection makefile for:	LuxBlend
# Date created:			29 November 2011
# Whom:					Shane Ambler
#
# $FreeBSD$
#

PORTNAME=	luxblend
PORTVERSION=	0.9.0.20120227
CATEGORIES=	graphics
MASTER_SITES=	http://src.luxrender.net/luxblend25/archive/ \
				http://bitbucket.org/luxrender/luxblend25/get/
DISTNAME=	${HG_NODEID}
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=
COMMENT=	Blender plugin to use Luxrender

LICENSE=	GPLv3

RUN_DEPENDS=	blender>=2.60:${PORTSDIR}/graphics/blender \
				luxconsole:${PORTSDIR}/graphics/luxrender

# recent snapshot - 2012-02-27
HG_NODEID=	7379271e2341

USES=		tar:bzip2

WRKSRC=		${WRKDIR}/luxblend25-${HG_NODEID}

.if defined(PREFIX) && ${PREFIX} != ""
TARGETROOT=${PREFIX}
.else
TARGETROOT=${LOCALBASE}
.endif

post-install:
	(cd ${WRKSRC}/src && ${COPYTREE_SHARE} "luxrender" \
			${TARGETROOT}/share/blender/scripts/addons/)

	(cd ${WRKSRC}/src/presets && ${COPYTREE_SHARE} "luxrender" \
			${TARGETROOT}/share/blender/scripts/presets/)

.if exists(${TARGETROOT}/lib/pylux.so)
	(cd ${TARGETROOT}/lib && ${COPYTREE_SHARE} "pylux.so" \
			${TARGETROOT}/share/blender/scripts/addons/luxrender/)
.else
	(cd ${LOCALBASE}/lib && ${COPYTREE_SHARE} "pylux.so" \
			${TARGETROOT}/share/blender/scripts/addons/luxrender/)
.endif

.include <bsd.port.mk>
