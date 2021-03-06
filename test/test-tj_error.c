/*
 * Copyright (c) 2013 Joe Kopena <tjkopena@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>

#include "cmocka.h"

#include "tj_error.h"

static void test_create1(void **state) {
    tj_error *err = tj_error_create(TJ_ERROR_FAILURE, "message");
    assert_non_null(err);

    assert_int_equal(tj_error_getCode(err), TJ_ERROR_FAILURE);
    assert_string_equal(tj_error_getMessage(err), "[FAILURE]: message");

    tj_error_finalize(err);
}

static void test_create2(void **state) {
    tj_error *err = tj_error_create(TJ_ERROR_FAILURE, "Foo %d Bar %d", 5, 10);
    assert_non_null(err);

    assert_int_equal(tj_error_getCode(err), TJ_ERROR_FAILURE);
    assert_string_equal(tj_error_getMessage(err), "[FAILURE]: Foo 5 Bar 10");

    tj_error_finalize(err);
}

static void test_append1(void **state) {
    tj_error *err = tj_error_create(TJ_ERROR_FAILURE, "A");
    assert_non_null(err);

    assert_int_equal(tj_error_getCode(err), TJ_ERROR_FAILURE);

    tj_error_appendMessage(err, "B");
    assert_string_equal(tj_error_getMessage(err),
            "[FAILURE]: A\n[FAILURE]: B");

    tj_error_appendMessage(err, "C");
    assert_string_equal(tj_error_getMessage(err),
            "[FAILURE]: A\n[FAILURE]: B\n[FAILURE]: C");

    assert_int_equal(tj_error_getCode(err), TJ_ERROR_FAILURE);

    tj_error_finalize(err);
}

int main(int argc, char *argv[]) {
    const UnitTest tests[] = {
        unit_test(test_create1),
        unit_test(test_create2),
        unit_test(test_append1),
    };

    return run_tests(tests);
}
