#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  _DECIMAL_ELEM,
  _REAL_ELEM,
  _STRING_ELEM
} value_type_tree_t;

typedef union {
  int64_t decimal;
  double real;
  uint8_t* string;
} value_tree_t;

typedef struct tree_node {
  struct {
    value_tree_t key;
    value_tree_t value;
  } data;
  struct tree_node* left;
  struct tree_node* right;
  struct tree_node* parent;
} tree_node;

typedef struct Tree {
  struct {
    value_type_tree_t key;
    value_type_tree_t value;
  } type;
  struct tree_node* node;
} Tree;

extern Tree* new_tree(value_type_tree_t key, value_type_tree_t value);
extern void free_tree(Tree* tree);

extern value_tree_t get_tree(Tree* tree, void* key);
extern void set_tree(Tree* tree, void* key, void* value);
extern void delete_tree(Tree* tree, void* key);
extern _Bool in_tree(Tree* tree, void* key);

extern void print_tree(Tree* tree);
extern void print_tree_as_list(Tree* tree);

extern void* decimal(int64_t x);
extern void* real(double x);
extern void* string(uint8_t* x);

static tree_node* _new_node(value_type_tree_t key_type, value_type_tree_t value_type, void* key, void* value);
static void _set_value(tree_node* node, value_type_tree_t value_type, void* value);
static void _set_key(tree_node* node, value_type_tree_t key_type, void* key);
static void _set_tree(tree_node* node, value_type_tree_t key_type, value_type_tree_t value_type, void* key, void* value);

static void _print_tree_element(tree_node* node, value_type_tree_t key_type, value_type_tree_t value_type);
static void _print_tree(tree_node* node, value_type_tree_t key_type, value_type_tree_t value_type);
static void _print_tree_as_list(tree_node* node, value_type_tree_t key_type, value_type_tree_t value_type);

static tree_node* _delete_tree_a(Tree* tree, value_type_tree_t key_type, void* key);
static tree_node* _delete_tree_b(Tree* tree, tree_node* node);
static tree_node* _delete_tree_c(tree_node* node);

static tree_node* _get_tree(tree_node* node, value_type_tree_t key_type, void* key);
static void _free_tree(tree_node* node);

int main(int count, const char** args) {
  Tree* tree = new_tree(_DECIMAL_ELEM, _STRING_ELEM);

  set_tree(tree, decimal(50), string("hello world"));
  set_tree(tree, decimal(32), string("B"));
  set_tree(tree, decimal(16), string("C"));

  value_tree_t v = get_tree(tree, decimal(50));
  printf("found node, value: %s\n", v.string);
  printf("in tree: %d\n", in_tree(tree, decimal(32)));

  print_tree_as_list(tree);
  print_tree(tree);
  free_tree(tree);
  return 0;
}

extern Tree* new_tree(value_type_tree_t key, value_type_tree_t value) {
  switch(key) {
    case _DECIMAL_ELEM: case _STRING_ELEM:
      break;
    default:
      fprintf(stderr, "%s\n", "key type not supported");
      return NULL;
  }
  switch(value) {
    case _DECIMAL_ELEM: case _REAL_ELEM: case _STRING_ELEM:
      break;
    default:
      fprintf(stderr, "%s\n", "value type not supported");
      return NULL;
  }
  Tree* tree = (Tree*)malloc(sizeof(Tree));
  tree->type.key = key;
  tree->type.value = value;
  tree->node = NULL;
  return tree;
}

extern value_tree_t get_tree(Tree* tree, void* key) {
  tree_node* node = _get_tree(tree->node, tree->type.key, key);
  if (node == NULL) {
    fprintf(stderr, "%s\n", "no such value, undefined");
    value_tree_t none;
    none.decimal = 0;
    return none;
  }
  return node->data.value;
}

extern _Bool in_tree(Tree* tree, void* key) {
  return _get_tree(tree->node, tree->type.key, key) != NULL;
}

extern void delete_tree(Tree* tree, void* key) {
  tree_node* node = _delete_tree_a(tree, tree->type.key, key);
  if (node == NULL) {
    return;
  }
  if (node->left != NULL && node->right != NULL) {
    _delete_tree_c(node);
    return;
  }
  _delete_tree_b(tree, node);
  return;
}

extern void set_tree(Tree* tree, void* key, void* value) {
  if (tree->node == NULL) {
    tree->node = _new_node(tree->type.key, tree->type.value, key, value);
    return;
  }
  _set_tree(tree->node, tree->type.key, tree->type.value, key, value);
}

extern void* decimal(int64_t x) {
  return (void*)x;
}

extern void* real(double x) {
  double* f = (double*)malloc(sizeof(double));
  *f = x;
  return (void*)f;
}

extern void* string(uint8_t* x) {
  return (void*)x;
}

extern void print_tree_as_list(Tree* tree) {
  fprintf(stdout, "%s", "[");
  _print_tree_as_list(tree->node, tree->type.key, tree->type.value);
  fprintf(stdout, "%s\n", "]");
}

extern void print_tree(Tree* tree) {
  _print_tree(tree->node, tree->type.key, tree->type.value);
  putchar('\n');
}

extern void free_tree(Tree* tree) {
  _free_tree(tree->node);
  free(tree);
}

static tree_node* _delete_tree_a(Tree* tree, value_type_tree_t key_type, void* key) {
  tree_node* node = tree->node;
  node = _get_tree(node, key_type, key);
  if (node == NULL) {
    return NULL:
  }
  if (node->left != NULL || node->right != NULL) {
    return node;
  }
  tree_node* parent = node->parent;
  if (parent == NULL) {
    tree->node = NULL;
  } else if (parent->left == node) {
    parent->left = NULL;
  } else {
    parent->right = NULL;
  }
  free(node);
  return NULL;
}

static tree_node* _get_tree(tree_node* node, value_type_tree_t key_type, void* key) {
  int condition;
  if (node == NULL) {
    return NULL;
  }
  switch (key_type) {
    case _DECIMAL_ELEM:
      if ((int64_t)key > node->data.key.decimal) {
        _get_tree(node->right, key_type, key);
      } else if ((int64_t)key < node->data.key.decimal) {
        _get_tree(node->left, key_type, key);
      }
      break;
    case _STRING_ELEM:
      condition = strcmp((uint8_t*)key, node->data.key.string);
      if (condition > 0) {
        _get_tree(node->right, key_type, key);
      } else if (condition < 0) {
        _get_tree(node->left, key_type, key);
      }
      break;
    }
  return node;
}

static void _free_tree(tree_node* node) {
  if (node == NULL) {
    return;
  }
  _free_tree(node->left);
  _free_tree(node->right);
  free(node);
}

static void _print_tree_as_list(tree_node* node, value_type_tree_t key_type, value_type_tree_t value_type) {
  if (node == NULL) {
    return;
  }
  _print_tree_as_list(node->left, key_type, value_type);
  _print_tree_element(node, key_type, value_type);
  _print_tree_as_list(node->right, key_type, value_type);
}

static void _print_tree_element(tree_node* node, value_type_tree_t key_type, value_type_tree_t value_type) {
  switch (key_type) {
    case _DECIMAL_ELEM:
      printf(" [%ld => ", node->data.key.decimal);
      switch (value_type) {
        case _DECIMAL_ELEM:
          printf("%ld] ", node->data.value.decimal);
          break;
        case _REAL_ELEM:
          printf("%lf] ", node->data.value.real);
          break;
        case _STRING_ELEM:
          printf("'%s'] ", node->data.value.string);
          break;
      }
      break;
    case _STRING_ELEM:
      printf(" [%s => ", node->data.key.string);
      switch (value_type) {
        case _DECIMAL_ELEM:
          printf("%ld] ", node->data.value.decimal);
          break;
        case _REAL_ELEM:
          printf("%lf] ", node->data.value.real);
          break;
        case _STRING_ELEM:
          printf("'%s'] ", node->data.value.string);
          break;
      }
      break;
  }
}

static void _print_tree(tree_node* node, value_type_tree_t key_type, value_type_tree_t value_type) {
  if (node == NULL) {
    printf("null\n");
    return;
  }
  putchar('(');
  _print_tree(node->left, key_type, value_type);
  _print_tree_element(node, key_type, value_type);
  _print_tree(node->right, key_type, value_type);
  putchar(')');
}

static void _set_tree(tree_node* node, value_type_tree_t key_type, value_type_tree_t value_type, void* key, void* value) {
  int condition;
  switch (key_type) {
    case _DECIMAL_ELEM:
      if ((int64_t)key > node->data.key.decimal) {
        if (node->right == NULL) {
          node->right = _new_node(key_type, value_type, key, value);
          node->right->parent = node;
        } else {
          _set_tree(node->right, key_type, value_type, key, value);
        }
      } else if ((int64_t) key < node->data.key.decimal) {
        if (node->left == NULL) {
          node->left = _new_node(key_type, value_type, key, value);
          node->left->parent = node;
        } else {
          _set_tree(node->left, key_type, value_type, key, value);
        }
      } else {
        _set_value(node, value_type, value);
      }
      break;
    case _STRING_ELEM:
      condition = strcmp((uint8_t*)key, node->data.key.string);
      if (condition > 0) {
        if (node->right == NULL) {
          node->right = _new_node(key_type, value_type, key, value);
          node->right->parent = node;
        } else {
          _set_tree(node->right, key_type, value_type, key, value);
        }
      } else if (condition < 0) {
        if (node->left == NULL) {
          node->left = _new_node(key_type, value_type, key, value);
          node->left->parent = node;
        } else {
          _set_tree(node->left, key_type, value_type, key, value);
        }
      } else {
        _set_value(node, value_type, value);
      }
      break;
  }
}

static tree_node* _new_node(value_type_tree_t key_type, value_type_tree_t value_type, void* key, void* value) {
  tree_node* node = (tree_node*)malloc(sizeof(tree_node));
  _set_key(node, key_type, key);
  _set_value(node, value_type, value);

  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  return node;
}

static void _set_key(tree_node* node, value_type_tree_t key_type, void* key) {
  switch (key_type) {
    case _DECIMAL_ELEM:
      node->data.key.decimal = (int64_t)key;
      break;
    case _STRING_ELEM:
      node->data.key.string = (uint8_t*)key;
      break;
  }
}

static void _set_value(tree_node* node, value_type_tree_t value_type, void* value) {
  switch (value_type) {
    case _DECIMAL_ELEM:
      node->data.value.decimal = (int64_t)value;
      break;
    case _REAL_ELEM:
      node->data.value.real = *(double*)value;
      free((double*)value);
      break;
    case _STRING_ELEM:
      node->data.value.string = (uint8_t*)value;
      break;
  }
}
