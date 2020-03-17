# Created by: Jonathan Chen <jonc@chen.org.nz>
# $FreeBSD$

PORTNAME=	sigil-sambler
PORTVERSION=	0.9.14
CATEGORIES=	textproc

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	WYSIWYG ePub editor

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING.txt

LIB_DEPENDS=	libminizip.so:archivers/minizip \
		libpcre.so:devel/pcre \
		libhunspell-1.7.so:textproc/hunspell
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}lxml>0:devel/py-lxml@${PY_FLAVOR}

USES=		cmake compiler:c++11-lib desktop-file-utils \
		pkgconfig python:3.4+ qt:5 shebangfix

SHEBANG_FILES=	src/Resource_Files/plugin_launchers/python/*.py \
		src/Resource_Files/python3lib/*.py

USE_GITHUB=	yes
GH_ACCOUNT=	Sigil-Ebook
GH_PROJECT=	Sigil

USE_QT=		concurrent core declarative gui location network printsupport \
		svg webchannel webkit widgets xml xmlpatterns \
		buildtools_build linguisttools_build qmake_build \
		imageformats_run

CMAKE_ARGS=	-DUSE_SYSTEM_LIBS:BOOL=1 \
		-DINSTALL_BUNDLED_DICTS:BOOL=1 \
		-DEXTRA_DICT_DIRS:STRING=${LOCALBASE}/share/hunspell \
		-DPYTHON_EXECUTABLE:STRING=${PYTHON_CMD} \
		-DPYTHON_LIBRARY:STRING=${LOCALBASE}/lib/libpython${PYTHON_VER}${PYTHON_ABIVER}.so \
		-DPYTHON_INCLUDE_DIR:STRING=${PYTHON_INCLUDEDIR} \
		-DSHARE_INSTALL_PREFIX=${DATADIR}
USE_LDCONFIG=	${PREFIX}/lib/sigil-sambler

# Upstream uses pkg-config output to pass libhunspell-1.7.so and
# libpcre16.so to the linker. pkg-config output does not include full
# paths, so add a workaround to keep the port linking for now.
LDFLAGS+=	-L${LOCALBASE}/lib

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/sigil-sambler/*.so

.include <bsd.port.mk>
