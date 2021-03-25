#ifndef STIMULUS_OPERATOR_H
#define STIMULUS_OPERATOR_H
template<typename R>
class Operator{
public:
    Operator(){}
    virtual R execute() = 0;
};
#endif //STIMULUS_OPERATOR_H
