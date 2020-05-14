#ifndef CLIBRARY_H_
#define CLIBRARY_H_
typedef int (*callback_fcn)(int);
void some_c_func(callback_fcn);
#endif