#pragma once

#pragma once

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define ENABLE_CRT_DEBUG() \
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define ENABLE_CRT_DEBUG() ((void)0)
#endif
