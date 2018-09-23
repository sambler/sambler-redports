--- intern/ghost/intern/GHOST_DisplayManager.cpp.orig	2018-09-11 18:17:23 UTC
+++ intern/ghost/intern/GHOST_DisplayManager.cpp
@@ -151,7 +151,12 @@ GHOST_DisplayManager::findMatch(
 	GHOST_TSuccess success = GHOST_kSuccess;
 	GHOST_ASSERT(m_settingsInitialized, "GHOST_DisplayManager::findMatch(): m_settingsInitialized=false");
 
-	int criteria[4] = { setting.xPixels, setting.yPixels, setting.bpp, setting.frequency };
+	int criteria[4] = { 
+		(int)setting.xPixels, 
+		(int)setting.yPixels, 
+		(int)setting.bpp, 
+		(int)setting.frequency
+	};
 	int capabilities[4];
 	double field, score;
 	double best = 1e12; // A big number
