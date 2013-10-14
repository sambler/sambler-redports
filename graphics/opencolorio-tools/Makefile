# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	opencolorio
PORTREVISION=	0
PKGNAMESUFFIX=	-tools

COMMENT=	Tools to work with OpenColorIO profiles

LICENSE=	BSD

LIB_DEPENDS=	libOpenImageIO.so:${PORTSDIR}/graphics/openimageio \
		libOpenColorIO.so:${PORTSDIR}/graphics/opencolorio

MASTERDIR=	${.CURDIR}/../opencolorio

CMAKE_ARGS=	-DOCIO_BUILD_APPS:BOOL=ON \
		-DOCIO_BUILD_JNIGLUE:BOOL=OFF \
		-DOCIO_BUILD_NUKE:BOOL=OFF \
		-DOCIO_BUILD_PYGLUE:BOOL=OFF \
		-DOCIO_BUILD_SHARED:BOOL=OFF \
		-DOCIO_BUILD_STATIC:BOOL=OFF \
		-DUSE_EXTERNAL_TINYXML:BOOL=ON \
		-DUSE_EXTERNAL_YAML:BOOL=ON

USE_GL=		glew glut

EXTRA_PATCHES=	${FILESDIR}/extra-patch-CMakeLists.txt

OCIO_TOOLS=	yes

.include "${MASTERDIR}/Makefile"
