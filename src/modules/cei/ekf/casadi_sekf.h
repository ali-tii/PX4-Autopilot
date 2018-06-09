/* This file was automatically generated by CasADi.
   The CasADi copyright holders make no ownership claim of its contents. */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef casadi_real
#define casadi_real double
#endif

#ifndef casadi_int
#define casadi_int long long int
#endif

#include <casadi/mem.h>
int x_dot(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void x_dot_incref(void);
void x_dot_decref(void);
casadi_int x_dot_n_out(void);
casadi_int x_dot_n_in(void);
const char* x_dot_name_in(casadi_int i);
const char* x_dot_name_out(casadi_int i);
const casadi_int* x_dot_sparsity_in(casadi_int i);
const casadi_int* x_dot_sparsity_out(casadi_int i);
int x_dot_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* x_dot_functions(void);
int P_dot(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void P_dot_incref(void);
void P_dot_decref(void);
casadi_int P_dot_n_out(void);
casadi_int P_dot_n_in(void);
const char* P_dot_name_in(casadi_int i);
const char* P_dot_name_out(casadi_int i);
const casadi_int* P_dot_sparsity_in(casadi_int i);
const casadi_int* P_dot_sparsity_out(casadi_int i);
int P_dot_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* P_dot_functions(void);
int correct(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void correct_incref(void);
void correct_decref(void);
casadi_int correct_n_out(void);
casadi_int correct_n_in(void);
const char* correct_name_in(casadi_int i);
const char* correct_name_out(casadi_int i);
const casadi_int* correct_sparsity_in(casadi_int i);
const casadi_int* correct_sparsity_out(casadi_int i);
int correct_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* correct_functions(void);
int cond(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void cond_incref(void);
void cond_decref(void);
casadi_int cond_n_out(void);
casadi_int cond_n_in(void);
const char* cond_name_in(casadi_int i);
const char* cond_name_out(casadi_int i);
const casadi_int* cond_sparsity_in(casadi_int i);
const casadi_int* cond_sparsity_out(casadi_int i);
int cond_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* cond_functions(void);
int P_init(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void P_init_incref(void);
void P_init_decref(void);
casadi_int P_init_n_out(void);
casadi_int P_init_n_in(void);
const char* P_init_name_in(casadi_int i);
const char* P_init_name_out(casadi_int i);
const casadi_int* P_init_sparsity_in(casadi_int i);
const casadi_int* P_init_sparsity_out(casadi_int i);
int P_init_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* P_init_functions(void);
#ifdef __cplusplus
} /* extern "C" */
#endif
