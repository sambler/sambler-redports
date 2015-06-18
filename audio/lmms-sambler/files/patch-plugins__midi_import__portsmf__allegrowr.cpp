--- ./plugins/MidiImport/portsmf/allegrowr.cpp.orig	2014-08-29 05:37:23.442454865 +0930
+++ ./plugins/MidiImport/portsmf/allegrowr.cpp	2014-08-29 05:37:23.607455215 +0930
@@ -41,7 +41,7 @@
         break;
     case 's': {
         string str;
-        string_escape(str, p->s, "\"");
+        string_escape(str, p->s, (char *)"\"");
         file << str;
         break;
     }
