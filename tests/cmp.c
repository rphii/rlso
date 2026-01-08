#include "test.h"

/* these are all combinations that should be equal */
#define C_00     0, 0
#define C_0P     0, &SO
#define C_P0     &SO, 0
#define C_PP     &SO, &SO
#define C_0C     0, &so("")
#define C_PC     &SO, &so("")
#define C_C0     &so(""), 0
#define C_CP     &so(""), &SO
#define C_CC     &so(""), &so("")

int zero_cmp(So_Cmp_Func_p f) {
    int i = 0;
    if(++i && f(C_00)) return i;
    if(++i && f(C_0P)) return i;
    if(++i && f(C_P0)) return i;
    if(++i && f(C_PP)) return i;
    if(++i && f(C_0C)) return i;
    if(++i && f(C_PC)) return i;
    if(++i && f(C_C0)) return i;
    if(++i && f(C_CP)) return i;
    if(++i && f(C_CC)) return i;
    return 0;
}

int main(void) {
    /* empty */
    EXPECT(so_cmpx_p(0, 0, SO_CMP), 0);
    EXPECT(so_cmpx_p(0, &SO, SO_CMP), 0);
    EXPECT(so_cmpx_p(&SO, 0, SO_CMP), 0);
    EXPECT(so_cmpx_p(&SO, &SO, SO_CMP), 0);
    EXPECT(so_cmpx_p(&SO, &SO, SO_CMP), 0);
    EXPECT(so_cmpx_p(&SO, &SO, SO_CMP_BEGIN), 0);
    EXPECT(so_cmpx_p(&SO, &SO, SO_CMP_END), 0);
    EXPECT(so_cmpx_p(&SO, &SO, SO_CMP_CASE_INSENSITIVE), 0);
    /* the same .. but actually calling the functions */
    EXPECT(zero_cmp(so_cmp_p), 0);
    EXPECT(zero_cmp(so_cmp0_p), 0);
    EXPECT(zero_cmp(so_cmpE_p), 0);
    EXPECT(zero_cmp(so_cmp_sp), 0);
    EXPECT(zero_cmp(so_cmp0_sp), 0);
    EXPECT(zero_cmp(so_cmpE_sp), 0);
    EXPECT(zero_cmp(so_cmp_ip), 0);
    EXPECT(zero_cmp(so_cmp0_ip), 0);
    EXPECT(zero_cmp(so_cmpE_ip), 0);
    EXPECT(zero_cmp(so_cmp_isp), 0);
    EXPECT(zero_cmp(so_cmp0_isp), 0);
    EXPECT(zero_cmp(so_cmpE_isp), 0);
    /* actual comparisons (equal) */
    EXPECT(so_cmpx_p(&so("some string"), &so("some string"), SO_CMP), 0);
    EXPECT(so_cmpx_p(&so("some string"), &so("some"), SO_CMP_BEGIN), 0);
    EXPECT(so_cmpx_p(&so("some string"), &so("string"), SO_CMP_END), 0);
    EXPECT(so_cmpx_p(&so("sOmE sTrInG"), &so("SoMe StRiNg"), SO_CMP | SO_CMP_CASE_INSENSITIVE), 0);
    EXPECT(so_cmpx_p(&so("SoMe StRiNg"), &so("sOmE"), SO_CMP_BEGIN | SO_CMP_CASE_INSENSITIVE), 0);
    EXPECT(so_cmpx_p(&so("sOmE sTrInG"), &so("StRiNg"), SO_CMP_END | SO_CMP_CASE_INSENSITIVE), 0);
    EXPECT(so_cmpx_p(&so("some string"), &so("some string"), SO_CMP_SORTABLE), 0);
    EXPECT(so_cmpx_p(&so("some string"), &so("some"), SO_CMP_BEGIN | SO_CMP_SORTABLE), 0);
    EXPECT(so_cmpx_p(&so("some string"), &so("string"), SO_CMP_END | SO_CMP_SORTABLE), 0);
    EXPECT(so_cmpx_p(&so("sOmE sTrInG"), &so("SoMe StRiNg"), SO_CMP | SO_CMP_CASE_INSENSITIVE | SO_CMP_SORTABLE), 0);
    EXPECT(so_cmpx_p(&so("SoMe StRiNg"), &so("sOmE"), SO_CMP_BEGIN | SO_CMP_CASE_INSENSITIVE | SO_CMP_SORTABLE), 0);
    EXPECT(so_cmpx_p(&so("sOmE sTrInG"), &so("StRiNg"), SO_CMP_END | SO_CMP_CASE_INSENSITIVE | SO_CMP_SORTABLE), 0);
    /* verify sortable */
    EXPECT(so_cmp_s(SO, so("abcdeg")) < 0, true);
    EXPECT(so_cmp_s(so("abcdef"), SO) > 0, true);
    EXPECT(so_cmp_s(so("abcdef"), so("abcdeg")) < 0, true);
    EXPECT(so_cmp_s(so("abcdeg"), so("abcdef")) > 0, true);
    EXPECT(so_cmp_s(so("abcde"), so("abcdeg")) < 0, true);
    EXPECT(so_cmp_s(so("abcdeg"), so("abcde")) > 0, true);
    /* the same .. but actually calling the functions */
    EXPECT(so_cmp_p(&so("some string"), &so("some string")), 0);
    EXPECT(so_cmp0_p(&so("some string"), &so("some")), 0);
    EXPECT(so_cmpE_p(&so("some string"), &so("string")), 0);
    EXPECT(so_cmp_ip(&so("SoMe StRiNg"), &so("sOmE sTrInG")), 0);
    EXPECT(so_cmp0_ip(&so("SoMe StRiNg"), &so("sOmE")), 0);
    EXPECT(so_cmpE_ip(&so("sOmE sTrInG"), &so("StRiNg")), 0);
    EXPECT(so_cmp_sp(&so("some string"), &so("some string")), 0);
    EXPECT(so_cmp0_sp(&so("some string"), &so("some")), 0);
    EXPECT(so_cmpE_sp(&so("some string"), &so("string")), 0);
    EXPECT(so_cmp_isp(&so("SoMe StRiNg"), &so("sOmE sTrInG")), 0);
    EXPECT(so_cmp0_isp(&so("SoMe StRiNg"), &so("sOmE")), 0);
    EXPECT(so_cmpE_isp(&so("sOmE sTrInG"), &so("StRiNg")), 0);
    /* too short left side.. */
    NEXPECT(so_cmp0_p(&so("some"), &so("some string")), 0);
    NEXPECT(so_cmpE_p(&so("string"), &so("some string")), 0);
    NEXPECT(so_cmp0_ip(&so("sOmE"), &so("SoMe StRiNg")), 0);
    NEXPECT(so_cmpE_ip(&so("StRiNg"), &so("sOmE sTrInG")), 0);
    NEXPECT(so_cmp0_sp(&so("some"), &so("some string")), 0);
    NEXPECT(so_cmpE_sp(&so("string"), &so("some string")), 0);
    NEXPECT(so_cmp0_isp(&so("sOmE"), &so("SoMe StRiNg")), 0);
    NEXPECT(so_cmpE_isp(&so("StRiNg"), &so("sOmE sTrInG")), 0);
    /* actual comparisons (different) */
    NEXPECT(so_cmp_p(&so("some string"), &so("xsome stringx")), 0);
    NEXPECT(so_cmp0_p(&so("xsome stringx"), &so("some")), 0);
    NEXPECT(so_cmpE_p(&so("xsome stringx"), &so("string")), 0);
    NEXPECT(so_cmp_ip(&so("SoMe StRiNg"), &so("xsOmE sTrInGx")), 0);
    NEXPECT(so_cmp0_ip(&so("xSoMe StRiNgx"), &so("sOmE")), 0);
    NEXPECT(so_cmpE_ip(&so("xsOmE sTrInGx"), &so("StRiNg")), 0);
    NEXPECT(so_cmp_sp(&so("some string"), &so("xsome stringx")), 0);
    NEXPECT(so_cmp0_sp(&so("xsome stringx"), &so("some")), 0);
    NEXPECT(so_cmpE_sp(&so("xsome stringx"), &so("string")), 0);
    NEXPECT(so_cmp_isp(&so("SoMe StRiNg"), &so("xsOmE sTrInGx")), 0);
    NEXPECT(so_cmp0_isp(&so("xSoMe StRiNgx"), &so("sOmE")), 0);
    NEXPECT(so_cmpE_isp(&so("xsOmE sTrInGx"), &so("StRiNg")), 0);
    /* too short left side.. */
    NEXPECT(so_cmp0_p(&so("some"), &so("xsome stringx")), 0);
    NEXPECT(so_cmpE_p(&so("string"), &so("xsome stringx")), 0);
    NEXPECT(so_cmp0_ip(&so("sOmE"), &so("xSoMe StRiNgx")), 0);
    NEXPECT(so_cmpE_ip(&so("StRiNg"), &so("xsOmE sTrInGx")), 0);
    NEXPECT(so_cmp0_sp(&so("some"), &so("xsome stringx")), 0);
    NEXPECT(so_cmpE_sp(&so("string"), &so("xsome stringx")), 0);
    NEXPECT(so_cmp0_isp(&so("sOmE"), &so("xSoMe StRiNgx")), 0);
    NEXPECT(so_cmpE_isp(&so("StRiNg"), &so("xsOmE sTrInGx")), 0);
    /* invalid */
    NEXPECT(so_cmpx_p(&so("sOmE sTrInG"), &so("StRiNg"), SO_CMP_END | SO_CMP_BEGIN | SO_CMP_CASE_INSENSITIVE), 0);
    return 0;
}

