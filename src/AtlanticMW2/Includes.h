#ifndef __INCLUDES_H__
#define __INCLUDES_H__

// Standard C libraries
#include <limits.h>
#include <math.h>
#include <time.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

// PS3 specific libraries
#include <sys/prx.h>
#include <sys/syscall.h>
#include <sys/ppu_thread.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/types.h>
#include <fastmath.h>
#include <cellstatus.h>
#include <cell/sysmodule.h>
#include <sys/random_number.h>
#include <ppu_intrinsics.h>
#include <sysutil/sysutil_msgdialog.h>
#include <sysutil/sysutil_oskdialog.h>
#include <sysutil/sysutil_oskdialog_ext.h>
#include <sysutil/sysutil_sysparam.h>

// Custom headers
#include "cstring.h"
#include "Memory.h"
#include "vector.h"
#include "string.h"
#include "g_scr.h"
#include "client.h"
#include "entity.h"
#include "g_hudelem.h"
#include "dvar.h"
#include "q_math.h"
#include "g_scr_mp.h"
#include "sockets.h"
#include "notifyInvoker.h"
#include "threads.h"
#include "Functions.h"
#include "handle.h"
#include "level.h"
#include "fieldInvoker.h"
#include "GameScriptFunctions.h"
#include "handleFunctions.h"
#include "bots_mp.h"
#include "keyboard.h"
#include "pFunctions.h"
#include "pMenu.h"
#include "menu.h"

// Custom memory management operators
inline void* operator new[](size_t count) {
    return malloc(count);
    }

    inline void* operator new(size_t count) {
        return malloc(count);
    }

    inline void operator delete[](void* ptr) {
        free(ptr);
        }

        inline void operator delete(void* ptr) {
            free(ptr);
        }

#endif /* __INCLUDES_H__ */