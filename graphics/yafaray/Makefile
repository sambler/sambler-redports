# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	yafaray
PORTVERSION=	0.1.5
PORTREVISION=	0
CATEGORIES=	graphics
MASTER_SITES=	https://github.com/YafaRay/Core/tarball/:core \
		https://github.com/YafaRay/Blender-2.5-Exporter/tarball/:blenaddon
DISTFILES=	${PORTVERSION}:core
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	A fast XML based raytracer

LICENSE=	LGPL21

BUILD_DEPENDS=	swig:devel/swig13
LIB_DEPENDS=	libfreetype.so:print/freetype2 \
		libIlmImf.so:graphics/OpenEXR \
		libpng.so:graphics/png \
		libtiff.so:graphics/tiff \
		libxml2.so:textproc/libxml2

FETCH_ARGS=	-pRr
USES=		cmake:outsource jpeg
CMAKE_VERBOSE=	yes
CMAKE_ARGS=	-DWITH_Freetype:BOOL=ON -DWITH_OpenEXR:BOOL=ON -DWITH_JPEG:BOOL=ON \
		-DWITH_PNG:BOOL=ON -DWITH_TIFF:BOOL=ON -DWITH_XML_LOADER:BOOL=ON \
		-DBUILDRELEASE:BOOL=ON

# uses asm that clang fails on
USE_GCC=	yes
USE_LDCONFIG=	yes
WRKSRC=		${WRKDIR}/YafaRay-Core-ec1c0b9

OPTIONS_DEFINE=	PYTHON QT_GUI BLENDER_ADDON
OPTIONS_DEFAULT=	PYTHON QT_GUI BLENDER_ADDON
## TODO: RUBY

OPTIONS_SUB=		yes
QT_GUI_DESC=		QT interface
BLENDER_ADDON_DESC=	Install Blender Addon

BLENDER_ADDON_DISTFILES= Blender_2.62:blenaddon
BLENDER_ADDON_RUN_DEPENDS= blender>=2.62:graphics/blender
BLENADDONDIR=	${WRKDIR}/YafaRay-Blender-2.5-Exporter-e8f3502

PYTHON_CMAKE_BOOL=	WITH_YAF_PY_BINDINGS
PYTHON_USES=		python:3.4

QT_GUI_CMAKE_BOOL=	WITH_QT
QT_GUI_USES=		qt:4
QT_GUI_USE=		QT=gui,moc_build,qmake_build,rcc_build,uic_build
RUBY_CMAKE_ON=		-DWITH_YAF_RUBY_BINDINGS:BOOL=ON
RUBY_CMAKE_OFF=		-DWITH_YAF_RUBY_BINDINGS:BOOL=OFF
RUBY_USE=		USE_RUBY=yes

post-install-BLENDER_ADDON-on:
	@cd ${BLENADDONDIR} && ${COPYTREE_SHARE} . \
		${STAGEDIR}${LOCALBASE}/share/blender/scripts/addons/yafaray/
	@${MKDIR} ${STAGEDIR}${LOCALBASE}/share/blender/scripts/addons/yafaray/bin/
	@cd ${STAGEDIR}${LOCALBASE}/lib && ${LN} -s libyafarayplugin.so \
		../share/blender/scripts/addons/yafaray/bin/

.include <bsd.port.mk>
