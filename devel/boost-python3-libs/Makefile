# Created by: Shane Ambler FreeBSD@Shaneware.biz
# $FreeBSD$

PORTNAME=	boost-python3-libs
COMMENT=	Framework for interfacing Python and C++

USE_PYTHON=	3.3

OPTIONS_DEFINE=	VERBOSE_BUILD DEBUG OPTIMIZED_CFLAGS
VERBOSE_BUILD_DESC=	Show compiler messages

.include "${.CURDIR}/../boost-all/common.mk"

.include "${.CURDIR}/../boost-all/compiled.mk"

.if ${ARCH} == "sparc64"
CXXFLAGS=	-O0
.endif

MAKE_ENV+=	PYTHON_ROOT="${LOCALBASE}"\
		PYTHON_VERSION="${PYTHON_VERSION}"\
		PYTHON_INCLUDES="${PYTHON_INCLUDEDIR}"\
		PYTHON_LIB_PATH="${PYTHON_LIBDIR}"

LIB_DEPENDS+=	libboost_thread.so:${PORTSDIR}/devel/boost-libs

BUILD_DEPENDS+=	${BJAM}:${PORTSDIR}/devel/boost-jam

do-build:
	@${ECHO_CMD} "using python : " ${PYTHON_VER} " : " ${PYTHON_CMD} " : " ${PYTHON_INCLUDEDIR} ";" >> ${WRKSRC}/tools/build/v2/site-config.jam
# build the library
	@cd ${WRKSRC} && \
		${SETENV} ${MAKE_ENV} ${BJAM} ${BJAM_ARGS} --with-python stage
	@cd ${WRKSRC}/stage/lib && \
		( for l in lib*.so.*; do ${LN} -sf $${l} $${l%.*}; done )

do-install:
	@cd ${WRKSRC}/stage/lib && ${PAX} -rw -p p libboost_python3* ${STAGEDIR}${PREFIX}/lib
# For some reasons BJAM forget about the links
	@cd ${WRKSRC}/stage/ && ${FIND} lib -type l -and -name "*python3*"| ${PAX} -rw -p p ${STAGEDIR}${PREFIX}

post-install:
# display pkg-message
	@${TOUCH} ${PKGMESSAGE}
	@${CAT} ${PKG_MESSAGE_FILE_THREADS} >> ${PKGMESSAGE}
	@${ECHO_CMD} >> ${PKGMESSAGE}
	@${CAT} ${PKG_MESSAGE_FILE_PYTHON} >> ${PKGMESSAGE}
	@${ECHO_CMD} >> ${PKGMESSAGE}
	@${REINPLACE_CMD} \
		-e "s|%%LOCALBASE%%|${STAGEDIR}${LOCALBASE}|g" \
		-e "s|%%PTHREAD_LIBS%%|${PTHREAD_LIBS}|g" \
		-e "s|%%PYTHON_INCLUDEDIR%%|${STAGEDIR}${PYTHON_INCLUDEDIR}|g" \
		-e "s|%%PYTHON_LIBDIR%%|${STAGEDIR}${PYTHON_LIBDIR}|g" \
		-e "s|%%PYTHON_VERSION%%|${STAGEDIR}${PYTHON_VERSION}|g" \
		-e "s|lboost_python|lboost_python3|g" ${PKGMESSAGE}
	@if [ -s ${PKGMESSAGE} ]; then \
		${CAT} ${PKGMESSAGE}; \
	fi

.include <bsd.port.post.mk>
