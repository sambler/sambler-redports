# Created by: Shane Ambler
# $FreeBSD$

PORTNAME=	nucular
PORTVERSION=	0.5
CATEGORIES=	textproc python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	fielded text indexing and retrieval

LICENSE=	BSD3CLAUSE

USES=		python
USE_PYTHON=	autoplist concurrent distutils
NO_ARCH=	yes

.include <bsd.port.pre.mk>

post-patch:
.if ${PYTHON_MAJOR_VER} == 3
	@cd ${WRKSRC} && ${FIND} . -name "*.py" | \
		${XARGS} ${LOCALBASE}/bin/2to3${UNIQUE_SUFFIX} -wn --no-diffs
.endif

.include <bsd.port.post.mk>
