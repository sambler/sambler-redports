--- googlefinance/__init__.py.orig	2018-02-28 05:49:32 UTC
+++ googlefinance/__init__.py
@@ -1,3 +1,4 @@
+from __future__ import print_function
 from urllib2 import Request, urlopen
 import json
 import sys
@@ -74,6 +75,6 @@ if __name__ == '__main__':
     symbols = symbols.split(',')
 
     try:
-        print json.dumps(getQuotes(symbols), indent=2)
+        print(json.dumps(getQuotes(symbols), indent=2))
     except:
-        print "Fail"
+        print("Fail")
