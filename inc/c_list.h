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

#ifndef _CSTL_LIST_H_
#define _CSTL_LIST_H_

struct cstl_list_node {
    struct cstl_object* elem;
    struct cstl_list_node *next;
};

struct cstl_list {
    struct cstl_list_node* head;
    cstl_destroy destruct_fn;
    cstl_compare compare_key_fn;
    int size;
};

extern struct cstl_list * cstl_list_new (cstl_destroy fn_d, cstl_compare fn_c);
extern void           cstl_list_delete   (struct cstl_list* pList);
extern cstl_error     cstl_list_insert   (struct cstl_list* pList, int pos, void* elem, size_t elem_size);
extern cstl_error     cstl_list_push_back(struct cstl_list* pList, void* elem, size_t elem_size);
extern void           cstl_list_remove   (struct cstl_list* pList, int pos);
extern void cstl_list_for_each(struct cstl_list* pList, void(*fn)(const void *elem, void *p), void *p);
extern const void *   cstl_list_find(struct cstl_list* pList, void* find_value);
extern const void *   cstl_list_element_at(struct cstl_list* pList, int pos);
extern size_t  cstl_list_size(struct cstl_list* pList);

extern struct cstl_iterator* cstl_list_new_iterator(struct cstl_list* pSlit);
extern void cstl_list_delete_iterator ( struct cstl_iterator* pItr);

#endif