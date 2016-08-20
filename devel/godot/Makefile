# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	godot
PORTVERSION=	2.1
DISTVERSIONSUFFIX=	-stable
CATEGORIES=	devel games

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT?=	Game runtime engine

LICENSE=		MIT CCBYv3
LICENSE_COMB=		multi
LICENSE_NAME_CCBYv3=	Creative Commons Attribution 3.0 Unported license
LICENSE_FILE_MIT=	${WRKSRC}/LICENSE.md
LICENSE_FILE_CCBYv3=	${WRKSRC}/LOGO_LICENSE.md
LICENSE_PERMS_CCBYv3=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

LIB_DEPENDS=	libfreetype.so:print/freetype2
RUN_DEPENDS=	xdg-user-dir:devel/xdg-user-dirs \
		xdg-open:devel/xdg-utils \
		xmessage:x11/xmessage

USE_GITHUB=	yes
GH_ACCOUNT=	godotengine
GH_TAGNAME_DEMOS=	dfa1274

USES=		scons ssl pkgconfig compiler
USE_XORG=	x11 xcursor xinerama xrandr
USE_GL=		gl

MAKE_ARGS+=	platform=x11
CXXFLAGS+=	-DGLEW_NO_GLU -DRTAUDIO_ENABLED

OPTIONS_DEFINE+=	DEBUG
OPTIONS_DEFAULT+=	OSS
OPTIONS_GROUP=		AUDIO
OPTIONS_GROUP_AUDIO=	ALSA OSS PULSEAUDIO

EXAMPLES_GH_TUPLE=	godotengine:godot-demo-projects:${GH_TAGNAME_DEMOS}:DEMOS

AUDIO_DESC=		Supported audio
ALSA_LIB_DEPENDS=	libasound.so:audio/alsa-lib
ALSA_MAKE_ARGS=		alsa=yes
OSS_MAKE_ARGS=		oss=yes
PULSEAUDIO_LIB_DEPENDS=	libpulse-simple.so:audio/pulseaudio
PULSEAUDIO_MAKE_ARGS=	pulseaudio=yes

GODOTFILE=		${PORTNAME}${PKGNAMESUFFIX}
PLIST_FILES=		bin/${GODOTFILE}
PORTDATA=		*

.include <bsd.port.pre.mk>

.ifdef WITH_DEBUG
MAKE_ARGS+=	target=debug
.elif ${SLAVE_PORT} == yes
MAKE_ARGS+=	target=release_debug
.else #SLAVE_PORT
MAKE_ARGS+=	target=release
.endif #SLAVE_PORT

.if ${SLAVE_PORT} == yes
MAKE_ARGS+=	tools=yes
DESKTOP_ENTRIES=	"Godot" "${COMMENT}" "${GODOTFILE}" \
			"${GODOTFILE}" "Development;IDE;" ""
PLIST_FILES+=	share/pixmaps/${GODOTFILE}.png \
		share/pixmaps/${GODOTFILE}.svg
.else #SLAVE_PORT
MAKE_ARGS+=	tools=no
.endif #SLAVE_PORT

.if ${CHOSEN_COMPILER_TYPE} == clang
MAKE_ARGS+=	use_llvm=yes
.else  # clang
USE_GCC=	yes
.if ${ARCH} == i386
CXXFLAGS+=	-march=i586
.endif
.endif # clang

post-patch:
	@${REINPLACE_CMD} -e 's|custom_build|${OPSYS}_Ports_build|' \
		${WRKSRC}/methods.py
	@${REINPLACE_CMD} -e 's|/usr/bin|${PREFIX}/bin|' \
		${WRKSRC}/platform/x11/os_x11.cpp

# the official godot binary name reflects options used to compile
# we just want a simple name matching the portname
# this gives us bin/godot for runtime and bin/godot-tools for the IDE
do-install:
	@cd ${WRKSRC}/bin && ${INSTALL_PROGRAM} godot.x11* \
		${STAGEDIR}/${PREFIX}/bin/${GODOTFILE}
.if ${SLAVE_PORT} == yes
	${INSTALL_DATA} ${WRKSRC}/icon.png \
		${STAGEDIR}${PREFIX}/share/pixmaps/${GODOTFILE}.png
	${INSTALL_DATA} ${WRKSRC}/icon.svg \
		${STAGEDIR}${PREFIX}/share/pixmaps/${GODOTFILE}.svg
.endif

do-install-EXAMPLES-on:
	(cd ${WRKSRC_DEMOS} && ${COPYTREE_SHARE} "${PORTDATA}" \
		${STAGEDIR}${DATADIR}/demos)

.include <bsd.port.post.mk>
