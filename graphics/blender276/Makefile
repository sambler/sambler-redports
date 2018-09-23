# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	blender276
PORTVERSION=	2.76b
PORTREVISION=	4
CATEGORIES=	graphics multimedia
MASTER_SITES=	http://download.blender.org/source/ \
		http://mirror.cs.umn.edu/blender.org/source/
DISTFILES=	blender-${PORTVERSION}.tar.gz

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	3D modeling/rendering/animation/gaming package

LICENSE=	GPLv2

LIB_DEPENDS=	libsamplerate.so:audio/libsamplerate \
		libsndfile.so:audio/libsndfile \
		libboost_thread.so:devel/boost-libs \
		libOpenColorIO.so:graphics/opencolorio \
		libIlmImf.so:graphics/openexr \
		libHalf.so:graphics/ilmbase \
		libOpenImageIO16.so:graphics/openimageio16 \
		libopenjpeg.so:graphics/openjpeg15 \
		libpng.so:graphics/png \
		libtiff.so:graphics/tiff \
		libfftw3.so:math/fftw3 \
		libavutil.so:multimedia/ffmpeg \
		libfreetype.so:print/freetype2 \
		libyaml-cpp03.so:devel/yaml-cpp03 \
		libtinyxml.so:textproc/tinyxml \
		libpcre.so:devel/pcre
RUN_DEPENDS=	${PYNUMPY} \
		xdg-mime:devel/xdg-utils

USES=		cmake:outsource compiler:c++11-lib shebangfix
USES+=		python:3.4 desktop-file-utils openal:al,alut jpeg
USES+=		imake:noman
WRKSRC=		${WRKDIR}/blender-${PORTVERSION}
LICDIR=		${PREFIX}/share/licenses/${PKGNAME}
VERS_TAG=	276
PORTSCOUT=	ignore:1

USE_SDL=	sdl2
USE_XORG=	x11 xext xi xmu xxf86vm
USE_GL=		gl glu glew
USE_GNOME=	libxml2

LDFLAGS+=	-L${LOCALBASE}/lib -lexecinfo

CMAKE_ON=	WITH_BUILDINFO WITH_AUDASPACE WITH_BLENDER \
		WITH_BULLET WITH_CODEC_FFMPEG WITH_CODEC_SNDFILE \
		WITH_COMPOSITOR WITH_CPP11 WITH_CYCLES WITH_FFTW3 \
		WITH_FREESTYLE WITH_GAMEENGINE WITH_GUARDEDALLOC \
		WITH_IK_ITASC WITH_IK_SOLVER WITH_IMAGE_CINEON \
		WITH_IMAGE_DDS WITH_IMAGE_FRAMESERVER WITH_IMAGE_HDR \
		WITH_IMAGE_OPENEXR WITH_IMAGE_OPENJPEG WITH_IMAGE_REDCODE \
		WITH_IMAGE_TIFF WITH_LIBMV WITH_LZMA WITH_LZO \
		WITH_MOD_BOOLEAN WITH_MOD_FLUID WITH_MOD_OCEANSIM \
		WITH_MOD_REMESH WITH_MOD_SMOKE WITH_OPENAL \
		WITH_OPENCOLORIO WITH_PYTHON WITH_RAYOPTIMIZATION \
		WITH_SDL WITH_SYSTEM_GLEW WITH_SYSTEM_OPENJPEG \
		WITH_X11_XF86VMODE WITH_X11_XINPUT
CMAKE_OFF=	WITH_BOOST_ICU WITH_CYCLES_CUDA_BINARIES \
		CYCLES_OPENCL_DEBUG WITH_CYCLES_LOGGING \
		WITH_CYCLES_STANDALONE WITH_CYCLES_STANDALONE_GUI \
		WITH_DOC_MANPAGE WITH_INSTALL_PORTABLE \
		WITH_MEM_JEMALLOC WITH_GCC_MUDFLAP WITH_PYTHON_INSTALL \
		WITH_PYTHON_MODULE WITH_PYTHON_SAFETY \
		WITH_PYTHON_INSTALL_REQUESTS WITH_PYTHON_INSTALL_NUMPY \
		WITH_STATIC_LIBS WITH_SYSTEM_BULLET
CMAKE_ARGS+=	-DFFMPEG:STRING="${LOCALBASE}"

SUB_FILES=	blender blenderplayer
python_CMD=	${PYTHON_CMD}
SHEBANG_FILES=	release/bin/blender-thumbnailer.py \
		release/scripts/modules/bl_i18n_utils/merge_po.py \
		release/scripts/modules/bl_i18n_utils/utils_rtl.py \
		release/scripts/modules/blend_render_info.py \
		doc/manpage/blender.1.py

OPTIONS_DEFINE=	COLLADA HEADLESS JACK MANPAGES NLS OPENMP OSD OSL PLAYER SECURITY
OPTIONS_DEFAULT=	COLLADA JACK NLS OSL PLAYER SECURITY

OPTIONS_SUB=	yes
HEADLESS_DESC=	Disable user interface
JACK_DESC=	Audio support using JackAudio
NLS_DESC=	Include translations
OSD_DESC=	Opensubdiv support
OSL_DESC=	OSL shading support
PLAYER_DESC=	Build blender player
SECURITY_DESC=	Disable scripts auto-run

COLLADA_CMAKE_BOOL=	WITH_OPENCOLLADA
COLLADA_LIB_DEPENDS=	libOpenCOLLADABaseUtils.so:graphics/opencollada

HEADLESS_CMAKE_BOOL=	WITH_HEADLESS

JACK_CMAKE_BOOL=	WITH_JACK WITH_JACK_DYNLOAD
JACK_LIB_DEPENDS=	libjack.so:audio/jack

NLS_CMAKE_BOOL=		WITH_INTERNATIONAL
# Use iconv:wchar_t to force the usage of iconv from ports.
# libboost_locale.so uses libiconv_open, while we only provide
# iconv_open in 10.x+
NLS_USES=		gettext iconv:lib,wchar_t
NLS_LDFLAGS=		-L${LOCALBASE}/lib -lintl

OPENMP_CMAKE_BOOL=	WITH_OPENMP

OSD_CMAKE_BOOL=		WITH_OPENSUBDIV
OSD_LIB_DEPENDS=	libosdCPU.so:graphics/opensubdiv

OSL_CMAKE_BOOL=		WITH_CYCLES_OSL DWITH_LLVM 
OSL_CMAKE_ON=		-DLLVM_STATIC:BOOL=OFF \
			-DLLVM_VERSION:STRING="3.5" \
			-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config35"
OSL_BUILD_DEPENDS=	llvm-config35:devel/llvm35
OSL_LIB_DEPENDS=	liboslcomp16.so:graphics/openshadinglanguage16
OSL_RUN_DEPENDS=	llvm-config35:devel/llvm35

PLAYER_CMAKE_BOOL=	WITH_PLAYER

SECURITY_CMAKE_BOOL=	WITH_PYTHON_SECURITY

.include <bsd.port.options.mk>

post-patch:
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' \
		${WRKSRC}/release/bin/blender-thumbnailer.py
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' \
		${WRKSRC}/release/freedesktop/blender.desktop
	@${FIND} ${WRKSRC}/intern/cycles -name "*.cpp" -or -name "*.h" | \
		${XARGS} ${REINPLACE_CMD} -e 's|OpenImageIO/|OpenImageIO16/|g'
	@${REINPLACE_CMD} -e 's|OpenImageIO/|OpenImageIO16/|g' \
		${WRKSRC}/source/blender/imbuf/intern/oiio/openimageio_api.cpp
	@${FIND} ${WRKSRC}/intern/cycles -name "*.cpp" -or -name "*.h" | \
		${XARGS} ${REINPLACE_CMD} -e 's|<OSL/|<OSL16/|g'
	@${REINPLACE_CMD} -e 's|yaml-cpp|&03|' \
		${PATCH_WRKSRC}/build_files/cmake/Modules/FindOpenColorIO.cmake

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

	@${MKDIR} ${STAGEDIR}${DATADIR}
	@${MV} ${STAGEDIR}/${PREFIX}/share/blender/${PORTVERSION:C/[abcd]//g}/* ${STAGEDIR}${DATADIR}
	@${RM} -R ${STAGEDIR}/${PREFIX}/share/blender
	@${INSTALL_DATA} ${WRKSRC}/release/freedesktop/icons/scalable/apps/blender.svg \
		${STAGEDIR}/${PREFIX}/share/pixmaps/blender-${VERS_TAG}.svg
	@${MKDIR} ${STAGEDIR}/${DESKTOPDIR}
	@${MV} ${STAGEDIR}/${DESKTOPDIR}/blender.desktop \
		${STAGEDIR}/${DESKTOPDIR}/${PORTNAME}.desktop
	@${REINPLACE_CMD} -i '' -e 's|%%VERS_TAG%%|${VERS_TAG}|g' \
		${STAGEDIR}/${DESKTOPDIR}/${PORTNAME}.desktop
	@-update-desktop-database -q
	@${MKDIR} ${STAGEDIR}/${LICDIR}
	@${MV} ${STAGEDIR}/${PREFIX}/share/doc/blender/* ${STAGEDIR}/${LICDIR}
	@${RM} -R ${STAGEDIR}/${PREFIX}/share/doc/blender
	@cd ${STAGEDIR}/${PREFIX}/share/icons && ${FIND} . -name "*.png" -or -name "*.svg" | \
		${SED} -e "p;s|blender|blender-${VERS_TAG}|" | xargs -n2 ${MV}

.if ${PORT_OPTIONS:MMANPAGES}
	@(cd ${WRKSRC}/doc/manpage && \
		${PYTHON_CMD} blender.1.py \
			${INSTALL_WRKSRC}/bin/blender \
			${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1)
	${INSTALL_MAN} ${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1 \
		${STAGEDIR}${MAN1PREFIX}/man/man1
.endif

.include <bsd.port.mk>
