/* ==========================================
    Unity Project - A Test Framework for C
    Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
    [Released under MIT License. Please refer to license.txt for details]
========================================== */

#ifndef UNITY_FRAMEWORK_H
#define UNITY_FRAMEWORK_H

#define UNITY

#include "unity_internals.h"

//-------------------------------------------------------
// Configuration Options
//-------------------------------------------------------

// Integers
//     - Unity assumes 32 bit integers by default
//     - If your compiler treats ints of a different size, define UNITY_INT_WIDTH

// Floats
//     - define UNITY_EXCLUDE_FLOAT to disallow floating point comparisons
//     - define UNITY_FLOAT_PRECISION to specify the precision to use when doing TEST_ASSERT_EQUAL_FLOAT
//     - define UNITY_FLOAT_TYPE to specify doubles instead of single precision floats
//     - define UNITY_FLOAT_VERBOSE to print floating point values in errors (uses sprintf)

// Output
//     - by default, Unity prints to standard out with putchar.  define UNITY_OUTPUT_CHAR(a) with a different function if desired

// Optimization
//     - by default, line numbers are stored in unsigned shorts.  Define UNITY_LINE_TYPE with a different type if your files are huge
//     - by default, test and failure counters are unsigned shorts.  Define UNITY_COUNTER_TYPE with a different type if you want to save space or have more than 65535 Tests.

//-------------------------------------------------------
// Test Running Macros
//-------------------------------------------------------

#define TEST_PROTECT() (setjmp(Unity.AbortFrame) == 0)

#define TEST_ABORT() {longjmp(Unity.AbortFrame, 1);}

#define RUN_TEST(func, line_num) \
    Unity.CurrentTestName = #func; \
    Unity.CurrentTestLineNumber = line_num; \
    Unity.NumberOfTests++; \
    runTest(func); \
    UnityConcludeTest();

#define TEST_LINE_NUM (Unity.CurrentTestLineNumber)
#define TEST_IS_IGNORED (Unity.CurrentTestIgnored)

//-------------------------------------------------------
// Basic Fail and Ignore
//-------------------------------------------------------

#define TEST_FAIL(message)                                                                         UNITY_TEST_FAIL(__LINE__, message)
#define TEST_IGNORE_MESSAGE(message)                                                               UNITY_TEST_IGNORE(__LINE__, message)
#define TEST_IGNORE(message)                                                                       UNITY_TEST_IGNORE(__LINE__, NULL)
#define TEST_ONLY()

//-------------------------------------------------------
// Test Asserts (simple)
//-------------------------------------------------------

//Boolean
#define TEST_ASSERT(condition)                                                                     UNITY_TEST_ASSERT(       (condition), __LINE__, " Expression Evaluated To FALSE")
#define TEST_ASSERT_TRUE(condition)                                                                UNITY_TEST_ASSERT(       (condition), __LINE__, " Expected TRUE Was FALSE")
#define TEST_ASSERT_UNLESS(condition)                                                              UNITY_TEST_ASSERT(      !(condition), __LINE__, " Expression Evaluated To TRUE")
#define TEST_ASSERT_FALSE(condition)                                                               UNITY_TEST_ASSERT(      !(condition), __LINE__, " Expected FALSE Was TRUE")
#define TEST_ASSERT_NULL(pointer)                                                                  UNITY_TEST_ASSERT_NULL(    (pointer), __LINE__, " Expected Null")
#define TEST_ASSERT_NOT_NULL(pointer)                                                              UNITY_TEST_ASSERT_NOT_NULL((pointer), __LINE__, " Expected Non-Null")

//Integers (of all sizes)
#define TEST_ASSERT_EQUAL_INT(expected, actual)                                                    UNITY_TEST_ASSERT_EQUAL_INT((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL(expected, actual)                                                        UNITY_TEST_ASSERT_EQUAL_INT((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_NOT_EQUAL(expected, actual)                                                    UNITY_TEST_ASSERT(((expected) !=  (actual)), __LINE__, " Expected Not-Equal")
#define TEST_ASSERT_EQUAL_UINT(expected, actual)                                                   UNITY_TEST_ASSERT_EQUAL_UINT( (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX8(expected, actual)                                                   UNITY_TEST_ASSERT_EQUAL_HEX8( (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX16(expected, actual)                                                  UNITY_TEST_ASSERT_EQUAL_HEX16((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX32(expected, actual)                                                  UNITY_TEST_ASSERT_EQUAL_HEX32((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX(expected, actual)                                                    UNITY_TEST_ASSERT_EQUAL_HEX32((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_BITS(mask, expected, actual)                                                   UNITY_TEST_ASSERT_BITS((mask), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_BITS_HIGH(mask, actual)                                                        UNITY_TEST_ASSERT_BITS((mask), (_UU32)(-1), (actual), __LINE__, NULL)
#define TEST_ASSERT_BITS_LOW(mask, actual)                                                         UNITY_TEST_ASSERT_BITS((mask), (_UU32)(0), (actual), __LINE__, NULL)
#define TEST_ASSERT_BIT_HIGH(bit, actual)                                                          UNITY_TEST_ASSERT_BITS(((_UU32)1 << bit), (_UU32)(-1), (actual), __LINE__, NULL)
#define TEST_ASSERT_BIT_LOW(bit, actual)                                                           UNITY_TEST_ASSERT_BITS(((_UU32)1 << bit), (_UU32)(0), (actual), __LINE__, NULL)

//Integer Ranges (of all sizes)
#define TEST_ASSERT_INT_WITHIN(delta, expected, actual)                                            UNITY_TEST_ASSERT_INT_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_UINT_WITHIN(delta, expected, actual)                                           UNITY_TEST_ASSERT_UINT_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_HEX8_WITHIN(delta, expected, actual)                                           UNITY_TEST_ASSERT_HEX8_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_HEX16_WITHIN(delta, expected, actual)                                          UNITY_TEST_ASSERT_HEX16_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_HEX32_WITHIN(delta, expected, actual)                                          UNITY_TEST_ASSERT_HEX32_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_HEX_WITHIN(delta, expected, actual)                                            UNITY_TEST_ASSERT_HEX32_WITHIN(delta, expected, actual, __LINE__, NULL)

//Structs and Strings
#define TEST_ASSERT_EQUAL_STRING(expected, actual)                                                 UNITY_TEST_ASSERT_EQUAL_STRING(expected, actual, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_MEMORY(expected, actual, len)                                            UNITY_TEST_ASSERT_EQUAL_MEMORY(expected, actual, len, __LINE__, NULL)

//Arrays
#define TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, num_elements)                                UNITY_TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT_ARRAY(expected, actual, num_elements)                               UNITY_TEST_ASSERT_EQUAL_UINT_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, num_elements)                               UNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX16_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_HEX16_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX_ARRAY(expected, actual, num_elements)                                UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, num_elements)                             UNITY_TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, num_elements)                        UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, num_elements, __LINE__, NULL)

//Floating Point (If Enabled)
#define TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual)                                          UNITY_TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_FLOAT(expected, actual)                                                  UNITY_TEST_ASSERT_EQUAL_FLOAT(expected, actual, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements, __LINE__, NULL)

//-------------------------------------------------------
// Test Asserts (with additional messages)
//-------------------------------------------------------

//Boolean
#define TEST_ASSERT_MESSAGE(condition, message)                                                    UNITY_TEST_ASSERT(       (condition), __LINE__, message)
#define TEST_ASSERT_TRUE_MESSAGE(condition, message)                                               UNITY_TEST_ASSERT(       (condition), __LINE__, message)
#define TEST_ASSERT_UNLESS_MESSAGE(condition, message)                                             UNITY_TEST_ASSERT(      !(condition), __LINE__, message)
#define TEST_ASSERT_FALSE_MESSAGE(condition, message)                                              UNITY_TEST_ASSERT(      !(condition), __LINE__, message)
#define TEST_ASSERT_NULL_MESSAGE(pointer, message)                                                 UNITY_TEST_ASSERT_NULL(    (pointer), __LINE__, message)
#define TEST_ASSERT_NOT_NULL_MESSAGE(pointer, message)                                             UNITY_TEST_ASSERT_NOT_NULL((pointer), __LINE__, message)

//Integers (of all sizes)
#define TEST_ASSERT_EQUAL_INT_MESSAGE(expected, actual, message)                                   UNITY_TEST_ASSERT_EQUAL_INT((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_MESSAGE(expected, actual, message)                                       UNITY_TEST_ASSERT_EQUAL_INT((expected), (actual), __LINE__, message)
#define TEST_ASSERT_NOT_EQUAL_MESSAGE(expected, actual, message)                                   UNITY_TEST_ASSERT(((expected) !=  (actual)), __LINE__, message)
#define TEST_ASSERT_EQUAL_UINT_MESSAGE(expected, actual, message)                                  UNITY_TEST_ASSERT_EQUAL_UINT( (expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX8_MESSAGE(expected, actual, message)                                  UNITY_TEST_ASSERT_EQUAL_HEX8( (expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX16_MESSAGE(expected, actual, message)                                 UNITY_TEST_ASSERT_EQUAL_HEX16((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected, actual, message)                                 UNITY_TEST_ASSERT_EQUAL_HEX32((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX_MESSAGE(expected, actual, message)                                   UNITY_TEST_ASSERT_EQUAL_HEX32((expected), (actual), __LINE__, message)
#define TEST_ASSERT_BITS_MESSAGE(mask, expected, actual, message)                                  UNITY_TEST_ASSERT_BITS((mask), (expected), (actual), __LINE__, message)
#define TEST_ASSERT_BITS_HIGH_MESSAGE(mask, actual, message)                                       UNITY_TEST_ASSERT_BITS((mask), (_UU32)(-1), (actual), __LINE__, message)
#define TEST_ASSERT_BITS_LOW_MESSAGE(mask, actual, message)                                        UNITY_TEST_ASSERT_BITS((mask), (_UU32)(0), (actual), __LINE__, message)
#define TEST_ASSERT_BIT_HIGH_MESSAGE(bit, actual, message)                                         UNITY_TEST_ASSERT_BITS(((_UU32)1 << bit), (_UU32)(-1), (actual), __LINE__, message)
#define TEST_ASSERT_BIT_LOW_MESSAGE(bit, actual, message)                                          UNITY_TEST_ASSERT_BITS(((_UU32)1 << bit), (_UU32)(0), (actual), __LINE__, message)

//Integer Ranges (of all sizes)
#define TEST_ASSERT_INT_WITHIN_MESSAGE(delta, expected, actual, message)                           UNITY_TEST_ASSERT_INT_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_UINT_WITHIN_MESSAGE(delta, expected, actual, message)                          UNITY_TEST_ASSERT_UINT_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_HEX8_WITHIN_MESSAGE(delta, expected, actual, message)                          UNITY_TEST_ASSERT_HEX8_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_HEX16_WITHIN_MESSAGE(delta, expected, actual, message)                         UNITY_TEST_ASSERT_HEX16_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_HEX32_WITHIN_MESSAGE(delta, expected, actual, message)                         UNITY_TEST_ASSERT_HEX32_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_HEX_WITHIN_MESSAGE(delta, expected, actual, message)                           UNITY_TEST_ASSERT_HEX32_WITHIN(delta, expected, actual, __LINE__, message)

//Structs and Strings
#define TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual, message)                                UNITY_TEST_ASSERT_EQUAL_STRING(expected, actual, __LINE__, message)
#define TEST_ASSERT_EQUAL_MEMORY_MESSAGE(expected, actual, len, message)                           UNITY_TEST_ASSERT_EQUAL_MEMORY(expected, actual, len, __LINE__, message)

//Arrays
#define TEST_ASSERT_EQUAL_INT_ARRAY_MESSAGE(expected, actual, num_elements, message)               UNITY_TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_UINT_ARRAY_MESSAGE(expected, actual, num_elements, message)              UNITY_TEST_ASSERT_EQUAL_UINT_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(expected, actual, num_elements, message)              UNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX16_ARRAY_MESSAGE(expected, actual, num_elements, message)             UNITY_TEST_ASSERT_EQUAL_HEX16_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX32_ARRAY_MESSAGE(expected, actual, num_elements, message)             UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX_ARRAY_MESSAGE(expected, actual, num_elements, message)               UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected, actual, num_elements, message)            UNITY_TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_MEMORY_ARRAY_MESSAGE(expected, actual, len, num_elements, message)       UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, num_elements, __LINE__, message)

//Floating Point (If Enabled)
#define TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, expected, actual, message)                         UNITY_TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected, actual, message)                                 UNITY_TEST_ASSERT_EQUAL_FLOAT(expected, actual, __LINE__, message)
#define TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(expected, actual, num_elements, message)             UNITY_TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements, __LINE__, message)
#endif
