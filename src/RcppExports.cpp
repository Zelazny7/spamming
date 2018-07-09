// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// ngCMatrix_to_array_test
SEXP ngCMatrix_to_array_test(Rcpp::S4 obj);
RcppExport SEXP _spamming_ngCMatrix_to_array_test(SEXP objSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type obj(objSEXP);
    rcpp_result_gen = Rcpp::wrap(ngCMatrix_to_array_test(obj));
    return rcpp_result_gen;
END_RCPP
}
// hamming_ngCMatrix_x_only
Rcpp::IntegerVector hamming_ngCMatrix_x_only(Rcpp::S4 obj);
RcppExport SEXP _spamming_hamming_ngCMatrix_x_only(SEXP objSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type obj(objSEXP);
    rcpp_result_gen = Rcpp::wrap(hamming_ngCMatrix_x_only(obj));
    return rcpp_result_gen;
END_RCPP
}
// hamming_ngCMatrix_x_and_y
IntegerMatrix hamming_ngCMatrix_x_and_y(Rcpp::S4 objx, Rcpp::S4 objy);
RcppExport SEXP _spamming_hamming_ngCMatrix_x_and_y(SEXP objxSEXP, SEXP objySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type objx(objxSEXP);
    Rcpp::traits::input_parameter< Rcpp::S4 >::type objy(objySEXP);
    rcpp_result_gen = Rcpp::wrap(hamming_ngCMatrix_x_and_y(objx, objy));
    return rcpp_result_gen;
END_RCPP
}
// hamming_find_mode
S4 hamming_find_mode(Rcpp::S4 obj);
RcppExport SEXP _spamming_hamming_find_mode(SEXP objSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type obj(objSEXP);
    rcpp_result_gen = Rcpp::wrap(hamming_find_mode(obj));
    return rcpp_result_gen;
END_RCPP
}
// test_conversion
S4 test_conversion(Rcpp::S4 obj);
RcppExport SEXP _spamming_test_conversion(SEXP objSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type obj(objSEXP);
    rcpp_result_gen = Rcpp::wrap(test_conversion(obj));
    return rcpp_result_gen;
END_RCPP
}
// BMM_v2
SEXP BMM_v2(Rcpp::S4 obj, int K, int max_iter, int verbose);
RcppExport SEXP _spamming_BMM_v2(SEXP objSEXP, SEXP KSEXP, SEXP max_iterSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type obj(objSEXP);
    Rcpp::traits::input_parameter< int >::type K(KSEXP);
    Rcpp::traits::input_parameter< int >::type max_iter(max_iterSEXP);
    Rcpp::traits::input_parameter< int >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(BMM_v2(obj, K, max_iter, verbose));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_spamming_ngCMatrix_to_array_test", (DL_FUNC) &_spamming_ngCMatrix_to_array_test, 1},
    {"_spamming_hamming_ngCMatrix_x_only", (DL_FUNC) &_spamming_hamming_ngCMatrix_x_only, 1},
    {"_spamming_hamming_ngCMatrix_x_and_y", (DL_FUNC) &_spamming_hamming_ngCMatrix_x_and_y, 2},
    {"_spamming_hamming_find_mode", (DL_FUNC) &_spamming_hamming_find_mode, 1},
    {"_spamming_test_conversion", (DL_FUNC) &_spamming_test_conversion, 1},
    {"_spamming_BMM_v2", (DL_FUNC) &_spamming_BMM_v2, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_spamming(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
