# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	blender-sambler
PORTVERSION=	2.78
PORTREVISION=	6
CATEGORIES=	graphics multimedia
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	3D modeling/rendering/animation/gaming package

LICENSE=	GPLv2

LIB_DEPENDS=	liblzo2.so:archivers/lzo2 \
		libsamplerate.so:audio/libsamplerate \
		libsndfile.so:audio/libsndfile \
		libboost_thread.so:devel/boost-libs \
		libexecinfo.so:devel/libexecinfo \
		libunwind.so:devel/libunwind \
		libpcre.so:devel/pcre \
		libyaml-cpp03.so:devel/yaml-cpp03 \
		libOpenColorIO.so:graphics/opencolorio \
		libOpenImageIO.so:graphics/openimageio \
		libIlmImf.so:graphics/OpenEXR \
		libHalf.so:graphics/ilmbase \
		libopenjpeg.so:graphics/openjpeg15 \
		libpng.so:graphics/png \
		libtiff.so:graphics/tiff \
		libfftw3.so:math/fftw3 \
		libavutil.so:multimedia/ffmpeg \
		libfreetype.so:print/freetype2 \
		libtinyxml.so:textproc/tinyxml
RUN_DEPENDS=	xdg-mime:devel/xdg-utils

USE_GITHUB=	yes
GH_ACCOUNT=	sambler \
		sambler:addons \
		sambler:contrib \
		sambler:trans
GH_PROJECT=	myblender \
		myblenderaddons:addons \
		myblendercontrib:contrib \
		myblendertranslations:trans
GH_TAGNAME=	sambler-${PORTVERSION}.${PORTREVISION} \
		addons-${PORTVERSION}.${PORTREVISION}:addons \
		contrib-${PORTVERSION}.${PORTREVISION}:contrib \
		translate-${PORTVERSION}.${PORTREVISION}:trans

USES=		cmake:outsource shebangfix compiler:c++11-lib \
		python:3.5 desktop-file-utils openal:al,alut jpeg
OUTDIR=		${STAGEDIR}/${PREFIX}/${PORTVERSION}
LICDIR=		${PREFIX}/share/licenses/${PKGNAME}
VERS_TAG=	sambler
HASHTAG=	1736184
PORTSCOUT=	ignore:1

SUB_FILES=	blender blenderplayer
python_CMD=	${PYTHON_CMD}
SHEBANG_FILES=	release/bin/blender-thumbnailer.py \
		release/scripts/modules/bl_i18n_utils/merge_po.py \
		release/scripts/modules/bl_i18n_utils/utils_rtl.py \
		release/scripts/modules/blend_render_info.py \
		doc/manpage/blender.1.py

USE_SDL=	sdl2
USE_XORG=	x11 xext xmu xi xxf86vm xrender
USE_GL=		gl glu glew
USE_GNOME=	libxml2

LDFLAGS+=	-L${LOCALBASE}/lib -lexecinfo

CMAKE_ARGS+=	-DWITH_BUILDINFO:BOOL=ON -DWITH_AUDASPACE:BOOL=ON \
		-DWITH_BLENDER:BOOL=ON \
		-DWITH_BOOST_ICU:BOOL=OFF -DWITH_BULLET:BOOL=ON \
		-DWITH_CODEC_FFMPEG:BOOL=ON -DWITH_CODEC_SNDFILE:BOOL=ON \
		-DFFMPEG:STRING="${LOCALBASE}" -DWITH_COMPOSITOR:BOOL=ON \
		-DWITH_CYCLES_CUDA_BINARIES:BOOL=OFF \
		-DCYCLES_OPENCL_DEBUG:BOOL=OFF -DWITH_CYCLES_STANDALONE:BOOL=OFF \
		-DWITH_CYCLES_STANDALONE_GUI:BOOL=OFF -DWITH_DOC_MANPAGE:BOOL=OFF \
		-DWITH_FFTW3:BOOL=ON -DWITH_FREESTYLE:BOOL=ON \
		-DWITH_GAMEENGINE:BOOL=ON -DWITH_GUARDEDALLOC:BOOL=ON \
		-DWITH_IK_ITASC:BOOL=ON \
		-DWITH_IK_SOLVER:BOOL=ON -DWITH_IMAGE_CINEON:BOOL=ON \
		-DWITH_IMAGE_DDS:BOOL=ON -DWITH_IMAGE_FRAMESERVER:BOOL=ON \
		-DWITH_IMAGE_HDR:BOOL=ON -DWITH_IMAGE_OPENEXR:BOOL=ON \
		-DWITH_IMAGE_OPENJPEG:BOOL=ON -DWITH_IMAGE_REDCODE:BOOL=ON \
		-DWITH_IMAGE_TIFF:BOOL=ON -DWITH_INSTALL_PORTABLE:BOOL=OFF \
		-DWITH_LIBMV:BOOL=ON -DWITH_LZMA:BOOL=ON -DWITH_LZO:BOOL=ON \
		-DWITH_MEM_JEMALLOC:BOOL=OFF -DWITH_MOD_BOOLEAN:BOOL=ON \
		-DWITH_MOD_FLUID:BOOL=ON \
		-DWITH_MOD_OCEANSIM:BOOL=ON -DWITH_MOD_REMESH:BOOL=ON \
		-DWITH_MOD_SMOKE:BOOL=ON -DWITH_GCC_MUDFLAP:BOOL=OFF \
		-DWITH_OPENAL:BOOL=ON -DWITH_OPENCOLORIO:BOOL=ON \
		-DWITH_OPENIMAGEIO:BOOL=ON \
		-DWITH_PYTHON:BOOL=ON -DWITH_PYTHON_INSTALL:BOOL=OFF \
		-DWITH_PYTHON_MODULE:BOOL=OFF -DWITH_PYTHON_SAFETY:BOOL=OFF \
		-DWITH_PYTHON_INSTALL_REQUESTS:BOOL=OFF \
		-DWITH_PYTHON_INSTALL_NUMPY:BOOL=OFF -DPYTHON_VERSION:STRING=3.5 \
		-DWITH_RAYOPTIMIZATION:BOOL=ON -DWITH_SDL:BOOL=ON \
		-DWITH_STATIC_LIBS:BOOL=OFF -DWITH_SYSTEM_BULLET:BOOL=OFF \
		-DWITH_SYSTEM_GLEW:BOOL=ON -DWITH_SYSTEM_LZO:BOOL=ON \
		-DWITH_SYSTEM_OPENJPEG:BOOL=ON \
		-DWITH_X11_XF86VMODE:BOOL=ON -DWITH_X11_XINPUT:BOOL=ON

OPTIONS_DEFINE=	COLLADA CYCLES HEADLESS JACK MANPAGES NLS OPENMP OSD OSL PLAYER SECURITY
## NDOF
OPTIONS_DEFAULT=	COLLADA CYCLES NLS OSL SECURITY
OPTIONS_SUB=		yes

COLLADA_DESC=	Include collada import
CYCLES_DESC=	Build cycles render engine
HEADLESS_DESC=	Disable user interface
JACK_DESC=	Audio support using JackAudio
#NDOF_DESC=	NDOF Support
NLS_DESC=	Include translations
OSD_DESC= 	Opensubdiv support
OSL_DESC=	OSL shading support
PLAYER_DESC=	Build blender player
SECURITY_DESC=	Disable scripts auto-run

COLLADA_CMAKE_ON=	-DWITH_OPENCOLLADA:BOOL=ON
COLLADA_CMAKE_OFF=	-DWITH_OPENCOLLADA:BOOL=OFF
COLLADA_LIB_DEPENDS=	libOpenCOLLADABaseUtils.so:graphics/opencollada

CYCLES_CMAKE_ON=	-DWITH_CYCLES:BOOL=ON
CYCLES_CMAKE_OFF=	-DWITH_CYCLES:BOOL=OFF

HEADLESS_CMAKE_ON=	-DWITH_HEADLESS:BOOL=ON
HEADLESS_CMAKE_OFF=	-DWITH_HEADLESS:BOOL=OFF

JACK_CMAKE_ON=		-DWITH_JACK:BOOL=ON \
			-DWITH_JACK_DYNLOAD:BOOL=ON
JACK_CMAKE_OFF=		-DWITH_JACK:BOOL=OFF
JACK_LIB_DEPENDS=	libjack.so:audio/jack

# TODO: add ndof lib to ports
NDOF_CMAKE_ON=		-DWITH_INPUT_NDOF:BOOL=ON
NDOF_CMAKE_OFF=		-DWITH_INPUT_NDOF:BOOL=OFF

NLS_CMAKE_ON=		-DWITH_INTERNATIONAL:BOOL=ON
NLS_CMAKE_OFF=		-DWITH_INTERNATIONAL:BOOL=OFF
# Use iconv:wchar_t to force the usage of iconv from ports.
# libboost_locale.so uses libiconv_open, while we only provide
# iconv_open in 10.x+
NLS_USES=		gettext iconv:lib,wchar_t
NLS_LDFLAGS=		-L${LOCALBASE}/lib -lintl

OPENMP_CMAKE_ON=	-DWITH_OPENMP:BOOL=ON
OPENMP_CMAKE_OFF=	-DWITH_OPENMP:BOOL=OFF
OPENMP_USES=		compiler:openmp

OSD_CMAKE_ON=		-DWITH_OPENSUBDIV:BOOL=ON -DWITH_CYCLES_OPENSUBDIV:BOOL=ON
OSD_CMAKE_OFF=		-DWITH_OPENSUBDIV:BOOL=OFF -DWITH_CYCLES_OPENSUBDIV:BOOL=OFF
OSD_LIB_DEPENDS=	libosdCPU.so:graphics/opensubdiv

OSL_IMPLIES=		CYCLES
OSL_CMAKE_ON=		-DWITH_CYCLES_OSL:BOOL=ON \
			-DWITH_CXX11:BOOL=ON \
			-DWITH_LLVM:BOOL=ON \
			-DLLVM_STATIC:BOOL=OFF \
			-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config40"
OSL_CMAKE_OFF=		-DWITH_CYCLES_OSL:BOOL=OFF
OSL_LIB_DEPENDS=	liboslcomp.so:graphics/openshadinglanguage
OSL_BUILD_DEPENDS=	llvm-config40:devel/llvm40
OSL_RUN_DEPENDS=	llvm-config40:devel/llvm40

PLAYER_CMAKE_ON=	-DWITH_PLAYER:BOOL=ON
PLAYER_CMAKE_OFF=	-DWITH_PLAYER:BOOL=OFF

SECURITY_CMAKE_ON=	-DWITH_PYTHON_SECURITY:BOOL=ON
SECURITY_CMAKE_OFF=	-DWITH_PYTHON_SECURITY:BOOL=OFF

.include <bsd.port.options.mk>

post-extract:
# tanslations
	@${MV} ${WRKSRC_trans}/* ${WRKSRC}/release/datafiles/locale/
# addons
	@${MV} ${WRKSRC_addons}/* ${WRKSRC}/release/scripts/addons/
# contrib
	@${MV} ${WRKSRC_contrib}/* ${WRKSRC}/release/scripts/addons_contrib/

post-patch:
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' \
		${WRKSRC}/release/bin/blender-thumbnailer.py
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' \
		${WRKSRC}/release/freedesktop/blender.desktop
	@${REINPLACE_CMD} -e 's|MY_WC_HASH "unknown"|MY_WC_HASH "${HASHTAG}"|g' \
		-e 's|MY_WC_BRANCH "unknown"|MY_WC_BRANCH "mymods"|g' \
		${WRKSRC}/build_files/cmake/buildinfo.cmake
	@${REINPLACE_CMD} -e 's|yaml-cpp|&03|' \
		${PATCH_WRKSRC}/build_files/cmake/Modules/FindOpenColorIO.cmake

post-build:
.if ${PORT_OPTIONS:MMANPAGES}
	@(cd ${WRKSRC}/doc/manpage && \
		${PYTHON_CMD} blender.1.py \
			${INSTALL_WRKSRC}/bin/blender \
			${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1)
.endif

post-install:
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blender
	${INSTALL_SCRIPT} ${WRKDIR}/blender ${STAGEDIR}/${PREFIX}/bin/blender-${VERS_TAG}
	@${MV} ${STAGEDIR}/${PREFIX}/bin/blender ${STAGEDIR}/${PREFIX}/bin/blender-bin-${VERS_TAG}
	@${MV} ${STAGEDIR}/${PREFIX}/bin/blender-thumbnailer.py \
		${STAGEDIR}/${PREFIX}/bin/blender-thumbnailer-${VERS_TAG}.py
	@${ECHO} bin/blender-${VERS_TAG} >> ${TMPPLIST}
	@${ECHO} bin/blender-bin-${VERS_TAG} >> ${TMPPLIST}
	@${ECHO} bin/blender-thumbnailer-${VERS_TAG}.py >> ${TMPPLIST}

.if ${PORT_OPTIONS:MPLAYER}
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blenderplayer
	${INSTALL_SCRIPT} ${WRKDIR}/blenderplayer ${STAGEDIR}/${PREFIX}/bin/blenderplayer-${VERS_TAG}
	@${MV} ${STAGEDIR}/${PREFIX}/bin/blenderplayer \
		${STAGEDIR}/${PREFIX}/bin/blenderplayer-bin-${VERS_TAG}
	@${ECHO} bin/blenderplayer-${VERS_TAG} >> ${TMPPLIST}
	@${ECHO} bin/blenderplayer-bin-${VERS_TAG} >> ${TMPPLIST}
.endif

	@${MKDIR} ${STAGEDIR}${DATADIR}
	@${MV} ${STAGEDIR}/${PREFIX}/share/blender/${PORTVERSION}/* ${STAGEDIR}${DATADIR}
	@${RM} -R ${STAGEDIR}/${PREFIX}/share/blender
	${INSTALL_DATA} ${WRKSRC}/release/freedesktop/icons/scalable/apps/blender.svg \
		${STAGEDIR}/${PREFIX}/share/pixmaps/blender-${VERS_TAG}.svg
	@${ECHO} share/pixmaps/blender-${VERS_TAG}.svg >> ${TMPPLIST}
	@${MKDIR} ${STAGEDIR}/${DESKTOPDIR}
	@${MV} ${STAGEDIR}/${DESKTOPDIR}/blender.desktop \
		${STAGEDIR}/${DESKTOPDIR}/${PORTNAME}.desktop
	@${REINPLACE_CMD} -i '' -e 's|%%VERS_TAG%%|${VERS_TAG}|g' \
		${STAGEDIR}/${DESKTOPDIR}/${PORTNAME}.desktop
	@${ECHO} share/applications/${PORTNAME}.desktop >> ${TMPPLIST}
	@-update-desktop-database -q
	@${MKDIR} ${STAGEDIR}/${LICDIR}
	@${MV} ${STAGEDIR}/${PREFIX}/share/doc/blender/* ${STAGEDIR}/${LICDIR}
	@${RM} -R ${STAGEDIR}/${PREFIX}/share/doc/blender
	@cd ${STAGEDIR}/${PREFIX}/share/icons && ${FIND} . -name "*.png" -or -name "*.svg" | \
		${SED} -e "p;s|blender|blender-${VERS_TAG}|" | ${XARGS} -n2 ${MV}
	@(cd ${STAGEDIR}/${PREFIX}; ${FIND} share/icons -type f) | ${SORT} >> ${TMPPLIST}
	@(cd ${STAGEDIR}/${PREFIX}; ${FIND} ${DATADIR_REL} -type f) | ${SORT} >> ${TMPPLIST}

.if ${PORT_OPTIONS:MMANPAGES}
	${INSTALL_MAN} ${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1 \
		${STAGEDIR}${MAN1PREFIX}/man/man1
.endif

.include <bsd.port.mk>
