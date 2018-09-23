--- extern/libmv/third_party/gflags/gflags.cc.orig	2018-07-02 23:30:01 UTC
+++ extern/libmv/third_party/gflags/gflags.cc
@@ -348,13 +348,13 @@ string FlagValue::ToString() const {
     case FV_BOOL:
       return VALUE_AS(bool) ? "true" : "false";
     case FV_INT32:
-      snprintf(intbuf, sizeof(intbuf), "%"PRId32, VALUE_AS(int32));
+      snprintf(intbuf, sizeof(intbuf), "%" PRId32, VALUE_AS(int32));
       return intbuf;
     case FV_INT64:
-      snprintf(intbuf, sizeof(intbuf), "%"PRId64, VALUE_AS(int64));
+      snprintf(intbuf, sizeof(intbuf), "%" PRId64, VALUE_AS(int64));
       return intbuf;
     case FV_UINT64:
-      snprintf(intbuf, sizeof(intbuf), "%"PRIu64, VALUE_AS(uint64));
+      snprintf(intbuf, sizeof(intbuf), "%" PRIu64, VALUE_AS(uint64));
       return intbuf;
     case FV_DOUBLE:
       snprintf(intbuf, sizeof(intbuf), "%.17g", VALUE_AS(double));
