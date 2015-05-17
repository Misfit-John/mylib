#ifndef JZMARCOFUNC_H
#define JZMARCOFUNC_H

#include "JZLogger.h"

#define JZSAFE_DELETE(ptr) {if(ptr != NULL){delete ptr;}}
#define JZIF_NULL_RETURN(ptr, args...) {if(NULL == ptr){JZWRITE_ERROR("%s",#ptr" is NULL ! Now return.");return args;}}

#endif /* end of include guard: JZMARCOFUNC_H */
