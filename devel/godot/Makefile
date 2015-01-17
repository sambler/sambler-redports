# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	godot
PORTVERSION=	1.0
CATEGORIES=	devel games

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Game development environment

LICENSE=	MIT

USE_GITHUB=	yes
GH_ACCOUNT=	okamstudio
GH_PROJECT=	godot
GH_TAGNAME=	${PORTVERSION}-stable
GH_COMMIT=	7eb5d04

LIB_DEPENDS=	libfreetype.so:${PORTSDIR}/print/freetype2 \
		libasound.so:${PORTSDIR}/audio/alsa-lib

USES=		scons pkgconfig
USE_XORG=	x11 xcursor
USE_GL=		glu
USE_OPENSSL=	yes
# uses pkg-config to find ssl - pkg-config only finds port version
WITH_OPENSSL_PORT=	yes

MAKE_ARGS+=	platform=x11 CCFLAGS="${CXXFLAGS}" LINKFLAGS="${LDFLAGS}"
#MAKE_ARGS+=	openssl=builtin 

OPTIONS_DEFINE=	LLVM EXAMPLES SANITIZE
OPTIONS_DEFAULT= LLVM
OPTIONS_SUB=	yes

LLVM_DESC=		Build using clang/llvm
LLVM_BUILD_DEPENDS=	clang++34:${PORTSDIR}/lang/clang34

SANITIZE_DESC=		Use llvm-sanitizer (needs CLANG)

.include <bsd.port.options.mk>

.if ${ARCH}==amd64 || ${ARCH}==powerpc64 || ${ARCH}==sparc64 || ${ARCH}==ia64
BITSUF=	64
.else
BITSUF=	32
.endif
.if ${PORT_OPTIONS:MLLVM}
#LLSUF=	.llvm
MAKE_ARGS+=	use_llvm=yes
CC=	/usr/local/bin/clang34
CXX=	/usr/local/bin/clang++34
CPP=	/usr/local/bin/clang-cpp34
.if ${PORT_OPTIONS:MSANITIZE}
#SANSUF=	s
MAKE_ARGS+=	use_sanitizer=yes
.endif
.endif

BINSUFFIX=	${BITSUF}${LLSUF}${SANSUF}
PLIST_SUB+=	BINSUFF=${BINSUFFIX}

post-patch:
	@${REINPLACE_CMD} -e 's|custom_build|FreeBSD Ports build|' ${WRKSRC}/methods.py

do-install:
	@${INSTALL_PROGRAM} ${WRKSRC}/bin/godot.x11.tools.${BINSUFFIX} \
		${STAGEDIR}/${PREFIX}/bin/godot.x11.tools.${BINSUFFIX}
	@${LN} ${STAGEDIR}/${PREFIX}/bin/godot.x11.tools.${BINSUFFIX} \
		${STAGEDIR}/${PREFIX}/bin/godot
.if ${PORT_OPTIONS:MEXAMPLES}
	${MKDIR} ${STAGEDIR}${DATADIR}
	(cd ${WRKSRC} && ${COPYTREE_SHARE} demos ${STAGEDIR}${DATADIR})
	${RM} ${STAGEDIR}${DATADIR}/demos/2d/hexamap/.fscache
.endif

.include <bsd.port.mk>
