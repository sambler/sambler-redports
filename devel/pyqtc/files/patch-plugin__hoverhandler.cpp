--- ./plugin/hoverhandler.cpp.orig	2013-04-11 21:25:34.000000000 +0930
+++ ./plugin/hoverhandler.cpp	2014-08-18 03:25:12.001454676 +0930
@@ -23,7 +23,7 @@
 void HoverHandler::identifyMatch(TextEditor::ITextEditor* editor, int pos) {
   current_reply_ = worker_pool_->NextHandler()->Tooltip(
         editor->document()->fileName(),
-        editor->contents(),
+        editor->textDocument()->contents(),
         pos);
 
   NewClosure(current_reply_, SIGNAL(Finished(bool)),
