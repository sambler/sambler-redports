--- ./libutil/pugixml.cpp.orig	2013-10-03 00:58:09.000000000 +0930
+++ ./libutil/pugixml.cpp	2013-10-03 00:59:45.000000000 +0930
@@ -1,7 +1,7 @@
 /**
- * pugixml parser - version 1.0
+ * pugixml parser - version 1.2
  * --------------------------------------------------------
- * Copyright (C) 2006-2010, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
+ * Copyright (C) 2006-2012, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
  * Report bugs and download new versions at http://pugixml.org/
  *
  * This library is distributed under the MIT License. See notice at the end
@@ -11,7 +11,8 @@
  * Copyright (C) 2003, by Kristen Wegner (kristen@tima.net)
  */
 
-#include "imageio.h"
+#ifndef SOURCE_PUGIXML_CPP
+#define SOURCE_PUGIXML_CPP
 
 #include "pugixml.hpp"
 
@@ -19,12 +20,14 @@
 #include <stdio.h>
 #include <string.h>
 #include <assert.h>
-#include <setjmp.h>
 #include <wchar.h>
 
 #ifndef PUGIXML_NO_XPATH
 #	include <math.h>
 #	include <float.h>
+#	ifdef PUGIXML_NO_EXCEPTIONS
+#		include <setjmp.h>
+#	endif
 #endif
 
 #ifndef PUGIXML_NO_STL
@@ -37,89 +40,130 @@
 #include <new>
 
 #ifdef _MSC_VER
+#	pragma warning(push)
 #	pragma warning(disable: 4127) // conditional expression is constant
 #	pragma warning(disable: 4324) // structure was padded due to __declspec(align())
 #	pragma warning(disable: 4611) // interaction between '_setjmp' and C++ object destruction is non-portable
 #	pragma warning(disable: 4702) // unreachable code
 #	pragma warning(disable: 4996) // this function or variable may be unsafe
+#	pragma warning(disable: 4793) // function compiled as native: presence of '_setjmp' makes a function unmanaged
 #endif
 
 #ifdef __INTEL_COMPILER
 #	pragma warning(disable: 177) // function was declared but never referenced 
+#	pragma warning(disable: 279) // controlling expression is constant
 #	pragma warning(disable: 1478 1786) // function was declared "deprecated"
+#	pragma warning(disable: 1684) // conversion from pointer to same-sized integral type
+#endif
+
+#if defined(__BORLANDC__) && defined(PUGIXML_HEADER_ONLY)
+#	pragma warn -8080 // symbol is declared but never used; disabling this inside push/pop bracket does not make the warning go away
 #endif
 
 #ifdef __BORLANDC__
+#	pragma option push
 #	pragma warn -8008 // condition is always false
 #	pragma warn -8066 // unreachable code
 #endif
 
 #ifdef __SNC__
+// Using diag_push/diag_pop does not disable the warnings inside templates due to a compiler bug
 #	pragma diag_suppress=178 // function was declared but never referenced
 #	pragma diag_suppress=237 // controlling expression is constant
 #endif
 
-// uintptr_t
-#if !defined(_MSC_VER) || _MSC_VER >= 1600
-#	include <stdint.h>
-#else
-#	if _MSC_VER < 1300
-// No native uintptr_t in MSVC6
-typedef size_t uintptr_t;
-#	endif
-typedef unsigned __int8 uint8_t;
-typedef unsigned __int16 uint16_t;
-typedef unsigned __int32 uint32_t;
-typedef __int32 int32_t;
-#endif
-
 // Inlining controls
 #if defined(_MSC_VER) && _MSC_VER >= 1300
-#	define PUGIXML_NO_INLINE __declspec(noinline)
+#	define PUGI__NO_INLINE __declspec(noinline)
 #elif defined(__GNUC__)
-#	define PUGIXML_NO_INLINE __attribute__((noinline))
+#	define PUGI__NO_INLINE __attribute__((noinline))
 #else
-#	define PUGIXML_NO_INLINE 
+#	define PUGI__NO_INLINE 
 #endif
 
 // Simple static assertion
-#define STATIC_ASSERT(cond) { static const char condition_failed[(cond) ? 1 : -1] = {0}; (void)condition_failed[0]; }
+#define PUGI__STATIC_ASSERT(cond) { static const char condition_failed[(cond) ? 1 : -1] = {0}; (void)condition_failed[0]; }
 
 // Digital Mars C++ bug workaround for passing char loaded from memory via stack
 #ifdef __DMC__
-#	define DMC_VOLATILE volatile
+#	define PUGI__DMC_VOLATILE volatile
 #else
-#	define DMC_VOLATILE
+#	define PUGI__DMC_VOLATILE
 #endif
 
+// Borland C++ bug workaround for not defining ::memcpy depending on header include order (can't always use std::memcpy because some compilers don't have it at all)
+#if defined(__BORLANDC__) && !defined(__MEM_H_USING_LIST)
+using std::memcpy;
+using std::memmove;
+#endif
 
-// Added by LG for OpenImageIO:
-using namespace OIIO;
-using namespace OIIO::pugi;
-using namespace pugi;
+// In some environments MSVC is a compiler but the CRT lacks certain MSVC-specific features
+#if defined(_MSC_VER) && !defined(__S3E__)
+#	define PUGI__MSVC_CRT_VERSION _MSC_VER
+#endif
+
+#ifdef PUGIXML_HEADER_ONLY
+#	define PUGI__NS_BEGIN namespace pugi { namespace impl {
+#	define PUGI__NS_END } }
+#	define PUGI__FN inline
+#	define PUGI__FN_NO_INLINE inline
+#else
+#	if defined(_MSC_VER) && _MSC_VER < 1300 // MSVC6 seems to have an amusing bug with anonymous namespaces inside namespaces
+#		define PUGI__NS_BEGIN namespace pugi { namespace impl {
+#		define PUGI__NS_END } }
+#	else
+#		define PUGI__NS_BEGIN namespace pugi { namespace impl { namespace {
+#		define PUGI__NS_END } } }
+#	endif
+#	define PUGI__FN
+#	define PUGI__FN_NO_INLINE PUGI__NO_INLINE
+#endif
+
+// uintptr_t
+#if !defined(_MSC_VER) || _MSC_VER >= 1600
+#	include <stdint.h>
+#else
+#	ifndef _UINTPTR_T_DEFINED
+// No native uintptr_t in MSVC6 and in some WinCE versions
+typedef size_t uintptr_t;
+#define _UINTPTR_T_DEFINED
+#	endif
+PUGI__NS_BEGIN
+	typedef unsigned __int8 uint8_t;
+	typedef unsigned __int16 uint16_t;
+	typedef unsigned __int32 uint32_t;
+PUGI__NS_END
+#endif
 
 // Memory allocation
-namespace
-{
-	void* default_allocate(size_t size)
+PUGI__NS_BEGIN
+	PUGI__FN void* default_allocate(size_t size)
 	{
 		return malloc(size);
 	}
 
-	void default_deallocate(void* ptr)
+	PUGI__FN void default_deallocate(void* ptr)
 	{
 		free(ptr);
 	}
 
-	allocation_function global_allocate = default_allocate;
-	deallocation_function global_deallocate = default_deallocate;
-}
+	template <typename T>
+	struct xml_memory_management_function_storage
+	{
+		static allocation_function allocate;
+		static deallocation_function deallocate;
+	};
+
+	template <typename T> allocation_function xml_memory_management_function_storage<T>::allocate = default_allocate;
+	template <typename T> deallocation_function xml_memory_management_function_storage<T>::deallocate = default_deallocate;
+
+	typedef xml_memory_management_function_storage<int> xml_memory;
+PUGI__NS_END
 
 // String utilities
-namespace
-{
+PUGI__NS_BEGIN
 	// Get string length
-	size_t strlength(const char_t* s)
+	PUGI__FN size_t strlength(const char_t* s)
 	{
 		assert(s);
 
@@ -131,7 +175,7 @@
 	}
 
 	// Compare two strings
-	bool strequal(const char_t* src, const char_t* dst)
+	PUGI__FN bool strequal(const char_t* src, const char_t* dst)
 	{
 		assert(src && dst);
 
@@ -143,7 +187,7 @@
 	}
 
 	// Compare lhs with [rhs_begin, rhs_end)
-	bool strequalrange(const char_t* lhs, const char_t* rhs, size_t count)
+	PUGI__FN bool strequalrange(const char_t* lhs, const char_t* rhs, size_t count)
 	{
 		for (size_t i = 0; i < count; ++i)
 			if (lhs[i] != rhs[i])
@@ -154,24 +198,23 @@
 	
 #ifdef PUGIXML_WCHAR_MODE
 	// Convert string to wide string, assuming all symbols are ASCII
-	void widen_ascii(wchar_t* dest, const char* source)
+	PUGI__FN void widen_ascii(wchar_t* dest, const char* source)
 	{
 		for (const char* i = source; *i; ++i) *dest++ = *i;
 		*dest = 0;
 	}
 #endif
-}
+PUGI__NS_END
 
 #if !defined(PUGIXML_NO_STL) || !defined(PUGIXML_NO_XPATH)
 // auto_ptr-like buffer holder for exception recovery
-namespace
-{
+PUGI__NS_BEGIN
 	struct buffer_holder
 	{
 		void* data;
 		void (*deleter)(void*);
 
-		buffer_holder(void* data, void (*deleter)(void*)): data(data), deleter(deleter)
+		buffer_holder(void* data_, void (*deleter_)(void*)): data(data_), deleter(deleter_)
 		{
 		}
 
@@ -187,12 +230,17 @@
 			return result;
 		}
 	};
-}
+PUGI__NS_END
 #endif
 
-namespace
-{
-	static const size_t xml_memory_page_size = 32768;
+PUGI__NS_BEGIN
+	static const size_t xml_memory_page_size =
+	#ifdef PUGIXML_MEMORY_PAGE_SIZE
+		PUGIXML_MEMORY_PAGE_SIZE
+	#else
+		32768
+	#endif
+		;
 
 	static const uintptr_t xml_memory_page_alignment = 32;
 	static const uintptr_t xml_memory_page_pointer_mask = ~(xml_memory_page_alignment - 1);
@@ -250,7 +298,7 @@
 			size_t size = offsetof(xml_memory_page, data) + data_size;
 
 			// allocate block with some alignment, leaving memory for worst-case padding
-			void* memory = global_allocate(size + xml_memory_page_alignment);
+			void* memory = xml_memory::allocate(size + xml_memory_page_alignment);
 			if (!memory) return 0;
 
 			// align upwards to page boundary
@@ -267,7 +315,7 @@
 
 		static void deallocate_page(xml_memory_page* page)
 		{
-			global_deallocate(page->memory);
+			xml_memory::deallocate(page->memory);
 		}
 
 		void* allocate_memory_oob(size_t size, xml_memory_page*& out_page);
@@ -343,17 +391,22 @@
 			assert(full_size < (1 << 16) || (page->busy_size == full_size && page_offset == 0));
 			header->full_size = static_cast<uint16_t>(full_size < (1 << 16) ? full_size : 0);
 
-			return reinterpret_cast<char_t*>(header + 1);
+			// round-trip through void* to avoid 'cast increases required alignment of target type' warning
+			// header is guaranteed a pointer-sized alignment, which should be enough for char_t
+			return static_cast<char_t*>(static_cast<void*>(header + 1));
 		}
 
 		void deallocate_string(char_t* string)
 		{
+			// this function casts pointers through void* to avoid 'cast increases required alignment of target type' warnings
+			// we're guaranteed the proper (pointer-sized) alignment on the input string if it was allocated via allocate_string
+
 			// get header
-			xml_memory_string_header* header = reinterpret_cast<xml_memory_string_header*>(string) - 1;
+			xml_memory_string_header* header = static_cast<xml_memory_string_header*>(static_cast<void*>(string)) - 1;
 
 			// deallocate
 			size_t page_offset = offsetof(xml_memory_page, data) + header->page_offset;
-			xml_memory_page* page = reinterpret_cast<xml_memory_page*>(reinterpret_cast<char*>(header) - page_offset);
+			xml_memory_page* page = reinterpret_cast<xml_memory_page*>(static_cast<void*>(reinterpret_cast<char*>(header) - page_offset));
 
 			// if full_size == 0 then this string occupies the whole page
 			size_t full_size = header->full_size == 0 ? page->busy_size : header->full_size;
@@ -365,11 +418,13 @@
 		size_t _busy_size;
 	};
 
-	PUGIXML_NO_INLINE void* xml_allocator::allocate_memory_oob(size_t size, xml_memory_page*& out_page)
+	PUGI__FN_NO_INLINE void* xml_allocator::allocate_memory_oob(size_t size, xml_memory_page*& out_page)
 	{
 		const size_t large_allocation_threshold = xml_memory_page_size / 4;
 
 		xml_memory_page* page = allocate_page(size <= large_allocation_threshold ? xml_memory_page_size : size);
+		out_page = page;
+
 		if (!page) return 0;
 
 		if (size <= large_allocation_threshold)
@@ -399,16 +454,9 @@
 		// allocate inside page
 		page->busy_size = size;
 
-		out_page = page;
 		return page->data;
 	}
-}
-
-
-
-// Added by LG for OpenImageIO:
-OIIO_NAMESPACE_ENTER
-{
+PUGI__NS_END
 
 namespace pugi
 {
@@ -416,7 +464,7 @@
 	struct xml_attribute_struct
 	{
 		/// Default ctor
-		xml_attribute_struct(xml_memory_page* page): header(reinterpret_cast<uintptr_t>(page)), name(0), value(0), prev_attribute_c(0), next_attribute(0)
+		xml_attribute_struct(impl::xml_memory_page* page): header(reinterpret_cast<uintptr_t>(page)), name(0), value(0), prev_attribute_c(0), next_attribute(0)
 		{
 		}
 
@@ -434,7 +482,7 @@
 	{
 		/// Default ctor
 		/// \param type - node type
-		xml_node_struct(xml_memory_page* page, xml_node_type type): header(reinterpret_cast<uintptr_t>(page) | (type - 1)), parent(0), name(0), value(0), first_child(0), prev_sibling_c(0), next_sibling(0), first_attribute(0)
+		xml_node_struct(impl::xml_memory_page* page, xml_node_type type): header(reinterpret_cast<uintptr_t>(page) | (type - 1)), parent(0), name(0), value(0), first_child(0), prev_sibling_c(0), next_sibling(0), first_attribute(0)
 		{
 		}
 
@@ -454,13 +502,7 @@
 	};
 }
 
-// Added by LG for OpenImageIO:
-}
-OIIO_NAMESPACE_EXIT
-
-
-namespace
-{
+PUGI__NS_BEGIN
 	struct xml_document_struct: public xml_node_struct, public xml_allocator
 	{
 		xml_document_struct(xml_memory_page* page): xml_node_struct(page, node_document), xml_allocator(page), buffer(0)
@@ -470,17 +512,16 @@
 		const char_t* buffer;
 	};
 
-	static inline xml_allocator& get_allocator(const xml_node_struct* node)
+	inline xml_allocator& get_allocator(const xml_node_struct* node)
 	{
 		assert(node);
 
 		return *reinterpret_cast<xml_memory_page*>(node->header & xml_memory_page_pointer_mask)->allocator;
 	}
-}
+PUGI__NS_END
 
 // Low-level DOM operations
-namespace
-{
+PUGI__NS_BEGIN
 	inline xml_attribute_struct* allocate_attribute(xml_allocator& alloc)
 	{
 		xml_memory_page* page;
@@ -501,8 +542,8 @@
 	{
 		uintptr_t header = a->header;
 
-		if (header & xml_memory_page_name_allocated_mask) alloc.deallocate_string(a->name);
-		if (header & xml_memory_page_value_allocated_mask) alloc.deallocate_string(a->value);
+		if (header & impl::xml_memory_page_name_allocated_mask) alloc.deallocate_string(a->name);
+		if (header & impl::xml_memory_page_value_allocated_mask) alloc.deallocate_string(a->value);
 
 		alloc.deallocate_memory(a, sizeof(xml_attribute_struct), reinterpret_cast<xml_memory_page*>(header & xml_memory_page_pointer_mask));
 	}
@@ -511,8 +552,8 @@
 	{
 		uintptr_t header = n->header;
 
-		if (header & xml_memory_page_name_allocated_mask) alloc.deallocate_string(n->name);
-		if (header & xml_memory_page_value_allocated_mask) alloc.deallocate_string(n->value);
+		if (header & impl::xml_memory_page_name_allocated_mask) alloc.deallocate_string(n->name);
+		if (header & impl::xml_memory_page_value_allocated_mask) alloc.deallocate_string(n->value);
 
 		for (xml_attribute_struct* attr = n->first_attribute; attr; )
 		{
@@ -535,7 +576,7 @@
 		alloc.deallocate_memory(n, sizeof(xml_node_struct), reinterpret_cast<xml_memory_page*>(header & xml_memory_page_pointer_mask));
 	}
 
-	PUGIXML_NO_INLINE xml_node_struct* append_node(xml_node_struct* node, xml_allocator& alloc, xml_node_type type = node_element)
+	PUGI__FN_NO_INLINE xml_node_struct* append_node(xml_node_struct* node, xml_allocator& alloc, xml_node_type type = node_element)
 	{
 		xml_node_struct* child = allocate_node(alloc, type);
 		if (!child) return 0;
@@ -561,7 +602,7 @@
 		return child;
 	}
 
-	PUGIXML_NO_INLINE xml_attribute_struct* append_attribute_ll(xml_node_struct* node, xml_allocator& alloc)
+	PUGI__FN_NO_INLINE xml_attribute_struct* append_attribute_ll(xml_node_struct* node, xml_allocator& alloc)
 	{
 		xml_attribute_struct* a = allocate_attribute(alloc);
 		if (!a) return 0;
@@ -584,11 +625,10 @@
 			
 		return a;
 	}
-}
+PUGI__NS_END
 
 // Helper classes for code generation
-namespace
-{
+PUGI__NS_BEGIN
 	struct opt_false
 	{
 		enum { value = 0 };
@@ -598,11 +638,10 @@
 	{
 		enum { value = 1 };
 	};
-}
+PUGI__NS_END
 
 // Unicode utilities
-namespace
-{
+PUGI__NS_BEGIN
 	inline uint16_t endian_swap(uint16_t value)
 	{
 		return static_cast<uint16_t>(((value & 0xff) << 8) | (value >> 8));
@@ -707,8 +746,8 @@
 
 		static value_type high(value_type result, uint32_t ch)
 		{
-			uint32_t msh = (uint32_t)(ch - 0x10000) >> 10;
-			uint32_t lsh = (uint32_t)(ch - 0x10000) & 0x3ff;
+			uint32_t msh = static_cast<uint32_t>(ch - 0x10000) >> 10;
+			uint32_t lsh = static_cast<uint32_t>(ch - 0x10000) & 0x3ff;
 
 			result[0] = static_cast<uint16_t>(0xD800 + msh);
 			result[1] = static_cast<uint16_t>(0xDC00 + lsh);
@@ -763,6 +802,27 @@
 		}
 	};
 
+	struct latin1_writer
+	{
+		typedef uint8_t* value_type;
+
+		static value_type low(value_type result, uint32_t ch)
+		{
+			*result = static_cast<uint8_t>(ch > 255 ? '?' : ch);
+
+			return result + 1;
+		}
+
+		static value_type high(value_type result, uint32_t ch)
+		{
+			(void)ch;
+
+			*result = '?';
+
+			return result + 1;
+		}
+	};
+
 	template <size_t size> struct wchar_selector;
 
 	template <> struct wchar_selector<2>
@@ -802,7 +862,8 @@
 					// process aligned single-byte (ascii) blocks
 					if ((reinterpret_cast<uintptr_t>(data) & 3) == 0)
 					{
-						while (size >= 4 && (*reinterpret_cast<const uint32_t*>(data) & 0x80808080) == 0)
+						// round-trip through void* to silence 'cast increases required alignment of target type' warnings
+						while (size >= 4 && (*static_cast<const uint32_t*>(static_cast<const void*>(data)) & 0x80808080) == 0)
 						{
 							result = Traits::low(result, data[0]);
 							result = Traits::low(result, data[1]);
@@ -814,21 +875,21 @@
 					}
 				}
 				// 110xxxxx -> U+0080..U+07FF
-				else if ((unsigned)(lead - 0xC0) < 0x20 && size >= 2 && (data[1] & 0xc0) == 0x80)
+				else if (static_cast<unsigned int>(lead - 0xC0) < 0x20 && size >= 2 && (data[1] & 0xc0) == 0x80)
 				{
 					result = Traits::low(result, ((lead & ~0xC0) << 6) | (data[1] & utf8_byte_mask));
 					data += 2;
 					size -= 2;
 				}
 				// 1110xxxx -> U+0800-U+FFFF
-				else if ((unsigned)(lead - 0xE0) < 0x10 && size >= 3 && (data[1] & 0xc0) == 0x80 && (data[2] & 0xc0) == 0x80)
+				else if (static_cast<unsigned int>(lead - 0xE0) < 0x10 && size >= 3 && (data[1] & 0xc0) == 0x80 && (data[2] & 0xc0) == 0x80)
 				{
 					result = Traits::low(result, ((lead & ~0xE0) << 12) | ((data[1] & utf8_byte_mask) << 6) | (data[2] & utf8_byte_mask));
 					data += 3;
 					size -= 3;
 				}
 				// 11110xxx -> U+10000..U+10FFFF
-				else if ((unsigned)(lead - 0xF0) < 0x08 && size >= 4 && (data[1] & 0xc0) == 0x80 && (data[2] & 0xc0) == 0x80 && (data[3] & 0xc0) == 0x80)
+				else if (static_cast<unsigned int>(lead - 0xF0) < 0x08 && size >= 4 && (data[1] & 0xc0) == 0x80 && (data[2] & 0xc0) == 0x80 && (data[3] & 0xc0) == 0x80)
 				{
 					result = Traits::high(result, ((lead & ~0xF0) << 18) | ((data[1] & utf8_byte_mask) << 12) | ((data[2] & utf8_byte_mask) << 6) | (data[3] & utf8_byte_mask));
 					data += 4;
@@ -860,17 +921,17 @@
 					data += 1;
 				}
 				// U+E000..U+FFFF
-				else if ((unsigned)(lead - 0xE000) < 0x2000)
+				else if (static_cast<unsigned int>(lead - 0xE000) < 0x2000)
 				{
 					result = Traits::low(result, lead);
 					data += 1;
 				}
 				// surrogate pair lead
-				else if ((unsigned)(lead - 0xD800) < 0x400 && data + 1 < end)
+				else if (static_cast<unsigned int>(lead - 0xD800) < 0x400 && data + 1 < end)
 				{
 					uint16_t next = opt_swap::value ? endian_swap(data[1]) : data[1];
 
-					if ((unsigned)(next - 0xDC00) < 0x400)
+					if (static_cast<unsigned int>(next - 0xDC00) < 0x400)
 					{
 						result = Traits::high(result, 0x10000 + ((lead & 0x3ff) << 10) + (next & 0x3ff));
 						data += 2;
@@ -913,24 +974,47 @@
 
 			return result;
 		}
+
+		static inline typename Traits::value_type decode_latin1_block(const uint8_t* data, size_t size, typename Traits::value_type result)
+		{
+			for (size_t i = 0; i < size; ++i)
+			{
+				result = Traits::low(result, data[i]);
+			}
+
+			return result;
+		}
+
+		static inline typename Traits::value_type decode_wchar_block_impl(const uint16_t* data, size_t size, typename Traits::value_type result)
+		{
+			return decode_utf16_block(data, size, result);
+		}
+
+		static inline typename Traits::value_type decode_wchar_block_impl(const uint32_t* data, size_t size, typename Traits::value_type result)
+		{
+			return decode_utf32_block(data, size, result);
+		}
+
+		static inline typename Traits::value_type decode_wchar_block(const wchar_t* data, size_t size, typename Traits::value_type result)
+		{
+			return decode_wchar_block_impl(reinterpret_cast<const wchar_selector<sizeof(wchar_t)>::type*>(data), size, result);
+		}
 	};
 
-	template <typename T> inline void convert_utf_endian_swap(T* result, const T* data, size_t length)
+	template <typename T> PUGI__FN void convert_utf_endian_swap(T* result, const T* data, size_t length)
 	{
 		for (size_t i = 0; i < length; ++i) result[i] = endian_swap(data[i]);
 	}
 
 #ifdef PUGIXML_WCHAR_MODE
-	inline void convert_wchar_endian_swap(wchar_t* result, const wchar_t* data, size_t length)
+	PUGI__FN void convert_wchar_endian_swap(wchar_t* result, const wchar_t* data, size_t length)
 	{
 		for (size_t i = 0; i < length; ++i) result[i] = static_cast<wchar_t>(endian_swap(static_cast<wchar_selector<sizeof(wchar_t)>::type>(data[i])));
 	}
 #endif
+PUGI__NS_END
 
-}
-
-namespace
-{	
+PUGI__NS_BEGIN
 	enum chartype_t
 	{
 		ct_parse_pcdata = 1,	// \0, &, \r, <
@@ -943,7 +1027,7 @@
 		ct_start_symbol = 128	// Any symbol > 127, a-z, A-Z, _, :
 	};
 
-	const unsigned char chartype_table[256] =
+	static const unsigned char chartype_table[256] =
 	{
 		55,  0,   0,   0,   0,   0,   0,   0,      0,   12,  12,  0,   0,   63,  0,   0,   // 0-15
 		0,   0,   0,   0,   0,   0,   0,   0,      0,   0,   0,   0,   0,   0,   0,   0,   // 16-31
@@ -973,7 +1057,7 @@
 		ctx_symbol = 16			  // Any symbol > 127, a-z, A-Z, 0-9, _, -, .
 	};
 	
-	const unsigned char chartypex_table[256] =
+	static const unsigned char chartypex_table[256] =
 	{
 		3,  3,  3,  3,  3,  3,  3,  3,     3,  0,  2,  3,  3,  2,  3,  3,     // 0-15
 		3,  3,  3,  3,  3,  3,  3,  3,     3,  3,  3,  3,  3,  3,  3,  3,     // 16-31
@@ -996,24 +1080,24 @@
 	};
 	
 #ifdef PUGIXML_WCHAR_MODE
-	#define IS_CHARTYPE_IMPL(c, ct, table) ((static_cast<unsigned int>(c) < 128 ? table[static_cast<unsigned int>(c)] : table[128]) & (ct))
+	#define PUGI__IS_CHARTYPE_IMPL(c, ct, table) ((static_cast<unsigned int>(c) < 128 ? table[static_cast<unsigned int>(c)] : table[128]) & (ct))
 #else
-	#define IS_CHARTYPE_IMPL(c, ct, table) (table[static_cast<unsigned char>(c)] & (ct))
+	#define PUGI__IS_CHARTYPE_IMPL(c, ct, table) (table[static_cast<unsigned char>(c)] & (ct))
 #endif
 
-	#define IS_CHARTYPE(c, ct) IS_CHARTYPE_IMPL(c, ct, chartype_table)
-	#define IS_CHARTYPEX(c, ct) IS_CHARTYPE_IMPL(c, ct, chartypex_table)
+	#define PUGI__IS_CHARTYPE(c, ct) PUGI__IS_CHARTYPE_IMPL(c, ct, chartype_table)
+	#define PUGI__IS_CHARTYPEX(c, ct) PUGI__IS_CHARTYPE_IMPL(c, ct, chartypex_table)
 
-	bool is_little_endian()
+	PUGI__FN bool is_little_endian()
 	{
 		unsigned int ui = 1;
 
 		return *reinterpret_cast<unsigned char*>(&ui) == 1;
 	}
 
-	xml_encoding get_wchar_encoding()
+	PUGI__FN xml_encoding get_wchar_encoding()
 	{
-		STATIC_ASSERT(sizeof(wchar_t) == 2 || sizeof(wchar_t) == 4);
+		PUGI__STATIC_ASSERT(sizeof(wchar_t) == 2 || sizeof(wchar_t) == 4);
 
 		if (sizeof(wchar_t) == 2)
 			return is_little_endian() ? encoding_utf16_le : encoding_utf16_be;
@@ -1021,7 +1105,7 @@
 			return is_little_endian() ? encoding_utf32_le : encoding_utf32_be;
 	}
 
-	xml_encoding guess_buffer_encoding(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
+	PUGI__FN xml_encoding guess_buffer_encoding(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
 	{
 		// look for BOM in first few bytes
 		if (d0 == 0 && d1 == 0 && d2 == 0xfe && d3 == 0xff) return encoding_utf32_be;
@@ -1045,7 +1129,7 @@
 		return encoding_utf8;
 	}
 
-	xml_encoding get_buffer_encoding(xml_encoding encoding, const void* contents, size_t size)
+	PUGI__FN xml_encoding get_buffer_encoding(xml_encoding encoding, const void* contents, size_t size)
 	{
 		// replace wchar encoding with utf implementation
 		if (encoding == encoding_wchar) return get_wchar_encoding();
@@ -1065,12 +1149,12 @@
 		// try to guess encoding (based on XML specification, Appendix F.1)
 		const uint8_t* data = static_cast<const uint8_t*>(contents);
 
-		DMC_VOLATILE uint8_t d0 = data[0], d1 = data[1], d2 = data[2], d3 = data[3];
+		PUGI__DMC_VOLATILE uint8_t d0 = data[0], d1 = data[1], d2 = data[2], d3 = data[3];
 
 		return guess_buffer_encoding(d0, d1, d2, d3);
 	}
 
-	bool get_mutable_buffer(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, bool is_mutable)
+	PUGI__FN bool get_mutable_buffer(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, bool is_mutable)
 	{
 		if (is_mutable)
 		{
@@ -1078,7 +1162,7 @@
 		}
 		else
 		{
-			void* buffer = global_allocate(size > 0 ? size : 1);
+			void* buffer = xml_memory::allocate(size > 0 ? size : 1);
 			if (!buffer) return false;
 
 			memcpy(buffer, contents, size);
@@ -1092,13 +1176,13 @@
 	}
 
 #ifdef PUGIXML_WCHAR_MODE
-	inline bool need_endian_swap_utf(xml_encoding le, xml_encoding re)
+	PUGI__FN bool need_endian_swap_utf(xml_encoding le, xml_encoding re)
 	{
 		return (le == encoding_utf16_be && re == encoding_utf16_le) || (le == encoding_utf16_le && re == encoding_utf16_be) ||
-		       (le == encoding_utf32_be && re == encoding_utf32_le) || (le == encoding_utf32_le && re == encoding_utf32_be);
+			   (le == encoding_utf32_be && re == encoding_utf32_le) || (le == encoding_utf32_le && re == encoding_utf32_be);
 	}
 
-	bool convert_buffer_endian_swap(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, bool is_mutable)
+	PUGI__FN bool convert_buffer_endian_swap(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, bool is_mutable)
 	{
 		const char_t* data = static_cast<const char_t*>(contents);
 	
@@ -1108,7 +1192,7 @@
 		}
 		else
 		{
-			out_buffer = static_cast<char_t*>(global_allocate(size > 0 ? size : 1));
+			out_buffer = static_cast<char_t*>(xml_memory::allocate(size > 0 ? size : 1));
 			if (!out_buffer) return false;
 		}
 
@@ -1119,7 +1203,7 @@
 		return true;
 	}
 
-	bool convert_buffer_utf8(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size)
+	PUGI__FN bool convert_buffer_utf8(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size)
 	{
 		const uint8_t* data = static_cast<const uint8_t*>(contents);
 
@@ -1127,7 +1211,7 @@
 		out_length = utf_decoder<wchar_counter>::decode_utf8_block(data, size, 0);
 
 		// allocate buffer of suitable length
-		out_buffer = static_cast<char_t*>(global_allocate((out_length > 0 ? out_length : 1) * sizeof(char_t)));
+		out_buffer = static_cast<char_t*>(xml_memory::allocate((out_length > 0 ? out_length : 1) * sizeof(char_t)));
 		if (!out_buffer) return false;
 
 		// second pass: convert utf8 input to wchar_t
@@ -1140,7 +1224,7 @@
 		return true;
 	}
 
-	template <typename opt_swap> bool convert_buffer_utf16(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, opt_swap)
+	template <typename opt_swap> PUGI__FN bool convert_buffer_utf16(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, opt_swap)
 	{
 		const uint16_t* data = static_cast<const uint16_t*>(contents);
 		size_t length = size / sizeof(uint16_t);
@@ -1149,7 +1233,7 @@
 		out_length = utf_decoder<wchar_counter, opt_swap>::decode_utf16_block(data, length, 0);
 
 		// allocate buffer of suitable length
-		out_buffer = static_cast<char_t*>(global_allocate((out_length > 0 ? out_length : 1) * sizeof(char_t)));
+		out_buffer = static_cast<char_t*>(xml_memory::allocate((out_length > 0 ? out_length : 1) * sizeof(char_t)));
 		if (!out_buffer) return false;
 
 		// second pass: convert utf16 input to wchar_t
@@ -1162,7 +1246,7 @@
 		return true;
 	}
 
-	template <typename opt_swap> bool convert_buffer_utf32(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, opt_swap)
+	template <typename opt_swap> PUGI__FN bool convert_buffer_utf32(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, opt_swap)
 	{
 		const uint32_t* data = static_cast<const uint32_t*>(contents);
 		size_t length = size / sizeof(uint32_t);
@@ -1171,7 +1255,7 @@
 		out_length = utf_decoder<wchar_counter, opt_swap>::decode_utf32_block(data, length, 0);
 
 		// allocate buffer of suitable length
-		out_buffer = static_cast<char_t*>(global_allocate((out_length > 0 ? out_length : 1) * sizeof(char_t)));
+		out_buffer = static_cast<char_t*>(xml_memory::allocate((out_length > 0 ? out_length : 1) * sizeof(char_t)));
 		if (!out_buffer) return false;
 
 		// second pass: convert utf32 input to wchar_t
@@ -1184,7 +1268,28 @@
 		return true;
 	}
 
-	bool convert_buffer(char_t*& out_buffer, size_t& out_length, xml_encoding encoding, const void* contents, size_t size, bool is_mutable)
+	PUGI__FN bool convert_buffer_latin1(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size)
+	{
+		const uint8_t* data = static_cast<const uint8_t*>(contents);
+
+		// get length in wchar_t units
+		out_length = size;
+
+		// allocate buffer of suitable length
+		out_buffer = static_cast<char_t*>(xml_memory::allocate((out_length > 0 ? out_length : 1) * sizeof(char_t)));
+		if (!out_buffer) return false;
+
+		// convert latin1 input to wchar_t
+		wchar_writer::value_type out_begin = reinterpret_cast<wchar_writer::value_type>(out_buffer);
+		wchar_writer::value_type out_end = utf_decoder<wchar_writer>::decode_latin1_block(data, size, out_begin);
+
+		assert(out_end == out_begin + out_length);
+		(void)!out_end;
+
+		return true;
+	}
+
+	PUGI__FN bool convert_buffer(char_t*& out_buffer, size_t& out_length, xml_encoding encoding, const void* contents, size_t size, bool is_mutable)
 	{
 		// get native encoding
 		xml_encoding wchar_encoding = get_wchar_encoding();
@@ -1218,11 +1323,14 @@
 				convert_buffer_utf32(out_buffer, out_length, contents, size, opt_true());
 		}
 
+		// source encoding is latin1
+		if (encoding == encoding_latin1) return convert_buffer_latin1(out_buffer, out_length, contents, size);
+
 		assert(!"Invalid encoding");
 		return false;
 	}
 #else
-	template <typename opt_swap> bool convert_buffer_utf16(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, opt_swap)
+	template <typename opt_swap> PUGI__FN bool convert_buffer_utf16(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, opt_swap)
 	{
 		const uint16_t* data = static_cast<const uint16_t*>(contents);
 		size_t length = size / sizeof(uint16_t);
@@ -1231,7 +1339,7 @@
 		out_length = utf_decoder<utf8_counter, opt_swap>::decode_utf16_block(data, length, 0);
 
 		// allocate buffer of suitable length
-		out_buffer = static_cast<char_t*>(global_allocate((out_length > 0 ? out_length : 1) * sizeof(char_t)));
+		out_buffer = static_cast<char_t*>(xml_memory::allocate((out_length > 0 ? out_length : 1) * sizeof(char_t)));
 		if (!out_buffer) return false;
 
 		// second pass: convert utf16 input to utf8
@@ -1244,7 +1352,7 @@
 		return true;
 	}
 
-	template <typename opt_swap> bool convert_buffer_utf32(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, opt_swap)
+	template <typename opt_swap> PUGI__FN bool convert_buffer_utf32(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, opt_swap)
 	{
 		const uint32_t* data = static_cast<const uint32_t*>(contents);
 		size_t length = size / sizeof(uint32_t);
@@ -1253,7 +1361,7 @@
 		out_length = utf_decoder<utf8_counter, opt_swap>::decode_utf32_block(data, length, 0);
 
 		// allocate buffer of suitable length
-		out_buffer = static_cast<char_t*>(global_allocate((out_length > 0 ? out_length : 1) * sizeof(char_t)));
+		out_buffer = static_cast<char_t*>(xml_memory::allocate((out_length > 0 ? out_length : 1) * sizeof(char_t)));
 		if (!out_buffer) return false;
 
 		// second pass: convert utf32 input to utf8
@@ -1266,7 +1374,49 @@
 		return true;
 	}
 
-	bool convert_buffer(char_t*& out_buffer, size_t& out_length, xml_encoding encoding, const void* contents, size_t size, bool is_mutable)
+	PUGI__FN size_t get_latin1_7bit_prefix_length(const uint8_t* data, size_t size)
+	{
+		for (size_t i = 0; i < size; ++i)
+			if (data[i] > 127)
+				return i;
+
+		return size;
+	}
+
+	PUGI__FN bool convert_buffer_latin1(char_t*& out_buffer, size_t& out_length, const void* contents, size_t size, bool is_mutable)
+	{
+		const uint8_t* data = static_cast<const uint8_t*>(contents);
+
+		// get size of prefix that does not need utf8 conversion
+		size_t prefix_length = get_latin1_7bit_prefix_length(data, size);
+		assert(prefix_length <= size);
+
+		const uint8_t* postfix = data + prefix_length;
+		size_t postfix_length = size - prefix_length;
+
+		// if no conversion is needed, just return the original buffer
+		if (postfix_length == 0) return get_mutable_buffer(out_buffer, out_length, contents, size, is_mutable);
+
+		// first pass: get length in utf8 units
+		out_length = prefix_length + utf_decoder<utf8_counter>::decode_latin1_block(postfix, postfix_length, 0);
+
+		// allocate buffer of suitable length
+		out_buffer = static_cast<char_t*>(xml_memory::allocate((out_length > 0 ? out_length : 1) * sizeof(char_t)));
+		if (!out_buffer) return false;
+
+		// second pass: convert latin1 input to utf8
+		memcpy(out_buffer, data, prefix_length);
+
+		uint8_t* out_begin = reinterpret_cast<uint8_t*>(out_buffer);
+		uint8_t* out_end = utf_decoder<utf8_writer>::decode_latin1_block(postfix, postfix_length, out_begin + prefix_length);
+
+		assert(out_end == out_begin + out_length);
+		(void)!out_end;
+
+		return true;
+	}
+
+	PUGI__FN bool convert_buffer(char_t*& out_buffer, size_t& out_length, xml_encoding encoding, const void* contents, size_t size, bool is_mutable)
 	{
 		// fast path: no conversion required
 		if (encoding == encoding_utf8) return get_mutable_buffer(out_buffer, out_length, contents, size, is_mutable);
@@ -1291,43 +1441,38 @@
 				convert_buffer_utf32(out_buffer, out_length, contents, size, opt_true());
 		}
 
+		// source encoding is latin1
+		if (encoding == encoding_latin1) return convert_buffer_latin1(out_buffer, out_length, contents, size, is_mutable);
+
 		assert(!"Invalid encoding");
 		return false;
 	}
 #endif
 
-	size_t as_utf8_begin(const wchar_t* str, size_t length)
+	PUGI__FN size_t as_utf8_begin(const wchar_t* str, size_t length)
 	{
-		STATIC_ASSERT(sizeof(wchar_t) == 2 || sizeof(wchar_t) == 4);
-
 		// get length in utf8 characters
-		return sizeof(wchar_t) == 2 ?
-			utf_decoder<utf8_counter>::decode_utf16_block(reinterpret_cast<const uint16_t*>(str), length, 0) :
-			utf_decoder<utf8_counter>::decode_utf32_block(reinterpret_cast<const uint32_t*>(str), length, 0);
-    }
-
-    void as_utf8_end(char* buffer, size_t size, const wchar_t* str, size_t length)
-    {
-		STATIC_ASSERT(sizeof(wchar_t) == 2 || sizeof(wchar_t) == 4);
+		return utf_decoder<utf8_counter>::decode_wchar_block(str, length, 0);
+	}
 
-        // convert to utf8
-        uint8_t* begin = reinterpret_cast<uint8_t*>(buffer);
-        uint8_t* end = sizeof(wchar_t) == 2 ?
-            utf_decoder<utf8_writer>::decode_utf16_block(reinterpret_cast<const uint16_t*>(str), length, begin) :
-            utf_decoder<utf8_writer>::decode_utf32_block(reinterpret_cast<const uint32_t*>(str), length, begin);
-    
-        assert(begin + size == end);
-        (void)!end;
+	PUGI__FN void as_utf8_end(char* buffer, size_t size, const wchar_t* str, size_t length)
+	{
+		// convert to utf8
+		uint8_t* begin = reinterpret_cast<uint8_t*>(buffer);
+		uint8_t* end = utf_decoder<utf8_writer>::decode_wchar_block(str, length, begin);
+	
+		assert(begin + size == end);
+		(void)!end;
 
 		// zero-terminate
 		buffer[size] = 0;
 	}
-    
+	
 #ifndef PUGIXML_NO_STL
-    std::string as_utf8_impl(const wchar_t* str, size_t length)
-    {
+	PUGI__FN std::string as_utf8_impl(const wchar_t* str, size_t length)
+	{
 		// first pass: get length in utf8 characters
-        size_t size = as_utf8_begin(str, length);
+		size_t size = as_utf8_begin(str, length);
 
 		// allocate resulting string
 		std::string result;
@@ -1336,10 +1481,10 @@
 		// second pass: convert to utf8
 		if (size > 0) as_utf8_end(&result[0], size, str, length);
 
-	  	return result;
-    }
+		return result;
+	}
 
-	std::wstring as_wide_impl(const char* str, size_t size)
+	PUGI__FN std::basic_string<wchar_t> as_wide_impl(const char* str, size_t size)
 	{
 		const uint8_t* data = reinterpret_cast<const uint8_t*>(str);
 
@@ -1347,7 +1492,7 @@
 		size_t length = utf_decoder<wchar_counter>::decode_utf8_block(data, size, 0);
 
 		// allocate resulting string
-		std::wstring result;
+		std::basic_string<wchar_t> result;
 		result.resize(length);
 
 		// second pass: convert to wchar_t
@@ -1378,7 +1523,7 @@
 		return target_length >= length && (target_length < reuse_threshold || target_length - length < target_length / 2);
 	}
 
-	bool strcpy_insitu(char_t*& dest, uintptr_t& header, uintptr_t header_mask, const char_t* source)
+	PUGI__FN bool strcpy_insitu(char_t*& dest, uintptr_t& header, uintptr_t header_mask, const char_t* source)
 	{
 		size_t source_length = strlength(source);
 
@@ -1466,7 +1611,7 @@
 		}
 	};
 	
-	char_t* strconv_escape(char_t* s, gap& g)
+	PUGI__FN char_t* strconv_escape(char_t* s, gap& g)
 	{
 		char_t* stre = s + 1;
 
@@ -1530,6 +1675,7 @@
 				g.push(s, stre - s);
 				return stre;
 			}
+
 			case 'a':	// &a
 			{
 				++stre;
@@ -1558,6 +1704,7 @@
 				}
 				break;
 			}
+
 			case 'g': // &g
 			{
 				if (*++stre == 't' && *++stre == ';') // &gt;
@@ -1570,6 +1717,7 @@
 				}
 				break;
 			}
+
 			case 'l': // &l
 			{
 				if (*++stre == 't' && *++stre == ';') // &lt;
@@ -1582,6 +1730,7 @@
 				}
 				break;
 			}
+
 			case 'q': // &q
 			{
 				if (*++stre == 'u' && *++stre == 'o' && *++stre == 't' && *++stre == ';') // &quot;
@@ -1594,6 +1743,9 @@
 				}
 				break;
 			}
+
+			default:
+				break;
 		}
 		
 		return stre;
@@ -1602,13 +1754,13 @@
 	// Utility macro for last character handling
 	#define ENDSWITH(c, e) ((c) == (e) || ((c) == 0 && endch == (e)))
 
-	char_t* strconv_comment(char_t* s, char_t endch)
+	PUGI__FN char_t* strconv_comment(char_t* s, char_t endch)
 	{
 		gap g;
 		
 		while (true)
 		{
-			while (!IS_CHARTYPE(*s, ct_parse_comment)) ++s;
+			while (!PUGI__IS_CHARTYPE(*s, ct_parse_comment)) ++s;
 		
 			if (*s == '\r') // Either a single 0x0d or 0x0d 0x0a pair
 			{
@@ -1630,13 +1782,13 @@
 		}
 	}
 
-	char_t* strconv_cdata(char_t* s, char_t endch)
+	PUGI__FN char_t* strconv_cdata(char_t* s, char_t endch)
 	{
 		gap g;
 			
 		while (true)
 		{
-			while (!IS_CHARTYPE(*s, ct_parse_cdata)) ++s;
+			while (!PUGI__IS_CHARTYPE(*s, ct_parse_cdata)) ++s;
 			
 			if (*s == '\r') // Either a single 0x0d or 0x0d 0x0a pair
 			{
@@ -1668,7 +1820,7 @@
 			
 			while (true)
 			{
-				while (!IS_CHARTYPE(*s, ct_parse_pcdata)) ++s;
+				while (!PUGI__IS_CHARTYPE(*s, ct_parse_pcdata)) ++s;
 					
 				if (*s == '<') // PCDATA ends here
 				{
@@ -1695,9 +1847,9 @@
 		}
 	};
 	
-	strconv_pcdata_t get_strconv_pcdata(unsigned int optmask)
+	PUGI__FN strconv_pcdata_t get_strconv_pcdata(unsigned int optmask)
 	{
-		STATIC_ASSERT(parse_escapes == 0x10 && parse_eol == 0x20);
+		PUGI__STATIC_ASSERT(parse_escapes == 0x10 && parse_eol == 0x20);
 
 		switch ((optmask >> 4) & 3) // get bitmask for flags (eol escapes)
 		{
@@ -1718,37 +1870,37 @@
 			gap g;
 
 			// trim leading whitespaces
-			if (IS_CHARTYPE(*s, ct_space))
+			if (PUGI__IS_CHARTYPE(*s, ct_space))
 			{
 				char_t* str = s;
 				
 				do ++str;
-				while (IS_CHARTYPE(*str, ct_space));
+				while (PUGI__IS_CHARTYPE(*str, ct_space));
 				
 				g.push(s, str - s);
 			}
 
 			while (true)
 			{
-				while (!IS_CHARTYPE(*s, ct_parse_attr_ws | ct_space)) ++s;
+				while (!PUGI__IS_CHARTYPE(*s, ct_parse_attr_ws | ct_space)) ++s;
 				
 				if (*s == end_quote)
 				{
 					char_t* str = g.flush(s);
 					
 					do *str-- = 0;
-					while (IS_CHARTYPE(*str, ct_space));
+					while (PUGI__IS_CHARTYPE(*str, ct_space));
 				
 					return s + 1;
 				}
-				else if (IS_CHARTYPE(*s, ct_space))
+				else if (PUGI__IS_CHARTYPE(*s, ct_space))
 				{
 					*s++ = ' ';
 		
-					if (IS_CHARTYPE(*s, ct_space))
+					if (PUGI__IS_CHARTYPE(*s, ct_space))
 					{
 						char_t* str = s + 1;
-						while (IS_CHARTYPE(*str, ct_space)) ++str;
+						while (PUGI__IS_CHARTYPE(*str, ct_space)) ++str;
 						
 						g.push(s, str - s);
 					}
@@ -1771,7 +1923,7 @@
 
 			while (true)
 			{
-				while (!IS_CHARTYPE(*s, ct_parse_attr_ws)) ++s;
+				while (!PUGI__IS_CHARTYPE(*s, ct_parse_attr_ws)) ++s;
 				
 				if (*s == end_quote)
 				{
@@ -1779,7 +1931,7 @@
 				
 					return s + 1;
 				}
-				else if (IS_CHARTYPE(*s, ct_space))
+				else if (PUGI__IS_CHARTYPE(*s, ct_space))
 				{
 					if (*s == '\r')
 					{
@@ -1807,7 +1959,7 @@
 
 			while (true)
 			{
-				while (!IS_CHARTYPE(*s, ct_parse_attr)) ++s;
+				while (!PUGI__IS_CHARTYPE(*s, ct_parse_attr)) ++s;
 				
 				if (*s == end_quote)
 				{
@@ -1839,7 +1991,7 @@
 
 			while (true)
 			{
-				while (!IS_CHARTYPE(*s, ct_parse_attr)) ++s;
+				while (!PUGI__IS_CHARTYPE(*s, ct_parse_attr)) ++s;
 				
 				if (*s == end_quote)
 				{
@@ -1860,9 +2012,9 @@
 		}
 	};
 
-	strconv_attribute_t get_strconv_attribute(unsigned int optmask)
+	PUGI__FN strconv_attribute_t get_strconv_attribute(unsigned int optmask)
 	{
-		STATIC_ASSERT(parse_escapes == 0x10 && parse_eol == 0x20 && parse_wconv_attribute == 0x40 && parse_wnorm_attribute == 0x80);
+		PUGI__STATIC_ASSERT(parse_escapes == 0x10 && parse_eol == 0x20 && parse_wconv_attribute == 0x40 && parse_wnorm_attribute == 0x80);
 		
 		switch ((optmask >> 4) & 15) // get bitmask for flags (wconv wnorm eol escapes)
 		{
@@ -1899,20 +2051,20 @@
 	{
 		xml_allocator alloc;
 		char_t* error_offset;
-		jmp_buf error_handler;
+		xml_parse_status error_status;
 		
 		// Parser utilities.
-		#define SKIPWS()			{ while (IS_CHARTYPE(*s, ct_space)) ++s; }
-		#define OPTSET(OPT)			( optmsk & OPT )
-		#define PUSHNODE(TYPE)		{ cursor = append_node(cursor, alloc, TYPE); if (!cursor) THROW_ERROR(status_out_of_memory, s); }
-		#define POPNODE()			{ cursor = cursor->parent; }
-		#define SCANFOR(X)			{ while (*s != 0 && !(X)) ++s; }
-		#define SCANWHILE(X)		{ while ((X)) ++s; }
-		#define ENDSEG()			{ ch = *s; *s = 0; ++s; }
-		#define THROW_ERROR(err, m)	error_offset = m, longjmp(error_handler, err)
-		#define CHECK_ERROR(err, m)	{ if (*s == 0) THROW_ERROR(err, m); }
+		#define PUGI__SKIPWS()			{ while (PUGI__IS_CHARTYPE(*s, ct_space)) ++s; }
+		#define PUGI__OPTSET(OPT)			( optmsk & (OPT) )
+		#define PUGI__PUSHNODE(TYPE)		{ cursor = append_node(cursor, alloc, TYPE); if (!cursor) PUGI__THROW_ERROR(status_out_of_memory, s); }
+		#define PUGI__POPNODE()			{ cursor = cursor->parent; }
+		#define PUGI__SCANFOR(X)			{ while (*s != 0 && !(X)) ++s; }
+		#define PUGI__SCANWHILE(X)		{ while ((X)) ++s; }
+		#define PUGI__ENDSEG()			{ ch = *s; *s = 0; ++s; }
+		#define PUGI__THROW_ERROR(err, m)	return error_offset = m, error_status = err, static_cast<char_t*>(0)
+		#define PUGI__CHECK_ERROR(err, m)	{ if (*s == 0) PUGI__THROW_ERROR(err, m); }
 		
-		xml_parser(const xml_allocator& alloc): alloc(alloc), error_offset(0)
+		xml_parser(const xml_allocator& alloc_): alloc(alloc_), error_offset(0), error_status(status_ok)
 		{
 		}
 
@@ -1929,8 +2081,8 @@
 			{
 				// quoted string
 				char_t ch = *s++;
-				SCANFOR(*s == ch);
-				if (!*s) THROW_ERROR(status_bad_doctype, s);
+				PUGI__SCANFOR(*s == ch);
+				if (!*s) PUGI__THROW_ERROR(status_bad_doctype, s);
 
 				s++;
 			}
@@ -1938,20 +2090,20 @@
 			{
 				// <? ... ?>
 				s += 2;
-				SCANFOR(s[0] == '?' && s[1] == '>'); // no need for ENDSWITH because ?> can't terminate proper doctype
-				if (!*s) THROW_ERROR(status_bad_doctype, s);
+				PUGI__SCANFOR(s[0] == '?' && s[1] == '>'); // no need for ENDSWITH because ?> can't terminate proper doctype
+				if (!*s) PUGI__THROW_ERROR(status_bad_doctype, s);
 
 				s += 2;
 			}
 			else if (s[0] == '<' && s[1] == '!' && s[2] == '-' && s[3] == '-')
 			{
 				s += 4;
-				SCANFOR(s[0] == '-' && s[1] == '-' && s[2] == '>'); // no need for ENDSWITH because --> can't terminate proper doctype
-				if (!*s) THROW_ERROR(status_bad_doctype, s);
+				PUGI__SCANFOR(s[0] == '-' && s[1] == '-' && s[2] == '>'); // no need for ENDSWITH because --> can't terminate proper doctype
+				if (!*s) PUGI__THROW_ERROR(status_bad_doctype, s);
 
 				s += 4;
 			}
-			else THROW_ERROR(status_bad_doctype, s);
+			else PUGI__THROW_ERROR(status_bad_doctype, s);
 
 			return s;
 		}
@@ -1967,6 +2119,7 @@
 				{
 					// nested ignore section
 					s = parse_doctype_ignore(s);
+					if (!s) return s;
 				}
 				else if (s[0] == ']' && s[1] == ']' && s[2] == '>')
 				{
@@ -1978,9 +2131,7 @@
 				else s++;
 			}
 
-			THROW_ERROR(status_bad_doctype, s);
-
-			return s;
+			PUGI__THROW_ERROR(status_bad_doctype, s);
 		}
 
 		char_t* parse_doctype_group(char_t* s, char_t endch, bool toplevel)
@@ -1996,17 +2147,20 @@
 					{
 						// ignore
 						s = parse_doctype_ignore(s);
+						if (!s) return s;
 					}
 					else
 					{
 						// some control group
 						s = parse_doctype_group(s, endch, false);
+						if (!s) return s;
 					}
 				}
 				else if (s[0] == '<' || s[0] == '"' || s[0] == '\'')
 				{
 					// unknown tag (forbidden), or some primitive group
 					s = parse_doctype_primitive(s);
+					if (!s) return s;
 				}
 				else if (*s == '>')
 				{
@@ -2017,7 +2171,7 @@
 				else s++;
 			}
 
-			if (!toplevel || endch != '>') THROW_ERROR(status_bad_doctype, s);
+			if (!toplevel || endch != '>') PUGI__THROW_ERROR(status_bad_doctype, s);
 
 			return s;
 		}
@@ -2035,31 +2189,31 @@
 				{
 					++s;
 
-					if (OPTSET(parse_comments))
+					if (PUGI__OPTSET(parse_comments))
 					{
-						PUSHNODE(node_comment); // Append a new node on the tree.
+						PUGI__PUSHNODE(node_comment); // Append a new node on the tree.
 						cursor->value = s; // Save the offset.
 					}
 
-					if (OPTSET(parse_eol) && OPTSET(parse_comments))
+					if (PUGI__OPTSET(parse_eol) && PUGI__OPTSET(parse_comments))
 					{
 						s = strconv_comment(s, endch);
 
-						if (!s) THROW_ERROR(status_bad_comment, cursor->value);
+						if (!s) PUGI__THROW_ERROR(status_bad_comment, cursor->value);
 					}
 					else
 					{
 						// Scan for terminating '-->'.
-						SCANFOR(s[0] == '-' && s[1] == '-' && ENDSWITH(s[2], '>'));
-						CHECK_ERROR(status_bad_comment, s);
+						PUGI__SCANFOR(s[0] == '-' && s[1] == '-' && ENDSWITH(s[2], '>'));
+						PUGI__CHECK_ERROR(status_bad_comment, s);
 
-						if (OPTSET(parse_comments))
+						if (PUGI__OPTSET(parse_comments))
 							*s = 0; // Zero-terminate this segment at the first terminating '-'.
 
 						s += (s[2] == '>' ? 3 : 2); // Step over the '\0->'.
 					}
 				}
-				else THROW_ERROR(status_bad_comment, s);
+				else PUGI__THROW_ERROR(status_bad_comment, s);
 			}
 			else if (*s == '[')
 			{
@@ -2068,22 +2222,22 @@
 				{
 					++s;
 
-					if (OPTSET(parse_cdata))
+					if (PUGI__OPTSET(parse_cdata))
 					{
-						PUSHNODE(node_cdata); // Append a new node on the tree.
+						PUGI__PUSHNODE(node_cdata); // Append a new node on the tree.
 						cursor->value = s; // Save the offset.
 
-						if (OPTSET(parse_eol))
+						if (PUGI__OPTSET(parse_eol))
 						{
 							s = strconv_cdata(s, endch);
 
-							if (!s) THROW_ERROR(status_bad_cdata, cursor->value);
+							if (!s) PUGI__THROW_ERROR(status_bad_cdata, cursor->value);
 						}
 						else
 						{
 							// Scan for terminating ']]>'.
-							SCANFOR(s[0] == ']' && s[1] == ']' && ENDSWITH(s[2], '>'));
-							CHECK_ERROR(status_bad_cdata, s);
+							PUGI__SCANFOR(s[0] == ']' && s[1] == ']' && ENDSWITH(s[2], '>'));
+							PUGI__CHECK_ERROR(status_bad_cdata, s);
 
 							*s++ = 0; // Zero-terminate this segment.
 						}
@@ -2091,43 +2245,44 @@
 					else // Flagged for discard, but we still have to scan for the terminator.
 					{
 						// Scan for terminating ']]>'.
-						SCANFOR(s[0] == ']' && s[1] == ']' && ENDSWITH(s[2], '>'));
-						CHECK_ERROR(status_bad_cdata, s);
+						PUGI__SCANFOR(s[0] == ']' && s[1] == ']' && ENDSWITH(s[2], '>'));
+						PUGI__CHECK_ERROR(status_bad_cdata, s);
 
 						++s;
 					}
 
 					s += (s[1] == '>' ? 2 : 1); // Step over the last ']>'.
 				}
-				else THROW_ERROR(status_bad_cdata, s);
+				else PUGI__THROW_ERROR(status_bad_cdata, s);
 			}
 			else if (s[0] == 'D' && s[1] == 'O' && s[2] == 'C' && s[3] == 'T' && s[4] == 'Y' && s[5] == 'P' && ENDSWITH(s[6], 'E'))
 			{
 				s -= 2;
 
-                if (cursor->parent) THROW_ERROR(status_bad_doctype, s);
+				if (cursor->parent) PUGI__THROW_ERROR(status_bad_doctype, s);
 
-                char_t* mark = s + 9;
+				char_t* mark = s + 9;
 
 				s = parse_doctype_group(s, endch, true);
+				if (!s) return s;
 
-                if (OPTSET(parse_doctype))
-                {
-                    while (IS_CHARTYPE(*mark, ct_space)) ++mark;
+				if (PUGI__OPTSET(parse_doctype))
+				{
+					while (PUGI__IS_CHARTYPE(*mark, ct_space)) ++mark;
 
-                    PUSHNODE(node_doctype);
+					PUGI__PUSHNODE(node_doctype);
 
-                    cursor->value = mark;
+					cursor->value = mark;
 
-                    assert((s[0] == 0 && endch == '>') || s[-1] == '>');
-                    s[*s == 0 ? 0 : -1] = 0;
+					assert((s[0] == 0 && endch == '>') || s[-1] == '>');
+					s[*s == 0 ? 0 : -1] = 0;
 
-                    POPNODE();
-                }
+					PUGI__POPNODE();
+				}
 			}
-			else if (*s == 0 && endch == '-') THROW_ERROR(status_bad_comment, s);
-			else if (*s == 0 && endch == '[') THROW_ERROR(status_bad_cdata, s);
-			else THROW_ERROR(status_unrecognized_tag, s);
+			else if (*s == 0 && endch == '-') PUGI__THROW_ERROR(status_bad_comment, s);
+			else if (*s == 0 && endch == '[') PUGI__THROW_ERROR(status_bad_cdata, s);
+			else PUGI__THROW_ERROR(status_unrecognized_tag, s);
 
 			return s;
 		}
@@ -2144,50 +2299,50 @@
 			// read PI target
 			char_t* target = s;
 
-			if (!IS_CHARTYPE(*s, ct_start_symbol)) THROW_ERROR(status_bad_pi, s);
+			if (!PUGI__IS_CHARTYPE(*s, ct_start_symbol)) PUGI__THROW_ERROR(status_bad_pi, s);
 
-			SCANWHILE(IS_CHARTYPE(*s, ct_symbol));
-			CHECK_ERROR(status_bad_pi, s);
+			PUGI__SCANWHILE(PUGI__IS_CHARTYPE(*s, ct_symbol));
+			PUGI__CHECK_ERROR(status_bad_pi, s);
 
 			// determine node type; stricmp / strcasecmp is not portable
 			bool declaration = (target[0] | ' ') == 'x' && (target[1] | ' ') == 'm' && (target[2] | ' ') == 'l' && target + 3 == s;
 
-			if (declaration ? OPTSET(parse_declaration) : OPTSET(parse_pi))
+			if (declaration ? PUGI__OPTSET(parse_declaration) : PUGI__OPTSET(parse_pi))
 			{
 				if (declaration)
 				{
 					// disallow non top-level declarations
-					if (cursor->parent) THROW_ERROR(status_bad_pi, s);
+					if (cursor->parent) PUGI__THROW_ERROR(status_bad_pi, s);
 
-					PUSHNODE(node_declaration);
+					PUGI__PUSHNODE(node_declaration);
 				}
 				else
 				{
-					PUSHNODE(node_pi);
+					PUGI__PUSHNODE(node_pi);
 				}
 
 				cursor->name = target;
 
-				ENDSEG();
+				PUGI__ENDSEG();
 
 				// parse value/attributes
 				if (ch == '?')
 				{
 					// empty node
-					if (!ENDSWITH(*s, '>')) THROW_ERROR(status_bad_pi, s);
+					if (!ENDSWITH(*s, '>')) PUGI__THROW_ERROR(status_bad_pi, s);
 					s += (*s == '>');
 
-					POPNODE();
+					PUGI__POPNODE();
 				}
-				else if (IS_CHARTYPE(ch, ct_space))
+				else if (PUGI__IS_CHARTYPE(ch, ct_space))
 				{
-					SKIPWS();
+					PUGI__SKIPWS();
 
 					// scan for tag end
 					char_t* value = s;
 
-					SCANFOR(s[0] == '?' && ENDSWITH(s[1], '>'));
-					CHECK_ERROR(status_bad_pi, s);
+					PUGI__SCANFOR(s[0] == '?' && ENDSWITH(s[1], '>'));
+					PUGI__CHECK_ERROR(status_bad_pi, s);
 
 					if (declaration)
 					{
@@ -2201,20 +2356,20 @@
 					{
 						// store value and step over >
 						cursor->value = value;
-						POPNODE();
+						PUGI__POPNODE();
 
-						ENDSEG();
+						PUGI__ENDSEG();
 
 						s += (*s == '>');
 					}
 				}
-				else THROW_ERROR(status_bad_pi, s);
+				else PUGI__THROW_ERROR(status_bad_pi, s);
 			}
 			else
 			{
 				// scan for tag end
-				SCANFOR(s[0] == '?' && ENDSWITH(s[1], '>'));
-				CHECK_ERROR(status_bad_pi, s);
+				PUGI__SCANFOR(s[0] == '?' && ENDSWITH(s[1], '>'));
+				PUGI__CHECK_ERROR(status_bad_pi, s);
 
 				s += (s[1] == '>' ? 2 : 1);
 			}
@@ -2225,7 +2380,7 @@
 			return s;
 		}
 
-		void parse(char_t* s, xml_node_struct* xmldoc, unsigned int optmsk, char_t endch)
+		char_t* parse(char_t* s, xml_node_struct* xmldoc, unsigned int optmsk, char_t endch)
 		{
 			strconv_attribute_t strconv_attribute = get_strconv_attribute(optmsk);
 			strconv_pcdata_t strconv_pcdata = get_strconv_pcdata(optmsk);
@@ -2241,43 +2396,43 @@
 					++s;
 
 				LOC_TAG:
-					if (IS_CHARTYPE(*s, ct_start_symbol)) // '<#...'
+					if (PUGI__IS_CHARTYPE(*s, ct_start_symbol)) // '<#...'
 					{
-						PUSHNODE(node_element); // Append a new node to the tree.
+						PUGI__PUSHNODE(node_element); // Append a new node to the tree.
 
 						cursor->name = s;
 
-						SCANWHILE(IS_CHARTYPE(*s, ct_symbol)); // Scan for a terminator.
-						ENDSEG(); // Save char in 'ch', terminate & step over.
+						PUGI__SCANWHILE(PUGI__IS_CHARTYPE(*s, ct_symbol)); // Scan for a terminator.
+						PUGI__ENDSEG(); // Save char in 'ch', terminate & step over.
 
 						if (ch == '>')
 						{
 							// end of tag
 						}
-						else if (IS_CHARTYPE(ch, ct_space))
+						else if (PUGI__IS_CHARTYPE(ch, ct_space))
 						{
 						LOC_ATTRIBUTES:
-						    while (true)
-						    {
-								SKIPWS(); // Eat any whitespace.
+							while (true)
+							{
+								PUGI__SKIPWS(); // Eat any whitespace.
 						
-								if (IS_CHARTYPE(*s, ct_start_symbol)) // <... #...
+								if (PUGI__IS_CHARTYPE(*s, ct_start_symbol)) // <... #...
 								{
 									xml_attribute_struct* a = append_attribute_ll(cursor, alloc); // Make space for this attribute.
-									if (!a) THROW_ERROR(status_out_of_memory, s);
+									if (!a) PUGI__THROW_ERROR(status_out_of_memory, s);
 
 									a->name = s; // Save the offset.
 
-									SCANWHILE(IS_CHARTYPE(*s, ct_symbol)); // Scan for a terminator.
-									CHECK_ERROR(status_bad_attribute, s); //$ redundant, left for performance
+									PUGI__SCANWHILE(PUGI__IS_CHARTYPE(*s, ct_symbol)); // Scan for a terminator.
+									PUGI__CHECK_ERROR(status_bad_attribute, s); //$ redundant, left for performance
 
-									ENDSEG(); // Save char in 'ch', terminate & step over.
-									CHECK_ERROR(status_bad_attribute, s); //$ redundant, left for performance
+									PUGI__ENDSEG(); // Save char in 'ch', terminate & step over.
+									PUGI__CHECK_ERROR(status_bad_attribute, s); //$ redundant, left for performance
 
-									if (IS_CHARTYPE(ch, ct_space))
+									if (PUGI__IS_CHARTYPE(ch, ct_space))
 									{
-										SKIPWS(); // Eat any whitespace.
-										CHECK_ERROR(status_bad_attribute, s); //$ redundant, left for performance
+										PUGI__SKIPWS(); // Eat any whitespace.
+										PUGI__CHECK_ERROR(status_bad_attribute, s); //$ redundant, left for performance
 
 										ch = *s;
 										++s;
@@ -2285,7 +2440,7 @@
 									
 									if (ch == '=') // '<... #=...'
 									{
-										SKIPWS(); // Eat any whitespace.
+										PUGI__SKIPWS(); // Eat any whitespace.
 
 										if (*s == '"' || *s == '\'') // '<... #="...'
 										{
@@ -2295,16 +2450,16 @@
 
 											s = strconv_attribute(s, ch);
 										
-											if (!s) THROW_ERROR(status_bad_attribute, a->value);
+											if (!s) PUGI__THROW_ERROR(status_bad_attribute, a->value);
 
 											// After this line the loop continues from the start;
 											// Whitespaces, / and > are ok, symbols and EOF are wrong,
 											// everything else will be detected
-											if (IS_CHARTYPE(*s, ct_start_symbol)) THROW_ERROR(status_bad_attribute, s);
+											if (PUGI__IS_CHARTYPE(*s, ct_start_symbol)) PUGI__THROW_ERROR(status_bad_attribute, s);
 										}
-										else THROW_ERROR(status_bad_attribute, s);
+										else PUGI__THROW_ERROR(status_bad_attribute, s);
 									}
-									else THROW_ERROR(status_bad_attribute, s);
+									else PUGI__THROW_ERROR(status_bad_attribute, s);
 								}
 								else if (*s == '/')
 								{
@@ -2312,16 +2467,16 @@
 									
 									if (*s == '>')
 									{
-										POPNODE();
+										PUGI__POPNODE();
 										s++;
 										break;
 									}
 									else if (*s == 0 && endch == '>')
 									{
-										POPNODE();
+										PUGI__POPNODE();
 										break;
 									}
-									else THROW_ERROR(status_bad_start_element, s);
+									else PUGI__THROW_ERROR(status_bad_start_element, s);
 								}
 								else if (*s == '>')
 								{
@@ -2333,16 +2488,16 @@
 								{
 									break;
 								}
-								else THROW_ERROR(status_bad_start_element, s);
+								else PUGI__THROW_ERROR(status_bad_start_element, s);
 							}
 
 							// !!!
 						}
 						else if (ch == '/') // '<#.../'
 						{
-							if (!ENDSWITH(*s, '>')) THROW_ERROR(status_bad_start_element, s);
+							if (!ENDSWITH(*s, '>')) PUGI__THROW_ERROR(status_bad_start_element, s);
 
-							POPNODE(); // Pop.
+							PUGI__POPNODE(); // Pop.
 
 							s += (*s == '>');
 						}
@@ -2351,45 +2506,46 @@
 							// we stepped over null terminator, backtrack & handle closing tag
 							--s;
 							
-							if (endch != '>') THROW_ERROR(status_bad_start_element, s);
+							if (endch != '>') PUGI__THROW_ERROR(status_bad_start_element, s);
 						}
-						else THROW_ERROR(status_bad_start_element, s);
+						else PUGI__THROW_ERROR(status_bad_start_element, s);
 					}
 					else if (*s == '/')
 					{
 						++s;
 
 						char_t* name = cursor->name;
-						if (!name) THROW_ERROR(status_end_element_mismatch, s);
+						if (!name) PUGI__THROW_ERROR(status_end_element_mismatch, s);
 						
-						while (IS_CHARTYPE(*s, ct_symbol))
+						while (PUGI__IS_CHARTYPE(*s, ct_symbol))
 						{
-							if (*s++ != *name++) THROW_ERROR(status_end_element_mismatch, s);
+							if (*s++ != *name++) PUGI__THROW_ERROR(status_end_element_mismatch, s);
 						}
 
 						if (*name)
 						{
-							if (*s == 0 && name[0] == endch && name[1] == 0) THROW_ERROR(status_bad_end_element, s);
-							else THROW_ERROR(status_end_element_mismatch, s);
+							if (*s == 0 && name[0] == endch && name[1] == 0) PUGI__THROW_ERROR(status_bad_end_element, s);
+							else PUGI__THROW_ERROR(status_end_element_mismatch, s);
 						}
 							
-						POPNODE(); // Pop.
+						PUGI__POPNODE(); // Pop.
 
-						SKIPWS();
+						PUGI__SKIPWS();
 
 						if (*s == 0)
 						{
-							if (endch != '>') THROW_ERROR(status_bad_end_element, s);
+							if (endch != '>') PUGI__THROW_ERROR(status_bad_end_element, s);
 						}
 						else
 						{
-							if (*s != '>') THROW_ERROR(status_bad_end_element, s);
+							if (*s != '>') PUGI__THROW_ERROR(status_bad_end_element, s);
 							++s;
 						}
 					}
 					else if (*s == '?') // '<?...'
 					{
 						s = parse_question(s, cursor, optmsk, endch);
+						if (!s) return s;
 
 						assert(cursor);
 						if ((cursor->header & xml_memory_page_type_mask) + 1 == node_declaration) goto LOC_ATTRIBUTES;
@@ -2397,37 +2553,48 @@
 					else if (*s == '!') // '<!...'
 					{
 						s = parse_exclamation(s, cursor, optmsk, endch);
+						if (!s) return s;
 					}
-					else if (*s == 0 && endch == '?') THROW_ERROR(status_bad_pi, s);
-					else THROW_ERROR(status_unrecognized_tag, s);
+					else if (*s == 0 && endch == '?') PUGI__THROW_ERROR(status_bad_pi, s);
+					else PUGI__THROW_ERROR(status_unrecognized_tag, s);
 				}
 				else
 				{
 					mark = s; // Save this offset while searching for a terminator.
 
-					SKIPWS(); // Eat whitespace if no genuine PCDATA here.
+					PUGI__SKIPWS(); // Eat whitespace if no genuine PCDATA here.
 
-					if ((!OPTSET(parse_ws_pcdata) || mark == s) && (*s == '<' || !*s))
+					if (*s == '<')
 					{
-						continue;
+						// We skipped some whitespace characters because otherwise we would take the tag branch instead of PCDATA one
+						assert(mark != s);
+
+						if (!PUGI__OPTSET(parse_ws_pcdata | parse_ws_pcdata_single))
+						{
+							continue;
+						}
+						else if (PUGI__OPTSET(parse_ws_pcdata_single))
+						{
+							if (s[1] != '/' || cursor->first_child) continue;
+						}
 					}
 
 					s = mark;
 							
 					if (cursor->parent)
 					{
-						PUSHNODE(node_pcdata); // Append a new node on the tree.
+						PUGI__PUSHNODE(node_pcdata); // Append a new node on the tree.
 						cursor->value = s; // Save the offset.
 
 						s = strconv_pcdata(s);
 								
-						POPNODE(); // Pop since this is a standalone.
+						PUGI__POPNODE(); // Pop since this is a standalone.
 						
 						if (!*s) break;
 					}
 					else
 					{
-						SCANFOR(*s == '<'); // '...<'
+						PUGI__SCANFOR(*s == '<'); // '...<'
 						if (!*s) break;
 						
 						++s;
@@ -2439,7 +2606,9 @@
 			}
 
 			// check that last tag is closed
-			if (cursor != xmldoc) THROW_ERROR(status_end_element_mismatch, s);
+			if (cursor != xmldoc) PUGI__THROW_ERROR(status_end_element_mismatch, s);
+
+			return s;
 		}
 
 		static xml_parse_result parse(char_t* buffer, size_t length, xml_node_struct* root, unsigned int optmsk)
@@ -2460,14 +2629,9 @@
 			buffer[length - 1] = 0;
 			
 			// perform actual parsing
-			int error = setjmp(parser.error_handler);
-
-			if (error == 0)
-			{
-				parser.parse(buffer, xmldoc, optmsk, endch);
-			}
+			parser.parse(buffer, xmldoc, optmsk, endch);
 
-			xml_parse_result result = make_parse_result(static_cast<xml_parse_status>(error), parser.error_offset ? parser.error_offset - buffer : 0);
+			xml_parse_result result = make_parse_result(parser.error_status, parser.error_offset ? parser.error_offset - buffer : 0);
 			assert(result.offset >= 0 && static_cast<size_t>(result.offset) <= length);
 
 			// update allocator state
@@ -2485,7 +2649,7 @@
 	};
 
 	// Output facilities
-	xml_encoding get_write_native_encoding()
+	PUGI__FN xml_encoding get_write_native_encoding()
 	{
 	#ifdef PUGIXML_WCHAR_MODE
 		return get_wchar_encoding();
@@ -2494,7 +2658,7 @@
 	#endif
 	}
 
-	xml_encoding get_write_encoding(xml_encoding encoding)
+	PUGI__FN xml_encoding get_write_encoding(xml_encoding encoding)
 	{
 		// replace wchar encoding with utf implementation
 		if (encoding == encoding_wchar) return get_wchar_encoding();
@@ -2513,20 +2677,20 @@
 	}
 
 #ifdef PUGIXML_WCHAR_MODE
-	size_t get_valid_length(const char_t* data, size_t length)
+	PUGI__FN size_t get_valid_length(const char_t* data, size_t length)
 	{
 		assert(length > 0);
 
 		// discard last character if it's the lead of a surrogate pair 
-		return (sizeof(wchar_t) == 2 && (unsigned)(static_cast<uint16_t>(data[length - 1]) - 0xD800) < 0x400) ? length - 1 : length;
+		return (sizeof(wchar_t) == 2 && static_cast<unsigned int>(static_cast<uint16_t>(data[length - 1]) - 0xD800) < 0x400) ? length - 1 : length;
 	}
 
-	size_t convert_buffer(char* result, const char_t* data, size_t length, xml_encoding encoding)
+	PUGI__FN size_t convert_buffer(char_t* r_char, uint8_t* r_u8, uint16_t* r_u16, uint32_t* r_u32, const char_t* data, size_t length, xml_encoding encoding)
 	{
 		// only endian-swapping is required
 		if (need_endian_swap_utf(encoding, get_wchar_encoding()))
 		{
-			convert_wchar_endian_swap(reinterpret_cast<char_t*>(result), data, length);
+			convert_wchar_endian_swap(r_char, data, length);
 
 			return length * sizeof(char_t);
 		}
@@ -2534,11 +2698,8 @@
 		// convert to utf8
 		if (encoding == encoding_utf8)
 		{
-			uint8_t* dest = reinterpret_cast<uint8_t*>(result);
-
-			uint8_t* end = sizeof(wchar_t) == 2 ?
-				utf_decoder<utf8_writer>::decode_utf16_block(reinterpret_cast<const uint16_t*>(data), length, dest) :
-				utf_decoder<utf8_writer>::decode_utf32_block(reinterpret_cast<const uint32_t*>(data), length, dest);
+			uint8_t* dest = r_u8;
+			uint8_t* end = utf_decoder<utf8_writer>::decode_wchar_block(data, length, dest);
 
 			return static_cast<size_t>(end - dest);
 		}
@@ -2546,10 +2707,10 @@
 		// convert to utf16
 		if (encoding == encoding_utf16_be || encoding == encoding_utf16_le)
 		{
-			uint16_t* dest = reinterpret_cast<uint16_t*>(result);
+			uint16_t* dest = r_u16;
 
 			// convert to native utf16
-			uint16_t* end = utf_decoder<utf16_writer>::decode_utf32_block(reinterpret_cast<const uint32_t*>(data), length, dest);
+			uint16_t* end = utf_decoder<utf16_writer>::decode_wchar_block(data, length, dest);
 
 			// swap if necessary
 			xml_encoding native_encoding = is_little_endian() ? encoding_utf16_le : encoding_utf16_be;
@@ -2562,10 +2723,10 @@
 		// convert to utf32
 		if (encoding == encoding_utf32_be || encoding == encoding_utf32_le)
 		{
-			uint32_t* dest = reinterpret_cast<uint32_t*>(result);
+			uint32_t* dest = r_u32;
 
 			// convert to native utf32
-			uint32_t* end = utf_decoder<utf32_writer>::decode_utf16_block(reinterpret_cast<const uint16_t*>(data), length, dest);
+			uint32_t* end = utf_decoder<utf32_writer>::decode_wchar_block(data, length, dest);
 
 			// swap if necessary
 			xml_encoding native_encoding = is_little_endian() ? encoding_utf32_le : encoding_utf32_be;
@@ -2575,11 +2736,20 @@
 			return static_cast<size_t>(end - dest) * sizeof(uint32_t);
 		}
 
+		// convert to latin1
+		if (encoding == encoding_latin1)
+		{
+			uint8_t* dest = r_u8;
+			uint8_t* end = utf_decoder<latin1_writer>::decode_wchar_block(data, length, dest);
+
+			return static_cast<size_t>(end - dest);
+		}
+
 		assert(!"Invalid encoding");
 		return 0;
 	}
 #else
-	size_t get_valid_length(const char_t* data, size_t length)
+	PUGI__FN size_t get_valid_length(const char_t* data, size_t length)
 	{
 		assert(length > 4);
 
@@ -2595,11 +2765,11 @@
 		return length;
 	}
 
-	size_t convert_buffer(char* result, const char_t* data, size_t length, xml_encoding encoding)
+	PUGI__FN size_t convert_buffer(char_t* /* r_char */, uint8_t* r_u8, uint16_t* r_u16, uint32_t* r_u32, const char_t* data, size_t length, xml_encoding encoding)
 	{
 		if (encoding == encoding_utf16_be || encoding == encoding_utf16_le)
 		{
-			uint16_t* dest = reinterpret_cast<uint16_t*>(result);
+			uint16_t* dest = r_u16;
 
 			// convert to native utf16
 			uint16_t* end = utf_decoder<utf16_writer>::decode_utf8_block(reinterpret_cast<const uint8_t*>(data), length, dest);
@@ -2614,7 +2784,7 @@
 
 		if (encoding == encoding_utf32_be || encoding == encoding_utf32_le)
 		{
-			uint32_t* dest = reinterpret_cast<uint32_t*>(result);
+			uint32_t* dest = r_u32;
 
 			// convert to native utf32
 			uint32_t* end = utf_decoder<utf32_writer>::decode_utf8_block(reinterpret_cast<const uint8_t*>(data), length, dest);
@@ -2627,6 +2797,14 @@
 			return static_cast<size_t>(end - dest) * sizeof(uint32_t);
 		}
 
+		if (encoding == encoding_latin1)
+		{
+			uint8_t* dest = r_u8;
+			uint8_t* end = utf_decoder<latin1_writer>::decode_utf8_block(reinterpret_cast<const uint8_t*>(data), length, dest);
+
+			return static_cast<size_t>(end - dest);
+		}
+
 		assert(!"Invalid encoding");
 		return 0;
 	}
@@ -2638,8 +2816,9 @@
 		xml_buffered_writer& operator=(const xml_buffered_writer&);
 
 	public:
-		xml_buffered_writer(xml_writer& writer, xml_encoding user_encoding): writer(writer), bufsize(0), encoding(get_write_encoding(user_encoding))
+		xml_buffered_writer(xml_writer& writer_, xml_encoding user_encoding): writer(writer_), bufsize(0), encoding(get_write_encoding(user_encoding))
 		{
+			PUGI__STATIC_ASSERT(bufcapacity >= 8);
 		}
 
 		~xml_buffered_writer()
@@ -2663,11 +2842,11 @@
 			else
 			{
 				// convert chunk
-				size_t result = convert_buffer(scratch, data, size, encoding);
+				size_t result = convert_buffer(scratch.data_char, scratch.data_u8, scratch.data_u16, scratch.data_u32, data, size, encoding);
 				assert(result <= sizeof(scratch));
 
 				// write data
-				writer.write(scratch, result);
+				writer.write(scratch.data_u8, result);
 			}
 		}
 
@@ -2783,53 +2962,41 @@
 		// utf8 maximum expansion: x4 (-> utf32)
 		// utf16 maximum expansion: x2 (-> utf32)
 		// utf32 maximum expansion: x1
-		enum { bufcapacity = 2048 };
+		enum
+		{
+			bufcapacitybytes =
+			#ifdef PUGIXML_MEMORY_OUTPUT_STACK
+				PUGIXML_MEMORY_OUTPUT_STACK
+			#else
+				10240
+			#endif
+			,
+			bufcapacity = bufcapacitybytes / (sizeof(char_t) + 4)
+		};
 
 		char_t buffer[bufcapacity];
-		char scratch[4 * bufcapacity];
+
+		union
+		{
+			uint8_t data_u8[4 * bufcapacity];
+			uint16_t data_u16[2 * bufcapacity];
+			uint32_t data_u32[bufcapacity];
+			char_t data_char[bufcapacity];
+		} scratch;
 
 		xml_writer& writer;
 		size_t bufsize;
 		xml_encoding encoding;
 	};
 
-	void write_bom(xml_writer& writer, xml_encoding encoding)
-	{
-		switch (encoding)
-		{
-		case encoding_utf8:
-			writer.write("\xef\xbb\xbf", 3);
-			break;
-
-		case encoding_utf16_be:
-			writer.write("\xfe\xff", 2);
-			break;
-
-		case encoding_utf16_le:
-			writer.write("\xff\xfe", 2);
-			break;
-
-		case encoding_utf32_be:
-			writer.write("\x00\x00\xfe\xff", 4);
-			break;
-
-		case encoding_utf32_le:
-			writer.write("\xff\xfe\x00\x00", 4);
-			break;
-
-		default:
-			assert(!"Invalid encoding");
-		}
-	}
-
-	void text_output_escaped(xml_buffered_writer& writer, const char_t* s, chartypex_t type)
+	PUGI__FN void text_output_escaped(xml_buffered_writer& writer, const char_t* s, chartypex_t type)
 	{
 		while (*s)
 		{
 			const char_t* prev = s;
 			
 			// While *s is a usual symbol
-			while (!IS_CHARTYPEX(*s, type)) ++s;
+			while (!PUGI__IS_CHARTYPEX(*s, type)) ++s;
 		
 			writer.write(prev, static_cast<size_t>(s - prev));
 
@@ -2863,7 +3030,15 @@
 		}
 	}
 
-	void text_output_cdata(xml_buffered_writer& writer, const char_t* s)
+	PUGI__FN void text_output(xml_buffered_writer& writer, const char_t* s, chartypex_t type, unsigned int flags)
+	{
+		if (flags & format_no_escapes)
+			writer.write(s);
+		else
+			text_output_escaped(writer, s, type);
+	}
+
+	PUGI__FN void text_output_cdata(xml_buffered_writer& writer, const char_t* s)
 	{
 		do
 		{
@@ -2885,7 +3060,7 @@
 		while (*s);
 	}
 
-	void node_output_attributes(xml_buffered_writer& writer, const xml_node& node)
+	PUGI__FN void node_output_attributes(xml_buffered_writer& writer, const xml_node& node, unsigned int flags)
 	{
 		const char_t* default_name = PUGIXML_TEXT(":anonymous");
 
@@ -2895,13 +3070,13 @@
 			writer.write(a.name()[0] ? a.name() : default_name);
 			writer.write('=', '"');
 
-			text_output_escaped(writer, a.value(), ctx_special_attr);
+			text_output(writer, a.value(), ctx_special_attr, flags);
 
 			writer.write('"');
 		}
 	}
 
-	void node_output(xml_buffered_writer& writer, const xml_node& node, const char_t* indent, unsigned int flags, unsigned int depth)
+	PUGI__FN void node_output(xml_buffered_writer& writer, const xml_node& node, const char_t* indent, unsigned int flags, unsigned int depth)
 	{
 		const char_t* default_name = PUGIXML_TEXT(":anonymous");
 
@@ -2924,7 +3099,7 @@
 			writer.write('<');
 			writer.write(name);
 
-			node_output_attributes(writer, node);
+			node_output_attributes(writer, node, flags);
 
 			if (flags & format_raw)
 			{
@@ -2948,10 +3123,10 @@
 			{
 				writer.write('>');
 
-                if (node.first_child().type() == node_pcdata)
-                    text_output_escaped(writer, node.first_child().value(), ctx_special_pcdata);
-                else
-                    text_output_cdata(writer, node.first_child().value());
+				if (node.first_child().type() == node_pcdata)
+					text_output(writer, node.first_child().value(), ctx_special_pcdata, flags);
+				else
+					text_output_cdata(writer, node.first_child().value());
 
 				writer.write('<', '/');
 				writer.write(name);
@@ -2976,7 +3151,7 @@
 		}
 		
 		case node_pcdata:
-			text_output_escaped(writer, node.value(), ctx_special_pcdata);
+			text_output(writer, node.value(), ctx_special_pcdata, flags);
 			if ((flags & format_raw) == 0) writer.write('\n');
 			break;
 
@@ -2999,7 +3174,7 @@
 
 			if (node.type() == node_declaration)
 			{
-				node_output_attributes(writer, node);
+				node_output_attributes(writer, node, flags);
 			}
 			else if (node.value()[0])
 			{
@@ -3015,13 +3190,13 @@
 			writer.write('<', '!', 'D', 'O', 'C');
 			writer.write('T', 'Y', 'P', 'E');
 
-            if (node.value()[0])
-            {
-                writer.write(' ');
-                writer.write(node.value());
-            }
+			if (node.value()[0])
+			{
+				writer.write(' ');
+				writer.write(node.value());
+			}
 
-            writer.write('>');
+			writer.write('>');
 			if ((flags & format_raw) == 0) writer.write('\n');
 			break;
 
@@ -3052,7 +3227,7 @@
 		return true;
 	}
 
-	void recursive_copy_skip(xml_node& dest, const xml_node& source, const xml_node& skip)
+	PUGI__FN void recursive_copy_skip(xml_node& dest, const xml_node& source, const xml_node& skip)
 	{
 		assert(dest.type() == source.type());
 
@@ -3081,7 +3256,7 @@
 		case node_pcdata:
 		case node_cdata:
 		case node_comment:
-        case node_doctype:
+		case node_doctype:
 			dest.set_value(source.value());
 			break;
 
@@ -3105,10 +3280,115 @@
 		}
 	}
 
+	inline bool is_text_node(xml_node_struct* node)
+	{
+		xml_node_type type = static_cast<xml_node_type>((node->header & impl::xml_memory_page_type_mask) + 1);
+
+		return type == node_pcdata || type == node_cdata;
+	}
+
+	// get value with conversion functions
+	PUGI__FN int get_value_int(const char_t* value, int def)
+	{
+		if (!value) return def;
+
+	#ifdef PUGIXML_WCHAR_MODE
+		return static_cast<int>(wcstol(value, 0, 10));
+	#else
+		return static_cast<int>(strtol(value, 0, 10));
+	#endif
+	}
+
+	PUGI__FN unsigned int get_value_uint(const char_t* value, unsigned int def)
+	{
+		if (!value) return def;
+
+	#ifdef PUGIXML_WCHAR_MODE
+		return static_cast<unsigned int>(wcstoul(value, 0, 10));
+	#else
+		return static_cast<unsigned int>(strtoul(value, 0, 10));
+	#endif
+	}
+
+	PUGI__FN double get_value_double(const char_t* value, double def)
+	{
+		if (!value) return def;
+
+	#ifdef PUGIXML_WCHAR_MODE
+		return wcstod(value, 0);
+	#else
+		return strtod(value, 0);
+	#endif
+	}
+
+	PUGI__FN float get_value_float(const char_t* value, float def)
+	{
+		if (!value) return def;
+
+	#ifdef PUGIXML_WCHAR_MODE
+		return static_cast<float>(wcstod(value, 0));
+	#else
+		return static_cast<float>(strtod(value, 0));
+	#endif
+	}
+
+	PUGI__FN bool get_value_bool(const char_t* value, bool def)
+	{
+		if (!value) return def;
+
+		// only look at first char
+		char_t first = *value;
+
+		// 1*, t* (true), T* (True), y* (yes), Y* (YES)
+		return (first == '1' || first == 't' || first == 'T' || first == 'y' || first == 'Y');
+	}
+
+	// set value with conversion functions
+	PUGI__FN bool set_value_buffer(char_t*& dest, uintptr_t& header, uintptr_t header_mask, char (&buf)[128])
+	{
+	#ifdef PUGIXML_WCHAR_MODE
+		char_t wbuf[128];
+		impl::widen_ascii(wbuf, buf);
+
+		return strcpy_insitu(dest, header, header_mask, wbuf);
+	#else
+		return strcpy_insitu(dest, header, header_mask, buf);
+	#endif
+	}
+
+	PUGI__FN bool set_value_convert(char_t*& dest, uintptr_t& header, uintptr_t header_mask, int value)
+	{
+		char buf[128];
+		sprintf(buf, "%d", value);
+	
+		return set_value_buffer(dest, header, header_mask, buf);
+	}
+
+	PUGI__FN bool set_value_convert(char_t*& dest, uintptr_t& header, uintptr_t header_mask, unsigned int value)
+	{
+		char buf[128];
+		sprintf(buf, "%u", value);
+
+		return set_value_buffer(dest, header, header_mask, buf);
+	}
+
+	PUGI__FN bool set_value_convert(char_t*& dest, uintptr_t& header, uintptr_t header_mask, double value)
+	{
+		char buf[128];
+		sprintf(buf, "%g", value);
+
+		return set_value_buffer(dest, header, header_mask, buf);
+	}
+	
+	PUGI__FN bool set_value_convert(char_t*& dest, uintptr_t& header, uintptr_t header_mask, bool value)
+	{
+		return strcpy_insitu(dest, header, header_mask, value ? PUGIXML_TEXT("true") : PUGIXML_TEXT("false"));
+	}
+
 	// we need to get length of entire file to load it in memory; the only (relatively) sane way to do it is via seek/tell trick
-	xml_parse_status get_file_size(FILE* file, size_t& out_result)
+	PUGI__FN xml_parse_status get_file_size(FILE* file, size_t& out_result)
 	{
-	#if defined(_MSC_VER) && _MSC_VER >= 1400
+	#if defined(PUGI__MSVC_CRT_VERSION) && PUGI__MSVC_CRT_VERSION >= 1400 && !defined(_WIN32_WCE)
 		// there are 64-bit versions of fseek/ftell, let's use them
 		typedef __int64 length_type;
 
@@ -3145,7 +3425,7 @@
 		return status_ok;
 	}
 
-	xml_parse_result load_file_impl(xml_document& doc, FILE* file, unsigned int options, xml_encoding encoding)
+	PUGI__FN xml_parse_result load_file_impl(xml_document& doc, FILE* file, unsigned int options, xml_encoding encoding)
 	{
 		if (!file) return make_parse_result(status_file_not_found);
 
@@ -3160,7 +3440,7 @@
 		}
 		
 		// allocate buffer for the whole file
-		char* contents = static_cast<char*>(global_allocate(size > 0 ? size : 1));
+		char* contents = static_cast<char*>(xml_memory::allocate(size > 0 ? size : 1));
 
 		if (!contents)
 		{
@@ -3174,7 +3454,7 @@
 
 		if (read_size != size)
 		{
-			global_deallocate(contents);
+			xml_memory::deallocate(contents);
 			return make_parse_result(status_io_error);
 		}
 		
@@ -3182,7 +3462,91 @@
 	}
 
 #ifndef PUGIXML_NO_STL
-	template <typename T> xml_parse_result load_stream_impl(xml_document& doc, std::basic_istream<T>& stream, unsigned int options, xml_encoding encoding)
+	template <typename T> struct xml_stream_chunk
+	{
+		static xml_stream_chunk* create()
+		{
+			void* memory = xml_memory::allocate(sizeof(xml_stream_chunk));
+			
+			return new (memory) xml_stream_chunk();
+		}
+
+		static void destroy(void* ptr)
+		{
+			xml_stream_chunk* chunk = static_cast<xml_stream_chunk*>(ptr);
+
+			// free chunk chain
+			while (chunk)
+			{
+				xml_stream_chunk* next = chunk->next;
+				xml_memory::deallocate(chunk);
+				chunk = next;
+			}
+		}
+
+		xml_stream_chunk(): next(0), size(0)
+		{
+		}
+
+		xml_stream_chunk* next;
+		size_t size;
+
+		T data[xml_memory_page_size / sizeof(T)];
+	};
+
+	template <typename T> PUGI__FN xml_parse_status load_stream_data_noseek(std::basic_istream<T>& stream, void** out_buffer, size_t* out_size)
+	{
+		buffer_holder chunks(0, xml_stream_chunk<T>::destroy);
+
+		// read file to a chunk list
+		size_t total = 0;
+		xml_stream_chunk<T>* last = 0;
+
+		while (!stream.eof())
+		{
+			// allocate new chunk
+			xml_stream_chunk<T>* chunk = xml_stream_chunk<T>::create();
+			if (!chunk) return status_out_of_memory;
+
+			// append chunk to list
+			if (last) last = last->next = chunk;
+			else chunks.data = last = chunk;
+
+			// read data to chunk
+			stream.read(chunk->data, static_cast<std::streamsize>(sizeof(chunk->data) / sizeof(T)));
+			chunk->size = static_cast<size_t>(stream.gcount()) * sizeof(T);
+
+			// read may set failbit | eofbit in case gcount() is less than read length, so check for other I/O errors
+			if (stream.bad() || (!stream.eof() && stream.fail())) return status_io_error;
+
+			// guard against huge files (chunk size is small enough to make this overflow check work)
+			if (total + chunk->size < total) return status_out_of_memory;
+			total += chunk->size;
+		}
+
+		// copy chunk list to a contiguous buffer
+		char* buffer = static_cast<char*>(xml_memory::allocate(total));
+		if (!buffer) return status_out_of_memory;
+
+		char* write = buffer;
+
+		for (xml_stream_chunk<T>* chunk = static_cast<xml_stream_chunk<T>*>(chunks.data); chunk; chunk = chunk->next)
+		{
+			assert(write + chunk->size <= buffer + total);
+			memcpy(write, chunk->data, chunk->size);
+			write += chunk->size;
+		}
+
+		assert(write == buffer + total);
+
+		// return buffer
+		*out_buffer = buffer;
+		*out_size = total;
+
+		return status_ok;
+	}
+
+	template <typename T> PUGI__FN xml_parse_status load_stream_data_seek(std::basic_istream<T>& stream, void** out_buffer, size_t* out_size)
 	{
 		// get length of remaining data in stream
 		typename std::basic_istream<T>::pos_type pos = stream.tellg();
@@ -3190,55 +3554,70 @@
 		std::streamoff length = stream.tellg() - pos;
 		stream.seekg(pos);
 
-		if (stream.fail() || pos < 0) return make_parse_result(status_io_error);
+		if (stream.fail() || pos < 0) return status_io_error;
 
 		// guard against huge files
 		size_t read_length = static_cast<size_t>(length);
 
-		if (static_cast<std::streamsize>(read_length) != length || length < 0) return make_parse_result(status_out_of_memory);
+		if (static_cast<std::streamsize>(read_length) != length || length < 0) return status_out_of_memory;
 
 		// read stream data into memory (guard against stream exceptions with buffer holder)
-		buffer_holder buffer(global_allocate((read_length > 0 ? read_length : 1) * sizeof(T)), global_deallocate);
-		if (!buffer.data) return make_parse_result(status_out_of_memory);
+		buffer_holder buffer(xml_memory::allocate((read_length > 0 ? read_length : 1) * sizeof(T)), xml_memory::deallocate);
+		if (!buffer.data) return status_out_of_memory;
 
 		stream.read(static_cast<T*>(buffer.data), static_cast<std::streamsize>(read_length));
 
 		// read may set failbit | eofbit in case gcount() is less than read_length (i.e. line ending conversion), so check for other I/O errors
-		if (stream.bad()) return make_parse_result(status_io_error);
+		if (stream.bad() || (!stream.eof() && stream.fail())) return status_io_error;
 
-		// load data from buffer
+		// return buffer
 		size_t actual_length = static_cast<size_t>(stream.gcount());
 		assert(actual_length <= read_length);
 
-		return doc.load_buffer_inplace_own(buffer.release(), actual_length * sizeof(T), options, encoding);
+		*out_buffer = buffer.release();
+		*out_size = actual_length * sizeof(T);
+
+		return status_ok;
+	}
+
+	template <typename T> PUGI__FN xml_parse_result load_stream_impl(xml_document& doc, std::basic_istream<T>& stream, unsigned int options, xml_encoding encoding)
+	{
+		void* buffer = 0;
+		size_t size = 0;
+
+		// load stream to memory (using seek-based implementation if possible, since it's faster and takes less memory)
+		xml_parse_status status = (stream.tellg() < 0) ? load_stream_data_noseek(stream, &buffer, &size) : load_stream_data_seek(stream, &buffer, &size);
+		if (status != status_ok) return make_parse_result(status);
+
+		return doc.load_buffer_inplace_own(buffer, size, options, encoding);
 	}
 #endif
 
-#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
-	FILE* open_file_wide(const wchar_t* path, const wchar_t* mode)
+#if defined(PUGI__MSVC_CRT_VERSION) || defined(__BORLANDC__) || (defined(__MINGW32__) && !defined(__STRICT_ANSI__))
+	PUGI__FN FILE* open_file_wide(const wchar_t* path, const wchar_t* mode)
 	{
 		return _wfopen(path, mode);
 	}
 #else
-	char* convert_path_heap(const wchar_t* str)
+	PUGI__FN char* convert_path_heap(const wchar_t* str)
 	{
 		assert(str);
 
 		// first pass: get length in utf8 characters
 		size_t length = wcslen(str);
-        size_t size = as_utf8_begin(str, length);
+		size_t size = as_utf8_begin(str, length);
 
 		// allocate resulting string
-		char* result = static_cast<char*>(global_allocate(size + 1));
+		char* result = static_cast<char*>(xml_memory::allocate(size + 1));
 		if (!result) return 0;
 
 		// second pass: convert to utf8
-        as_utf8_end(result, size, str, length);
+		as_utf8_end(result, size, str, length);
 
-	  	return result;
+		return result;
 	}
 
-	FILE* open_file_wide(const wchar_t* path, const wchar_t* mode)
+	PUGI__FN FILE* open_file_wide(const wchar_t* path, const wchar_t* mode)
 	{
 		// there is no standard function to open wide paths, so our best bet is to try utf8 path
 		char* path_utf8 = convert_path_heap(path);
@@ -3252,39 +3631,49 @@
 		FILE* result = fopen(path_utf8, mode_ascii);
 
 		// free dummy buffer
-		global_deallocate(path_utf8);
+		xml_memory::deallocate(path_utf8);
 
 		return result;
 	}
 #endif
-}
 
+	PUGI__FN bool save_file_impl(const xml_document& doc, FILE* file, const char_t* indent, unsigned int flags, xml_encoding encoding)
+	{
+		if (!file) return false;
 
-// Added by LG for OpenImageIO:
-OIIO_NAMESPACE_ENTER
-{
+		xml_writer_file writer(file);
+		doc.save(writer, indent, flags, encoding);
+
+		int result = ferror(file);
+
+		fclose(file);
+
+		return result == 0;
+	}
+PUGI__NS_END
 
 namespace pugi
 {
-	xml_writer_file::xml_writer_file(void* file): file(file)
+	PUGI__FN xml_writer_file::xml_writer_file(void* file_): file(file_)
 	{
 	}
 
-	void xml_writer_file::write(const void* data, size_t size)
+	PUGI__FN void xml_writer_file::write(const void* data, size_t size)
 	{
-		fwrite(data, size, 1, static_cast<FILE*>(file));
+		size_t result = fwrite(data, 1, size, static_cast<FILE*>(file));
+		(void)!result; // unfortunately we can't do proper error handling here
 	}
 
 #ifndef PUGIXML_NO_STL
-	xml_writer_stream::xml_writer_stream(std::basic_ostream<char, std::char_traits<char> >& stream): narrow_stream(&stream), wide_stream(0)
+	PUGI__FN xml_writer_stream::xml_writer_stream(std::basic_ostream<char, std::char_traits<char> >& stream): narrow_stream(&stream), wide_stream(0)
 	{
 	}
 
-	xml_writer_stream::xml_writer_stream(std::basic_ostream<wchar_t, std::char_traits<wchar_t> >& stream): narrow_stream(0), wide_stream(&stream)
+	PUGI__FN xml_writer_stream::xml_writer_stream(std::basic_ostream<wchar_t, std::char_traits<wchar_t> >& stream): narrow_stream(0), wide_stream(&stream)
 	{
 	}
 
-	void xml_writer_stream::write(const void* data, size_t size)
+	PUGI__FN void xml_writer_stream::write(const void* data, size_t size)
 	{
 		if (narrow_stream)
 		{
@@ -3301,393 +3690,369 @@
 	}
 #endif
 
-	xml_tree_walker::xml_tree_walker(): _depth(0)
+	PUGI__FN xml_tree_walker::xml_tree_walker(): _depth(0)
 	{
 	}
 	
-	xml_tree_walker::~xml_tree_walker()
+	PUGI__FN xml_tree_walker::~xml_tree_walker()
 	{
 	}
 
-	int xml_tree_walker::depth() const
+	PUGI__FN int xml_tree_walker::depth() const
 	{
 		return _depth;
 	}
 
-	bool xml_tree_walker::begin(xml_node&)
+	PUGI__FN bool xml_tree_walker::begin(xml_node&)
 	{
 		return true;
 	}
 
-	bool xml_tree_walker::end(xml_node&)
+	PUGI__FN bool xml_tree_walker::end(xml_node&)
 	{
 		return true;
 	}
 
-	xml_attribute::xml_attribute(): _attr(0)
+	PUGI__FN xml_attribute::xml_attribute(): _attr(0)
 	{
 	}
 
-	xml_attribute::xml_attribute(xml_attribute_struct* attr): _attr(attr)
+	PUGI__FN xml_attribute::xml_attribute(xml_attribute_struct* attr): _attr(attr)
 	{
 	}
 
-	xml_attribute::operator xml_attribute::unspecified_bool_type() const
+	PUGI__FN static void unspecified_bool_xml_attribute(xml_attribute***)
 	{
-      	return _attr ? &xml_attribute::_attr : 0;
-   	}
+	}
 
-   	bool xml_attribute::operator!() const
-   	{
-   		return !_attr;
-   	}
+	PUGI__FN xml_attribute::operator xml_attribute::unspecified_bool_type() const
+	{
+		return _attr ? unspecified_bool_xml_attribute : 0;
+	}
 
-	bool xml_attribute::operator==(const xml_attribute& r) const
+	PUGI__FN bool xml_attribute::operator!() const
+	{
+		return !_attr;
+	}
+
+	PUGI__FN bool xml_attribute::operator==(const xml_attribute& r) const
 	{
 		return (_attr == r._attr);
 	}
 	
-	bool xml_attribute::operator!=(const xml_attribute& r) const
+	PUGI__FN bool xml_attribute::operator!=(const xml_attribute& r) const
 	{
 		return (_attr != r._attr);
 	}
 
-	bool xml_attribute::operator<(const xml_attribute& r) const
+	PUGI__FN bool xml_attribute::operator<(const xml_attribute& r) const
 	{
 		return (_attr < r._attr);
 	}
 	
-	bool xml_attribute::operator>(const xml_attribute& r) const
+	PUGI__FN bool xml_attribute::operator>(const xml_attribute& r) const
 	{
 		return (_attr > r._attr);
 	}
 	
-	bool xml_attribute::operator<=(const xml_attribute& r) const
+	PUGI__FN bool xml_attribute::operator<=(const xml_attribute& r) const
 	{
 		return (_attr <= r._attr);
 	}
 	
-	bool xml_attribute::operator>=(const xml_attribute& r) const
+	PUGI__FN bool xml_attribute::operator>=(const xml_attribute& r) const
 	{
 		return (_attr >= r._attr);
 	}
 
-   	xml_attribute xml_attribute::next_attribute() const
-   	{
-    	return _attr ? xml_attribute(_attr->next_attribute) : xml_attribute();
-   	}
-
-    xml_attribute xml_attribute::previous_attribute() const
-    {
-    	return _attr && _attr->prev_attribute_c->next_attribute ? xml_attribute(_attr->prev_attribute_c) : xml_attribute();
-    }
-
-	int xml_attribute::as_int() const
+	PUGI__FN xml_attribute xml_attribute::next_attribute() const
 	{
-		if (!_attr || !_attr->value) return 0;
-
-	#ifdef PUGIXML_WCHAR_MODE
-		return (int)wcstol(_attr->value, 0, 10);
-	#else
-		return (int)strtol(_attr->value, 0, 10);
-	#endif
+		return _attr ? xml_attribute(_attr->next_attribute) : xml_attribute();
 	}
 
-	unsigned int xml_attribute::as_uint() const
+	PUGI__FN xml_attribute xml_attribute::previous_attribute() const
 	{
-		if (!_attr || !_attr->value) return 0;
-
-	#ifdef PUGIXML_WCHAR_MODE
-		return (unsigned int)wcstoul(_attr->value, 0, 10);
-	#else
-		return (unsigned int)strtoul(_attr->value, 0, 10);
-	#endif
+		return _attr && _attr->prev_attribute_c->next_attribute ? xml_attribute(_attr->prev_attribute_c) : xml_attribute();
 	}
 
-	double xml_attribute::as_double() const
+	PUGI__FN const char_t* xml_attribute::as_string(const char_t* def) const
 	{
-		if (!_attr || !_attr->value) return 0;
-
-	#ifdef PUGIXML_WCHAR_MODE
-		return wcstod(_attr->value, 0);
-	#else
-		return strtod(_attr->value, 0);
-	#endif
+		return (_attr && _attr->value) ? _attr->value : def;
 	}
 
-	float xml_attribute::as_float() const
+	PUGI__FN int xml_attribute::as_int(int def) const
 	{
-		if (!_attr || !_attr->value) return 0;
+		return impl::get_value_int(_attr ? _attr->value : 0, def);
+	}
 
-	#ifdef PUGIXML_WCHAR_MODE
-		return (float)wcstod(_attr->value, 0);
-	#else
-		return (float)strtod(_attr->value, 0);
-	#endif
+	PUGI__FN unsigned int xml_attribute::as_uint(unsigned int def) const
+	{
+		return impl::get_value_uint(_attr ? _attr->value : 0, def);
 	}
 
-	bool xml_attribute::as_bool() const
+	PUGI__FN double xml_attribute::as_double(double def) const
 	{
-		if (!_attr || !_attr->value) return false;
+		return impl::get_value_double(_attr ? _attr->value : 0, def);
+	}
 
-		// only look at first char
-		char_t first = *_attr->value;
+	PUGI__FN float xml_attribute::as_float(float def) const
+	{
+		return impl::get_value_float(_attr ? _attr->value : 0, def);
+	}
 
-		// 1*, t* (true), T* (True), y* (yes), Y* (YES)
-		return (first == '1' || first == 't' || first == 'T' || first == 'y' || first == 'Y');
+	PUGI__FN bool xml_attribute::as_bool(bool def) const
+	{
+		return impl::get_value_bool(_attr ? _attr->value : 0, def);
 	}
 
-	bool xml_attribute::empty() const
+	PUGI__FN bool xml_attribute::empty() const
 	{
 		return !_attr;
 	}
 
-	const char_t* xml_attribute::name() const
+	PUGI__FN const char_t* xml_attribute::name() const
 	{
 		return (_attr && _attr->name) ? _attr->name : PUGIXML_TEXT("");
 	}
 
-	const char_t* xml_attribute::value() const
+	PUGI__FN const char_t* xml_attribute::value() const
 	{
 		return (_attr && _attr->value) ? _attr->value : PUGIXML_TEXT("");
 	}
 
-    size_t xml_attribute::hash_value() const
-    {
-        return static_cast<size_t>(reinterpret_cast<uintptr_t>(_attr) / sizeof(xml_attribute_struct));
-    }
+	PUGI__FN size_t xml_attribute::hash_value() const
+	{
+		return static_cast<size_t>(reinterpret_cast<uintptr_t>(_attr) / sizeof(xml_attribute_struct));
+	}
 
-	xml_attribute_struct* xml_attribute::internal_object() const
+	PUGI__FN xml_attribute_struct* xml_attribute::internal_object() const
 	{
-        return _attr;
+		return _attr;
 	}
 
-	xml_attribute& xml_attribute::operator=(const char_t* rhs)
+	PUGI__FN xml_attribute& xml_attribute::operator=(const char_t* rhs)
 	{
 		set_value(rhs);
 		return *this;
 	}
 	
-	xml_attribute& xml_attribute::operator=(int rhs)
+	PUGI__FN xml_attribute& xml_attribute::operator=(int rhs)
 	{
 		set_value(rhs);
 		return *this;
 	}
 
-	xml_attribute& xml_attribute::operator=(unsigned int rhs)
+	PUGI__FN xml_attribute& xml_attribute::operator=(unsigned int rhs)
 	{
 		set_value(rhs);
 		return *this;
 	}
 
-	xml_attribute& xml_attribute::operator=(double rhs)
+	PUGI__FN xml_attribute& xml_attribute::operator=(double rhs)
 	{
 		set_value(rhs);
 		return *this;
 	}
 	
-	xml_attribute& xml_attribute::operator=(bool rhs)
+	PUGI__FN xml_attribute& xml_attribute::operator=(bool rhs)
 	{
 		set_value(rhs);
 		return *this;
 	}
 
-	bool xml_attribute::set_name(const char_t* rhs)
+	PUGI__FN bool xml_attribute::set_name(const char_t* rhs)
 	{
 		if (!_attr) return false;
 		
-		return strcpy_insitu(_attr->name, _attr->header, xml_memory_page_name_allocated_mask, rhs);
+		return impl::strcpy_insitu(_attr->name, _attr->header, impl::xml_memory_page_name_allocated_mask, rhs);
 	}
 		
-	bool xml_attribute::set_value(const char_t* rhs)
+	PUGI__FN bool xml_attribute::set_value(const char_t* rhs)
 	{
 		if (!_attr) return false;
 
-		return strcpy_insitu(_attr->value, _attr->header, xml_memory_page_value_allocated_mask, rhs);
+		return impl::strcpy_insitu(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs);
 	}
 
-	bool xml_attribute::set_value(int rhs)
+	PUGI__FN bool xml_attribute::set_value(int rhs)
 	{
-		char buf[128];
-		sprintf(buf, "%d", rhs);
-	
-	#ifdef PUGIXML_WCHAR_MODE
-		char_t wbuf[128];
-		widen_ascii(wbuf, buf);
+		if (!_attr) return false;
 
-		return set_value(wbuf);
-	#else
-		return set_value(buf);
-	#endif
+		return impl::set_value_convert(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs);
 	}
 
-	bool xml_attribute::set_value(unsigned int rhs)
+	PUGI__FN bool xml_attribute::set_value(unsigned int rhs)
 	{
-		char buf[128];
-		sprintf(buf, "%u", rhs);
-
-	#ifdef PUGIXML_WCHAR_MODE
-		char_t wbuf[128];
-		widen_ascii(wbuf, buf);
+		if (!_attr) return false;
 
-		return set_value(wbuf);
-	#else
-		return set_value(buf);
-	#endif
+		return impl::set_value_convert(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs);
 	}
 
-	bool xml_attribute::set_value(double rhs)
+	PUGI__FN bool xml_attribute::set_value(double rhs)
 	{
-		char buf[128];
-		sprintf(buf, "%g", rhs);
-
-	#ifdef PUGIXML_WCHAR_MODE
-		char_t wbuf[128];
-		widen_ascii(wbuf, buf);
+		if (!_attr) return false;
 
-		return set_value(wbuf);
-	#else
-		return set_value(buf);
-	#endif
+		return impl::set_value_convert(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs);
 	}
 	
-	bool xml_attribute::set_value(bool rhs)
+	PUGI__FN bool xml_attribute::set_value(bool rhs)
 	{
-		return set_value(rhs ? PUGIXML_TEXT("true") : PUGIXML_TEXT("false"));
+		if (!_attr) return false;
+
+		return impl::set_value_convert(_attr->value, _attr->header, impl::xml_memory_page_value_allocated_mask, rhs);
 	}
 
 #ifdef __BORLANDC__
-	bool operator&&(const xml_attribute& lhs, bool rhs)
+	PUGI__FN bool operator&&(const xml_attribute& lhs, bool rhs)
 	{
 		return (bool)lhs && rhs;
 	}
 
-	bool operator||(const xml_attribute& lhs, bool rhs)
+	PUGI__FN bool operator||(const xml_attribute& lhs, bool rhs)
 	{
 		return (bool)lhs || rhs;
 	}
 #endif
 
-	xml_node::xml_node(): _root(0)
+	PUGI__FN xml_node::xml_node(): _root(0)
 	{
 	}
 
-	xml_node::xml_node(xml_node_struct* p): _root(p)
+	PUGI__FN xml_node::xml_node(xml_node_struct* p): _root(p)
 	{
 	}
 	
-	xml_node::operator xml_node::unspecified_bool_type() const
+	PUGI__FN static void unspecified_bool_xml_node(xml_node***)
 	{
-      	return _root ? &xml_node::_root : 0;
-   	}
+	}
 
-   	bool xml_node::operator!() const
-   	{
-   		return !_root;
-   	}
+	PUGI__FN xml_node::operator xml_node::unspecified_bool_type() const
+	{
+		return _root ? unspecified_bool_xml_node : 0;
+	}
 
-	xml_node::iterator xml_node::begin() const
+	PUGI__FN bool xml_node::operator!() const
+	{
+		return !_root;
+	}
+
+	PUGI__FN xml_node::iterator xml_node::begin() const
 	{
 		return iterator(_root ? _root->first_child : 0, _root);
 	}
 
-	xml_node::iterator xml_node::end() const
+	PUGI__FN xml_node::iterator xml_node::end() const
 	{
 		return iterator(0, _root);
 	}
 	
-	xml_node::attribute_iterator xml_node::attributes_begin() const
+	PUGI__FN xml_node::attribute_iterator xml_node::attributes_begin() const
 	{
 		return attribute_iterator(_root ? _root->first_attribute : 0, _root);
 	}
 
-	xml_node::attribute_iterator xml_node::attributes_end() const
+	PUGI__FN xml_node::attribute_iterator xml_node::attributes_end() const
 	{
 		return attribute_iterator(0, _root);
 	}
+	
+	PUGI__FN xml_object_range<xml_node_iterator> xml_node::children() const
+	{
+		return xml_object_range<xml_node_iterator>(begin(), end());
+	}
 
-	bool xml_node::operator==(const xml_node& r) const
+	PUGI__FN xml_object_range<xml_named_node_iterator> xml_node::children(const char_t* name_) const
+	{
+		return xml_object_range<xml_named_node_iterator>(xml_named_node_iterator(child(name_), name_), xml_named_node_iterator());
+	}
+
+	PUGI__FN xml_object_range<xml_attribute_iterator> xml_node::attributes() const
+	{
+		return xml_object_range<xml_attribute_iterator>(attributes_begin(), attributes_end());
+	}
+
+	PUGI__FN bool xml_node::operator==(const xml_node& r) const
 	{
 		return (_root == r._root);
 	}
 
-	bool xml_node::operator!=(const xml_node& r) const
+	PUGI__FN bool xml_node::operator!=(const xml_node& r) const
 	{
 		return (_root != r._root);
 	}
 
-	bool xml_node::operator<(const xml_node& r) const
+	PUGI__FN bool xml_node::operator<(const xml_node& r) const
 	{
 		return (_root < r._root);
 	}
 	
-	bool xml_node::operator>(const xml_node& r) const
+	PUGI__FN bool xml_node::operator>(const xml_node& r) const
 	{
 		return (_root > r._root);
 	}
 	
-	bool xml_node::operator<=(const xml_node& r) const
+	PUGI__FN bool xml_node::operator<=(const xml_node& r) const
 	{
 		return (_root <= r._root);
 	}
 	
-	bool xml_node::operator>=(const xml_node& r) const
+	PUGI__FN bool xml_node::operator>=(const xml_node& r) const
 	{
 		return (_root >= r._root);
 	}
 
-	bool xml_node::empty() const
+	PUGI__FN bool xml_node::empty() const
 	{
 		return !_root;
 	}
 	
-	const char_t* xml_node::name() const
+	PUGI__FN const char_t* xml_node::name() const
 	{
 		return (_root && _root->name) ? _root->name : PUGIXML_TEXT("");
 	}
 
-	xml_node_type xml_node::type() const
+	PUGI__FN xml_node_type xml_node::type() const
 	{
-		return _root ? static_cast<xml_node_type>((_root->header & xml_memory_page_type_mask) + 1) : node_null;
+		return _root ? static_cast<xml_node_type>((_root->header & impl::xml_memory_page_type_mask) + 1) : node_null;
 	}
 	
-	const char_t* xml_node::value() const
+	PUGI__FN const char_t* xml_node::value() const
 	{
 		return (_root && _root->value) ? _root->value : PUGIXML_TEXT("");
 	}
 	
-	xml_node xml_node::child(const char_t* name) const
+	PUGI__FN xml_node xml_node::child(const char_t* name_) const
 	{
 		if (!_root) return xml_node();
 
 		for (xml_node_struct* i = _root->first_child; i; i = i->next_sibling)
-			if (i->name && strequal(name, i->name)) return xml_node(i);
+			if (i->name && impl::strequal(name_, i->name)) return xml_node(i);
 
 		return xml_node();
 	}
 
-	xml_attribute xml_node::attribute(const char_t* name) const
+	PUGI__FN xml_attribute xml_node::attribute(const char_t* name_) const
 	{
 		if (!_root) return xml_attribute();
 
 		for (xml_attribute_struct* i = _root->first_attribute; i; i = i->next_attribute)
-			if (i->name && strequal(name, i->name))
+			if (i->name && impl::strequal(name_, i->name))
 				return xml_attribute(i);
 		
 		return xml_attribute();
 	}
 	
-	xml_node xml_node::next_sibling(const char_t* name) const
+	PUGI__FN xml_node xml_node::next_sibling(const char_t* name_) const
 	{
 		if (!_root) return xml_node();
 		
 		for (xml_node_struct* i = _root->next_sibling; i; i = i->next_sibling)
-			if (i->name && strequal(name, i->name)) return xml_node(i);
+			if (i->name && impl::strequal(name_, i->name)) return xml_node(i);
 
 		return xml_node();
 	}
 
-	xml_node xml_node::next_sibling() const
+	PUGI__FN xml_node xml_node::next_sibling() const
 	{
 		if (!_root) return xml_node();
 		
@@ -3695,17 +4060,17 @@
 		else return xml_node();
 	}
 
-	xml_node xml_node::previous_sibling(const char_t* name) const
+	PUGI__FN xml_node xml_node::previous_sibling(const char_t* name_) const
 	{
 		if (!_root) return xml_node();
 		
 		for (xml_node_struct* i = _root->prev_sibling_c; i->next_sibling; i = i->prev_sibling_c)
-			if (i->name && strequal(name, i->name)) return xml_node(i);
+			if (i->name && impl::strequal(name_, i->name)) return xml_node(i);
 
 		return xml_node();
 	}
 
-	xml_node xml_node::previous_sibling() const
+	PUGI__FN xml_node xml_node::previous_sibling() const
 	{
 		if (!_root) return xml_node();
 		
@@ -3713,75 +4078,76 @@
 		else return xml_node();
 	}
 
-	xml_node xml_node::parent() const
+	PUGI__FN xml_node xml_node::parent() const
 	{
 		return _root ? xml_node(_root->parent) : xml_node();
 	}
 
-	xml_node xml_node::root() const
+	PUGI__FN xml_node xml_node::root() const
 	{
 		if (!_root) return xml_node();
 
-		xml_memory_page* page = reinterpret_cast<xml_memory_page*>(_root->header & xml_memory_page_pointer_mask);
+		impl::xml_memory_page* page = reinterpret_cast<impl::xml_memory_page*>(_root->header & impl::xml_memory_page_pointer_mask);
 
-		return xml_node(static_cast<xml_document_struct*>(page->allocator));
+		return xml_node(static_cast<impl::xml_document_struct*>(page->allocator));
 	}
 
-	const char_t* xml_node::child_value() const
+	PUGI__FN xml_text xml_node::text() const
+	{
+		return xml_text(_root);
+	}
+
+	PUGI__FN const char_t* xml_node::child_value() const
 	{
 		if (!_root) return PUGIXML_TEXT("");
 		
 		for (xml_node_struct* i = _root->first_child; i; i = i->next_sibling)
-		{
-			xml_node_type type = static_cast<xml_node_type>((i->header & xml_memory_page_type_mask) + 1);
-
-			if (i->value && (type == node_pcdata || type == node_cdata))
+			if (i->value && impl::is_text_node(i))
 				return i->value;
-		}
 
 		return PUGIXML_TEXT("");
 	}
 
-	const char_t* xml_node::child_value(const char_t* name) const
+	PUGI__FN const char_t* xml_node::child_value(const char_t* name_) const
 	{
-		return child(name).child_value();
+		return child(name_).child_value();
 	}
 
-	xml_attribute xml_node::first_attribute() const
+	PUGI__FN xml_attribute xml_node::first_attribute() const
 	{
 		return _root ? xml_attribute(_root->first_attribute) : xml_attribute();
 	}
 
-	xml_attribute xml_node::last_attribute() const
+	PUGI__FN xml_attribute xml_node::last_attribute() const
 	{
 		return _root && _root->first_attribute ? xml_attribute(_root->first_attribute->prev_attribute_c) : xml_attribute();
 	}
 
-	xml_node xml_node::first_child() const
+	PUGI__FN xml_node xml_node::first_child() const
 	{
 		return _root ? xml_node(_root->first_child) : xml_node();
 	}
 
-	xml_node xml_node::last_child() const
+	PUGI__FN xml_node xml_node::last_child() const
 	{
 		return _root && _root->first_child ? xml_node(_root->first_child->prev_sibling_c) : xml_node();
 	}
 
-	bool xml_node::set_name(const char_t* rhs)
+	PUGI__FN bool xml_node::set_name(const char_t* rhs)
 	{
 		switch (type())
 		{
 		case node_pi:
 		case node_declaration:
 		case node_element:
-			return strcpy_insitu(_root->name, _root->header, xml_memory_page_name_allocated_mask, rhs);
+			return impl::strcpy_insitu(_root->name, _root->header, impl::xml_memory_page_name_allocated_mask, rhs);
 
 		default:
 			return false;
 		}
 	}
 		
-	bool xml_node::set_value(const char_t* rhs)
+	PUGI__FN bool xml_node::set_value(const char_t* rhs)
 	{
 		switch (type())
 		{
@@ -3789,50 +4155,50 @@
 		case node_cdata:
 		case node_pcdata:
 		case node_comment:
-        case node_doctype:
-			return strcpy_insitu(_root->value, _root->header, xml_memory_page_value_allocated_mask, rhs);
+		case node_doctype:
+			return impl::strcpy_insitu(_root->value, _root->header, impl::xml_memory_page_value_allocated_mask, rhs);
 
 		default:
 			return false;
 		}
 	}
 
-	xml_attribute xml_node::append_attribute(const char_t* name)
+	PUGI__FN xml_attribute xml_node::append_attribute(const char_t* name_)
 	{
 		if (type() != node_element && type() != node_declaration) return xml_attribute();
 		
-		xml_attribute a(append_attribute_ll(_root, get_allocator(_root)));
-		a.set_name(name);
+		xml_attribute a(impl::append_attribute_ll(_root, impl::get_allocator(_root)));
+		a.set_name(name_);
 		
 		return a;
 	}
 
-	xml_attribute xml_node::prepend_attribute(const char_t* name)
+	PUGI__FN xml_attribute xml_node::prepend_attribute(const char_t* name_)
 	{
 		if (type() != node_element && type() != node_declaration) return xml_attribute();
 		
-		xml_attribute a(allocate_attribute(get_allocator(_root)));
+		xml_attribute a(impl::allocate_attribute(impl::get_allocator(_root)));
 		if (!a) return xml_attribute();
 
-		a.set_name(name);
+		a.set_name(name_);
 		
-        xml_attribute_struct* head = _root->first_attribute;
+		xml_attribute_struct* head = _root->first_attribute;
 
 		if (head)
-        {
-            a._attr->prev_attribute_c = head->prev_attribute_c;
-            head->prev_attribute_c = a._attr;
-        }
-        else
-            a._attr->prev_attribute_c = a._attr;
+		{
+			a._attr->prev_attribute_c = head->prev_attribute_c;
+			head->prev_attribute_c = a._attr;
+		}
+		else
+			a._attr->prev_attribute_c = a._attr;
 		
 		a._attr->next_attribute = head;
-        _root->first_attribute = a._attr;
+		_root->first_attribute = a._attr;
 				
 		return a;
 	}
 
-	xml_attribute xml_node::insert_attribute_before(const char_t* name, const xml_attribute& attr)
+	PUGI__FN xml_attribute xml_node::insert_attribute_before(const char_t* name_, const xml_attribute& attr)
 	{
 		if ((type() != node_element && type() != node_declaration) || attr.empty()) return xml_attribute();
 		
@@ -3843,10 +4209,10 @@
 
 		if (cur != _root->first_attribute) return xml_attribute();
 
-		xml_attribute a(allocate_attribute(get_allocator(_root)));
+		xml_attribute a(impl::allocate_attribute(impl::get_allocator(_root)));
 		if (!a) return xml_attribute();
 
-		a.set_name(name);
+		a.set_name(name_);
 
 		if (attr._attr->prev_attribute_c->next_attribute)
 			attr._attr->prev_attribute_c->next_attribute = a._attr;
@@ -3860,7 +4226,7 @@
 		return a;
 	}
 
-	xml_attribute xml_node::insert_attribute_after(const char_t* name, const xml_attribute& attr)
+	PUGI__FN xml_attribute xml_node::insert_attribute_after(const char_t* name_, const xml_attribute& attr)
 	{
 		if ((type() != node_element && type() != node_declaration) || attr.empty()) return xml_attribute();
 		
@@ -3871,10 +4237,10 @@
 
 		if (cur != _root->first_attribute) return xml_attribute();
 
-		xml_attribute a(allocate_attribute(get_allocator(_root)));
+		xml_attribute a(impl::allocate_attribute(impl::get_allocator(_root)));
 		if (!a) return xml_attribute();
 
-		a.set_name(name);
+		a.set_name(name_);
 
 		if (attr._attr->next_attribute)
 			attr._attr->next_attribute->prev_attribute_c = a._attr;
@@ -3888,7 +4254,7 @@
 		return a;
 	}
 
-	xml_attribute xml_node::append_copy(const xml_attribute& proto)
+	PUGI__FN xml_attribute xml_node::append_copy(const xml_attribute& proto)
 	{
 		if (!proto) return xml_attribute();
 
@@ -3898,7 +4264,7 @@
 		return result;
 	}
 
-	xml_attribute xml_node::prepend_copy(const xml_attribute& proto)
+	PUGI__FN xml_attribute xml_node::prepend_copy(const xml_attribute& proto)
 	{
 		if (!proto) return xml_attribute();
 
@@ -3908,7 +4274,7 @@
 		return result;
 	}
 
-	xml_attribute xml_node::insert_copy_after(const xml_attribute& proto, const xml_attribute& attr)
+	PUGI__FN xml_attribute xml_node::insert_copy_after(const xml_attribute& proto, const xml_attribute& attr)
 	{
 		if (!proto) return xml_attribute();
 
@@ -3918,7 +4284,7 @@
 		return result;
 	}
 
-	xml_attribute xml_node::insert_copy_before(const xml_attribute& proto, const xml_attribute& attr)
+	PUGI__FN xml_attribute xml_node::insert_copy_before(const xml_attribute& proto, const xml_attribute& attr)
 	{
 		if (!proto) return xml_attribute();
 
@@ -3928,50 +4294,50 @@
 		return result;
 	}
 
-	xml_node xml_node::append_child(xml_node_type type)
+	PUGI__FN xml_node xml_node::append_child(xml_node_type type_)
 	{
-		if (!allow_insert_child(this->type(), type)) return xml_node();
+		if (!impl::allow_insert_child(this->type(), type_)) return xml_node();
 		
-		xml_node n(append_node(_root, get_allocator(_root), type));
+		xml_node n(impl::append_node(_root, impl::get_allocator(_root), type_));
 
-		if (type == node_declaration) n.set_name(PUGIXML_TEXT("xml"));
+		if (type_ == node_declaration) n.set_name(PUGIXML_TEXT("xml"));
 
 		return n;
 	}
 
-	xml_node xml_node::prepend_child(xml_node_type type)
+	PUGI__FN xml_node xml_node::prepend_child(xml_node_type type_)
 	{
-		if (!allow_insert_child(this->type(), type)) return xml_node();
+		if (!impl::allow_insert_child(this->type(), type_)) return xml_node();
 		
-		xml_node n(allocate_node(get_allocator(_root), type));
+		xml_node n(impl::allocate_node(impl::get_allocator(_root), type_));
 		if (!n) return xml_node();
 
-        n._root->parent = _root;
+		n._root->parent = _root;
 
-        xml_node_struct* head = _root->first_child;
+		xml_node_struct* head = _root->first_child;
 
 		if (head)
-        {
-            n._root->prev_sibling_c = head->prev_sibling_c;
-            head->prev_sibling_c = n._root;
-        }
-        else
-            n._root->prev_sibling_c = n._root;
+		{
+			n._root->prev_sibling_c = head->prev_sibling_c;
+			head->prev_sibling_c = n._root;
+		}
+		else
+			n._root->prev_sibling_c = n._root;
 		
 		n._root->next_sibling = head;
-        _root->first_child = n._root;
+		_root->first_child = n._root;
 				
-		if (type == node_declaration) n.set_name(PUGIXML_TEXT("xml"));
+		if (type_ == node_declaration) n.set_name(PUGIXML_TEXT("xml"));
 
 		return n;
 	}
 
-	xml_node xml_node::insert_child_before(xml_node_type type, const xml_node& node)
+	PUGI__FN xml_node xml_node::insert_child_before(xml_node_type type_, const xml_node& node)
 	{
-		if (!allow_insert_child(this->type(), type)) return xml_node();
+		if (!impl::allow_insert_child(this->type(), type_)) return xml_node();
 		if (!node._root || node._root->parent != _root) return xml_node();
 	
-		xml_node n(allocate_node(get_allocator(_root), type));
+		xml_node n(impl::allocate_node(impl::get_allocator(_root), type_));
 		if (!n) return xml_node();
 
 		n._root->parent = _root;
@@ -3985,17 +4351,17 @@
 		n._root->next_sibling = node._root;
 		node._root->prev_sibling_c = n._root;
 
-		if (type == node_declaration) n.set_name(PUGIXML_TEXT("xml"));
+		if (type_ == node_declaration) n.set_name(PUGIXML_TEXT("xml"));
 
 		return n;
 	}
 
-	xml_node xml_node::insert_child_after(xml_node_type type, const xml_node& node)
+	PUGI__FN xml_node xml_node::insert_child_after(xml_node_type type_, const xml_node& node)
 	{
-		if (!allow_insert_child(this->type(), type)) return xml_node();
+		if (!impl::allow_insert_child(this->type(), type_)) return xml_node();
 		if (!node._root || node._root->parent != _root) return xml_node();
 	
-		xml_node n(allocate_node(get_allocator(_root), type));
+		xml_node n(impl::allocate_node(impl::get_allocator(_root), type_));
 		if (!n) return xml_node();
 
 		n._root->parent = _root;
@@ -4009,89 +4375,89 @@
 		n._root->prev_sibling_c = node._root;
 		node._root->next_sibling = n._root;
 
-		if (type == node_declaration) n.set_name(PUGIXML_TEXT("xml"));
+		if (type_ == node_declaration) n.set_name(PUGIXML_TEXT("xml"));
 
 		return n;
 	}
 
-    xml_node xml_node::append_child(const char_t* name)
-    {
-        xml_node result = append_child(node_element);
+	PUGI__FN xml_node xml_node::append_child(const char_t* name_)
+	{
+		xml_node result = append_child(node_element);
 
-        result.set_name(name);
+		result.set_name(name_);
 
-        return result;
-    }
+		return result;
+	}
 
-    xml_node xml_node::prepend_child(const char_t* name)
-    {
-        xml_node result = prepend_child(node_element);
+	PUGI__FN xml_node xml_node::prepend_child(const char_t* name_)
+	{
+		xml_node result = prepend_child(node_element);
 
-        result.set_name(name);
+		result.set_name(name_);
 
-        return result;
-    }
+		return result;
+	}
 
-    xml_node xml_node::insert_child_after(const char_t* name, const xml_node& node)
-    {
-        xml_node result = insert_child_after(node_element, node);
+	PUGI__FN xml_node xml_node::insert_child_after(const char_t* name_, const xml_node& node)
+	{
+		xml_node result = insert_child_after(node_element, node);
 
-        result.set_name(name);
+		result.set_name(name_);
 
-        return result;
-    }
+		return result;
+	}
 
-    xml_node xml_node::insert_child_before(const char_t* name, const xml_node& node)
-    {
-        xml_node result = insert_child_before(node_element, node);
+	PUGI__FN xml_node xml_node::insert_child_before(const char_t* name_, const xml_node& node)
+	{
+		xml_node result = insert_child_before(node_element, node);
 
-        result.set_name(name);
+		result.set_name(name_);
 
-        return result;
-    }
+		return result;
+	}
 
-	xml_node xml_node::append_copy(const xml_node& proto)
+	PUGI__FN xml_node xml_node::append_copy(const xml_node& proto)
 	{
 		xml_node result = append_child(proto.type());
 
-		if (result) recursive_copy_skip(result, proto, result);
+		if (result) impl::recursive_copy_skip(result, proto, result);
 
 		return result;
 	}
 
-	xml_node xml_node::prepend_copy(const xml_node& proto)
+	PUGI__FN xml_node xml_node::prepend_copy(const xml_node& proto)
 	{
 		xml_node result = prepend_child(proto.type());
 
-		if (result) recursive_copy_skip(result, proto, result);
+		if (result) impl::recursive_copy_skip(result, proto, result);
 
 		return result;
 	}
 
-	xml_node xml_node::insert_copy_after(const xml_node& proto, const xml_node& node)
+	PUGI__FN xml_node xml_node::insert_copy_after(const xml_node& proto, const xml_node& node)
 	{
 		xml_node result = insert_child_after(proto.type(), node);
 
-		if (result) recursive_copy_skip(result, proto, result);
+		if (result) impl::recursive_copy_skip(result, proto, result);
 
 		return result;
 	}
 
-	xml_node xml_node::insert_copy_before(const xml_node& proto, const xml_node& node)
+	PUGI__FN xml_node xml_node::insert_copy_before(const xml_node& proto, const xml_node& node)
 	{
 		xml_node result = insert_child_before(proto.type(), node);
 
-		if (result) recursive_copy_skip(result, proto, result);
+		if (result) impl::recursive_copy_skip(result, proto, result);
 
 		return result;
 	}
 
-	bool xml_node::remove_attribute(const char_t* name)
+	PUGI__FN bool xml_node::remove_attribute(const char_t* name_)
 	{
-		return remove_attribute(attribute(name));
+		return remove_attribute(attribute(name_));
 	}
 
-	bool xml_node::remove_attribute(const xml_attribute& a)
+	PUGI__FN bool xml_node::remove_attribute(const xml_attribute& a)
 	{
 		if (!_root || !a._attr) return false;
 
@@ -4108,17 +4474,17 @@
 		if (a._attr->prev_attribute_c->next_attribute) a._attr->prev_attribute_c->next_attribute = a._attr->next_attribute;
 		else _root->first_attribute = a._attr->next_attribute;
 
-		destroy_attribute(a._attr, get_allocator(_root));
+		impl::destroy_attribute(a._attr, impl::get_allocator(_root));
 
 		return true;
 	}
 
-	bool xml_node::remove_child(const char_t* name)
+	PUGI__FN bool xml_node::remove_child(const char_t* name_)
 	{
-		return remove_child(child(name));
+		return remove_child(child(name_));
 	}
 
-	bool xml_node::remove_child(const xml_node& n)
+	PUGI__FN bool xml_node::remove_child(const xml_node& n)
 	{
 		if (!_root || !n._root || n._root->parent != _root) return false;
 
@@ -4127,47 +4493,45 @@
 		
 		if (n._root->prev_sibling_c->next_sibling) n._root->prev_sibling_c->next_sibling = n._root->next_sibling;
 		else _root->first_child = n._root->next_sibling;
-        
-        destroy_node(n._root, get_allocator(_root));
+		
+		impl::destroy_node(n._root, impl::get_allocator(_root));
 
 		return true;
 	}
 
-	xml_node xml_node::find_child_by_attribute(const char_t* name, const char_t* attr_name, const char_t* attr_value) const
+	PUGI__FN xml_node xml_node::find_child_by_attribute(const char_t* name_, const char_t* attr_name, const char_t* attr_value) const
 	{
 		if (!_root) return xml_node();
 		
 		for (xml_node_struct* i = _root->first_child; i; i = i->next_sibling)
-			if (i->name && strequal(name, i->name))
+			if (i->name && impl::strequal(name_, i->name))
 			{
 				for (xml_attribute_struct* a = i->first_attribute; a; a = a->next_attribute)
-					if (strequal(attr_name, a->name) && strequal(attr_value, a->value))
+					if (impl::strequal(attr_name, a->name) && impl::strequal(attr_value, a->value))
 						return xml_node(i);
 			}
 
 		return xml_node();
 	}
 
-	xml_node xml_node::find_child_by_attribute(const char_t* attr_name, const char_t* attr_value) const
+	PUGI__FN xml_node xml_node::find_child_by_attribute(const char_t* attr_name, const char_t* attr_value) const
 	{
 		if (!_root) return xml_node();
 		
 		for (xml_node_struct* i = _root->first_child; i; i = i->next_sibling)
 			for (xml_attribute_struct* a = i->first_attribute; a; a = a->next_attribute)
-				if (strequal(attr_name, a->name) && strequal(attr_value, a->value))
+				if (impl::strequal(attr_name, a->name) && impl::strequal(attr_value, a->value))
 					return xml_node(i);
 
 		return xml_node();
 	}
 
 #ifndef PUGIXML_NO_STL
-	string_t xml_node::path(char_t delimiter) const
+	PUGI__FN string_t xml_node::path(char_t delimiter) const
 	{
-		string_t path;
-
 		xml_node cursor = *this; // Make a copy.
 		
-		path = cursor.name();
+		string_t result = cursor.name();
 
 		while (cursor.parent())
 		{
@@ -4175,28 +4539,28 @@
 			
 			string_t temp = cursor.name();
 			temp += delimiter;
-			temp += path;
-			path.swap(temp);
+			temp += result;
+			result.swap(temp);
 		}
 
-		return path;
+		return result;
 	}
 #endif
 
-	xml_node xml_node::first_element_by_path(const char_t* path, char_t delimiter) const
+	PUGI__FN xml_node xml_node::first_element_by_path(const char_t* path_, char_t delimiter) const
 	{
 		xml_node found = *this; // Current search context.
 
-		if (!_root || !path || !path[0]) return found;
+		if (!_root || !path_ || !path_[0]) return found;
 
-		if (path[0] == delimiter)
+		if (path_[0] == delimiter)
 		{
 			// Absolute path; e.g. '/foo/bar'
 			found = found.root();
-			++path;
+			++path_;
 		}
 
-		const char_t* path_segment = path;
+		const char_t* path_segment = path_;
 
 		while (*path_segment == delimiter) ++path_segment;
 
@@ -4218,7 +4582,7 @@
 		{
 			for (xml_node_struct* j = found._root->first_child; j; j = j->next_sibling)
 			{
-				if (j->name && strequalrange(j->name, path_segment, static_cast<size_t>(path_segment_end - path_segment)))
+				if (j->name && impl::strequalrange(j->name, path_segment, static_cast<size_t>(path_segment_end - path_segment)))
 				{
 					xml_node subsearch = xml_node(j).first_element_by_path(next_segment, delimiter);
 
@@ -4230,7 +4594,7 @@
 		}
 	}
 
-	bool xml_node::traverse(xml_tree_walker& walker)
+	PUGI__FN bool xml_node::traverse(xml_tree_walker& walker)
 	{
 		walker._depth = -1;
 		
@@ -4259,7 +4623,7 @@
 				else
 				{
 					// Borland C++ workaround
-					while (!cur.next_sibling() && cur != *this && (bool)cur.parent())
+					while (!cur.next_sibling() && cur != *this && !cur.parent().empty())
 					{
 						--walker._depth;
 						cur = cur.parent();
@@ -4278,34 +4642,34 @@
 		return walker.end(arg_end);
 	}
 
-    size_t xml_node::hash_value() const
-    {
-        return static_cast<size_t>(reinterpret_cast<uintptr_t>(_root) / sizeof(xml_node_struct));
-    }
+	PUGI__FN size_t xml_node::hash_value() const
+	{
+		return static_cast<size_t>(reinterpret_cast<uintptr_t>(_root) / sizeof(xml_node_struct));
+	}
 
-	xml_node_struct* xml_node::internal_object() const
+	PUGI__FN xml_node_struct* xml_node::internal_object() const
 	{
-        return _root;
+		return _root;
 	}
 
-	void xml_node::print(xml_writer& writer, const char_t* indent, unsigned int flags, xml_encoding encoding, unsigned int depth) const
+	PUGI__FN void xml_node::print(xml_writer& writer, const char_t* indent, unsigned int flags, xml_encoding encoding, unsigned int depth) const
 	{
 		if (!_root) return;
 
-		xml_buffered_writer buffered_writer(writer, encoding);
+		impl::xml_buffered_writer buffered_writer(writer, encoding);
 
-		node_output(buffered_writer, *this, indent, flags, depth);
+		impl::node_output(buffered_writer, *this, indent, flags, depth);
 	}
 
 #ifndef PUGIXML_NO_STL
-	void xml_node::print(std::basic_ostream<char, std::char_traits<char> >& stream, const char_t* indent, unsigned int flags, xml_encoding encoding, unsigned int depth) const
+	PUGI__FN void xml_node::print(std::basic_ostream<char, std::char_traits<char> >& stream, const char_t* indent, unsigned int flags, xml_encoding encoding, unsigned int depth) const
 	{
 		xml_writer_stream writer(stream);
 
 		print(writer, indent, flags, encoding, depth);
 	}
 
-	void xml_node::print(std::basic_ostream<wchar_t, std::char_traits<wchar_t> >& stream, const char_t* indent, unsigned int flags, unsigned int depth) const
+	PUGI__FN void xml_node::print(std::basic_ostream<wchar_t, std::char_traits<wchar_t> >& stream, const char_t* indent, unsigned int flags, unsigned int depth) const
 	{
 		xml_writer_stream writer(stream);
 
@@ -4313,13 +4677,13 @@
 	}
 #endif
 
-	ptrdiff_t xml_node::offset_debug() const
+	PUGI__FN ptrdiff_t xml_node::offset_debug() const
 	{
 		xml_node_struct* r = root()._root;
 
 		if (!r) return -1;
 
-		const char_t* buffer = static_cast<xml_document_struct*>(r)->buffer;
+		const char_t* buffer = static_cast<impl::xml_document_struct*>(r)->buffer;
 
 		if (!buffer) return -1;
 
@@ -4331,13 +4695,13 @@
 		case node_element:
 		case node_declaration:
 		case node_pi:
-			return (_root->header & xml_memory_page_name_allocated_mask) ? -1 : _root->name - buffer;
+			return (_root->header & impl::xml_memory_page_name_allocated_mask) ? -1 : _root->name - buffer;
 
 		case node_pcdata:
 		case node_cdata:
 		case node_comment:
 		case node_doctype:
-			return (_root->header & xml_memory_page_value_allocated_mask) ? -1 : _root->value - buffer;
+			return (_root->header & impl::xml_memory_page_value_allocated_mask) ? -1 : _root->value - buffer;
 
 		default:
 			return -1;
@@ -4345,149 +4709,370 @@
 	}
 
 #ifdef __BORLANDC__
-	bool operator&&(const xml_node& lhs, bool rhs)
+	PUGI__FN bool operator&&(const xml_node& lhs, bool rhs)
 	{
 		return (bool)lhs && rhs;
 	}
 
-	bool operator||(const xml_node& lhs, bool rhs)
+	PUGI__FN bool operator||(const xml_node& lhs, bool rhs)
 	{
 		return (bool)lhs || rhs;
 	}
 #endif
 
-	xml_node_iterator::xml_node_iterator()
+	PUGI__FN xml_text::xml_text(xml_node_struct* root): _root(root)
 	{
 	}
 
-	xml_node_iterator::xml_node_iterator(const xml_node& node): _wrap(node), _parent(node.parent())
+	PUGI__FN xml_node_struct* xml_text::_data() const
 	{
+		if (!_root || impl::is_text_node(_root)) return _root;
+
+		for (xml_node_struct* node = _root->first_child; node; node = node->next_sibling)
+			if (impl::is_text_node(node))
+				return node;
+
+		return 0;
 	}
 
-	xml_node_iterator::xml_node_iterator(xml_node_struct* ref, xml_node_struct* parent): _wrap(ref), _parent(parent)
+	PUGI__FN xml_node_struct* xml_text::_data_new()
+	{
+		xml_node_struct* d = _data();
+		if (d) return d;
+
+		return xml_node(_root).append_child(node_pcdata).internal_object();
+	}
+
+	PUGI__FN xml_text::xml_text(): _root(0)
 	{
 	}
 
-	bool xml_node_iterator::operator==(const xml_node_iterator& rhs) const
+	PUGI__FN static void unspecified_bool_xml_text(xml_text***)
+	{
+	}
+
+	PUGI__FN xml_text::operator xml_text::unspecified_bool_type() const
+	{
+		return _data() ? unspecified_bool_xml_text : 0;
+	}
+
+	PUGI__FN bool xml_text::operator!() const
+	{
+		return !_data();
+	}
+
+	PUGI__FN bool xml_text::empty() const
+	{
+		return _data() == 0;
+	}
+
+	PUGI__FN const char_t* xml_text::get() const
+	{
+		xml_node_struct* d = _data();
+
+		return (d && d->value) ? d->value : PUGIXML_TEXT("");
+	}
+
+	PUGI__FN const char_t* xml_text::as_string(const char_t* def) const
+	{
+		xml_node_struct* d = _data();
+
+		return (d && d->value) ? d->value : def;
+	}
+
+	PUGI__FN int xml_text::as_int(int def) const
+	{
+		xml_node_struct* d = _data();
+
+		return impl::get_value_int(d ? d->value : 0, def);
+	}
+
+	PUGI__FN unsigned int xml_text::as_uint(unsigned int def) const
+	{
+		xml_node_struct* d = _data();
+
+		return impl::get_value_uint(d ? d->value : 0, def);
+	}
+
+	PUGI__FN double xml_text::as_double(double def) const
+	{
+		xml_node_struct* d = _data();
+
+		return impl::get_value_double(d ? d->value : 0, def);
+	}
+
+	PUGI__FN float xml_text::as_float(float def) const
+	{
+		xml_node_struct* d = _data();
+
+		return impl::get_value_float(d ? d->value : 0, def);
+	}
+
+	PUGI__FN bool xml_text::as_bool(bool def) const
+	{
+		xml_node_struct* d = _data();
+
+		return impl::get_value_bool(d ? d->value : 0, def);
+	}
+
+	PUGI__FN bool xml_text::set(const char_t* rhs)
+	{
+		xml_node_struct* dn = _data_new();
+
+		return dn ? impl::strcpy_insitu(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs) : false;
+	}
+
+	PUGI__FN bool xml_text::set(int rhs)
+	{
+		xml_node_struct* dn = _data_new();
+
+		return dn ? impl::set_value_convert(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs) : false;
+	}
+
+	PUGI__FN bool xml_text::set(unsigned int rhs)
+	{
+		xml_node_struct* dn = _data_new();
+
+		return dn ? impl::set_value_convert(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs) : false;
+	}
+
+	PUGI__FN bool xml_text::set(double rhs)
+	{
+		xml_node_struct* dn = _data_new();
+
+		return dn ? impl::set_value_convert(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs) : false;
+	}
+
+	PUGI__FN bool xml_text::set(bool rhs)
+	{
+		xml_node_struct* dn = _data_new();
+
+		return dn ? impl::set_value_convert(dn->value, dn->header, impl::xml_memory_page_value_allocated_mask, rhs) : false;
+	}
+
+	PUGI__FN xml_text& xml_text::operator=(const char_t* rhs)
+	{
+		set(rhs);
+		return *this;
+	}
+
+	PUGI__FN xml_text& xml_text::operator=(int rhs)
+	{
+		set(rhs);
+		return *this;
+	}
+
+	PUGI__FN xml_text& xml_text::operator=(unsigned int rhs)
+	{
+		set(rhs);
+		return *this;
+	}
+
+	PUGI__FN xml_text& xml_text::operator=(double rhs)
+	{
+		set(rhs);
+		return *this;
+	}
+
+	PUGI__FN xml_text& xml_text::operator=(bool rhs)
+	{
+		set(rhs);
+		return *this;
+	}
+
+	PUGI__FN xml_node xml_text::data() const
+	{
+		return xml_node(_data());
+	}
+
+#ifdef __BORLANDC__
+	PUGI__FN bool operator&&(const xml_text& lhs, bool rhs)
+	{
+		return (bool)lhs && rhs;
+	}
+
+	PUGI__FN bool operator||(const xml_text& lhs, bool rhs)
+	{
+		return (bool)lhs || rhs;
+	}
+#endif
+
+	PUGI__FN xml_node_iterator::xml_node_iterator()
+	{
+	}
+
+	PUGI__FN xml_node_iterator::xml_node_iterator(const xml_node& node): _wrap(node), _parent(node.parent())
+	{
+	}
+
+	PUGI__FN xml_node_iterator::xml_node_iterator(xml_node_struct* ref, xml_node_struct* parent): _wrap(ref), _parent(parent)
+	{
+	}
+
+	PUGI__FN bool xml_node_iterator::operator==(const xml_node_iterator& rhs) const
 	{
 		return _wrap._root == rhs._wrap._root && _parent._root == rhs._parent._root;
 	}
 	
-	bool xml_node_iterator::operator!=(const xml_node_iterator& rhs) const
+	PUGI__FN bool xml_node_iterator::operator!=(const xml_node_iterator& rhs) const
 	{
 		return _wrap._root != rhs._wrap._root || _parent._root != rhs._parent._root;
 	}
 
-	xml_node& xml_node_iterator::operator*()
+	PUGI__FN xml_node& xml_node_iterator::operator*() const
 	{
 		assert(_wrap._root);
 		return _wrap;
 	}
 
-	xml_node* xml_node_iterator::operator->()
+	PUGI__FN xml_node* xml_node_iterator::operator->() const
 	{
 		assert(_wrap._root);
-		return &_wrap;
+		return const_cast<xml_node*>(&_wrap); // BCC32 workaround
 	}
 
-	const xml_node_iterator& xml_node_iterator::operator++()
+	PUGI__FN const xml_node_iterator& xml_node_iterator::operator++()
 	{
 		assert(_wrap._root);
 		_wrap._root = _wrap._root->next_sibling;
 		return *this;
 	}
 
-	xml_node_iterator xml_node_iterator::operator++(int)
+	PUGI__FN xml_node_iterator xml_node_iterator::operator++(int)
 	{
 		xml_node_iterator temp = *this;
 		++*this;
 		return temp;
 	}
 
-	const xml_node_iterator& xml_node_iterator::operator--()
+	PUGI__FN const xml_node_iterator& xml_node_iterator::operator--()
 	{
 		_wrap = _wrap._root ? _wrap.previous_sibling() : _parent.last_child();
 		return *this;
 	}
 
-	xml_node_iterator xml_node_iterator::operator--(int)
+	PUGI__FN xml_node_iterator xml_node_iterator::operator--(int)
 	{
 		xml_node_iterator temp = *this;
 		--*this;
 		return temp;
 	}
 
-	xml_attribute_iterator::xml_attribute_iterator()
+	PUGI__FN xml_attribute_iterator::xml_attribute_iterator()
 	{
 	}
 
-	xml_attribute_iterator::xml_attribute_iterator(const xml_attribute& attr, const xml_node& parent): _wrap(attr), _parent(parent)
+	PUGI__FN xml_attribute_iterator::xml_attribute_iterator(const xml_attribute& attr, const xml_node& parent): _wrap(attr), _parent(parent)
 	{
 	}
 
-	xml_attribute_iterator::xml_attribute_iterator(xml_attribute_struct* ref, xml_node_struct* parent): _wrap(ref), _parent(parent)
+	PUGI__FN xml_attribute_iterator::xml_attribute_iterator(xml_attribute_struct* ref, xml_node_struct* parent): _wrap(ref), _parent(parent)
 	{
 	}
 
-	bool xml_attribute_iterator::operator==(const xml_attribute_iterator& rhs) const
+	PUGI__FN bool xml_attribute_iterator::operator==(const xml_attribute_iterator& rhs) const
 	{
 		return _wrap._attr == rhs._wrap._attr && _parent._root == rhs._parent._root;
 	}
 	
-	bool xml_attribute_iterator::operator!=(const xml_attribute_iterator& rhs) const
+	PUGI__FN bool xml_attribute_iterator::operator!=(const xml_attribute_iterator& rhs) const
 	{
 		return _wrap._attr != rhs._wrap._attr || _parent._root != rhs._parent._root;
 	}
 
-	xml_attribute& xml_attribute_iterator::operator*()
+	PUGI__FN xml_attribute& xml_attribute_iterator::operator*() const
 	{
 		assert(_wrap._attr);
 		return _wrap;
 	}
 
-	xml_attribute* xml_attribute_iterator::operator->()
+	PUGI__FN xml_attribute* xml_attribute_iterator::operator->() const
 	{
 		assert(_wrap._attr);
-		return &_wrap;
+		return const_cast<xml_attribute*>(&_wrap); // BCC32 workaround
 	}
 
-	const xml_attribute_iterator& xml_attribute_iterator::operator++()
+	PUGI__FN const xml_attribute_iterator& xml_attribute_iterator::operator++()
 	{
 		assert(_wrap._attr);
 		_wrap._attr = _wrap._attr->next_attribute;
 		return *this;
 	}
 
-	xml_attribute_iterator xml_attribute_iterator::operator++(int)
+	PUGI__FN xml_attribute_iterator xml_attribute_iterator::operator++(int)
 	{
 		xml_attribute_iterator temp = *this;
 		++*this;
 		return temp;
 	}
 
-	const xml_attribute_iterator& xml_attribute_iterator::operator--()
+	PUGI__FN const xml_attribute_iterator& xml_attribute_iterator::operator--()
 	{
 		_wrap = _wrap._attr ? _wrap.previous_attribute() : _parent.last_attribute();
 		return *this;
 	}
 
-	xml_attribute_iterator xml_attribute_iterator::operator--(int)
+	PUGI__FN xml_attribute_iterator xml_attribute_iterator::operator--(int)
 	{
 		xml_attribute_iterator temp = *this;
 		--*this;
 		return temp;
 	}
 
-    xml_parse_result::xml_parse_result(): status(status_internal_error), offset(0), encoding(encoding_auto)
-    {
-    }
+	PUGI__FN xml_named_node_iterator::xml_named_node_iterator(): _name(0)
+	{
+	}
 
-    xml_parse_result::operator bool() const
-    {
-        return status == status_ok;
-    }
+	PUGI__FN xml_named_node_iterator::xml_named_node_iterator(const xml_node& node, const char_t* name): _node(node), _name(name)
+	{
+	}
 
-	const char* xml_parse_result::description() const
+	PUGI__FN bool xml_named_node_iterator::operator==(const xml_named_node_iterator& rhs) const
+	{
+		return _node == rhs._node;
+	}
+
+	PUGI__FN bool xml_named_node_iterator::operator!=(const xml_named_node_iterator& rhs) const
+	{
+		return _node != rhs._node;
+	}
+
+	PUGI__FN xml_node& xml_named_node_iterator::operator*() const
+	{
+		assert(_node._root);
+		return _node;
+	}
+
+	PUGI__FN xml_node* xml_named_node_iterator::operator->() const
+	{
+		assert(_node._root);
+		return const_cast<xml_node*>(&_node); // BCC32 workaround
+	}
+
+	PUGI__FN const xml_named_node_iterator& xml_named_node_iterator::operator++()
+	{
+		assert(_node._root);
+		_node = _node.next_sibling(_name);
+		return *this;
+	}
+
+	PUGI__FN xml_named_node_iterator xml_named_node_iterator::operator++(int)
+	{
+		xml_named_node_iterator temp = *this;
+		++*this;
+		return temp;
+	}
+
+	PUGI__FN xml_parse_result::xml_parse_result(): status(status_internal_error), offset(0), encoding(encoding_auto)
+	{
+	}
+
+	PUGI__FN xml_parse_result::operator bool() const
+	{
+		return status == status_ok;
+	}
+
+	PUGI__FN const char* xml_parse_result::description() const
 	{
 		switch (status)
 		{
@@ -4514,72 +5099,72 @@
 		}
 	}
 
-	xml_document::xml_document(): _buffer(0)
+	PUGI__FN xml_document::xml_document(): _buffer(0)
 	{
 		create();
 	}
 
-	xml_document::~xml_document()
+	PUGI__FN xml_document::~xml_document()
 	{
 		destroy();
 	}
 
-	void xml_document::reset()
+	PUGI__FN void xml_document::reset()
 	{
 		destroy();
 		create();
 	}
 
-    void xml_document::reset(const xml_document& proto)
-    {
-        reset();
+	PUGI__FN void xml_document::reset(const xml_document& proto)
+	{
+		reset();
 
-        for (xml_node cur = proto.first_child(); cur; cur = cur.next_sibling())
-            append_copy(cur);
-    }
+		for (xml_node cur = proto.first_child(); cur; cur = cur.next_sibling())
+			append_copy(cur);
+	}
 
-	void xml_document::create()
+	PUGI__FN void xml_document::create()
 	{
 		// initialize sentinel page
-		STATIC_ASSERT(offsetof(xml_memory_page, data) + sizeof(xml_document_struct) + xml_memory_page_alignment <= sizeof(_memory));
+		PUGI__STATIC_ASSERT(offsetof(impl::xml_memory_page, data) + sizeof(impl::xml_document_struct) + impl::xml_memory_page_alignment <= sizeof(_memory));
 
 		// align upwards to page boundary
-		void* page_memory = reinterpret_cast<void*>((reinterpret_cast<uintptr_t>(_memory) + (xml_memory_page_alignment - 1)) & ~(xml_memory_page_alignment - 1));
+		void* page_memory = reinterpret_cast<void*>((reinterpret_cast<uintptr_t>(_memory) + (impl::xml_memory_page_alignment - 1)) & ~(impl::xml_memory_page_alignment - 1));
 
 		// prepare page structure
-		xml_memory_page* page = xml_memory_page::construct(page_memory);
+		impl::xml_memory_page* page = impl::xml_memory_page::construct(page_memory);
 
-		page->busy_size = xml_memory_page_size;
+		page->busy_size = impl::xml_memory_page_size;
 
 		// allocate new root
-		_root = new (page->data) xml_document_struct(page);
+		_root = new (page->data) impl::xml_document_struct(page);
 		_root->prev_sibling_c = _root;
 
 		// setup sentinel page
-		page->allocator = static_cast<xml_document_struct*>(_root);
+		page->allocator = static_cast<impl::xml_document_struct*>(_root);
 	}
 
-	void xml_document::destroy()
+	PUGI__FN void xml_document::destroy()
 	{
 		// destroy static storage
 		if (_buffer)
 		{
-			global_deallocate(_buffer);
+			impl::xml_memory::deallocate(_buffer);
 			_buffer = 0;
 		}
 
 		// destroy dynamic storage, leave sentinel page (it's in static memory)
 		if (_root)
 		{
-			xml_memory_page* root_page = reinterpret_cast<xml_memory_page*>(_root->header & xml_memory_page_pointer_mask);
+			impl::xml_memory_page* root_page = reinterpret_cast<impl::xml_memory_page*>(_root->header & impl::xml_memory_page_pointer_mask);
 			assert(root_page && !root_page->prev && !root_page->memory);
 
 			// destroy all pages
-			for (xml_memory_page* page = root_page->next; page; )
+			for (impl::xml_memory_page* page = root_page->next; page; )
 			{
-				xml_memory_page* next = page->next;
+				impl::xml_memory_page* next = page->next;
 
-				xml_allocator::deallocate_page(page);
+				impl::xml_allocator::deallocate_page(page);
 
 				page = next;
 			}
@@ -4594,22 +5179,22 @@
 	}
 
 #ifndef PUGIXML_NO_STL
-	xml_parse_result xml_document::load(std::basic_istream<char, std::char_traits<char> >& stream, unsigned int options, xml_encoding encoding)
+	PUGI__FN xml_parse_result xml_document::load(std::basic_istream<char, std::char_traits<char> >& stream, unsigned int options, xml_encoding encoding)
 	{
 		reset();
 
-		return load_stream_impl(*this, stream, options, encoding);
+		return impl::load_stream_impl(*this, stream, options, encoding);
 	}
 
-	xml_parse_result xml_document::load(std::basic_istream<wchar_t, std::char_traits<wchar_t> >& stream, unsigned int options)
+	PUGI__FN xml_parse_result xml_document::load(std::basic_istream<wchar_t, std::char_traits<wchar_t> >& stream, unsigned int options)
 	{
 		reset();
 
-		return load_stream_impl(*this, stream, options, encoding_wchar);
+		return impl::load_stream_impl(*this, stream, options, encoding_wchar);
 	}
 #endif
 
-	xml_parse_result xml_document::load(const char_t* contents, unsigned int options)
+	PUGI__FN xml_parse_result xml_document::load(const char_t* contents, unsigned int options)
 	{
 		// Force native encoding (skip autodetection)
 	#ifdef PUGIXML_WCHAR_MODE
@@ -4618,28 +5203,28 @@
 		xml_encoding encoding = encoding_utf8;
 	#endif
 
-		return load_buffer(contents, strlength(contents) * sizeof(char_t), options, encoding);
+		return load_buffer(contents, impl::strlength(contents) * sizeof(char_t), options, encoding);
 	}
 
-	xml_parse_result xml_document::load_file(const char* path, unsigned int options, xml_encoding encoding)
+	PUGI__FN xml_parse_result xml_document::load_file(const char* path_, unsigned int options, xml_encoding encoding)
 	{
 		reset();
 
-		FILE* file = fopen(path, "rb");
+		FILE* file = fopen(path_, "rb");
 
-		return load_file_impl(*this, file, options, encoding);
+		return impl::load_file_impl(*this, file, options, encoding);
 	}
 
-	xml_parse_result xml_document::load_file(const wchar_t* path, unsigned int options, xml_encoding encoding)
+	PUGI__FN xml_parse_result xml_document::load_file(const wchar_t* path_, unsigned int options, xml_encoding encoding)
 	{
 		reset();
 
-		FILE* file = open_file_wide(path, L"rb");
+		FILE* file = impl::open_file_wide(path_, L"rb");
 
-		return load_file_impl(*this, file, options, encoding);
+		return impl::load_file_impl(*this, file, options, encoding);
 	}
 
-	xml_parse_result xml_document::load_buffer_impl(void* contents, size_t size, unsigned int options, xml_encoding encoding, bool is_mutable, bool own)
+	PUGI__FN xml_parse_result xml_document::load_buffer_impl(void* contents, size_t size, unsigned int options, xml_encoding encoding, bool is_mutable, bool own)
 	{
 		reset();
 
@@ -4647,19 +5232,19 @@
 		assert(contents || size == 0);
 
 		// get actual encoding
-		xml_encoding buffer_encoding = get_buffer_encoding(encoding, contents, size);
+		xml_encoding buffer_encoding = impl::get_buffer_encoding(encoding, contents, size);
 
 		// get private buffer
 		char_t* buffer = 0;
 		size_t length = 0;
 
-		if (!convert_buffer(buffer, length, buffer_encoding, contents, size, is_mutable)) return make_parse_result(status_out_of_memory);
+		if (!impl::convert_buffer(buffer, length, buffer_encoding, contents, size, is_mutable)) return impl::make_parse_result(status_out_of_memory);
 		
 		// delete original buffer if we performed a conversion
-		if (own && buffer != contents && contents) global_deallocate(contents);
+		if (own && buffer != contents && contents) impl::xml_memory::deallocate(contents);
 
 		// parse
-		xml_parse_result res = xml_parser::parse(buffer, length, _root, options);
+		xml_parse_result res = impl::xml_parser::parse(buffer, length, _root, options);
 
 		// remember encoding
 		res.encoding = buffer_encoding;
@@ -4670,45 +5255,56 @@
 		return res;
 	}
 
-	xml_parse_result xml_document::load_buffer(const void* contents, size_t size, unsigned int options, xml_encoding encoding)
+	PUGI__FN xml_parse_result xml_document::load_buffer(const void* contents, size_t size, unsigned int options, xml_encoding encoding)
 	{
 		return load_buffer_impl(const_cast<void*>(contents), size, options, encoding, false, false);
 	}
 
-	xml_parse_result xml_document::load_buffer_inplace(void* contents, size_t size, unsigned int options, xml_encoding encoding)
+	PUGI__FN xml_parse_result xml_document::load_buffer_inplace(void* contents, size_t size, unsigned int options, xml_encoding encoding)
 	{
 		return load_buffer_impl(contents, size, options, encoding, true, false);
 	}
 		
-	xml_parse_result xml_document::load_buffer_inplace_own(void* contents, size_t size, unsigned int options, xml_encoding encoding)
+	PUGI__FN xml_parse_result xml_document::load_buffer_inplace_own(void* contents, size_t size, unsigned int options, xml_encoding encoding)
 	{
 		return load_buffer_impl(contents, size, options, encoding, true, true);
 	}
 
-	void xml_document::save(xml_writer& writer, const char_t* indent, unsigned int flags, xml_encoding encoding) const
+	PUGI__FN void xml_document::save(xml_writer& writer, const char_t* indent, unsigned int flags, xml_encoding encoding) const
 	{
-		if (flags & format_write_bom) write_bom(writer, get_write_encoding(encoding));
+		impl::xml_buffered_writer buffered_writer(writer, encoding);
 
-		xml_buffered_writer buffered_writer(writer, encoding);
+		if ((flags & format_write_bom) && encoding != encoding_latin1)
+		{
+			// BOM always represents the codepoint U+FEFF, so just write it in native encoding
+		#ifdef PUGIXML_WCHAR_MODE
+			unsigned int bom = 0xfeff;
+			buffered_writer.write(static_cast<wchar_t>(bom));
+		#else
+			buffered_writer.write('\xef', '\xbb', '\xbf');
+		#endif
+		}
 
-		if (!(flags & format_no_declaration) && !has_declaration(*this))
+		if (!(flags & format_no_declaration) && !impl::has_declaration(*this))
 		{
-			buffered_writer.write(PUGIXML_TEXT("<?xml version=\"1.0\"?>"));
+			buffered_writer.write(PUGIXML_TEXT("<?xml version=\"1.0\""));
+			if (encoding == encoding_latin1) buffered_writer.write(PUGIXML_TEXT(" encoding=\"ISO-8859-1\""));
+			buffered_writer.write('?', '>');
 			if (!(flags & format_raw)) buffered_writer.write('\n');
 		}
 
-		node_output(buffered_writer, *this, indent, flags, 0);
+		impl::node_output(buffered_writer, *this, indent, flags, 0);
 	}
 
 #ifndef PUGIXML_NO_STL
-	void xml_document::save(std::basic_ostream<char, std::char_traits<char> >& stream, const char_t* indent, unsigned int flags, xml_encoding encoding) const
+	PUGI__FN void xml_document::save(std::basic_ostream<char, std::char_traits<char> >& stream, const char_t* indent, unsigned int flags, xml_encoding encoding) const
 	{
 		xml_writer_stream writer(stream);
 
 		save(writer, indent, flags, encoding);
 	}
 
-	void xml_document::save(std::basic_ostream<wchar_t, std::char_traits<wchar_t> >& stream, const char_t* indent, unsigned int flags) const
+	PUGI__FN void xml_document::save(std::basic_ostream<wchar_t, std::char_traits<wchar_t> >& stream, const char_t* indent, unsigned int flags) const
 	{
 		xml_writer_stream writer(stream);
 
@@ -4716,102 +5312,88 @@
 	}
 #endif
 
-	bool xml_document::save_file(const char* path, const char_t* indent, unsigned int flags, xml_encoding encoding) const
+	PUGI__FN bool xml_document::save_file(const char* path_, const char_t* indent, unsigned int flags, xml_encoding encoding) const
 	{
-		FILE* file = fopen(path, "wb");
-		if (!file) return false;
-
-		xml_writer_file writer(file);
-		save(writer, indent, flags, encoding);
-
-		fclose(file);
-
-		return true;
+		FILE* file = fopen(path_, (flags & format_save_file_text) ? "w" : "wb");
+		return impl::save_file_impl(*this, file, indent, flags, encoding);
 	}
 
-	bool xml_document::save_file(const wchar_t* path, const char_t* indent, unsigned int flags, xml_encoding encoding) const
+	PUGI__FN bool xml_document::save_file(const wchar_t* path_, const char_t* indent, unsigned int flags, xml_encoding encoding) const
 	{
-		FILE* file = open_file_wide(path, L"wb");
-		if (!file) return false;
-
-		xml_writer_file writer(file);
-		save(writer, indent, flags, encoding);
-
-		fclose(file);
-
-		return true;
+		FILE* file = impl::open_file_wide(path_, (flags & format_save_file_text) ? L"w" : L"wb");
+		return impl::save_file_impl(*this, file, indent, flags, encoding);
 	}
 
-    xml_node xml_document::document_element() const
-    {
+	PUGI__FN xml_node xml_document::document_element() const
+	{
 		for (xml_node_struct* i = _root->first_child; i; i = i->next_sibling)
-			if ((i->header & xml_memory_page_type_mask) + 1 == node_element)
-                return xml_node(i);
+			if ((i->header & impl::xml_memory_page_type_mask) + 1 == node_element)
+				return xml_node(i);
 
-        return xml_node();
-    }
+		return xml_node();
+	}
 
 #ifndef PUGIXML_NO_STL
-	std::string PUGIXML_FUNCTION as_utf8(const wchar_t* str)
+	PUGI__FN std::string PUGIXML_FUNCTION as_utf8(const wchar_t* str)
 	{
 		assert(str);
 
-        return as_utf8_impl(str, wcslen(str));
+		return impl::as_utf8_impl(str, wcslen(str));
 	}
 
-	std::string PUGIXML_FUNCTION as_utf8(const std::wstring& str)
+	PUGI__FN std::string PUGIXML_FUNCTION as_utf8(const std::basic_string<wchar_t>& str)
 	{
-        return as_utf8_impl(str.c_str(), str.size());
+		return impl::as_utf8_impl(str.c_str(), str.size());
 	}
 	
-	std::wstring PUGIXML_FUNCTION as_wide(const char* str)
+	PUGI__FN std::basic_string<wchar_t> PUGIXML_FUNCTION as_wide(const char* str)
 	{
 		assert(str);
 
-        return as_wide_impl(str, strlen(str));
+		return impl::as_wide_impl(str, strlen(str));
 	}
 	
-	std::wstring PUGIXML_FUNCTION as_wide(const std::string& str)
+	PUGI__FN std::basic_string<wchar_t> PUGIXML_FUNCTION as_wide(const std::string& str)
 	{
-        return as_wide_impl(str.c_str(), str.size());
+		return impl::as_wide_impl(str.c_str(), str.size());
 	}
 #endif
 
-    void PUGIXML_FUNCTION set_memory_management_functions(allocation_function allocate, deallocation_function deallocate)
-    {
-    	global_allocate = allocate;
-    	global_deallocate = deallocate;
-    }
-
-    allocation_function PUGIXML_FUNCTION get_memory_allocation_function()
-    {
-    	return global_allocate;
-    }
+	PUGI__FN void PUGIXML_FUNCTION set_memory_management_functions(allocation_function allocate, deallocation_function deallocate)
+	{
+		impl::xml_memory::allocate = allocate;
+		impl::xml_memory::deallocate = deallocate;
+	}
 
-    deallocation_function PUGIXML_FUNCTION get_memory_deallocation_function()
-    {
-    	return global_deallocate;
-    }
-}
+	PUGI__FN allocation_function PUGIXML_FUNCTION get_memory_allocation_function()
+	{
+		return impl::xml_memory::allocate;
+	}
 
-// Added by LG for OpenImageIO:
+	PUGI__FN deallocation_function PUGIXML_FUNCTION get_memory_deallocation_function()
+	{
+		return impl::xml_memory::deallocate;
+	}
 }
-OIIO_NAMESPACE_EXIT
-
 
 #if !defined(PUGIXML_NO_STL) && (defined(_MSC_VER) || defined(__ICC))
 namespace std
 {
 	// Workarounds for (non-standard) iterator category detection for older versions (MSVC7/IC8 and earlier)
-	std::bidirectional_iterator_tag _Iter_cat(const xml_node_iterator&)
+	PUGI__FN std::bidirectional_iterator_tag _Iter_cat(const pugi::xml_node_iterator&)
 	{
 		return std::bidirectional_iterator_tag();
 	}
 
-	std::bidirectional_iterator_tag _Iter_cat(const xml_attribute_iterator&)
+	PUGI__FN std::bidirectional_iterator_tag _Iter_cat(const pugi::xml_attribute_iterator&)
 	{
 		return std::bidirectional_iterator_tag();
 	}
+
+	PUGI__FN std::forward_iterator_tag _Iter_cat(const pugi::xml_named_node_iterator&)
+	{
+		return std::forward_iterator_tag();
+	}
 }
 #endif
 
@@ -4819,23 +5401,27 @@
 namespace std
 {
 	// Workarounds for (non-standard) iterator category detection
-	std::bidirectional_iterator_tag __iterator_category(const xml_node_iterator&)
+	PUGI__FN std::bidirectional_iterator_tag __iterator_category(const pugi::xml_node_iterator&)
 	{
 		return std::bidirectional_iterator_tag();
 	}
 
-	std::bidirectional_iterator_tag __iterator_category(const xml_attribute_iterator&)
+	PUGI__FN std::bidirectional_iterator_tag __iterator_category(const pugi::xml_attribute_iterator&)
 	{
 		return std::bidirectional_iterator_tag();
 	}
+
+	PUGI__FN std::forward_iterator_tag __iterator_category(const pugi::xml_named_node_iterator&)
+	{
+		return std::forward_iterator_tag();
+	}
 }
 #endif
 
 #ifndef PUGIXML_NO_XPATH
 
 // STL replacements
-namespace
-{
+PUGI__NS_BEGIN
 	struct equal_to
 	{
 		template <typename T> bool operator()(const T& lhs, const T& rhs) const
@@ -5059,16 +5645,21 @@
 		// insertion sort small chunk
 		if (begin != end) insertion_sort(begin, end, pred, &*begin);
 	}
-}
+PUGI__NS_END
 
 // Allocator used for AST and evaluation stacks
-namespace
-{
+PUGI__NS_BEGIN
 	struct xpath_memory_block
 	{	
 		xpath_memory_block* next;
 
-		char data[4096];
+		char data[
+	#ifdef PUGIXML_MEMORY_XPATH_PAGE_SIZE
+			PUGIXML_MEMORY_XPATH_PAGE_SIZE
+	#else
+			4096
+	#endif
+		];
 	};
 		
 	class xpath_allocator
@@ -5106,7 +5697,7 @@
 				size_t block_data_size = (size > block_capacity) ? size : block_capacity;
 				size_t block_size = block_data_size + offsetof(xpath_memory_block, data);
 
-				xpath_memory_block* block = static_cast<xpath_memory_block*>(global_allocate(block_size));
+				xpath_memory_block* block = static_cast<xpath_memory_block*>(xml_memory::allocate(block_size));
 				if (!block) return 0;
 				
 				block->next = _root;
@@ -5171,7 +5762,7 @@
 					if (next)
 					{
 						// deallocate the whole page, unless it was the first one
-						global_deallocate(_root->next);
+						xml_memory::deallocate(_root->next);
 						_root->next = next;
 					}
 				}
@@ -5189,7 +5780,7 @@
 			{
 				xpath_memory_block* next = cur->next;
 
-				global_deallocate(cur);
+				xml_memory::deallocate(cur);
 
 				cur = next;
 			}
@@ -5208,7 +5799,7 @@
 			{
 				xpath_memory_block* next = cur->next;
 
-				global_deallocate(cur);
+				xml_memory::deallocate(cur);
 
 				cur = next;
 			}
@@ -5265,11 +5856,10 @@
 			temp.release();
 		}
 	};
-}
+PUGI__NS_END
 
 // String class
-namespace
-{
+PUGI__NS_BEGIN
 	class xpath_string
 	{
 		const char_t* _buffer;
@@ -5298,10 +5888,10 @@
 
 		explicit xpath_string(const char_t* str, xpath_allocator* alloc)
 		{
-			bool empty = (*str == 0);
+			bool empty_ = (*str == 0);
 
-			_buffer = empty ? PUGIXML_TEXT("") : duplicate_string(str, alloc);
-			_uses_heap = !empty;
+			_buffer = empty_ ? PUGIXML_TEXT("") : duplicate_string(str, alloc);
+			_uses_heap = !empty_;
 		}
 
 		explicit xpath_string(const char_t* str, bool use_heap): _buffer(str), _uses_heap(use_heap)
@@ -5312,10 +5902,10 @@
 		{
 			assert(begin <= end);
 
-			bool empty = (begin == end);
+			bool empty_ = (begin == end);
 
-			_buffer = empty ? PUGIXML_TEXT("") : duplicate_string(begin, static_cast<size_t>(end - begin), alloc);
-			_uses_heap = !empty;
+			_buffer = empty_ ? PUGIXML_TEXT("") : duplicate_string(begin, static_cast<size_t>(end - begin), alloc);
+			_uses_heap = !empty_;
 		}
 
 		void append(const xpath_string& o, xpath_allocator* alloc)
@@ -5333,10 +5923,10 @@
 				// need to make heap copy
 				size_t target_length = strlength(_buffer);
 				size_t source_length = strlength(o._buffer);
-				size_t length = target_length + source_length;
+				size_t result_length = target_length + source_length;
 
 				// allocate new buffer
-				char_t* result = static_cast<char_t*>(alloc->reallocate(_uses_heap ? const_cast<char_t*>(_buffer) : 0, (target_length + 1) * sizeof(char_t), (length + 1) * sizeof(char_t)));
+				char_t* result = static_cast<char_t*>(alloc->reallocate(_uses_heap ? const_cast<char_t*>(_buffer) : 0, (target_length + 1) * sizeof(char_t), (result_length + 1) * sizeof(char_t)));
 				assert(result);
 
 				// append first string to the new buffer in case there was no reallocation
@@ -5344,7 +5934,7 @@
 
 				// append second string to the new buffer
 				memcpy(result + target_length, o._buffer, source_length * sizeof(char_t));
-				result[length] = 0;
+				result[result_length] = 0;
 
 				// finalize
 				_buffer = result;
@@ -5395,15 +5985,14 @@
 		}
 	};
 
-	xpath_string xpath_string_const(const char_t* str)
+	PUGI__FN xpath_string xpath_string_const(const char_t* str)
 	{
 		return xpath_string(str, false);
 	}
-}
+PUGI__NS_END
 
-namespace
-{
-	bool starts_with(const char_t* string, const char_t* pattern)
+PUGI__NS_BEGIN
+	PUGI__FN bool starts_with(const char_t* string, const char_t* pattern)
 	{
 		while (*pattern && *string == *pattern)
 		{
@@ -5414,7 +6003,7 @@
 		return *pattern == 0;
 	}
 
-	const char_t* find_char(const char_t* s, char_t c)
+	PUGI__FN const char_t* find_char(const char_t* s, char_t c)
 	{
 	#ifdef PUGIXML_WCHAR_MODE
 		return wcschr(s, c);
@@ -5423,7 +6012,7 @@
 	#endif
 	}
 
-	const char_t* find_substring(const char_t* s, const char_t* p)
+	PUGI__FN const char_t* find_substring(const char_t* s, const char_t* p)
 	{
 	#ifdef PUGIXML_WCHAR_MODE
 		// MSVC6 wcsstr bug workaround (if s is empty it always returns 0)
@@ -5434,12 +6023,12 @@
 	}
 
 	// Converts symbol to lower case, if it is an ASCII one
-	char_t tolower_ascii(char_t ch)
+	PUGI__FN char_t tolower_ascii(char_t ch)
 	{
 		return static_cast<unsigned int>(ch - 'A') < 26 ? static_cast<char_t>(ch | ' ') : ch;
 	}
 
-	xpath_string string_value(const xpath_node& na, xpath_allocator* alloc)
+	PUGI__FN xpath_string string_value(const xpath_node& na, xpath_allocator* alloc)
 	{
 		if (na.attribute())
 			return xpath_string_const(na.attribute().value());
@@ -5489,76 +6078,76 @@
 		}
 	}
 	
-	unsigned int node_height(xml_node n)
+	PUGI__FN unsigned int node_height(xml_node n)
 	{
-	    unsigned int result = 0;
-	    
-	    while (n)
-	    {
-	        ++result;
-	        n = n.parent();
-	    }
-	    
-	    return result;
+		unsigned int result = 0;
+		
+		while (n)
+		{
+			++result;
+			n = n.parent();
+		}
+		
+		return result;
 	}
 	
-	bool node_is_before(xml_node ln, unsigned int lh, xml_node rn, unsigned int rh)
+	PUGI__FN bool node_is_before(xml_node ln, unsigned int lh, xml_node rn, unsigned int rh)
 	{
 		// normalize heights
 		for (unsigned int i = rh; i < lh; i++) ln = ln.parent();
 		for (unsigned int j = lh; j < rh; j++) rn = rn.parent();
-	    
+		
 		// one node is the ancestor of the other
-	    if (ln == rn) return lh < rh;
-	    
+		if (ln == rn) return lh < rh;
+		
 		// find common ancestor
-	    while (ln.parent() != rn.parent())
-	    {
-	        ln = ln.parent();
-	        rn = rn.parent();
-	    }
+		while (ln.parent() != rn.parent())
+		{
+			ln = ln.parent();
+			rn = rn.parent();
+		}
 
 		// there is no common ancestor (the shared parent is null), nodes are from different documents
 		if (!ln.parent()) return ln < rn;
 
 		// determine sibling order
-        for (; ln; ln = ln.next_sibling())
-            if (ln == rn)
-                return true;
-                
-        return false;
-    }
+		for (; ln; ln = ln.next_sibling())
+			if (ln == rn)
+				return true;
+				
+		return false;
+	}
 
-    bool node_is_ancestor(xml_node parent, xml_node node)
-    {
-    	while (node && node != parent) node = node.parent();
+	PUGI__FN bool node_is_ancestor(xml_node parent, xml_node node)
+	{
+		while (node && node != parent) node = node.parent();
 
-    	return parent && node == parent;
-    }
+		return parent && node == parent;
+	}
 
-    const void* document_order(const xpath_node& xnode)
-    {
-        xml_node_struct* node = xnode.node().internal_object();
+	PUGI__FN const void* document_order(const xpath_node& xnode)
+	{
+		xml_node_struct* node = xnode.node().internal_object();
 
-        if (node)
-        {
-            if (node->name && (node->header & xml_memory_page_name_allocated_mask) == 0) return node->name;
-            if (node->value && (node->header & xml_memory_page_value_allocated_mask) == 0) return node->value;
-            return 0;
-        }
+		if (node)
+		{
+			if (node->name && (node->header & xml_memory_page_name_allocated_mask) == 0) return node->name;
+			if (node->value && (node->header & xml_memory_page_value_allocated_mask) == 0) return node->value;
+			return 0;
+		}
 
-        xml_attribute_struct* attr = xnode.attribute().internal_object();
+		xml_attribute_struct* attr = xnode.attribute().internal_object();
 
-        if (attr)
-        {
-            if ((attr->header & xml_memory_page_name_allocated_mask) == 0) return attr->name;
-            if ((attr->header & xml_memory_page_value_allocated_mask) == 0) return attr->value;
-            return 0;
-        }
+		if (attr)
+		{
+			if ((attr->header & xml_memory_page_name_allocated_mask) == 0) return attr->name;
+			if ((attr->header & xml_memory_page_value_allocated_mask) == 0) return attr->value;
+			return 0;
+		}
 
 		return 0;
-    }
-    
+	}
+	
 	struct document_order_comparator
 	{
 		bool operator()(const xpath_node& lhs, const xpath_node& rhs) const
@@ -5569,7 +6158,7 @@
 
 			if (lo && ro) return lo < ro;
 
-            // slow comparison
+			// slow comparison
 			xml_node ln = lhs.node(), rn = rhs.node();
 
 			// compare attributes
@@ -5579,11 +6168,11 @@
 				if (lhs.parent() == rhs.parent())
 				{
 					// determine sibling order
-				    for (xml_attribute a = lhs.attribute(); a; a = a.next_attribute())
-				        if (a == rhs.attribute())
-				            return true;
-				    
-				    return false;
+					for (xml_attribute a = lhs.attribute(); a; a = a.next_attribute())
+						if (a == rhs.attribute())
+							return true;
+					
+					return false;
 				}
 				
 				// compare attribute parents
@@ -5623,10 +6212,10 @@
 		}
 	};
 	
-	double gen_nan()
+	PUGI__FN double gen_nan()
 	{
 	#if defined(__STDC_IEC_559__) || ((FLT_RADIX - 0 == 2) && (FLT_MAX_EXP - 0 == 128) && (FLT_MANT_DIG - 0 == 24))
-		union { float f; int32_t i; } u[sizeof(float) == sizeof(int32_t) ? 1 : -1];
+		union { float f; uint32_t i; } u[sizeof(float) == sizeof(uint32_t) ? 1 : -1];
 		u[0].i = 0x7fc00000;
 		return u[0].f;
 	#else
@@ -5636,9 +6225,9 @@
 	#endif
 	}
 	
-	bool is_nan(double value)
+	PUGI__FN bool is_nan(double value)
 	{
-	#if defined(_MSC_VER) || defined(__BORLANDC__)
+	#if defined(PUGI__MSVC_CRT_VERSION) || defined(__BORLANDC__)
 		return !!_isnan(value);
 	#elif defined(fpclassify) && defined(FP_NAN)
 		return fpclassify(value) == FP_NAN;
@@ -5649,12 +6238,12 @@
 	#endif
 	}
 	
-	const char_t* convert_number_to_string_special(double value)
+	PUGI__FN const char_t* convert_number_to_string_special(double value)
 	{
-	#if defined(_MSC_VER) || defined(__BORLANDC__)
+	#if defined(PUGI__MSVC_CRT_VERSION) || defined(__BORLANDC__)
 		if (_finite(value)) return (value == 0) ? PUGIXML_TEXT("0") : 0;
 		if (_isnan(value)) return PUGIXML_TEXT("NaN");
-		return PUGIXML_TEXT("-Infinity") + (value > 0);
+		return value > 0 ? PUGIXML_TEXT("Infinity") : PUGIXML_TEXT("-Infinity");
 	#elif defined(fpclassify) && defined(FP_NAN) && defined(FP_INFINITE) && defined(FP_ZERO)
 		switch (fpclassify(value))
 		{
@@ -5662,7 +6251,7 @@
 			return PUGIXML_TEXT("NaN");
 
 		case FP_INFINITE:
-                        return value>0 ? PUGIXML_TEXT("Infinity") : PUGIXML_TEXT("-Infinity");
+			return value > 0 ? PUGIXML_TEXT("Infinity") : PUGIXML_TEXT("-Infinity");
 
 		case FP_ZERO:
 			return PUGIXML_TEXT("0");
@@ -5676,18 +6265,17 @@
 
 		if (v == 0) return PUGIXML_TEXT("0");
 		if (v != v) return PUGIXML_TEXT("NaN");
-		if (v * 2 == v)
-                    return value>0 ? PUGIXML_TEXT("Infinity") : PUGIXML_TEXT("-Infinity");
+		if (v * 2 == v) return value > 0 ? PUGIXML_TEXT("Infinity") : PUGIXML_TEXT("-Infinity");
 		return 0;
 	#endif
 	}
 	
-	bool convert_number_to_boolean(double value)
+	PUGI__FN bool convert_number_to_boolean(double value)
 	{
 		return (value != 0 && !is_nan(value));
 	}
 	
-	void truncate_zeros(char* begin, char* end)
+	PUGI__FN void truncate_zeros(char* begin, char* end)
 	{
 		while (begin != end && end[-1] == '0') end--;
 
@@ -5695,8 +6283,8 @@
 	}
 
 	// gets mantissa digits in the form of 0.xxxxx with 0. implied and the exponent
-#if defined(_MSC_VER) && _MSC_VER >= 1400
-	void convert_number_to_mantissa_exponent(double value, char* buffer, size_t buffer_size, char** out_mantissa, int* out_exponent)
+#if defined(PUGI__MSVC_CRT_VERSION) && PUGI__MSVC_CRT_VERSION >= 1400 && !defined(_WIN32_WCE)
+	PUGI__FN void convert_number_to_mantissa_exponent(double value, char* buffer, size_t buffer_size, char** out_mantissa, int* out_exponent)
 	{
 		// get base values
 		int sign, exponent;
@@ -5710,7 +6298,7 @@
 		*out_exponent = exponent;
 	}
 #else
-	void convert_number_to_mantissa_exponent(double value, char* buffer, size_t buffer_size, char** out_mantissa, int* out_exponent)
+	PUGI__FN void convert_number_to_mantissa_exponent(double value, char* buffer, size_t buffer_size, char** out_mantissa, int* out_exponent)
 	{
 		// get a scientific notation value with IEEE DBL_DIG decimals
 		sprintf(buffer, "%.*e", DBL_DIG, value);
@@ -5741,7 +6329,7 @@
 	}
 #endif
 
-	xpath_string convert_number_to_string(double value, xpath_allocator* alloc)
+	PUGI__FN xpath_string convert_number_to_string(double value, xpath_allocator* alloc)
 	{
 		// try special number conversion
 		const char_t* special = convert_number_to_string_special(value);
@@ -5770,7 +6358,7 @@
 		{
 			while (exponent > 0)
 			{
-				assert(*mantissa == 0 || (unsigned)(*mantissa - '0') <= 9);
+				assert(*mantissa == 0 || static_cast<unsigned int>(*mantissa - '0') <= 9);
 				*s++ = *mantissa ? *mantissa++ : '0';
 				exponent--;
 			}
@@ -5792,7 +6380,7 @@
 			// extra mantissa digits
 			while (*mantissa)
 			{
-				assert((unsigned)(*mantissa - '0') <= 9);
+				assert(static_cast<unsigned int>(*mantissa - '0') <= 9);
 				*s++ = *mantissa++;
 			}
 		}
@@ -5804,10 +6392,10 @@
 		return xpath_string(result, alloc);
 	}
 	
-	bool check_string_to_number_format(const char_t* string)
+	PUGI__FN bool check_string_to_number_format(const char_t* string)
 	{
 		// parse leading whitespace
-		while (IS_CHARTYPE(*string, ct_space)) ++string;
+		while (PUGI__IS_CHARTYPE(*string, ct_space)) ++string;
 
 		// parse sign
 		if (*string == '-') ++string;
@@ -5815,26 +6403,26 @@
 		if (!*string) return false;
 
 		// if there is no integer part, there should be a decimal part with at least one digit
-		if (!IS_CHARTYPEX(string[0], ctx_digit) && (string[0] != '.' || !IS_CHARTYPEX(string[1], ctx_digit))) return false;
+		if (!PUGI__IS_CHARTYPEX(string[0], ctx_digit) && (string[0] != '.' || !PUGI__IS_CHARTYPEX(string[1], ctx_digit))) return false;
 
 		// parse integer part
-		while (IS_CHARTYPEX(*string, ctx_digit)) ++string;
+		while (PUGI__IS_CHARTYPEX(*string, ctx_digit)) ++string;
 
 		// parse decimal part
 		if (*string == '.')
 		{
 			++string;
 
-			while (IS_CHARTYPEX(*string, ctx_digit)) ++string;
+			while (PUGI__IS_CHARTYPEX(*string, ctx_digit)) ++string;
 		}
 
 		// parse trailing whitespace
-		while (IS_CHARTYPE(*string, ct_space)) ++string;
+		while (PUGI__IS_CHARTYPE(*string, ct_space)) ++string;
 
 		return *string == 0;
 	}
 
-	double convert_string_to_number(const char_t* string)
+	PUGI__FN double convert_string_to_number(const char_t* string)
 	{
 		// check string format
 		if (!check_string_to_number_format(string)) return gen_nan();
@@ -5847,7 +6435,7 @@
 	#endif
 	}
 
-	bool convert_string_to_number(const char_t* begin, const char_t* end, double* out_result)
+	PUGI__FN bool convert_string_to_number(const char_t* begin, const char_t* end, double* out_result)
 	{
 		char_t buffer[32];
 
@@ -5857,7 +6445,7 @@
 		if (length >= sizeof(buffer) / sizeof(buffer[0]))
 		{
 			// need to make dummy on-heap copy
-			scratch = static_cast<char_t*>(global_allocate((length + 1) * sizeof(char_t)));
+			scratch = static_cast<char_t*>(xml_memory::allocate((length + 1) * sizeof(char_t)));
 			if (!scratch) return false;
 		}
 
@@ -5868,29 +6456,29 @@
 		*out_result = convert_string_to_number(scratch);
 
 		// free dummy buffer
-		if (scratch != buffer) global_deallocate(scratch);
+		if (scratch != buffer) xml_memory::deallocate(scratch);
 
 		return true;
 	}
 	
-	double round_nearest(double value)
+	PUGI__FN double round_nearest(double value)
 	{
 		return floor(value + 0.5);
 	}
 
-	double round_nearest_nzero(double value)
+	PUGI__FN double round_nearest_nzero(double value)
 	{
 		// same as round_nearest, but returns -0 for [-0.5, -0]
 		// ceil is used to differentiate between +0 and -0 (we return -0 for [-0.5, -0] and +0 for +0)
 		return (value >= -0.5 && value <= 0) ? ceil(value) : floor(value + 0.5);
 	}
 	
-	const char_t* qualified_name(const xpath_node& node)
+	PUGI__FN const char_t* qualified_name(const xpath_node& node)
 	{
 		return node.attribute() ? node.attribute().name() : node.node().name();
 	}
 	
-	const char_t* local_name(const xpath_node& node)
+	PUGI__FN const char_t* local_name(const xpath_node& node)
 	{
 		const char_t* name = qualified_name(node);
 		const char_t* p = find_char(name, ':');
@@ -5921,7 +6509,7 @@
 		}
 	};
 
-	const char_t* namespace_uri(const xml_node& node)
+	PUGI__FN const char_t* namespace_uri(const xml_node& node)
 	{
 		namespace_uri_predicate pred = node.name();
 		
@@ -5939,7 +6527,7 @@
 		return PUGIXML_TEXT("");
 	}
 
-	const char_t* namespace_uri(const xml_attribute& attr, const xml_node& parent)
+	PUGI__FN const char_t* namespace_uri(const xml_attribute& attr, const xml_node& parent)
 	{
 		namespace_uri_predicate pred = attr.name();
 		
@@ -5960,12 +6548,12 @@
 		return PUGIXML_TEXT("");
 	}
 
-	const char_t* namespace_uri(const xpath_node& node)
+	PUGI__FN const char_t* namespace_uri(const xpath_node& node)
 	{
 		return node.attribute() ? namespace_uri(node.attribute(), node.parent()) : namespace_uri(node.node());
 	}
 
-	void normalize_space(char_t* buffer)
+	PUGI__FN void normalize_space(char_t* buffer)
 	{
 		char_t* write = buffer;
 
@@ -5973,10 +6561,10 @@
 		{
 			char_t ch = *it++;
 
-			if (IS_CHARTYPE(ch, ct_space))
+			if (PUGI__IS_CHARTYPE(ch, ct_space))
 			{
 				// replace whitespace sequence with single space
-				while (IS_CHARTYPE(*it, ct_space)) it++;
+				while (PUGI__IS_CHARTYPE(*it, ct_space)) it++;
 
 				// avoid leading spaces
 				if (write != buffer) *write++ = ' ';
@@ -5985,13 +6573,13 @@
 		}
 
 		// remove trailing space
-		if (write != buffer && IS_CHARTYPE(write[-1], ct_space)) write--;
+		if (write != buffer && PUGI__IS_CHARTYPE(write[-1], ct_space)) write--;
 
 		// zero-terminate
 		*write = 0;
 	}
 
-	void translate(char_t* buffer, const char_t* from, const char_t* to)
+	PUGI__FN void translate(char_t* buffer, const char_t* from, const char_t* to)
 	{
 		size_t to_length = strlength(to);
 
@@ -5999,7 +6587,7 @@
 
 		while (*buffer)
 		{
-			DMC_VOLATILE char_t ch = *buffer++;
+			PUGI__DMC_VOLATILE char_t ch = *buffer++;
 
 			const char_t* pos = find_char(from, ch);
 
@@ -6041,7 +6629,7 @@
 
 		~xpath_variable_string()
 		{
-			if (value) global_deallocate(value);
+			if (value) xml_memory::deallocate(value);
 		}
 
 		char_t* value;
@@ -6054,9 +6642,9 @@
 		char_t name[1];
 	};
 
-	const xpath_node_set dummy_node_set;
+	static const xpath_node_set dummy_node_set;
 
-	unsigned int hash_string(const char_t* str)
+	PUGI__FN unsigned int hash_string(const char_t* str)
 	{
 		// Jenkins one-at-a-time hash (http://en.wikipedia.org/wiki/Jenkins_hash_function#one-at-a-time)
 		unsigned int result = 0;
@@ -6075,13 +6663,13 @@
 		return result;
 	}
 
-	template <typename T> T* new_xpath_variable(const char_t* name)
+	template <typename T> PUGI__FN T* new_xpath_variable(const char_t* name)
 	{
 		size_t length = strlength(name);
 		if (length == 0) return 0; // empty variable names are invalid
 
 		// $$ we can't use offsetof(T, name) because T is non-POD, so we just allocate additional length characters
-		void* memory = global_allocate(sizeof(T) + length * sizeof(char_t));
+		void* memory = xml_memory::allocate(sizeof(T) + length * sizeof(char_t));
 		if (!memory) return 0;
 
 		T* result = new (memory) T();
@@ -6091,7 +6679,7 @@
 		return result;
 	}
 
-	xpath_variable* new_xpath_variable(xpath_value_type type, const char_t* name)
+	PUGI__FN xpath_variable* new_xpath_variable(xpath_value_type type, const char_t* name)
 	{
 		switch (type)
 		{
@@ -6112,13 +6700,13 @@
 		}
 	}
 
-	template <typename T> void delete_xpath_variable(T* var)
+	template <typename T> PUGI__FN void delete_xpath_variable(T* var)
 	{
 		var->~T();
-		global_deallocate(var);
+		xml_memory::deallocate(var);
 	}
 
-	void delete_xpath_variable(xpath_value_type type, xpath_variable* var)
+	PUGI__FN void delete_xpath_variable(xpath_value_type type, xpath_variable* var)
 	{
 		switch (type)
 		{
@@ -6143,7 +6731,7 @@
 		}
 	}
 
-	xpath_variable* get_variable(xpath_variable_set* set, const char_t* begin, const char_t* end)
+	PUGI__FN xpath_variable* get_variable(xpath_variable_set* set, const char_t* begin, const char_t* end)
 	{
 		char_t buffer[32];
 
@@ -6153,7 +6741,7 @@
 		if (length >= sizeof(buffer) / sizeof(buffer[0]))
 		{
 			// need to make dummy on-heap copy
-			scratch = static_cast<char_t*>(global_allocate((length + 1) * sizeof(char_t)));
+			scratch = static_cast<char_t*>(xml_memory::allocate((length + 1) * sizeof(char_t)));
 			if (!scratch) return 0;
 		}
 
@@ -6164,16 +6752,15 @@
 		xpath_variable* result = set->get(scratch);
 
 		// free dummy buffer
-		if (scratch != buffer) global_deallocate(scratch);
+		if (scratch != buffer) xml_memory::deallocate(scratch);
 
 		return result;
 	}
-}
+PUGI__NS_END
 
 // Internal node set class
-namespace
-{
-	xpath_node_set::type_t xpath_sort(xpath_node* begin, xpath_node* end, xpath_node_set::type_t type, bool rev)
+PUGI__NS_BEGIN
+	PUGI__FN xpath_node_set::type_t xpath_sort(xpath_node* begin, xpath_node* end, xpath_node_set::type_t type, bool rev)
 	{
 		xpath_node_set::type_t order = rev ? xpath_node_set::type_sorted_reverse : xpath_node_set::type_sorted;
 
@@ -6189,7 +6776,7 @@
 		return order;
 	}
 
-	xpath_node xpath_first(const xpath_node* begin, const xpath_node* end, xpath_node_set::type_t type)
+	PUGI__FN xpath_node xpath_first(const xpath_node* begin, const xpath_node* end, xpath_node_set::type_t type)
 	{
 		if (begin == end) return xpath_node();
 
@@ -6209,6 +6796,7 @@
 			return xpath_node();
 		}
 	}
+
 	class xpath_node_set_raw
 	{
 		xpath_node_set::type_t _type;
@@ -6269,25 +6857,25 @@
 			*_end++ = node;
 		}
 
-		void append(const xpath_node* begin, const xpath_node* end, xpath_allocator* alloc)
+		void append(const xpath_node* begin_, const xpath_node* end_, xpath_allocator* alloc)
 		{
-			size_t size = static_cast<size_t>(_end - _begin);
+			size_t size_ = static_cast<size_t>(_end - _begin);
 			size_t capacity = static_cast<size_t>(_eos - _begin);
-			size_t count = static_cast<size_t>(end - begin);
+			size_t count = static_cast<size_t>(end_ - begin_);
 
-			if (size + count > capacity)
+			if (size_ + count > capacity)
 			{
 				// reallocate the old array or allocate a new one
-				xpath_node* data = static_cast<xpath_node*>(alloc->reallocate(_begin, capacity * sizeof(xpath_node), (size + count) * sizeof(xpath_node)));
+				xpath_node* data = static_cast<xpath_node*>(alloc->reallocate(_begin, capacity * sizeof(xpath_node), (size_ + count) * sizeof(xpath_node)));
 				assert(data);
 
 				// finalize
 				_begin = data;
-				_end = data + size;
-				_eos = data + size + count;
+				_end = data + size_;
+				_eos = data + size_ + count;
 			}
 
-			memcpy(_end, begin, count * sizeof(xpath_node));
+			memcpy(_end, begin_, count * sizeof(xpath_node));
 			_end += count;
 		}
 
@@ -6316,21 +6904,20 @@
 			return _type;
 		}
 
-		void set_type(xpath_node_set::type_t type)
+		void set_type(xpath_node_set::type_t value)
 		{
-			_type = type;
+			_type = value;
 		}
 	};
-}
+PUGI__NS_END
 
-namespace
-{
+PUGI__NS_BEGIN
 	struct xpath_context
 	{
 		xpath_node n;
 		size_t position, size;
 
-		xpath_context(const xpath_node& n, size_t position, size_t size): n(n), position(position), size(size)
+		xpath_context(const xpath_node& n_, size_t position_, size_t size_): n(n_), position(position_), size(size_)
 		{
 		}
 	};
@@ -6406,7 +6993,7 @@
 		{
 			const char_t* cur = _cur;
 
-			while (IS_CHARTYPE(*cur, ct_space)) ++cur;
+			while (PUGI__IS_CHARTYPE(*cur, ct_space)) ++cur;
 
 			// save lexeme position for error reporting
 			_cur_lexeme_pos = cur;
@@ -6488,17 +7075,17 @@
 			case '$':
 				cur += 1;
 
-				if (IS_CHARTYPEX(*cur, ctx_start_symbol))
+				if (PUGI__IS_CHARTYPEX(*cur, ctx_start_symbol))
 				{
 					_cur_lexeme_contents.begin = cur;
 
-					while (IS_CHARTYPEX(*cur, ctx_symbol)) cur++;
+					while (PUGI__IS_CHARTYPEX(*cur, ctx_symbol)) cur++;
 
-					if (cur[0] == ':' && IS_CHARTYPEX(cur[1], ctx_symbol)) // qname
+					if (cur[0] == ':' && PUGI__IS_CHARTYPEX(cur[1], ctx_symbol)) // qname
 					{
 						cur++; // :
 
-						while (IS_CHARTYPEX(*cur, ctx_symbol)) cur++;
+						while (PUGI__IS_CHARTYPEX(*cur, ctx_symbol)) cur++;
 					}
 
 					_cur_lexeme_contents.end = cur;
@@ -6561,13 +7148,13 @@
 					cur += 2;
 					_cur_lexeme = lex_double_dot;
 				}
-				else if (IS_CHARTYPEX(*(cur+1), ctx_digit))
+				else if (PUGI__IS_CHARTYPEX(*(cur+1), ctx_digit))
 				{
 					_cur_lexeme_contents.begin = cur; // .
 
 					++cur;
 
-					while (IS_CHARTYPEX(*cur, ctx_digit)) cur++;
+					while (PUGI__IS_CHARTYPEX(*cur, ctx_digit)) cur++;
 
 					_cur_lexeme_contents.end = cur;
 					
@@ -6621,28 +7208,28 @@
 				break;
 
 			default:
-				if (IS_CHARTYPEX(*cur, ctx_digit))
+				if (PUGI__IS_CHARTYPEX(*cur, ctx_digit))
 				{
 					_cur_lexeme_contents.begin = cur;
 
-					while (IS_CHARTYPEX(*cur, ctx_digit)) cur++;
+					while (PUGI__IS_CHARTYPEX(*cur, ctx_digit)) cur++;
 				
 					if (*cur == '.')
 					{
 						cur++;
 
-						while (IS_CHARTYPEX(*cur, ctx_digit)) cur++;
+						while (PUGI__IS_CHARTYPEX(*cur, ctx_digit)) cur++;
 					}
 
 					_cur_lexeme_contents.end = cur;
 
 					_cur_lexeme = lex_number;
 				}
-				else if (IS_CHARTYPEX(*cur, ctx_start_symbol))
+				else if (PUGI__IS_CHARTYPEX(*cur, ctx_start_symbol))
 				{
 					_cur_lexeme_contents.begin = cur;
 
-					while (IS_CHARTYPEX(*cur, ctx_symbol)) cur++;
+					while (PUGI__IS_CHARTYPEX(*cur, ctx_symbol)) cur++;
 
 					if (cur[0] == ':')
 					{
@@ -6650,11 +7237,11 @@
 						{
 							cur += 2; // :*
 						}
-						else if (IS_CHARTYPEX(cur[1], ctx_symbol)) // namespace test qname
+						else if (PUGI__IS_CHARTYPEX(cur[1], ctx_symbol)) // namespace test qname
 						{
 							cur++; // :
 
-							while (IS_CHARTYPEX(*cur, ctx_symbol)) cur++;
+							while (PUGI__IS_CHARTYPEX(*cur, ctx_symbol)) cur++;
 						}
 					}
 
@@ -6694,7 +7281,7 @@
 		ast_op_or,						// left or right
 		ast_op_and,						// left and right
 		ast_op_equal,					// left = right
-		ast_op_not_equal, 				// left != right
+		ast_op_not_equal,				// left != right
 		ast_op_less,					// left < right
 		ast_op_greater,					// left > right
 		ast_op_less_or_equal,			// left <= right
@@ -7389,34 +7976,34 @@
 		}
 		
 	public:
-		xpath_ast_node(ast_type_t type, xpath_value_type rettype, const char_t* value):
-			_type((char)type), _rettype((char)rettype), _axis(0), _test(0), _left(0), _right(0), _next(0)
+		xpath_ast_node(ast_type_t type, xpath_value_type rettype_, const char_t* value):
+			_type(static_cast<char>(type)), _rettype(static_cast<char>(rettype_)), _axis(0), _test(0), _left(0), _right(0), _next(0)
 		{
 			assert(type == ast_string_constant);
 			_data.string = value;
 		}
 
-		xpath_ast_node(ast_type_t type, xpath_value_type rettype, double value):
-			_type((char)type), _rettype((char)rettype), _axis(0), _test(0), _left(0), _right(0), _next(0)
+		xpath_ast_node(ast_type_t type, xpath_value_type rettype_, double value):
+			_type(static_cast<char>(type)), _rettype(static_cast<char>(rettype_)), _axis(0), _test(0), _left(0), _right(0), _next(0)
 		{
 			assert(type == ast_number_constant);
 			_data.number = value;
 		}
 		
-		xpath_ast_node(ast_type_t type, xpath_value_type rettype, xpath_variable* value):
-			_type((char)type), _rettype((char)rettype), _axis(0), _test(0), _left(0), _right(0), _next(0)
+		xpath_ast_node(ast_type_t type, xpath_value_type rettype_, xpath_variable* value):
+			_type(static_cast<char>(type)), _rettype(static_cast<char>(rettype_)), _axis(0), _test(0), _left(0), _right(0), _next(0)
 		{
 			assert(type == ast_variable);
 			_data.variable = value;
 		}
 		
-		xpath_ast_node(ast_type_t type, xpath_value_type rettype, xpath_ast_node* left = 0, xpath_ast_node* right = 0):
-			_type((char)type), _rettype((char)rettype), _axis(0), _test(0), _left(left), _right(right), _next(0)
+		xpath_ast_node(ast_type_t type, xpath_value_type rettype_, xpath_ast_node* left = 0, xpath_ast_node* right = 0):
+			_type(static_cast<char>(type)), _rettype(static_cast<char>(rettype_)), _axis(0), _test(0), _left(left), _right(right), _next(0)
 		{
 		}
 
 		xpath_ast_node(ast_type_t type, xpath_ast_node* left, axis_t axis, nodetest_t test, const char_t* contents):
-			_type((char)type), _rettype(xpath_type_node_set), _axis((char)axis), _test((char)test), _left(left), _right(0), _next(0)
+			_type(static_cast<char>(type)), _rettype(xpath_type_node_set), _axis(static_cast<char>(axis)), _test(static_cast<char>(test)), _left(left), _right(0), _next(0)
 		{
 			_data.nodetest = contents;
 		}
@@ -7586,30 +8173,30 @@
 				return _data.number;
 
 			case ast_func_last:
-				return (double)c.size;
+				return static_cast<double>(c.size);
 			
 			case ast_func_position:
-				return (double)c.position;
+				return static_cast<double>(c.position);
 
 			case ast_func_count:
 			{
 				xpath_allocator_capture cr(stack.result);
 
-				return (double)_left->eval_node_set(c, stack).size();
+				return static_cast<double>(_left->eval_node_set(c, stack).size());
 			}
 			
 			case ast_func_string_length_0:
 			{
 				xpath_allocator_capture cr(stack.result);
 
-				return (double)string_value(c.n, stack.result).length();
+				return static_cast<double>(string_value(c.n, stack.result).length());
 			}
 			
 			case ast_func_string_length_1:
 			{
 				xpath_allocator_capture cr(stack.result);
 
-				return (double)_left->eval_string(c, stack).length();
+				return static_cast<double>(_left->eval_string(c, stack).length());
 			}
 			
 			case ast_func_number_0:
@@ -7858,7 +8445,7 @@
 				if (is_nan(first)) return xpath_string(); // NaN
 				else if (first >= s_length + 1) return xpath_string();
 				
-				size_t pos = first < 1 ? 1 : (size_t)first;
+				size_t pos = first < 1 ? 1 : static_cast<size_t>(first);
 				assert(1 <= pos && pos <= s_length + 1);
 
 				const char_t* rbegin = s.c_str() + (pos - 1);
@@ -7883,8 +8470,8 @@
 				else if (first >= last) return xpath_string();
 				else if (last < 1) return xpath_string();
 				
-				size_t pos = first < 1 ? 1 : (size_t)first;
-				size_t end = last >= s_length + 1 ? s_length + 1 : (size_t)last;
+				size_t pos = first < 1 ? 1 : static_cast<size_t>(first);
+				size_t end = last >= s_length + 1 ? s_length + 1 : static_cast<size_t>(last);
 
 				assert(1 <= pos && pos <= end && end <= s_length + 1);
 				const char_t* rbegin = s.c_str() + (pos - 1);
@@ -7978,7 +8565,7 @@
 				xpath_node_set_raw rs = _right->eval_node_set(c, stack);
 				
 				// we can optimize merging two sorted sets, but this is a very rare operation, so don't bother
-  		        rs.set_type(xpath_node_set::type_unsorted);
+				rs.set_type(xpath_node_set::type_unsorted);
 
 				rs.append(ls.begin(), ls.end(), stack.result);
 				rs.remove_duplicates();
@@ -8045,6 +8632,10 @@
 				
 				case axis_self:
 					return step_do(c, stack, axis_to_type<axis_self>());
+
+				default:
+					assert(!"Unknown axis");
+					return xpath_node_set_raw();
 				}
 			}
 
@@ -8126,8 +8717,8 @@
 
 	struct xpath_parser
 	{
-	    xpath_allocator* _alloc;
-	    xpath_lexer _lexer;
+		xpath_allocator* _alloc;
+		xpath_lexer _lexer;
 
 		const char_t* _query;
 		xpath_variable_set* _variables;
@@ -8151,13 +8742,13 @@
 		}
 
 		void throw_error_oom()
-        {
-        #ifdef PUGIXML_NO_EXCEPTIONS
-            throw_error("Out of memory");
-        #else
-            throw std::bad_alloc();
-        #endif
-        }
+		{
+		#ifdef PUGIXML_NO_EXCEPTIONS
+			throw_error("Out of memory");
+		#else
+			throw std::bad_alloc();
+		#endif
+		}
 
 		void* alloc_node()
 		{
@@ -8297,6 +8888,9 @@
 					return new (alloc_node()) xpath_ast_node(ast_func_true, xpath_type_boolean);
 					
 				break;
+
+			default:
+				break;
 			}
 
 			throw_error("Unrecognized function or wrong parameter count");
@@ -8363,6 +8957,9 @@
 					return axis_self;
 				
 				break;
+
+			default:
+				break;
 			}
 
 			specified = false;
@@ -8396,18 +8993,21 @@
 					return nodetest_type_text;
 
 				break;
+			
+			default:
+				break;
 			}
 
 			return nodetest_none;
 		}
 
-	    // PrimaryExpr ::= VariableReference | '(' Expr ')' | Literal | Number | FunctionCall
-	    xpath_ast_node* parse_primary_expression()
-	    {
-	    	switch (_lexer.current())
-	    	{
-	    	case lex_var_ref:
-	    	{
+		// PrimaryExpr ::= VariableReference | '(' Expr ')' | Literal | Number | FunctionCall
+		xpath_ast_node* parse_primary_expression()
+		{
+			switch (_lexer.current())
+			{
+			case lex_var_ref:
+			{
 				xpath_lexer_string name = _lexer.contents();
 
 				if (!_variables)
@@ -8420,7 +9020,7 @@
 
 				_lexer.next();
 
-	    		return new (alloc_node()) xpath_ast_node(ast_variable, var->type(), var);
+				return new (alloc_node()) xpath_ast_node(ast_variable, var->type(), var);
 			}
 
 			case lex_open_brace:
@@ -8497,23 +9097,23 @@
 				return parse_function(function, argc, args);
 			}
 
-	    	default:
-	    		throw_error("Unrecognizable primary expression");
+			default:
+				throw_error("Unrecognizable primary expression");
 
-	    		return 0;
-	    	}
-	    }
-	    
-	    // FilterExpr ::= PrimaryExpr | FilterExpr Predicate
-	    // Predicate ::= '[' PredicateExpr ']'
-	    // PredicateExpr ::= Expr
-	    xpath_ast_node* parse_filter_expression()
-	    {
-	    	xpath_ast_node* n = parse_primary_expression();
+				return 0;
+			}
+		}
+		
+		// FilterExpr ::= PrimaryExpr | FilterExpr Predicate
+		// Predicate ::= '[' PredicateExpr ']'
+		// PredicateExpr ::= Expr
+		xpath_ast_node* parse_filter_expression()
+		{
+			xpath_ast_node* n = parse_primary_expression();
 
-	    	while (_lexer.current() == lex_open_square_brace)
-	    	{
-	    		_lexer.next();
+			while (_lexer.current() == lex_open_square_brace)
+			{
+				_lexer.next();
 
 				xpath_ast_node* expr = parse_expression();
 
@@ -8521,24 +9121,24 @@
 
 				bool posinv = expr->rettype() != xpath_type_number && expr->is_posinv();
 
-	    		n = new (alloc_node()) xpath_ast_node(posinv ? ast_filter_posinv : ast_filter, xpath_type_node_set, n, expr);
+				n = new (alloc_node()) xpath_ast_node(posinv ? ast_filter_posinv : ast_filter, xpath_type_node_set, n, expr);
 
-	    		if (_lexer.current() != lex_close_square_brace)
-	    			throw_error("Unmatched square brace");
-	    	
-	    		_lexer.next();
-	    	}
-	    	
-	    	return n;
-	    }
-	    
-	    // Step ::= AxisSpecifier NodeTest Predicate* | AbbreviatedStep
-	    // AxisSpecifier ::= AxisName '::' | '@'?
-	    // NodeTest ::= NameTest | NodeType '(' ')' | 'processing-instruction' '(' Literal ')'
-	    // NameTest ::= '*' | NCName ':' '*' | QName
-	    // AbbreviatedStep ::= '.' | '..'
-	    xpath_ast_node* parse_step(xpath_ast_node* set)
-	    {
+				if (_lexer.current() != lex_close_square_brace)
+					throw_error("Unmatched square brace");
+			
+				_lexer.next();
+			}
+			
+			return n;
+		}
+		
+		// Step ::= AxisSpecifier NodeTest Predicate* | AbbreviatedStep
+		// AxisSpecifier ::= AxisName '::' | '@'?
+		// NodeTest ::= NameTest | NodeType '(' ')' | 'processing-instruction' '(' Literal ')'
+		// NameTest ::= '*' | NCName ':' '*' | QName
+		// AbbreviatedStep ::= '.' | '..'
+		xpath_ast_node* parse_step(xpath_ast_node* set)
+		{
 			if (set && set->rettype() != xpath_type_node_set)
 				throw_error("Step has to be applied to node set");
 
@@ -8564,7 +9164,7 @@
 				
 				return new (alloc_node()) xpath_ast_node(ast_step, set, axis_parent, nodetest_type_node, 0);
 			}
-	    
+		
 			nodetest_t nt_type = nodetest_none;
 			xpath_lexer_string nt_name;
 			
@@ -8668,7 +9268,7 @@
 				xpath_ast_node* pred = new (alloc_node()) xpath_ast_node(ast_predicate, xpath_type_node_set, expr);
 				
 				if (_lexer.current() != lex_close_square_brace)
-	    			throw_error("Unmatched square brace");
+					throw_error("Unmatched square brace");
 				_lexer.next();
 				
 				if (last) last->set_next(pred);
@@ -8678,11 +9278,11 @@
 			}
 			
 			return n;
-	    }
-	    
-	    // RelativeLocationPath ::= Step | RelativeLocationPath '/' Step | RelativeLocationPath '//' Step
-	    xpath_ast_node* parse_relative_location_path(xpath_ast_node* set)
-	    {
+		}
+		
+		// RelativeLocationPath ::= Step | RelativeLocationPath '/' Step | RelativeLocationPath '//' Step
+		xpath_ast_node* parse_relative_location_path(xpath_ast_node* set)
+		{
 			xpath_ast_node* n = parse_step(set);
 			
 			while (_lexer.current() == lex_slash || _lexer.current() == lex_double_slash)
@@ -8697,12 +9297,12 @@
 			}
 			
 			return n;
-	    }
-	    
-	    // LocationPath ::= RelativeLocationPath | AbsoluteLocationPath
-	    // AbsoluteLocationPath ::= '/' RelativeLocationPath? | '//' RelativeLocationPath
-	    xpath_ast_node* parse_location_path()
-	    {
+		}
+		
+		// LocationPath ::= RelativeLocationPath | AbsoluteLocationPath
+		// AbsoluteLocationPath ::= '/' RelativeLocationPath? | '//' RelativeLocationPath
+		xpath_ast_node* parse_location_path()
+		{
 			if (_lexer.current() == lex_slash)
 			{
 				_lexer.next();
@@ -8729,14 +9329,14 @@
 
 			// else clause moved outside of if because of bogus warning 'control may reach end of non-void function being inlined' in gcc 4.0.1
 			return parse_relative_location_path(0);
-	    }
-	    
-	    // PathExpr ::= LocationPath
-	    //				| FilterExpr
-	    //				| FilterExpr '/' RelativeLocationPath
-	    //				| FilterExpr '//' RelativeLocationPath
-	    xpath_ast_node* parse_path_expression()
-	    {
+		}
+		
+		// PathExpr ::= LocationPath
+		//				| FilterExpr
+		//				| FilterExpr '/' RelativeLocationPath
+		//				| FilterExpr '//' RelativeLocationPath
+		xpath_ast_node* parse_path_expression()
+		{
 			// Clarification.
 			// PathExpr begins with either LocationPath or FilterExpr.
 			// FilterExpr begins with PrimaryExpr
@@ -8747,27 +9347,27 @@
 			if (_lexer.current() == lex_var_ref || _lexer.current() == lex_open_brace || 
 				_lexer.current() == lex_quoted_string || _lexer.current() == lex_number ||
 				_lexer.current() == lex_string)
-	    	{
-	    		if (_lexer.current() == lex_string)
-	    		{
-	    			// This is either a function call, or not - if not, we shall proceed with location path
-	    			const char_t* state = _lexer.state();
-	    			
-					while (IS_CHARTYPE(*state, ct_space)) ++state;
-	    			
-	    			if (*state != '(') return parse_location_path();
+			{
+				if (_lexer.current() == lex_string)
+				{
+					// This is either a function call, or not - if not, we shall proceed with location path
+					const char_t* state = _lexer.state();
+					
+					while (PUGI__IS_CHARTYPE(*state, ct_space)) ++state;
+					
+					if (*state != '(') return parse_location_path();
 
 					// This looks like a function call; however this still can be a node-test. Check it.
 					if (parse_node_test_type(_lexer.contents()) != nodetest_none) return parse_location_path();
-	    		}
-	    		
-	    		xpath_ast_node* n = parse_filter_expression();
+				}
+				
+				xpath_ast_node* n = parse_filter_expression();
 
-	    		if (_lexer.current() == lex_slash || _lexer.current() == lex_double_slash)
-	    		{
+				if (_lexer.current() == lex_slash || _lexer.current() == lex_double_slash)
+				{
 					lexeme_t l = _lexer.current();
-	    			_lexer.next();
-	    			
+					_lexer.next();
+					
 					if (l == lex_double_slash)
 					{
 						if (n->rettype() != xpath_type_node_set) throw_error("Step has to be applied to node set");
@@ -8775,171 +9375,171 @@
 						n = new (alloc_node()) xpath_ast_node(ast_step, n, axis_descendant_or_self, nodetest_type_node, 0);
 					}
 	
-	    			// select from location path
-	    			return parse_relative_location_path(n);
-	    		}
+					// select from location path
+					return parse_relative_location_path(n);
+				}
 
-	    		return n;
-	    	}
-	    	else return parse_location_path();
-	    }
+				return n;
+			}
+			else return parse_location_path();
+		}
 
-	    // UnionExpr ::= PathExpr | UnionExpr '|' PathExpr
-	    xpath_ast_node* parse_union_expression()
-	    {
-	    	xpath_ast_node* n = parse_path_expression();
+		// UnionExpr ::= PathExpr | UnionExpr '|' PathExpr
+		xpath_ast_node* parse_union_expression()
+		{
+			xpath_ast_node* n = parse_path_expression();
 
-	    	while (_lexer.current() == lex_union)
-	    	{
-	    		_lexer.next();
+			while (_lexer.current() == lex_union)
+			{
+				_lexer.next();
 
 				xpath_ast_node* expr = parse_union_expression();
 
 				if (n->rettype() != xpath_type_node_set || expr->rettype() != xpath_type_node_set)
 					throw_error("Union operator has to be applied to node sets");
 
-	    		n = new (alloc_node()) xpath_ast_node(ast_op_union, xpath_type_node_set, n, expr);
-	    	}
+				n = new (alloc_node()) xpath_ast_node(ast_op_union, xpath_type_node_set, n, expr);
+			}
 
-	    	return n;
-	    }
+			return n;
+		}
 
-	    // UnaryExpr ::= UnionExpr | '-' UnaryExpr
-	    xpath_ast_node* parse_unary_expression()
-	    {
-	    	if (_lexer.current() == lex_minus)
-	    	{
-	    		_lexer.next();
+		// UnaryExpr ::= UnionExpr | '-' UnaryExpr
+		xpath_ast_node* parse_unary_expression()
+		{
+			if (_lexer.current() == lex_minus)
+			{
+				_lexer.next();
 
 				xpath_ast_node* expr = parse_unary_expression();
 
-	    		return new (alloc_node()) xpath_ast_node(ast_op_negate, xpath_type_number, expr);
-	    	}
-	    	else return parse_union_expression();
-	    }
-	    
-	    // MultiplicativeExpr ::= UnaryExpr
-	    //						  | MultiplicativeExpr '*' UnaryExpr
-	    //						  | MultiplicativeExpr 'div' UnaryExpr
-	    //						  | MultiplicativeExpr 'mod' UnaryExpr
-	    xpath_ast_node* parse_multiplicative_expression()
-	    {
-	    	xpath_ast_node* n = parse_unary_expression();
+				return new (alloc_node()) xpath_ast_node(ast_op_negate, xpath_type_number, expr);
+			}
+			else return parse_union_expression();
+		}
+		
+		// MultiplicativeExpr ::= UnaryExpr
+		//						  | MultiplicativeExpr '*' UnaryExpr
+		//						  | MultiplicativeExpr 'div' UnaryExpr
+		//						  | MultiplicativeExpr 'mod' UnaryExpr
+		xpath_ast_node* parse_multiplicative_expression()
+		{
+			xpath_ast_node* n = parse_unary_expression();
 
-	    	while (_lexer.current() == lex_multiply || (_lexer.current() == lex_string &&
-	    		   (_lexer.contents() == PUGIXML_TEXT("mod") || _lexer.contents() == PUGIXML_TEXT("div"))))
-	    	{
-	    		ast_type_t op = _lexer.current() == lex_multiply ? ast_op_multiply :
-	    			_lexer.contents().begin[0] == 'd' ? ast_op_divide : ast_op_mod;
-	    		_lexer.next();
+			while (_lexer.current() == lex_multiply || (_lexer.current() == lex_string &&
+				   (_lexer.contents() == PUGIXML_TEXT("mod") || _lexer.contents() == PUGIXML_TEXT("div"))))
+			{
+				ast_type_t op = _lexer.current() == lex_multiply ? ast_op_multiply :
+					_lexer.contents().begin[0] == 'd' ? ast_op_divide : ast_op_mod;
+				_lexer.next();
 
 				xpath_ast_node* expr = parse_unary_expression();
 
-	    		n = new (alloc_node()) xpath_ast_node(op, xpath_type_number, n, expr);
-	    	}
+				n = new (alloc_node()) xpath_ast_node(op, xpath_type_number, n, expr);
+			}
 
-	    	return n;
-	    }
+			return n;
+		}
 
-	    // AdditiveExpr ::= MultiplicativeExpr
-	    //					| AdditiveExpr '+' MultiplicativeExpr
-	    //					| AdditiveExpr '-' MultiplicativeExpr
-	    xpath_ast_node* parse_additive_expression()
-	    {
-	    	xpath_ast_node* n = parse_multiplicative_expression();
+		// AdditiveExpr ::= MultiplicativeExpr
+		//					| AdditiveExpr '+' MultiplicativeExpr
+		//					| AdditiveExpr '-' MultiplicativeExpr
+		xpath_ast_node* parse_additive_expression()
+		{
+			xpath_ast_node* n = parse_multiplicative_expression();
 
-	    	while (_lexer.current() == lex_plus || _lexer.current() == lex_minus)
-	    	{
-	    		lexeme_t l = _lexer.current();
+			while (_lexer.current() == lex_plus || _lexer.current() == lex_minus)
+			{
+				lexeme_t l = _lexer.current();
 
-	    		_lexer.next();
+				_lexer.next();
 
 				xpath_ast_node* expr = parse_multiplicative_expression();
 
-	    		n = new (alloc_node()) xpath_ast_node(l == lex_plus ? ast_op_add : ast_op_subtract, xpath_type_number, n, expr);
-	    	}
+				n = new (alloc_node()) xpath_ast_node(l == lex_plus ? ast_op_add : ast_op_subtract, xpath_type_number, n, expr);
+			}
 
-	    	return n;
-	    }
+			return n;
+		}
 
-	    // RelationalExpr ::= AdditiveExpr
-	    //					  | RelationalExpr '<' AdditiveExpr
-	    //					  | RelationalExpr '>' AdditiveExpr
-	    //					  | RelationalExpr '<=' AdditiveExpr
-	    //					  | RelationalExpr '>=' AdditiveExpr
-	    xpath_ast_node* parse_relational_expression()
-	    {
-	    	xpath_ast_node* n = parse_additive_expression();
+		// RelationalExpr ::= AdditiveExpr
+		//					  | RelationalExpr '<' AdditiveExpr
+		//					  | RelationalExpr '>' AdditiveExpr
+		//					  | RelationalExpr '<=' AdditiveExpr
+		//					  | RelationalExpr '>=' AdditiveExpr
+		xpath_ast_node* parse_relational_expression()
+		{
+			xpath_ast_node* n = parse_additive_expression();
 
-	    	while (_lexer.current() == lex_less || _lexer.current() == lex_less_or_equal || 
-	    		   _lexer.current() == lex_greater || _lexer.current() == lex_greater_or_equal)
-	    	{
-	    		lexeme_t l = _lexer.current();
-	    		_lexer.next();
+			while (_lexer.current() == lex_less || _lexer.current() == lex_less_or_equal || 
+				   _lexer.current() == lex_greater || _lexer.current() == lex_greater_or_equal)
+			{
+				lexeme_t l = _lexer.current();
+				_lexer.next();
 
 				xpath_ast_node* expr = parse_additive_expression();
 
-	    		n = new (alloc_node()) xpath_ast_node(l == lex_less ? ast_op_less : l == lex_greater ? ast_op_greater :
-	    						l == lex_less_or_equal ? ast_op_less_or_equal : ast_op_greater_or_equal, xpath_type_boolean, n, expr);
-	    	}
+				n = new (alloc_node()) xpath_ast_node(l == lex_less ? ast_op_less : l == lex_greater ? ast_op_greater :
+								l == lex_less_or_equal ? ast_op_less_or_equal : ast_op_greater_or_equal, xpath_type_boolean, n, expr);
+			}
 
-	    	return n;
-	    }
-	    
-	    // EqualityExpr ::= RelationalExpr
-	    //					| EqualityExpr '=' RelationalExpr
-	    //					| EqualityExpr '!=' RelationalExpr
-	    xpath_ast_node* parse_equality_expression()
-	    {
-	    	xpath_ast_node* n = parse_relational_expression();
+			return n;
+		}
+		
+		// EqualityExpr ::= RelationalExpr
+		//					| EqualityExpr '=' RelationalExpr
+		//					| EqualityExpr '!=' RelationalExpr
+		xpath_ast_node* parse_equality_expression()
+		{
+			xpath_ast_node* n = parse_relational_expression();
 
-	    	while (_lexer.current() == lex_equal || _lexer.current() == lex_not_equal)
-	    	{
-	    		lexeme_t l = _lexer.current();
+			while (_lexer.current() == lex_equal || _lexer.current() == lex_not_equal)
+			{
+				lexeme_t l = _lexer.current();
 
-	    		_lexer.next();
+				_lexer.next();
 
 				xpath_ast_node* expr = parse_relational_expression();
 
-	    		n = new (alloc_node()) xpath_ast_node(l == lex_equal ? ast_op_equal : ast_op_not_equal, xpath_type_boolean, n, expr);
-	    	}
+				n = new (alloc_node()) xpath_ast_node(l == lex_equal ? ast_op_equal : ast_op_not_equal, xpath_type_boolean, n, expr);
+			}
 
-	    	return n;
-	    }
-	    
-	    // AndExpr ::= EqualityExpr | AndExpr 'and' EqualityExpr
-	    xpath_ast_node* parse_and_expression()
-	    {
-	    	xpath_ast_node* n = parse_equality_expression();
+			return n;
+		}
+		
+		// AndExpr ::= EqualityExpr | AndExpr 'and' EqualityExpr
+		xpath_ast_node* parse_and_expression()
+		{
+			xpath_ast_node* n = parse_equality_expression();
 
-	    	while (_lexer.current() == lex_string && _lexer.contents() == PUGIXML_TEXT("and"))
-	    	{
-	    		_lexer.next();
+			while (_lexer.current() == lex_string && _lexer.contents() == PUGIXML_TEXT("and"))
+			{
+				_lexer.next();
 
 				xpath_ast_node* expr = parse_equality_expression();
 
-	    		n = new (alloc_node()) xpath_ast_node(ast_op_and, xpath_type_boolean, n, expr);
-	    	}
+				n = new (alloc_node()) xpath_ast_node(ast_op_and, xpath_type_boolean, n, expr);
+			}
 
-	    	return n;
-	    }
+			return n;
+		}
 
-	    // OrExpr ::= AndExpr | OrExpr 'or' AndExpr
-	    xpath_ast_node* parse_or_expression()
-	    {
-	    	xpath_ast_node* n = parse_and_expression();
+		// OrExpr ::= AndExpr | OrExpr 'or' AndExpr
+		xpath_ast_node* parse_or_expression()
+		{
+			xpath_ast_node* n = parse_and_expression();
 
-	    	while (_lexer.current() == lex_string && _lexer.contents() == PUGIXML_TEXT("or"))
-	    	{
-	    		_lexer.next();
+			while (_lexer.current() == lex_string && _lexer.contents() == PUGIXML_TEXT("or"))
+			{
+				_lexer.next();
 
 				xpath_ast_node* expr = parse_and_expression();
 
-	    		n = new (alloc_node()) xpath_ast_node(ast_op_or, xpath_type_boolean, n, expr);
-	    	}
+				n = new (alloc_node()) xpath_ast_node(ast_op_or, xpath_type_boolean, n, expr);
+			}
 
-	    	return n;
-	    }
+			return n;
+		}
 		
 		// Expr ::= OrExpr
 		xpath_ast_node* parse_expression()
@@ -8978,13 +9578,13 @@
 		}
 	};
 
-    struct xpath_query_impl
-    {
+	struct xpath_query_impl
+	{
 		static xpath_query_impl* create()
 		{
-			void* memory = global_allocate(sizeof(xpath_query_impl));
+			void* memory = xml_memory::allocate(sizeof(xpath_query_impl));
 
-            return new (memory) xpath_query_impl();
+			return new (memory) xpath_query_impl();
 		}
 
 		static void destroy(void* ptr)
@@ -8995,20 +9595,20 @@
 			static_cast<xpath_query_impl*>(ptr)->alloc.release();
 
 			// free allocator memory (with the first page)
-			global_deallocate(ptr);
+			xml_memory::deallocate(ptr);
 		}
 
-        xpath_query_impl(): root(0), alloc(&block)
-        {
-            block.next = 0;
-        }
+		xpath_query_impl(): root(0), alloc(&block)
+		{
+			block.next = 0;
+		}
 
-        xpath_ast_node* root;
-        xpath_allocator alloc;
-        xpath_memory_block block;
-    };
+		xpath_ast_node* root;
+		xpath_allocator alloc;
+		xpath_memory_block block;
+	};
 
-	xpath_string evaluate_string_impl(xpath_query_impl* impl, const xpath_node& n, xpath_stack_data& sd)
+	PUGI__FN xpath_string evaluate_string_impl(xpath_query_impl* impl, const xpath_node& n, xpath_stack_data& sd)
 	{
 		if (!impl) return xpath_string();
 
@@ -9020,113 +9620,111 @@
 
 		return impl->root->eval_string(c, sd.stack);
 	}
-}
-
-
-
-// Added by LG for OpenImageIO:
-OIIO_NAMESPACE_ENTER
-{
+PUGI__NS_END
 
 namespace pugi
 {
 #ifndef PUGIXML_NO_EXCEPTIONS
-	xpath_exception::xpath_exception(const xpath_parse_result& result): _result(result)
+	PUGI__FN xpath_exception::xpath_exception(const xpath_parse_result& result_): _result(result_)
 	{
-		assert(result.error);
+		assert(_result.error);
 	}
 	
-	const char* xpath_exception::what() const throw()
+	PUGI__FN const char* xpath_exception::what() const throw()
 	{
 		return _result.error;
 	}
 
-	const xpath_parse_result& xpath_exception::result() const
+	PUGI__FN const xpath_parse_result& xpath_exception::result() const
 	{
 		return _result;
 	}
 #endif
 	
-	xpath_node::xpath_node()
+	PUGI__FN xpath_node::xpath_node()
 	{
 	}
 		
-	xpath_node::xpath_node(const xml_node& node): _node(node)
+	PUGI__FN xpath_node::xpath_node(const xml_node& node_): _node(node_)
 	{
 	}
 		
-	xpath_node::xpath_node(const xml_attribute& attribute, const xml_node& parent): _node(attribute ? parent : xml_node()), _attribute(attribute)
+	PUGI__FN xpath_node::xpath_node(const xml_attribute& attribute_, const xml_node& parent_): _node(attribute_ ? parent_ : xml_node()), _attribute(attribute_)
 	{
 	}
 
-	xml_node xpath_node::node() const
+	PUGI__FN xml_node xpath_node::node() const
 	{
 		return _attribute ? xml_node() : _node;
 	}
 		
-	xml_attribute xpath_node::attribute() const
+	PUGI__FN xml_attribute xpath_node::attribute() const
 	{
 		return _attribute;
 	}
 	
-	xml_node xpath_node::parent() const
+	PUGI__FN xml_node xpath_node::parent() const
 	{
 		return _attribute ? _node : _node.parent();
 	}
 
-	xpath_node::operator xpath_node::unspecified_bool_type() const
+	PUGI__FN static void unspecified_bool_xpath_node(xpath_node***)
 	{
-		return (_node || _attribute) ? &xpath_node::_node : 0;
+	}
+
+	PUGI__FN xpath_node::operator xpath_node::unspecified_bool_type() const
+	{
+		return (_node || _attribute) ? unspecified_bool_xpath_node : 0;
 	}
 	
-	bool xpath_node::operator!() const
+	PUGI__FN bool xpath_node::operator!() const
 	{
 		return !(_node || _attribute);
 	}
 
-	bool xpath_node::operator==(const xpath_node& n) const
+	PUGI__FN bool xpath_node::operator==(const xpath_node& n) const
 	{
 		return _node == n._node && _attribute == n._attribute;
 	}
 	
-	bool xpath_node::operator!=(const xpath_node& n) const
+	PUGI__FN bool xpath_node::operator!=(const xpath_node& n) const
 	{
 		return _node != n._node || _attribute != n._attribute;
 	}
 
 #ifdef __BORLANDC__
-	bool operator&&(const xpath_node& lhs, bool rhs)
+	PUGI__FN bool operator&&(const xpath_node& lhs, bool rhs)
 	{
 		return (bool)lhs && rhs;
 	}
 
-	bool operator||(const xpath_node& lhs, bool rhs)
+	PUGI__FN bool operator||(const xpath_node& lhs, bool rhs)
 	{
 		return (bool)lhs || rhs;
 	}
 #endif
 
-	void xpath_node_set::_assign(const_iterator begin, const_iterator end)
+	PUGI__FN void xpath_node_set::_assign(const_iterator begin_, const_iterator end_)
 	{
-		assert(begin <= end);
+		assert(begin_ <= end_);
 
-		size_t size = static_cast<size_t>(end - begin);
+		size_t size_ = static_cast<size_t>(end_ - begin_);
 
-		if (size <= 1)
+		if (size_ <= 1)
 		{
 			// deallocate old buffer
-			if (_begin != &_storage) global_deallocate(_begin);
+			if (_begin != &_storage) impl::xml_memory::deallocate(_begin);
 
 			// use internal buffer
-			if (begin != end) _storage = *begin;
+			if (begin_ != end_) _storage = *begin_;
 
 			_begin = &_storage;
-			_end = &_storage + size;
+			_end = &_storage + size_;
 		}
 		else
 		{
 			// make heap copy
-			xpath_node* storage = static_cast<xpath_node*>(global_allocate(size * sizeof(xpath_node)));
+			xpath_node* storage = static_cast<xpath_node*>(impl::xml_memory::allocate(size_ * sizeof(xpath_node)));
 
 			if (!storage)
 			{
@@ -9137,37 +9735,37 @@
 			#endif
 			}
 
-			memcpy(storage, begin, size * sizeof(xpath_node));
+			memcpy(storage, begin_, size_ * sizeof(xpath_node));
 			
 			// deallocate old buffer
-			if (_begin != &_storage) global_deallocate(_begin);
+			if (_begin != &_storage) impl::xml_memory::deallocate(_begin);
 
 			// finalize
 			_begin = storage;
-			_end = storage + size;
+			_end = storage + size_;
 		}
 	}
 
-	xpath_node_set::xpath_node_set(): _type(type_unsorted), _begin(&_storage), _end(&_storage)
+	PUGI__FN xpath_node_set::xpath_node_set(): _type(type_unsorted), _begin(&_storage), _end(&_storage)
 	{
 	}
 
-	xpath_node_set::xpath_node_set(const_iterator begin, const_iterator end, type_t type): _type(type), _begin(&_storage), _end(&_storage)
+	PUGI__FN xpath_node_set::xpath_node_set(const_iterator begin_, const_iterator end_, type_t type_): _type(type_), _begin(&_storage), _end(&_storage)
 	{
-		_assign(begin, end);
+		_assign(begin_, end_);
 	}
 
-	xpath_node_set::~xpath_node_set()
+	PUGI__FN xpath_node_set::~xpath_node_set()
 	{
-		if (_begin != &_storage) global_deallocate(_begin);
+		if (_begin != &_storage) impl::xml_memory::deallocate(_begin);
 	}
 		
-	xpath_node_set::xpath_node_set(const xpath_node_set& ns): _type(ns._type), _begin(&_storage), _end(&_storage)
+	PUGI__FN xpath_node_set::xpath_node_set(const xpath_node_set& ns): _type(ns._type), _begin(&_storage), _end(&_storage)
 	{
 		_assign(ns._begin, ns._end);
 	}
 	
-	xpath_node_set& xpath_node_set::operator=(const xpath_node_set& ns)
+	PUGI__FN xpath_node_set& xpath_node_set::operator=(const xpath_node_set& ns)
 	{
 		if (this == &ns) return *this;
 		
@@ -9177,79 +9775,80 @@
 		return *this;
 	}
 
-	xpath_node_set::type_t xpath_node_set::type() const
+	PUGI__FN xpath_node_set::type_t xpath_node_set::type() const
 	{
 		return _type;
 	}
 		
-	size_t xpath_node_set::size() const
+	PUGI__FN size_t xpath_node_set::size() const
 	{
 		return _end - _begin;
 	}
 		
-	bool xpath_node_set::empty() const
+	PUGI__FN bool xpath_node_set::empty() const
 	{
 		return _begin == _end;
 	}
 		
-	const xpath_node& xpath_node_set::operator[](size_t index) const
+	PUGI__FN const xpath_node& xpath_node_set::operator[](size_t index) const
 	{
 		assert(index < size());
 		return _begin[index];
 	}
 
-	xpath_node_set::const_iterator xpath_node_set::begin() const
+	PUGI__FN xpath_node_set::const_iterator xpath_node_set::begin() const
 	{
 		return _begin;
 	}
 		
-	xpath_node_set::const_iterator xpath_node_set::end() const
+	PUGI__FN xpath_node_set::const_iterator xpath_node_set::end() const
 	{
 		return _end;
 	}
 	
-	void xpath_node_set::sort(bool reverse)
+	PUGI__FN void xpath_node_set::sort(bool reverse)
 	{
-		_type = xpath_sort(_begin, _end, _type, reverse);
+		_type = impl::xpath_sort(_begin, _end, _type, reverse);
 	}
 
-	xpath_node xpath_node_set::first() const
+	PUGI__FN xpath_node xpath_node_set::first() const
 	{
-		return xpath_first(_begin, _end, _type);
+		return impl::xpath_first(_begin, _end, _type);
 	}
 
-    xpath_parse_result::xpath_parse_result(): error("Internal error"), offset(0)
-    {
-    }
+	PUGI__FN xpath_parse_result::xpath_parse_result(): error("Internal error"), offset(0)
+	{
+	}
 
-    xpath_parse_result::operator bool() const
-    {
-        return error == 0;
-    }
-	const char* xpath_parse_result::description() const
+	PUGI__FN xpath_parse_result::operator bool() const
+	{
+		return error == 0;
+	}
+
+	PUGI__FN const char* xpath_parse_result::description() const
 	{
 		return error ? error : "No error";
 	}
 
-	xpath_variable::xpath_variable()
-    {
-    }
+	PUGI__FN xpath_variable::xpath_variable()
+	{
+	}
 
-	const char_t* xpath_variable::name() const
+	PUGI__FN const char_t* xpath_variable::name() const
 	{
 		switch (_type)
 		{
 		case xpath_type_node_set:
-			return static_cast<const xpath_variable_node_set*>(this)->name;
+			return static_cast<const impl::xpath_variable_node_set*>(this)->name;
 
 		case xpath_type_number:
-			return static_cast<const xpath_variable_number*>(this)->name;
+			return static_cast<const impl::xpath_variable_number*>(this)->name;
 
 		case xpath_type_string:
-			return static_cast<const xpath_variable_string*>(this)->name;
+			return static_cast<const impl::xpath_variable_string*>(this)->name;
 
 		case xpath_type_boolean:
-			return static_cast<const xpath_variable_boolean*>(this)->name;
+			return static_cast<const impl::xpath_variable_boolean*>(this)->name;
 
 		default:
 			assert(!"Invalid variable type");
@@ -9257,83 +9856,83 @@
 		}
 	}
 
-	xpath_value_type xpath_variable::type() const
+	PUGI__FN xpath_value_type xpath_variable::type() const
 	{
 		return _type;
 	}
 
-	bool xpath_variable::get_boolean() const
+	PUGI__FN bool xpath_variable::get_boolean() const
 	{
-		return (_type == xpath_type_boolean) ? static_cast<const xpath_variable_boolean*>(this)->value : false;
+		return (_type == xpath_type_boolean) ? static_cast<const impl::xpath_variable_boolean*>(this)->value : false;
 	}
 
-	double xpath_variable::get_number() const
+	PUGI__FN double xpath_variable::get_number() const
 	{
-		return (_type == xpath_type_number) ? static_cast<const xpath_variable_number*>(this)->value : gen_nan();
+		return (_type == xpath_type_number) ? static_cast<const impl::xpath_variable_number*>(this)->value : impl::gen_nan();
 	}
 
-	const char_t* xpath_variable::get_string() const
+	PUGI__FN const char_t* xpath_variable::get_string() const
 	{
-		const char_t* value = (_type == xpath_type_string) ? static_cast<const xpath_variable_string*>(this)->value : 0;
+		const char_t* value = (_type == xpath_type_string) ? static_cast<const impl::xpath_variable_string*>(this)->value : 0;
 		return value ? value : PUGIXML_TEXT("");
 	}
 
-	const xpath_node_set& xpath_variable::get_node_set() const
+	PUGI__FN const xpath_node_set& xpath_variable::get_node_set() const
 	{
-		return (_type == xpath_type_node_set) ? static_cast<const xpath_variable_node_set*>(this)->value : dummy_node_set;
+		return (_type == xpath_type_node_set) ? static_cast<const impl::xpath_variable_node_set*>(this)->value : impl::dummy_node_set;
 	}
 
-	bool xpath_variable::set(bool value)
+	PUGI__FN bool xpath_variable::set(bool value)
 	{
 		if (_type != xpath_type_boolean) return false;
 
-		static_cast<xpath_variable_boolean*>(this)->value = value;
+		static_cast<impl::xpath_variable_boolean*>(this)->value = value;
 		return true;
 	}
 
-	bool xpath_variable::set(double value)
+	PUGI__FN bool xpath_variable::set(double value)
 	{
 		if (_type != xpath_type_number) return false;
 
-		static_cast<xpath_variable_number*>(this)->value = value;
+		static_cast<impl::xpath_variable_number*>(this)->value = value;
 		return true;
 	}
 
-	bool xpath_variable::set(const char_t* value)
+	PUGI__FN bool xpath_variable::set(const char_t* value)
 	{
 		if (_type != xpath_type_string) return false;
 
-		xpath_variable_string* var = static_cast<xpath_variable_string*>(this);
+		impl::xpath_variable_string* var = static_cast<impl::xpath_variable_string*>(this);
 
 		// duplicate string
-		size_t size = (strlength(value) + 1) * sizeof(char_t);
+		size_t size = (impl::strlength(value) + 1) * sizeof(char_t);
 
-		char_t* copy = static_cast<char_t*>(global_allocate(size));
+		char_t* copy = static_cast<char_t*>(impl::xml_memory::allocate(size));
 		if (!copy) return false;
 
 		memcpy(copy, value, size);
 
 		// replace old string
-		if (var->value) global_deallocate(var->value);
+		if (var->value) impl::xml_memory::deallocate(var->value);
 		var->value = copy;
 
 		return true;
 	}
 
-	bool xpath_variable::set(const xpath_node_set& value)
+	PUGI__FN bool xpath_variable::set(const xpath_node_set& value)
 	{
 		if (_type != xpath_type_node_set) return false;
 
-		static_cast<xpath_variable_node_set*>(this)->value = value;
+		static_cast<impl::xpath_variable_node_set*>(this)->value = value;
 		return true;
 	}
 
-	xpath_variable_set::xpath_variable_set()
+	PUGI__FN xpath_variable_set::xpath_variable_set()
 	{
 		for (size_t i = 0; i < sizeof(_data) / sizeof(_data[0]); ++i) _data[i] = 0;
 	}
 
-	xpath_variable_set::~xpath_variable_set()
+	PUGI__FN xpath_variable_set::~xpath_variable_set()
 	{
 		for (size_t i = 0; i < sizeof(_data) / sizeof(_data[0]); ++i)
 		{
@@ -9343,38 +9942,38 @@
 			{
 				xpath_variable* next = var->_next;
 
-				delete_xpath_variable(var->_type, var);
+				impl::delete_xpath_variable(var->_type, var);
 
 				var = next;
 			}
 		}
 	}
 
-	xpath_variable* xpath_variable_set::find(const char_t* name) const
+	PUGI__FN xpath_variable* xpath_variable_set::find(const char_t* name) const
 	{
 		const size_t hash_size = sizeof(_data) / sizeof(_data[0]);
-		size_t hash = hash_string(name) % hash_size;
+		size_t hash = impl::hash_string(name) % hash_size;
 
 		// look for existing variable
 		for (xpath_variable* var = _data[hash]; var; var = var->_next)
-			if (strequal(var->name(), name))
+			if (impl::strequal(var->name(), name))
 				return var;
 
 		return 0;
 	}
 
-	xpath_variable* xpath_variable_set::add(const char_t* name, xpath_value_type type)
+	PUGI__FN xpath_variable* xpath_variable_set::add(const char_t* name, xpath_value_type type)
 	{
 		const size_t hash_size = sizeof(_data) / sizeof(_data[0]);
-		size_t hash = hash_string(name) % hash_size;
+		size_t hash = impl::hash_string(name) % hash_size;
 
 		// look for existing variable
 		for (xpath_variable* var = _data[hash]; var; var = var->_next)
-			if (strequal(var->name(), name))
+			if (impl::strequal(var->name(), name))
 				return var->type() == type ? var : 0;
 
 		// add new variable
-		xpath_variable* result = new_xpath_variable(type, name);
+		xpath_variable* result = impl::new_xpath_variable(type, name);
 
 		if (result)
 		{
@@ -9387,199 +9986,203 @@
 		return result;
 	}
 
-	bool xpath_variable_set::set(const char_t* name, bool value)
+	PUGI__FN bool xpath_variable_set::set(const char_t* name, bool value)
 	{
 		xpath_variable* var = add(name, xpath_type_boolean);
 		return var ? var->set(value) : false;
 	}
 
-	bool xpath_variable_set::set(const char_t* name, double value)
+	PUGI__FN bool xpath_variable_set::set(const char_t* name, double value)
 	{
 		xpath_variable* var = add(name, xpath_type_number);
 		return var ? var->set(value) : false;
 	}
 
-	bool xpath_variable_set::set(const char_t* name, const char_t* value)
+	PUGI__FN bool xpath_variable_set::set(const char_t* name, const char_t* value)
 	{
 		xpath_variable* var = add(name, xpath_type_string);
 		return var ? var->set(value) : false;
 	}
 
-	bool xpath_variable_set::set(const char_t* name, const xpath_node_set& value)
+	PUGI__FN bool xpath_variable_set::set(const char_t* name, const xpath_node_set& value)
 	{
 		xpath_variable* var = add(name, xpath_type_node_set);
 		return var ? var->set(value) : false;
 	}
 
-	xpath_variable* xpath_variable_set::get(const char_t* name)
+	PUGI__FN xpath_variable* xpath_variable_set::get(const char_t* name)
 	{
 		return find(name);
 	}
 
-	const xpath_variable* xpath_variable_set::get(const char_t* name) const
+	PUGI__FN const xpath_variable* xpath_variable_set::get(const char_t* name) const
 	{
 		return find(name);
 	}
 
-	xpath_query::xpath_query(const char_t* query, xpath_variable_set* variables): _impl(0)
+	PUGI__FN xpath_query::xpath_query(const char_t* query, xpath_variable_set* variables): _impl(0)
 	{
-		xpath_query_impl* impl = xpath_query_impl::create();
+		impl::xpath_query_impl* qimpl = impl::xpath_query_impl::create();
 
-		if (!impl)
+		if (!qimpl)
 		{
 		#ifdef PUGIXML_NO_EXCEPTIONS
 			_result.error = "Out of memory";
-        #else
+		#else
 			throw std::bad_alloc();
 		#endif
 		}
 		else
 		{
-			buffer_holder impl_holder(impl, xpath_query_impl::destroy);
+			impl::buffer_holder impl_holder(qimpl, impl::xpath_query_impl::destroy);
 
-			impl->root = xpath_parser::parse(query, variables, &impl->alloc, &_result);
+			qimpl->root = impl::xpath_parser::parse(query, variables, &qimpl->alloc, &_result);
 
-			if (impl->root)
+			if (qimpl->root)
 			{
-                _impl = static_cast<xpath_query_impl*>(impl_holder.release());
+				_impl = static_cast<impl::xpath_query_impl*>(impl_holder.release());
 				_result.error = 0;
 			}
 		}
 	}
 
-	xpath_query::~xpath_query()
+	PUGI__FN xpath_query::~xpath_query()
 	{
-		xpath_query_impl::destroy(_impl);
+		impl::xpath_query_impl::destroy(_impl);
 	}
 
-	xpath_value_type xpath_query::return_type() const
+	PUGI__FN xpath_value_type xpath_query::return_type() const
 	{
 		if (!_impl) return xpath_type_none;
 
-		return static_cast<xpath_query_impl*>(_impl)->root->rettype();
+		return static_cast<impl::xpath_query_impl*>(_impl)->root->rettype();
 	}
 
-	bool xpath_query::evaluate_boolean(const xpath_node& n) const
+	PUGI__FN bool xpath_query::evaluate_boolean(const xpath_node& n) const
 	{
 		if (!_impl) return false;
 		
-		xpath_context c(n, 1, 1);
-		xpath_stack_data sd;
+		impl::xpath_context c(n, 1, 1);
+		impl::xpath_stack_data sd;
 
 	#ifdef PUGIXML_NO_EXCEPTIONS
 		if (setjmp(sd.error_handler)) return false;
 	#endif
 		
-		return static_cast<xpath_query_impl*>(_impl)->root->eval_boolean(c, sd.stack);
+		return static_cast<impl::xpath_query_impl*>(_impl)->root->eval_boolean(c, sd.stack);
 	}
 	
-	double xpath_query::evaluate_number(const xpath_node& n) const
+	PUGI__FN double xpath_query::evaluate_number(const xpath_node& n) const
 	{
-		if (!_impl) return gen_nan();
+		if (!_impl) return impl::gen_nan();
 		
-		xpath_context c(n, 1, 1);
-		xpath_stack_data sd;
+		impl::xpath_context c(n, 1, 1);
+		impl::xpath_stack_data sd;
 
 	#ifdef PUGIXML_NO_EXCEPTIONS
-		if (setjmp(sd.error_handler)) return gen_nan();
+		if (setjmp(sd.error_handler)) return impl::gen_nan();
 	#endif
 
-		return static_cast<xpath_query_impl*>(_impl)->root->eval_number(c, sd.stack);
+		return static_cast<impl::xpath_query_impl*>(_impl)->root->eval_number(c, sd.stack);
 	}
 
 #ifndef PUGIXML_NO_STL
-	string_t xpath_query::evaluate_string(const xpath_node& n) const
+	PUGI__FN string_t xpath_query::evaluate_string(const xpath_node& n) const
 	{
-		xpath_stack_data sd;
+		impl::xpath_stack_data sd;
 
-		return evaluate_string_impl(static_cast<xpath_query_impl*>(_impl), n, sd).c_str();
+		return impl::evaluate_string_impl(static_cast<impl::xpath_query_impl*>(_impl), n, sd).c_str();
 	}
 #endif
 
-	size_t xpath_query::evaluate_string(char_t* buffer, size_t capacity, const xpath_node& n) const
+	PUGI__FN size_t xpath_query::evaluate_string(char_t* buffer, size_t capacity, const xpath_node& n) const
 	{
-		xpath_stack_data sd;
+		impl::xpath_stack_data sd;
 
-		xpath_string r = evaluate_string_impl(static_cast<xpath_query_impl*>(_impl), n, sd);
+		impl::xpath_string r = impl::evaluate_string_impl(static_cast<impl::xpath_query_impl*>(_impl), n, sd);
 
 		size_t full_size = r.length() + 1;
 		
 		if (capacity > 0)
-        {
-            size_t size = (full_size < capacity) ? full_size : capacity;
-            assert(size > 0);
+		{
+			size_t size = (full_size < capacity) ? full_size : capacity;
+			assert(size > 0);
 
-            memcpy(buffer, r.c_str(), (size - 1) * sizeof(char_t));
-            buffer[size - 1] = 0;
-        }
+			memcpy(buffer, r.c_str(), (size - 1) * sizeof(char_t));
+			buffer[size - 1] = 0;
+		}
 		
 		return full_size;
 	}
 
-	xpath_node_set xpath_query::evaluate_node_set(const xpath_node& n) const
+	PUGI__FN xpath_node_set xpath_query::evaluate_node_set(const xpath_node& n) const
 	{
 		if (!_impl) return xpath_node_set();
 
-        xpath_ast_node* root = static_cast<xpath_query_impl*>(_impl)->root;
+		impl::xpath_ast_node* root = static_cast<impl::xpath_query_impl*>(_impl)->root;
 
 		if (root->rettype() != xpath_type_node_set)
 		{
 		#ifdef PUGIXML_NO_EXCEPTIONS
 			return xpath_node_set();
 		#else
-			xpath_parse_result result;
-			result.error = "Expression does not evaluate to node set";
+			xpath_parse_result res;
+			res.error = "Expression does not evaluate to node set";
 
-			throw xpath_exception(result);
+			throw xpath_exception(res);
 		#endif
 		}
 		
-		xpath_context c(n, 1, 1);
-		xpath_stack_data sd;
+		impl::xpath_context c(n, 1, 1);
+		impl::xpath_stack_data sd;
 
 	#ifdef PUGIXML_NO_EXCEPTIONS
 		if (setjmp(sd.error_handler)) return xpath_node_set();
 	#endif
 
-		xpath_node_set_raw r = root->eval_node_set(c, sd.stack);
+		impl::xpath_node_set_raw r = root->eval_node_set(c, sd.stack);
 
 		return xpath_node_set(r.begin(), r.end(), r.type());
 	}
 
-	const xpath_parse_result& xpath_query::result() const
+	PUGI__FN const xpath_parse_result& xpath_query::result() const
 	{
 		return _result;
 	}
 
-	xpath_query::operator xpath_query::unspecified_bool_type() const
+	PUGI__FN static void unspecified_bool_xpath_query(xpath_query***)
 	{
-		return _impl ? &xpath_query::_impl : 0;
 	}
 
-	bool xpath_query::operator!() const
+	PUGI__FN xpath_query::operator xpath_query::unspecified_bool_type() const
+	{
+		return _impl ? unspecified_bool_xpath_query : 0;
+	}
+
+	PUGI__FN bool xpath_query::operator!() const
 	{
 		return !_impl;
 	}
 
-	xpath_node xml_node::select_single_node(const char_t* query, xpath_variable_set* variables) const
+	PUGI__FN xpath_node xml_node::select_single_node(const char_t* query, xpath_variable_set* variables) const
 	{
 		xpath_query q(query, variables);
 		return select_single_node(q);
 	}
 
-	xpath_node xml_node::select_single_node(const xpath_query& query) const
+	PUGI__FN xpath_node xml_node::select_single_node(const xpath_query& query) const
 	{
 		xpath_node_set s = query.evaluate_node_set(*this);
 		return s.empty() ? xpath_node() : s.first();
 	}
 
-	xpath_node_set xml_node::select_nodes(const char_t* query, xpath_variable_set* variables) const
+	PUGI__FN xpath_node_set xml_node::select_nodes(const char_t* query, xpath_variable_set* variables) const
 	{
 		xpath_query q(query, variables);
 		return select_nodes(q);
 	}
 
-	xpath_node_set xml_node::select_nodes(const xpath_query& query) const
+	PUGI__FN xpath_node_set xml_node::select_nodes(const xpath_query& query) const
 	{
 		return query.evaluate_node_set(*this);
 	}
@@ -9587,14 +10190,42 @@
 
 #endif
 
+#ifdef __BORLANDC__
+#	pragma option pop
+#endif
 
-// Added by LG for OpenImageIO:
-}
-OIIO_NAMESPACE_EXIT
+// Intel C++ does not properly keep warning state for function templates,
+// so popping warning state at the end of translation unit leads to warnings in the middle.
+#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
+#	pragma warning(pop)
+#endif
 
+// Undefine all local macros (makes sure we're not leaking macros in header-only mode)
+#undef PUGI__NO_INLINE
+#undef PUGI__STATIC_ASSERT
+#undef PUGI__DMC_VOLATILE
+#undef PUGI__MSVC_CRT_VERSION
+#undef PUGI__NS_BEGIN
+#undef PUGI__NS_END
+#undef PUGI__FN
+#undef PUGI__FN_NO_INLINE
+#undef PUGI__IS_CHARTYPE_IMPL
+#undef PUGI__IS_CHARTYPE
+#undef PUGI__IS_CHARTYPEX
+#undef PUGI__SKIPWS
+#undef PUGI__OPTSET
+#undef PUGI__PUSHNODE
+#undef PUGI__POPNODE
+#undef PUGI__SCANFOR
+#undef PUGI__SCANWHILE
+#undef PUGI__ENDSEG
+#undef PUGI__THROW_ERROR
+#undef PUGI__CHECK_ERROR
+
+#endif
 
 /**
- * Copyright (c) 2006-2010 Arseny Kapoulkine
+ * Copyright (c) 2006-2012 Arseny Kapoulkine
  *
  * Permission is hereby granted, free of charge, to any person
  * obtaining a copy of this software and associated documentation
