#include <glib.h>

#include "sha512tree.h"

void test_add(void)
{
        sha512tree *root = new_leaf();

        int expected = 0;
        int actual = sha512tree_add(root, (unsigned char*)"ee26b0dd4af7e749aa1a8ee3c10ae9923f618980772e473f8819a5d4940e0db27ac185f8a0e1d5f84f88bc887fd67b143732c304cc5fa9ad8e6f57f50028a8ff");

        g_assert_cmpint(actual, ==, expected);
}

void test_contains(void)
{
        sha512tree *root = new_leaf();

        /* Test not contains */
        int expected = 0;
        int actual = sha512tree_contains(root, (unsigned char*)"ee26b0dd4af7e749aa1a8ee3c10ae9923f618980772e473f8819a5d4940e0db27ac185f8a0e1d5f84f88bc887fd67b143732c304cc5fa9ad8e6f57f50028a8ff");

        g_assert_cmpint(actual, ==, expected);

        /* test contains */
        sha512tree_add(root, (unsigned char*)"ee26b0dd4af7e749aa1a8ee3c10ae9923f618980772e473f8819a5d4940e0db27ac185f8a0e1d5f84f88bc887fd67b143732c304cc5fa9ad8e6f57f50028a8ff");

        expected = 1;
        actual = sha512tree_contains(root, (unsigned char*)"ee26b0dd4af7e749aa1a8ee3c10ae9923f618980772e473f8819a5d4940e0db27ac185f8a0e1d5f84f88bc887fd67b143732c304cc5fa9ad8e6f57f50028a8ff");

        g_assert_cmpint(actual, ==, expected);
}

void test_del(void)
{
        sha512tree *root = new_leaf();

        int expected = 0;
        int actual = sha512tree_del(root, (unsigned char*) "ee26b0dd4af7e749aa1a8ee3c10ae9923f618980772e473f8819a5d4940e0db27ac185f8a0e1d5f84f88bc887fd67b143732c304cc5fa9ad8e6f57f50028a8ff");

        g_assert_cmpint(actual, ==, expected);
}

int main(int argc, char *argv[])
{
        g_test_init(&argc, &argv, NULL);
        g_test_add_func("/sha512tree test", test_contains);
        return g_test_run();
}
