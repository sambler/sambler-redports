# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	blender-sambler
PORTVERSION=	2.73
PORTREVISION=	2
CATEGORIES=	graphics multimedia
MASTER_SITES=	https://github.com/sambler/myblender/tarball/:base \
		https://github.com/sambler/myblendertranslations/tarball/:trans \
		https://github.com/sambler/myblenderaddons/tarball/:addons \
		https://github.com/sambler/myblendercontrib/tarball/:contrib
DISTFILES=	sambler-${PORTVERSION}.${PORTREVISION}:base \
		translate-${PORTVERSION}.${PORTREVISION}:trans \
		addons-${PORTVERSION}.${PORTREVISION}:addons \
		contrib-${PORTVERSION}.${PORTREVISION}:contrib
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	3D modeling/rendering/animation/gaming package

LICENSE=	GPLv2

LIB_DEPENDS=	libsamplerate.so:${PORTSDIR}/audio/libsamplerate
LIB_DEPENDS+=	libsndfile.so:${PORTSDIR}/audio/libsndfile
LIB_DEPENDS+=	libboost_thread.so:${PORTSDIR}/devel/boost-libs
LIB_DEPENDS+=	libexecinfo.so:${PORTSDIR}/devel/libexecinfo
LIB_DEPENDS+=	libunwind.so:${PORTSDIR}/devel/libunwind
LIB_DEPENDS+=	libjpeg.so:${PORTSDIR}/graphics/jpeg
LIB_DEPENDS+=	libOpenColorIO.so:${PORTSDIR}/graphics/opencolorio
LIB_DEPENDS+=	libOpenImageIO14.so:${PORTSDIR}/graphics/openimageio14
LIB_DEPENDS+=	libIlmImf.so:${PORTSDIR}/graphics/OpenEXR
LIB_DEPENDS+=	libopenjpeg.so:${PORTSDIR}/graphics/openjpeg15
LIB_DEPENDS+=	libpng.so:${PORTSDIR}/graphics/png
LIB_DEPENDS+=	libtiff.so:${PORTSDIR}/graphics/tiff
LIB_DEPENDS+=	libfftw3.so:${PORTSDIR}/math/fftw3
LIB_DEPENDS+=	libavutil.so:${PORTSDIR}/multimedia/ffmpeg
LIB_DEPENDS+=	libfreetype.so:${PORTSDIR}/print/freetype2
RUN_DEPENDS=	xdg-mime:${PORTSDIR}/devel/xdg-utils

#USE_GITHUB=	yes
#GH_ACCOUNT=	sambler:base \
#		sambler:addons \
#		sambler:contrib \
#		sambler:trans
#GH_PROJECT=	myblender
#GH_PROJECT=	myblender:base \
#		myblenderaddons:addons \
#		myblendercontrib:contrib \
#		myblendertranslations:trans
#GH_TAGNAME=	sambler-${PORTVERSION}.${PORTREVISION}
#GH_TAGNAME=	sambler-${PORTVERSION}.${PORTREVISION}:base \
#		addons-${PORTVERSION}.${PORTREVISION}:addons \
#		contrib-${PORTVERSION}.${PORTREVISION}:contrib \
#		translate-${PORTVERSION}.${PORTREVISION}:trans
GH_COMMIT=	6865bec

FETCH_ARGS=	-pRr

USES=		cmake:outsource shebangfix compiler desktop-file-utils openal:al,alut
USES+=		python:3.4
WRKSRC=		${WRKDIR}/sambler-myblender-${GH_COMMIT}
#OUTDIR=		${INSTALL_WRKSRC}/bin/${PORTVERSION}
OUTDIR=		${STAGEDIR}/${PREFIX}/${PORTVERSION}
LICDIR=		${PREFIX}/share/licenses/${PKGNAME}
VERS_TAG=	sambler

SUB_FILES=	blender blenderplayer
python_CMD=	${PYTHON_CMD}
SHEBANG_FILES=	release/bin/blender-thumbnailer.py \
		release/scripts/modules/bl_i18n_utils/merge_po.py \
		release/scripts/modules/bl_i18n_utils/utils_rtl.py \
		release/scripts/modules/blend_render_info.py \
		doc/manpage/blender.1.py

USE_SDL=	sdl
USE_XORG=	x11 xext xmu
USE_GL=		glew

LDFLAGS+=	-L${LOCALBASE}/lib -lexecinfo

CMAKE_ARGS+=	-DWITH_BUILDINFO:BOOL=ON -DWITH_AUDASPACE:BOOL=ON
CMAKE_ARGS+=	-DWITH_BLENDER:BOOL=ON
CMAKE_ARGS+=	-DWITH_BOOST_ICU:BOOL=OFF -DWITH_BULLET:BOOL=ON
CMAKE_ARGS+=	-DWITH_CODEC_FFMPEG:BOOL=ON -DWITH_CODEC_SNDFILE:BOOL=ON
CMAKE_ARGS+=	-DFFMPEG:STRING="${LOCALBASE}" -DWITH_COMPOSITOR:BOOL=ON
CMAKE_ARGS+=	-DWITH_CYCLES:BOOL=ON -DWITH_CYCLES_CUDA_BINARIES:BOOL=OFF
CMAKE_ARGS+=	-DCYCLES_OPENCL_DEBUG:BOOL=OFF -DWITH_CYCLES_STANDALONE:BOOL=OFF
CMAKE_ARGS+=	-DWITH_CYCLES_STANDALONE_GUI:BOOL=OFF
CMAKE_ARGS+=	-DWITH_FFTW3:BOOL=ON -DWITH_FREESTYLE:BOOL=ON
CMAKE_ARGS+=	-DWITH_GAMEENGINE:BOOL=ON -DWITH_GUARDEDALLOC:BOOL=ON
CMAKE_ARGS+=	-DWITH_IK_ITASC:BOOL=ON
CMAKE_ARGS+=	-DWITH_IK_SOLVER:BOOL=ON -DWITH_IMAGE_CINEON:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_DDS:BOOL=ON -DWITH_IMAGE_FRAMESERVER:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_HDR:BOOL=ON -DWITH_IMAGE_OPENEXR:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_OPENJPEG:BOOL=ON -DWITH_IMAGE_REDCODE:BOOL=ON
CMAKE_ARGS+=	-DWITH_IMAGE_TIFF:BOOL=ON -DWITH_INSTALL_PORTABLE:BOOL=ON
CMAKE_ARGS+=	-DWITH_LIBMV:BOOL=ON -DWITH_LZMA:BOOL=ON -DWITH_LZO:BOOL=ON
CMAKE_ARGS+=	-DWITH_MEM_JEMALLOC:BOOL=OFF -DWITH_MOD_BOOLEAN:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_FLUID:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_OCEANSIM:BOOL=ON -DWITH_MOD_REMESH:BOOL=ON
CMAKE_ARGS+=	-DWITH_MOD_SMOKE:BOOL=ON -DWITH_GCC_MUDFLAP:BOOL=OFF
CMAKE_ARGS+=	-DWITH_OPENAL:BOOL=ON -DWITH_OPENCOLORIO:BOOL=ON
CMAKE_ARGS+=	-DWITH_OPENIMAGEIO:BOOL=ON
CMAKE_ARGS+=	-DWITH_PYTHON:BOOL=ON -DWITH_PYTHON_INSTALL:BOOL=OFF
CMAKE_ARGS+=	-DWITH_PYTHON_MODULE:BOOL=OFF -DWITH_PYTHON_SAFETY:BOOL=OFF
CMAKE_ARGS+=	-DWITH_PYTHON_INSTALL_REQUESTS:BOOL=OFF
CMAKE_ARGS+=	-DWITH_PYTHON_INSTALL_NUMPY:BOOL=OFF -DPYTHON_VERSION:STRING=3.4
CMAKE_ARGS+=	-DWITH_RAYOPTIMIZATION:BOOL=ON -DWITH_SDL:BOOL=ON
CMAKE_ARGS+=	-DWITH_STATIC_LIBS:BOOL=OFF -DWITH_SYSTEM_BULLET:BOOL=OFF
CMAKE_ARGS+=	-DWITH_SYSTEM_GLEW:BOOL=ON -DWITH_SYSTEM_OPENJPEG:BOOL=ON
CMAKE_ARGS+=	-DWITH_X11_XF86VMODE:BOOL=ON -DWITH_X11_XINPUT:BOOL=ON

OPTIONS_DEFINE=	COLLADA HEADLESS SECURITY PLAYER JACK NLS OSL OPENMP
## NDOF
OPTIONS_DEFAULT=	COLLADA PLAYER SECURITY NLS OSL

HEADLESS_DESC=	"Disable user interface"
SECURITY_DESC=	"Disable scripts auto-run"
PLAYER_DESC=	"Build blender player"
JACK_DESC=	"Audio support using JackAudio"
COLLADA_DESC=	"Include collada import"
#NDOF_DESC=	"NDOF Support"
NLS_DESC=	"Include translations"
OSL_DESC=	"OSL shading support"

COLLADA_CMAKE_ON=	-DWITH_OPENCOLLADA:BOOL=ON
COLLADA_CMAKE_OFF=	-DWITH_OPENCOLLADA:BOOL=OFF
COLLADA_LIB_DEPENDS=	libOpenCOLLADABaseUtils.so:${PORTSDIR}/graphics/opencollada

HEADLESS_CMAKE_ON=	-DWITH_HEADLESS:BOOL=ON
HEADLESS_CMAKE_OFF=	-DWITH_HEADLESS:BOOL=OFF

JACK_CMAKE_ON=		-DWITH_JACK:BOOL=ON \
			-DWITH_JACK_DYNLOAD:BOOL=ON
JACK_CMAKE_OFF=		-DWITH_JACK:BOOL=OFF
JACK_LIB_DEPENDS=	libjack.so:${PORTSDIR}/audio/jack

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

OSL_CMAKE_ON=		-DWITH_CYCLES_OSL:BOOL=ON \
			-DWITH_LLVM:BOOL=ON \
			-DLLVM_STATIC:BOOL=OFF \
			-DLLVM_VERSION:STRING="3.4" \
			-DLLVM_CONFIG:STRING="${LOCALBASE}/bin/llvm-config34"
OSL_CMAKE_OFF=		-DWITH_CYCLES_OSL:BOOL=OFF
OSL_LIB_DEPENDS=	liboslcomp.so:${PORTSDIR}/graphics/openshadinglanguage

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
	@${REINPLACE_CMD} -e 's|MY_WC_HASH "unknown"|MY_WC_HASH "${GH_COMMIT}"|g' \
		-e 's|MY_WC_BRANCH "unknown"|MY_WC_BRANCH "mymods"|g' \
		${WRKSRC}/build_files/cmake/buildinfo.cmake
	@${FIND} ${WRKSRC}/intern/cycles -name "*.cpp" -or -name "*.h" | \
		${XARGS} ${REINPLACE_CMD} -i '' -e 's|OpenImageIO/|OpenImageIO14/|g'
	@${REINPLACE_CMD} -i '' -e 's|OpenImageIO/|OpenImageIO14/|g' \
		${WRKSRC}/source/blender/imbuf/intern/oiio/openimageio_api.cpp

post-extract:
# tanslations
	@${MV} ${WRKDIR}/sambler-myblendertranslations-*/* ${WRKSRC}/release/datafiles/locale/
# addons
	@${MV} ${WRKDIR}/sambler-myblenderaddons-*/* ${WRKSRC}/release/scripts/addons/
# contrib
	@${MV} ${WRKDIR}/sambler-myblendercontrib-*/* ${WRKSRC}/release/scripts/addons_contrib/

# We ignore MAKE_ARGS, since those would set DESTDIR for make stage,
# which in turn would cause make install to install everything in a
# wrong location
#do-install:
#	@(cd ${INSTALL_WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE_CMD} \
#		${MAKE_FLAGS} ${MAKEFILE} ${INSTALL_TARGET})

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
#	@${INSTALL_DATA} ${INSTALL_WRKSRC}/bin/blender.svg \
#		${STAGEDIR}/${PREFIX}/share/pixmaps/blender-${VERS_TAG}.svg
	@${INSTALL_DATA} ${OUTDIR}/../blender.svg \
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
#	@${INSTALL_DATA} ${WRKSRC}/release/freedesktop/blender.desktop \
#		${STAGEDIR}/${DESKTOPDIR}/${PORTNAME}.desktop
	@${INSTALL_DATA} ${OUTDIR}/../blender.desktop \
		${STAGEDIR}/${DESKTOPDIR}/${PORTNAME}.desktop
	@-update-desktop-database -q
	@${ECHO} share/applications/${PORTNAME}.desktop >> ${TMPPLIST}

###
	@${MKDIR} ${STAGEDIR}/${LICDIR}
	@${MV} ${STAGEDIR}/${PREFIX}/copyright.txt ${STAGEDIR}/${LICDIR}
	@${ECHO} ${LICDIR}/copyright.txt >> ${TMPPLIST}
	@${MV} ${STAGEDIR}/${PREFIX}/LICENSE-bfont.ttf.txt ${STAGEDIR}/${LICDIR}
	@${ECHO} ${LICDIR}/LICENSE-bfont.ttf.txt >> ${TMPPLIST}
	@${MV} ${STAGEDIR}/${PREFIX}/LICENSE-bmonofont-i18n.ttf.txt ${STAGEDIR}/${LICDIR}
	@${ECHO} ${LICDIR}/LICENSE-bmonofont-i18n.ttf.txt >> ${TMPPLIST}
	@${MV} ${STAGEDIR}/${PREFIX}/LICENSE-droidsans.ttf.txt ${STAGEDIR}/${LICDIR}
	@${ECHO} ${LICDIR}/LICENSE-droidsans.ttf.txt >> ${TMPPLIST}
	@${MKDIR} ${STAGEDIR}/${DOCSDIR}
	@${MV} ${STAGEDIR}/${PREFIX}/readme.html ${STAGEDIR}/${DOCSDIR}
	@${ECHO} ${DOCSDIR}/readme.html >> ${TMPPLIST}
# cleanup
	@${RM} ${STAGEDIR}/${PREFIX}/blender
	@${RM} ${STAGEDIR}/${PREFIX}/blender.desktop
	@${RM} ${STAGEDIR}/${PREFIX}/blender.svg
	@${RM} ${STAGEDIR}/${PREFIX}/blender-thumbnailer.py
	@${RM} ${STAGEDIR}/${PREFIX}/GPL-license.txt
	@${RM} ${STAGEDIR}/${PREFIX}/Python-license.txt
	@${RM} -R ${STAGEDIR}/${PREFIX}/${PORTVERSION}
###

#.if !defined(NO_INSTALL_MANPAGES)
#	@cd ${INSTALL_WRKSRC}/bin/ && ${PYTHON_CMD} ${WRKSRC}/doc/manpage/blender.1.py ./blender ./blender-${VERS_TAG}.1
#	${INSTALL_MAN} ${INSTALL_WRKSRC}/bin/blender-${VERS_TAG}.1 \
#		${STAGEDIR}${MAN1PREFIX}/man/man1
#	@${ECHO} man/man1/blender-${VERS_TAG}.1.gz >> ${TMPPLIST}
#.endif

.include <bsd.port.mk>
