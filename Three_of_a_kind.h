#ifndef THREE_OF_A_KIND_H
#define THREE_OF_A_KIND_H

#include "Field.h"

class ThreeOfAKind : Field{

public:

    // just say that we use overlapped operator from the above class
    using Field::operator+;
    using Field::operator==;
    using Field::operator!=;
    using Field::operator=;

    ThreeOfAKind(){
        field_value = -1;
    }

    bool valid_input(const std::vector<Dice>& input) const override ;
    void calculate_field_value(const std::vector<Dice>& selected_dices) override ;

    // TODO delete function after finished testing classes
    int get_field_value() const{
        return field_value;
    }

};

#endif
