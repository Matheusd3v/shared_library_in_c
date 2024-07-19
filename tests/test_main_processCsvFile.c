#include "../libcsv.h"
#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "helper/test_helper.h"


void test_processCsvFile_with_less_than_operator(void) {
    const char *filepath = "tests/mock/test_30_lines.csv";
    const char *expected_output = "IBNFKBSVWRHTJTVRMQREWQCNFL\n44\n28\n11\n"; 
    
    ProcessCsvArgs args = {
        .input = filepath,
        .headers_output = "IBNFKBSVWRHTJTVRMQREWQCNFL",
        .filter = "VACVQJWALGXPRTLYHICSITGXRF<10"
    };

    char *output = capture_stdout(processCsvFile, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsvFile_with_less_than_or_equal_operator(void) {
    const char *filepath = "tests/mock/test_30_lines.csv";
    const char *expected_output = "XHLRRNTUIVPSFSFARGWRGSVGXD\n23\n87\n64\n37\n10\n66\n78\n47\n78\n63\n"; 
    
    ProcessCsvArgs args = {
        .input = filepath,
        .headers_output = "XHLRRNTUIVPSFSFARGWRGSVGXD",
        .filter = "IBNFKBSVWRHTJTVRMQREWQCNFL<=22"
    };

    char *output = capture_stdout(processCsvFile, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsvFile_with_greather_than_operator(void) {
    const char *filepath = "tests/mock/test_2000_lines.csv";
    const char *expected_output = "PCCJG\n91\n29\n"; 
    
    ProcessCsvArgs args = {
        .input = filepath,
        .headers_output = "PCCJG",
        .filter = "VAWSF>100"
    };

    char *output = capture_stdout(processCsvFile, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsvFile_with_greather_than_or_equal_operator(void) {
    const char *filepath = "tests/mock/many_numbers.csv";
    const char *expected_output = "WINZKZXNIMYRKHRAMAGIFQNWRMVYQCOOZDXKUHGITUCPAIQWKN\n7413152591\n9336073531\n2123292546\n5662239088\n7420779733\n7036409465\n7852112451\n"; 
    
    ProcessCsvArgs args = {
        .input = filepath,
        .headers_output = "WINZKZXNIMYRKHRAMAGIFQNWRMVYQCOOZDXKUHGITUCPAIQWKN",
        .filter = "XBYGICBAHYIEGVKGNMIFEZTWEGQCZMWLHIWTOFWHKGGPYGMBTT>=9999999998"
    };

    char *output = capture_stdout(processCsvFile, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsvFile_with_equal_operator(void) {
    const char *filepath = "tests/mock/many_numbers.csv";
    const char *expected_output = "TCUKDGABFUJQCLPHCAIZZWJSNBUNRBKXJIAHPHPFBGPZOSKERW\n9193270258\n"; 
    
    ProcessCsvArgs args = {
        .input = filepath,
        .headers_output = "TCUKDGABFUJQCLPHCAIZZWJSNBUNRBKXJIAHPHPFBGPZOSKERW",
        .filter = "CAKFTJXHFNDZTJIQRZOMMUOICZROLMVEVIJOKTKBTLLZLRXAGI=573951221"
    };

    char *output = capture_stdout(processCsvFile, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsvFile_with_not_equal_operator(void) {
    const char *filepath = "tests/mock/many_numbers.csv";
    const char *expected_output = "WINZKZXNIMYRKHRAMAGIFQNWRMVYQCOOZDXKUHGITUCPAIQWKN\n7413152591\n3034255010\n9336073531\n2123292546\n6680012174\n7769788256\n545266125\n5172656102\n1865147621\n7788585118\n2623850337\n653140201\n5662239088\n9464282222\n7438234461\n5479312540\n3865831934\n4221280947\n3970224776\n132069280\n9561046026\n612220745\n8644873833\n1593612016\n7420779733\n684986526\n7036409465\n1098261626\n6245587842\n7852112451\n"; 
    
    ProcessCsvArgs args = {
        .input = filepath,
        .headers_output = "WINZKZXNIMYRKHRAMAGIFQNWRMVYQCOOZDXKUHGITUCPAIQWKN",
        .filter = "XBYGICBAHYIEGVKGNMIFEZTWEGQCZMWLHIWTOFWHKGGPYGMBTT!=1"
    };

    char *output = capture_stdout(processCsvFile, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}