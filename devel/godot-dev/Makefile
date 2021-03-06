# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	godot
PORTVERSION=	3.2
PORTREVISION=	0
CATEGORIES=	devel games
PKGNAMESUFFIX=	-devel

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT?=	Game runtime engine

LICENSE=		MIT CC-BY-3.0
LICENSE_COMB=		multi
LICENSE_FILE_CC-BY-3.0=	${WRKSRC}/LOGO_LICENSE.md
LICENSE_FILE_MIT=	${WRKSRC}/LICENSE.txt

LIB_DEPENDS=	libfreetype.so:print/freetype2 \
		libpng.so:graphics/png
RUN_DEPENDS=	xdg-user-dir:devel/xdg-user-dirs \
		xdg-open:devel/xdg-utils \
		xmessage:x11/xmessage

USE_GITHUB=	yes
GH_ACCOUNT=	godotengine
#GH_PROJECT=	godot
# rc4 27/1
GH_TAGNAME=	9daaa12bae0c
GH_TUPLE=	mono:nuget-binary:ebedbf8:NUGT/nuget-binary

USES=		compiler:c++11-lib gl pkgconfig scons
USE_XORG=	x11 xcursor xi xinerama xrandr xrender
USE_GL=		gl glew glu

MAKE_ARGS+=		platform=x11 builtin_freetype=no builtin_libpng=no
MAKE_ARGS+=		builtin_openssl=no
#MAKE_ARGS+=		warnings=extra werror=yes verbose=yes
MAKE_ARGS+=		warnings=no werror=no verbose=no
MAKE_ARGS+=		${MAKE_ARGS_${CHOSEN_COMPILER_TYPE}}
MAKE_ARGS_clang=	use_llvm=True
CXXFLAGS+=		-DRTAUDIO_ENABLED
CXXFLAGS_i386=		${CXXFLAGS_i386_${CHOSEN_COMPILER_TYPE}}
CXXFLAGS_i386_gcc=	-march=i586
CXXFLAGS_aarch64=	-DNO_THREADS
CXXFLAGS_sparc64=	-DNO_THREADS
CXXFLAGS_mips=		-DNO_THREADS
CXXFLAGS_mips64=	-DNO_THREADS

OPTIONS_DEFINE=		EXAMPLES MONO TOOLS
OPTIONS_DEFAULT=	ALSA MONO
# Moved to devel/godot-tools -- remove for -devel
#OPTIONS_EXCLUDE?=	EXAMPLES TOOLS
OPTIONS_GROUP=		AUDIO
OPTIONS_GROUP_AUDIO=	ALSA PULSEAUDIO

AUDIO_DESC=		Audio support
ALSA_LIB_DEPENDS=	libasound.so:audio/alsa-lib
ALSA_MAKE_ARGS=		alsa=True
ALSA_MAKE_ARGS_OFF=		alsa=False
EXAMPLES_GH_PROJECT=	godot-demo-projects:DEMOS
# master for dev demos
EXAMPLES_GH_TAGNAME=	97f9632be43a:DEMOS # 29/1
EXAMPLES_PORTEXAMPLES=	*

MONO_DESC=		Mono (C#) Support xx(not stable)
MONO_USES=		mono:nuget
#MONO_BUILD_DEPENDS=	xbuild:lang/mono
#MONO_CXXFLAGS=         -I${LOCALBASE}/include/glib-2.0 -I${LOCALBASE}/include/glib-1.2
MONO_MAKE_ARGS=		module_mono_enabled=yes xbuild_fallback=yes mono_glue=True NUGET_PATH=${WRKSRC_NUGT}/nuget.exe
MONO_MAKE_ARGS_OFF=	module_mono_enabled=no
MONO_USES=		mono:nuget
NUGET_DEPENDS=		DotNet.Glob=2.1.1

PULSEAUDIO_LIB_DEPENDS=	libpulse-simple.so:audio/pulseaudio
PULSEAUDIO_MAKE_ARGS=	pulseaudio=True
PULSEAUDIO_MAKE_ARGS_OFF=	pulseaudio=False
TOOLS_DESC=		Include development tools (IDE)
#TOOLS_MAKE_ARGS=	target=release_debug tools=True
TOOLS_MAKE_ARGS=	target=debug tools=True
TOOLS_MAKE_ARGS_OFF=	target=release tools=False
TOOLS_DESKTOP_ENTRIES=	"Godot-devel" "${COMMENT}" "${GODOTFILE}" \
			"${GODOTFILE}" "Development;IDE;" ""
TOOLS_PLIST_FILES=	share/pixmaps/${GODOTFILE}.png \
			share/pixmaps/${GODOTFILE}.svg

GODOTFILE=		${PORTNAME}${PKGNAMESUFFIX}
PLIST_FILES=		bin/${GODOTFILE}

.ifmake makesum
# Always include optional distfiles
.MAKEFLAGS:	WITH="${OPTIONS_DEFINE}" OPTIONS_EXCLUDE=
.endif

.include <bsd.port.pre.mk>

.if ${ARCH} != aarch64 && ${ARCH} != amd64 && ${ARCH} != i386 && ${ARCH} != armv6 && ${ARCH} != armv7
# use system libvpx on archs that break with built-in
LIB_DEPENDS+=	libvpx.so:multimedia/libvpx
MAKE_ARGS+=		builtin_libvpx=False
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|custom_build|${OPSYS}_Ports_build|' \
		${WRKSRC}/methods.py
	@${REINPLACE_CMD} -e 's|/usr/bin|${PREFIX}/bin|' \
		${WRKSRC}/platform/x11/os_x11.cpp

pre-build-MONO-on: makenuget
	@(cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${MAKE_FLAGS} \
		${_MAKE_JOBS} ${MAKE_ARGS:C,^${DESTDIRNAME}=.*,,g} \
		target=release_debug tools=True module_mono_enabled=True mono_glue=False)
	@(cd ${WRKSRC} && ${FIND} ${WRKSRC}/bin -name 'godot*' -exec {} \
		--generate-mono-glue modules/mono/glue \; && \
		${FIND} ${WRKSRC}/bin -name 'godot*' -delete)

# The official godot binary name reflects options used to compile
# We just want a simple name matching the portname
# This gives us bin/godot for runtime and bin/godot-tools for the IDE
do-install:
	@${RM} ${WRKSRC}/bin/*.debugsymbols
	cd ${WRKSRC}/bin && ${INSTALL_PROGRAM} godot.x11* \
		${STAGEDIR}/${PREFIX}/bin/${GODOTFILE}

do-install-EXAMPLES-on:
	(cd ${WRKSRC_DEMOS} && ${COPYTREE_SHARE} "${PORTEXAMPLES}" \
		${STAGEDIR}${EXAMPLESDIR})

do-install-TOOLS-on:
	${INSTALL_DATA} ${WRKSRC}/icon.png \
		${STAGEDIR}${PREFIX}/share/pixmaps/${GODOTFILE}.png
	${INSTALL_DATA} ${WRKSRC}/icon.svg \
		${STAGEDIR}${PREFIX}/share/pixmaps/${GODOTFILE}.svg

.include <bsd.port.post.mk>
