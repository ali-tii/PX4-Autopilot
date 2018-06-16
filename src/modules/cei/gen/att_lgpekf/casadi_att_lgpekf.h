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
int mrp_shadow(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void mrp_shadow_incref(void);
void mrp_shadow_decref(void);
casadi_int mrp_shadow_n_out(void);
casadi_int mrp_shadow_n_in(void);
const char* mrp_shadow_name_in(casadi_int i);
const char* mrp_shadow_name_out(casadi_int i);
const casadi_int* mrp_shadow_sparsity_in(casadi_int i);
const casadi_int* mrp_shadow_sparsity_out(casadi_int i);
int mrp_shadow_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* mrp_shadow_functions(void);
int mrp_to_quat(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void mrp_to_quat_incref(void);
void mrp_to_quat_decref(void);
casadi_int mrp_to_quat_n_out(void);
casadi_int mrp_to_quat_n_in(void);
const char* mrp_to_quat_name_in(casadi_int i);
const char* mrp_to_quat_name_out(casadi_int i);
const casadi_int* mrp_to_quat_sparsity_in(casadi_int i);
const casadi_int* mrp_to_quat_sparsity_out(casadi_int i);
int mrp_to_quat_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* mrp_to_quat_functions(void);
int quat_to_euler(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void quat_to_euler_incref(void);
void quat_to_euler_decref(void);
casadi_int quat_to_euler_n_out(void);
casadi_int quat_to_euler_n_in(void);
const char* quat_to_euler_name_in(casadi_int i);
const char* quat_to_euler_name_out(casadi_int i);
const casadi_int* quat_to_euler_sparsity_in(casadi_int i);
const casadi_int* quat_to_euler_sparsity_out(casadi_int i);
int quat_to_euler_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* quat_to_euler_functions(void);
int predict_W(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void predict_W_incref(void);
void predict_W_decref(void);
casadi_int predict_W_n_out(void);
casadi_int predict_W_n_in(void);
const char* predict_W_name_in(casadi_int i);
const char* predict_W_name_out(casadi_int i);
const casadi_int* predict_W_sparsity_in(casadi_int i);
const casadi_int* predict_W_sparsity_out(casadi_int i);
int predict_W_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* predict_W_functions(void);
int x_predict(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void x_predict_incref(void);
void x_predict_decref(void);
casadi_int x_predict_n_out(void);
casadi_int x_predict_n_in(void);
const char* x_predict_name_in(casadi_int i);
const char* x_predict_name_out(casadi_int i);
const casadi_int* x_predict_sparsity_in(casadi_int i);
const casadi_int* x_predict_sparsity_out(casadi_int i);
int x_predict_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* x_predict_functions(void);
int correct_accel(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void correct_accel_incref(void);
void correct_accel_decref(void);
casadi_int correct_accel_n_out(void);
casadi_int correct_accel_n_in(void);
const char* correct_accel_name_in(casadi_int i);
const char* correct_accel_name_out(casadi_int i);
const casadi_int* correct_accel_sparsity_in(casadi_int i);
const casadi_int* correct_accel_sparsity_out(casadi_int i);
int correct_accel_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* correct_accel_functions(void);
int correct_mag(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void correct_mag_incref(void);
void correct_mag_decref(void);
casadi_int correct_mag_n_out(void);
casadi_int correct_mag_n_in(void);
const char* correct_mag_name_in(casadi_int i);
const char* correct_mag_name_out(casadi_int i);
const casadi_int* correct_mag_sparsity_in(casadi_int i);
const casadi_int* correct_mag_sparsity_out(casadi_int i);
int correct_mag_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* correct_mag_functions(void);
int init(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem);
void init_incref(void);
void init_decref(void);
casadi_int init_n_out(void);
casadi_int init_n_in(void);
const char* init_name_in(casadi_int i);
const char* init_name_out(casadi_int i);
const casadi_int* init_sparsity_in(casadi_int i);
const casadi_int* init_sparsity_out(casadi_int i);
int init_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w);
casadi_functions* init_functions(void);
#ifdef __cplusplus
} /* extern "C" */
#endif
