#include <kernel/arch/i686/global_constructors.h>

func_ptr _init_array_start[0] __attribute__ ((used, section(".init_array"), aligned(sizeof(func_ptr)))) = { };
func_ptr _fini_array_start[0] __attribute__ ((used, section(".fini_array"), aligned(sizeof(func_ptr)))) = { };

func_ptr _init_array_end[0] __attribute__ ((used, section(".init_array"), aligned(sizeof(func_ptr)))) = { };
func_ptr _fini_array_end[0] __attribute__ ((used, section(".fini_array"), aligned(sizeof(func_ptr)))) = { };

void CallGlobalConstructors(void)
{
    for(func_ptr* func = _init_array_start; func != _init_array_end; func++) {
        (*func)();
    }
}

void CallGlobalDestructors(void)
{
    for(func_ptr* func = _fini_array_start; func != _fini_array_end; func++) {
        (*func)();
    }
}