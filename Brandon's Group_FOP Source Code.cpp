#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<cctype>
#include<limits>
using namespace std;

//universal variables that are used throughout the program
string name, orderType, phoneNum;
char orderTypeCode;
int tableNum, noPax, orderNum = 0;
double itemTotal, total = 0.0;
const char SENTINEL = 'n';
int month[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
int year;
int day;
int lastDay;
double sales = 0.00;
double monthProfit[12] = {};
double daySales;

//vectors to store the data
vector<string> mealId = {"M1", "M2", "M3", "M4", "M5", "M6", "M7"};
vector<string> mealNames = {"Burger", "Pizza", "Pasta", "Salad", "Soup", "Ice Cream", "Cake"};
vector<double> mealPrices = {5.99, 8.99, 67.99, 4.99, 3.99, 2.99, 3.99};
vector<string> drinkId = {"D1", "D2", "D3", "D4", "D5"};
vector<string> drinkNames = {"Coke", "Pepsi", "Lemonade", "Water", "Tea"};
vector<double> drinkPrices = {1.99, 1.99, 2.99, 0.99, 1.99};
vector<string> orderId;
vector<int> quantity;

//Function to display menu
void displayMenu(){
  cout << "\t\t\t\tMenu\n";
  cout << "-------------------------------------\n";
  for (int i = 0; i < (mealNames.size()); ++i) {
    cout << left << setw(15) << mealId[i] << setw(15) << mealNames[i] << "RM" << fixed << setprecision(2) << mealPrices[i] << endl;
  }
  cout << "\n\t\t\t\tDrinks\n";
  cout << "-------------------------------------\n";
  for (int i = 0; i < (drinkNames.size()); ++i) {
    cout << left << setw(15) << drinkId[i] << setw(15) << drinkNames[i] << "RM" << fixed << setprecision(2) << drinkPrices[i] << endl;
  }
}

//Function to register patrons
void registerPatron(){
  string id;
  int qty;
  char addMore;
  char deleteItem;
  string deleteId;
  int deleteQty;

  //reset vector for next order 
  orderId.clear();  
  quantity.clear(); 
  total = 0.0;    

  //Prompts users for personal details
  cout << "Patron Name: ";
  cin.ignore();
  getline(cin, name);
  cout << "Order Type (D for Dine-in/T for Takeaway): "; //Determines the order type of the customer
  cin >> orderTypeCode;
  while(orderTypeCode != 'D' && orderTypeCode != 'd' && orderTypeCode != 'T' && orderTypeCode != 't'){
    cout << "Invalid order type. Enter a valid order type\n(D for Dine-in/T for Takeaway): ";
    cin >> orderTypeCode;
  }
  orderTypeCode = toupper(orderTypeCode); //Converts the order type to uppercase
  switch(orderTypeCode){
    case 'D':
      orderType = "Dine-in";
      cout << "Phone number: ";
      cin >> phoneNum;
      cout << "No. of pax: ";
      cin >> noPax;
      while(cin.fail() || noPax<=0){
        cin.clear(); //clears fail flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discards the whole line
        cout << "Please input a valid integer. \nNo. of Pax: ";
        cin >> noPax;
      }
      cout << "Table Number (1-25): ";
      cin >> tableNum;
      while(cin.fail() || tableNum <= 0 || tableNum >25){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid table number(1-25): ";
        cin >> tableNum;
      }
    break;
    case 'T':
      orderType = "Takeaway";
      cout << "Phone number: ";
      cin >> phoneNum;
    break;
  }
  orderNum++;
  displayMenu(); //displays the menu for customers to view

  //loop to add items to the order
  do {
    cout << "\nEnter food or drink id you want to order: ";
    cin >> id;
    transform(id.begin(), id.end(), id.begin(), ::toupper); //converts the id to uppercase
    while(id != "M1" && id != "M2" && id != "M3" && id != "M4" && id != "M5" && id != "M6" && id != "M7" && id != "D1" && id != "D2" && id != "D3" && id != "D4" && id != "D5"){
      cout << "Invalid ID. Please enter a valid ID: ";
      cin >> id;
      transform(id.begin(), id.end(), id.begin(), ::toupper);
    }
    cout << "Enter quantity: ";
    cin >> qty;
    while(cin.fail() || qty<=0){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Please input a valid integer. \nEnter quantity: ";
      cin >> qty;
    }
    orderId.push_back(id);
    quantity.push_back(qty);
    cout << "Do you want to add more food? (y/n): "; //asks if the customer wants to add more items
    cin >> addMore;
    if (addMore == 'N' || addMore == 'n')
      break;
    else if(addMore != 'Y' && addMore != 'y')
      while(addMore != 'N' && addMore != 'n' && addMore != 'Y' && addMore != 'y'){
        cout << "Invalid input. Please enter Y or N.\n";
        cout << "Do you want to add more food? (y/n): ";
        cin >> addMore;
      }
  } while (addMore == 'Y' || addMore == 'y');

  //Displays the order details
  cout << "\n\t\t\t\t\t\tOrder Summary\n";
  cout << "--------------------------------------------------------------\n";
  cout << "  Item Name\t\t   Qty\t\t\tUnit Price (RM)\t\tPrice (RM)\n";
  cout << "--------------------------------------------------------------\n";
  for (int i = 0; i < orderId.size(); ++i) {
    for (int j = 0; j < mealId.size(); ++j) {
      if (orderId[i] == mealId[j]) {
        itemTotal = mealPrices[j] * quantity[i];
        total += itemTotal;
        cout << left << setw(5) << mealId[j] << fixed << setw(15) << mealNames[j] << setw(15) << quantity[i] << "" << fixed << setprecision(2) << mealPrices[j] << "\t\t\t\t" << fixed << setprecision(2) << itemTotal << endl;
      }
    }
    for (int j = 0; j < drinkId.size(); ++j) {
      if (orderId[i] == drinkId[j]) {
        itemTotal = drinkPrices[j] * quantity[i];
        total += itemTotal;
        cout << left << setw(5) << drinkId[j] << fixed << setw(15) << drinkNames[j] << setw(15) << quantity[i] << "" << fixed << setprecision(2) << drinkPrices[j] <<  "\t\t\t\t" << fixed  << setprecision(2) << itemTotal << endl;
      }
    }
  }
  cout << "\nTotal: RM" << fixed << setprecision(2) << total << endl;
//asks user if they want to delete an item
  do{
    cout << "\nDo you want to delete an item? (y/n): ";
    cin >> deleteItem;
    if (deleteItem == 'y' || deleteItem == 'Y') {
      cout << "Enter food or drink id you want to delete: ";
      cin >> deleteId;
      transform(deleteId.begin(), deleteId.end(), deleteId.begin(), ::toupper);
      while(id != "M1" && id != "M2" && id != "M3" && id != "M4" && id != "M5" && id != "M6" && id != "M7" && id != "D1" && id != "D2" && id != "D3" && id != "D4" && id != "D5"){
        cout << "Invalid ID. Please enter a valid ID: ";
        cin >> id;
        transform(deleteId.begin(), deleteId.end(), deleteId.begin(), ::toupper);
      }
      cout << "Enter quantity: ";
      cin >> deleteQty;
      while(cin.fail() || deleteQty<=0){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please input a valid integer. \nEnter quantity: ";
        cin >> deleteId;
      }
      for (int i = 0; i < orderId.size(); ++i) {
        if (orderId[i] == deleteId) {
          if(quantity[i] >= deleteQty){
            quantity[i] -= deleteQty;
            cout << "The item has been deleted" << endl;
          }
          else{
            cout << "Quantity to delete exceeds current order quantity." << endl;
          }
        if(quantity[i] == 0){
            orderId.erase(orderId.begin() + i);
            quantity.erase(quantity.begin() + i);
          }
          break;
        }
        if(i == orderId.size()){
          cout << "Item not found in the order." << endl;
        }
      }
    } else if(deleteItem == 'n' || deleteItem == 'N') {
        break;
    }
    else
      cout << "Invalid input. Please enter Y or N.";
  }
  while(deleteItem == 'Y' || deleteItem == 'y');
}

//Function to calculate and display charges to the customer 
void displayCharges(int orderNum, int noPax, int tableNum, int i){
  cout << "\n\n\t\t\t\t\tJi Li & Friends\n";
  cout << "---------------------------------------------------------------\n";
  cout << "\t\t\t\t\t" << orderType << " " << orderNum << endl;
  cout << "---------------------------------------------------------------\n";
  cout << "Order Number: "<< year << month[i] << day << orderTypeCode << orderNum << endl;
  cout << "Name: " << name << endl;
  cout << "Phone Number: " << phoneNum << endl;
  cout << "Date: " << year << "-" << month[i] << "-" << day << endl;
  if(orderType == "Dine-in"){ //only displays number of pax and table number if the order type is dine-in
   cout << "No. of Pax: " << noPax << endl;
   cout << "Table Number: " << tableNum << endl;
  }
  cout << "--------------------------------------------------------------\n";
  cout << "  Item Name\t\t   Qty\t\t\tUnit Price (RM)\t\tPrice (RM)\n";
  cout << "--------------------------------------------------------------\n";
  for (int i = 0; i < orderId.size(); ++i) {
    for (int j = 0; j < mealId.size(); ++j) {
      if (orderId[i] == mealId[j]) {
        itemTotal = mealPrices[j] * quantity[i];
        cout << left << setw(5) << mealId[j] << fixed << setw(15) << mealNames[j] << setw(15) << quantity[i] << "" << fixed << setprecision(2) << mealPrices[j] << "\t\t\t\t" << fixed << setprecision(2) << itemTotal << endl;
      }
    }
    for (int j = 0; j < drinkId.size(); ++j) {
      if (orderId[i] == drinkId[j]) {
        itemTotal = drinkPrices[j] * quantity[i];
        cout << left << setw(5) << drinkId[j] << fixed << setw(15) << drinkNames[j] << setw(15) << quantity[i] << "" << fixed << setprecision(2) << drinkPrices[j] <<  "\t\t\t\t" << fixed  << setprecision(2) << itemTotal << endl;
      }
    }
  }
  cout << "--------------------------------------------------------------\n";
  cout << "\n\t\t\t\t\t\t\t\t\t\t\tTotal: RM" << fixed << setprecision(2) << total << endl;

  daySales += total; //calculates the total sales for the day
  monthProfit[i] += total; //calculates the total profit for the month
}

//Function to display total sales
void calculateSales(double daySales, char codeFunction, int i){
//receives code from main to display either daily or montly sales
  if(codeFunction == '2'){
    cout << fixed << setprecision(2) << "\nThe sales for the day so far is RM" << daySales << endl << endl;
  }
  else if(codeFunction == '3'){
    cout << "\nThe sales for the month so far is RM" << monthProfit[i] << endl << endl;
  }
}


int main(void)
{
  char codeFunction;
  int i;

  cout << "Enter the date (dd mm yyyy): "; //prompts user to input the current date
  cin >> day >> i >> year;
  while(cin.fail() || day <= 0 || day > 31 || i <= 0 || i > 12 || year <= 0){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Please enter a valid date (dd mm yyyy): ";
    cin >> day >> i >> year;
  }

  for(; year < 2050; year++){  //loop for year, year value is received at the beginning of the program
    for(i = i-1; i<12; i++){  //loop for month, month value is received at the beginning of the program
      
      switch(month[i]){  //determines the number of days in a month
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
          lastDay = 31;
        break;
        case 4: case 6: case 9: case 11:
          lastDay = 30;
        break;
        case 2:{
          if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
            lastDay = 29;
          else
            lastDay = 28;
        }
        break;
      }
      monthProfit[i] = 0; //resets the monthly profit to 0
      for(;day <= lastDay;day++){ //day value is received at the beginning of the program
        total = 0.00; //resets the total to 0
        do{
          cout << "\nDate: " << day << "-" << month[i] << "-" << year << endl; //displays the date so that the user knows what date they are on
          cout << "\nWelcome to Ji Li & Friends\n";
          cout << "Enter a code: \n1 - Register Patrons\n2 - Display Sales For The Day\n3 - Display Sales For The Month\nn - End The Day\nz - Terminate The Program\n";
          cin >> codeFunction;
          codeFunction = tolower(codeFunction);
          switch(codeFunction){
            case '1': //runs the primary function of the program
              registerPatron();
              displayCharges(orderNum, noPax, tableNum, i);
            break;
            case '2': //displays daily sales
              calculateSales(daySales,codeFunction, i);
            break;
            case '3': //displays sales for the month so far
              calculateSales(daySales, codeFunction, i);
            break;
            case 'n': //ends the day
              orderNum = 1;
              calculateSales(daySales, codeFunction, i);
            break;
            case 'z': //terminates the program
              break;
            break;
            default:{
              cout << "Invalid input. Please enter a valid code.\n1 - Register Patrons\n2 - Display Sales For The Day\n3 - Display Sales For The Month\nn - End The Day\nz - Terminate The Program\n";
              cin >> codeFunction;
              codeFunction = tolower(codeFunction);
            }
          }
          daySales += sales;
          if(codeFunction == 'z')
            break;
        }
        while(codeFunction != SENTINEL); 
        if(codeFunction == 'z')
          break;
        cout << "\nSales for " << day << "/" << month[i] << "/" << year << ": RM" << daySales << endl << endl; //displays the total sales for the day when the day is ended
        sales = 0.0; 
        if(day == lastDay){ //displays the monthly sales if it is the end of the month
          cout << "Month sales = RM" << monthProfit[i] << endl << endl;
        }
        daySales = 0.00;
        if(day == lastDay){
          day = 1; //resets day to 1 at the start of each month
          break;
        }
        //day ends here
      }
      monthProfit[i] = 0.0;
      if(codeFunction == 'z')
        break;
      //month ends here
    }
    if(codeFunction == 'z')
      break;
    //year ends here
  }
  return(0);
}


/*

References:
Title: C++ Vector
Author: Programiz
Date: n.d.
Availability: https://www.programiz.com/cpp-programming/vectors

Title: how to ensure an input is an integer?
Author: Peter87
Date: 2022
Availability: https://cplusplus.com/forum/beginner/283248/
*/