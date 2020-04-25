# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	blender279
DISTVERSION=	2.79b
PORTREVISION=	7
CATEGORIES=	graphics multimedia
MASTER_SITES=	http://download.blender.org/source/ \
		http://mirror.cs.umn.edu/blender.org/source/
DISTNAME=	blender-${DISTVERSION}

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
		libOpenImageIO18.so:graphics/openimageio18 \
		libIlmImf.so:graphics/openexr \
		libHalf.so:graphics/ilmbase \
		libopenjpeg.so:graphics/openjpeg15 \
		libopenvdb.so:misc/openvdb \
		libpng.so:graphics/png \
		libtbb.so:devel/tbb \
		libtiff.so:graphics/tiff \
		libfftw3.so:math/fftw3 \
		libavutil.so:multimedia/ffmpeg \
		libfreetype.so:print/freetype2 \
		libtinyxml.so:textproc/tinyxml
RUN_DEPENDS=	${PYNUMPY} \
		xdg-mime:devel/xdg-utils

USES=		cmake compiler:c++11-lib gl shebangfix \
		python:3.5 desktop-file-utils openal:al,alut jpeg
USES+=		imake:noman
LICDIR=		${PREFIX}/share/licenses/${PKGNAME}
VERS_TAG=	${DISTVERSION:C/[.abcd]//g}
LLVM_VER=	80
PORTSCOUT=	ignore:1

USE_SDL=	sdl2
USE_XORG=	x11 xext xfixes xmu xi xxf86vm xrender
USE_GL=		gl glu glew
USE_GNOME=	libxml2

# Use LLVM linker where available
.if exists(/usr/bin/ld.lld) && (${/usr/bin/ld:L:tA} != /usr/bin/ld.lld)
LDFLAGS+=	-fuse-ld=lld
.endif
LDFLAGS+=	-L${LOCALBASE}/lib -lexecinfo

CMAKE_ON=	WITH_BUILDINFO WITH_AUDASPACE WITH_BLENDER WITH_BULLET \
		WITH_CODEC_FFMPEG WITH_CODEC_SNDFILE WITH_COMPOSITOR \
		WITH_FFTW3 WITH_FREESTYLE WITH_GAMEENGINE WITH_GUARDEDALLOC \
		WITH_IK_ITASC WITH_IK_SOLVER WITH_IMAGE_CINEON WITH_IMAGE_DDS \
		WITH_IMAGE_FRAMESERVER WITH_IMAGE_HDR WITH_IMAGE_OPENEXR \
		WITH_IMAGE_OPENJPEG WITH_IMAGE_REDCODE WITH_IMAGE_TIFF \
		WITH_LIBMV WITH_LZMA WITH_LZO WITH_MOD_BOOLEAN WITH_MOD_FLUID \
		WITH_MOD_OCEANSIM WITH_MOD_REMESH WITH_MOD_SMOKE WITH_OPENAL \
		WITH_OPENCOLORIO WITH_PYTHON WITH_RAYOPTIMIZATION WITH_SDL \
		WITH_SYSTEM_GLEW WITH_OPENIMAGEIO WITH_SYSTEM_OPENJPEG \
		WITH_OPENVDB WITH_OPENVDB_BLOSC WITH_X11_XF86VMODE WITH_X11_XINPUT
CMAKE_OFF=	WITH_BOOST_ICU WITH_CYCLES_CUDA_BINARIES CYCLES_OPENCL_DEBUG \
		WITH_CYCLES_LOGGING WITH_CYCLES_STANDALONE \
		WITH_CYCLES_STANDALONE_GUI WITH_DOC_MANPAGE \
		WITH_INSTALL_PORTABLE WITH_MEM_JEMALLOC WITH_GCC_MUDFLAP \
		WITH_OPENVDB_3_ABI_COMPATIBLE WITH_PYTHON_INSTALL \
		WITH_PYTHON_MODULE WITH_PYTHON_SAFETY \
		WITH_PYTHON_INSTALL_REQUESTS WITH_PYTHON_INSTALL_NUMPY \
		WITH_STATIC_LIBS WITH_SYSTEM_BULLET
CMAKE_ARGS+=	-DFFMPEG:STRING="${LOCALBASE}"

SUB_FILES=	blender blenderplayer
SHEBANG_FILES=	release/bin/blender-thumbnailer.py \
		release/scripts/modules/bl_i18n_utils/merge_po.py \
		release/scripts/modules/bl_i18n_utils/utils_rtl.py \
		release/scripts/modules/blend_render_info.py \
		doc/manpage/blender.1.py

OPTIONS_DEFINE=		ALEMBIC ALEMBIC_HDF5 COLLADA CYCLES HEADLESS JACK \
			MANPAGES NLS OPENMP OSD PLAYER SECURITY
OPTIONS_DEFAULT=	ALEMBIC ALEMBIC_HDF5 COLLADA CYCLES JACK NLS \
			OPENMP OSD PLAYER SECURITY

OPTIONS_SUB=	yes
ALEMBIC_DESC=		Enable Alembic file support
ALEMBIC_HDF5_DESC=	Enable Alembic hdf5 file support
COLLADA_DESC=		Include collada import
CYCLES_DESC=		Build cycles render engine
HEADLESS_DESC=		Disable user interface
JACK_DESC=		Audio support using JackAudio
NLS_DESC=		Include translations
OSD_DESC=		Opensubdiv support
#OSL_DESC=		OSL shading support
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

NLS_CMAKE_BOOL=		WITH_INTERNATIONAL
# Use iconv:wchar_t to force the usage of iconv from ports.
# libboost_locale.so uses libiconv_open, while we only provide
# iconv_open in 10.x+
NLS_USES=		gettext iconv:lib,wchar_t
NLS_LDFLAGS=		-L${LOCALBASE}/lib -lintl

OPENMP_CMAKE_BOOL=	WITH_OPENMP
OPENMP_LIB_DEPENDS=	libomp.so:devel/openmp

OSD_CMAKE_BOOL=		WITH_OPENSUBDIV
OSD_LIB_DEPENDS=	libosdCPU.so:graphics/opensubdiv

# OSL needs to be built using the same version of oiio
#OSL_IMPLIES=		CYCLES
#OSL_CMAKE_BOOL=		WITH_CYCLES_OSL WITH_CXX11 WITH_LLVM
#OSL_CMAKE_ON=		-DLLVM_STATIC:BOOL=OFF \
#			-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config${LLVM_VER}"
#OSL_BUILD_DEPENDS=	llvm-config${LLVM_VER}:devel/llvm${LLVM_VER}
#OSL_LIB_DEPENDS=	liboslcomp.so:graphics/openshadinglanguage
#OSL_RUN_DEPENDS=	llvm-config${LLVM_VER}:devel/llvm${LLVM_VER}
PLIST_SUB+=		OSL="@comment "

PLAYER_CMAKE_BOOL=	WITH_PLAYER

SECURITY_CMAKE_BOOL=	WITH_PYTHON_SECURITY

post-patch:
	${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' \
		${WRKSRC}/release/bin/blender-thumbnailer.py
	${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' \
		${WRKSRC}/release/freedesktop/blender.desktop
	@${FIND} ${WRKSRC}/intern/cycles -name "*.cpp" -or -name "*.h" | \
		${XARGS} ${REINPLACE_CMD} -e 's|OpenImageIO/|OpenImageIO18/|g'
	@${REINPLACE_CMD} -e 's|pugixml.hpp|OpenImageIO18/pugixml.hpp|g' \
		${WRKSRC}/intern/cycles/util/util_xml.h
	@${REINPLACE_CMD} -e 's|OpenImageIO/|OpenImageIO18/|g' \
		${WRKSRC}/source/blender/imbuf/intern/oiio/openimageio_api.cpp
	${REINPLACE_CMD} -e 's|yaml-cpp|&03|' \
		${PATCH_WRKSRC}/build_files/cmake/Modules/FindOpenColorIO.cmake

post-install:
	${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blender
	${INSTALL_SCRIPT} ${WRKDIR}/blender ${STAGEDIR}/${PREFIX}/bin/blender-${VERS_TAG}
	${MV} ${STAGEDIR}/${PREFIX}/bin/blender ${STAGEDIR}/${PREFIX}/bin/blender-bin-${VERS_TAG}
	${MV} ${STAGEDIR}/${PREFIX}/bin/blender-thumbnailer.py \
		${STAGEDIR}/${PREFIX}/bin/blender-thumbnailer-${VERS_TAG}.py
	${MKDIR} ${STAGEDIR}${DATADIR}
	${MV} ${STAGEDIR}/${PREFIX}/share/blender/${DISTVERSION:C/[abcd]//g}/* ${STAGEDIR}${DATADIR}
	${RM} -R ${STAGEDIR}/${PREFIX}/share/blender
	${INSTALL_DATA} ${WRKSRC}/release/freedesktop/icons/scalable/apps/blender.svg \
		${STAGEDIR}/${PREFIX}/share/pixmaps/blender-${VERS_TAG}.svg
	${MKDIR} ${STAGEDIR}/${DESKTOPDIR}
	${MV} ${STAGEDIR}/${DESKTOPDIR}/blender.desktop \
		${STAGEDIR}/${DESKTOPDIR}/${PORTNAME}.desktop
	${REINPLACE_CMD} -i '' -e 's|%%VERS_TAG%%|${VERS_TAG}|g' \
		${STAGEDIR}/${DESKTOPDIR}/${PORTNAME}.desktop
	${MKDIR} ${STAGEDIR}/${LICDIR}
	${MV} ${STAGEDIR}/${PREFIX}/share/doc/blender/* ${STAGEDIR}/${LICDIR}
	${RM} -R ${STAGEDIR}/${PREFIX}/share/doc/blender
	cd ${STAGEDIR}/${PREFIX}/share/icons && ${FIND} . -name "*.png" -or -name "*.svg" | \
		${SED} -e "p;s|blender|blender-${VERS_TAG}|" | ${XARGS} -n2 ${MV}

post-install-PLAYER-on:
	${REINPLACE_CMD} -e 's|%%VERS_TAG%%|${VERS_TAG}|g' ${WRKDIR}/blenderplayer
	${INSTALL_SCRIPT} ${WRKDIR}/blenderplayer ${STAGEDIR}/${PREFIX}/bin/blenderplayer-${VERS_TAG}
	${MV} ${STAGEDIR}/${PREFIX}/bin/blenderplayer \
		${STAGEDIR}/${PREFIX}/bin/blenderplayer-bin-${VERS_TAG}

post-install-MANPAGES-on:
	@(cd ${WRKSRC}/doc/manpage && \
		${PYTHON_CMD} blender.1.py \
			${INSTALL_WRKSRC}/bin/blender \
			${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1)
	${INSTALL_MAN} ${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1 \
		${STAGEDIR}${MAN1PREFIX}/man/man1

.include <bsd.port.mk>
