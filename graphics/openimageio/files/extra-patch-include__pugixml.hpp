--- ./include/pugixml.hpp.orig	2013-10-03 00:57:46.000000000 +0930
+++ ./include/pugixml.hpp	2013-10-03 00:59:16.000000000 +0930
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
@@ -11,44 +11,30 @@
  * Copyright (C) 2003, by Kristen Wegner (kristen@tima.net)
  */
 
-#ifndef HEADER_PUGIXML_HPP
-#define HEADER_PUGIXML_HPP
+#ifndef PUGIXML_VERSION
+// Define version macro; evaluates to major * 100 + minor so that it's safe to use in less-than comparisons
+#	define PUGIXML_VERSION 120
+#endif
 
+// Include user configuration file (this can define various configuration macros)
 #include "pugiconfig.hpp"
-#include "version.h"
-
-// Signify that we use Pugixml embedded in OIIO.  If OIIO is compiled with
-// the system Pugi, this will not be defined.
-#define USING_OIIO_PUGI 1
 
+#ifndef HEADER_PUGIXML_HPP
+#define HEADER_PUGIXML_HPP
 
-#ifndef PUGIXML_NO_STL
-namespace std
-{
-	struct bidirectional_iterator_tag;
+// Include stddef.h for size_t and ptrdiff_t
+#include <stddef.h>
 
-#ifdef __SUNPRO_CC
-	// Sun C++ compiler has a bug which forces template argument names in forward declarations to be the same as in actual definitions
-	template <class _T> class allocator;
-	template <class _charT> struct char_traits;
-	template <class _charT, class _Traits> class basic_istream;
-	template <class _charT, class _Traits> class basic_ostream;
-	template <class _charT, class _Traits, class _Allocator> class basic_string;
-#else
-	// Borland C++ compiler has a bug which forces template argument names in forward declarations to be the same as in actual definitions
-	template <class _Ty> class allocator;
-	template <class _Ty> struct char_traits;
-	template <class _Elem, class _Traits> class basic_istream;
-	template <class _Elem, class _Traits> class basic_ostream;
-	template <class _Elem, class _Traits, class _Ax> class basic_string;
+// Include exception header for XPath
+#if !defined(PUGIXML_NO_XPATH) && !defined(PUGIXML_NO_EXCEPTIONS)
+#	include <exception>
 #endif
 
-	// Digital Mars compiler has a bug which requires a forward declaration for explicit instantiation (otherwise type selection is messed up later, producing link errors)
-	// Also note that we have to declare char_traits as a class here, since it's defined that way
-#ifdef __DMC__
-	template <> class char_traits<char>;
-#endif
-}
+// Include STL headers
+#ifndef PUGIXML_NO_STL
+#	include <iterator>
+#	include <iosfwd>
+#	include <string>
 #endif
 
 // Macro for deprecated features
@@ -62,28 +48,21 @@
 #	endif
 #endif
 
-// Include exception header for XPath
-#if !defined(PUGIXML_NO_XPATH) && !defined(PUGIXML_NO_EXCEPTIONS)
-#	include <exception>
-#endif
-
 // If no API is defined, assume default
 #ifndef PUGIXML_API
-#   define PUGIXML_API
+#	define PUGIXML_API
 #endif
 
 // If no API for classes is defined, assume default
 #ifndef PUGIXML_CLASS
-#   define PUGIXML_CLASS PUGIXML_API
+#	define PUGIXML_CLASS PUGIXML_API
 #endif
 
 // If no API for functions is defined, assume default
 #ifndef PUGIXML_FUNCTION
-#   define PUGIXML_FUNCTION PUGIXML_API
+#	define PUGIXML_FUNCTION PUGIXML_API
 #endif
 
-#include <stddef.h>
-
 // Character interface macros
 #ifdef PUGIXML_WCHAR_MODE
 #	define PUGIXML_TEXT(t) L ## t
@@ -93,11 +72,6 @@
 #	define PUGIXML_CHAR char
 #endif
 
-
-// Added by LG for OpenImageIO:
-OIIO_NAMESPACE_ENTER
-{
-
 namespace pugi
 {
 	// Character type used for all internal storage and operations; depends on PUGIXML_WCHAR_MODE
@@ -115,7 +89,7 @@
 	// Tree node types
 	enum xml_node_type
 	{
-		node_null,          // Empty (null) node handle
+		node_null,			// Empty (null) node handle
 		node_document,		// A document tree's absolute root
 		node_element,		// Element tag, i.e. '<node/>'
 		node_pcdata,		// Plain character data, i.e. 'text'
@@ -123,13 +97,13 @@
 		node_comment,		// Comment tag, i.e. '<!-- text -->'
 		node_pi,			// Processing instruction, i.e. '<?name?>'
 		node_declaration,	// Document declaration, i.e. '<?xml version="1.0"?>'
-        node_doctype        // Document type declaration, i.e. '<!DOCTYPE doc>'
+		node_doctype		// Document type declaration, i.e. '<!DOCTYPE doc>'
 	};
 
 	// Parsing options
 
 	// Minimal parsing mode (equivalent to turning all other flags off).
-    // Only elements and PCDATA sections are added to the DOM tree, no text conversions are performed.
+	// Only elements and PCDATA sections are added to the DOM tree, no text conversions are performed.
 	const unsigned int parse_minimal = 0x0000;
 
 	// This flag determines if processing instructions (node_pi) are added to the DOM tree. This flag is off by default.
@@ -142,7 +116,7 @@
 	const unsigned int parse_cdata = 0x0004;
 
 	// This flag determines if plain character data (node_pcdata) that consist only of whitespace are added to the DOM tree.
-    // This flag is off by default; turning it on usually results in slower parsing and more memory consumption.
+	// This flag is off by default; turning it on usually results in slower parsing and more memory consumption.
 	const unsigned int parse_ws_pcdata = 0x0008;
 
 	// This flag determines if character and entity references are expanded during parsing. This flag is on by default.
@@ -151,40 +125,46 @@
 	// This flag determines if EOL characters are normalized (converted to #xA) during parsing. This flag is on by default.
 	const unsigned int parse_eol = 0x0020;
 	
- 	// This flag determines if attribute values are normalized using CDATA normalization rules during parsing. This flag is on by default.
- 	const unsigned int parse_wconv_attribute = 0x0040;
+	// This flag determines if attribute values are normalized using CDATA normalization rules during parsing. This flag is on by default.
+	const unsigned int parse_wconv_attribute = 0x0040;
 
- 	// This flag determines if attribute values are normalized using NMTOKENS normalization rules during parsing. This flag is off by default.
- 	const unsigned int parse_wnorm_attribute = 0x0080;
+	// This flag determines if attribute values are normalized using NMTOKENS normalization rules during parsing. This flag is off by default.
+	const unsigned int parse_wnorm_attribute = 0x0080;
 	
-    // This flag determines if document declaration (node_declaration) is added to the DOM tree. This flag is off by default.
+	// This flag determines if document declaration (node_declaration) is added to the DOM tree. This flag is off by default.
 	const unsigned int parse_declaration = 0x0100;
 
-    // This flag determines if document type declaration (node_doctype) is added to the DOM tree. This flag is off by default.
+	// This flag determines if document type declaration (node_doctype) is added to the DOM tree. This flag is off by default.
 	const unsigned int parse_doctype = 0x0200;
 
+	// This flag determines if plain character data (node_pcdata) that is the only child of the parent node and that consists only
+	// of whitespace is added to the DOM tree.
+	// This flag is off by default; turning it on may result in slower parsing and more memory consumption.
+	const unsigned int parse_ws_pcdata_single = 0x0400;
+
 	// The default parsing mode.
-    // Elements, PCDATA and CDATA sections are added to the DOM tree, character/reference entities are expanded,
-    // End-of-Line characters are normalized, attribute values are normalized using CDATA normalization rules.
+	// Elements, PCDATA and CDATA sections are added to the DOM tree, character/reference entities are expanded,
+	// End-of-Line characters are normalized, attribute values are normalized using CDATA normalization rules.
 	const unsigned int parse_default = parse_cdata | parse_escapes | parse_wconv_attribute | parse_eol;
 
-    // The full parsing mode.
-    // Nodes of all types are added to the DOM tree, character/reference entities are expanded,
-    // End-of-Line characters are normalized, attribute values are normalized using CDATA normalization rules.
-    const unsigned int parse_full = parse_default | parse_pi | parse_comments | parse_declaration | parse_doctype;
+	// The full parsing mode.
+	// Nodes of all types are added to the DOM tree, character/reference entities are expanded,
+	// End-of-Line characters are normalized, attribute values are normalized using CDATA normalization rules.
+	const unsigned int parse_full = parse_default | parse_pi | parse_comments | parse_declaration | parse_doctype;
 
 	// These flags determine the encoding of input data for XML document
 	enum xml_encoding
 	{
-		encoding_auto,      // Auto-detect input encoding using BOM or < / <? detection; use UTF8 if BOM is not found
-		encoding_utf8,      // UTF8 encoding
-		encoding_utf16_le,  // Little-endian UTF16
-		encoding_utf16_be,  // Big-endian UTF16
-		encoding_utf16,     // UTF16 with native endianness
-		encoding_utf32_le,  // Little-endian UTF32
-		encoding_utf32_be,  // Big-endian UTF32
-		encoding_utf32,     // UTF32 with native endianness
-		encoding_wchar      // The same encoding wchar_t has (either UTF16 or UTF32)
+		encoding_auto,		// Auto-detect input encoding using BOM or < / <? detection; use UTF8 if BOM is not found
+		encoding_utf8,		// UTF8 encoding
+		encoding_utf16_le,	// Little-endian UTF16
+		encoding_utf16_be,	// Big-endian UTF16
+		encoding_utf16,		// UTF16 with native endianness
+		encoding_utf32_le,	// Little-endian UTF32
+		encoding_utf32_be,	// Big-endian UTF32
+		encoding_utf32,		// UTF32 with native endianness
+		encoding_wchar,		// The same encoding wchar_t has (either UTF16 or UTF32)
+		encoding_latin1
 	};
 
 	// Formatting flags
@@ -201,8 +181,14 @@
 	// Omit default XML declaration even if there is no declaration in the document. This flag is off by default.
 	const unsigned int format_no_declaration = 0x08;
 
+	// Don't escape attribute values and PCDATA contents. This flag is off by default.
+	const unsigned int format_no_escapes = 0x10;
+
+	// Open file using text mode in xml_document::save_file. This enables special character (i.e. new-line) conversions on some systems. This flag is off by default.
+	const unsigned int format_save_file_text = 0x20;
+
 	// The default set of formatting flags.
-    // Nodes are indented depending on their depth in DOM tree, a default declaration is output if document has none.
+	// Nodes are indented depending on their depth in DOM tree, a default declaration is output if document has none.
 	const unsigned int format_default = format_indent;
 		
 	// Forward declarations
@@ -211,11 +197,14 @@
 
 	class xml_node_iterator;
 	class xml_attribute_iterator;
+	class xml_named_node_iterator;
 
 	class xml_tree_walker;
-	
+
 	class xml_node;
 
+	class xml_text;
+	
 	#ifndef PUGIXML_NO_XPATH
 	class xpath_node;
 	class xpath_node_set;
@@ -223,6 +212,23 @@
 	class xpath_variable_set;
 	#endif
 
+	// Range-based for loop support
+	template <typename It> class xml_object_range
+	{
+	public:
+		typedef It const_iterator;
+
+		xml_object_range(It b, It e): _begin(b), _end(e)
+		{
+		}
+
+		It begin() const { return _begin; }
+		It end() const { return _end; }
+
+	private:
+		It _begin, _end;
+	};
+
 	// Writer interface for node printing (see xml_node::print)
 	class PUGIXML_CLASS xml_writer
 	{
@@ -237,7 +243,7 @@
 	class PUGIXML_CLASS xml_writer_file: public xml_writer
 	{
 	public:
-        // Construct writer from a FILE* object; void* is used to avoid header dependencies on stdio
+		// Construct writer from a FILE* object; void* is used to avoid header dependencies on stdio
 		xml_writer_file(void* file);
 
 		virtual void write(const void* data, size_t size);
@@ -251,7 +257,7 @@
 	class PUGIXML_CLASS xml_writer_stream: public xml_writer
 	{
 	public:
-        // Construct writer from an output stream object
+		// Construct writer from an output stream object
 		xml_writer_stream(std::basic_ostream<char, std::char_traits<char> >& stream);
 		xml_writer_stream(std::basic_ostream<wchar_t, std::char_traits<wchar_t> >& stream);
 
@@ -272,20 +278,20 @@
 	private:
 		xml_attribute_struct* _attr;
 	
-    	typedef xml_attribute_struct* xml_attribute::*unspecified_bool_type;
+		typedef void (*unspecified_bool_type)(xml_attribute***);
 
 	public:
-        // Default constructor. Constructs an empty attribute.
+		// Default constructor. Constructs an empty attribute.
 		xml_attribute();
 		
-        // Constructs attribute from internal pointer
+		// Constructs attribute from internal pointer
 		explicit xml_attribute(xml_attribute_struct* attr);
 
-    	// Safe bool conversion operator
-    	operator unspecified_bool_type() const;
+		// Safe bool conversion operator
+		operator unspecified_bool_type() const;
 
-    	// Borland C++ workaround
-    	bool operator!() const;
+		// Borland C++ workaround
+		bool operator!() const;
 
 		// Comparison operators (compares wrapped attribute pointers)
 		bool operator==(const xml_attribute& r) const;
@@ -302,20 +308,23 @@
 		const char_t* name() const;
 		const char_t* value() const;
 
-		// Get attribute value as a number, or 0 if conversion did not succeed or attribute is empty
-		int as_int() const;
-		unsigned int as_uint() const;
-		double as_double() const;
-		float as_float() const;
+		// Get attribute value, or the default value if attribute is empty
+		const char_t* as_string(const char_t* def = PUGIXML_TEXT("")) const;
 
-        // Get attribute value as bool (returns true if first character is in '1tTyY' set), or false if attribute is empty
-		bool as_bool() const;
+		// Get attribute value as a number, or the default value if conversion did not succeed or attribute is empty
+		int as_int(int def = 0) const;
+		unsigned int as_uint(unsigned int def = 0) const;
+		double as_double(double def = 0) const;
+		float as_float(float def = 0) const;
 
-        // Set attribute name/value (returns false if attribute is empty or there is not enough memory)
+		// Get attribute value as bool (returns true if first character is in '1tTyY' set), or the default value if attribute is empty
+		bool as_bool(bool def = false) const;
+
+		// Set attribute name/value (returns false if attribute is empty or there is not enough memory)
 		bool set_name(const char_t* rhs);
 		bool set_value(const char_t* rhs);
 
-        // Set attribute value with type conversion (numbers are converted to strings, boolean is converted to "true"/"false")
+		// Set attribute value with type conversion (numbers are converted to strings, boolean is converted to "true"/"false")
 		bool set_value(int rhs);
 		bool set_value(unsigned int rhs);
 		bool set_value(double rhs);
@@ -328,12 +337,12 @@
 		xml_attribute& operator=(double rhs);
 		xml_attribute& operator=(bool rhs);
 
-        // Get next/previous attribute in the attribute list of the parent node
-    	xml_attribute next_attribute() const;
-    	xml_attribute previous_attribute() const;
+		// Get next/previous attribute in the attribute list of the parent node
+		xml_attribute next_attribute() const;
+		xml_attribute previous_attribute() const;
 
-        // Get hash value (unique for handles to the same object)
-        size_t hash_value() const;
+		// Get hash value (unique for handles to the same object)
+		size_t hash_value() const;
 
 		// Get internal pointer
 		xml_attribute_struct* internal_object() const;
@@ -350,20 +359,21 @@
 	{
 		friend class xml_attribute_iterator;
 		friend class xml_node_iterator;
+		friend class xml_named_node_iterator;
 
 	protected:
 		xml_node_struct* _root;
 
-    	typedef xml_node_struct* xml_node::*unspecified_bool_type;
+		typedef void (*unspecified_bool_type)(xml_node***);
 
 	public:
 		// Default constructor. Constructs an empty node.
 		xml_node();
 
-        // Constructs node from internal pointer
+		// Constructs node from internal pointer
 		explicit xml_node(xml_node_struct* p);
 
-    	// Safe bool conversion operator
+		// Safe bool conversion operator
 		operator unspecified_bool_type() const;
 
 		// Borland C++ workaround
@@ -389,22 +399,25 @@
 	
 		// Get attribute list
 		xml_attribute first_attribute() const;
-        xml_attribute last_attribute() const;
+		xml_attribute last_attribute() const;
 
-        // Get children list
+		// Get children list
 		xml_node first_child() const;
-        xml_node last_child() const;
+		xml_node last_child() const;
 
-        // Get next/previous sibling in the children list of the parent node
+		// Get next/previous sibling in the children list of the parent node
 		xml_node next_sibling() const;
 		xml_node previous_sibling() const;
 		
-        // Get parent node
+		// Get parent node
 		xml_node parent() const;
 
 		// Get root of DOM tree this node belongs to
 		xml_node root() const;
 
+		// Get text object for the current node
+		xml_text text() const;
+
 		// Get child, attribute or next/previous sibling with the specified name
 		xml_node child(const char_t* name) const;
 		xml_attribute attribute(const char_t* name) const;
@@ -479,8 +492,8 @@
 			for (xml_node node = first_child(); node; node = node.next_sibling())
 				if (pred(node))
 					return node;
-        
-	        return xml_node();
+		
+			return xml_node();
 		}
 
 		// Find node from subtree using predicate. Returns first node from subtree (depth-first), for which predicate returned true.
@@ -553,11 +566,16 @@
 		attribute_iterator attributes_begin() const;
 		attribute_iterator attributes_end() const;
 
+		// Range-based for support
+		xml_object_range<xml_node_iterator> children() const;
+		xml_object_range<xml_named_node_iterator> children(const char_t* name) const;
+		xml_object_range<xml_attribute_iterator> attributes() const;
+
 		// Get node offset in parsed file/string (in char_t units) for debugging purposes
 		ptrdiff_t offset_debug() const;
 
-        // Get hash value (unique for handles to the same object)
-        size_t hash_value() const;
+		// Get hash value (unique for handles to the same object)
+		size_t hash_value() const;
 
 		// Get internal pointer
 		xml_node_struct* internal_object() const;
@@ -569,13 +587,81 @@
 	bool PUGIXML_FUNCTION operator||(const xml_node& lhs, bool rhs);
 #endif
 
+	// A helper for working with text inside PCDATA nodes
+	class PUGIXML_CLASS xml_text
+	{
+		friend class xml_node;
+
+		xml_node_struct* _root;
+
+		typedef void (*unspecified_bool_type)(xml_text***);
+
+		explicit xml_text(xml_node_struct* root);
+
+		xml_node_struct* _data_new();
+		xml_node_struct* _data() const;
+
+	public:
+		// Default constructor. Constructs an empty object.
+		xml_text();
+
+		// Safe bool conversion operator
+		operator unspecified_bool_type() const;
+
+		// Borland C++ workaround
+		bool operator!() const;
+
+		// Check if text object is empty
+		bool empty() const;
+
+		// Get text, or "" if object is empty
+		const char_t* get() const;
+
+		// Get text, or the default value if object is empty
+		const char_t* as_string(const char_t* def = PUGIXML_TEXT("")) const;
+
+		// Get text as a number, or the default value if conversion did not succeed or object is empty
+		int as_int(int def = 0) const;
+		unsigned int as_uint(unsigned int def = 0) const;
+		double as_double(double def = 0) const;
+		float as_float(float def = 0) const;
+
+		// Get text as bool (returns true if first character is in '1tTyY' set), or the default value if object is empty
+		bool as_bool(bool def = false) const;
+
+		// Set text (returns false if object is empty or there is not enough memory)
+		bool set(const char_t* rhs);
+
+		// Set text with type conversion (numbers are converted to strings, boolean is converted to "true"/"false")
+		bool set(int rhs);
+		bool set(unsigned int rhs);
+		bool set(double rhs);
+		bool set(bool rhs);
+
+		// Set text (equivalent to set without error checking)
+		xml_text& operator=(const char_t* rhs);
+		xml_text& operator=(int rhs);
+		xml_text& operator=(unsigned int rhs);
+		xml_text& operator=(double rhs);
+		xml_text& operator=(bool rhs);
+
+		// Get the data node (node_pcdata or node_cdata) for this object
+		xml_node data() const;
+	};
+
+#ifdef __BORLANDC__
+	// Borland C++ workaround
+	bool PUGIXML_FUNCTION operator&&(const xml_text& lhs, bool rhs);
+	bool PUGIXML_FUNCTION operator||(const xml_text& lhs, bool rhs);
+#endif
+
 	// Child node iterator (a bidirectional iterator over a collection of xml_node)
 	class PUGIXML_CLASS xml_node_iterator
 	{
 		friend class xml_node;
 
 	private:
-		xml_node _wrap;
+		mutable xml_node _wrap;
 		xml_node _parent;
 
 		xml_node_iterator(xml_node_struct* ref, xml_node_struct* parent);
@@ -591,18 +677,18 @@
 		typedef std::bidirectional_iterator_tag iterator_category;
 	#endif
 
-        // Default constructor
+		// Default constructor
 		xml_node_iterator();
 
-        // Construct an iterator which points to the specified node
+		// Construct an iterator which points to the specified node
 		xml_node_iterator(const xml_node& node);
 
-        // Iterator operators
+		// Iterator operators
 		bool operator==(const xml_node_iterator& rhs) const;
 		bool operator!=(const xml_node_iterator& rhs) const;
 
-		xml_node& operator*();
-		xml_node* operator->();
+		xml_node& operator*() const;
+		xml_node* operator->() const;
 
 		const xml_node_iterator& operator++();
 		xml_node_iterator operator++(int);
@@ -617,7 +703,7 @@
 		friend class xml_node;
 
 	private:
-		xml_attribute _wrap;
+		mutable xml_attribute _wrap;
 		xml_node _parent;
 
 		xml_attribute_iterator(xml_attribute_struct* ref, xml_node_struct* parent);
@@ -633,18 +719,18 @@
 		typedef std::bidirectional_iterator_tag iterator_category;
 	#endif
 
-        // Default constructor
+		// Default constructor
 		xml_attribute_iterator();
 
-        // Construct an iterator which points to the specified attribute
+		// Construct an iterator which points to the specified attribute
 		xml_attribute_iterator(const xml_attribute& attr, const xml_node& parent);
 
 		// Iterator operators
 		bool operator==(const xml_attribute_iterator& rhs) const;
 		bool operator!=(const xml_attribute_iterator& rhs) const;
 
-		xml_attribute& operator*();
-		xml_attribute* operator->();
+		xml_attribute& operator*() const;
+		xml_attribute* operator->() const;
 
 		const xml_attribute_iterator& operator++();
 		xml_attribute_iterator operator++(int);
@@ -653,6 +739,41 @@
 		xml_attribute_iterator operator--(int);
 	};
 
+	// Named node range helper
+	class xml_named_node_iterator
+	{
+	public:
+		// Iterator traits
+		typedef ptrdiff_t difference_type;
+		typedef xml_node value_type;
+		typedef xml_node* pointer;
+		typedef xml_node& reference;
+
+	#ifndef PUGIXML_NO_STL
+		typedef std::forward_iterator_tag iterator_category;
+	#endif
+
+		// Default constructor
+		xml_named_node_iterator();
+
+		// Construct an iterator which points to the specified node
+		xml_named_node_iterator(const xml_node& node, const char_t* name);
+
+		// Iterator operators
+		bool operator==(const xml_named_node_iterator& rhs) const;
+		bool operator!=(const xml_named_node_iterator& rhs) const;
+
+		xml_node& operator*() const;
+		xml_node* operator->() const;
+
+		const xml_named_node_iterator& operator++();
+		xml_named_node_iterator operator++(int);
+
+	private:
+		mutable xml_node _node;
+		const char_t* _name;
+	};
+
 	// Abstract tree walker class (see xml_node::traverse)
 	class PUGIXML_CLASS xml_tree_walker
 	{
@@ -682,23 +803,23 @@
 	// Parsing status, returned as part of xml_parse_result object
 	enum xml_parse_status
 	{
-		status_ok = 0,              // No error
+		status_ok = 0,				// No error
 
-		status_file_not_found,      // File was not found during load_file()
-		status_io_error,            // Error reading from file/stream
-		status_out_of_memory,       // Could not allocate memory
-		status_internal_error,      // Internal error occurred
+		status_file_not_found,		// File was not found during load_file()
+		status_io_error,			// Error reading from file/stream
+		status_out_of_memory,		// Could not allocate memory
+		status_internal_error,		// Internal error occurred
 
-		status_unrecognized_tag,    // Parser could not determine tag type
+		status_unrecognized_tag,	// Parser could not determine tag type
 
-		status_bad_pi,              // Parsing error occurred while parsing document declaration/processing instruction
-		status_bad_comment,         // Parsing error occurred while parsing comment
-		status_bad_cdata,           // Parsing error occurred while parsing CDATA section
-		status_bad_doctype,         // Parsing error occurred while parsing document type declaration
-		status_bad_pcdata,          // Parsing error occurred while parsing PCDATA section
-		status_bad_start_element,   // Parsing error occurred while parsing start element tag
-		status_bad_attribute,       // Parsing error occurred while parsing element attribute
-		status_bad_end_element,     // Parsing error occurred while parsing end element tag
+		status_bad_pi,				// Parsing error occurred while parsing document declaration/processing instruction
+		status_bad_comment,			// Parsing error occurred while parsing comment
+		status_bad_cdata,			// Parsing error occurred while parsing CDATA section
+		status_bad_doctype,			// Parsing error occurred while parsing document type declaration
+		status_bad_pcdata,			// Parsing error occurred while parsing PCDATA section
+		status_bad_start_element,	// Parsing error occurred while parsing start element tag
+		status_bad_attribute,		// Parsing error occurred while parsing element attribute
+		status_bad_end_element,		// Parsing error occurred while parsing end element tag
 		status_end_element_mismatch // There was a mismatch of start-end tags (closing tag had incorrect name, some tag was not closed or there was an excessive closing tag)
 	};
 
@@ -714,7 +835,7 @@
 		// Source document encoding
 		xml_encoding encoding;
 
-        // Default constructor, initializes object to failed state
+		// Default constructor, initializes object to failed state
 		xml_parse_result();
 
 		// Cast to bool operator
@@ -748,10 +869,10 @@
 		// Destructor, invalidates all node/attribute handles to this document
 		~xml_document();
 
-        // Removes all nodes, leaving the empty document
+		// Removes all nodes, leaving the empty document
 		void reset();
 
-        // Removes all nodes, then copies the entire contents of the specified document
+		// Removes all nodes, then copies the entire contents of the specified document
 		void reset(const xml_document& proto);
 
 	#ifndef PUGIXML_NO_STL
@@ -771,11 +892,11 @@
 		xml_parse_result load_buffer(const void* contents, size_t size, unsigned int options = parse_default, xml_encoding encoding = encoding_auto);
 
 		// Load document from buffer, using the buffer for in-place parsing (the buffer is modified and used for storage of document data).
-        // You should ensure that buffer data will persist throughout the document's lifetime, and free the buffer memory manually once document is destroyed.
+		// You should ensure that buffer data will persist throughout the document's lifetime, and free the buffer memory manually once document is destroyed.
 		xml_parse_result load_buffer_inplace(void* contents, size_t size, unsigned int options = parse_default, xml_encoding encoding = encoding_auto);
 
 		// Load document from buffer, using the buffer for in-place parsing (the buffer is modified and used for storage of document data).
-        // You should allocate the buffer with pugixml allocation function; document will free the buffer when it is no longer needed (you can't use it anymore).
+		// You should allocate the buffer with pugixml allocation function; document will free the buffer when it is no longer needed (you can't use it anymore).
 		xml_parse_result load_buffer_inplace_own(void* contents, size_t size, unsigned int options = parse_default, xml_encoding encoding = encoding_auto);
 
 		// Save XML document to writer (semantics is slightly different from xml_node::print, see documentation for details).
@@ -791,22 +912,22 @@
 		bool save_file(const char* path, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, xml_encoding encoding = encoding_auto) const;
 		bool save_file(const wchar_t* path, const char_t* indent = PUGIXML_TEXT("\t"), unsigned int flags = format_default, xml_encoding encoding = encoding_auto) const;
 
-        // Get document element
-        xml_node document_element() const;
+		// Get document element
+		xml_node document_element() const;
 	};
 
 #ifndef PUGIXML_NO_XPATH
 	// XPath query return type
 	enum xpath_value_type
 	{
-		xpath_type_none,      // Unknown type (query failed to compile)
+		xpath_type_none,	  // Unknown type (query failed to compile)
 		xpath_type_node_set,  // Node set (xpath_node_set)
-		xpath_type_number,    // Number
-		xpath_type_string,    // String
-		xpath_type_boolean    // Boolean
+		xpath_type_number,	  // Number
+		xpath_type_string,	  // String
+		xpath_type_boolean	  // Boolean
 	};
 
-    // XPath parsing result
+	// XPath parsing result
 	struct PUGIXML_CLASS xpath_parse_result
 	{
 		// Error message (0 if no error)
@@ -815,7 +936,7 @@
 		// Last parsed offset (in char_t units from string start)
 		ptrdiff_t offset;
 
-        // Default constructor, initializes object to failed state
+		// Default constructor, initializes object to failed state
 		xpath_parse_result();
 
 		// Cast to bool operator
@@ -841,19 +962,19 @@
 		xpath_variable& operator=(const xpath_variable&);
 		
 	public:
-        // Get variable name
+		// Get variable name
 		const char_t* name() const;
 
-        // Get variable type
+		// Get variable type
 		xpath_value_type type() const;
 
-        // Get variable value; no type conversion is performed, default value (false, NaN, empty string, empty node set) is returned on type mismatch error
+		// Get variable value; no type conversion is performed, default value (false, NaN, empty string, empty node set) is returned on type mismatch error
 		bool get_boolean() const;
 		double get_number() const;
 		const char_t* get_string() const;
 		const xpath_node_set& get_node_set() const;
 
-        // Set variable value; no type conversion is performed, false is returned on type mismatch error
+		// Set variable value; no type conversion is performed, false is returned on type mismatch error
 		bool set(bool value);
 		bool set(double value);
 		bool set(const char_t* value);
@@ -873,20 +994,20 @@
 		xpath_variable* find(const char_t* name) const;
 
 	public:
-        // Default constructor/destructor
+		// Default constructor/destructor
 		xpath_variable_set();
 		~xpath_variable_set();
 
-        // Add a new variable or get the existing one, if the types match
+		// Add a new variable or get the existing one, if the types match
 		xpath_variable* add(const char_t* name, xpath_value_type type);
 
-        // Set value of an existing variable; no type conversion is performed, false is returned if there is no such variable or if types mismatch
+		// Set value of an existing variable; no type conversion is performed, false is returned if there is no such variable or if types mismatch
 		bool set(const char_t* name, bool value);
 		bool set(const char_t* name, double value);
 		bool set(const char_t* name, const char_t* value);
 		bool set(const char_t* name, const xpath_node_set& value);
 
-        // Get existing variable by name
+		// Get existing variable by name
 		xpath_variable* get(const char_t* name);
 		const xpath_variable* get(const char_t* name) const;
 	};
@@ -898,15 +1019,15 @@
 		void* _impl;
 		xpath_parse_result _result;
 
-    	typedef void* xpath_query::*unspecified_bool_type;
+		typedef void (*unspecified_bool_type)(xpath_query***);
 
 		// Non-copyable semantics
 		xpath_query(const xpath_query&);
 		xpath_query& operator=(const xpath_query&);
 
 	public:
-        // Construct a compiled object from XPath expression.
-        // If PUGIXML_NO_EXCEPTIONS is not defined, throws xpath_exception on compilation errors.
+		// Construct a compiled object from XPath expression.
+		// If PUGIXML_NO_EXCEPTIONS is not defined, throws xpath_exception on compilation errors.
 		explicit xpath_query(const char_t* query, xpath_variable_set* variables = 0);
 
 		// Destructor
@@ -916,28 +1037,28 @@
 		xpath_value_type return_type() const;
 		
 		// Evaluate expression as boolean value in the specified context; performs type conversion if necessary.
-        // If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
+		// If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
 		bool evaluate_boolean(const xpath_node& n) const;
 		
 		// Evaluate expression as double value in the specified context; performs type conversion if necessary.
-        // If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
+		// If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
 		double evaluate_number(const xpath_node& n) const;
 		
 	#ifndef PUGIXML_NO_STL
 		// Evaluate expression as string value in the specified context; performs type conversion if necessary.
-        // If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
+		// If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
 		string_t evaluate_string(const xpath_node& n) const;
 	#endif
 		
 		// Evaluate expression as string value in the specified context; performs type conversion if necessary.
-        // At most capacity characters are written to the destination buffer, full result size is returned (includes terminating zero).
-        // If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
-        // If PUGIXML_NO_EXCEPTIONS is defined, returns empty  set instead.
+		// At most capacity characters are written to the destination buffer, full result size is returned (includes terminating zero).
+		// If PUGIXML_NO_EXCEPTIONS is not defined, throws std::bad_alloc on out of memory errors.
+		// If PUGIXML_NO_EXCEPTIONS is defined, returns empty  set instead.
 		size_t evaluate_string(char_t* buffer, size_t capacity, const xpath_node& n) const;
 
 		// Evaluate expression as node set in the specified context.
-        // If PUGIXML_NO_EXCEPTIONS is not defined, throws xpath_exception on type mismatch and std::bad_alloc on out of memory errors.
-        // If PUGIXML_NO_EXCEPTIONS is defined, returns empty node set instead.
+		// If PUGIXML_NO_EXCEPTIONS is not defined, throws xpath_exception on type mismatch and std::bad_alloc on out of memory errors.
+		// If PUGIXML_NO_EXCEPTIONS is defined, returns empty node set instead.
 		xpath_node_set evaluate_node_set(const xpath_node& n) const;
 
 		// Get parsing result (used to get compilation errors in PUGIXML_NO_EXCEPTIONS mode)
@@ -946,7 +1067,7 @@
 		// Safe bool conversion operator
 		operator unspecified_bool_type() const;
 
-    	// Borland C++ workaround
+		// Borland C++ workaround
 		bool operator!() const;
 	};
 	
@@ -964,7 +1085,7 @@
 		// Get error message
 		virtual const char* what() const throw();
 
-        // Get parse result
+		// Get parse result
 		const xpath_parse_result& result() const;
 	};
 	#endif
@@ -976,7 +1097,7 @@
 		xml_node _node;
 		xml_attribute _attribute;
 	
-    	typedef xml_node xpath_node::*unspecified_bool_type;
+		typedef void (*unspecified_bool_type)(xpath_node***);
 
 	public:
 		// Default constructor; constructs empty XPath node
@@ -993,11 +1114,11 @@
 		// Get parent of contained node/attribute
 		xml_node parent() const;
 
-    	// Safe bool conversion operator
+		// Safe bool conversion operator
 		operator unspecified_bool_type() const;
 		
-    	// Borland C++ workaround
-    	bool operator!() const;
+		// Borland C++ workaround
+		bool operator!() const;
 
 		// Comparison operators
 		bool operator==(const xpath_node& n) const;
@@ -1044,7 +1165,7 @@
 		// Get collection size
 		size_t size() const;
 
-        // Indexing operator
+		// Indexing operator
 		const xpath_node& operator[](size_t index) const;
 		
 		// Collection iterators
@@ -1059,7 +1180,7 @@
 		
 		// Check if collection is empty
 		bool empty() const;
-    
+	
 	private:
 		type_t _type;
 		
@@ -1086,28 +1207,23 @@
 	typedef void* (*allocation_function)(size_t size);
 	
 	// Memory deallocation function interface
-    typedef void (*deallocation_function)(void* ptr);
-
-    // Override default memory management functions. All subsequent allocations/deallocations will be performed via supplied functions.
-    void PUGIXML_FUNCTION set_memory_management_functions(allocation_function allocate, deallocation_function deallocate);
-    
-    // Get current memory management functions
-    allocation_function PUGIXML_FUNCTION get_memory_allocation_function();
-    deallocation_function PUGIXML_FUNCTION get_memory_deallocation_function();
-}
-
-
+	typedef void (*deallocation_function)(void* ptr);
 
-// Added by LG for OpenImageIO:
+	// Override default memory management functions. All subsequent allocations/deallocations will be performed via supplied functions.
+	void PUGIXML_FUNCTION set_memory_management_functions(allocation_function allocate, deallocation_function deallocate);
+	
+	// Get current memory management functions
+	allocation_function PUGIXML_FUNCTION get_memory_allocation_function();
+	deallocation_function PUGIXML_FUNCTION get_memory_deallocation_function();
 }
-OIIO_NAMESPACE_EXIT
 
-#if !defined(PUGIXML_NO_STL) && ((defined(_MSC_VER) && _MSC_VER < 1400) || defined(__ICC))
+#if !defined(PUGIXML_NO_STL) && (defined(_MSC_VER) || defined(__ICC))
 namespace std
 {
 	// Workarounds for (non-standard) iterator category detection for older versions (MSVC7/IC8 and earlier)
-	std::bidirectional_iterator_tag PUGIXML_FUNCTION _Iter_cat(const OpenImageIO::pugi::xml_node_iterator&);
-	std::bidirectional_iterator_tag PUGIXML_FUNCTION _Iter_cat(const OpenImageIO::pugi::xml_attribute_iterator&);
+	std::bidirectional_iterator_tag PUGIXML_FUNCTION _Iter_cat(const pugi::xml_node_iterator&);
+	std::bidirectional_iterator_tag PUGIXML_FUNCTION _Iter_cat(const pugi::xml_attribute_iterator&);
+	std::forward_iterator_tag PUGIXML_FUNCTION _Iter_cat(const pugi::xml_named_node_iterator&);
 }
 #endif
 
@@ -1115,15 +1231,16 @@
 namespace std
 {
 	// Workarounds for (non-standard) iterator category detection
-	std::bidirectional_iterator_tag PUGIXML_FUNCTION __iterator_category(const OpenImageIO::pugi::xml_node_iterator&);
-	std::bidirectional_iterator_tag PUGIXML_FUNCTION __iterator_category(const OpenImageIO::pugi::xml_attribute_iterator&);
+	std::bidirectional_iterator_tag PUGIXML_FUNCTION __iterator_category(const pugi::xml_node_iterator&);
+	std::bidirectional_iterator_tag PUGIXML_FUNCTION __iterator_category(const pugi::xml_attribute_iterator&);
+	std::forward_iterator_tag PUGIXML_FUNCTION __iterator_category(const pugi::xml_named_node_iterator&);
 }
 #endif
 
 #endif
 
 /**
- * Copyright (c) 2006-2010 Arseny Kapoulkine
+ * Copyright (c) 2006-2012 Arseny Kapoulkine
  *
  * Permission is hereby granted, free of charge, to any person
  * obtaining a copy of this software and associated documentation
