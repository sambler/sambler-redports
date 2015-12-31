--- libavformat/udp.c.orig	2014-09-09 17:30:58 UTC
+++ libavformat/udp.c
@@ -55,6 +55,8 @@
 #define UDP_TX_BUF_SIZE 32768
 #define UDP_MAX_PKT_SIZE 65536
 
+#define IPPROTO_IPV6 41
+
 typedef struct {
     const AVClass *class;
     int udp_fd;
