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

USES=		scons pkgconfig compiler
USE_XORG=	x11 xcursor
USE_GL=		glu
USE_OPENSSL=	yes
# uses pkg-config to find ssl - pkg-config only finds port version
WITH_OPENSSL_PORT=	yes

MAKE_ARGS+=	platform=x11 
#MAKE_ARGS+=	openssl=builtin

OPTIONS_DEFINE=	EXAMPLES SANITIZE
OPTIONS_DEFAULT= EXAMPLES
OPTIONS_SUB=	yes

SANITIZE_DESC=		Use sanitize=address

.include <bsd.port.pre.mk>

.if ${ARCH}==amd64 || ${ARCH}==powerpc64 || ${ARCH}==sparc64 || ${ARCH}==ia64
BITSUF=	64
.else
BITSUF=	32
.endif

.if ${COMPILER_TYPE} == clang
.if ${OSVERSION} < 900000
BROKEN=	clang fails to link on 8.x
.endif
#LLSUF=	.llvm
MAKE_ARGS+=	use_llvm=yes
.else  # LLVM
USE_GCC=	4.8+
.if ${ARCH} == i386
CXXFLAGS+=	-march=i586
.endif
.endif # LLVM

.if ${PORT_OPTIONS:MSANITIZE}
#SANSUF=	s
MAKE_ARGS+=	use_sanitizer=yes
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

.include <bsd.port.post.mk>
