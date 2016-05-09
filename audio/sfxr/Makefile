# Created by: Shane Ambler
# $FreeBSD$

PORTNAME=	sfxr
PORTVERSION=	1.2.1
CATEGORIES=	audio
MASTER_SITES=	http://www.drpetter.se/files/
DISTNAME=	sfxr-sdl-1.2.1

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Sound generator for 8-bit game sounds

LICENSE=	MIT

USES=		tar pkgconfig gnome gmake
USE_SDL=	sdl
USE_GNOME=	gtk30
INSTALLS_ICONS=	yes

do-build:
	@cd ${WRKSRC} && gmake

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/sfxr ${STAGEDIR}${PREFIX}/bin
	${MKDIR} -p ${STAGEDIR}${DATADIR}
	${INSTALL_DATA} ${WRKSRC}/*.tga ${STAGEDIR}${DATADIR}
	${INSTALL_DATA} ${WRKSRC}/*.bmp ${STAGEDIR}${DATADIR}
	${MKDIR} -p ${STAGEDIR}${PREFIX}/share/icons/hicolor/48x48/apps
	${INSTALL_DATA} ${WRKSRC}/sfxr.png ${STAGEDIR}${PREFIX}/share/icons/hicolor/48x48/apps
	${INSTALL_DATA} ${WRKSRC}/sfxr.desktop ${STAGEDIR}${DESKTOPDIR}
	${MKDIR} -p ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/readme.txt ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
