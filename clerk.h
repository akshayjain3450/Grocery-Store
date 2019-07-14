/************************************************************************************
 *                                                                                  *
 *    Code by : Group A                                                             *
 *    Code : Clerk Class. It inherits dataClass to acces data of the shop.          *
 *                                                                                  *
 ************************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#ifndef _CLERK_H
#define _CLERK_H
#include "dataClass.h"

using namespace std;

//Class definition
class clerk : protected items {

public:

  /* Getters */

  // To acess the item code
  char* get_code () { return items::get_code (); }
  // To acess the item quantity
  float get_quantity () { return items::get_quantity (); }

  /* Setter */

  // to set item Code
  void set_code (char code [10]) { items::set_code (code); }
  // to set item name
  void set_name (char name [20]) { items::set_name (name); }
  // to set item price
  void set_price (float price) { items::set_price (price); }
  // to set item quantity
  void set_quantity (int quantity) { items::set_quantity (quantity); }

  // To display the items
  void display_item ();

};

void clerk::display_item () {

    std::cout << std::endl;
    std::cout << "\t\t" << std::setw (10) << items::get_code () << "  ";
    std::cout << std::setw (20) << items::get_name () << "  ";
    std::cout << std::setw (10) << items::get_price () << "  ";
    std::cout << std::setw (10) << items::get_quantity ();

}

#endif
