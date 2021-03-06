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

#ifndef _C_SET_H_
#define _C_SET_H_

struct cstl_set {
    struct cstl_rb* root;
};

extern struct cstl_set* cstl_set_new( cstl_compare fn_c, cstl_destroy fn_d);
extern cstl_error   cstl_set_insert ( struct cstl_set* pSet, void* key, size_t key_size);
extern cstl_bool    cstl_set_exists ( struct cstl_set* pSet, void* key);
extern cstl_error   cstl_set_remove ( struct cstl_set* pSet, void* key);
extern cstl_bool    cstl_set_find   ( struct cstl_set* pSet, void* key, const void **outKey);
extern cstl_error   cstl_set_delete ( struct cstl_set* pSet);

extern struct cstl_iterator* cstl_set_new_iterator(struct cstl_set* pSet);
extern void cstl_set_delete_iterator ( struct cstl_iterator* pItr);

#endif
