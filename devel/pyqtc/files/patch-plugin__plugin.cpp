--- ./plugin/plugin.cpp.orig	2013-04-11 21:25:34.000000000 +0930
+++ ./plugin/plugin.cpp	2014-08-18 03:25:12.014455518 +0930
@@ -134,7 +134,7 @@
 
   if (response.has_line()) {
     if (response.has_file_path()) {
-      editor->openEditorAt(response.file_path(), response.line());
+      Core::EditorManager::openEditorAt(response.file_path(), response.line());
     } else {
       editor->gotoLine(response.line());
     }
