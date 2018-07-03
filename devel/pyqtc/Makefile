# Created by: Shane Ambler <FreeBSD@ShaneWare.Biz>
# $FreeBSD$

PORTNAME=	pyqtc
PORTVERSION=	0.0.4
CATEGORIES=	devel
MASTER_SITES=	GH

MAINTAINER=	FreeBSD@ShaneWare.Biz
COMMENT=	QtCreator plugin for python code completion

LICENSE=	MIT

BUILD_DEPENDS+=	qtcreator:${PORTSDIR}/devel/qtcreator \
		pylint:${PORTSDIR}/devel/pylint
LIB_DEPENDS+=	libprotoc.so:${PORTSDIR}/devel/protobuf
RUN_DEPENDS+=	pylint:${PORTSDIR}/devel/pylint

# originator - https://github.com/davidsansome/pyqtc
# latest update - https://github.com/mkr3142/pyqtc
USE_GITHUB=	yes
GH_ACCOUNT=	mkr3142
GH_PROJECT=	pyqtc
GH_TAGNAME=	${GH_COMMIT}
GH_COMMIT=	252a7b9

USES=		cmake:outsource python qt:4
CMAKE_ARGS+=	-DQTC_SOURCE:STRING=${WRKDIR}/qt-creator-2.8.0-src \
		-DQTC_BINARY:STRING=${LOCALBASE}
CXXFLAGS+=	-I${LOCALBASE}/include
USE_QT=		qmake_build corelib gui network 
# assistant_run qt3support declarative script sql xml webkit moc_build rcc_build uic_build

# /usr/local/lib/qtcreator/plugins/
#QT_PLUGINDIR_REL

post-extract:
	@${TAR} xf ${DISTDIR}/KDE/qt-creator-2.8.0-src.tar.gz -C ${WRKDIR}

.include <bsd.port.mk>
