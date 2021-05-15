#include "headers/MinJerk.h"

Vector3d* MinJerk::cubicInterpolate(Vector3d theta_ini, Vector3d theta_f, Vector3d theta_dot_ini, Vector3d theta_dot_f, double tf){
    /* 
        Returns Cubic Polynomial with the Given Boundary Conditions
        https://www.tu-chemnitz.de/informatik//KI/edu/robotik/ws2016/lecture-tg%201.pdf
    */
    Vector3d* coefs = new Vector3d[4]; // a0, a1, a2, a3
    coefs[0] = theta_ini;
    coefs[1] = theta_dot_ini;
    coefs[2] = 3/pow(tf,2) * (theta_f - theta_ini) - 1/tf * (2 * theta_dot_ini + theta_dot_f);
    coefs[3] = -2/pow(tf,3) * (theta_f - theta_ini) + 1/pow(tf,2) * (theta_dot_ini + theta_dot_f);
    return coefs;
}

Vector3d* MinJerk::poly6Interpolate(Vector3d x_ini, Vector3d x_mid, Vector3d x_f, double tf){
    /* 
        This function fits a 5th order (C2) Polynomial to given given inputs
        Inputs : X0, Xmid, Xf   !Xd, Xdd at begining and end are assumed to be zero!
    */
    
    Vector3d* a = new Vector3d[7];
    a[0] = x_ini;
    a[1] = Vector3d::Zero(3);
    a[2] = Vector3d::Zero(3);
    a[3] = -2/pow(tf,3) * (21 * x_ini + 11 * x_f - 32 * x_mid);
    a[4] = 3/pow(tf,4) * (37 * x_ini + 27 * x_f - 64 * x_mid);
    a[5] = -6/pow(tf,5) * (17 * x_ini + 15 * x_f - 32 * x_mid);
    a[6] = 3/pow(tf,4) * (x_ini + x_f - 2 * x_mid);
    return a;
}