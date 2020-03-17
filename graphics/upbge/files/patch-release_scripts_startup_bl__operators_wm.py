--- release/scripts/startup/bl_operators/wm.py.orig	2020-03-02 16:43:39 UTC
+++ release/scripts/startup/bl_operators/wm.py
@@ -1586,7 +1586,7 @@ class WM_OT_blenderplayer_start(Operator):
         blender_bin_path = bpy.app.binary_path
         blender_bin_dir = os.path.dirname(blender_bin_path)
         ext = os.path.splitext(blender_bin_path)[-1]
-        player_path = os.path.join(blender_bin_dir, "blenderplayer" + ext)
+        player_path = os.path.join(blender_bin_dir, "upbgeplayer" + ext)
         # done static vars
 
         if sys.platform == "darwin":
