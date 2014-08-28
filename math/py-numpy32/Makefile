# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	numpy32
PORTVERSION=	1.9.0r1
CATEGORIES=	math python
#MASTER_SITES=	SF/numpy/NumPy/${PORTVERSION}:source
MASTER_SITES=	SF/numpy/NumPy/1.9.0rc1:source
#		http://docs.scipy.org/doc/numpy-${PORTVERSION}/:doc
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
#DISTFILES=	numpy-${PORTVERSION}${EXTRACT_SUFX}:source
DISTFILES=	numpy-1.9.0rc1${EXTRACT_SUFX}:source
#		numpy-ref-${PORTVERSION}.pdf:doc \
#		numpy-user-${PORTVERSION}.pdf:doc
#EXTRACT_ONLY=	numpy-${PORTVERSION}${EXTRACT_SUFX}
EXTRACT_ONLY=	numpy-1.9.0rc1${EXTRACT_SUFX}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	The New Numeric Extension to Python

LICENSE=	BSD3CLAUSE

RUN_DEPENDS=	nosetests:${PORTSDIR}/devel/py-nose

OPTIONS_DEFINE=	ATLAS SUITESPARSE
OPTIONS_DEFAULT=	SUITESPARSE
ATLAS_DESC=	Use optimized blas library
SUITESPARSE_DESC=	Use AMD and UMFPACK in SuiteSparse

USES=		fortran python:3.2
USE_PYTHON=	distutils
PYDISTUTILS_CONFIGUREARGS+=	--fcompiler=gnu95
PYDISTUTILS_BUILDARGS+=		--fcompiler=gnu95

#PORTDOCS=	*
#WRKSRC=		${WRKDIR}/numpy-${PORTVERSION}
WRKSRC=		${WRKDIR}/numpy-1.9.0rc1

.include <bsd.port.pre.mk>

.if ${PORT_OPTIONS:MATLAS}
LIB_DEPENDS+=	libatlas.so:${PORTSDIR}/math/atlas
.else
LIB_DEPENDS+=	liblapack.so:${PORTSDIR}/math/lapack \
		libblas.so:${PORTSDIR}/math/blas
.endif

.if ${PORT_OPTIONS:MSUITESPARSE}
LIB_DEPENDS+=	libumfpack.so:${PORTSDIR}/math/suitesparse
.endif

#post-extract:
#	@${CP} ${DISTDIR}/numpy-ref-${PORTVERSION}.pdf ${WRKDIR}
#	@${CP} ${DISTDIR}/numpy-user-${PORTVERSION}.pdf ${WRKDIR}

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

#post-install:
#	#${INSTALL_MAN} ${WRKSRC}/numpy/f2py/f2py.1 ${STAGEDIR}${MANPREFIX}/man/man1
#	@${MKDIR} ${STAGEDIR}${DOCSDIR}
#	${INSTALL_DATA} ${WRKDIR}/numpy-ref-${PORTVERSION}.pdf ${STAGEDIR}${DOCSDIR}
#	${INSTALL_DATA} ${WRKDIR}/numpy-user-${PORTVERSION}.pdf ${STAGEDIR}${DOCSDIR}

.include <bsd.port.post.mk>
