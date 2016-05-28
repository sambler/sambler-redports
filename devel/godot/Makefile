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

ALSA_LIB_DEPENDS=	libasound.so:audio/alsa-lib
ALSA_MAKE_ARGS=		alsa=yes
OSS_MAKE_ARGS=		oss=yes
PULSEAUDIO_LIB_DEPENDS=	libpulse-simple.so:audio/pulseaudio
PULSEAUDIO_MAKE_ARGS=	pulseaudio=yes

PORTDATA=	*
PLIST_FILES=	bin/${PORTNAME}${PKGNAMESUFFIX}

.include <bsd.port.pre.mk>

.if ${SLAVE_PORT} == yes
MAKE_ARGS+=	tools=yes
.ifdef WITH_DEBUG
MAKE_ARGS+=	target=debug
TOOLSUF=	.tools
.else #WITH_DEBUG
MAKE_ARGS+=	target=release_debug
TOOLSUF=	.opt.tools
.endif #WITH_DEBUG
DESKTOP_ENTRIES=	"Godot" "${COMMENT}" "${PORTNAME}${PKGNAMESUFFIX}" \
			"${PORTNAME}${PKGNAMESUFFIX}" "Development;IDE;" ""
PLIST_FILES+=	share/pixmaps/${PORTNAME}${PKGNAMESUFFIX}.png \
		share/pixmaps/${PORTNAME}${PKGNAMESUFFIX}.svg
.else #SLAVE_PORT
MAKE_ARGS+=	tools=no target=release
TOOLSUF=	.opt
.endif #SLAVE_PORT

.if ${ARCH}==amd64 || ${ARCH}==powerpc64 || ${ARCH}==sparc64 || ${ARCH}==ia64
BITSUF=	.64
.else
BITSUF=	.32
.endif

.if ${CHOSEN_COMPILER_TYPE} == clang
LLSUF=	.llvm
MAKE_ARGS+=	use_llvm=yes
.else  # clang
USE_GCC=	yes
.if ${ARCH} == i386
CXXFLAGS+=	-march=i586
.endif
.endif # clang

BINSUFFIX=	${TOOLSUF}${BITSUF}${LLSUF}

post-patch:
	@${REINPLACE_CMD} -e 's|custom_build|${OPSYS}_Ports_build|' \
		${WRKSRC}/methods.py

# the official godot binary name reflects options used to compile
# we just want a simple name matching the portname
# this gives us bin/godot for runtime and bin/godot-tools for the IDE
do-install:
	@cd ${WRKSRC}/bin && ${INSTALL_PROGRAM} godot.x11${BINSUFFIX} \
		${STAGEDIR}/${PREFIX}/bin/${PORTNAME}${PKGNAMESUFFIX}
.if ${SLAVE_PORT} == yes
	${INSTALL_DATA} ${WRKSRC}/icon.png \
		${STAGEDIR}${PREFIX}/share/pixmaps/${PORTNAME}${PKGNAMESUFFIX}.png
	${INSTALL_DATA} ${WRKSRC}/icon.svg \
		${STAGEDIR}${PREFIX}/share/pixmaps/${PORTNAME}${PKGNAMESUFFIX}.svg
.endif

do-install-EXAMPLES-on:
	@${MKDIR} ${STAGEDIR}${DATADIR}
	(cd ${WRKSRC} && ${COPYTREE_SHARE} demos ${STAGEDIR}${DATADIR})
	${RM} ${STAGEDIR}${DATADIR}/demos/2d/hexamap/.fscache

.include <bsd.port.post.mk>
