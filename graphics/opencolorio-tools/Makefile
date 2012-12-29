# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD: ports/graphics/opencolorio-tools/Makefile,v 1.1 2012/12/20 10:45:19 svnexp Exp $

PORTNAME=	opencolorio
PORTREVISION=	0
PKGNAMESUFFIX=	-tools

COMMENT=	Tools to work with OpenColorIO profiles

LICENSE=	BSD

LIB_DEPENDS=	OpenImageIO:${PORTSDIR}/graphics/openimageio \
		OpenColorIO:${PORTSDIR}/graphics/opencolorio

MASTERDIR=	${.CURDIR}/../opencolorio

CMAKE_ARGS=	-DOCIO_BUILD_APPS:BOOL=ON \
		-DOCIO_BUILD_JNIGLUE:BOOL=OFF \
		-DOCIO_BUILD_NUKE:BOOL=OFF \
		-DOCIO_BUILD_PYGLUE:BOOL=OFF \
		-DOCIO_BUILD_SHARED:BOOL=OFF \
		-DOCIO_BUILD_STATIC:BOOL=OFF \
		-DOCIO_BUILD_DOCS:BOOL=OFF

USE_GL=		glew glut
LDFLAGS+=	-L${LOCALBASE}/lib

EXTRA_PATCHES=	${FILESDIR}/extra-patch-CMakeLists.txt \
		${FILESDIR}/extra-patch-src__apps__ocioconvert__main.cpp \
		${FILESDIR}/extra-patch-src__apps__ociodisplay__main.cpp \
		${FILESDIR}/extra-patch-src__apps__ociolutimage__main.cpp

OCIO_TOOLS=	yes

.include "${MASTERDIR}/Makefile"
