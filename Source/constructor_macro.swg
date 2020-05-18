/*Use the macro SWIG_constructor to generate a swig constructor for metadata with at least 1 member*/

#define APPLY_MACRO_N_ARGS(M,...) \
ARGS_N__(__VA_ARGS__, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)(M, __VA_ARGS__)

#define ARGS_N__(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, N, ...) APPLY_MACRO_ ## N ## _ARGS

#define APPLY_MACRO_1_ARGS(M, X)      M(X)
#define APPLY_MACRO_2_ARGS(M, X, ...) M(X),APPLY_MACRO_1_ARGS(M, __VA_ARGS__)
#define APPLY_MACRO_3_ARGS(M, X, ...) M(X),APPLY_MACRO_2_ARGS(M, __VA_ARGS__)
#define APPLY_MACRO_4_ARGS(M, X, ...) M(X),APPLY_MACRO_3_ARGS(M, __VA_ARGS__)
#define APPLY_MACRO_5_ARGS(M, X, ...) M(X),APPLY_MACRO_4_ARGS(M, __VA_ARGS__)
#define APPLY_MACRO_6_ARGS(M, X, ...) M(X),APPLY_MACRO_5_ARGS(M, __VA_ARGS__)
#define APPLY_MACRO_7_ARGS(M, X, ...) M(X),APPLY_MACRO_6_ARGS(M, __VA_ARGS__)
#define APPLY_MACRO_8_ARGS(M, X, ...) M(X),APPLY_MACRO_7_ARGS(M, __VA_ARGS__)
#define APPLY_MACRO_9_ARGS(M, X, ...) M(X),APPLY_MACRO_8_ARGS(M, __VA_ARGS__)
#define APPLY_MACRO_10_ARGS(M, X, ...) M(X),APPLY_MACRO_9_ARGS(M, __VA_ARGS__)
#define APPLY_MACRO_11_ARGS(M, X, ...) M(X),APPLY_MACRO_10_ARGS(M, __VA_ARGS__)
#define APPLY_MACRO_12_ARGS(M, X, ...) M(X),APPLY_MACRO_11_ARGS(M, __VA_ARGS__)


%define SWIG_Constructor(class_name, args...)

#define GET_MEMBER_TYPE(MEMBER) decltype(class_name ## :: ## MEMBER) MEMBER

%extend class_name {
class_name(APPLY_MACRO_N_ARGS(GET_MEMBER_TYPE, args)) {
    return new class_name{args};
}
};

#undef GET_MEMBER_TYPE
%enddef