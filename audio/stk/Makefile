# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	stk
PORTVERSION=	4.5.0
CATEGORIES=	audio
MASTER_SITES=	http://ccrma.stanford.edu/software/stk/release/

MAINTAINER=	FreeBSD@Shaneware.biz
COMMENT=	Synthesis ToolKit for audio signal processing & algorithmic synthesis

LICENSE=	MIT

USES=		gmake
GNU_CONFIGURE=	yes
CONFIGURE_ARGS= --disable-realtime

OPTIONS_DEFINE=		JACK ALSA
OPTIONS_DEFAULT=	JACK ALSA

JACK_CONFIGURE_WITH=	jack
JACK_LIB_DEPENDS=	libjack.so:${PORTSDIR}/audio/jack

ALSA_CONFIGURE_WITH=	alsa
ALSA_LIB_DEPENDS=	libasound.so:${PORTSDIR}/audio/alsa-lib

.include <bsd.port.mk>
