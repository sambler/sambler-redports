# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	blender249
PORTVERSION=	2.49b
PORTREVISION=	4
CATEGORIES=	graphics multimedia
MASTER_SITES=	http://download.blender.org/source/ \
		http://mirror.cs.umn.edu/blender.org/source/
DISTFILES=	blender-2.49b.tar.gz

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	3D modeling/rendering/animation/gaming package

LICENSE=	GPLv2

BUILD_DEPENDS=  ${LOCALBASE}/lib/libode.a:${PORTSDIR}/devel/ode
LIB_DEPENDS=	libpng.so:${PORTSDIR}/graphics/png
LIB_DEPENDS+=	libtiff.so:${PORTSDIR}/graphics/tiff
LIB_DEPENDS+=	libIlmImf.so:${PORTSDIR}/graphics/OpenEXR
LIB_DEPENDS+=	libavutil0.so:${PORTSDIR}/multimedia/ffmpeg0
LIB_DEPENDS+=	libopenjpeg.so:${PORTSDIR}/graphics/openjpeg15
LIB_DEPENDS+=	libfreetype.so:${PORTSDIR}/print/freetype2
LIB_DEPENDS+=   libftgl.so:${PORTSDIR}/graphics/ftgl

USES=		cmake:outsource dos2unix openal:al,alut python:2.7 jpeg
WRKSRC=		${WRKDIR}/blender-2.49b
VERS_TAG=	249

WANT_GNOME=	yes
USE_SDL=	sdl
USE_XORG=	x11 xext xmu xi
USE_GL=		gl glu glew
LDFLAGS+=	-L${LOCALBASE}/lib -lX11 -lopenjpeg -lGLEW
# adjust for ffmpeg0
CFLAGS+=	-I${LOCALBASE}/include/ffmpeg0
CXXFLAGS+=	-I${LOCALBASE}/include/ffmpeg0
LDFLAGS+=	-L${LOCALBASE}/lib/ffmpeg0

CMAKE_ARGS+=	-DWITH_BULLET:BOOL=ON -DWITH_DDS:BOOL=ON
CMAKE_ARGS+=	-DWITH_ELBEEM:BOOL=ON -DWITH_FFMPEG:BOOL=ON
CMAKE_ARGS+=	-DFREETYPE_INC:STRING=${LOCALBASE}/include/freetype2
CMAKE_ARGS+=	-DWITH_GAMEENGINE:BOOL=ON
CMAKE_ARGS+=	-DWITH_KETSJI:BOOL=ON -DWITH_OPENAL:BOOL=ON
CMAKE_ARGS+=	-DWITH_OPENEXR:BOOL=ON -DWITH_OPENJPEG:BOOL=ON
CMAKE_ARGS+=	-DWITH_QUICKTIME:BOOL=OFF
CMAKE_ARGS+=	-DWITH_VERSE:BOOL=OFF -DWITH_WEBPLUGIN:BOOL=OFF

SUB_FILES=	blender blenderplayer
DOS2UNIX_FILES=	extern/bullet2/src/BulletSoftBody/btSoftBodyInternals.h \
		extern/libopenjpeg/opj_malloc.h

LANG=		ar bg ca cs de el es fi fr hr hr_HR it ja ko nl pl pt_BR ro \
		ru sr sr@Latn sv uk zh_CN

OPTIONS_DEFINE=	HEADLESS SECURITY PLAYER NLS OPENMP
OPTIONS_DEFAULT=	SECURITY PLAYER NLS

OPTIONS_SUB=	yes
HEADLESS_DESC=	Disable user interface
SECURITY_DESC=	Disable scripts auto-run
PLAYER_DESC=	Build blender player
NLS_DESC=	Include translations

HEADLESS_CMAKE_ON=	-DWITH_HEADLESS:BOOL=ON
HEADLESS_CMAKE_OFF=	-DWITH_HEADLESS:BOOL=OFF

NLS_CMAKE_ON=		-DWITH_INTERNATIONAL:BOOL=ON
NLS_CMAKE_OFF=		-DWITH_INTERNATIONAL:BOOL=OFF
NLS_USES=		gettext iconv
NLS_LDFLAGS=		-L${LOCALBASE}/lib -lintl

OPENMP_CMAKE_ON=	-DWITH_OPENMP:BOOL=ON
OPENMP_CMAKE_OFF=	-DWITH_OPENMP:BOOL=OFF

PLAYER_CMAKE_ON=	-DWITH_PLAYER:BOOL=ON
PLAYER_CMAKE_OFF=	-DWITH_PLAYER:BOOL=OFF

SECURITY_CMAKE_ON=	-DWITH_PYTHON_SECURITY:BOOL=ON
SECURITY_CMAKE_OFF=	-DWITH_PYTHON_SECURITY:BOOL=OFF

OUTDIR=		${WRKSRC}/bin

.include <bsd.port.options.mk>

do-install:
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blender
	@${INSTALL_SCRIPT} ${WRKDIR}/blender ${STAGEDIR}/${PREFIX}/bin/blender-${VERS_TAG}
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/bin/blender \
		${STAGEDIR}/${PREFIX}/bin/blender-bin-${VERS_TAG}
	@${ECHO} bin/blender-${VERS_TAG} >> ${TMPPLIST}
	@${ECHO} bin/blender-bin-${VERS_TAG} >> ${TMPPLIST}

.if ${PORT_OPTIONS:MPLAYER}
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blenderplayer
	@${INSTALL_SCRIPT} ${WRKDIR}/blenderplayer ${STAGEDIR}/${PREFIX}/bin/blenderplayer-${VERS_TAG}
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/bin/blenderplayer \
		${STAGEDIR}/${PREFIX}/bin/blenderplayer-bin-${VERS_TAG}
	@${ECHO} bin/blenderplayer-${VERS_TAG} >> ${TMPPLIST}
	@${ECHO} bin/blenderplayer-bin-${VERS_TAG} >> ${TMPPLIST}
.endif

	@${MKDIR} ${STAGEDIR}/${DATADIR}
	@${CP} -R ${WRKSRC}/release/scripts ${STAGEDIR}/${DATADIR}
	@${INSTALL_DATA} ${WRKSRC}/bin/.blender/.Blanguages ${STAGEDIR}/${DATADIR}
	@${INSTALL_DATA} ${WRKSRC}/bin/.blender/.bfont.ttf ${STAGEDIR}/${DATADIR}
	@${ECHO} ${DATADIR_REL}/.Blanguages >> ${TMPPLIST}
	@${ECHO} ${DATADIR_REL}/.bfont.ttf >> ${TMPPLIST}
	@(cd ${WRKSRC}/release; ${FIND} scripts -type f) | ${SORT} | ${SED} "s|^|${DATADIR_REL}/|" >> ${TMPPLIST}

.if ${PORT_OPTIONS:MNLS}
.for ii in ${LANG}
	@${MKDIR} ${STAGEDIR}/${DATADIR}/datafiles/locale/${ii}/LC_MESSAGES
	@${INSTALL_DATA} \
		${WRKSRC}/bin/.blender/locale/${ii}/LC_MESSAGES/blender.mo \
		${STAGEDIR}/${DATADIR}/datafiles/locale/${ii}/LC_MESSAGES/blender.mo
.endfor
	@(cd ${OUTDIR}/.blender; ${FIND} locale -type f) | ${SORT} | ${SED} "s|^|${DATADIR_REL}/datafiles/|" >> ${TMPPLIST}
.endif

.include <bsd.port.mk>
