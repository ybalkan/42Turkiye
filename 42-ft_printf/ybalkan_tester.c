#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

/* --- COLORS & STYLING --- */
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define BOLD "\033[1m"

/* --- STATS --- */
int g_tests_run = 0;
int g_tests_passed = 0;

/* --- MACRO MAGIC --- */
/* This macro runs both printf and ft_printf, prints their output side-by-side,
   and compares return values. */
#define TEST(desc, fmt, ...)                                                   \
  do {                                                                         \
    int ret_orig, ret_user;                                                    \
    printf(CYAN "\n[%02d] %s" RESET "\n", ++g_tests_run, desc);                \
                                                                               \
    printf(YELLOW "   [ORG]: " RESET);                                         \
    fflush(stdout);                                                            \
    ret_orig = printf(fmt, ##__VA_ARGS__);                                     \
    printf(RESET);                                                             \
                                                                               \
    printf(BLUE "\n   [USR]: " RESET);                                         \
    fflush(stdout);                                                            \
    ret_user = ft_printf(fmt, ##__VA_ARGS__);                                  \
    printf(RESET);                                                             \
                                                                               \
    printf("\n   ");                                                           \
    if (ret_orig == ret_user) {                                                \
      printf(GREEN "✅ [OK] Return: %d" RESET, ret_orig);                      \
      g_tests_passed++;                                                        \
    } else {                                                                   \
      printf(RED "❌ [FAIL] Return MISMATCH! Org:%d vs Usr:%d" RESET,          \
             ret_orig, ret_user);                                              \
    }                                                                          \
    printf("\n");                                                              \
  } while (0)

/* --- MAIN HEADER --- */
void print_header() {
  printf("\n" MAGENTA);
  printf("************************************************************\n");
  printf("*                                                          *\n");
  printf("*            🔥 ULTIMATE FT_PRINTF TESTER 🔥                 *\n");
  printf("*                  User: ybalkan                           *\n");
  printf("*                                                          *\n");
  printf("************************************************************\n");
  printf(RESET "\n");
}

/* --- MAIN FOOTER --- */
void print_footer() {
  printf("\n" MAGENTA);
  printf("************************************************************\n");
  printf("*                    TEST SUMMARY                          *\n");
  printf("************************************************************\n");
  printf(BOLD "   TOTAL TESTS: %d\n" RESET, g_tests_run);

  if (g_tests_passed == g_tests_run)
    printf(GREEN "   PASSED     : %d  (100%% Success! 🎉)\n" RESET,
           g_tests_passed);
  else
    printf(RED "   PASSED     : %d\n   FAILED     : %d\n" RESET, g_tests_passed,
           g_tests_run - g_tests_passed);

  printf(
      MAGENTA
      "************************************************************\n" RESET);
  printf("\n");
}

int main() {
  void *ptr = (void *)0x12345678;
  char *null_str = NULL;

  print_header();

  // --- BASIC TESTS ---
  TEST("Simple String", "Hello World");
  TEST("Character", "%c", 'A');
  TEST("Integer", "%d", 42);
  TEST("Negative Integer", "%i", -12345);
  TEST("Unsigned", "%u", 4294967295U);
  TEST("Hex Lower", "%x", 255);
  TEST("Hex Upper", "%X", 255);
  TEST("Percent", "%%");

  // --- POINTER TESTS ---
  TEST("Pointer Normal", "%p", ptr);
  TEST("Pointer NULL", "%p", NULL);

  // --- EDGE CASES ---
  TEST("Null String", "%s", null_str);
  TEST("Mixed Combo", "Char: %c, Int: %d, Str: %s", 'Z', 999, "Test");
  TEST("Max/Min Integers", "Max: %d, Min: %d", INT_MAX, INT_MIN);
  TEST("Zero Values", "%d %i %u %x %X", 0, 0, 0, 0, 0);

  // --- ADVANCED / TRICKY ---
  TEST("Consecutive Percents", "%%%% %%");
  TEST("Multiple Strings", "%s %s", "One", "Two");
  TEST("Embedded Nulls", "Start %c End", '\0'); // Should print null char

  /*
     NOTE: undefined behavior tests like %k are tricky because
     standard printf behavior is undefined. We test them if your implementation
     handles them gracefully (printing literally).
  */
  TEST("Undefined Specifier %k", "Hello %k World");

  // --- ORIGINAL ULTIMATE TESTS (Restored) ---
  TEST("Original: Multiple Strings", " %s %s %s %s %s %s ", "test_case", NULL,
       "intraybalkan", "", " ", NULL);
  TEST("Original: Pointer Madness", " %p %p %p %p %p %p %p %p ", "pointer", ptr,
       NULL, "", -42, NULL, LONG_MIN, LONG_MAX);
  TEST("Original: Advanced Pointers", " %p %p %p %p %p %p ", LONG_MIN + 1,
       LONG_MIN + 2, LONG_MIN + 3, -ULONG_MAX, ULONG_MAX, ULONG_MAX - 1);
  TEST("Original: Decimal/Int Mix", " %d %d %d %d %d %d %d %d %d %i ", 42, -42,
       INT_MIN, INT_MAX, NULL, "TEST", "", LONG_MIN, LONG_MAX, ptr);
  TEST("Original: Unsigned Edge", " %u %u %u %u %u %u %u ", INT_MIN, 2147483650,
       -1, NULL, ULONG_MAX, LONG_MAX, LLONG_MAX);
  TEST("Original: Hex Limits", " %x %x %x %x %x %x %x %x ", NULL, INT_MIN,
       INT_MAX, 0, '0', LONG_MIN, LONG_MAX, LLONG_MAX);
  TEST("Original: HEX Limits", " %X %X %X %X %X %X %X %X ", NULL, INT_MIN,
       INT_MAX, 0, '0', LONG_MIN, LONG_MAX, LLONG_MAX);
  TEST("Original: Percent Combo", " %% %%%|%%%%|%%%%% | %%%%%%%%%%%% %%%%% ");

  // --- STRESS / TORTURE ---
  TEST("Chain Reaction", "Int:%d Hex:%x Char:%c Str:%s Ptr:%p", 42, 0xDEAD, 'X',
       "Combo", ptr);
  TEST("Long String", "%s",
       "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do "
       "eiusmod tempor incididunt ut labore et dolore magna aliqua.");
  TEST("Empty & Spaces", "|%s|  |%s|  |%s|", "", "   ", "");

  // --- TORTURE LEVEL (EXTREME) ---
  TEST("Torture: Rapid Fire", "%c%c%c%c%c%c%c%c", 'R', 'a', 'p', 'i', 'd', '!',
       '!', '!');
  TEST("Torture: Mixed Signs", "%d %d %i %i", INT_MAX, INT_MIN, INT_MAX,
       INT_MIN);
  TEST("Torture: Null Ptr Combo", "Ptr: %p, Str: %s, NullPtr: %p", ptr, "test",
       NULL);
  TEST("Torture: Garbage", "%s %x %d", "Garbage", 0xCAFE, -1);
  TEST("Torture: Zero/Null Mix", "%d %i %u %x %X %p", 0, 0, 0, 0, 0, NULL);

  // --- COMMUNITY NIGHTMARE (THE FINAL 8) ---
  TEST("Ngt: Negative Hex", "%x", -1);
  TEST("Ngt: Stack Address", "%p", &ptr);
  TEST("Ngt: Percent in String", "%s", "100% Success");
  TEST("Ngt: Unsigned Negative", "%u", -42);
  TEST("Ngt: Empty Argument", "|%s|", "");
  TEST("Ngt: Triple String", "%s-%s-%s", "A", "B", "C");
  TEST("Ngt: Format Trap", "%s", "Don't expand %d");
  TEST("THE ANSWER TO LIFE", "The answer is %d", 42);

  print_footer();

  ft_printf("Hello %a World");

  return (0);
}

/*
        src/pf_a.c                    ---->  Makefile Eklenecek

#include "../ft_printf.h"             ---->  pf_a.c dosyasının içeriği

int pf_a(va_list *args)
{
    (void)args;
    return (ft_putstr("42"));
}


table['a'] = &pf_a;                  ---->  init_table fonksiyonuna eklenecek

int		pf_a(va_list *args);       ---->  pf.h


     Çalıştırmak için:
    -------------------------
    Terminale şu komutu yapıştır:
    cc printf_tester.c libftprintf.a -o tester && ./tester
*/
