--- clipgrab.cpp.orig	2013-07-18 05:53:21.000000000 +0930
+++ clipgrab.cpp	2013-09-06 22:54:05.671988673 +0930
@@ -129,8 +129,8 @@
     }
 
     activateProxySettings();
-    QNetworkAccessManager* obeyatorManager = new QNetworkAccessManager;
-    QNetworkRequest obeyatorRequest;
+    //QNetworkAccessManager* obeyatorManager = new QNetworkAccessManager;
+    //QNetworkRequest obeyatorRequest;
     QString sys = "x11";
 
     #if defined Q_WS_WIN
@@ -149,9 +149,9 @@
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
 
