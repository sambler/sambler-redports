--- intern/cycles/util/util_progress.h.orig	2018-06-26 03:23:33 UTC
+++ intern/cycles/util/util_progress.h
@@ -44,12 +44,12 @@ public:
 		substatus = "";
 		sync_status = "";
 		sync_substatus = "";
-		update_cb = NULL;
+		update_cb = function_null;
 		cancel = false;
 		cancel_message = "";
 		error = false;
 		error_message = "";
-		cancel_cb = NULL;
+		cancel_cb = function_null;
 	}
 
 	Progress(Progress& progress)
