# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME?=	numpy-devel
PORTVERSION=	1.9.0
CATEGORIES=	math python
MASTER_SITES=	SF/numpy/NumPy/${PORTVERSION}
#		http://docs.scipy.org/doc/numpy/${PORTVERSION}/:doc
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTFILES=	numpy-${PORTVERSION}${EXTRACT_SUFX} \
		reference.pdf \
		userguide.pdf
EXTRACT_ONLY=	numpy-${PORTVERSION}${EXTRACT_SUFX}
DIST_SUBDIR=	numpy${PORTVERSION}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	The New Numeric Extension to Python

LICENSE=	BSD3CLAUSE
CONFLICTS_INSTALL= ${PYTHON_PKGNAMEPREFIX}numpy-*

RUN_DEPENDS=	nosetests:${PORTSDIR}/devel/py-nose

OPTIONS_DEFINE=	ATLAS SUITESPARSE
OPTIONS_DEFAULT=	SUITESPARSE
ATLAS_DESC=	Use optimized blas library
SUITESPARSE_DESC=	Use AMD and UMFPACK in SuiteSparse

USES=		fortran python
USE_PYTHON=	distutils concurrent py3kplist
LDFLAGS+=	-shared

OPTIONS_DEFINE=		ATLAS SUITESPARSE DOCS
OPTIONS_DEFAULT=	SUITESPARSE
ATLAS_DESC=		Use optimized blas library
SUITESPARSE_DESC=	Use AMD and UMFPACK in SuiteSparse

PYDISTUTILS_CONFIGUREARGS+=	--fcompiler=gnu95
PYDISTUTILS_BUILDARGS+=		--fcompiler=gnu95

PORTDOCS=	*
WRKSRC=		${WRKDIR}/numpy-${PORTVERSION}
INSTALL_TARGET=install-strip

ATLAS_LIB_DEPENDS=	libatlas.so:${PORTSDIR}/math/atlas
ATLAS_LIB_DEPENDS_OFF=	libblas.so:${PORTSDIR}/math/blas \
			liblapack.so:${PORTSDIR}/math/lapack
SUITESPARSE_LIB_DEPENDS=libumfpack.so:${PORTSDIR}/math/suitesparse

.include <bsd.port.pre.mk>

PLIST_SUB+=	PYTHON_VER=${PYTHON_VER}
.if ${PYTHON_VERSION} == ${PYTHON_DEFAULT_VERSION}
PLIST_FILES+=	man/man1/f2py.1.gz
.endif

post-extract:
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/reference.pdf ${WRKDIR}
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/userguide.pdf ${WRKDIR}

post-patch:
	@${REINPLACE_CMD} -e "s+%%FC%%+${FC}+" ${WRKSRC}/numpy/distutils/fcompiler/gnu.py
	@${CP} ${FILESDIR}/site.cfg ${WRKSRC}/site.cfg
# ignore LDFLAGS from env, as it overrides internal flags (e.g. -shared) for some reason
	@${REINPLACE_CMD} -e "s|'LDFLAGS'|None|" ${WRKSRC}/numpy/distutils/fcompiler/__init__.py

GCCLIBDIR_CMDS=	${FC} -print-file-name=libgfortran.so|${SED} -e s/libgfortran.so//

pre-configure:
.if ${PORT_OPTIONS:MATLAS}
	@${REINPLACE_CMD} -e "s+%%ATLASLIBS%%+alapack, f77blas, cblas, atlas+" ${WRKSRC}/site.cfg
.else
	@${REINPLACE_CMD} -e "s+%%ATLASLIBS%%+lapack, blas+" ${WRKSRC}/site.cfg
.endif
.if !${PORT_OPTIONS:MSUITESPARSE}
	@${REINPLACE_CMD} -e "s+:%%LOCALBASE%%/include/suitesparse++" ${WRKSRC}/site.cfg
.endif
	@${REINPLACE_CMD} -e "s+%%GCCLIBDIR%%+$$(${GCCLIBDIR_CMDS})+" \
	    -e "s+%%LOCALBASE%%+${LOCALBASE}+g" \
		${WRKSRC}/site.cfg
	@${REINPLACE_CMD} -e "s+%%GCCLIBDIR%%+$$(${GCCLIBDIR_CMDS})+" ${WRKSRC}/numpy/distutils/system_info.py

post-install:
	${INSTALL_MAN} ${WRKSRC}/doc/f2py/f2py.1 ${STAGEDIR}${MANPREFIX}/man/man1/f2py-${PYTHON_VER}.1
.if ${PYTHON_VERSION} == ${PYTHON_DEFAULT_VERSION}
	${LN} -sf ${MANPREFIX}/man/man1/f2py-${PYTHON_VER}.1 ${STAGEDIR}${MANPREFIX}/man/man1/f2py.1
.endif
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKDIR}/reference.pdf ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKDIR}/userguide.pdf ${STAGEDIR}${DOCSDIR}

.include <bsd.port.post.mk>
