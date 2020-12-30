#ifndef MINMAX_H
#define MINMAX_H

#include "Field.h"
#include "F_Number.h"

class MinMax : public Field{
public:
    MinMax()
    {
        field_value = -1;
    }

    void calculate_field_value(const std::vector<Dice>& selected_dices) override;

private:
    // this function should be private because we need it just in this class
    bool valid_input(const std::vector<Dice>& input) const override;
};

#endif
