#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef _DEBUG
#define printd(...) printf(__VA_ARGS__)
#else
#define printd(...)
#endif

#ifdef _DEBUG
#define calld(a) a
#else
#define calld(a)
#endif

#endif /* __DEBUG_H__ */