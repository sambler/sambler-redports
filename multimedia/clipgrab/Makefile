# Created by: Veniamin Gvozdikov <vg@FreeBSD.org>
# $FreeBSD$

PORTNAME=	clipgrab
PORTVERSION=	3.4.7
CATEGORIES=	multimedia
MASTER_SITES=	http://clipgrab.de/download/ \
		http://vanbittern.org/

MAINTAINER=	vg@FreeBSD.org
COMMENT=	Program to download videos from YouTube and etc

LICENSE=	GPLv3

USES=		qmake tar:bzip2
USE_QT4=	gui xml uic_build moc_build \
		rcc_build network dbus webkit
CXXFLAGS+= -I${LOCALBASE}/include/qt4/QtNetwork -I${LOCALBASE}/include/qt4/QtWebKit
CXXFLAGS+= -I${LOCALBASE}/include/qt4/QtXml
LDFLAGS+=  -L${LOCALBASE}/lib/qt4 -lQtNetwork -lQtWebKit -lQtXml

PLIST_FILES=	bin/${PORTNAME} \
		%%DATADIR%%/icon.png \
		%%DATADIR%%/logo.png \
		%%DATADIR%%/paypal-logo.png \
		%%DATADIR%%/splash.png

DESKTOP_ENTRIES="Clipgrab" "Download and convert videos from YouTube and etc" \
		"${DATADIR}/icon.png" "${PORTNAME}" \
		"AudioVideo;" true

post-patch:
	${REINPLACE_CMD} -e 's,img/,share/${PORTNAME}/,g' \
	${WRKSRC}/*.cpp

pre-configure:
	@(cd ${WRKSRC} && ${RM} video_tudou.* video_youku.*)
	@(cd ${WRKSRC} && qmake-qt4 -project)

do-install:
	${MKDIR} ${STAGEDIR}${DATADIR}
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME}-3 ${STAGEDIR}${PREFIX}/bin/${PORTNAME}
	${INSTALL_DATA} ${WRKSRC}/*.png ${STAGEDIR}${DATADIR}

.include <bsd.port.mk>
