#ifndef _SINGLY_LINKED_LIST_
#define _SINGLY_LINKED_LIST_

typedef enum {
  _INIT_ELEM,
  _DECIMAL_ELEM,
  _REAL_ELEM,
  _STRING_ELEM
} value_type_list_t;

typedef union {
  int64_t decimal;
  double real;
  uint8_t* string;
} value_list_t;

typedef struct List {
  value_type_list_t type;
  value_list_t value;
  struct List* next;
} List;

/*
 * d - decimal
 * r - real
 * s - string
 *
 * List* list = new_list("drs", 32, 3.42, "hello world");
*/

extern List* new_list(uint8_t* format, ...);
extern void free_list(List* list);

extern List* push_list(List* list, uint8_t* format, ...);
extern List* pop_list(List* list);

extern void print_list(List* list);

extern List* delete_by_id_list(List* list, const size_t index);
extern List* add_by_id(List* list, const size_t index, uint8_t* format, ...);
extern _Bool exists_list(List* list, uint8_t* format, ...);

#endif
