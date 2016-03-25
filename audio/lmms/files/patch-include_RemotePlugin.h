--- include/RemotePlugin.h.orig	2016-03-25 22:24:55 UTC
+++ include/RemotePlugin.h
@@ -221,9 +221,6 @@ public:
 
 	~shmFifo()
 	{
-#ifndef USE_QT_SHMEM
-		shmdt( m_data );
-#endif
 		// master?
 		if( m_master )
 		{
@@ -235,6 +232,9 @@ public:
 			sem_destroy( m_messageSem );
 #endif
 		}
+#ifndef USE_QT_SHMEM
+		shmdt( m_data );
+#endif
 	}
 
 	inline bool isInvalid() const
