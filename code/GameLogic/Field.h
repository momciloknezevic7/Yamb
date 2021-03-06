#ifndef FIELD_H
#define FIELD_H

#include <vector>

#include "Dice.h"

// Enum that defines types of fields.
enum class Fields {
  Number_1,
  Number_2,
  Number_3,
  Number_4,
  Number_5,
  Number_6,
  Maximum,
  Minimum,
  Straight,
  ThreeOfAKind,
  Full,
  Poker,
  Yamb,
  None  // Extra field that helps with announcement.
};

// Class that acts like an interface.
class Field {
 public:
  // Functions that we need to implement in every field.
  virtual bool valid_input(const std::vector<Dice>& input) const = 0;
  virtual void calculate_field_value(
      const std::vector<Dice>& selected_dices) = 0;

  // Universal getter.
  virtual int get_field_value() const { return field_value; }

  Field& operator=(int other) {
    this->field_value = other;
    return *this;
  }

  friend int operator+(const Field& a, const Field& b) {
    return a.field_value + b.field_value;
  }
  friend int operator+(const Field& a, int b) { return a.field_value + b; }
  friend int operator+(int a, const Field& b) { return a + b.field_value; }

  friend int operator-(const Field& a, const Field& b) {
    return a.field_value - b.field_value;
  }
  friend int operator-(int a, const Field& b) { return a - b.field_value; }
  friend int operator-(const Field& a, int b) { return a.field_value - b; }

  friend int operator*(const Field& a, const Field& b) {
    return a.field_value * b.field_value;
  }
  friend int operator*(const Field& a, int b) { return a.field_value * b; }
  friend int operator*(int a, const Field& b) { return a * b.field_value; }

  friend bool operator==(const Field& a, const Field& b) {
    return a.field_value == b.field_value;
  }
  friend bool operator==(const Field& a, int b) { return a.field_value == b; }
  friend bool operator==(int a, const Field& b) { return a == b.field_value; }

  friend bool operator!=(const Field& a, const Field& b) { return !(a == b); }
  friend bool operator!=(const Field& a, int b) { return !(a == b); }
  friend bool operator!=(int a, const Field& b) { return !(a == b); }

  // Function that gets field type by the row number.
  static Fields row_to_enum(int8_t row) {
    Fields field;

    switch (row) {
      case 0:
        field = Fields::Number_1;
        break;
      case 1:
        field = Fields::Number_2;
        break;
      case 2:
        field = Fields::Number_3;
        break;
      case 3:
        field = Fields::Number_4;
        break;
      case 4:
        field = Fields::Number_5;
        break;
      case 5:
        field = Fields::Number_6;
        break;
      case 7:
        field = Fields::Maximum;
        break;
      case 8:
        field = Fields::Minimum;
        break;
      case 10:
        field = Fields::Straight;
        break;
      case 11:
        field = Fields::ThreeOfAKind;
        break;
      case 12:
        field = Fields::Full;
        break;
      case 13:
        field = Fields::Poker;
        break;
      case 14:
        field = Fields::Yamb;
        break;
    }

    return field;
  }

 protected:
  // Here we store value of the field.
  int field_value;
};

#endif
