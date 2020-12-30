#ifndef C_FROMMIDDLE_H
#define C_FROMMIDDLE_H

#include "Column.h"

class C_FromMiddle : public Column {
 public:
  C_FromMiddle() = default;
  C_FromMiddle(bool *announcement_ptr, Fields *field_announced_ptr,
               int *number_of_filled_columns);

  bool valid_order(Fields type_of_current) const override;
};

#endif