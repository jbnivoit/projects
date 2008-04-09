#include "Stack.h"

#include <stdlib.h>

void Stack_Init(Stack *s)
{
  initList(s);
}

void Stack_Destroy(Stack *s, void *userData, void (*destroyData)(void *userData, void *data))
{
  destroyList(s,userData,destroyData);
}

static void dt(void *userData, void *data) {
  void (*destroyData)(void *data) = (void (*)(void *data)) userData;
  (*destroyData)(data);
}

void Stack_destroy(Stack *s, void (*destroyData)(void *data)) {
  Stack_Destroy(s, (void *)destroyData, &dt);
}

void Stack_push(Stack *s, void *item) {
  ListPrepend(s,item);
}

unsigned int Stack_size(Stack *s)
{
  return ListLength(s);
}

void *Stack_pop(Stack *s) {
  return ListRemoveHead(s);
}

void *Stack_top(Stack *s) {
  if(s->m_head==NULL) return NULL;
  return s->m_head->m_data;
}
