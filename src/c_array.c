/** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
 *  This file is part of cstl library
 *  Copyright (C) 2011 Avinash Dongre ( dongre.avinash@gmail.com )
 *  Copyright (C) 2018 ssrlive ( ssrlivebox@gmail.com )
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **/

#include "c_lib.h"
#include <string.h>
#include <stdio.h>

static struct cstl_array*
cstl_array_check_and_grow(struct cstl_array* pArray) {
    if (pArray->count >= pArray->capacity) {
        size_t size;
        pArray->capacity = 2 * pArray->capacity;
        size = pArray->capacity * sizeof(struct cstl_object*);
        pArray->pElements = (struct cstl_object**) realloc(pArray->pElements, size);
    }
    return pArray;
}

struct cstl_array*
cstl_array_new(int array_size, cstl_compare fn_c, cstl_destroy fn_d) {
    struct cstl_array* pArray = (struct cstl_array*)calloc(1, sizeof(struct cstl_array));
    if (!pArray) {
        return (struct cstl_array*)0;
    }
    pArray->capacity = array_size < 8 ? 8 : array_size;
    pArray->pElements = (struct cstl_object**) calloc(pArray->capacity, sizeof(struct cstl_object*));
    if (!pArray->pElements) {
        free(pArray);
        return (struct cstl_array*)0;
    }
    pArray->compare_fn = fn_c;
    pArray->destruct_fn = fn_d;
    pArray->count = 0;

    return pArray;
}

static cstl_error
cstl_array_insert(struct cstl_array* pArray, int index, void* elem, size_t elem_size) {
    cstl_error rc = CSTL_ERROR_SUCCESS;
    struct cstl_object* pObject = cstl_object_new(elem, elem_size);
    if (!pObject) {
        return CSTL_ARRAY_INSERT_FAILED;
    }
    pArray->pElements[index] = pObject;
    pArray->count++;
    return rc;
}

cstl_error
cstl_array_push_back(struct cstl_array* pArray, void* elem, size_t elem_size) {
    cstl_error rc = CSTL_ERROR_SUCCESS;

    if (!pArray) {
        return CSTL_ARRAY_NOT_INITIALIZED;
    }
    cstl_array_check_and_grow(pArray);

    rc = cstl_array_insert(pArray, pArray->count, elem, elem_size);

    return rc;
}

const void *
cstl_array_element_at(struct cstl_array* pArray, int index) {
    if (!pArray) {
        return NULL;
    }
    if (index < 0 || index > pArray->capacity) {
        return NULL;
    }
    return cstl_object_get_data(pArray->pElements[index]);
}

int
cstl_array_size(struct cstl_array* pArray) {
    if (pArray == (struct cstl_array*)0) {
        return 0;
    }
    return pArray->count;
}

int
cstl_array_capacity(struct cstl_array* pArray) {
    if (pArray == (struct cstl_array*)0) {
        return 0;
    }
    return pArray->capacity;
}

cstl_bool
cstl_array_empty(struct cstl_array* pArray) {
    if (pArray == (struct cstl_array*)0) {
        return 0;
    }
    return pArray->count == 0 ? cstl_true : cstl_false;
}

cstl_error
cstl_array_reserve(struct cstl_array* pArray, int new_size) {
    if (pArray == (struct cstl_array*)0) {
        return CSTL_ARRAY_NOT_INITIALIZED;
    }
    if (new_size <= pArray->capacity) {
        return CSTL_ERROR_SUCCESS;
    }
    cstl_array_check_and_grow(pArray);
    return CSTL_ERROR_SUCCESS;
}

const void *
cstl_array_front(struct cstl_array* pArray) {
    return cstl_array_element_at(pArray, 0);
}

const void *
cstl_array_back(struct cstl_array* pArray) {
    return cstl_array_element_at(pArray, pArray->count - 1);
}

cstl_error
cstl_array_insert_at(struct cstl_array* pArray, int index, void* elem, size_t elem_size) {
    cstl_error rc = CSTL_ERROR_SUCCESS;
    if (!pArray) {
        return CSTL_ARRAY_NOT_INITIALIZED;
    }
    if (index < 0 || index > pArray->capacity) {
        return CSTL_ARRAY_INDEX_OUT_OF_BOUND;
    }
    cstl_array_check_and_grow(pArray);

    memmove(&(pArray->pElements[index + 1]),
            &pArray->pElements[index],
            (pArray->count - index) * sizeof(struct cstl_object*));

    rc = cstl_array_insert(pArray, index, elem, elem_size);

    return rc;
}

cstl_error
cstl_array_remove_from(struct cstl_array* pArray, int index) {
    cstl_error   rc = CSTL_ERROR_SUCCESS;

    if (!pArray) {
        return rc;
    }
    if (index < 0 || index > pArray->capacity) {
        return CSTL_ARRAY_INDEX_OUT_OF_BOUND;
    }
    if (pArray->destruct_fn) {
        void *elem = (void *) cstl_array_element_at(pArray, index);
        if (elem) {
            pArray->destruct_fn(elem);
        }
    }
    cstl_object_delete(pArray->pElements[index]);

    memmove(&(pArray->pElements[index]),
            &pArray->pElements[index + 1],
            (pArray->count - index) * sizeof(struct cstl_object*));
    pArray->count--;

    return rc;
}

cstl_error
cstl_array_delete(struct cstl_array* pArray) {
    cstl_error rc = CSTL_ERROR_SUCCESS;
    int i = 0;

    if (pArray == (struct cstl_array*)0) {
        return CSTL_ARRAY_NOT_INITIALIZED;
    }
    if (pArray->destruct_fn) {
        for (i = 0; i < pArray->count; i++) {
            void *elem = (void *) cstl_array_element_at(pArray, i);
            if ( elem ) {
                pArray->destruct_fn(elem);
            }
        }
    }

    for (i = 0; i < pArray->count; i++) {
        cstl_object_delete(pArray->pElements[i]);
    }
    free(pArray->pElements);
    free(pArray);
    return rc;
}

static struct cstl_object*
cstl_array_get_next(struct cstl_iterator* pIterator) {
    struct cstl_array *pArray = (struct cstl_array*)pIterator->pContainer;
    if (pIterator->pCurrent >= cstl_array_size(pArray)) {
        return (struct cstl_object*)0;
    }
    pIterator->pCurrentElement = pArray->pElements[pIterator->pCurrent++];
    return (struct cstl_object *)pIterator->pCurrentElement;
}

static const void*
cstl_array_get_value(void* pObject) {
    return cstl_object_get_data((struct cstl_object *)pObject);
}

static void
cstl_array_replace_value(struct cstl_iterator *pIterator, void* elem, size_t elem_size) {
    struct cstl_array*  pArray = (struct cstl_array*)pIterator->pContainer;
    struct cstl_object *currentElement = (struct cstl_object *)pIterator->pCurrentElement;
    if (pArray->destruct_fn) {
        void *old_element = (void *) cstl_object_get_data(currentElement);
        if (old_element) {
            pArray->destruct_fn(old_element);
        }
    }
    cstl_object_replace_raw(currentElement, elem, elem_size);
}

struct cstl_iterator*
cstl_array_new_iterator(struct cstl_array* pArray) {
    struct cstl_iterator *itr = (struct cstl_iterator*) calloc(1, sizeof(struct cstl_iterator));
    itr->get_next = cstl_array_get_next;
    itr->get_value = cstl_array_get_value;
    itr->replace_value = cstl_array_replace_value;
    itr->pContainer = pArray;
    itr->pCurrent = 0;
    return itr;
}

void
cstl_array_delete_iterator(struct cstl_iterator* pItr) {
    free(pItr);
}
