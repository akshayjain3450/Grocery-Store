/*********************************************************************************
 *                                                                               *
 *    Code by : Group A                                                          *
 *    Code : Main grocery stoe interface                                         *
 *                                                                               *
 *********************************************************************************/

#include <iostream>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include "clerk.h"
#include "customer.h"

 void customer_acces ();
 void clerk_acces ();
 int getch();
 string getpass(const char*, bool);

 using namespace std;

 int main(int argc, char const *argv[]) {

     int acc;

     do {

         system ("clear");

         std::cout << "\n\n\t\t\t Access Menu";
         std::cout << "\n\n\t 1. Customer";
         std::cout << "\n\t 2. Clerk";
         std::cout << "\n\t 3. Exit";
         std::cout << "\n\n\t Enter the choice : ";
         std::cin >> acc;

         switch (acc) {

             case 1 : customer_acces ();
                      break;

             case 2 : clerk_acces ();
                      break;

             case 3 : exit (0);

             default : std::cout << "\n\t Wrong Choice!!" << '\n';
                       cin.ignore ();
                       getchar ();

         }

     } while (1);

     return 0;
 }

 void customer_acces () {

     int option;
     fstream item, cart;
     customer cstmr;

     do {

         system ("clear");

         std::cout << "\n\n\n\t\t\t\t Welcome to ABC grocery store : customer";
         std::cout << "\n\n\t\t Menu";
         std::cout << "\n\n\t 1. Display item list";
         std::cout << "\n\t 2. Add item to cart";
         std::cout << "\n\t 3. Delete item from cart";
         std::cout << "\n\t 4. Display cart";
         std::cout << "\n\t 5. Bill";
         std::cout << "\n\t 6. Exit";
         std::cout << "\n\n\t Enter choice : ";
         std::cin >> option;

         switch (option) {

             case 1 : item.open ("/home/ankit/Desktop/c++ project/items.dat", ios::in | ios::binary);
                      if (item.fail ()) {
                          std::cout << "\n\n\t File does not exist" << '\n';
                          std::cin.ignore ();
                          getchar ();
                          break;
                      }
                      item.seekg (0);
                      system ("clear");
                      std::cout << "\t======================================================================" << std::endl;
                      std::cout << "\t\t" << std::setw (10) << "Item Code" << "  ";
                      std::cout << std::setw (20) << "Item Name" << "  ";
                      std::cout << std::setw (10) << "Item Price";
                      std::cout << std::endl << "\t======================================================================";
                      while (1) {
                          item.read ((char*) &cstmr, sizeof (cstmr));
                          if (item.eof ())
                            break;

                          cstmr.display_catalog ();
                      }
                      item.close ();
                      std::cin.ignore ();
                      getchar ();
                      break;

             case 2 :{
                       cart.open("/home/ankit/Desktop/c++ project/cart.txt", ios::out | ios::app);
                       if (cart.fail ()) {
                           std::cout << "\n\n\t Cart does not exist" << '\n';
                           std::cin.ignore ();
                           getchar ();
                           break;
                       }
                       system ("clear");
                       char ans = 'y';
                       int flag = 0;
                       char cd [10];
                       int qty;

                       do {
                           item.open ("/home/ankit/Desktop/c++ project/items.dat", ios::in | ios::binary);
                           if (item.fail ()) {
                               std::cout << "\n\n\t file does not exist" << '\n';
                               std::cin.ignore ();
                               getchar ();
                               break;
                           }

                           flag = 0;
                           system ("clear");
                           cout<<"\n\n\t Enter the Code of the item : ";
                           cin>>cd;
                           item.seekg (0);
                           while (1) {
                               item.read((char*) &cstmr, sizeof(cstmr));
                               if (item.eof ())
                                break;
                               if(!std::strcmp (cstmr.get_code(), cd)) {
                                   flag++;
                                   std::cout << "\t======================================================================" << std::endl;
                                   std::cout << "\t\t" << std::setw (10) << "Item Code" << "  ";
                                   std::cout << std::setw (20) << "Item Name" << "  ";
                                   std::cout << std::setw (10) << "Item Price";
                                   std::cout << std::endl << "\t======================================================================";
                                   cstmr.display_catalog ();
                                   std::cout << "\n\n\t Enter the quantity needed : ";
                                   cin >> qty;
                                   while (cstmr.get_quantity () < qty) {
                                       std::cout << "\n\n\t The quantity entered is not possible" << '\n';
                                       std::cout << "\tMax possible quantity is : " << cstmr.get_quantity () << '\n';
                                       std::cout << "\tEnter new quantity : ";
                                       std::cin >> qty;
                                   }
                                   cstmr.set_quantity(qty);
                                   if (qty > 0) {
                                       cart.write((char*) &cstmr, sizeof(cstmr));
                                       std::cout << "\n\t Item added" << '\n';
                                       cin.ignore ();
                                       getchar ();
                                   }
                               }
                           }
                           if (!flag) {
                               std::cout << "\n\t Item with that code does not exist" << '\n';
                           }
                           flag= 0;
                           std::cout << "\n\t Do you wanna add more items? (Y/N) : ";
                           std::cin >> ans;
                           item.close();
                       } while (ans == 'y' || ans == 'Y');
                       cart.close();
                       break;
                   }

             case 3 :{ char cd [10];
                       char found='f',confirm='n';
                       cart.open("/home/ankit/Desktop/c++ project/cart.txt", ios::in);
                       if (cart.fail ()) {
                           std::cout << "\n\n\t cart does not exist" << '\n';
                           std::cin.ignore ();
                           getchar ();
                           break;
                       }
                       ofstream fout;
                       fout.open("/home/ankit/Desktop/c++ project/temp.txt",ios::out);
                       cout<<"\n\n\t Enter the code of the item you want to be deleted : ";
                       cin>>cd;
                       while(1) {
                           cart.read((char*)&cstmr,sizeof(cstmr));
                           if (cart.eof ())
                            break;
                           if(!std::strcmp (cstmr.get_code(), cd)) {
                               found='t';
                               std::cout << "\t======================================================================" << std::endl;
                               std::cout << "\t\t" << std::setw (10) << "Item Code" << "  ";
                               std::cout << std::setw (20) << "Item Name" << "  ";
                               std::cout << std::setw (10) << "Item Price";
                               std::cout << std::endl << "\t======================================================================";
                               cstmr.display_catalog ();
                               cout<<"\n\n\t Are you sure you want to delete this item? [y/n] : ";
                               cin>>confirm;
                               if(confirm=='n')
                                 fout.write((char*)&cstmr,sizeof(cstmr));
                             }
                             else
                                 fout.write((char*)&cstmr,sizeof(cstmr));
                       }
                       if(found=='f')
                          cout<<"\n\n\t Item not found";
                       cart.close();
                       fout.close();
                       remove("/home/ankit/Desktop/c++ project/cart.txt");
                       rename("/home/ankit/Desktop/c++ project/temp.txt","/home/ankit/Desktop/c++ project/cart.txt");
                       std::cin.ignore ();
                       getchar ();
                       break;
                     }

             case 4 : cart.open("/home/ankit/Desktop/c++ project/cart.txt", ios::in);
                      if (cart.fail ()) {
                          std::cout << "\n\n\t Cart does not exist" << '\n';
                          std::cin.ignore ();
                          getchar ();
                          break;
                      }
                      cart.seekg (0);
                      system ("clear");
                      std::cout << "\n\n\t\t\t CART" << '\n';
                      std::cout << "\t======================================================================" << std::endl;
                      std::cout << "\t\t" << std::setw (10) << "Item Code" << "  ";
                      std::cout << std::setw (20) << "Item Name" << "  ";
                      std::cout << std::setw (10) << "Item Price" << "  ";
                      std::cout << std::setw (10) << "Quantity" << '\n';
                      std::cout << std::endl << "\t======================================================================";
                      while(1) {
                          cart.read((char*) &cstmr, sizeof(cstmr));
                          if (cart.eof ())
                             break;
                             cstmr.display_catalog ();
                             std::cout << "  " << std::setw (10) << cstmr.get_quantity ();
                      }
                      cart.close();
                      std::cin.ignore ();
                      getchar ();
                      break;

             case 5 :{ float sum = 0;
                       item.open ("/home/ankit/Desktop/c++ project/items.dat", ios::in | ios::binary | ios::out | ios::ate);
                       if (item.fail ()) {
                           std::cout << "\n\n\t File does not exist" << '\n';
                           std::cin.ignore ();
                           getchar ();
                           break;
                       }
                       cart.open("/home/ankit/Desktop/c++ project/cart.txt", ios::in);
                       if (cart.fail ()) {
                           std::cout << "\n\n\t Cart does not exist" << '\n';
                           std::cin.ignore ();
                           item.close ();
                           getchar ();
                           break;
                       }
                       system ("clear");
                       clerk clrk;
                       cart.seekg (0);
                       std::cout << "\t======================================================================" << std::endl;
                       std::cout << "\t\t" << std::setw (10) << "Item Code" << "  ";
                       std::cout << std::setw (20) << "Item Name" << "  ";
                       std::cout << std::setw (10) << "Item Price" << "  ";
                       std::cout << std::setw (10) << "Quantity" << '\n';
                       std::cout << std::endl << "\t======================================================================";
                       while(1) {
                           cart.read((char*)&cstmr,sizeof(cstmr));
                           if (cart.eof ())
                              break;
                           cstmr.display_catalog ();
                           std::cout << "  " << std::setw (10) << cstmr.get_quantity ();
                           item.seekg (0);
                           while (1) {
                               item.read ((char*) &clrk, sizeof (clrk));
                               if (item.eof ())
                                  break;
                               if (!std::strcmp (clrk.get_code (), cstmr.get_code ())) {
                                   clrk.set_quantity (clrk.get_quantity () - cstmr.get_quantity ());
                                   item.seekp (-sizeof (clrk), ios::cur);
                                   item.write ((char*) &clrk, sizeof (clrk));
                                   break;
                               }
                           }
                           sum+=(cstmr.get_price() * cstmr.get_quantity ());
                       }
                       cout<<"\n\n\t The total amount is $ " << sum;
                       std::cin.ignore ();
                       getchar ();
                       cart.close ();
                       item.close ();
                       remove ("/home/ankit/Desktop/c++ project/cart.txt");
                       break;
                   }

             case 6 :   remove ("/home/ankit/Desktop/c++ project/cart.txt");
                        return;

             default : std::cout << "\n\t Wrong choice!" << '\n';
                       std::cin.ignore ();
                       getchar ();

         }

     } while (1);

 }

 // Clerk Function
 void clerk_acces () {

    const char *correct_password = "groupa";
     std::cin.ignore ();
     std::cout << std::endl;
     string password = getpass("Please enter the password: ",true);

     if (password != correct_password) {
         std::cout << "\n\n\t Wrong Password" << '\n';
         std::cin.ignore ();
         getchar ();
         return;
     }

     int option;
     clerk clrk;
     char code [10], name [20], ans;
     float price;
     int quantity;
     int size, flag = 0, pos;

     fstream item;
     item.open ("/home/ankit/Desktop/c++ project/items.dat", ios::in | ios::binary | ios::out | ios::app);
     item.close ();

     do {

         system ("clear");

         std::cout << "\n\n\n\t\t\t\t Welcome to ABC grocery store : Admin Access ";
         std::cout << "\n\n\t\t Menu";
         std::cout << "\n\n\t 1. Display item list";
         std::cout << "\n\t 2. Add items";
         std::cout << "\n\t 3. Delete item";
         std::cout << "\n\t 4. Modify item";
         std::cout << "\n\t 5. Exit";
         std::cout << "\n\n\t Enter the choice : ";
         std::cin >> option;

         switch (option) {

             case 1 : item.open ("/home/ankit/Desktop/c++ project/items.dat", ios::in | ios::binary);
                      if (item.fail ()) {
                          std::cout << "\nfile couldn't open ";
                          std::cin.ignore ();
                          getchar ();
                          break;
                      }
                      item.seekg (0, ios::beg);
                      system ("clear");
                      std::cout << "\t======================================================================" << std::endl;
                      std::cout << "\t\t" << std::setw (10) << "Item Code" << "  ";
                      std::cout << std::setw (20) << "Item Name" << "  ";
                      std::cout << std::setw (10) << "Item Price" << "  ";
                      std::cout << std::setw (10) << "Quantity";
                      std::cout << std::endl << "\t======================================================================";
                      while (1) {
                          item.read ((char*) &clrk, sizeof (clrk));
                          if (item.eof ())
                            break;
                          clrk.display_item ();
                      }
                      item.close ();
                      std::cin.ignore ();
                      getchar ();
                      break;

             case 2 : flag = 0;
                      item.open ("/home/ankit/Desktop/c++ project/items.dat", ios::in | ios::binary);
                      if (item.fail ()) {
                          std::cout << "\n\t File couldn't open";
                          std::cin.ignore ();
                          getchar ();
                          break;
                      }
                      system ("clear");
                      item.seekg (0, ios::beg);
                      cout<<"\n\n\tPlease Enter the Item Code : ";
                      cin >>code;
                      while (1) {
                          item.read ((char*) &clrk, sizeof (clrk));
                          if (item.eof ())
                            break;
                          if (!std::strcmp (clrk.get_code (), code))
                              flag++;
                      }
                      if (flag != 0) {
                          std::cout << "\n\n\t Entered code already exists" << '\n';
                          item.close ();
                          std::cin.ignore ();
                          getchar ();
                          break;
                      }
                      item.close ();
                      cout<<"\n\tPlease Enter The Item Name : ";
                      cin >>name;
                      cout<<"\n\tPlease Enter The Item Price : ";
                      cin>>price;
                      cout<<"\n\tPlease Enter The Item Quantity : ";
                      cin>>quantity;
                      clrk.set_code (code);
                      clrk.set_name (name);
                      clrk.set_price (price);
                      clrk.set_quantity (quantity);
                      item.open ("/home/ankit/Desktop/c++ project/items.dat", ios::binary | ios::out | ios::app);
                      item.write ((char*) &clrk, sizeof (clrk));
                      std::cout << "\n\t written in file" << '\n';
                      item.close ();
                      std::cin.ignore ();
                      getchar ();
                      break;

             case 3 :{
                      item.open ("/home/ankit/Desktop/c++ project/items.dat", ios::in | ios::binary);
                      ofstream file;
                      int check = 0;
                      file.open ("/home/ankit/Desktop/c++ project/temp.dat", ios::out | ios::binary | ios::app);
                      if (item.fail ()) {
                          std::cout << "\n\n\t File does not exist" << '\n';
                          file.close ();
                          remove ("/home/ankit/Desktop/c++ project/temp.dat");
                          std::cin.ignore ();
                          getchar ();
                          break;
                      }
                      system ("clear");
                      std::cout << "\n\n\t Enter the code of item which you wanna delete : ";
                      std::cin >> code;
                      item.seekg (0);
                      while (1) {
                          flag = 0;
                          item.read ((char*) &clrk, sizeof (clrk));
                          if (item.eof ())
                            break;
                          if (!std::strcmp (clrk.get_code (), code)) {
                              std::cout << "\t======================================================================" << std::endl;
                              std::cout << "\t\t" << std::setw (10) << "Item Code" << "  ";
                              std::cout << std::setw (20) << "Item Name" << "  ";
                              std::cout << std::setw (10) << "Item Price" << "  ";
                              std::cout << std::setw (10) << "Quantity";
                              std::cout << std::endl << "\t======================================================================";
                              clrk.display_item ();
                              std::cout << "\n\n\t Do you wanna delete it ? (y/n) : ";
                              std::cin >> ans;
                              if (ans == 'y' || ans == 'Y') {
                                std::cout << "\n\n\tDeleted" << '\n';
                                flag++;
                              }
                              check++;
                          }
                          if (!flag)
                            file.write ((char*) &clrk, sizeof (clrk));
                      }
                      if (!check)
                        std::cout << "\n\t Item does not exist" << '\n';
                      item.close ();
                      file.close ();
                      remove ("/home/ankit/Desktop/c++ project/items.dat");
                      rename ("/home/ankit/Desktop/c++ project/temp.dat", "/home/ankit/Desktop/c++ project/items.dat");
                      std::cin.ignore ();
                      getchar ();
                      break;
                  }

             case 4 : item.open ("/home/ankit/Desktop/c++ project/items.dat", ios::in | ios::binary | ios::out | ios::ate);
                      if (item.fail ()) {
                          std::cout << "\n\n\t File does not exist" << '\n';
                          std::cin.ignore ();
                          getchar ();
                          break;
                      }
                      system ("clear");
                      std::cout << "\n\n\t Enter the code of item you wanna modify : ";
                      std::cin >> code;
                      flag = 0;
                      item.seekg (0);
                      while (1) {
                          pos = item.tellg ();
                          item.read ((char*) &clrk, sizeof (clrk));
                          if (item.eof ())
                            break;
                          if (!std::strcmp (clrk.get_code (), code)) {
                              std::cout << "\t======================================================================" << std::endl;
                              std::cout << "\t\t" << std::setw (10) << "Item Code" << "  ";
                              std::cout << std::setw (20) << "Item Name" << "  ";
                              std::cout << std::setw (10) << "Item Price" << "  ";
                              std::cout << std::setw (10) << "Quantity";
                              std::cout << std::endl << "\t======================================================================";
                              clrk.display_item ();
                              std::cout << "\n\n\t Enter modified details : " << '\n';
                              std::cout << "\n Enter modified code : ";
                              std::cin >> code;
                              std::cout << "\n Enter modified name : ";
                              std::cin >> name;
                              std::cout << "\n Enter the modified price : ";
                              std::cin >> price;
                              std::cout << "\n Enter the modified quantity : ";
                              std::cin >> quantity;
                              flag++;
                              break;
                          }
                      }
                      if (flag == 0) {
                        std::cout << "\n\t Item does not exist" << '\n';
                        item.close ();
                        std::cin.ignore ();
                        getchar ();
                        break;
                      }
                      item.seekp (pos);
                      clrk.set_code (code);
                      clrk.set_name (name);
                      clrk.set_price (price);
                      clrk.set_quantity (quantity);
                      item.write ((char*) &clrk, sizeof (clrk));
                      system ("clear");

                      std::cout << "\n\n\t After modification" << '\n';
                      std::cout << "\t======================================================================" << std::endl;
                      std::cout << "\t\t" << std::setw (10) << "Item Code" << "  ";
                      std::cout << std::setw (20) << "Item Name" << "  ";
                      std::cout << std::setw (10) << "Item Price" << "  ";
                      std::cout << std::setw (10) << "Quantity";
                      std::cout << std::endl << "\t======================================================================";
                      clrk.display_item ();

                      item.close ();
                      std::cin.ignore ();
                      getchar ();
                      break;

             case 5 : return;

             default : std::cout << "\n\t Wrong choice!! " << '\n';
                       std::cin.ignore ();
                       getchar ();

         }

     } while (1);

 }

 int getch() {
    int ch;
    struct termios t_old, t_new;
    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
 }

 string getpass(const char *prompt, bool show_asterisk = true) {
  const char BACKSPACE = 127;
  const char RETURN = 10;
  string password;
  unsigned char ch=0;
  cout << prompt;
  while((ch = getch()) != RETURN) {
       if(ch == BACKSPACE) {
            if(password.length()!=0) {
                 if(show_asterisk)
                 cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else {
             password += ch;
             if(show_asterisk)
                 cout << '*';
         }
   }
   cout << endl;
   return password;
 }
