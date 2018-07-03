# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	numpy-devel
PORTVERSION=	1.11.1
CATEGORIES=	math python
MASTER_SITES=	http://docs.scipy.org/doc/numpy/:doc \
		SF/numpy/NumPy/${PORTVERSION:S/r/rc/}:source
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTFILES=	numpy-${PORTVERSION:S/r/rc/}${EXTRACT_SUFX}:source \
		numpy-ref-${DOCVERSION}.pdf:doc \
		numpy-user-${DOCVERSION}.pdf:doc
EXTRACT_ONLY=	numpy-${PORTVERSION:S/r/rc/}${EXTRACT_SUFX}
DIST_SUBDIR=	${PORTNAME}${PORTVERSION}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	The New Numeric Extension to Python

LICENSE=	BSD3CLAUSE

CONFLICTS_INSTALL= ${PYTHON_PKGNAMEPREFIX}numpy-*

USES=		fortran python
USE_PYTHON=	concurrent distutils py3kplist
LDFLAGS+=	-shared

OPTIONS_DEFINE=		DOCS SUITESPARSE TESTS
OPTIONS_SINGLE=		BLASLIB
OPTIONS_DEFAULT=	NETLIB SUITESPARSE
OPTIONS_SINGLE_BLASLIB=	ATLAS NETLIB OPENBLAS
SUITESPARSE_DESC=	Use AMD and UMFPACK in SuiteSparse
TESTS_DESC=		Install test suite requirements

PYDISTUTILS_CONFIGUREARGS+=	--fcompiler=gnu95
PYDISTUTILS_BUILDARGS+=		--fcompiler=gnu95

PORTDOCS=	*
WRKSRC=		${WRKDIR}/numpy-${PORTVERSION:S/r/rc/}
DOCVERSION=	1.11.0

ATLAS_USES=	blaslapack:atlas
NETLIB_USES=	blaslapack:netlib
OPENBLAS_USES=	blaslapack:openblas
SUITESPARSE_LIB_DEPENDS=libumfpack.so:math/suitesparse
TESTS_RUN_DEPENDS=	${PYTHON_SITELIBDIR}/nose/__init__.py:devel/py-nose

PLIST_SUB+=	NPVERS=${PORTVERSION}

.include <bsd.port.pre.mk>

post-patch:
	${REINPLACE_CMD} -e "s+%%FC%%+${FC}+" ${WRKSRC}/numpy/distutils/fcompiler/gnu.py
	${CP} ${FILESDIR}/site.cfg ${WRKSRC}/site.cfg

GCCLIBDIR_CMDS=	${FC} -print-file-name=libgfortran.so|${SED} -e s/libgfortran.so//

pre-configure:
.if ${PORT_OPTIONS:MOPENBLAS}
	@${REINPLACE_CMD} -e "s+%%BLASNAME%%+openblas+" \
		-e "s+%%LIBRARIES%%+libraries+" \
		-e "s+%%LAPACKLIBS%%+%%BLASLIBS%%+" \
		-e "s+%%BLASLIBS%%+openblasp, gfortran+" \
			${WRKSRC}/site.cfg
.elif ${PORT_OPTIONS:MATLAS}
	@${REINPLACE_CMD} -e "s+%%BLASNAME%%+atlas+" \
		-e "s+%%LIBRARIES%%+atlas_libs+" \
		-e "s+%%BLASLIBS%%+%%ATLASLIBS%%+" \
		-e "s+%%LAPACKLIBS%%+alapack+" \
		-e "s+%%ATLASLIBS%%+ptf77blas, ptcblas+" \
			${WRKSRC}/site.cfg
.else
	@${REINPLACE_CMD} -e "s+%%BLASNAME%%+atlas+" \
		-e "s+%%LIBRARIES%%+atlas_libs+" \
		-e "s+%%BLASLIBS%%+blas+" \
		-e "s+%%LAPACKLIBS%%+lapack+" \
			${WRKSRC}/site.cfg
.endif
.if !${PORT_OPTIONS:MSUITESPARSE}
	@${REINPLACE_CMD} -e "s+:%%LOCALBASE%%/include/suitesparse++" ${WRKSRC}/site.cfg
.endif
	@${REINPLACE_CMD} -e "s+%%GCCLIBDIR%%+$$(${GCCLIBDIR_CMDS})+" \
	    -e "s+%%LOCALBASE%%+${LOCALBASE}+g" \
		${WRKSRC}/site.cfg
	@${REINPLACE_CMD} -e "s+%%GCCLIBDIR%%+$$(${GCCLIBDIR_CMDS})+" ${WRKSRC}/numpy/distutils/system_info.py

post-install:
	@${FIND} ${STAGEDIR}${PYTHON_SITELIBDIR}/numpy -name "*.so" | ${XARGS} ${STRIP_CMD}
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${DISTDIR}/${DIST_SUBDIR}/numpy-ref-${DOCVERSION}.pdf ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${DISTDIR}/${DIST_SUBDIR}/numpy-user-${DOCVERSION}.pdf ${STAGEDIR}${DOCSDIR}
.endif

.include <bsd.port.post.mk>
