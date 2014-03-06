/* -*- C -*- */
#ifndef _list_H
#define _list_H

typedef struct ListElem ListElem;
typedef struct List List;

struct ListElem {
  void *m_data;
  ListElem *m_next;
};

struct List {
  ListElem *m_head;
  ListElem *m_tail;
};

extern List *newList();
extern void initList(List *);
extern void destroyList(List *p, void *userData, void (*destroyData)(void *userData, void *data));
extern void ListAppend(List *p, void *data);
extern void ListPrepend(List *p, void *data);
extern unsigned int ListLength(List *p);
extern void ListUnlinkItem(List *p, void *data);
extern void ListUnlinkElem(List *p, ListElem *elem);
extern void ListInsertAfter(ListElem *p, void *data);

typedef void (*ForEachItemFunction)(void *userData, void *elemData);
extern void forEach(List *p, void *userData, ForEachItemFunction applyFunc);

extern void *ListRemoveHead(List *p);
extern void *ListRemoveTail(List *p);

#endif
