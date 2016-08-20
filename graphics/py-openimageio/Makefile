# Created by: Shane Ambler
# $FreeBSD$

CATEGORIES=	graphics multimedia python
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

COMMENT=	OpenImageIO python bindings

MASTERDIR=	${.CURDIR}/../openimageio
# we want to use the same options as the main port
OPTIONS_NAME=	graphics_openimageio

do-install:
	@${MKDIR} ${STAGEDIR}${PYTHON_SITELIBDIR}
	${INSTALL_LIB} ${BUILD_WRKSRC}/src/python/OpenImageIO.so ${STAGEDIR}${PYTHON_SITELIBDIR}

.include "${MASTERDIR}/Makefile"
