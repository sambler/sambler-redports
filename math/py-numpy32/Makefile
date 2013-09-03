# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	numpy32
PORTVERSION=	1.8.0b1
PORTREVISION=	0
CATEGORIES=	math python
MASTER_SITES=	http://docs.scipy.org/doc/${DISTNAME:C/\..$/.0/}/:doc \
		SF/numpy/NumPy/${PORTVERSION}:source
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTFILES=	numpy-${PORTVERSION}${EXTRACT_SUFX}:source \
		numpy-ref.pdf:doc \
		numpy-user.pdf:doc
EXTRACT_ONLY=	numpy-${PORTVERSION}${EXTRACT_SUFX}

MAINTAINER=	llwang@infor.org
COMMENT=	The New Numeric Extension to Python

LICENSE=	BSD

RUN_DEPENDS=	nosetests:${PORTSDIR}/devel/py-nose

OPTIONS_DEFINE=	ATLAS SUITESPARSE
OPTIONS_DEFAULT=	SUITESPARSE
ATLAS_DESC=	Use optimized blas library
SUITESPARSE_DESC=	Use AMD and UMFPACK in SuiteSparse

USE_FORTRAN=	yes
USE_PYTHON=	3.2
USE_PYDISTUTILS=yes
MAN1=		f2py32.1
NO_CHECKSUM=	yes

LATEST_LINK=	py-${PORTNAME}
WRKSRC=	${WRKDIR}/numpy-${PORTVERSION}

PYDISTUTILS_NOEGGINFO= yes

.include <bsd.port.pre.mk>

.if (${OSVERSION} <= 703100 || \
(${OSVERSION} >= 800000 && ${OSVERSION} <= 800502) || \
(${OSVERSION} >= 900000 && ${OSVERSION} <= 900009)) && \
(${ARCH} == "i386" || ${ARCH} == "amd64")
WITH_FIXED_FENV=	yes
.endif

.if defined(WITH_FIXED_FENV)
MASTER_SITES+=	http://svn.freebsd.org/base/head/lib/msun/:fp
.if ${ARCH} == "i386"
FP_ARCH=	i387
.elif ${ARCH} == "amd64"
FP_ARCH=	${ARCH}
.endif
DISTFILES+=	${FP_ARCH}/fenv.c?p=203441:fp ${FP_ARCH}/fenv.h?p=203441:fp
.endif

.if ${PORT_OPTIONS:MATLAS}
LIB_DEPENDS+=	libatlas.so:${PORTSDIR}/math/atlas
.if !exists(${LOCALBASE}/lib/libalapack.a)
IGNORE=	atlas needs to be built with WITH_STATIC for numpy to function properly
.endif
.else
LIB_DEPENDS+=	liblapack.so:${PORTSDIR}/math/lapack \
		libblas.so:${PORTSDIR}/math/blas
.endif

.if ${PORT_OPTIONS:MSUITESPARSE}
LIB_DEPENDS+=	libumfpack.so:${PORTSDIR}/math/suitesparse
.endif

PYDISTUTILS_CONFIGUREARGS+=	--fcompiler=gnu95
PYDISTUTILS_BUILDARGS+=	--fcompiler=gnu95

post-extract:
	@${CP} ${DISTDIR}/numpy-ref.pdf ${WRKDIR}
	@${CP} ${DISTDIR}/numpy-user.pdf ${WRKDIR}

post-patch:
	@${REINPLACE_CMD} -e "s+%%FC%%+${FC}+" ${WRKSRC}/numpy/distutils/fcompiler/gnu.py
	@${CP} ${FILESDIR}/site.cfg ${WRKSRC}/site.cfg
# ignore LDFLAGS from env, as it overrides internal flags (e.g. -shared) for some reason
	@${REINPLACE_CMD} -e "s|'LDFLAGS'|None|" ${WRKSRC}/numpy/distutils/fcompiler/__init__.py

GCCLIBDIR_CMDS=	${FC} -print-file-name=libgfortran.so|${SED} -e s/libgfortran.so//
pre-configure:
.if defined(WITH_FIXED_FENV)
	@if [ "`${PKG_VERSION} -t \"\`\\\`${CC} -print-prog-name=as\\\` --version | ${AWK} 'NR==1 {sub(/\(GNU Binutils\)/,""); print $$3}'\`\" 2.18.49`" = ">" ] ; then \
		${CP} ${DISTDIR}/${FP_ARCH}/fenv.c?p=203441 ${WRKSRC}/numpy/core/include/numpy/fenv/fenv.c; \
		${CP} ${DISTDIR}/${FP_ARCH}/fenv.h?p=203441 ${WRKSRC}/numpy/core/include/numpy/fenv/fenv.h; \
		${REINPLACE_CMD} -e 's|<fenv.h>|"fenv.h"|' ${WRKSRC}/numpy/core/include/numpy/fenv/fenv.c; \
		${PATCH} ${PATCH_DIST_ARGS} < ${FILESDIR}/fenv.patch; \
 	fi
.endif
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

pre-install:
.if defined(WITH_FIXED_FENV)
	@if [ "`${PKG_VERSION} -t \"\`\\\`${CC} -print-prog-name=as\\\` --version | ${AWK} 'NR==1 {sub(/\(GNU Binutils\)/,""); print $$3}'\`\" 2.18.49`" = ">" ] ; then \
		${RM} ${WRKSRC}/numpy/core/include/numpy/fenv/fenv.c.bak; \
	fi
.endif

post-install:
	${INSTALL_MAN} ${WRKSRC}/numpy/f2py/f2py.1 ${MAN1PREFIX}/man/man1/f2py32.1
.if !defined(NOPORTDOCS)
	@${MKDIR} ${DOCSDIR}
	${INSTALL_DATA} ${WRKDIR}/numpy-ref.pdf ${DOCSDIR}
	${INSTALL_DATA} ${WRKDIR}/numpy-user.pdf ${DOCSDIR}
.endif
.if defined(WITH_FIXED_FENV)
	@if [ "`${PKG_VERSION} -t \"\`\\\`${CC} -print-prog-name=as\\\` --version | ${AWK} 'NR==1 {sub(/\(GNU Binutils\)/,""); print $$3}'\`\" 2.18.49`" = ">" ] ; then \
		${REINPLACE_CMD} -e "s|%%FENV%%||g" ${TMPPLIST}; \
	else \
		${REINPLACE_CMD} -e "s|%%FENV%%|@comment |g" ${TMPPLIST}; \
	fi
.else
	@${REINPLACE_CMD} -e "s|%%FENV%%|@comment |g" ${TMPPLIST}
.endif

.include <bsd.port.post.mk>