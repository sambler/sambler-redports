# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	godot
PORTVERSION=	1.0
CATEGORIES=	devel games

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Game development environment

LICENSE=	MIT

USE_GITHUB=	yes
GH_ACCOUNT=	okamstudio
GH_PROJECT=	godot
GH_TAGNAME=	${PORTVERSION}-stable
GH_COMMIT=	7eb5d04

LIB_DEPENDS=	libfreetype.so:${PORTSDIR}/print/freetype2 \
		libasound.so:${PORTSDIR}/audio/alsa-lib

USES=		scons pkgconfig
USE_XORG=	x11 xcursor
USE_GL=		glu
USE_OPENSSL=	yes
# uses pkg-config to find ssl - pkg-config only finds port version
WITH_OPENSSL_PORT=	yes

# this doesn't work - replace do-build instead
#SCONS_ARGS+=	platform=x11
#SCONS_ENV+=	BUILD_REVISION="FreeBSD Ports build"

.include <bsd.port.pre.mk>

post-patch:
	@${REINPLACE_CMD} -e 's|custom_build|FreeBSD Ports build|' ${WRKSRC}/methods.py

do-build:
	@cd ${WRKSRC} && scons platform=x11

do-install:
	@${INSTALL_PROGRAM} ${WRKSRC}/bin/godot.x11.tools.64 \
		${STAGEDIR}/${PREFIX}/bin/godot.x11.tools.64
	@${LN} ${STAGEDIR}/${PREFIX}/bin/godot.x11.tools.64 \
		${STAGEDIR}/${PREFIX}/bin/godot

.include <bsd.port.post.mk>
