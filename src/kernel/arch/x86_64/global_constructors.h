#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*func_ptr)(void);

extern func_ptr _init_array_start[0], _init_array_end[0];
extern func_ptr _fini_array_start[0], _fini_array_end[0];

void CallGlobalConstructors(void);
void CallGlobalDestructors(void);

#ifdef __cplusplus
}
#endif