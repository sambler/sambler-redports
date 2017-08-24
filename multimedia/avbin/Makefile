# Created by: Dmitry Marakasov <amdmi3@FreeBSD.org>
# $FreeBSD$

PORTNAME=	avbin
PORTVERSION=	10
DISTVERSIONPREFIX= avbin-
CATEGORIES=	multimedia

MAINTAINER=	amdmi3@FreeBSD.org
COMMENT=	FFmpeg wrapper

LICENSE=	LGPL3

LIB_DEPENDS=	libavcodec.so:multimedia/ffmpeg

USE_GITHUB=	yes

LIBNAME=	libavbin.so.${PORTVERSION}
PLIST_FILES=	include/avbin.h \
		lib/${LIBNAME} \
		lib/libavbin.so
USE_LDCONFIG=	yes
WRKSRC=		${WRKDIR}/AVbin-${PORTNAME}-${PORTVERSION}

.include <bsd.port.options.mk>

.if ${ARCH} == "amd64" || ${ARCH} == "ia64"
CFLAGS+=	-fPIC
.endif

do-build:
	cd ${WRKSRC} && \
		${CC} ${CFLAGS} -shared -Wl,-soname,${LIBNAME} -o ${LIBNAME} \
		src/avbin.c -Iinclude -I${LOCALBASE}/include \
		-DAVBIN_VERSION=${PORTVERSION} \
		-DAVBIN_PRERELEASE="" \
		-DAVBIN_VERSION_STRING="\"$AVBIN_VERSION$AVBIN_PRERELEASE\"" \
		-DAVBIN_BUILD_DATE="\"`date +\"%Y-%m-%d %H:%M:%S %z\"`\"" \
		-DAVBIN_REPO="\"http://github.com/AVbin/AVbin.git\"" \
		-DAVBIN_COMMIT="\"avbin-10\"" \
		-DAVBIN_BACKEND="\"ffmpeg\"" \
		-DAVBIN_BACKEND_VERSION_STRING="\"2.8.7\"" \
		-DAVBIN_BACKEND_REPO="\"Release tarball\"" \
		-DAVBIN_BACKEND_COMMIT="\"2.8.7\"" \
		-DFFMPEG_REVISION=2 \
		-L${LOCALBASE}/lib -lavcodec -lavformat

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${LIBNAME} ${STAGEDIR}${PREFIX}/lib/
	${LN} -s ${LIBNAME} ${STAGEDIR}${PREFIX}/lib/libavbin.so
	${INSTALL_DATA} ${WRKSRC}/include/avbin.h ${STAGEDIR}${PREFIX}/include/

.include <bsd.port.mk>
