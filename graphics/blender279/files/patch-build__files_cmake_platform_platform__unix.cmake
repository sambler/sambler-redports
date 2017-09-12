--- build_files/cmake/platform/platform_unix.cmake.orig	2016-10-02 06:55:02 UTC
+++ build_files/cmake/platform/platform_unix.cmake
@@ -254,6 +254,7 @@ if(WITH_BOOST)
 		endif()
 		if(WITH_INTERNATIONAL)
 			list(APPEND __boost_packages locale)
+			set(PLATFORM_LINKFLAGS "${PLATFORM_LINKFLAGS} -liconv") # boost_locale needs it !
 		endif()
 		if(WITH_CYCLES_NETWORK)
 			list(APPEND __boost_packages serialization)
