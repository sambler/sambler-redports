--- drivers/unix/ip_unix.cpp.orig	2014-12-15 18:49:18 UTC
+++ drivers/unix/ip_unix.cpp
@@ -54,7 +54,9 @@
  #endif
  #include <arpa/inet.h>
  #include <sys/socket.h>
-
+ #ifdef __FreeBSD__
+  #include <netinet/in.h>
+ #endif
 #endif
 
 IP_Address IP_Unix::_resolve_hostname(const String& p_hostname) {
