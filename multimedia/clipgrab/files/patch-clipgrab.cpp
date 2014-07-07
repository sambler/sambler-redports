--- ./clipgrab.cpp.orig	2014-03-13 18:48:17.000000000 +1030
+++ ./clipgrab.cpp	2014-07-04 14:29:02.429536470 +0930
@@ -133,8 +133,8 @@
     }
 
     activateProxySettings();
-    QNetworkAccessManager* obeyatorManager = new QNetworkAccessManager;
-    QNetworkRequest obeyatorRequest;
+    //QNetworkAccessManager* obeyatorManager = new QNetworkAccessManager;
+    //QNetworkRequest obeyatorRequest;
     QString sys = "x11";
 
     #if defined Q_WS_WIN
@@ -157,9 +157,9 @@
     {
         settings.setValue("firstStarted-" + version, startedDateTime.toTime_t());
     }
-    obeyatorRequest.setUrl("http://clipgrab.de/or.php?version=" + version +"&lang="+QLocale::system().name().split("_")[0]+"&sys="+sys+"&current=" + settings.value("firstStarted-" + version, startedDateTime.toTime_t()).toString()+"&first="+settings.value("firstStarted", startedDateTime.toTime_t()).toString());
-    obeyatorManager->get(obeyatorRequest);
-    connect(obeyatorManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(obey(QNetworkReply*)));
+    //obeyatorRequest.setUrl("http://clipgrab.de/or.php?version=" + version +"&lang="+QLocale::system().name().split("_")[0]+"&sys="+sys+"&current=" + settings.value("firstStarted-" + version, startedDateTime.toTime_t()).toString()+"&first="+settings.value("firstStarted", startedDateTime.toTime_t()).toString());
+    //obeyatorManager->get(obeyatorRequest);
+    //connect(obeyatorManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(obey(QNetworkReply*)));
 
     connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardChanged()));
 
