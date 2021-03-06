#include "Human_player.h"

#include <iostream>

#include "../NetworkCommon/common.h"
#include "Dice.h"

// Function that finds number of same dices.
int number_of_same_dices(int number, std::vector<Dice>& dices) {
  int number_of_same = 0;

  for (const auto& dice : dices) {
    if (dice.get_value() == number) number_of_same++;
  }

  return number_of_same;
}

// Function that gets sum of dices.
int sum_of_dices(std::vector<Dice>& dices) {
  int sum = 0;
  for (const auto& dice : dices) {
    sum += dice.get_value();
  }

  return sum;
}

// Check if the given vector of dices gives maximum value for field.
bool is_maximum(Fields field, std::vector<Dice>& dices, int number_of_throws) {
  switch (field) {
    case Fields::Number_1: {
      return 5 == number_of_same_dices(1, dices);
    }
    case Fields::Number_2: {
      return 5 == number_of_same_dices(2, dices);
    }
    case Fields::Number_3: {
      return 5 == number_of_same_dices(3, dices);
    }
    case Fields::Number_4: {
      return 5 == number_of_same_dices(4, dices);
    }
    case Fields::Number_5: {
      return 5 == number_of_same_dices(5, dices);
    }
    case Fields::Number_6: {
      return 5 == number_of_same_dices(6, dices);
    }
    case Fields::Maximum: {
      return 30 == sum_of_dices(dices);
    }
    case Fields::Minimum: {
      return 5 == sum_of_dices(dices);
    }
    case Fields::Straight: {
      return 1 == number_of_throws;
    }
    case Fields::ThreeOfAKind: {
      return 18 == sum_of_dices(dices);
    }
    case Fields::Full: {
      return 28 == sum_of_dices(dices);
    }
    case Fields::Poker: {
      return 24 == sum_of_dices(dices);
    }
    case Fields::Yamb: {
      return 30 == sum_of_dices(dices);
    }
    case Fields::None: {
      return false;
    }
  }

  return false;
}

bool HumanPlayer::write_on_ticket(std::vector<Dice> dices, Fields field,
                                  Columns column, int number_of_throws) {
  switch (column) {
    case Columns::FromUp: {
      if (*announcement) {
        // Other player announce something.
        return false;
      }

      // Check if the field can be written.
      if (get_ticket().getFromUpToDown().valid_order(field)) {
        get_ticket().getFromUpToDown().write_in_column(dices, field,
                                                       number_of_throws);

        // Convert enum to field and column number.
        int row = static_cast<int>(field);
        int col = static_cast<int>(column);
        if (get_ticket().get_ticket_value()[row][col] == -1) return false;

        // Check if the column is fully filled, and increase number of filled
        // columns.
        if (get_ticket().getFromUpToDown().column_full_filled())
          *number_of_filled_columns += 1;

        return true;
      } else {
        // Can't write in this field.
        return false;
      }
    }
    case Columns::Free: {
      if (*announcement) {
        // Other player announce something.
        return false;
      }

      // Check if the field can be written.
      if (get_ticket().getFree().valid_order(field)) {
        get_ticket().getFree().write_in_column(dices, field, number_of_throws);

        int row = static_cast<int>(field);
        int col = static_cast<int>(column);
        if (get_ticket().get_ticket_value()[row][col] == -1) return false;

        // Check if the column is fully filled, and increase number of filled
        // columns.
        if (get_ticket().getFree().column_full_filled())
          *number_of_filled_columns += 1;

        return true;
      } else {
        // Can't write in this field.
        return false;
      }
    }
    case Columns::FromBottom: {
      if (*announcement) {
        // Other player announce something.
        return false;
      }

      // Check if the field can be written.
      if (get_ticket().getFromBottom().valid_order(field)) {
        get_ticket().getFromBottom().write_in_column(dices, field,
                                                     number_of_throws);

        int row = static_cast<int>(field);
        int col = static_cast<int>(column);
        if (get_ticket().get_ticket_value()[row][col] == -1) return false;

        // Check if the column is fully filled, and increase number of filled
        // columns.
        if (get_ticket().getFromBottom().column_full_filled())
          *number_of_filled_columns += 1;

        return true;
      } else {
        // Can't write in this field.
        return false;
      }
    }
    case Columns::Hand: {
      if (*announcement) {
        // Other player announce something.
        return false;
      }

      // Hand is only valid if we play it from the first throw.
      if (number_of_throws != 1) {
        // If number of throws is greater then 1 the field value must be 0
        // so we just send zero vector to be written in column field.
        std::vector<Dice> zero_vector;
        zero_vector.emplace_back(0);
        get_ticket().getHand().write_in_column(zero_vector, field,
                                               number_of_throws);

        return true;
      }

      // Check if the field can be written.
      if (get_ticket().getHand().valid_order(field)) {
        get_ticket().getHand().write_in_column(dices, field, number_of_throws);

        int row = static_cast<int>(field);
        int col = static_cast<int>(column);
        if (get_ticket().get_ticket_value()[row][col] == -1) return false;

        // Check if the column is fully filled, and increase number of filled
        // columns.
        if (get_ticket().getHand().column_full_filled())
          *number_of_filled_columns += 1;

        return true;
      } else {
        // Can't write in this field.
        return false;
      }
    }
    case Columns::FromMiddle: {
      if (*announcement) {
        // Other player announce something.
        return false;
      }

      // Check if the field can be written.
      if (get_ticket().getFromMiddle().valid_order(field)) {
        get_ticket().getFromMiddle().write_in_column(dices, field,
                                                     number_of_throws);

        int row = static_cast<int>(field);
        int col = static_cast<int>(column);
        if (get_ticket().get_ticket_value()[row][col] == -1) return false;

        // Check if the column is fully filled, and increase number of filled
        // columns.
        if (get_ticket().getFromMiddle().column_full_filled())
          *number_of_filled_columns += 1;

        return true;
      } else {
        // Can't write in this field.
        return false;
      }
    }
    case Columns::ToMiddle: {
      if (*announcement) {
        // Other player announce something.
        return false;
      }

      // Check if the field can be written.
      if (get_ticket().getToMiddle().valid_order(field)) {
        get_ticket().getToMiddle().write_in_column(dices, field,
                                                   number_of_throws);

        int row = static_cast<int>(field);
        int col = static_cast<int>(column);
        if (get_ticket().get_ticket_value()[row][col] == -1) return false;

        // Check if the column is fully filled, and increase number of filled
        // columns.
        if (get_ticket().getToMiddle().column_full_filled())
          *number_of_filled_columns += 1;

        return true;
      } else {
        // Can't write in this field.
        return false;
      }
    }
    case Columns::Announcement: {
      if (!*announcement) {
        // Player must announce field that he want to play.
        return false;
      }

      // Check if the field can be written.
      if (get_ticket().getAnnouncement().valid_order(field)) {
        get_ticket().getAnnouncement().write_in_column(dices, field,
                                                       number_of_throws);

        int row = static_cast<int>(field);
        int col = static_cast<int>(column);
        if (get_ticket().get_ticket_value()[row][col] == -1) return false;

        // Check if the column is fully filled, and increase number of filled
        // columns.
        if (get_ticket().getAnnouncement().column_full_filled())
          *number_of_filled_columns += 1;

        return true;
      } else {
        // Can't write in this field.
        return false;
      }
    }
    case Columns::Respond: {
      if (!*announcement) {
        // Other player didn't announce anything. You can't play this.
        return false;
      }

      // Check if the field can be written.
      if (get_ticket().getRespond().valid_order(field)) {
        // Write in ticket and then say that player responded to announcement.
        get_ticket().getRespond().write_in_column(dices, field,
                                                  number_of_throws);

        int row = static_cast<int>(field);
        int col = static_cast<int>(column);
        if (get_ticket().get_ticket_value()[row][col] == -1) return false;

        // Check if the column is fully filled, and increase number of filled
        // columns.
        if (get_ticket().getRespond().column_full_filled())
          *number_of_filled_columns += 1;

        // Player has successfully respond on announcement.
        respond_announce();

        return true;
      } else {
        // Can't write in this field.
        return false;
      }
    }
    case Columns::Checkout: {
      if (*announcement) {
        // Something was announced previously.
        return false;
      }
      // Check if the field can be written.
      if (get_ticket().getCheckout().valid_order(field)) {
        get_ticket().getCheckout().write_in_column(dices, field,
                                                   number_of_throws);

        int row = static_cast<int>(field);
        int col = static_cast<int>(column);
        if (get_ticket().get_ticket_value()[row][col] == -1) return false;

        // check if the column is fully filled, and increase number of filled
        // columns
        if (get_ticket().getAnnouncement().column_full_filled())
          *number_of_filled_columns += 1;

        return true;
      } else {
        // Can't write in this field.
        return false;
      }
    }
    case Columns::Maximum: {
      if (*announcement) {
        // Something was announced previously.
        return false;
      }
      // Check if the field can be written.
      if (get_ticket().getMaximum().valid_order(field)) {
        // Check if the given dices gives maximum for that field.
        if (is_maximum(field, dices, number_of_throws)) {
          get_ticket().getMaximum().write_in_column(dices, field,
                                                    number_of_throws);

          int row = static_cast<int>(field);
          int col = static_cast<int>(column);
          if (get_ticket().get_ticket_value()[row][col] == -1) return false;
        } else {
          // If dices doesn't give maximum for chosen field the field value must
          // be 0 so we just send zero vector to be written in column field.
          std::vector<Dice> zero_vector;
          zero_vector.emplace_back(0);
          get_ticket().getMaximum().write_in_column(zero_vector, field,
                                                    number_of_throws);
        }

        // Check if the column is fully filled, and increase number of filled
        // columns.
        if (get_ticket().getMaximum().column_full_filled())
          *number_of_filled_columns += 1;

        return true;
      } else {
        return false;
      }
    }
    case Columns::None: {
      return false;
    }
    default:
      return false;
  }
}

bool HumanPlayer::announce(Fields field) {
  if (*announcement) {
    // Something is already announced.
    return false;
  }

  // Set communication fields for announcement.
  *announcement = true;
  *field_announced = field;

  return true;
}

// Reset announcement fields to None.
void HumanPlayer::respond_announce() {
  *announcement = false;
  *field_announced = Fields::None;
}
