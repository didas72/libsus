#ifndef SUS_ILLIST_H_
#define SUS_ILLIST_H_

#include "versioning.h"

#include <stddef.h>

typedef struct illist_t illist_t;
typedef struct illist_entry_t illist_entry_t;

illist_t *illist_create(size_t element_size);
int illist_destroy();
illist_t *illist_duplicate(illist_t *ll);

int illist_push_front(illist_t *ll, void *content);
int illist_push_back(illist_t *ll, void *content);
int illist_pop_front(illist_t *ll);
int illist_pop_back(illist_t *ll);
int illist_clear(illist_t *ll);

size_t illist_get_count(illist_t *ll);

illist_entry_t *illist_begin(illist_t *ll);
illist_entry_t *illist_end(illist_t *ll);
illist_entry_t *illist_rbegin(illist_t *ll);
illist_entry_t *illist_rend(illist_t *ll);

//Head and tail getting without iterator?

void *illist_get(illist_entry_t *entry);
int illist_fetch(illist_entry_t *entry, void *store);
int illist_next(illist_entry_t **entry);
int illist_prev(illist_entry_t **entry);
int illist_pop(illist_t *ll, illist_entry_t **entry); //Pop and advance/rewind/invalidate?
int illist_append(illist_t *ll, illist_entry_t *entry, void *content);
int illist_prepend(illist_t *ll, illist_entry_t *entry, void *content); //Needed? Just prev and append

#endif
