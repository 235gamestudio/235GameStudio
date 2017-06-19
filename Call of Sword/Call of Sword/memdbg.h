#pragma once
#ifndef MEMDBG_H
#define MEMDBG_H

#ifdef _DEBUG
//memory leak detection
#include <stdlib.h>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif /* _DEBUG */

#endif /* MEMDBG_H */
