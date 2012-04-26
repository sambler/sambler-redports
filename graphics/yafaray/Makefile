# New ports collection makefile for:	YafaRay
# Date created:				18 May 2003
# Whom:					David Yeske <dyeske@gmail.com>
#
# $FreeBSD: ports/graphics/yafray/Makefile,v 1.24 2011/06/17 09:59:29 danfe Exp $
#

PORTNAME=	yafaray
PORTVERSION=	0.1.2b4
PORTREVISION=	0
CATEGORIES=	graphics
# official repo is at https://github.com/yafaray/Core but they don't have tags
# which we want for downloading so I forked and tagged it
MASTER_SITES=	https://github.com/sambler/Core/tarball/
EXTRACT_SUFX=

MAINTAINER=	ports@FreeBSD.org
COMMENT=	A fast XML based raytracer

LICENSE=	LGPL21

BUILD_DEPENDS=	swig:${PORTSDIR}/devel/swig13
LIB_DEPENDS=	jpeg.11:${PORTSDIR}/graphics/jpeg \
				freetype.9:${PORTSDIR}/print/freetype2 \
				IlmImf.6:${PORTSDIR}/graphics/OpenEXR \
				png.6:${PORTSDIR}/graphics/png \
				tiff.4:${PORTSDIR}/graphics/tiff \
				xml2.5:${PORTSDIR}/textproc/libxml2

FETCH_ARGS=	-pRr
USE_CMAKE=	yes
CMAKE_VERBOSE=	yes
CMAKE_OUTSOURCE=	yes
CMAKE_ARGS=	-DWITH_Freetype:BOOL=ON -DWITH_OpenEXR:BOOL=ON -DWITH_JPEG:BOOL=ON \
			-DWITH_PNG:BOOL=ON -DWITH_TIFF:BOOL=ON -DWITH_XML_LOADER:BOOL=ON \
			-DWITH_QT:BOOL=ON -DWITH_YAF_PY_BINDINGS:BOOL=ON \
			-DWITH_YAF_RUBY_BINDINGS:BOOL=OFF -DBUILDRELEASE:BOOL=ON

USE_LDCONFIG=	yes
USE_GCC=	4.6+
LDFLAGS+=	-rpath ${LOCALBASE}/lib/gcc46
MAKE_JOBS_SAFE=	yes
USE_PYTHON=	3.2
USE_QT_VER=	4
QT_COMPONENTS=	gui moc_build qmake_build rcc_build uic_build

WRKSRC=		${WRKDIR}/sambler-Core-57adf87

.include <bsd.port.mk>
