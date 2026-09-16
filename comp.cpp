#include "comp.h"
//#include "cmath"

comp::comp(double x) {
    re_ = x;
    im_ = 0;
}

comp::comp(double x, double y) {
    re_ = x;
    im_ = y;
}

comp comp::operator+(comp oper) {
    return comp(re_ + oper.re_, im_ + oper.im_);
}

double sqmodul(comp oper) {
    return (oper.re_ * oper.re_) + (oper.im_ * oper.im_);
}

comp power(comp oper) {
    return comp(oper.re_ * oper.re_ - oper.im_ * oper.im_, 2 * oper.re_ * oper.im_);
}
