#ifndef COMP_H
#define COMP_H

class comp
{
public:
    comp(double x, double y);
    comp(double x);
    comp operator+(comp oper);
    friend double sqmodul(comp oper);
    friend comp power(comp oper);
private:
    double re_, im_;
};

#endif // COMP_H
