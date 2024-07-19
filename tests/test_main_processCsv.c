#include "../libcsv.h"
#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "helper/test_helper.h"

void test_processCsv_with_simple_header(void) {
    const char *test_input = "header1,header2,header3\n1,2,3\n4,5,6\n7,8,9"; 
    const char *expected_output = "header1,header3\n4,6\n"; 

    ProcessCsvArgs args = {
        .input = test_input,
        .headers_output = "header1,header3",
        .filter = "header1>1\nheader3<8"
    };

    char *output = capture_stdout(processCsv, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsv_with_256_headers_to_get_all_headers(void) {
    const char *test_input = "IGMFS,XYPCA,LNTUI,DNVPI,ALBLP,BWCZQ,QTJVV,EOUHA,EDRRH,KOJTZ,CBBFE,YXLSS,UECVQ,OCYDE,GEIRL,PAOZK,IIOAB,PJDLE,IHTBJ,XAVWZ,LQLPP,MZYUZ,MWQBA,RMGTF,POPNU,YHJEU,MKFGR,ZCENA,TXVWT,LQSTT,OVYRR,OJBNM,QOZRN,TNEWD,MLSVJ,ZRQJW,LLAUL,GZGJY,TFGKO,WLKXS,TMRTT,NZLDJ,JEPUN,UDTWC,HOVFD,IOINJ,HZUXL,VTBYW,WOSOB,MKTJW,EVJAS,QCVZJ,IMGPN,RWQNI,PSMNS,OFTKM,WACZZ,RYLMJ,JJZVH,BUVQB,SSHPW,PFAJX,THEKS,HBHZN,BGHUD,XPXRL,ULDOA,GTVOH,DJIAW,HYNNQ,GTRRZ,BFTCS,HCMNW,PIEFX,ATBUI,THPFV,DSULK,MTOVJ,WJTFB,RSZUE,LOOTK,YLWZR,WXAKL,JPNPX,MFGJP,EEVPA,IJJPK,UBVDN,KKRGM,SCZBX,SJWGP,FCGEH,RQJEO,LGNQJ,KAQLE,QWBKT,ZBRXL,LVLVU,QJTJG,SAUVX,WHDHW,SDVND,HDRSD,QADNT,ULDPC,KPYXX,UFMSD,OQWNX,QULWI,ZFXNK,XECPY,TFHLK,AIVYF,UWOUX,IPMCN,FNRVH,ODCOG,CWXHZ,VXQUO,XDFQR,RTNPX,ALFBW,PSQXL,QSSOL,HCQSM,SCGWG,UTRKF,LKHVX,ASBYL,JFGCX,SYYWO,AEFUS,PGVHU,EEUUX,ZYYQD,DTKSW,QMBZO,UIYYJ,VAZOT,NUYTH,EWGWC,DXXDG,UFVQO,MMWAU,ZBQNI,GVDUF,BPPHS,IPDAH,WXKOT,INISQ,EFBJR,DEGRC,XGOJH,JIOKQ,DRTLV,SEDJR,CTFXW,NMPVM,TYNKX,GSCOA,WXKVF,FASUY,JMAMQ,LOVYH,PFSCF,KQMSX,ZYDRV,XFFMP,FDTAI,FOBTX,TPVEN,MFXLA,MBVAX,LNLKH,YEDDU,GRRTR,KEGGT,IPFZM,NAKXA,YULPK,QOWPP,UDJPN,MNWKU,VUENA,UEMJZ,CQQKB,VDXSX,SXHNS,NAQYT,WATNL,XGPBL,PMUOY,CGOQE,BABRC,ZZDFT,QRKHR,PZUZD,UDFPZ,ZCHPM,ZUQWS,ZBGJP,JUDTE,HDVUG,TMGNX,MPYSM,PTDJA,RNFOW,YHHQZ,KTMET,CSLWS,WMDDP,MYVOS,LFKPG,YSCTQ,URNXU,SIDYD,EXZLY,YQXDB,GRCWB,IWZOV,UQDFH,AXZWL,TBKZW,UBZMQ,KKFDZ,MAUNN,SKPHZ,QMJEV,IYXRH,AYHDR,OEZZI,KWPHB,CJBLH,MGNAS,QQVLP,ZTJTB,NNGHL,WEYDL,LYTHS,DNEVG,GEBBB,NHCHR,FEZNK,KIHFQ,JRDIP,GCGTT,RVFJZ,ZPBWK,CNLIX,FXHFR,ZQAYL,GJUTO,HENCP,VHUOI,GGDIY,VAHTY\n6,90,8,9,3,79,22,9,32,90,94,15,4,46,18,37,97,90,100,74,84,14,6,67,58,31,29,61,71,57,81,49,78,22,20,52,49,64,39,50,53,35,26,75,62,7,15,56,31,41,61,78,88,99,82,69,76,50,43,20,94,68,54,2,42,73,63,22,43,84,40,4,12,90,70,26,57,61,79,91,38,33,27,50,72,9,12,43,23,44,22,90,47,32,88,24,36,72,90,100,75,74,53,77,1,30,57,35,25,23,97,90,87,67,9,30,92,18,33,2,95,54,19,16,4,76,65,95,91,47,37,50,25,71,98,53,63,15,32,83,54,28,98,63,22,27,38,65,62,81,13,10,66,98,81,7,28,61,100,69,4,52,26,83,66,98,53,27,88,80,60,6,86,87,7,4,91,84,75,47,59,20,65,51,60,5,90,24,8,43,85,11,31,14,50,99,68,60,15,26,28,45,64,42,16,5,95,52,35,39,98,92,97,14,46,68,87,29,21,64,37,71,2,93,22,20,40,63,46,95,80,41,35,50,69,88,54,36,74,31,32,7,83,96,38,75,23,27,25,25,15,73,45,81,38,94\n6,3,64,48,13,36,55,49,30,17,49,95,58,49,1,23,72,71,54,57,25,12,15,54,5,17,40,19,10,86,46,72,83,60,21,85,99,70,25,56,82,93,54,57,91,34,72,6,52,5,54,15,43,8,35,38,32,35,93,98,66,59,67,15,10,31,98,28,85,7,41,39,77,94,13,8,65,94,6,87,97,26,79,23,67,5,49,53,86,15,76,25,64,53,47,95,41,23,35,62,7,74,44,66,81,59,89,90,55,83,78,89,98,78,15,27,1,42,13,29,95,4,89,37,71,44,92,89,14,83,41,28,36,83,57,63,83,19,13,41,44,90,45,47,41,18,21,49,60,14,18,29,21,35,40,14,81,45,84,83,59,85,12,17,31,10,64,34,54,4,55,57,94,22,1,51,26,81,54,99,32,86,60,88,67,76,88,3,26,64,75,87,92,4,51,2,21,91,67,99,14,75,11,24,83,41,47,80,17,17,79,57,8,80,47,87,49,8,49,25,17,36,80,27,5,73,44,6,50,38,92,99,11,84,90,43,66,39,53,64,62,84,16,50,91,32,32,35,25,70,74,13,42,49,78,37\n50,39,55,7,71,100,3,28,3,67,16,92,36,56,3,18,50,27,73,22,54,10,62,33,26,45,25,32,94,12,1,40,94,1,92,15,25,20,59,28,3,12,78,27,16,81,62,54,88,33,84,32,89,11,1,37,10,81,36,51,19,98,58,26,27,84,9,67,95,24,87,38,10,19,82,38,64,32,76,20,32,57,92,76,70,59,2,75,64,60,18,12,20,45,74,19,78,50,3,19,83,1,66,72,50,17,52,76,83,64,69,59,98,65,77,69,27,15,29,75,56,69,20,83,27,55,33,56,63,44,54,46,7,40,95,58,48,45,7,100,8,25,42,8,7,73,3,49,4,61,40,27,50,99,65,48,4,72,40,50,9,77,90,2,55,29,99,73,9,9,7,36,36,88,56,36,4,67,66,95,1,83,80,46,100,7,5,47,34,77,70,23,77,60,53,83,91,32,25,15,85,15,65,58,6,82,69,72,43,26,2,53,49,89,41,28,40,40,63,38,6,51,26,31,72,93,92,65,50,66,31,41,45,42,39,54,21,50,73,31,85,51,98,88,19,79,20,44,30,19,29,93,37,81,49,4";
    const char *expected_output = "IGMFS\n6\n"; 
    
    ProcessCsvArgs args = {
        .input = test_input,
        .headers_output = "IGMFS",
        .filter = "VAHTY=37"
    };

    char *output = capture_stdout(processCsv, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsv_with_256_headers_to_get_last_header_and_last_column_line(void) {
    const char *test_input = "IGMFS,XYPCA,LNTUI,DNVPI,ALBLP,BWCZQ,QTJVV,EOUHA,EDRRH,KOJTZ,CBBFE,YXLSS,UECVQ,OCYDE,GEIRL,PAOZK,IIOAB,PJDLE,IHTBJ,XAVWZ,LQLPP,MZYUZ,MWQBA,RMGTF,POPNU,YHJEU,MKFGR,ZCENA,TXVWT,LQSTT,OVYRR,OJBNM,QOZRN,TNEWD,MLSVJ,ZRQJW,LLAUL,GZGJY,TFGKO,WLKXS,TMRTT,NZLDJ,JEPUN,UDTWC,HOVFD,IOINJ,HZUXL,VTBYW,WOSOB,MKTJW,EVJAS,QCVZJ,IMGPN,RWQNI,PSMNS,OFTKM,WACZZ,RYLMJ,JJZVH,BUVQB,SSHPW,PFAJX,THEKS,HBHZN,BGHUD,XPXRL,ULDOA,GTVOH,DJIAW,HYNNQ,GTRRZ,BFTCS,HCMNW,PIEFX,ATBUI,THPFV,DSULK,MTOVJ,WJTFB,RSZUE,LOOTK,YLWZR,WXAKL,JPNPX,MFGJP,EEVPA,IJJPK,UBVDN,KKRGM,SCZBX,SJWGP,FCGEH,RQJEO,LGNQJ,KAQLE,QWBKT,ZBRXL,LVLVU,QJTJG,SAUVX,WHDHW,SDVND,HDRSD,QADNT,ULDPC,KPYXX,UFMSD,OQWNX,QULWI,ZFXNK,XECPY,TFHLK,AIVYF,UWOUX,IPMCN,FNRVH,ODCOG,CWXHZ,VXQUO,XDFQR,RTNPX,ALFBW,PSQXL,QSSOL,HCQSM,SCGWG,UTRKF,LKHVX,ASBYL,JFGCX,SYYWO,AEFUS,PGVHU,EEUUX,ZYYQD,DTKSW,QMBZO,UIYYJ,VAZOT,NUYTH,EWGWC,DXXDG,UFVQO,MMWAU,ZBQNI,GVDUF,BPPHS,IPDAH,WXKOT,INISQ,EFBJR,DEGRC,XGOJH,JIOKQ,DRTLV,SEDJR,CTFXW,NMPVM,TYNKX,GSCOA,WXKVF,FASUY,JMAMQ,LOVYH,PFSCF,KQMSX,ZYDRV,XFFMP,FDTAI,FOBTX,TPVEN,MFXLA,MBVAX,LNLKH,YEDDU,GRRTR,KEGGT,IPFZM,NAKXA,YULPK,QOWPP,UDJPN,MNWKU,VUENA,UEMJZ,CQQKB,VDXSX,SXHNS,NAQYT,WATNL,XGPBL,PMUOY,CGOQE,BABRC,ZZDFT,QRKHR,PZUZD,UDFPZ,ZCHPM,ZUQWS,ZBGJP,JUDTE,HDVUG,TMGNX,MPYSM,PTDJA,RNFOW,YHHQZ,KTMET,CSLWS,WMDDP,MYVOS,LFKPG,YSCTQ,URNXU,SIDYD,EXZLY,YQXDB,GRCWB,IWZOV,UQDFH,AXZWL,TBKZW,UBZMQ,KKFDZ,MAUNN,SKPHZ,QMJEV,IYXRH,AYHDR,OEZZI,KWPHB,CJBLH,MGNAS,QQVLP,ZTJTB,NNGHL,WEYDL,LYTHS,DNEVG,GEBBB,NHCHR,FEZNK,KIHFQ,JRDIP,GCGTT,RVFJZ,ZPBWK,CNLIX,FXHFR,ZQAYL,GJUTO,HENCP,VHUOI,GGDIY,VAHTY\n6,90,8,9,3,79,22,9,32,90,94,15,4,46,18,37,97,90,100,74,84,14,6,67,58,31,29,61,71,57,81,49,78,22,20,52,49,64,39,50,53,35,26,75,62,7,15,56,31,41,61,78,88,99,82,69,76,50,43,20,94,68,54,2,42,73,63,22,43,84,40,4,12,90,70,26,57,61,79,91,38,33,27,50,72,9,12,43,23,44,22,90,47,32,88,24,36,72,90,100,75,74,53,77,1,30,57,35,25,23,97,90,87,67,9,30,92,18,33,2,95,54,19,16,4,76,65,95,91,47,37,50,25,71,98,53,63,15,32,83,54,28,98,63,22,27,38,65,62,81,13,10,66,98,81,7,28,61,100,69,4,52,26,83,66,98,53,27,88,80,60,6,86,87,7,4,91,84,75,47,59,20,65,51,60,5,90,24,8,43,85,11,31,14,50,99,68,60,15,26,28,45,64,42,16,5,95,52,35,39,98,92,97,14,46,68,87,29,21,64,37,71,2,93,22,20,40,63,46,95,80,41,35,50,69,88,54,36,74,31,32,7,83,96,38,75,23,27,25,25,15,73,45,81,38,94\n6,3,64,48,13,36,55,49,30,17,49,95,58,49,1,23,72,71,54,57,25,12,15,54,5,17,40,19,10,86,46,72,83,60,21,85,99,70,25,56,82,93,54,57,91,34,72,6,52,5,54,15,43,8,35,38,32,35,93,98,66,59,67,15,10,31,98,28,85,7,41,39,77,94,13,8,65,94,6,87,97,26,79,23,67,5,49,53,86,15,76,25,64,53,47,95,41,23,35,62,7,74,44,66,81,59,89,90,55,83,78,89,98,78,15,27,1,42,13,29,95,4,89,37,71,44,92,89,14,83,41,28,36,83,57,63,83,19,13,41,44,90,45,47,41,18,21,49,60,14,18,29,21,35,40,14,81,45,84,83,59,85,12,17,31,10,64,34,54,4,55,57,94,22,1,51,26,81,54,99,32,86,60,88,67,76,88,3,26,64,75,87,92,4,51,2,21,91,67,99,14,75,11,24,83,41,47,80,17,17,79,57,8,80,47,87,49,8,49,25,17,36,80,27,5,73,44,6,50,38,92,99,11,84,90,43,66,39,53,64,62,84,16,50,91,32,32,35,25,70,74,13,42,49,78,37\n50,39,55,7,71,100,3,28,3,67,16,92,36,56,3,18,50,27,73,22,54,10,62,33,26,45,25,32,94,12,1,40,94,1,92,15,25,20,59,28,3,12,78,27,16,81,62,54,88,33,84,32,89,11,1,37,10,81,36,51,19,98,58,26,27,84,9,67,95,24,87,38,10,19,82,38,64,32,76,20,32,57,92,76,70,59,2,75,64,60,18,12,20,45,74,19,78,50,3,19,83,1,66,72,50,17,52,76,83,64,69,59,98,65,77,69,27,15,29,75,56,69,20,83,27,55,33,56,63,44,54,46,7,40,95,58,48,45,7,100,8,25,42,8,7,73,3,49,4,61,40,27,50,99,65,48,4,72,40,50,9,77,90,2,55,29,99,73,9,9,7,36,36,88,56,36,4,67,66,95,1,83,80,46,100,7,5,47,34,77,70,23,77,60,53,83,91,32,25,15,85,15,65,58,6,82,69,72,43,26,2,53,49,89,41,28,40,40,63,38,6,51,26,31,72,93,92,65,50,66,31,41,45,42,39,54,21,50,73,31,85,51,98,88,19,79,20,44,30,19,29,93,37,81,49,4";
    const char *expected_output = "VAHTY\n4\n"; 
    
    ProcessCsvArgs args = {
        .input = test_input,
        .headers_output = "VAHTY",
        .filter = "VAHTY=4"
    };

    char *output = capture_stdout(processCsv, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsv_with_less_than_operator(void) {
    const char *test_input = "header1,header2,header3,header4,header5\n11,2,3,4,5\n26,7,8,9,10\n1,12,13,14,15";
    const char *expected_output = "header1,header2,header3,header4,header5\n1,12,13,14,15\n"; 
    
    ProcessCsvArgs args = {
        .input = test_input,
        .headers_output = "",
        .filter = "header1<2"
    };

    char *output = capture_stdout(processCsv, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsv_with_less_than_or_equal_operator(void) {
    const char *test_input = "header1,header2,header3,header4,header5\n11,23,3,4,5\n26,1,8,9,10\n1,2,13,14,15";
    const char *expected_output = "header1,header2,header3,header4,header5\n26,1,8,9,10\n1,2,13,14,15\n"; 
    
    ProcessCsvArgs args = {
        .input = test_input,
        .headers_output = "",
        .filter = "header2<=2"
    };

    char *output = capture_stdout(processCsv, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsv_with_greather_than_operator(void) {
    const char *test_input = "header1,header2,header3,header4,header5\n11,2,1,4,5\n26,7,8,9,10\n1,12,1,14,15";
    const char *expected_output = "header1,header2,header3,header4,header5\n26,7,8,9,10\n"; 
    
    ProcessCsvArgs args = {
        .input = test_input,
        .headers_output = "",
        .filter = "header3>2"
    };

    char *output = capture_stdout(processCsv, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsv_with_greather_than_or_equal_operator(void) {
    const char *test_input = "header1,header2,header3,header4,header5\n11,2,1,4,5\n26,7,8,9,10\n1,12,1,14,1";
    const char *expected_output = "header1,header2,header3,header4,header5\n11,2,1,4,5\n26,7,8,9,10\n"; 
    
    ProcessCsvArgs args = {
        .input = test_input,
        .headers_output = "",
        .filter = "header5>=5"
    };

    char *output = capture_stdout(processCsv, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsv_with_equal_operator(void) {
    const char *test_input = "header1,header2,header3,header4,header5\n11,2,1,4,5\n26,7,8,9,10\n1,12,1,14,15";
    const char *expected_output = "header1,header2,header3,header4,header5\n1,12,1,14,15\n"; 
    
    ProcessCsvArgs args = {
        .input = test_input,
        .headers_output = "",
        .filter = "header4=14"
    };

    char *output = capture_stdout(processCsv, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}

void test_processCsv_with_not_equal_operator(void) {
    const char *test_input = "header1,header2,header3,header4,header5\n11,2,1,4,5\n26,7,8,9,10\n1,12,1,14,15";
    const char *expected_output = "header3\n1\n8\n1\n"; 
    
    ProcessCsvArgs args = {
        .input = test_input,
        .headers_output = "header3",
        .filter = "header4!=33"
    };

    char *output = capture_stdout(processCsv, &args);

    TEST_ASSERT_EQUAL_STRING(expected_output, output);

    free(output); 
}