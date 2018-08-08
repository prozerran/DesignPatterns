
#ifndef __DESIGN_PATTERN_H__
#define __DESIGN_PATTERN_H__

#ifdef _WIN32
#include "Windows.h"
#endif

// More Design Patterns in ...
// http://calumgrant.net/patterns/
// http://www.ccplusplus.com/2011/07/design-pattern-guide-with-example-and.html
// http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns


#if (_MSC_VER >= 1800)		// Visual Studio 2013
#include <mutex>
#include <stdexcept>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <list>
#include <map>

#else

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <list>
#include <map>

#endif

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName() {}; \
	TypeName(const TypeName& _s) {}; \
	TypeName& operator=(const TypeName& _s) {};

#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(arr) (sizeof(arr)/sizeof(*arr))
#endif

#define FOR_EACH(_t_, _v_,_l_) for each(_t_ _v_ in _l_)

#endif