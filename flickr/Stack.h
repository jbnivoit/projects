#ifndef _STACK_H
#define _STACK_H

#include "list.h"
typedef List Stack;

extern void Stack_Init(Stack *s);
extern void Stack_Destroy(Stack *s, void *userData, void (*destroyData)(void *userData, void *data));
extern void Stack_destroy(Stack *s, void (*destroyData)(void *data));

extern void Stack_push(Stack *s, void *item);
extern unsigned int Stack_size(Stack *s);
extern void *Stack_pop(Stack *s);
extern void *Stack_top(Stack *s);

#endif
