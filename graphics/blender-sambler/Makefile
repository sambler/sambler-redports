# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	blender-sambler
PORTVERSION=	2.79
PORTREVISION=	2
CATEGORIES=	graphics multimedia
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	3D modeling/rendering/animation/gaming package

LICENSE=	GPLv2

LIB_DEPENDS=	liblzo2.so:archivers/lzo2 \
		libsamplerate.so:audio/libsamplerate \
		libsndfile.so:audio/libsndfile \
		libboost_thread.so:devel/boost-libs \
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
RUN_DEPENDS=	${PYNUMPY} \
		xdg-mime:devel/xdg-utils

USES=		cmake:outsource shebangfix compiler:c++11-lib \
		python:3.6 desktop-file-utils openal:al,alut jpeg
OUTDIR=		${STAGEDIR}/${PREFIX}/${PORTVERSION}
LICDIR=		${PREFIX}/share/licenses/${PKGNAME}
VERS_TAG=	sambler
HASHTAG=	ba46c6f9aeed
PORTSCOUT=	ignore:1

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

SUB_FILES=	blender blenderplayer
python_CMD=	${PYTHON_CMD}
SHEBANG_FILES=	release/bin/blender-thumbnailer.py \
		release/scripts/modules/bl_i18n_utils/merge_po.py \
		release/scripts/modules/bl_i18n_utils/utils_rtl.py \
		release/scripts/modules/blend_render_info.py \
		doc/manpage/blender.1.py

USE_SDL=	sdl2
USE_XORG=	x11 xext xfixes xmu xi xxf86vm xrender
USE_GL=		gl glu glew
USE_GNOME=	libxml2

LDFLAGS+=	-L${LOCALBASE}/lib -lexecinfo

CMAKE_ON=	WITH_BUILDINFO WITH_AUDASPACE WITH_BLENDER WITH_BULLET \
		WITH_CODEC_FFMPEG WITH_CODEC_SNDFILE WITH_COMPOSITOR WITH_FREESTYLE \
		WITH_FFTW3 WITH_GAMEENGINE WITH_GUARDEDALLOC WITH_IK_ITASC \
		WITH_IK_SOLVER WITH_IMAGE_CINEON WITH_IMAGE_DDS \
		WITH_IMAGE_FRAMESERVER WITH_IMAGE_HDR WITH_IMAGE_OPENEXR \
		WITH_IMAGE_OPENJPEG WITH_IMAGE_REDCODE WITH_IMAGE_TIFF \
		WITH_LIBMV WITH_LZMA WITH_LZO WITH_MOD_BOOLEAN \
		WITH_MOD_FLUID WITH_MOD_OCEANSIM WITH_MOD_REMESH \
		WITH_MOD_SMOKE WITH_OPENAL WITH_OPENCOLORIO WITH_OPENIMAGEIO \
		WITH_PYTHON WITH_RAYOPTIMIZATION WITH_SDL WITH_SYSTEM_GLEW \
		WITH_SYSTEM_LZO WITH_SYSTEM_OPENJPEG WITH_X11_XF86VMODE \
		WITH_X11_XINPUT

CMAKE_OFF=	WITH_BOOST_ICU WITH_CYCLES_CUDA_BINARIES DCYCLES_OPENCL_DEBUG \
		WITH_CYCLES_STANDALONE WITH_CYCLES_STANDALONE_GUI \
		WITH_INSTALL_PORTABLE WITH_MEM_JEMALLOC WITH_GCC_MUDFLAP \
		WITH_PYTHON_INSTALL WITH_PYTHON_MODULE WITH_PYTHON_SAFETY \
		WITH_PYTHON_INSTALL_REQUESTS WITH_PYTHON_INSTALL_NUMPY \
		WITH_STATIC_LIBS WITH_SYSTEM_BULLET

CMAKE_ARGS+=	-DFFMPEG:STRING="${LOCALBASE}"
#-DPYTHON_VERSION:STRING=3.6

OPTIONS_DEFINE=	ALEMBIC ALEMBIC_HDF5 COLLADA CYCLES HEADLESS JACK \
		MANPAGES NLS OPENMP OSD OSL PLAYER SECURITY
## NDOF
OPTIONS_DEFAULT=	ALEMBIC ALEMBIC_HDF5 COLLADA CYCLES NLS OSL SECURITY
OPTIONS_SUB=		yes

ALEMBIC_DESC=		Enable Alembic file support
ALEMBIC_HDF5_DESC=	Enable Alembic hdf5 file support
COLLADA_DESC=		Include collada import
CYCLES_DESC=		Build cycles render engine
HEADLESS_DESC=		Disable user interface
JACK_DESC=		Audio support using JackAudio
#NDOF_DESC=		NDOF Support
NLS_DESC=		Include translations
OSD_DESC= 		Opensubdiv support
OSL_DESC=		OSL shading support
PLAYER_DESC=		Build blender player
SECURITY_DESC=		Disable scripts auto-run

ALEMBIC_CMAKE_BOOL=	WITH_ALEMBIC
ALEMBIC_LIB_DEPENDS=	libAlembic.so:graphics/alembic
# note that this needs to be set to match alembics hdf5 option
ALEMBIC_HDF5_REQUIRES=	ALEMBIC
ALEMBIC_HDF5_CMAKE_BOOL= WITH_ALEMBIC_HDF5
ALEMBIC_HDF5_LIB_DEPENDS=	libhdf5.so:science/hdf5

COLLADA_CMAKE_BOOL=	WITH_OPENCOLLADA
COLLADA_LIB_DEPENDS=	libOpenCOLLADABaseUtils.so:graphics/opencollada

CYCLES_CMAKE_BOOL=	WITH_CYCLES

HEADLESS_CMAKE_BOOL=	WITH_HEADLESS

JACK_CMAKE_BOOL=	WITH_JACK WITH_JACK_DYNLOAD
JACK_LIB_DEPENDS=	libjack.so:audio/jack

MANPAGES_CMAKE_BOOL=	WITH_DOC_MANPAGE

# TODO: add ndof lib to ports
NDOF_CMAKE_BOOL=	WITH_INPUT_NDOF

NLS_CMAKE_BOOL=		WITH_INTERNATIONAL
# Use iconv:wchar_t to force the usage of iconv from ports.
# libboost_locale.so uses libiconv_open, while we only provide
# iconv_open in 10.x+
NLS_USES=		gettext iconv:lib,wchar_t
NLS_LDFLAGS=		-L${LOCALBASE}/lib -lintl

OPENMP_CMAKE_BOOL=	WITH_OPENMP
OPENMP_CMAKE_ON=	-DOpenMP_C_FLAGS:STRING=-fopenmp -lm \
			-DOpenMP_CXX_FLAGS:STRING=-fopenmp -lm
OPENMP_LIB_DEPENDS=	libomp.so:devel/openmp
OPENMP_LDFLAGS=		-L${LOCALBASE}/lib

OSD_CMAKE_BOOL=		WITH_OPENSUBDIV WITH_CYCLES_OPENSUBDIV
OSD_LIB_DEPENDS=	libosdCPU.so:graphics/opensubdiv

OSL_IMPLIES=		CYCLES
OSL_CMAKE_BOOL=		WITH_CYCLES_OSL WITH_CXX11 WITH_LLVM
OSL_CMAKE_ON=		-DLLVM_STATIC:BOOL=OFF \
			-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config40"
OSL_BUILD_DEPENDS=	llvm-config40:devel/llvm40
OSL_LIB_DEPENDS=	liboslcomp.so:graphics/openshadinglanguage
OSL_RUN_DEPENDS=	llvm-config40:devel/llvm40

PLAYER_CMAKE_BOOL=	WITH_PLAYER

SECURITY_CMAKE_BOOL=	WITH_PYTHON_SECURITY

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MOPENMP} && ${ARCH} != amd64
BROKEN= devel/openmp only supports amd64
.endif

post-extract:
# translations
	@${MV} ${WRKSRC_trans}/* ${WRKSRC}/release/datafiles/locale/
# addons
	@${MV} ${WRKSRC_addons}/* ${WRKSRC}/release/scripts/addons/
# contrib
	@${MV} ${WRKSRC_contrib}/* ${WRKSRC}/release/scripts/addons_contrib/
# remove empty dir that we don't need
	@${RM} -r ${WRKSRC}/release/scripts/addons_contrib/coa_tools/coa_tools_updater

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

post-build-MANPAGES-on:
	@(cd ${WRKSRC}/doc/manpage && \
		${PYTHON_CMD} blender.1.py \
			${INSTALL_WRKSRC}/bin/blender \
			${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1)

post-install:
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blender
	${INSTALL_SCRIPT} ${WRKDIR}/blender ${STAGEDIR}/${PREFIX}/bin/blender-${VERS_TAG}
	@${MV} ${STAGEDIR}/${PREFIX}/bin/blender ${STAGEDIR}/${PREFIX}/bin/blender-bin-${VERS_TAG}
	@${MV} ${STAGEDIR}/${PREFIX}/bin/blender-thumbnailer.py \
		${STAGEDIR}/${PREFIX}/bin/blender-thumbnailer-${VERS_TAG}.py
	@${ECHO} bin/blender-${VERS_TAG} >> ${TMPPLIST}
	@${ECHO} bin/blender-bin-${VERS_TAG} >> ${TMPPLIST}
	@${ECHO} bin/blender-thumbnailer-${VERS_TAG}.py >> ${TMPPLIST}

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
	@(cd ${STAGEDIR}/${PREFIX}/share/icons && ${FIND} . -name "*.png" -or -name "*.svg" | \
		${SED} -e "p;s|blender|blender-${VERS_TAG}|" | ${XARGS} -n2 ${MV})
	@(cd ${STAGEDIR}/${PREFIX}; ${FIND} share/icons -type f) | ${SORT} >> ${TMPPLIST}
	@(cd ${STAGEDIR}/${PREFIX}; ${FIND} ${DATADIR_REL} -type f) | ${SORT} >> ${TMPPLIST}

post-install-PLAYER-on:
	@${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blenderplayer
	${INSTALL_SCRIPT} ${WRKDIR}/blenderplayer ${STAGEDIR}/${PREFIX}/bin/blenderplayer-${VERS_TAG}
	@${MV} ${STAGEDIR}/${PREFIX}/bin/blenderplayer \
		${STAGEDIR}/${PREFIX}/bin/blenderplayer-bin-${VERS_TAG}
	@${ECHO} bin/blenderplayer-${VERS_TAG} >> ${TMPPLIST}
	@${ECHO} bin/blenderplayer-bin-${VERS_TAG} >> ${TMPPLIST}

post-install-MANPAGES-on:
	${INSTALL_MAN} ${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1 \
		${STAGEDIR}${MAN1PREFIX}/man/man1

.include <bsd.port.mk>
