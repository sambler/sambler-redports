# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	godot
PORTVERSION=	2.0.3
DISTVERSIONSUFFIX=	-stable
PORTREVISION=	1
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
RUN_DEPENDS=	xdg-open:devel/xdg-utils \
		xdg-user-dir:devel/xdg-user-dirs \
		xmessage:x11/xmessage

USE_GITHUB=	yes
GH_ACCOUNT=	godotengine

USES=		scons pkgconfig compiler
USE_XORG=	x11 xcursor xinerama
USE_GL=		gl glu
USE_OPENSSL=	yes

MAKE_ARGS+=	platform=x11
CXXFLAGS+=	-DRTAUDIO_ENABLED

OPTIONS_GROUP=		AUDIO
OPTIONS_GROUP_AUDIO=	ALSA OSS PULSEAUDIO
OPTIONS_DEFAULT=	OSS

AUDIO_DESC=		Supported audio
ALSA_LIB_DEPENDS=	libasound.so:audio/alsa-lib
ALSA_MAKE_ARGS=		alsa=yes
OSS_MAKE_ARGS=		oss=yes
PULSEAUDIO_LIB_DEPENDS=	libpulse-simple.so:audio/pulseaudio
PULSEAUDIO_MAKE_ARGS=	pulseaudio=yes

GODOTFILE=	${PORTNAME}${PKGNAMESUFFIX}
PLIST_FILES=	bin/${PORTNAME}${PKGNAMESUFFIX}
PORTDATA=	*

.include <bsd.port.pre.mk>

.if ${SLAVE_PORT} == yes
MAKE_ARGS+=	tools=yes
.ifdef WITH_DEBUG
MAKE_ARGS+=	target=debug
.else #WITH_DEBUG
MAKE_ARGS+=	target=release_debug
.endif #WITH_DEBUG
DESKTOP_ENTRIES=	"Godot" "${COMMENT}" "${GODOTFILE}" \
			"${GODOTFILE}" "Development;IDE;" ""
PLIST_FILES+=	share/pixmaps/${GODOTFILE}.png \
		share/pixmaps/${GODOTFILE}.svg
.else #SLAVE_PORT
MAKE_ARGS+=	tools=no target=release
.endif #SLAVE_PORT

.if ${CHOSEN_COMPILER_TYPE} == clang
LLSUF=	.llvm
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
	@${MKDIR} ${STAGEDIR}${DATADIR}
	(cd ${WRKSRC} && ${COPYTREE_SHARE} demos ${STAGEDIR}${DATADIR})

.include <bsd.port.post.mk>
