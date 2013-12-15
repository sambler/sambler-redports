# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	blender249
PORTVERSION=	2.49b
PORTREVISION=	3
CATEGORIES=	graphics multimedia
MASTER_SITES=	http://download.blender.org/source/ \
		http://mirror.cs.umn.edu/blender.org/source/ \
		http://public.planetmirror.com/pub/blender/source/
DISTFILES=	blender-2.49b.tar.gz

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	3D modeling/rendering/animation/gaming package

LICENSE=	GPLv2

BUILD_DEPENDS=  ${LOCALBASE}/lib/libode.a:${PORTSDIR}/devel/ode
LIB_DEPENDS=	libjpeg.so:${PORTSDIR}/graphics/jpeg
LIB_DEPENDS+=	libpng15.so:${PORTSDIR}/graphics/png
LIB_DEPENDS+=	libtiff.so:${PORTSDIR}/graphics/tiff
LIB_DEPENDS+=	libIlmImf.so:${PORTSDIR}/graphics/OpenEXR
LIB_DEPENDS+=	libavutil0.so:${PORTSDIR}/multimedia/ffmpeg0
LIB_DEPENDS+=	libopenjpeg.so:${PORTSDIR}/graphics/openjpeg
LIB_DEPENDS+=	libfreetype.so:${PORTSDIR}/print/freetype2
LIB_DEPENDS+=   libftgl.so:${PORTSDIR}/graphics/ftgl

USES=		cmake:outsource
WRKSRC=		${WRKDIR}/blender-2.49b
VERS_TAG=	249

USE_PYTHON=	2.7
WANT_GNOME=	yes
USE_OPENAL=	al alut
USE_SDL=	sdl
USE_XORG=	x11 xext xmu xi
USE_GL=		gl glu glew
LDFLAGS+=	-L${LOCALBASE}/lib -lX11 -lopenjpeg -lGLEW
# adjust for ffmpeg0
CFLAGS+=	-I${LOCALBASE}/include/ffmpeg0
CXXFLAGS+=	-I${LOCALBASE}/include/ffmpeg0
LDFLAGS+=	-L${LOCALBASE}/lib/ffmpeg0

CMAKE_ARGS+=	-DWITH_BULLET=ON -DWITH_DDS=ON
CMAKE_ARGS+=	-DWITH_ELBEEM=ON -DWITH_FFMPEG=ON
CMAKE_ARGS+=	-DWITH_GAMEENGINE=ON
CMAKE_ARGS+=	-DWITH_KETSJI=ON -DWITH_OPENAL=ON
CMAKE_ARGS+=	-DWITH_OPENEXR=ON -DWITH_OPENJPEG=ON
CMAKE_ARGS+=	-DWITH_OPENMP=ON -DWITH_QUICKTIME=OFF
CMAKE_ARGS+=	-DWITH_VERSE=OFF -DWITH_WEBPLUGIN=OFF

SUB_FILES=	blender blenderplayer

LANG=		ar bg ca cs de el es fi fr hr hr_HR it ja ko nl pl pt_BR ro \
		ru sr sr@Latn sv uk zh_CN

OPTIONS_DEFINE=	HEADLESS SECURITY PLAYER NLS
OPTIONS_DEFAULT=	SECURITY PLAYER NLS

HEADLESS_DESC=	"Disable user interface"
SECURITY_DESC=	"Disable scripts auto-run"
PLAYER_DESC=	"Build blender player"
NLS_DESC=	"Include translations"

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MHEADLESS}
CMAKE_ARGS+=	-DWITH_HEADLESS:BOOL=ON
.else
CMAKE_ARGS+=	-DWITH_HEADLESS:BOOL=OFF
.endif

.if ${PORT_OPTIONS:MSECURITY}
CMAKE_ARGS+=	-DWITH_PYTHON_SECURITY:BOOL=ON
.else
CMAKE_ARGS+=	-DWITH_PYTHON_SECURITY:BOOL=OFF
.endif

.if ${PORT_OPTIONS:MPLAYER}
CMAKE_ARGS+=	-DWITH_PLAYER:BOOL=ON
PLIST_SUB+=	PLAYER=""
.else
CMAKE_ARGS+=	-DWITH_PLAYER:BOOL=OFF
PLIST_SUB+=	PLAYER="@comment "
.endif

.if ${PORT_OPTIONS:MNLS}
CMAKE_ARGS+=	-DWITH_INTERNATIONAL:BOOL=ON
PLIST_SUB+=	NLS=""
USES+=		gettext iconv
LDFLAGS+=	-lintl
.else
CMAKE_ARGS+=	-DWITH_INTERNATIONAL:BOOL=OFF
PLIST_SUB+=	NLS="@comment "
.endif

do-install:
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blender
	@${INSTALL_SCRIPT} ${WRKDIR}/blender ${STAGEDIR}/${PREFIX}/bin/blender-${VERS_TAG}
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/bin/blender \
		${STAGEDIR}/${PREFIX}/bin/blender-bin-${VERS_TAG}

.if ${PORT_OPTIONS:MPLAYER}
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blenderplayer
	@${INSTALL_SCRIPT} ${WRKDIR}/blenderplayer ${STAGEDIR}/${PREFIX}/bin/blenderplayer-${VERS_TAG}
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/bin/blenderplayer \
		${STAGEDIR}/${PREFIX}/bin/blenderplayer-bin-${VERS_TAG}
.endif

	@${MKDIR} ${STAGEDIR}/${DATADIR}
	@${CP} -R ${WRKSRC}/release/scripts ${STAGEDIR}/${DATADIR}
	@${INSTALL_DATA} ${WRKSRC}/bin/.blender/.Blanguages ${STAGEDIR}/${DATADIR}
	@${INSTALL_DATA} ${WRKSRC}/bin/.blender/.bfont.ttf ${STAGEDIR}/${DATADIR}

.if ${PORT_OPTIONS:MNLS}
.for ii in ${LANG}
	@${MKDIR} ${STAGEDIR}/${DATADIR}/datafiles/locale/${ii}/LC_MESSAGES
	@${INSTALL_DATA} \
		${WRKSRC}/bin/.blender/locale/${ii}/LC_MESSAGES/blender.mo \
		${STAGEDIR}/${DATADIR}/datafiles/locale/${ii}/LC_MESSAGES/blender.mo
.endfor
.endif

.include <bsd.port.mk>