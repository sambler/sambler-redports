# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	blender-249
PORTVERSION=	2.49b
PORTREVISION=	0
CATEGORIES=	graphics multimedia
MASTER_SITES=	http://download.blender.org/source/ \
		http://mirror.cs.umn.edu/blender.org/source/ \
		http://public.planetmirror.com/pub/blender/source/
DISTFILES=	blender-2.49b.tar.gz

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	3D modeling/rendering/animation/gaming package

LICENSE=	GPLv2

BUILD_DEPENDS=  ${LOCALBASE}/lib/libode.a:${PORTSDIR}/devel/ode
LIB_DEPENDS=	jpeg:${PORTSDIR}/graphics/jpeg
LIB_DEPENDS+=	png15:${PORTSDIR}/graphics/png
LIB_DEPENDS+=	tiff:${PORTSDIR}/graphics/tiff
LIB_DEPENDS+=	IlmImf:${PORTSDIR}/graphics/OpenEXR
LIB_DEPENDS+=	avutil:${PORTSDIR}/multimedia/ffmpeg
LIB_DEPENDS+=	openjpeg:${PORTSDIR}/graphics/openjpeg
LIB_DEPENDS+=	freetype:${PORTSDIR}/print/freetype2
LIB_DEPENDS+=   ftgl.2:${PORTSDIR}/graphics/ftgl

USES=		cmake:outsource
MAKE_JOBS_SAFE=	yes
WRKSRC=		${WRKDIR}/blender-2.49b

USE_PYTHON=	2.7
WANT_GNOME=	yes
USE_OPENAL=	al alut
USE_SDL=	sdl
USE_XORG=	x11 xext xmu xi
USE_GL=		gl glu glew
USE_GCC=	4.6+
LDFLAGS+=	-lX11 -lopenjpeg -lGLEW

CMAKE_ARGS+=	-DWITH_BULLET=ON -DWITH_DDS=ON
CMAKE_ARGS+=	-DWITH_ELBEEM=ON -DWITH_FFMPEG=ON
CMAKE_ARGS+=	-DWITH_GAMEENGINE=OFF
CMAKE_ARGS+=	-DWITH_KETSJI=ON -DWITH_OPENAL=ON
CMAKE_ARGS+=	-DWITH_OPENEXR=ON -DWITH_OPENJPEG=ON
CMAKE_ARGS+=	-DWITH_OPENMP=ON -DWITH_QUICKTIME=OFF
CMAKE_ARGS+=	-DWITH_VERSE=OFF -DWITH_WEBPLUGIN=OFF

SUB_FILES=	blender 
#blenderplayer
#MAN1=		blender.1

LANG=		ar bg ca cs de el es fi fr hr hr_HR it ja ko nl pl pt_BR ro \
		ru sr sr@Latn sv uk zh_CN

OPTIONS_DEFINE=	HEADLESS SECURITY PLAYER NLS
OPTIONS_DEFAULT=	SECURITY NLS

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
BROKEN= blender-249 player not currently working
CMAKE_ARGS+=	-DWITH_PLAYER:BOOL=ON
PLIST_SUB+=	PLAYER=""
.else
CMAKE_ARGS+=	-DWITH_PLAYER:BOOL=OFF
PLIST_SUB+=	PLAYER="@comment "
.endif

.if ${PORT_OPTIONS:MNLS}
CMAKE_ARGS+=	-DWITH_INTERNATIONAL:BOOL=ON
PLIST_SUB+=	NLS=""
USE_GETTEXT=	yes
USE_ICONV=	yes
.else
CMAKE_ARGS+=	-DWITH_INTERNATIONAL:BOOL=OFF
PLIST_SUB+=	NLS="@comment "
.endif

do-install:
	@${INSTALL_SCRIPT} ${WRKDIR}/blender ${PREFIX}/bin/blender-249
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/bin/blender \
		${PREFIX}/bin/blender-bin-249
	@${MKDIR} ${DATADIR}

.if ${PORT_OPTIONS:MPLAYER}
	@${INSTALL_SCRIPT} ${WRKDIR}/blenderplayer ${PREFIX}/bin/blenderplayer-249
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/bin/blenderplayer \
		${PREFIX}/bin/blenderplayer-bin-249
.endif

	@${CP} -R ${WRKSRC}/release/scripts ${DATADIR}
	@${INSTALL_DATA} ${WRKSRC}/bin/.blender/.Blanguages ${DATADIR}
	@${INSTALL_DATA} ${WRKSRC}/bin/.blender/.bfont.ttf ${DATADIR}

.if ${PORT_OPTIONS:MNLS}
.for ii in ${LANG}
	@${MKDIR} ${DATADIR}/datafiles/locale/${ii}/LC_MESSAGES
	@${INSTALL_DATA} \
		${WRKSRC}/bin/.blender/locale/${ii}/LC_MESSAGES/blender.mo \
		${DATADIR}/datafiles/locale/${ii}/LC_MESSAGES/blender.mo
.endfor
.endif

.include <bsd.port.mk>
