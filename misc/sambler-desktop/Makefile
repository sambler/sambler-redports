# Created by: Shane Ambler <FreeBSD@Shaneware.biz>
# $FreeBSD$

PORTNAME=	sambler-desktop
PORTVERSION=	1
CATEGORIES=	misc
MASTER_SITES=	# Empty
DISTFILES=	# None

MAINTAINER=	me
COMMENT=	LOCAL Metaport for building my software

# general options
NO_BUILD=	yes
#CC=		clang
#CXX=		clang++
#CPP=		clang-cpp
#ARCH=		amd64
#CPUTYPE=	corei7
CFLAGS=		-O3 -msse4.2 -fno-strict-aliasing -pipe -fno-omit-frame-pointer
CXXFLAGS=	${CFLAGS} 
NO_WERROR=
WERROR=
STRIP=
WITH_CTF=1

# version choices
#WITH_NEW_XORG=	yes
#WITH_KMS=	yes
#PERL_VERSION=	5.16.2
PERL_PORT=	perl5.16
#PYTHON_VERSION=	python3.3
#RUBY_DEFAULT_VER=	1.8
WITH_PGSQL_VER=	92
APACHE_VERSION=	22

# global options
WITH_PKGNG=	true
PKGSUFFIX=	.txz
MAKE_JOBS_SAFE=	true
QMAKESPEC=	freebsd-clang
QT4_OPTIONS=	CUPS QGTKSTYLE
KDE4_PREFIX=	/usr/local
PAPERSIZE=	a4
WITH_OPENSSL_PORT=	true
GNUSTEP_WITH_CLANG=	true
OPTIONS_SET=	PGSQL SQLITE JACK IPV6 OPTIMIZED_CFLAGS SIMD MMX SSE SSE2 SSSE3
OPTIONS_UNSET=	MYSQL MSQL NLS JAVA

# Use ccache for building everything
BUILD_DEPENDS=	ccache:${PORTSDIR}/devel/ccache

RUN_DEPENDS=	# Empty this so subsequent RUN_DEPENDS need +=
LIB_DEPENDS=	# Empty this so subsequent LIB_DEPENDS need +=

# archivers
RUN_DEPENDS+=	cabextract:${PORTSDIR}/archivers/cabextract
RUN_DEPENDS+=	file-roller:${PORTSDIR}/archivers/file-roller 
LIB_DEPENDS+=	lz:${PORTSDIR}/archivers/lzlib 
RUN_DEPENDS+=	lzma:${PORTSDIR}/archivers/lzma 
RUN_DEPENDS+=	p7zip :${PORTSDIR}/archivers/p7zip 
RUN_DEPENDS+=	plzip:${PORTSDIR}/archivers/plzip 
RUN_DEPENDS+=	rpm:${PORTSDIR}/archivers/rpm 
RUN_DEPENDS+=	rpm2cpio:${PORTSDIR}/archivers/rpm2cpio 
RUN_DEPENDS+=	gshar:${PORTSDIR}/archivers/sharutils 
RUN_DEPENDS+=	${LOCALBASE}/lib/thunarx-2/thunar-archive-plugin:${PORTSDIR}/archivers/thunar-archive-plugin 
RUN_DEPENDS+=	xarchiver:${PORTSDIR}/archivers/xarchiver 

# audio
RUN_DEPENDS+=	aacgain:${PORTSDIR}/audio/aacgain 
RUN_DEPENDS+=	${LOCALBASE}/lib/ladspa/aw:${PORTSDIR}/audio/alienwah 
RUN_DEPENDS+=	alsactl:${PORTSDIR}/audio/alsa-utils 
RUN_DEPENDS+=	${LOCALBASE}/lib/ladspa/ambisonic0:${PORTSDIR}/audio/amb-plugins 
RUN_DEPENDS+=	ardour2:${PORTSDIR}/audio/ardour 
RUN_DEPENDS+=	artswrapper:${PORTSDIR}/audio/artswrapper 
RUN_DEPENDS+=	asunder:${PORTSDIR}/audio/asunder 
RUN_DEPENDS+=	audacity:${PORTSDIR}/audio/audacity 
RUN_DEPENDS+=	${LOCALBASE}/lib/ladspa/autotalent:${PORTSDIR}/audio/autotalent 
RUN_DEPENDS+=	${LOCALBASE}/lib/ladspa/adsr_1653:${PORTSDIR}/audio/blop 
RUN_DEPENDS+=	bristol:${PORTSDIR}/audio/bristol 
RUN_DEPENDS+=	calfjackhost:${PORTSDIR}/audio/calf 
RUN_DEPENDS+=	gmidimonitor:${PORTSDIR}/audio/gmidimonitor 
RUN_DEPENDS+=	gtkguitune:${PORTSDIR}/audio/gtkguitune 
RUN_DEPENDS+=	${LOCALBASE}/lib/gstreamer-0.10/libgstfaac.so:${PORTSDIR}/audio/gstreamer-plugins-faac 
RUN_DEPENDS+=	${LOCALBASE}/lib/gstreamer-0.10/libgstlame.so:${PORTSDIR}/audio/gstreamer-plugins-lame 
RUN_DEPENDS+=	${LOCALBASE}/lib/dssi/hexter:${PORTSDIR}/audio/hexter 
RUN_DEPENDS+=	hydrogen:${PORTSDIR}/audio/hydrogen-devel 
RUN_DEPENDS+=	jack-keyboard:${PORTSDIR}/audio/jack-keyboard 
RUN_DEPENDS+=	jack-rack:${PORTSDIR}/audio/jack-rack 
RUN_DEPENDS+=	jack_mixer:${PORTSDIR}/audio/jack_mixer 
RUN_DEPENDS+=	jack_umidi:${PORTSDIR}/audio/jack_umidi 
RUN_DEPENDS+=	smfsh:${PORTSDIR}/audio/libsmf 
LIB_DEPENDS+=	umidi20:${PORTSDIR}/audio/libumidi 
RUN_DEPENDS+=	lv2ls:${PORTSDIR}/audio/lilv 
RUN_DEPENDS+=	lmms:${PORTSDIR}/audio/lmms-sambler 
RUN_DEPENDS+=	mixmos:${PORTSDIR}/audio/mixmos 
RUN_DEPENDS+=	mp3gain:${PORTSDIR}/audio/mp3gain 
RUN_DEPENDS+=	mscore:${PORTSDIR}/audio/musescore 
RUN_DEPENDS+=	patchage:${PORTSDIR}/audio/patchage 
RUN_DEPENDS+=	mutagen-inspect:${PORTSDIR}/audio/py-mutagen 
RUN_DEPENDS+=	qjackctl:${PORTSDIR}/audio/qjackctl 
RUN_DEPENDS+=	rosegarden:${PORTSDIR}/audio/rosegarden 
RUN_DEPENDS+=	rubberband:${PORTSDIR}/audio/rubberband 
RUN_DEPENDS+=	lv2_inspect:${PORTSDIR}/audio/slv2 
LIB_DEPENDS+=	suil-0:${PORTSDIR}/audio/suil 
RUN_DEPENDS+=	${LOCALBASE}/lib/thunarx-2/thunar-media-tags-plugin:${PORTSDIR}/audio/thunar-media-tags-plugin 
RUN_DEPENDS+=	ttaenc:${PORTSDIR}/audio/tta 
RUN_DEPENDS+=	vorbisgain:${PORTSDIR}/audio/vorbisgain 
RUN_DEPENDS+=	xmms2:${PORTSDIR}/audio/xmms2 
RUN_DEPENDS+=	${LOCALBASE}/lib/dssi/xsynth-dssi:${PORTSDIR}/audio/xsynth-dssi 
RUN_DEPENDS+=	zynaddsubfx:${PORTSDIR}/audio/zynaddsubfx 

# cad
RUN_DEPENDS+=	meshlab:${PORTSDIR}/cad/meshlab 

# comms
RUN_DEPENDS+=	ideviceinfo:${PORTSDIR}/comms/libimobiledevice 

# database
RUN_DEPENDS+=	db_stat-4.6:${PORTSDIR}/databases/db46 
RUN_DEPENDS+=	${LOCALBASE}/lib/dbd/libdbdpgsql:${PORTSDIR}/databases/libdbi-drivers 
RUN_DEPENDS+=	${LOCALBASE}/lib/libgda-4.0/providers/libgda-postgres.so:${PORTSDIR}/databases/libgda4-postgresql 
RUN_DEPENDS+=	gdamm-4.0:${PORTSDIR}/databases/libgdamm 
RUN_DEPENDS+=	pgadmin3:${PORTSDIR}/databases/pgadmin3 
RUN_DEPENDS+=	pg_upgrade:${PORTSDIR}/databases/postgresql92-contrib 
RUN_DEPENDS+=	${LOCALBASE}/share/doc/postgresql/release-92/index.html:${PORTSDIR}/databases/postgresql92-docs 
RUN_DEPENDS+=	${LOCALBASE}/share/postgresql/extension/plperl.control:${PORTSDIR}/databases/postgresql92-plperl 
RUN_DEPENDS+=	${LOCALBASE}/lib/postgresql/plpython2:${PORTSDIR}/databases/postgresql92-plpython 
RUN_DEPENDS+=	psql:${PORTSDIR}/databases/postgresql92-client
RUN_DEPENDS+=	postgres:${PORTSDIR}/databases/postgresql92-server

# deskutils
RUN_DEPENDS+=	alacarte:${PORTSDIR}/deskutils/alacarte 
RUN_DEPENDS+=	cdcat:${PORTSDIR}/deskutils/cdcat 
RUN_DEPENDS+=	FBReader:${PORTSDIR}/deskutils/fbreader 
RUN_DEPENDS+=	gnochm:${PORTSDIR}/deskutils/gnochm 
RUN_DEPENDS+=	korganizer:${PORTSDIR}/deskutils/kdepim4 
RUN_DEPENDS+=	planner:${PORTSDIR}/deskutils/planner 
RUN_DEPENDS+=	${LOCALBASE}/lib/xfce4/xfce4/panel-plugins/xfce4-generic-slider-plugin:${PORTSDIR}/deskutils/xfce4-generic-slider 
RUN_DEPENDS+=	xfce4-notes:${PORTSDIR}/deskutils/xfce4-notes-plugin 
RUN_DEPENDS+=	notification-settings:${PORTSDIR}/deskutils/xfce4-notification-daemon 
RUN_DEPENDS+=	${LOCALBASE}/libexec/xfce4/panel-plugins/xfce4-xkb-plugin:${PORTSDIR}/deskutils/xfce4-xkb-plugin 

# devel
RUN_DEPENDS+=	autogen:${PORTSDIR}/devel/autogen 
RUN_DEPENDS+=	automoc4:${PORTSDIR}/devel/automoc4 
RUN_DEPENDS+=	bison:${PORTSDIR}/devel/bison 
RUN_DEPENDS+=	${LOCALBASE}/share/doc/boost/index.html:${PORTSDIR}/devel/boost-docs 
RUN_DEPENDS+=	bjam:${PORTSDIR}/devel/boost-jam 
LIB_DEPENDS+=	boost_python3:${PORTSDIR}/devel/boost-python3-libs 
RUN_DEPENDS+=	buildtool:${PORTSDIR}/devel/buildtool 
RUN_DEPENDS+=	${LOCALBASE}/share/doc/buildtool-doc/index.html:${PORTSDIR}/devel/buildtool-doc 
RUN_DEPENDS+=	ccache:${PORTSDIR}/devel/ccache 
RUN_DEPENDS+=	chrpath:${PORTSDIR}/devel/chrpath 
RUN_DEPENDS+=	cmake-gui:${PORTSDIR}/devel/cmake-gui 
RUN_DEPENDS+=	cppunit-config:${PORTSDIR}/devel/cppunit 
RUN_DEPENDS+=	cscope:${PORTSDIR}/devel/cscope 
RUN_DEPENDS+=	exctags:${PORTSDIR}/devel/ctags 
RUN_DEPENDS+=	dbus-qt-1:${PORTSDIR}/devel/dbus-qt3 
RUN_DEPENDS+=	dcmconv:${PORTSDIR}/devel/dcmtk 
RUN_DEPENDS+=	ddd:${PORTSDIR}/devel/ddd 
RUN_DEPENDS+=	as86:${PORTSDIR}/devel/dev86 
RUN_DEPENDS+=	devhelp:${PORTSDIR}/devel/devhelp 
RUN_DEPENDS+=	dmake:${PORTSDIR}/devel/dmake 
RUN_DEPENDS+=	dmalloc:${PORTSDIR}/devel/dmalloc 
RUN_DEPENDS+=	doxygen:${PORTSDIR}/devel/doxygen 
RUN_DEPENDS+=	OpenCL:${PORTSDIR}/devel/freeocl 
RUN_DEPENDS+=	gdb76:${PORTSDIR}/devel/gdb 
RUN_DEPENDS+=	gdb66:${PORTSDIR}/devel/gdb66 
RUN_DEPENDS+=	${LOCALBASE}/lib/geany/addons.so:${PORTSDIR}/devel/geany-plugins 
RUN_DEPENDS+=	gitg:${PORTSDIR}/devel/gitg 
RUN_DEPENDS+=	${LOCALBASE}/lib/gnome-js/lang.js:${PORTSDIR}/devel/gnome-js-common 
RUN_DEPENDS+=	${LOCALBASE}/GNUstep/GNUstep.conf:${PORTSDIR}/devel/gnustep-make 
RUN_DEPENDS+=	pprof:${PORTSDIR}/devel/google-perftools 
RUN_DEPENDS+=	gperf:${PORTSDIR}/devel/gperf 
RUN_DEPENDS+=	gps:${PORTSDIR}/devel/gps 
RUN_DEPENDS+=	gwenhywfar-config:${PORTSDIR}/devel/gwenhywfar 
RUN_DEPENDS+=	imake:${PORTSDIR}/devel/imake 
RUN_DEPENDS+=	jsmin:${PORTSDIR}/devel/jsmin 
RUN_DEPENDS+=	checkmk:${PORTSDIR}/devel/libcheck 
LIB_DEPENDS+=	config:${PORTSDIR}/devel/libconfig 
LIB_DEPENDS+=	galago:${PORTSDIR}/devel/libgalago 
LIB_DEPENDS+=	inotify :${PORTSDIR}/devel/libinotify 
LIB_DEPENDS+=	kgapi:${PORTSDIR}/devel/libkgapi 
LIB_DEPENDS+=	kolab:${PORTSDIR}/devel/libkolab 
LIB_DEPENDS+=	owfat:${PORTSDIR}/devel/libowfat 
LIB_DEPENDS+=	slang:${PORTSDIR}/devel/libslang2 
LIB_DEPENDS+=	thai:${PORTSDIR}/devel/libthai 
RUN_DEPENDS+=	hg:${PORTSDIR}/devel/mercurial 
RUN_DEPENDS+=	nasm:${PORTSDIR}/devel/nasm 
RUN_DEPENDS+=	ode-config:${PORTSDIR}/devel/ode 
RUN_DEPENDS+=	puic4:${PORTSDIR}/devel/p5-perlqt 
RUN_DEPENDS+=	gpatch:${PORTSDIR}/devel/patch 
RUN_DEPENDS+=	premake:${PORTSDIR}/devel/premake 
RUN_DEPENDS+=	${PYTHON_SITELIBDIR}/lxml/__init__.py:${PORTSDIR}/devel/py-lxml 
RUN_DEPENDS+=	pykdeuic4:${PORTSDIR}/devel/py-pykdeuic4 
RUN_DEPENDS+=	pyuic4:${PORTSDIR}/devel/py-qt4 
RUN_DEPENDS+=	twistd:${PORTSDIR}/devel/py-twistedCore 
RUN_DEPENDS+=	qgit:${PORTSDIR}/devel/qgit 
RUN_DEPENDS+=	qmake:${PORTSDIR}/devel/qmake 
RUN_DEPENDS+=	qsvn:${PORTSDIR}/devel/qsvn 
RUN_DEPENDS+=	assistant_adp:${PORTSDIR}/devel/qt4-assistant-adp 
LIB_DEPENDS+=	QtSolutions_SingleApplication-head:${PORTSDIR}/devel/qt4-qtsolutions-singleapplication 
LIB_DEPENDS+=	QtSolutions_SOAP-head:${PORTSDIR}/devel/qt4-qtsolutions-soap 
RUN_DEPENDS+=	uic3:${PORTSDIR}/devel/qt4-uic3 
RUN_DEPENDS+=	qtcreator:${PORTSDIR}/devel/qtcreator 
RUN_DEPENDS+=	rapidsvn:${PORTSDIR}/devel/rapidsvn 
RUN_DEPENDS+=	rake:${PORTSDIR}/devel/rubygem-rake 
RUN_DEPENDS+=	scons:${PORTSDIR}/devel/scons 
RUN_DEPENDS+=	${LOCALBASE}/lib/thunarx-2/thunar-vcs-plugin:${PORTSDIR}/devel/thunar-vcs-plugin 
RUN_DEPENDS+=	tmake:${PORTSDIR}/devel/tmake 
RUN_DEPENDS+=	ucpp:${PORTSDIR}/devel/ucpp 
RUN_DEPENDS+=	valgrind:${PORTSDIR}/devel/valgrind 
RUN_DEPENDS+=	${LOCALBASE}/etc/rc.d/viewvc:${PORTSDIR}/devel/viewvc 
RUN_DEPENDS+=	xdt-autogen:${PORTSDIR}/devel/xfce4-dev-tools 
RUN_DEPENDS+=	${LOCALBASE}/share/aclocal/xorg-macros.m4:${PORTSDIR}/devel/xorg-macros 
RUN_DEPENDS+=	xxgdb:${PORTSDIR}/devel/xxgdb 
RUN_DEPENDS+=	yasm:${PORTSDIR}/devel/yasm 
RUN_DEPENDS+=	zzcat:${PORTSDIR}/devel/zziplib 

# dns
RUN_DEPENDS+=	adnshost:${PORTSDIR}/dns/adns 
RUN_DEPENDS+=	${PYTHON_SITELIBDIR}/dns/__init__.py:${PORTSDIR}/dns/py-dnspython 

# editors
RUN_DEPENDS+=	${LOCALBASE}/lib/gedit-2/plugins/drawspaces.gedit-plugin:${PORTSDIR}/editors/gedit-plugins 
RUN_DEPENDS+=	leafpad:${PORTSDIR}/editors/leafpad 
RUN_DEPENDS+=	nano:${PORTSDIR}/editors/nano 
RUN_DEPENDS+=	SciTE:${PORTSDIR}/editors/scite 
RUN_DEPENDS+=	Ted:${PORTSDIR}/editors/ted 
RUN_DEPENDS+=	texmakerx:${PORTSDIR}/editors/texmakerx 

# emulators
RUN_DEPENDS+=	mtools:${PORTSDIR}/emulators/mtools 

# finance
RUN_DEPENDS+=	gnucash:${PORTSDIR}/finance/gnucash 
RUN_DEPENDS+=	${LOCALBASE}/ledger-smb/bin/mozilla/admin.pl:${PORTSDIR}/finance/ledgersmb 

# ftp
RUN_DEPENDS+=	filezilla:${PORTSDIR}/ftp/filezilla 

# games
RUN_DEPENDS+=	tuxtype:${PORTSDIR}/games/tuxtype
RUN_DEPENDS+=	mahjongg:${PORTSDIR}/games/gnome-games 

# graphics
RUN_DEPENDS+=	GraphicsMagick-config:${PORTSDIR}/graphics/GraphicsMagick 
RUN_DEPENDS+=	blender:${PORTSDIR}/graphics/blender 
RUN_DEPENDS+=	blender-249:${PORTSDIR}/graphics/blender-249 
RUN_DEPENDS+=	blender-262:${PORTSDIR}/graphics/blender-262 
RUN_DEPENDS+=	blender-263:${PORTSDIR}/graphics/blender-263 
RUN_DEPENDS+=	blender-264:${PORTSDIR}/graphics/blender-264 
RUN_DEPENDS+=	blender-265:${PORTSDIR}/graphics/blender-265 
RUN_DEPENDS+=	blender-266:${PORTSDIR}/graphics/blender-266 
RUN_DEPENDS+=	blender-267:${PORTSDIR}/graphics/blender-267 
RUN_DEPENDS+=	blender-sambler:${PORTSDIR}/graphics/blender-sambler 
RUN_DEPENDS+=	cbrpager:${PORTSDIR}/graphics/cbrpager 
RUN_DEPENDS+=	cbview:${PORTSDIR}/graphics/cbview 
RUN_DEPENDS+=	comix:${PORTSDIR}/graphics/comix 
RUN_DEPENDS+=	djview4:${PORTSDIR}/graphics/djview4 
RUN_DEPENDS+=	enblend:${PORTSDIR}/graphics/enblend 
RUN_DEPENDS+=	epdfview:${PORTSDIR}/graphics/epdfview 
RUN_DEPENDS+=	${LOCALBASE}/lib/frei0r-1/RGB.so:${PORTSDIR}/graphics/frei0r 
RUN_DEPENDS+=	${LOCALBASE}/share/gimp/help/en/index.html:${PORTSDIR}/graphics/gimp-help 
RUN_DEPENDS+=	${LOCALBASE}/libexec/gimp/2.2/plug-ins/resynthesizer:${PORTSDIR}/graphics/gimp-resynthesizer 
LIB_DEPENDS+=	goom2:${PORTSDIR}/graphics/goom 
RUN_DEPENDS+=	gr2fonttest:${PORTSDIR}/graphics/graphite2 
RUN_DEPENDS+=	inkscape:${PORTSDIR}/graphics/inkscape 
RUN_DEPENDS+=	kiconedit:${PORTSDIR}/graphics/kiconedit 
LIB_DEPENDS+=	lensfun:${PORTSDIR}/graphics/lensfun 
LIB_DEPENDS+=	luxrays:${PORTSDIR}/graphics/luxrays 
RUN_DEPENDS+=	luxrender:${PORTSDIR}/graphics/luxrender 
RUN_DEPENDS+=	cuberender:${PORTSDIR}/graphics/mesa-demos 
RUN_DEPENDS+=	mypaint:${PORTSDIR}/graphics/mypaint 
RUN_DEPENDS+=	ociolutimage:${PORTSDIR}/graphics/opencolorio-tools 
RUN_DEPENDS+=	panomatic:${PORTSDIR}/graphics/panomatic 
LIB_DEPENDS+=	pngwriter:${PORTSDIR}/graphics/pngwriter 
RUN_DEPENDS+=	povray:${PORTSDIR}/graphics/povray-meta 
RUN_DEPENDS+=	${PYTHON_SITELIBDIR}/OpenImageIO.so:${PORTSDIR}/graphics/py-openimageio 
LIB_DEPENDS+=	QtGTL:${PORTSDIR}/graphics/qtgtl 
RUN_DEPENDS+=	iccDumpProfile:${PORTSDIR}/graphics/sampleicc 
RUN_DEPENDS+=	xscanimage:${PORTSDIR}/graphics/sane-frontends 
RUN_DEPENDS+=	sswf:${PORTSDIR}/graphics/sswf 
RUN_DEPENDS+=	tesseract:${PORTSDIR}/graphics/tesseract 
RUN_DEPENDS+=	${LOCALBASE}/share/WindowMaker/Icons/Book.xpm:${PORTSDIR}/graphics/wmicons 
RUN_DEPENDS+=	xsane:${PORTSDIR}/graphics/xsane 
RUN_DEPENDS+=	yafaray-xml:${PORTSDIR}/graphics/yafaray 

# irc
RUN_DEPENDS+=	quassel:${PORTSDIR}/irc/quassel 

# lang
#RUN_DEPENDS+=	clang:${PORTSDIR}/lang/clang 
RUN_DEPENDS+=	clang:${PORTSDIR}/lang/clang-devel 
RUN_DEPENDS+=	clang33:${PORTSDIR}/lang/clang33 
RUN_DEPENDS+=	gawk:${PORTSDIR}/lang/gawk 
RUN_DEPENDS+=	${LOCALBASE}/share/doc/libstdc++_stldoc_4.2.2/stldoc/index.html:${PORTSDIR}/lang/libstdc++_stldoc_4.2.2 
RUN_DEPENDS+=	${PORTSDIR}/lang/php5-extensions 

# mail
RUN_DEPENDS+=	fetchmail:${PORTSDIR}/mail/fetchmail 
RUN_DEPENDS+=	${LOCALBASE}/lib/thunderbird/dictionaries/en-AU.dic:${PORTSDIR}/mail/thunderbird-dictionaries 
RUN_DEPENDS+=	${LOCALBASE}/libexec/xfce4/panel-plugins/xfce4-mailwatch-plugin:${PORTSDIR}/mail/xfce4-mailwatch-plugin 

# math
LIB_DEPENDS+=	arpack:${PORTSDIR}/math/arpack 
LIB_DEPENDS+=	djbfft:${PORTSDIR}/math/djbfft 
RUN_DEPENDS+=	${LOCALBASE}/include/eigen2/Eigen/Array:${PORTSDIR}/math/eigen2 
RUN_DEPENDS+=	${LOCALBASE}/include/gmm/gmm.h:${PORTSDIR}/math/gmm++ 
RUN_DEPENDS+=	gnumeric:${PORTSDIR}/math/gnumeric 
RUN_DEPENDS+=	qalc:${PORTSDIR}/math/libqalculate 
RUN_DEPENDS+=	lp_solve:${PORTSDIR}/math/lp_solve 
RUN_DEPENDS+=	f2py32:${PORTSDIR}/math/py-numpy32 
RUN_DEPENDS+=	f2py33:${PORTSDIR}/math/py-numpy33 
RUN_DEPENDS+=	qhull:${PORTSDIR}/math/qhull5 
LIB_DEPENDS+=	qrupdate:${PORTSDIR}/math/qrupdate 

# misc
RUN_DEPENDS+=	${LOCALBASE}/share/games/fortune/ferengi_rules_of_acquisition:${PORTSDIR}/misc/fortune-mod-ferengi_rules_of_acquisition 
RUN_DEPENDS+=	${LOCALBASE}/share/games/fortune/futurama:${PORTSDIR}/misc/fortune-mod-futurama 
RUN_DEPENDS+=	${LOCALBASE}/share/doc/freebsd/en_US.ISO8859-1/books/handbook/index.html:${PORTSDIR}/misc/freebsd-doc-en 
RUN_DEPENDS+=	${LOCALBASE}/share/gnome/help/gdp-handbook/C/manuals.xml:${PORTSDIR}/misc/gnome-devel-docs 
RUN_DEPENDS+=	help2man:${PORTSDIR}/misc/help2man 
RUN_DEPENDS+=	qtconfig-qt4:${PORTSDIR}/misc/qt4-qtconfig 
RUN_DEPENDS+=	rtfm:${PORTSDIR}/misc/rtfm 
RUN_DEPENDS+=	shc:${PORTSDIR}/misc/shc 
RUN_DEPENDS+=	${LOCALBASE}/lib/xfce4/panel/plugins/libweather.so:${PORTSDIR}/misc/xfce4-weather-plugin 
RUN_DEPENDS+=	${LOCALBASE}/share/themes/Xfce/xfwm4/themerc:${PORTSDIR}/misc/xfce4-wm-themes 

# multimedia
RUN_DEPENDS+=	audacious:${PORTSDIR}/multimedia/audacious 
RUN_DEPENDS+=	${LOCALBASE}/lib/audacious/Effect/resample.so:${PORTSDIR}/multimedia/audacious-plugins 
RUN_DEPENDS+=	cclive:${PORTSDIR}/multimedia/cclive 
RUN_DEPENDS+=	clipgrab:${PORTSDIR}/multimedia/clipgrab 
RUN_DEPENDS+=	clive:${PORTSDIR}/multimedia/clive 
RUN_DEPENDS+=	devede:${PORTSDIR}/multimedia/devede 
RUN_DEPENDS+=	dvdrip:${PORTSDIR}/multimedia/dvdrip 
RUN_DEPENDS+=	ffmpeg2theora:${PORTSDIR}/multimedia/ffmpeg2theora 
RUN_DEPENDS+=	gcap:${PORTSDIR}/multimedia/gcap 
RUN_DEPENDS+=	grake:${PORTSDIR}/multimedia/grake 
LIB_DEPENDS+=	gstreamermm-0.10:${PORTSDIR}/multimedia/gstreamermm 
RUN_DEPENDS+=	gtk-recordMyDesktop:${PORTSDIR}/multimedia/gtk-recordmydesktop 
RUN_DEPENDS+=	lsdvd:${PORTSDIR}/multimedia/lsdvd 
RUN_DEPENDS+=	mediainfo:${PORTSDIR}/multimedia/mediainfo 
RUN_DEPENDS+=	minitube:${PORTSDIR}/multimedia/minitube 
RUN_DEPENDS+=	mplayer:${PORTSDIR}/multimedia/mplayer2 
RUN_DEPENDS+=	${LOCALBASE}/lib/kde4/plugins/phonon_backend/phonon_vlc.so:${PORTSDIR}/multimedia/phonon-vlc 
RUN_DEPENDS+=	pitivi:${PORTSDIR}/multimedia/pitivi 
RUN_DEPENDS+=	umph:${PORTSDIR}/multimedia/umph 
RUN_DEPENDS+=	${LOCALBASE}/include/linux/videodev.h:${PORTSDIR}/multimedia/v4l_compat 
RUN_DEPENDS+=	vamps:${PORTSDIR}/multimedia/vamps 
RUN_DEPENDS+=	xfmedia:${PORTSDIR}/multimedia/xfce4-media 
RUN_DEPENDS+=	parole:${PORTSDIR}/multimedia/xfce4-parole 
RUN_DEPENDS+=	${LOCALBASE}/libexec/xfce4/panel-plugins/xfce4-xmms-plugin:${PORTSDIR}/multimedia/xfce4-xmms-plugin 
RUN_DEPENDS+=	xine:${PORTSDIR}/multimedia/xine 

# net-im
RUN_DEPENDS+=	pidgin:${PORTSDIR}/net-im/pidgin 
LIB_DEPENDS+=	gadu:${PORTSDIR}/polish/libgadu 

# net
RUN_DEPENDS+=	cvsup:${PORTSDIR}/net/cvsup-without-gui 
LIB_DEPENDS+=	gupnp-1.0:${PORTSDIR}/net/gupnp 
RUN_DEPENDS+=	liferea:${PORTSDIR}/net/liferea 
RUN_DEPENDS+=	linphonec:${PORTSDIR}/net/linphone-base 
RUN_DEPENDS+=	openRTSP:${PORTSDIR}/net/liveMedia 
RUN_DEPENDS+=	slptool:${PORTSDIR}/net/openslp 
RUN_DEPENDS+=	rdesktop:${PORTSDIR}/net/rdesktop 
RUN_DEPENDS+=	vncviewer:${PORTSDIR}/net/tightvnc 
RUN_DEPENDS+=	vino-passwd:${PORTSDIR}/net/vino 

# ports-mgmt
RUN_DEPENDS+=	dialog4ports:${PORTSDIR}/ports-mgmt/dialog4ports 
RUN_DEPENDS+=	fbsdmon:${PORTSDIR}/ports-mgmt/fbsdmon 
RUN_DEPENDS+=	pkg:${PORTSDIR}/ports-mgmt/pkg 
RUN_DEPENDS+=	portlint:${PORTSDIR}/ports-mgmt/portlint 
RUN_DEPENDS+=	portmaster:${PORTSDIR}/ports-mgmt/portmaster 
RUN_DEPENDS+=	${LOCALBASE}/tinderbox/scripts/tc:${PORTSDIR}/ports-mgmt/tinderbox 

# print
RUN_DEPENDS+=	lpr:${PORTSDIR}/print/cups-base 
RUN_DEPENDS+=	lout:${PORTSDIR}/print/lout 
RUN_DEPENDS+=	${PYTHON_SITELIBDIR}/cups.so:${PORTSDIR}/print/py-cups 
RUN_DEPENDS+=	scribus:${PORTSDIR}/print/scribus 
RUN_DEPENDS+=	info:${PORTSDIR}/print/texinfo 

# security
RUN_DEPENDS+=	apg:${PORTSDIR}/security/apg 
RUN_DEPENDS+=	clamav-config:${PORTSDIR}/security/clamav 
RUN_DEPENDS+=	denyhosts.py:${PORTSDIR}/security/denyhosts 
RUN_DEPENDS+=	dirmngr:${PORTSDIR}/security/dirmngr 
RUN_DEPENDS+=	krb5-config:${PORTSDIR}/security/heimdal 
RUN_DEPENDS+=	keychain:${PORTSDIR}/security/keychain 
RUN_DEPENDS+=	otr_parse:${PORTSDIR}/security/libotr 
LIB_DEPENDS+=	ssh2:${PORTSDIR}/security/libssh 
RUN_DEPENDS+=	ssh-askpass:${PORTSDIR}/security/openssh-askpass 
RUN_DEPENDS+=	pgp:${PORTSDIR}/security/pgp 
RUN_DEPENDS+=	pinentry:${PORTSDIR}/security/pinentry 
RUN_DEPENDS+=	pinentry-gtk-2:${PORTSDIR}/security/pinentry-gtk2 
RUN_DEPENDS+=	pinentry-qt4:${PORTSDIR}/security/pinentry-qt4 
RUN_DEPENDS+=	${LOCALBASE}/lib/qt4/plugins/crypto/libqca-ossl.so:${PORTSDIR}/security/qca-ossl 
RUN_DEPENDS+=	rkhunter:${PORTSDIR}/security/rkhunter 
RUN_DEPENDS+=	seahorse-tool:${PORTSDIR}/security/seahorse-plugins 
RUN_DEPENDS+=	zenmap:${PORTSDIR}/security/zenmap 

# shells
RUN_DEPENDS+=	psh:${PORTSDIR}/shells/psh 
RUN_DEPENDS+=	zsh:${PORTSDIR}/shells/zsh 

# sysutils
RUN_DEPENDS+=	procsystime:${PORTSDIR}/sysutils/DTraceToolkit 
RUN_DEPENDS+=	automount2amd:${PORTSDIR}/sysutils/am-utils 
RUN_DEPENDS+=	anacron:${PORTSDIR}/sysutils/anacron 
RUN_DEPENDS+=	apcupsd:${PORTSDIR}/sysutils/apcupsd 
RUN_DEPENDS+=	ataidle:${PORTSDIR}/sysutils/ataidle 
RUN_DEPENDS+=	automounter:${PORTSDIR}/sysutils/automounter 
RUN_DEPENDS+=	rcstatus:${PORTSDIR}/sysutils/bsdadminscripts 
RUN_DEPENDS+=	${LOCALBASE}/etc/rc.d/bsdstats:${PORTSDIR}/sysutils/bsdstats 
RUN_DEPENDS+=	conky:${PORTSDIR}/sysutils/conky 
RUN_DEPENDS+=	gcat:${PORTSDIR}/sysutils/coreutils 
RUN_DEPENDS+=	cpdup:${PORTSDIR}/sysutils/cpdup 
RUN_DEPENDS+=	ddrescue:${PORTSDIR}/sysutils/ddrescue 
RUN_DEPENDS+=	e2fsck:${PORTSDIR}/sysutils/e2fsprogs 
RUN_DEPENDS+=	gdisk:${PORTSDIR}/sysutils/gdisk 
RUN_DEPENDS+=	gkrellm:${PORTSDIR}/sysutils/gkrellm 
RUN_DEPENDS+=	gksu:${PORTSDIR}/sysutils/gksu 
RUN_DEPENDS+=	network-admin:${PORTSDIR}/sysutils/gnome-system-tools 
RUN_DEPENDS+=	healthd:${PORTSDIR}/sysutils/healthd 
RUN_DEPENDS+=	jailme:${PORTSDIR}/sysutils/jailme 
RUN_DEPENDS+=	jails:${PORTSDIR}/sysutils/jailutils 
RUN_DEPENDS+=	k3b:${PORTSDIR}/sysutils/k3b-kde4 
RUN_DEPENDS+=	ksystemlog:${PORTSDIR}/sysutils/kdeadmin4 
RUN_DEPENDS+=	ksysguardd:${PORTSDIR}/sysutils/ksysguardd 
RUN_DEPENDS+=	lineakd:${PORTSDIR}/sysutils/lineakd 
RUN_DEPENDS+=	lmmon:${PORTSDIR}/sysutils/lmmon 
RUN_DEPENDS+=	logwatch.pl:${PORTSDIR}/sysutils/logwatch 
RUN_DEPENDS+=	luckybackup:${PORTSDIR}/sysutils/luckybackup 
RUN_DEPENDS+=	ntfslabel:${PORTSDIR}/sysutils/ntfsprogs 
RUN_DEPENDS+=	nvclock:${PORTSDIR}/sysutils/nvclock 
RUN_DEPENDS+=	lspci:${PORTSDIR}/sysutils/pciutils 
RUN_DEPENDS+=	quicksynergy:${PORTSDIR}/sysutils/quicksynergy 
RUN_DEPENDS+=	screen:${PORTSDIR}/sysutils/screen 
RUN_DEPENDS+=	${LOCALBASE}/libexec/sensors-applet:${PORTSDIR}/sysutils/sensors-applet 
RUN_DEPENDS+=	sg_get_config:${PORTSDIR}/sysutils/sg3_utils 
RUN_DEPENDS+=	synergys:${PORTSDIR}/sysutils/synergy 
RUN_DEPENDS+=	testdisk:${PORTSDIR}/sysutils/testdisk 
RUN_DEPENDS+=	vobcopy:${PORTSDIR}/sysutils/vobcopy 
RUN_DEPENDS+=	volmand:${PORTSDIR}/sysutils/volman 
RUN_DEPENDS+=	${LOCALBASE}/etc/rc.d/webmin:${PORTSDIR}/sysutils/webmin 
RUN_DEPENDS+=	${LOCALBASE}/lib/xfce4/panel/plugins/libcpugraph.so:${PORTSDIR}/sysutils/xfce4-cpugraph-plugin 
RUN_DEPENDS+=	${LOCALBASE}/lib/xfce4/panel/plugins/libfsguard.so:${PORTSDIR}/sysutils/xfce4-fsguard-plugin 
RUN_DEPENDS+=	${LOCALBASE}/lib/xfce4/panel/plugins/libgenmon.so:${PORTSDIR}/sysutils/xfce4-genmon-plugin 
RUN_DEPENDS+=	${LOCALBASE}/lib/xfce4/panel-plugins/libminicmd.so:${PORTSDIR}/sysutils/xfce4-minicmd-plugin 
RUN_DEPENDS+=	${LOCALBASE}/libexec/xfce4/panel-plugins/xfce4-netload-plugin:${PORTSDIR}/sysutils/xfce4-netload-plugin 
RUN_DEPENDS+=	${LOCALBASE}/lib/xfce4/panel/plugins/libsystemload.so:${PORTSDIR}/sysutils/xfce4-systemload-plugin 
RUN_DEPENDS+=	${LOCALBASE}/libexec/xfce4/panel-plugins/xfce4-wavelan-plugin:${PORTSDIR}/sysutils/xfce4-wavelan-plugin 
RUN_DEPENDS+=	xfsm:${PORTSDIR}/sysutils/xfsm 
RUN_DEPENDS+=	xmbmon:${PORTSDIR}/sysutils/xmbmon 
RUN_DEPENDS+=	xosview:${PORTSDIR}/sysutils/xosview 
RUN_DEPENDS+=	zfs-stats:${PORTSDIR}/sysutils/zfs-stats 

# textproc
RUN_DEPENDS+=	clit:${PORTSDIR}/textproc/clit 
RUN_DEPENDS+=	docbook-to-man:${PORTSDIR}/textproc/docbook-to-man 
RUN_DEPENDS+=	docbook2html:${PORTSDIR}/textproc/docbook-utils 
RUN_DEPENDS+=	${LOCALBASE}/share/sgml/docbook/4.5/docbookx.dtd:${PORTSDIR}/textproc/docproj-nojadetex 
RUN_DEPENDS+=	flex:${PORTSDIR}/textproc/flex 
RUN_DEPENDS+=	${LOCALBASE}/lib/gnome-spell/libgnome-spell-component.so:${PORTSDIR}/textproc/gnome-spell 
RUN_DEPENDS+=	gsed:${PORTSDIR}/textproc/gsed 
RUN_DEPENDS+=	gtkdoc-scan:${PORTSDIR}/textproc/gtk-doc 
RUN_DEPENDS+=	${LOCALBASE}/share/sgml/html/4.01/strict.dtd:${PORTSDIR}/textproc/html 
RUN_DEPENDS+=	createfpx:${PORTSDIR}/textproc/libexttextcat 
RUN_DEPENDS+=	vss2text:${PORTSDIR}/textproc/libvisio 
RUN_DEPENDS+=	wps2text:${PORTSDIR}/textproc/libwps 
RUN_DEPENDS+=	${LOCALBASE}/share/sgml/linuxdoc/linuxdoc.dec:${PORTSDIR}/textproc/linuxdoc 
RUN_DEPENDS+=	man2html:${PORTSDIR}/textproc/man2html 
RUN_DEPENDS+=	meld:${PORTSDIR}/textproc/meld 
RUN_DEPENDS+=	th_gen_idx.pl:${PORTSDIR}/textproc/mythes 
RUN_DEPENDS+=	${PYTHON_SITELIBDIR}/rdflib/__init__.py:${PORTSDIR}/textproc/py-rdflib 
RUN_DEPENDS+=	sphinx-build:${PORTSDIR}/textproc/py-sphinx 
RUN_DEPENDS+=	rtfreader:${PORTSDIR}/textproc/rtfreader 
RUN_DEPENDS+=	deplate:${PORTSDIR}/textproc/ruby-deplate 
RUN_DEPENDS+=	sigil:${PORTSDIR}/textproc/sigil 
RUN_DEPENDS+=	xfce4-dict:${PORTSDIR}/textproc/xfce4-dict-plugin 
RUN_DEPENDS+=	xmlto:${PORTSDIR}/textproc/xmlto 

# www
RUN_DEPENDS+=	bluefish:${PORTSDIR}/www/bluefish 
RUN_DEPENDS+=	chrome:${PORTSDIR}/www/chromium 
RUN_DEPENDS+=	cs:${PORTSDIR}/www/clearsilver-python 
RUN_DEPENDS+=	firefox:${PORTSDIR}/www/firefox 
LIB_DEPENDS+=	gtkhtml-3.*:${PORTSDIR}/www/gtkhtml3 
LIB_DEPENDS+=	microhttpd:${PORTSDIR}/www/libmicrohttpd 
#RUN_DEPENDS+=	xulrunner:${PORTSDIR}/www/libxul 
RUN_DEPENDS+=	lighttpd:${PORTSDIR}/www/lighttpd 
RUN_DEPENDS+=	flash-player-properties:${PORTSDIR}/www/linux-f10-flashplugin11 
RUN_DEPENDS+=	midori:${PORTSDIR}/www/midori 
RUN_DEPENDS+=	${LOCALBASE}/libexec/apache22/mod_fastcgi.so:${PORTSDIR}/www/mod_fastcgi 
RUN_DEPENDS+=	${LOCALBASE}/libexec/apache22/mod_perl.so:${PORTSDIR}/www/mod_perl2 
RUN_DEPENDS+=	${LOCALBASE}/libexec/apache22/mod_security2.so:${PORTSDIR}/www/mod_security 
RUN_DEPENDS+=	${LOCALBASE}/libexec/apache22/mod_wsgi.so:${PORTSDIR}/www/mod_wsgi3 
RUN_DEPENDS+=	nspluginwrapper:${PORTSDIR}/www/nspluginwrapper 
RUN_DEPENDS+=	cssparse:${PORTSDIR}/www/py-cssutils 
RUN_DEPENDS+=	${PYTHON_SITELIBDIR}/django_cms-*.egg/apps/__init__.py:${PORTSDIR}/www/py-django-cms 
RUN_DEPENDS+=	urlgrabber:${PORTSDIR}/www/py-urlgrabber 
RUN_DEPENDS+=	spawn-fcgi:${PORTSDIR}/www/spawn-fcgi 
RUN_DEPENDS+=	${LOCALBASE}/lib/browser_plugins/swfdec-plugin/libswfdecmozilla.so:${PORTSDIR}/www/swfdec-plugin 
RUN_DEPENDS+=	${PYTHON_SITELIBDIR}/codetags-0.1-py2.7.egg:${PORTSDIR}/www/trac-codetags 
RUN_DEPENDS+=	${PYTHON_SITELIBDIR}/TracGit-0.12.0.5dev-py2.7.egg:${PORTSDIR}/www/trac-gitplugin 
RUN_DEPENDS+=	${PYTHON_SITELIBDIR}/IniAdmin-0.2-py2.7.egg:${PORTSDIR}/www/trac-iniadmin 
RUN_DEPENDS+=	${LOCALBASE}/lib/xfce4/panel/plugins/libsmartbookmark.so:${PORTSDIR}/www/xfce4-smartbookmark-plugin 

# x11-clocks
RUN_DEPENDS+=	${LOCALBASE}/lib/xfce4/panel/plugins/libdatetime.so:${PORTSDIR}/x11-clocks/xfce4-datetime-plugin 
RUN_DEPENDS+=	${LOCALBASE}/lib/xfce4/panel/plugins/libtime-out.so:${PORTSDIR}/x11-clocks/xfce4-timer-out-plugin 
RUN_DEPENDS+=	${LOCALBASE}/libexec/xfce4/panel-plugins/xfce4-timer:${PORTSDIR}/x11-clocks/xfce4-timer-plugin 

# x11-drivers
RUN_DEPENDS+=	xsetwacom:${PORTSDIR}/x11-drivers/input-wacom 
RUN_DEPENDS+=	${LOCALBASE}/lib/xorg/modules/input/egalax_drv.so:${PORTSDIR}/x11-drivers/xf86-input-egalax 
RUN_DEPENDS+=	${LOCALBASE}/lib/xorg/modules/input/joystick_drv.so:${PORTSDIR}/x11-drivers/xf86-input-joystick 
RUN_DEPENDS+=	${LOCALBASE}/lib/xorg/modules/drivers/sis_drv.so:${PORTSDIR}/x11-drivers/xf86-video-sis 

# x11-fm
RUN_DEPENDS+=	xfe:${PORTSDIR}/x11-fm/xfe 

# x11-fonts
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/alee-ttf/Bandal.ttf:${PORTSDIR}/korean/aleefonts-ttf 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/unfonts-core/UnBatang.ttf:${PORTSDIR}/korean/unfonts-core 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/unfonts-extra/UnPen.ttf:${PORTSDIR}/korean/unfonts-extra 
RUN_DEPENDS+=	${LOCALBASE}/share/font-jisx0213/K12-1.pcf.gz:${PORTSDIR}/japanese/alias-fonts 
RUN_DEPENDS+=	${LOCALBASE}/share/font-ipa/ipamp.otf:${PORTSDIR}/japanese/font-ipa 
RUN_DEPENDS+=	${LOCALBASE}/share/fonts/TTF/ipagui.ttf:${PORTSDIR}/japanese/font-ipa-uigothic 
RUN_DEPENDS+=	${LOCALBASE}/share/font-ipaex/ipaexg.otf:${PORTSDIR}/japanese/font-ipaex 
RUN_DEPENDS+=	${LOCALBASE}/share/font-kochi/kochi-mincho-subst.ttf:${PORTSDIR}/japanese/font-kochi 
RUN_DEPENDS+=	${LOCALBASE}/share/font-migmix/migmix-1m-bold.ttf:${PORTSDIR}/japanese/font-migmix 
RUN_DEPENDS+=	${LOCALBASE}/share/font-migu/migu-1c-bold.ttf:${PORTSDIR}/japanese/font-migu 
RUN_DEPENDS+=	${LOCALBASE}/share/font-mona-ipa/fonts/ipam-mona.ttf:${PORTSDIR}/japanese/font-mona-ipa 
RUN_DEPENDS+=	${LOCALBASE}/share/font-motoya-al/MTLc3m.ttf:${PORTSDIR}/japanese/font-motoya-al 
RUN_DEPENDS+=	${LOCALBASE}/share/font-mplus-ipa/fonts/ipam.ttf:${PORTSDIR}/japanese/font-mplus-ipa 
RUN_DEPENDS+=	${LOCALBASE}/share/font-sazanami/sazanami-mincho.ttf:${PORTSDIR}/japanese/font-sazanami 
RUN_DEPENDS+=	${LOCALBASE}/share/font-takao/TakaoPMincho.otf:${PORTSDIR}/japanese/font-takao 
RUN_DEPENDS+=	${LOCALBASE}/share/font-ume/ume-pgc4.ttf:${PORTSDIR}/japanese/font-ume 
RUN_DEPENDS+=	${LOCALBASE}/share/font-vlgothic/VL-PGothic-Regular.ttf:${PORTSDIR}/japanese/font-vlgothic 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/TrueType/mika.ttf:${PORTSDIR}/japanese/mikachan-ttfonts 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/hebrew/rashih.pcf:${PORTSDIR}/hebrew/elmar-fonts 
RUN_DEPENDS+=	${LOCALBASE}/share/fonts/std.zh_CN/STHeiti-Regular:${PORTSDIR}/chinese/font-std 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/anonymous-pro/Anonymous\ Pro.ttf:${PORTSDIR}/x11-fonts/anonymous-pro 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/artwiz-aleczapka-en/fkp.pcf:${PORTSDIR}/x11-fonts/artwiz-aleczapka 
RUN_DEPENDS+=	bdftopcf:${PORTSDIR}/x11-fonts/bdftopcf 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/CharisSIL/CharisSIL-B.ttf:${PORTSDIR}/x11-fonts/charis 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/DoulosSIL/DoulosSIL-R.ttf:${PORTSDIR}/x11-fonts/doulos 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/ecofont/ecofont_vera_sans_regular.ttf:${PORTSDIR}/x11-fonts/ecofont 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/fonts-te/vemana.ttf:${PORTSDIR}/x11-fonts/fonts-te 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/koi8-u-gemini/gem1c.pcf.gz:${PORTSDIR}/x11-fonts/geminifonts 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/Hana/HanaMinA.ttf:${PORTSDIR}/x11-fonts/hanazono-fonts-ttf 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/OTF/Inconsolata.otf:${PORTSDIR}/x11-fonts/inconsolata-ttf 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/stracke/Isabella.ttf:${PORTSDIR}/x11-fonts/isabella 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/junicode/Junicode-Bold.ttf:${PORTSDIR}/x11-fonts/junicode 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/Khmer//KhmerOS.ttf:${PORTSDIR}/x11-fonts/khmeros 
RUN_DEPENDS+=	mkbold:${PORTSDIR}/x11-fonts/mkbold-mkitalic 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/Myanmar/Padauk-bold.ttf:${PORTSDIR}/x11-fonts/padauk 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/ParaType/PTC55F.ttf:${PORTSDIR}/x11-fonts/paratype 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/stix/STIX-Regular.otf:${PORTSDIR}/x11-fonts/stix-fonts 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/local/suxus/suxus-iso-8859-1.pcf.gz:${PORTSDIR}/x11-fonts/suxus 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/terminus-font/ter-524b.pcf.gz:${PORTSDIR}/x11-fonts/terminus-font 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/ubuntu-font/Ubuntu-B.ttf:${PORTSDIR}/x11-fonts/ubuntu-font 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/urwfonts-ttf/a010013l.ttf:${PORTSDIR}/x11-fonts/urwfonts-ttf 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/webfonts/andalemo.ttf:${PORTSDIR}/x11-fonts/webfonts 
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/fonts/wqy/wenquanyi_10pt.pcf:${PORTSDIR}/x11-fonts/wqy 
RUN_DEPENDS+=	${LOCALBASE}/include/X11/extensions/xf86bigfont.h:${PORTSDIR}/x11-fonts/xf86bigfontproto 
RUN_DEPENDS+=	xfontsel:${PORTSDIR}/x11-fonts/xfontsel 

# x11-servers
RUN_DEPENDS+=	Xnest:${PORTSDIR}/x11-servers/xorg-nestserver 
RUN_DEPENDS+=	Xvfb:${PORTSDIR}/x11-servers/xorg-vfbserver 

# x11-themes
RUN_DEPENDS+=	${LOCALBASE}/lib/X11/icons/Jimmac/cursors/arrow:${PORTSDIR}/x11-themes/cursor-jimmac-theme 
RUN_DEPENDS+=	${LOCALBASE}/share/emerald/themes/Minimal/buttons.restore.png:${PORTSDIR}/x11-themes/emerald-themes 
RUN_DEPENDS+=	${LOCALBASE}/lib/kde4/kcm_gtk4.so:${PORTSDIR}/x11-themes/gtk-qt4-engine 
RUN_DEPENDS+=	${LOCALBASE}/libexec/icon-name-mapping:${PORTSDIR}/x11-themes/icon-naming-utils 
RUN_DEPENDS+=	lxappearance:${PORTSDIR}/x11-themes/lxappearance 

# x11-toolkits
LIB_DEPENDS+=	gdl-1:${PORTSDIR}/x11-toolkits/gdl 
LIB_DEPENDS+=	gtkimageview:${PORTSDIR}/x11-toolkits/gtkimageview 
RUN_DEPENDS+=	${LOCALBASE}/lib/gtk-2.0/modules/libgail-gnome.so:${PORTSDIR}/x11-toolkits/libgail-gnome 
LIB_DEPENDS+=	gtksourceviewmm-2.0:${PORTSDIR}/x11-toolkits/libgtksourceviewmm 
LIB_DEPENDS+=	wx_gtk2_gizmos-2.8:${PORTSDIR}/x11-toolkits/wxgtk28-contrib 

# x11-wm
RUN_DEPENDS+=	${LOCALBASE}/etc/gdm/Sessions/XFce4:${PORTSDIR}/x11-wm/xfce4 

# x11
RUN_DEPENDS+=	${LOCALBASE}/include/X11/extensions/bigreqsproto.h:${PORTSDIR}/x11/bigreqsproto 
RUN_DEPENDS+=	${LOCALBASE}/include/X11/extensions/evieproto.h:${PORTSDIR}/x11/evieext 
RUN_DEPENDS+=	florence:${PORTSDIR}/x11/florence 
RUN_DEPENDS+=	${PORTSDIR}/x11/gnome2-lite 
RUN_DEPENDS+=	switch2:${PORTSDIR}/x11/gtk-theme-switch2 
RUN_DEPENDS+=	idesk:${PORTSDIR}/x11/idesk 
LIB_DEPENDS+=	xdg-basedir:${PORTSDIR}/x11/libxdg-basedir 
RUN_DEPENDS+=	numlockx:${PORTSDIR}/x11/numlockx 
RUN_DEPENDS+=	/boot/modules/nvidia.ko:${PORTSDIR}/x11/nvidia-driver 
RUN_DEPENDS+=	nvidia-settings:${PORTSDIR}/x11/nvidia-settings 
RUN_DEPENDS+=	printscreen:${PORTSDIR}/x11/printscreen 
RUN_DEPENDS+=	${LOCALBASE}/include/X11/extensions/XResproto.h:${PORTSDIR}/x11/resourceproto 
RUN_DEPENDS+=	${PYTHON_SITELIBDIR}/xcbgen/__init__.py:${PORTSDIR}/x11/xcb-proto 
LIB_DEPENDS+=	xcb-image:${PORTSDIR}/x11/xcb-util-image 
LIB_DEPENDS+=	xcb-ewmh:${PORTSDIR}/x11/xcb-util-wm 
RUN_DEPENDS+=	${LOCALBASE}/include/X11/extensions/xcmiscproto.h:${PORTSDIR}/x11/xcmiscproto 
RUN_DEPENDS+=	${LOCALBASE}/include/X11/dri/xf86driproto.h:${PORTSDIR}/x11/xf86driproto 
RUN_DEPENDS+=	xfce4-clipman:${PORTSDIR}/x11/xfce4-clipman-plugin 
RUN_DEPENDS+=	${LOCALBASE}/lib/xfce4/panel-plugins/libquicklauncher.so:${PORTSDIR}/x11/xfce4-quicklauncher-plugin 
RUN_DEPENDS+=	xfce4-screenshooter:${PORTSDIR}/x11/xfce4-screenshooter-plugin 
RUN_DEPENDS+=	xfce4-taskmanager:${PORTSDIR}/x11/xfce4-taskmanager 
RUN_DEPENDS+=	verve-focus:${PORTSDIR}/x11/xfce4-verve-plugin 
RUN_DEPENDS+=	${LOCALBASE}/libexec/xfce4/panel-plugins/xfce4-wmdock-plugin:${PORTSDIR}/x11/xfce4-wmdock-plugin 
RUN_DEPENDS+=	${LOCALBASE}/libexec/xfce4/panel-plugins/xfce4-xfapplet-plugin:${PORTSDIR}/x11/xfce4-xfapplet-plugin 
RUN_DEPENDS+=	xman:${PORTSDIR}/x11/xman 
RUN_DEPENDS+=	Xorg:${PORTSDIR}/x11/xorg 
RUN_DEPENDS+=	xscreensaver:${PORTSDIR}/x11/xscreensaver 

do-install:

.include <bsd.port.mk>

