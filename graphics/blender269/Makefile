# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	blender269
PORTVERSION=	2.69
PORTREVISION=	7
CATEGORIES=	graphics multimedia
MASTER_SITES=	http://download.blender.org/source/ \
		http://mirror.cs.umn.edu/blender.org/source/
DISTFILES=	blender-${PORTVERSION}.tar.gz

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	3D modeling/rendering/animation/gaming package

LICENSE=	GPLv2

LIB_DEPENDS=	libsamplerate.so:audio/libsamplerate
LIB_DEPENDS+=	libsndfile.so:audio/libsndfile
LIB_DEPENDS+=	libboost_thread.so:devel/boost-libs
LIB_DEPENDS+=	libexecinfo.so:devel/libexecinfo
LIB_DEPENDS+=	libOpenColorIO.so:graphics/opencolorio
LIB_DEPENDS+=	libIlmImf.so:graphics/OpenEXR
LIB_DEPENDS+=	libOpenImageIO14.so:graphics/openimageio14
LIB_DEPENDS+=	libopenjpeg.so:graphics/openjpeg15
LIB_DEPENDS+=	libpng.so:graphics/png
LIB_DEPENDS+=	libtiff.so:graphics/tiff
LIB_DEPENDS+=	libfftw3.so:math/fftw3
LIB_DEPENDS+=	libavutil1.so:multimedia/ffmpeg1
LIB_DEPENDS+=	libfreetype.so:print/freetype2
RUN_DEPENDS=	xdg-mime:devel/xdg-utils

USES=		cmake:outsource compiler:c++11-lib shebangfix
USES+=		python:3.3 desktop-file-utils openal:al,alut jpeg
WRKSRC=		${WRKDIR}/blender-${PORTVERSION}
LICDIR=		${PREFIX}/share/licenses/${PKGNAME}
VERS_TAG=	269
PORTSCOUT=	ignore:1

USE_SDL=	sdl
USE_XORG=	x11 xext xmu
USE_GL=		glew

LDFLAGS+=	-L${LOCALBASE}/lib -lexecinfo
# adjust for ffmpeg1
CFLAGS+=	-I${LOCALBASE}/include/ffmpeg1
CXXFLAGS+=	-I${LOCALBASE}/include/ffmpeg1
LDFLAGS+=	-L${LOCALBASE}/lib/ffmpeg1
CMAKE_ARGS+=	-DFFMPEG_LIBRARIES:STRING="avformat1;avcodec1;avutil1;avdevice1;swscale1"

CMAKE_ARGS+=	-DWITH_BUILDINFO:BOOL=ON -DWITH_AUDASPACE:BOOL=ON
CMAKE_ARGS+=	-DWITH_BLENDER:BOOL=ON -DWITH_BOOL_COMPAT:BOOL=ON
CMAKE_ARGS+=	-DWITH_BOOST_ICU:BOOL=OFF -DWITH_BULLET:BOOL=ON
CMAKE_ARGS+=	-DWITH_CODEC_FFMPEG:BOOL=ON -DWITH_CODEC_SNDFILE:BOOL=ON
CMAKE_ARGS+=	-DFFMPEG:STRING="${LOCALBASE}" -DWITH_COMPOSITOR:BOOL=ON
CMAKE_ARGS+=	-DWITH_CYCLES:BOOL=ON -DWITH_CYCLES_CUDA_BINARIES:BOOL=OFF
CMAKE_ARGS+=	-DCYCLES_OPENCL_DEBUG:BOOL=OFF -DWITH_CYCLES_STANDALONE:BOOL=OFF
CMAKE_ARGS+=	-DWITH_CYCLES_OSL:BOOL=OFF
CMAKE_ARGS+=	-DWITH_CYCLES_STANDALONE_GUI:BOOL=OFF
CMAKE_ARGS+=	-DWITH_FFTW3:BOOL=ON -DWITH_FREESTYLE:BOOL=ON
CMAKE_ARGS+=	-DWITH_GAMEENGINE:BOOL=ON -DWITH_GUARDEDALLOC:BOOL=ON
CMAKE_ARGS+=	-DWITH_IK_ITASC:BOOL=ON
CMAKE_ARGS+=	-DWITH_IK_SOLVER:BOOL=ON -DWITH_IMAGE_CINEON:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_DDS:BOOL=ON -DWITH_IMAGE_FRAMESERVER:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_HDR:BOOL=ON -DWITH_IMAGE_OPENEXR:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_OPENJPEG:BOOL=ON -DWITH_IMAGE_REDCODE:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_TIFF:BOOL=ON -DWITH_INSTALL_PORTABLE:BOOL=OFF
CMAKE_ARGS+=	-DWITH_LIBMV:BOOL=ON -DWITH_LZMA:BOOL=ON -DWITH_LZO:BOOL=ON
CMAKE_ARGS+=	-DWITH_MEM_JEMALLOC:BOOL=OFF -DWITH_MOD_BOOLEAN:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_FLUID:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_OCEANSIM:BOOL=ON -DWITH_MOD_REMESH:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_SMOKE:BOOL=ON -DWITH_GCC_MUDFLAP:BOOL=OFF
CMAKE_ARGS+=	-DWITH_OPENAL:BOOL=ON -DWITH_OPENCOLORIO:BOOL=ON
CMAKE_ARGS+=	-DWITH_PYTHON:BOOL=ON -DWITH_PYTHON_INSTALL:BOOL=OFF
CMAKE_ARGS+=	-DWITH_PYTHON_MODULE:BOOL=OFF -DWITH_PYTHON_SAFETY:BOOL=OFF
CMAKE_ARGS+=	-DWITH_PYTHON_INSTALL_NUMPY:BOOL=OFF
CMAKE_ARGS+=	-DWITH_RAYOPTIMIZATION:BOOL=ON -DWITH_SDL:BOOL=ON
CMAKE_ARGS+=	-DWITH_STATIC_LIBS:BOOL=OFF -DWITH_SYSTEM_BULLET:BOOL=OFF
CMAKE_ARGS+=	-DWITH_SYSTEM_GLEW:BOOL=ON -DWITH_SYSTEM_OPENJPEG:BOOL=ON
CMAKE_ARGS+=	-DWITH_X11_XF86VMODE:BOOL=ON -DWITH_X11_XINPUT:BOOL=ON

SUB_FILES=	blender blenderplayer
python_CMD=	${PYTHON_CMD}
SHEBANG_FILES=	release/bin/blender-thumbnailer.py \
		release/scripts/modules/bl_i18n_utils/merge_po.py \
		release/scripts/modules/bl_i18n_utils/utils_rtl.py \
		release/scripts/modules/blend_render_info.py \
		doc/manpage/blender.1.py

OPTIONS_DEFINE=	COLLADA HEADLESS MANPAGES SECURITY PLAYER JACK NLS OPENMP
OPTIONS_DEFAULT=	COLLADA SECURITY PLAYER NLS JACK

OPTIONS_SUB=	yes
HEADLESS_DESC=	Disable user interface
SECURITY_DESC=	Disable scripts auto-run
PLAYER_DESC=	Build blender player
JACK_DESC=	Audio support using JackAudio
NLS_DESC=	Include translations
#OSL_DESC=	OSL shading support

COLLADA_CMAKE_ON=	-DWITH_OPENCOLLADA:BOOL=ON
COLLADA_CMAKE_OFF=	-DWITH_OPENCOLLADA:BOOL=OFF
COLLADA_LIB_DEPENDS=	libOpenCOLLADABaseUtils.so:graphics/opencollada

HEADLESS_CMAKE_ON=	-DWITH_HEADLESS:BOOL=ON
HEADLESS_CMAKE_OFF=	-DWITH_HEADLESS:BOOL=OFF

JACK_CMAKE_ON=		-DWITH_JACK:BOOL=ON \
			-DWITH_JACK_DYNLOAD:BOOL=ON
JACK_CMAKE_OFF=		-DWITH_JACK:BOOL=OFF
JACK_LIB_DEPENDS=	libjack.so:audio/jack

NLS_CMAKE_ON=		-DWITH_INTERNATIONAL:BOOL=ON
NLS_CMAKE_OFF=		-DWITH_INTERNATIONAL:BOOL=OFF
NLS_USES=		gettext iconv
NLS_LDFLAGS=		-L${LOCALBASE}/lib -lintl

OPENMP_CMAKE_ON=	-DWITH_OPENMP:BOOL=ON
OPENMP_CMAKE_OFF=	-DWITH_OPENMP:BOOL=OFF

#OSL_CMAKE_ON=		-DWITH_CYCLES_OSL:BOOL=ON \
#			-DWITH_LLVM:BOOL=ON \
#			-DLLVM_STATIC:BOOL=ON \
#			-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config33" \
#			-DOSL_COMPILER:STRING="${LOCALBASE}/bin/oslc14" \
#			-DOSL_INCLUDES:STRING="${LOCALBASE}/include" \
#			-DOSL_LIB_COMP:STRING="${LOCALBASE}/lib/liboslcomp14.so" \
#			-DOSL_LIB_EXEC:STRING="${LOCALBASE}/lib/liboslexec14.so" \
#			-DOSL_LIB_QUERY:STRING="${LOCALBASE}/lib/liboslquery14.so"
#OSL_CMAKE_OFF=		-DWITH_CYCLES_OSL:BOOL=OFF
#OSL_LIB_DEPENDS=	liboslcomp14.so:graphics/openshadinglanguage14

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

post-install:
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blender
	@${INSTALL_SCRIPT} ${WRKDIR}/blender ${STAGEDIR}/${PREFIX}/bin/blender-${VERS_TAG}
	@${MV} ${STAGEDIR}/${PREFIX}/bin/blender ${STAGEDIR}/${PREFIX}/bin/blender-bin-${VERS_TAG}
	@${MV} ${STAGEDIR}/${PREFIX}/bin/blender-thumbnailer.py \
		${STAGEDIR}/${PREFIX}/bin/blender-thumbnailer-${VERS_TAG}.py

.if ${PORT_OPTIONS:MPLAYER}
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blenderplayer
	@${INSTALL_SCRIPT} ${WRKDIR}/blenderplayer ${STAGEDIR}/${PREFIX}/bin/blenderplayer-${VERS_TAG}
	@${MV} ${STAGEDIR}/${PREFIX}/bin/blenderplayer \
		${STAGEDIR}/${PREFIX}/bin/blenderplayer-bin-${VERS_TAG}
.endif

	${MKDIR} ${STAGEDIR}${DATADIR}
	@${MV} ${STAGEDIR}/${PREFIX}/share/blender/${PORTVERSION:C/[abcd]//g}/* ${STAGEDIR}${DATADIR}
	@${RM} -R ${STAGEDIR}/${PREFIX}/share/blender
	@${INSTALL_DATA} ${WRKSRC}/release/freedesktop/icons/scalable/apps/blender.svg \
		${STAGEDIR}/${PREFIX}/share/pixmaps/blender-${VERS_TAG}.svg
	@${MV} ${STAGEDIR}/${DESKTOPDIR}/blender.desktop \
		${STAGEDIR}/${DESKTOPDIR}/${PORTNAME}.desktop

	@-update-desktop-database -q
	@${MKDIR} ${STAGEDIR}/${LICDIR}
	@${MV} ${STAGEDIR}/${PREFIX}/share/doc/blender/* ${STAGEDIR}/${LICDIR}
	@${RM} -R ${STAGEDIR}/${PREFIX}/share/doc/blender
	@cd ${STAGEDIR}/${PREFIX}/share/icons && ${FIND} . -name "*.png" -or -name "*.svg" | \
		${SED} -e "p;s|blender|blender-${VERS_TAG}|" | xargs -n2 ${MV}

.if ${PORT_OPTIONS:MMANPAGES}
	@${MV} ${INSTALL_WRKSRC}/bin/blender.1 ${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1
	${INSTALL_MAN} ${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1 \
		${STAGEDIR}${MAN1PREFIX}/man/man1
.endif

.include <bsd.port.mk>
