--- intern/cycles/util/util_logging.h.orig	2018-06-14 14:31:32 UTC
+++ intern/cycles/util/util_logging.h
@@ -26,21 +26,23 @@
 CCL_NAMESPACE_BEGIN
 
 #if !defined(WITH_CYCLES_LOGGING) || defined(__KERNEL_GPU__)
-class StubStream : public std::ostream {
- public:
-	StubStream() : std::ostream(NULL) { }
+class StubStream {
+public:
+	template<class T>
+	StubStream& operator<<(const T&) {
+		return *this;
+	}
 };
 
 class LogMessageVoidify {
 public:
 	LogMessageVoidify() { }
-	void operator&(::std::ostream&) { }
+	void operator&(StubStream&) { }
 };
 
 #  define LOG_SUPPRESS() (true) ? (void) 0 : LogMessageVoidify() & StubStream()
 #  define LOG(severity) LOG_SUPPRESS()
 #  define VLOG(severity) LOG_SUPPRESS()
-
 #endif
 
 #define VLOG_ONCE(level, flag) if(!flag) flag = true, VLOG(level)
