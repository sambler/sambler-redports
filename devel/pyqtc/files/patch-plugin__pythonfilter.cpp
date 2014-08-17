--- ./plugin/pythonfilter.cpp.orig	2013-04-11 21:25:34.000000000 +0930
+++ ./plugin/pythonfilter.cpp	2014-08-18 03:25:12.111454643 +0930
@@ -74,9 +74,9 @@
   QString editor_kind;
 #endif
 
-  TextEditor::BaseTextEditorWidget::openEditorAt(
+  Core::EditorManager::openEditorAt(
         data.file_path_, data.line_number_, 0,
-        editor_kind, Core::EditorManager::ModeSwitch);
+        editor_kind, 0);
 }
 
 void PythonFilterBase::refresh(QFutureInterface<void>& future) {
