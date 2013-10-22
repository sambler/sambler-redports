# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	blender262
PORTVERSION=	2.62
PORTREVISION=	3
CATEGORIES=	graphics multimedia
MASTER_SITES=	http://download.blender.org/source/ \
		http://mirror.cs.umn.edu/blender.org/source/ \
		http://public.planetmirror.com/pub/blender/source/
DISTFILES=	blender-${PORTVERSION}.tar.gz

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	3D modeling/rendering/animation/gaming package

LICENSE=	GPLv2

LIB_DEPENDS=	libsamplerate.so:${PORTSDIR}/audio/libsamplerate
LIB_DEPENDS+=	libsndfile.so:${PORTSDIR}/audio/libsndfile
LIB_DEPENDS+=	libboost_thread.so:${PORTSDIR}/devel/boost-libs
LIB_DEPENDS+=	libunwind.so:${PORTSDIR}/devel/libunwind
LIB_DEPENDS+=	libjpeg.so:${PORTSDIR}/graphics/jpeg
LIB_DEPENDS+=	libIlmImf.so:${PORTSDIR}/graphics/OpenEXR
LIB_DEPENDS+=	libopenjpeg.so:${PORTSDIR}/graphics/openjpeg
LIB_DEPENDS+=	libpng15.so:${PORTSDIR}/graphics/png
LIB_DEPENDS+=	libtiff.so:${PORTSDIR}/graphics/tiff
LIB_DEPENDS+=	libfftw3.so:${PORTSDIR}/math/fftw3
LIB_DEPENDS+=	libavutil0.so:${PORTSDIR}/multimedia/ffmpeg0
LIB_DEPENDS+=	libfreetype.so:${PORTSDIR}/print/freetype2
RUN_DEPENDS=	xdg-mime:${PORTSDIR}/devel/xdg-utils
.if exists(${PORTSDIR}/math/py-numpy32)
# PYTHON_SITELIBDIR most likely points to python2.7/site-packages
# we specifically want a 3.2 version installed
RUN_DEPENDS+=	${LOCALBASE}/lib/python3.2/site-packages/numpy/__init__.py:${PORTSDIR}/math/py-numpy32
CMAKE_ARGS+=	-DPYTHON_NUMPY_PATH:STRING=${LOCALBASE}/lib/python3.2/site-packages
.endif

USES=		cmake:outsource
WRKSRC=		${WRKDIR}/blender-${PORTVERSION}

USE_PYTHON=	3.2
WANT_GNOME=	yes
USE_GNOME=	desktopfileutils
USE_OPENAL=	al alut
USE_SDL=	sdl
USE_XORG=	x11 xext xmu
USE_GL=		glew
CFLAGS+=	-I${WRKSRC}/extern/libopenjpeg
LDFLAGS+=	-rpath ${LOCALBASE}/lib/gcc46
# adjust for ffmpeg0
CFLAGS+=	-I${LOCALBASE}/include/ffmpeg0
CXXFLAGS+=	-I${LOCALBASE}/include/ffmpeg0
LDFLAGS+=	-L${LOCALBASE}/lib/ffmpeg0
CMAKE_ARGS+=	-DFFMPEG_LIBRARIES:STRING="avformat0;avcodec0;avutil0;avdevice0;swscale0"

CMAKE_ARGS+=	-DWITH_BUILDINFO:BOOL=ON -DWITH_AUDASPACE:BOOL=ON
CMAKE_ARGS+=	-DWITH_BLENDER:BOOL=ON -DWITH_BUILTIN_GLEW:BOOL=ON
CMAKE_ARGS+=	-DWITH_BULLET:BOOL=ON -DWITH_CARVE:BOOL=ON
CMAKE_ARGS+=	-DWITH_CODEC_FFMPEG:BOOL=ON -DWITH_CODEC_SNDFILE:BOOL=ON
CMAKE_ARGS+=	-DWITH_FFTW3:BOOL=ON -DWITH_GAMEENGINE:BOOL=ON
CMAKE_ARGS+=	-DWITH_IK_ITASC:BOOL=ON -DWITH_IMAGE_CINEON:BOOL=ON 
CMAKE_ARGS+=	-DWITH_IMAGE_DDS:BOOL=ON -DWITH_IMAGE_FRAMESERVER:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_HDR:BOOL=ON -DWITH_IMAGE_OPENEXR:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_OPENJPEG:BOOL=ON -DWITH_IMAGE_REDCODE:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_TIFF:BOOL=ON -DWITH_INSTALL_PORTABLE:BOOL=ON
CMAKE_ARGS+=	-DWITH_LIBMV:BOOL=ON -DWITH_LZMA:BOOL=ON -DWITH_LZO:BOOL=ON
CMAKE_ARGS+=	-DWITH_MEM_JEMALLOC:BOOL=OFF -DWITH_MOD_BOOLEAN:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_CLOTH_ELTOPO:BOOL=ON -DWITH_MOD_DECIMATE=ON
CMAKE_ARGS+=	-DWITH_MOD_FLUID:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_OCEANSIM:BOOL=ON -DWITH_MOD_REMESH:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_SMOKE:BOOL=ON -DWITH_OPENAL:BOOL=ON
CMAKE_ARGS+=	-DWITH_OPENCOLLADA:BOOL=OFF -DWITH_OPENMP:BOOL=ON
CMAKE_ARGS+=	-DWITH_INPUT_NDOF:BOOL=OFF -DWITH_PYTHON:BOOL=ON
CMAKE_ARGS+=	-DWITH_PYTHON_INSTALL:BOOL=OFF -DWITH_PYTHON_MODULE:BOOL=OFF
CMAKE_ARGS+=	-DWITH_PYTHON_SAFETY:BOOL=OFF 
CMAKE_ARGS+=	-DWITH_RAYOPTIMIZATION:BOOL=ON -DWITH_SDL:BOOL=ON
CMAKE_ARGS+=	-DWITH_X11_XF86VMODE:BOOL=ON -DWITH_X11_XINPUT:BOOL=ON

SUB_FILES=	blender blenderplayer

OUTDIR=		${INSTALL_WRKSRC}/bin/2.62

OPTIONS_DEFINE=	HEADLESS SECURITY PLAYER JACK NLS
OPTIONS_DEFAULT=	SECURITY PLAYER NLS JACK

HEADLESS_DESC=	"Disable user interface"
SECURITY_DESC=	"Disable scripts auto-run"
PLAYER_DESC=	"Build blender player"
JACK_DESC=	"Audio support using JackAudio"
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
.else
CMAKE_ARGS+=	-DWITH_PLAYER:BOOL=OFF
.endif

.if ${PORT_OPTIONS:MJACK}
LIB_DEPENDS+=	libjack.so:${PORTSDIR}/audio/jack
CMAKE_ARGS+=	-DWITH_JACK:BOOL=ON
.else
CMAKE_ARGS+=	-DWITH_JACK:BOOL=OFF
.endif

.if ${PORT_OPTIONS:MNLS}
CMAKE_ARGS+=	-DWITH_INTERNATIONAL:BOOL=ON
USES+=		gettext iconv
.else
CMAKE_ARGS+=	-DWITH_INTERNATIONAL:BOOL=OFF
.endif

do-install:
	@${INSTALL_SCRIPT} ${WRKDIR}/blender ${STAGEDIR}/${PREFIX}/bin/blender-262
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/bin/blender \
		${STAGEDIR}/${PREFIX}/bin/blender-bin-262
	@${MKDIR} ${STAGEDIR}/${DATADIR}
	@${INSTALL_SCRIPT} ${WRKSRC}/release/bin/blender-thumbnailer.py \
		${STAGEDIR}/${PREFIX}/bin/blender-thumbnailer-262.py
	@${ECHO} bin/blender-262 >> ${TMPPLIST}
	@${ECHO} bin/blender-bin-262 >> ${TMPPLIST}
	@${ECHO} bin/blender-thumbnailer-262.py >> ${TMPPLIST}

.if ${PORT_OPTIONS:MPLAYER}
	@${INSTALL_SCRIPT} ${WRKDIR}/blenderplayer ${STAGEDIR}/${PREFIX}/bin/blenderplayer-262
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/bin/blenderplayer \
		${STAGEDIR}/${PREFIX}/bin/blenderplayer-bin-262
	@${ECHO} bin/blenderplayer-262 >> ${TMPPLIST}
	@${ECHO} bin/blenderplayer-bin-262 >> ${TMPPLIST}
.endif

	@${CP} -R ${WRKSRC}/release/scripts ${STAGEDIR}/${DATADIR}/
	@${INSTALL_DATA} ${WRKSRC}/release/freedesktop/icons/scalable/apps/blender.svg \
		${STAGEDIR}/${PREFIX}/share/pixmaps/blender-262.svg
	@(cd ${WRKSRC}/release; ${FIND} scripts -type f) | ${SORT} | ${SED} "s|^|${DATADIR_REL}/|" >> ${TMPPLIST}
	@(cd ${WRKSRC}/release; ${FIND} scripts -type d) | ${SORT} -r | ${SED} "s|^|@dirrm ${DATADIR_REL}/|" >> ${TMPPLIST}
	@${ECHO} share/pixmaps/blender-262.svg >> ${TMPPLIST}

.if ${PORT_OPTIONS:MNLS}
	@cd ${WRKSRC}/release && ${COPYTREE_SHARE} datafiles/locale ${STAGEDIR}/${DATADIR}/
	@(cd ${WRKSRC}/release; ${FIND} datafiles/locale -type f -name blender.mo) | ${SORT} | ${SED} "s|^|${DATADIR_REL}/|" >> ${TMPPLIST}
	@(cd ${WRKSRC}/release; ${FIND} datafiles/locale -type f -name languages) | ${SORT} | ${SED} "s|^|${DATADIR_REL}/|" >> ${TMPPLIST}
	@(cd ${WRKSRC}/release; ${FIND} datafiles/locale -type d) | ${SORT} -r | ${SED} "s|^|@dirrm ${DATADIR_REL}/|" >> ${TMPPLIST}
.endif

	@cd ${WRKSRC}/release && ${COPYTREE_SHARE} datafiles/fonts ${STAGEDIR}/${DATADIR}/
	@(cd ${WRKSRC}/release; ${FIND} datafiles/fonts -type f) | ${SORT} | ${SED} "s|^|${DATADIR_REL}/|" >> ${TMPPLIST}
	@(cd ${WRKSRC}/release; ${FIND} datafiles/fonts -type d) | ${SORT} -r | ${SED} "s|^|@dirrm ${DATADIR_REL}/|" >> ${TMPPLIST}

	@${MKDIR} ${STAGEDIR}/${DESKTOPDIR}
	@${INSTALL_DATA} ${WRKSRC}/release/freedesktop/blender.desktop \
		${STAGEDIR}/${DESKTOPDIR}/blender-262.desktop
	@-update-desktop-database -q
	@${ECHO} share/applications/blender-262.desktop >> ${TMPPLIST}

	@${ECHO} @dirrm ${DATADIR_REL}/datafiles >> ${TMPPLIST}
	@${ECHO} @dirrm ${DATADIR_REL} >> ${TMPPLIST}

.include <bsd.port.mk>
