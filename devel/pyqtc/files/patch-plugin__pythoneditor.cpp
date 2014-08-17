--- ./plugin/pythoneditor.cpp.orig	2013-04-11 21:25:34.000000000 +0930
+++ ./plugin/pythoneditor.cpp	2014-08-18 03:25:12.089478961 +0930
@@ -52,10 +52,10 @@
   setDisplayName(tr(constants::kEditorDisplayName));
   setIndenter(new PythonIndenter);
 
-  comment_definition_.setAfterWhiteSpaces(false);
-  comment_definition_.setSingleLine("#");
-  comment_definition_.setMultiLineStart("'''");
-  comment_definition_.setMultiLineEnd("'''");
+  comment_definition_.isAfterWhiteSpaces = false;
+  comment_definition_.singleLine = "#";
+  comment_definition_.multiLineStart = "'''";
+  comment_definition_.multiLineEnd = "'''";
 }
 
 void PythonEditorWidget::unCommentSelection() {
