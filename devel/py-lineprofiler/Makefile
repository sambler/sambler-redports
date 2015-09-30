# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	lineprofiler
PORTVERSION=	1.0
CATEGORIES=	devel python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTNAME=	line_profiler-${PORTVERSION}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Line-by-line time profiling

LICENSE=	BSD3CLAUSE PSFL
LICENSE_COMB=	multi
#The file timers.c was derived from the timer code in Python 2.5.2's _lsprof.c
#file and falls under the PSF license - the rest is under the bsd 3-clause

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}cython>=0.10:${PORTSDIR}/lang/cython

USES=		python shebangfix
USE_PYTHON=	autoplist concurrent distutils

python_OLD_CMD=	"/usr/bin/env\ python"
SHEBANG_FILES=	${WRKSRC}/line_profiler.py ${WRKSRC}/kernprof.py
PLIST_FILES=	bin/line_profiler bin/kernprof

post-install:
	${INSTALL_SCRIPT} ${WRKSRC}/line_profiler.py ${STAGEDIR}${PREFIX}/bin/line_profiler
	${INSTALL_SCRIPT} ${WRKSRC}/kernprof.py ${STAGEDIR}${PREFIX}/bin/kernprof
	@${STRIP_CMD} ${STAGEDIR}${PYTHON_SITELIBDIR}/_line_profiler.so

.include <bsd.port.mk>
