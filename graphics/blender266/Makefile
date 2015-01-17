# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	blender266
PORTVERSION=	2.66a
PORTREVISION=	9
CATEGORIES=	graphics multimedia
MASTER_SITES=	http://download.blender.org/source/ \
		http://mirror.cs.umn.edu/blender.org/source/
DISTFILES=	blender-${PORTVERSION}.tar.gz

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	3D modeling/rendering/animation/gaming package

LICENSE=	GPLv2

LIB_DEPENDS=	libsamplerate.so:${PORTSDIR}/audio/libsamplerate
LIB_DEPENDS+=	libsndfile.so:${PORTSDIR}/audio/libsndfile
LIB_DEPENDS+=	libboost_thread.so:${PORTSDIR}/devel/boost-libs
LIB_DEPENDS+=	libjpeg.so:${PORTSDIR}/graphics/jpeg
LIB_DEPENDS+=	libOpenColorIO.so:${PORTSDIR}/graphics/opencolorio
LIB_DEPENDS+=	libIlmImf.so:${PORTSDIR}/graphics/OpenEXR
LIB_DEPENDS+=	libOpenImageIO14.so:${PORTSDIR}/graphics/openimageio14
LIB_DEPENDS+=	libopenjpeg.so:${PORTSDIR}/graphics/openjpeg15
LIB_DEPENDS+=	libpng.so:${PORTSDIR}/graphics/png
LIB_DEPENDS+=	libtiff.so:${PORTSDIR}/graphics/tiff
LIB_DEPENDS+=	libfftw3.so:${PORTSDIR}/math/fftw3
LIB_DEPENDS+=	libavutil0.so:${PORTSDIR}/multimedia/ffmpeg0
LIB_DEPENDS+=	libfreetype.so:${PORTSDIR}/print/freetype2
RUN_DEPENDS=	xdg-mime:${PORTSDIR}/devel/xdg-utils

USES=		cmake:outsource compiler shebangfix desktop-file-utils openal:al,alut
USES+=		python:3.3
WRKSRC=		${WRKDIR}/blender-${PORTVERSION}
OUTDIR=		${INSTALL_WRKSRC}/bin/2.66
VERS_TAG=	266

USE_SDL=	sdl
USE_XORG=	x11 xext xmu
USE_GL=		glew
# adjust for ffmpeg0
CFLAGS+=	-I${LOCALBASE}/include/ffmpeg0
CXXFLAGS+=	-I${LOCALBASE}/include/ffmpeg0
LDFLAGS+=	-L${LOCALBASE}/lib/ffmpeg0
CMAKE_ARGS+=	-DFFMPEG_LIBRARIES:STRING="avformat0;avcodec0;avutil0;avdevice0;swscale0"

CMAKE_ARGS+=	-DWITH_BUILDINFO:BOOL=ON -DWITH_AUDASPACE:BOOL=ON
CMAKE_ARGS+=	-DWITH_BLENDER:BOOL=ON -DWITH_BULLET:BOOL=ON
CMAKE_ARGS+=	-DWITH_CODEC_FFMPEG:BOOL=ON -DWITH_CODEC_SNDFILE:BOOL=ON
CMAKE_ARGS+=	-DWITH_COMPOSITOR:BOOL=ON -DWITH_CYCLES:BOOL=ON
CMAKE_ARGS+=	-DWITH_CYCLES_CUDA_BINARIES:BOOL=OFF -DWITH_CYCLES_TEST:BOOL=OFF
CMAKE_ARGS+=	-DWITH_FFTW3:BOOL=ON -DWITH_GAMEENGINE:BOOL=ON
CMAKE_ARGS+=	-DWITH_IK_ITASC:BOOL=ON -DWITH_IK_SOLVER:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_CINEON:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_DDS:BOOL=ON -DWITH_IMAGE_FRAMESERVER:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_HDR:BOOL=ON -DWITH_IMAGE_OPENEXR:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_OPENJPEG:BOOL=ON -DWITH_IMAGE_REDCODE:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_TIFF:BOOL=ON -DWITH_INSTALL_PORTABLE:BOOL=ON
CMAKE_ARGS+=	-DWITH_LIBMV:BOOL=ON -DWITH_LZMA:BOOL=ON -DWITH_LZO:BOOL=ON
CMAKE_ARGS+=	-DWITH_MEM_JEMALLOC:BOOL=OFF -DWITH_MOD_BOOLEAN:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_CLOTH_ELTOPO:BOOL=OFF -DWITH_MOD_FLUID:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_OCEANSIM:BOOL=ON -DWITH_MOD_REMESH:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_SMOKE:BOOL=ON -DWITH_OPENAL:BOOL=ON
CMAKE_ARGS+=	-DWITH_OPENCOLORIO:BOOL=ON -DWITH_OPENCOLLADA:BOOL=OFF
CMAKE_ARGS+=	-DWITH_INPUT_NDOF:BOOL=OFF -DWITH_PYTHON:BOOL=ON
CMAKE_ARGS+=	-DWITH_PYTHON_INSTALL:BOOL=OFF -DWITH_PYTHON_MODULE:BOOL=OFF
CMAKE_ARGS+=	-DWITH_PYTHON_INSTALL_NUMPY:BOOL=OFF
CMAKE_ARGS+=	-DWITH_RAYOPTIMIZATION:BOOL=ON -DWITH_SDL:BOOL=ON
CMAKE_ARGS+=	-DWITH_STATIC_LIBS:BOOL=OFF
CMAKE_ARGS+=	-DWITH_SYSTEM_GLEW:BOOL=ON -DWITH_SYSTEM_OPENJPEG:BOOL=ON
CMAKE_ARGS+=	-DWITH_X11_XF86VMODE:BOOL=ON -DWITH_X11_XINPUT:BOOL=ON

SUB_FILES=	blender blenderplayer
python_CMD=	${PYTHON_CMD}
SHEBANG_FILES=	release/bin/blender-thumbnailer.py \
		release/scripts/modules/bl_i18n_utils/merge_po.py \
		release/scripts/modules/blend_render_info.py \
		doc/manpage/blender.1.py

OPTIONS_DEFINE=	HEADLESS SECURITY PLAYER JACK NLS OSL OPENMP
OPTIONS_DEFAULT=	SECURITY PLAYER NLS OSL JACK

OPTIONS_SUB=	yes
HEADLESS_DESC=	"Disable user interface"
SECURITY_DESC=	"Disable scripts auto-run"
PLAYER_DESC=	"Build blender player"
JACK_DESC=	"Audio support using JackAudio"
NLS_DESC=	"Include translations"
OSL_DESC=	"OSL shading support"

HEADLESS_CMAKE_ON=	-DWITH_HEADLESS:BOOL=ON
HEADLESS_CMAKE_OFF=	-DWITH_HEADLESS:BOOL=OFF

JACK_CMAKE_ON=		-DWITH_JACK:BOOL=ON
JACK_CMAKE_OFF=		-DWITH_JACK:BOOL=OFF
JACK_LIB_DEPENDS=	libjack.so:${PORTSDIR}/audio/jack

NLS_CMAKE_ON=		-DWITH_INTERNATIONAL:BOOL=ON
NLS_CMAKE_OFF=		-DWITH_INTERNATIONAL:BOOL=OFF
NLS_USES=		gettext iconv
NLS_LDFLAGS=		-L${LOCALBASE}/lib -lintl

OPENMP_CMAKE_ON=	-DWITH_OPENMP:BOOL=ON
OPENMP_CMAKE_OFF=	-DWITH_OPENMP:BOOL=OFF

OSL_CMAKE_ON=		-DWITH_CYCLES_OSL:BOOL=ON \
			-DWITH_LLVM:BOOL=ON \
			-DLLVM_STATIC:BOOL=ON \
			-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config33" \
			-DOSL_COMPILER:STRING="${LOCALBASE}/bin/oslc14" \
			-DOSL_INCLUDES:STRING="${LOCALBASE}/include" \
			-DOSL_LIB_COMP:STRING="${LOCALBASE}/lib/liboslcomp14.so" \
			-DOSL_LIB_EXEC:STRING="${LOCALBASE}/lib/liboslexec14.so" \
			-DOSL_LIB_QUERY:STRING="${LOCALBASE}/lib/liboslquery14.so"
OSL_CMAKE_OFF=		-DWITH_CYCLES_OSL:BOOL=OFF
OSL_LIB_DEPENDS=	liboslcomp14.so:${PORTSDIR}/graphics/openshadinglanguage14

PLAYER_CMAKE_ON=	-DWITH_PLAYER:BOOL=ON
PLAYER_CMAKE_OFF=	-DWITH_PLAYER:BOOL=OFF

SECURITY_CMAKE_ON=	-DWITH_PYTHON_SECURITY:BOOL=ON
SECURITY_CMAKE_OFF=	-DWITH_PYTHON_SECURITY:BOOL=OFF

.include <bsd.port.options.mk>

post-patch:
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' \
		${WRKSRC}/release/bin/blender-thumbnailer.py
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' \
		${WRKSRC}/release/freedesktop/blender.desktop
	@cd ${WRKSRC}/intern/cycles && ${REINPLACE_CMD} \
		-e 's/__align/cycles_align/' \
		-e 's/__global/cycles_global/g' \
		util/util_types.h kernel/kernel_compat_cuda.h \
		kernel/kernel_displace.h kernel/kernel_film.h \
		kernel/kernel_passes.h kernel/kernel_path.h \
		kernel/kernel_random.h
	@${FIND} ${WRKSRC}/intern/cycles -name "*.cpp" -or -name "*.h" | \
		${XARGS} ${REINPLACE_CMD} -i '' -e 's|<OpenImageIO/|<OpenImageIO14/|g'
	@${FIND} ${WRKSRC}/intern/cycles -name "*.cpp" -or -name "*.h" | \
		${XARGS} ${REINPLACE_CMD} -i '' -e 's|<OSL/|<OSL14/|g'

# We ignore MAKE_ARGS, since those would set DESTDIR for make stage,
# which in turn would cause make install to install everything in a
# wrong location
do-install:
	@(cd ${INSTALL_WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE_CMD} \
		${MAKE_FLAGS} ${MAKEFILE} ${INSTALL_TARGET})

post-install:
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blender
	@${INSTALL_SCRIPT} ${WRKDIR}/blender ${STAGEDIR}/${PREFIX}/bin/blender-${VERS_TAG}
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/bin/blender \
		${STAGEDIR}/${PREFIX}/bin/blender-bin-${VERS_TAG}
	@${MKDIR} ${STAGEDIR}/${DATADIR}
	@${INSTALL_SCRIPT} ${WRKSRC}/release/bin/blender-thumbnailer.py \
		${STAGEDIR}/${PREFIX}/bin/blender-thumbnailer-${VERS_TAG}.py
	@${ECHO} bin/blender-${VERS_TAG} >> ${TMPPLIST}
	@${ECHO} bin/blender-bin-${VERS_TAG} >> ${TMPPLIST}
	@${ECHO} bin/blender-thumbnailer-${VERS_TAG}.py >> ${TMPPLIST}

.if ${PORT_OPTIONS:MPLAYER}
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blenderplayer
	@${INSTALL_SCRIPT} ${WRKDIR}/blenderplayer ${STAGEDIR}/${PREFIX}/bin/blenderplayer-${VERS_TAG}
	@${INSTALL_PROGRAM} ${INSTALL_WRKSRC}/bin/blenderplayer \
		${STAGEDIR}/${PREFIX}/bin/blenderplayer-bin-${VERS_TAG}
	@${ECHO} bin/blenderplayer-${VERS_TAG} >> ${TMPPLIST}
	@${ECHO} bin/blenderplayer-bin-${VERS_TAG} >> ${TMPPLIST}
.endif

	${MKDIR} ${STAGEDIR}${DATADIR}
	(cd ${OUTDIR} && ${COPYTREE_SHARE} scripts ${STAGEDIR}${DATADIR})
	@${INSTALL_DATA} ${INSTALL_WRKSRC}/bin/blender.svg \
		${STAGEDIR}/${PREFIX}/share/pixmaps/blender-${VERS_TAG}.svg
	@(cd ${OUTDIR}; ${FIND} scripts -type f) | ${SORT} | ${SED} "s|^|${DATADIR_REL}/|" >> ${TMPPLIST}
	@${ECHO} share/pixmaps/blender-${VERS_TAG}.svg >> ${TMPPLIST}

	@cd ${OUTDIR} && ${COPYTREE_SHARE} datafiles/colormanagement ${STAGEDIR}/${DATADIR}
	@(cd ${OUTDIR}; ${FIND} datafiles/colormanagement -type f) | ${SORT} | ${SED} "s|^|${DATADIR_REL}/|" >> ${TMPPLIST}

.if ${PORT_OPTIONS:MNLS}
	@cd ${OUTDIR} && ${COPYTREE_SHARE} datafiles/locale ${STAGEDIR}/${DATADIR}/
	@(cd ${OUTDIR}; ${FIND} datafiles/locale -type f -name blender.mo) | ${SORT} | ${SED} "s|^|${DATADIR_REL}/|" >> ${TMPPLIST}
	@(cd ${OUTDIR}; ${FIND} datafiles/locale -type f -name languages) | ${SORT} | ${SED} "s|^|${DATADIR_REL}/|" >> ${TMPPLIST}

	@cd ${OUTDIR} && ${COPYTREE_SHARE} datafiles/fonts ${STAGEDIR}/${DATADIR}/
	@(cd ${OUTDIR}; ${FIND} datafiles/fonts -type f) | ${SORT} | ${SED} "s|^|${DATADIR_REL}/|" >> ${TMPPLIST}
.endif

	@${MKDIR} ${STAGEDIR}/${DESKTOPDIR}
	@${INSTALL_DATA} ${WRKSRC}/release/freedesktop/blender.desktop \
		${STAGEDIR}/${DESKTOPDIR}/${PORTNAME}.desktop
	@-update-desktop-database -q
	@${ECHO} share/applications/${PORTNAME}.desktop >> ${TMPPLIST}

.if !defined(NO_INSTALL_MANPAGES)
	@${MV} ${INSTALL_WRKSRC}/bin/blender.1 ${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1
	${INSTALL_MAN} ${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1 \
		${STAGEDIR}${MAN1PREFIX}/man/man1
	@${ECHO} man/man1/blender-${VERS_TAG}.1.gz >> ${TMPPLIST}
.endif

.include <bsd.port.mk>
