
/*
Name: Darren Kong Yan Ren
Id:2207505
Program: SE

Name: Lim Cammy
Id: 2206892
Program: SE

Name: Liow Ke Han
Id:
Program: SE

Name: Wong Yu Chi
Id: 2207129
Program: SE

Compiler: Visual Studio 2022
*/


#include <iostream> 
#include <iomanip>		// setw(), setprecision()
#include <fstream>		// open and read file
#include <cstring>
#include <string>
#include <cctype>	// isalpha(), isdigit(), toupper()
#include <cstdlib>    //system("cls")  for clear screen
#include <algorithm> // for sort()
#include <ctime>     //date(year,month,date)
#include <sstream>
#include <vector>
#include <utility>
using namespace std;
#define MAXSIZE 20

// define STRUCTURE for edit_menu()
typedef struct
{
	char code[5];		//A123\0
	char name[51];
	double unit_price;
} DISH_INFO;


// Define STRUCTURE for order info
typedef struct
{
	int orderId;
	vector<pair<DISH_INFO, int>> dishes; // pair of dish and its quantity
} ORDER_INFO;


typedef struct
{
	char order_code[10];		// T001\0
	char order_time[10];		// 03:45:20
} ORDER_INFO_FO;


// function prototype for main()
bool main_repeat();



// function prototype for edit_menu()
void edit_menu();
char operation();
bool repeat();
void display_menu_heading();
void display_all_dishes(DISH_INFO dish[], int rows);
void add_dish(DISH_INFO dish[], int rows);
void delete_dish(DISH_INFO dish[], int rows);
void delete_line(const string& dish_menu, const string& empty_line);

// function prototype for customer()
void  customer();
void store_order(const ORDER_INFO& order);
void display_payment_bill(const ORDER_INFO& order);

// Function prototypes For Statistics
void statistics_menu();
void display_stats_menu(); // Function to display the statistics menu
void retrieve_daily_statistics(); // Function to retrieve and display daily statistics
void calculate_overall_stats(double* avg_daily_sales, double* avg_daily_order); // Function to calculate overall statistics
void display_overall_stats(); // Function to display overall statistics
bool validate_date(const string date); // Function to validate date format
void display_statistics_by_date(); // function to display statistics by date


// function prototypes for food operator

void food_op();
void display_time(void);
void delete_line(const string& order_menu, const string& empty_line);
void display_heading(string heading, string line1, string line2);
int open_file(string incomplete, string file_name, ORDER_INFO_FO orders[], string line1, string line2);
void display_all_orders(ORDER_INFO_FO orders[], int rows);
string code(ORDER_INFO_FO orders[], int rows, string choice);
void display_all_dishes(DISH_INFO dishes[], int rows);



int main()
{
	char position;
	char action;

	do
	{
		cout << "==================================================================" << endl;
		cout << "                           Hola Makmak" << endl;
		cout << "==================================================================" << endl;
		cout << "\n";
		cout << "                              Hello!" << endl;
		cout << "                             Bonjour!" << endl;
		cout << "                              Hallo!" << endl;
		cout << "                               Hola!" << endl;
		cout << "                               Ciao!" << endl;
		cout << "\n";
		cout << "<A>\tManager" << endl;
		cout << "<B>\tFood Operator" << endl;
		cout << "<C>\tCustomers" << endl;
		cout << "<Q>\tQuit" << endl << endl;
		cout << "Choose Your Position: ";
		cin >> position;
		cin.ignore();
		position = toupper(position);


		switch (position)
		{
		case 'A':
		{	// start for manager
			system("cls");
			cout << "==================================================================" << endl;
			cout << "                  Welcome My Distinguished Manager" << endl;
			cout << "==================================================================" << endl;
			cout << endl;
			cout << "<A>\tEdit Menu" << endl;
			cout << "<B>\tReports" << endl;
			cout << "<Q>\tQuit" << endl << endl;

			cout << "Option: ";
			cin >> action;
			cin.ignore();
			action = toupper(action);



			switch (action)
			{	// start for action
			case 'A':
			{
				system("cls");
				// call EDIT MENU part
				edit_menu();

				break;
			}
			case 'B':
			{
				system("cls");
				// call STATISTICS part
				statistics_menu();
				break;
			}
			case 'Q':
			{

				// exit previous page
				break;
			}
			default:
			{
				cout << "Error: Invalid Input.\nPlease enter <A/B/Q>." << endl;
				break;
			}
			}	// end for action


			break;
		}	// end for manager

		case 'B':
		{	// start for food operator
			system("cls");
			void food_op();
			// call OPERATOR part
			break;

		}	// end for food operator

		case 'C':
		{	// start for customers
			system("cls");
			cout << "==================================================================" << endl;
			cout << "                 Welcome My Distinguished Customer" << endl;
			cout << "==================================================================" << endl;
			cout << endl;
			cout << "<A>\tOrder" << endl;
			cout << "<Q>\tQuit" << endl << endl;
			cout << "Option: ";
			cin >> action;
			cin.ignore();
			action = toupper(action);

			system("cls");
			switch (action)
			{
			case 'A':
			{
				system("cls");          // start for order
				customer();        // call ORDER part
				break;                // end for order
			}



			case 'Q':
			{
				break;
			}

			default:
			{
				cout << "Error: Invalid Input.\nPlease enter <A/B/Q>." << endl;
				break;
			}

			}
			break;

		}	// end for customers

		case 'Q':
		{
			return 0;
		}

		default:
		{
			cout << "Error: Invalid Input.\nPlease enter <A/B/C/Q>." << endl;
			break;
		}

		}	// end for position

	} while (main_repeat());

	return 0;
}


// Purpose: tp reflash main menu page
bool main_repeat()
{
	char repeat;
	// verify if input invalid
	do
	{
		cout << "\nQuit System <Y/N>: ";
		cin >> repeat;
		cin.ignore();

		repeat = toupper(repeat);

		if (repeat != 'N' && repeat != 'Y')
		{
			cout << "Error: Invalid Input.\nPlease enter <Y/N>.\n";
		}
	} while (repeat != 'N' && repeat != 'Y');

	system("cls");

	return (repeat == 'N');
}



/*

		STATR FOR EDIT MENU

*/
void edit_menu()
{

	DISH_INFO dishes[1000];
	char option;
	int index = 0, num_dishes;

	do
	{

		delete_line("dish_menu.txt", "\n");
		display_menu_heading();

		// read DISH MENU from file
		ifstream read_dish_menu("dish_menu.txt");		// open file
		if (!read_dish_menu)
			cout << "Error: Cannot Open 'dish_menu.txt' File." << endl;
		else
		{

			int i = 0;		// initialization
			while (read_dish_menu)		// testing
			{
				if (read_dish_menu.peek() == '\n')
					read_dish_menu.ignore(256, '\n');
				read_dish_menu.getline(dishes[i].code, 5);		 // read code
				read_dish_menu.getline(dishes[i].name, 51);		 // read name
				read_dish_menu >> dishes[i].unit_price;			 // read unit price
				if (read_dish_menu.peek() == '\n')
					read_dish_menu.ignore(256, '\n');
				//read_dish_menu.ignore(); // Ignore the newline character after price

				i++; // updating

			}
			read_dish_menu.close();		//close read file


			// -1 because have empty line at the bottom in txt, do not want to show the empty line
			num_dishes = i - 1;
			display_all_dishes(dishes, num_dishes);		// display dishes exist in txt

			num_dishes = i;

			option = operation();		// to do adding / delete / quit

			switch (option)
			{
			case 'A':
			{
				add_dish(dishes, num_dishes);
				break;
			}	// end of case 'A'

			case 'D':
			{
				delete_dish(dishes, num_dishes);
				break;
			}

			case 'Q':
				break;


			default:
				cout << "Error: Invalid Input.\nPlease enter <A/D/Q>.\n";	//verify if invalid input for option
				break;
			}// end of switch

			if (option == 'Q')
				break;		// direact quit from previous page without gothrough repeat()

		}		//end of if cannot open read file
	} while (repeat());


	return;
}

// Purpose: To add dish into menu
void add_dish(DISH_INFO dish[], int rows)
{
	cout << "Enter Dish Code: ";
	cin.getline(dish[rows].code, 5);
	cout << "[Please Press Enter to Continue.]";
	cin.ignore();

	// verify if the code format invalid
	if (!isalpha(dish[rows].code[0]) ||
		!isdigit(dish[rows].code[1]) ||
		!isdigit(dish[rows].code[2]) ||
		!isdigit(dish[rows].code[3]))
	{
		cout << "Error: Invalid Dish Code Format.\nPlease enter dish code with format [A123]." << endl;
		return;
	}


	dish[rows].code[0] = toupper(dish[rows].code[0]);



	if ((dish[rows].code[0]) != 'A' &&
		(dish[rows].code[0]) != 'B' &&
		(dish[rows].code[0]) != 'C')
	{
		cout << "Error: Invalid Dish Code. Please Using [A/B/C] to classify the dish categories.";
		return;
	}



	// verify if the code exist
	for (int i = 0; i < rows; ++i)
	{
		if (strcmp(dish[i].code, dish[rows].code) == 0)
		{
			cout << "Error: Dish Code Exists.\nPlease enter another dish code." << endl;
			return;
		}
	}

	cout << "Enter Dish Name: ";
	cin.getline(dish[rows].name, 51);

	// verify if the name exist
	for (int i = 0; i < rows; ++i)
	{
		if (strcmp(dish[i].name, dish[rows].name) == 0)
		{
			cout << "Error: Dish Name Exists.\nPlease enter another dish name." << endl;
			return;
		}
	}


	cout << "Enter Unit Price: ";
	cin >> dish[rows].unit_price;
	cin.ignore(100, '\n');


	//store DISH MENU into file
	ofstream store_dish_menu("dish_menu.txt", ios::app);		//open file
	if (!store_dish_menu)
	{
		cout << "Error: Cannot Open File." << endl;
	}
	else
	{
		store_dish_menu << dish[rows].code << endl;
		store_dish_menu << dish[rows].name << endl;
		store_dish_menu << dish[rows].unit_price << endl;

		cout << "Adding successful.";

		store_dish_menu.close();
	}	// end of error of cannot open file


	return;
}


// Purpose: to choose an operation function
char operation()
{
	char option;

	cout << "__________________________________________________________________" << endl;
	cout << "<A>dding\t<D>elete\t<Q>uit" << endl;
	cout << "Option: ";
	cin >> option;
	cin.ignore();
	option = toupper(option);

	return option;
}


// Purpose: to display menu heading
void display_menu_heading()
{
	cout << "==================================================================" << endl;
	cout << "                              MENU" << endl;
	cout << "==================================================================" << endl;
	cout << setw(6) << left << "CODE"
		<< setw(50) << left << "NAME"
		<< setw(10) << right << "PRICE (RM)" << endl;
	cout << "__________________________________________________________________" << endl;
	cout << "*Code: A=Food   B=Drink   C=Dessert" << endl;
	cout << "__________________________________________________________________" << endl;
	return;
}


// Purpose: to display all dishes exist in txt
void display_all_dishes(DISH_INFO dish[], int rows)
{
	// sort based on codes
	sort(dish, dish + rows, [](const DISH_INFO& a, const DISH_INFO& b) {
		return strcmp(a.code, b.code) < 0;
		});

	for (int i = 0; i < rows; ++i)
	{
		cout << setw(6) << left << dish[i].code
			<< setw(50) << left << dish[i].name
			<< setw(10) << right << fixed << setprecision(2) << dish[i].unit_price << endl;
	}
}


// Purpose: to reflash edit menu page
bool repeat()
{
	char repeat;

	// verify if input invalid
	do
	{
		cout << "\nContinue Edit <Y/N>: ";
		cin >> repeat;
		cin.ignore();

		repeat = toupper(repeat);

		if (repeat != 'N' && repeat != 'Y')
		{
			cout << "Error: Invalid Input.\nPlease enter <Y/N>.\n";
		}

	} while (repeat != 'N' && repeat != 'Y');

	system("cls");

	return (repeat == 'Y');
}




// Purpose: to delete dish exist in txt
void delete_dish(DISH_INFO dish[], int rows)
{
	int i = 0;
	bool exist = false;
	char find_code[5];

	cout << "Enter dish code: ";
	cin.getline(find_code, 5);
	cout << "[Please Press Enter to Continue.]";
	cin.ignore();


	// verify if the code format invalid
	if (strlen(find_code) != 4 ||
		!isalpha(find_code[0]) ||
		!isdigit(find_code[1]) ||
		!isdigit(find_code[2]) ||
		!isdigit(find_code[3]))
	{
		cout << "Error: Invalid code format.\nPlease enter dish code with format [A123]." << endl;
		return;
	}

	if (isalpha(find_code[0]))
	{
		find_code[0] = toupper(find_code[0]);
	}

	// verify if the code exist in txt file
	while (i < rows && !exist)
	{
		if (strcmp(find_code, dish[i].code) == 0)
		{
			exist = true;
		}
		else
			i++;
	}
	if (exist)
	{
		/*
			delete by shifting dish below to replace the original dish

			e.g:
			delete a002
			- the a003 will replace the place of a002,
			- a004 replace place of a002 and so on

		*/
		for (int j = i; j < rows - 1; j++)
		{

			strcpy_s(dish[j].code, sizeof(dish[j].code), dish[j + 1].code);        // using strcpy_s()
			strcpy_s(dish[j].name, sizeof(dish[j].name), dish[j + 1].name);
			dish[j].unit_price = dish[j + 1].unit_price;

		}

		// Decrement rows after the loop
		rows--;

		// store dish
		ofstream store_dish_menu("dish_menu.txt");
		if (!store_dish_menu)
		{
			cout << "Error: Cannot Open File." << endl;
		}
		else
		{
			for (int i = 0; i < rows - 1; i++)
			{
				store_dish_menu << dish[i].code << endl;
				store_dish_menu << dish[i].name << endl;
				store_dish_menu << fixed << setprecision(2) << dish[i].unit_price << endl;
			}
		}
		store_dish_menu.close();
		cout << "Delete Successfuly.";
	}
	else
		cout << "Error: Dish Code Does Not Exist." << endl;

}


// Purpose: to delete empty line that exist in txt after delete a dish to make sure read file can function well
void delete_line(const string& dish_menu, const string& empty_line)
{
	ifstream in_dish_file(dish_menu);
	if (!in_dish_file)
	{
		cout << "Error: Cannot open input file." << endl;
		return;
	}

	ofstream out_dish_file(dish_menu + ".tmp"); // Temporary file
	if (!out_dish_file)
	{
		cout << "Error: Cannot create temporary output file." << endl;
		return;
	}

	string line;
	while (getline(in_dish_file, line))
	{
		if (line != empty_line)
		{
			out_dish_file << line << endl;
		}
	}

	in_dish_file.close();
	out_dish_file.close();

	// remove original file and rename the temporary file 
	// to replace original file with the temporary file
	remove(dish_menu.c_str());
	rename((dish_menu + ".tmp").c_str(), dish_menu.c_str());


	return;
}


/*

		END FOR EDIT MENU

*/

/*

		STATR FOR CUSTOMER

*/
void customer()
{

	char answer;
	ORDER_INFO order;

	int quantity = 0;
	time_t now = time(nullptr);

	do
	{

		system("cls");
		DISH_INFO dishes[1000];
		int num_dishes;

		ifstream read_dish_menu("dish_menu.txt");
		if (!read_dish_menu)
		{
			cout << "Error: Cannot Open 'dish_menu.txt' File." << endl;
			return;
		}
		else
		{
			int i = 0;
			while (!read_dish_menu.eof())
			{
				if (read_dish_menu.peek() == '\n')
					read_dish_menu.ignore(256, '\n');
				read_dish_menu.getline(dishes[i].code, 5);
				read_dish_menu.getline(dishes[i].name, 51);
				read_dish_menu >> dishes[i].unit_price;
				if (read_dish_menu.peek() == '\n')
					read_dish_menu.ignore(256, '\n');
				i++;
			}
			read_dish_menu.close();
			num_dishes = i - 1;


			display_menu_heading();
			display_all_dishes(dishes, num_dishes);

			cout << "__________________________________________________________________" << endl;

			char menuCode[5];
			bool exist = false;

			cout << "Please enter a code: ";
			cin >> menuCode;

			// Verify if the code exists in the menu
			int j = 0;
			while (j < num_dishes && !exist)
			{
				if (strcmp(menuCode, dishes[j].code) == 0)
				{
					exist = true;
				}
				else
					j++;
			}

			if (!exist)
			{
				cout << "Error: Dish Code Does Not Exist." << endl;
				return;
			}
			else
			{
				cout << "Please enter the quantity (max 99): ";
				cin >> quantity;

				if (quantity < 1 || quantity > 99)
				{
					cout << "Invalid quantity amount." << endl;

					return;
				}

				// Store the order
				order.dishes.push_back(make_pair(dishes[j], quantity));




				cout << "Do you want to order more? (Y/N): ";
				cin >> answer;
			}
		}
	} while (answer == 'Y' || answer == 'y');
	int chaos = rand();
	int rand_no = rand() + 1;;
	srand(time(NULL));
	order.orderId = (rand_no * 10000) - (order.orderId / chaos);
	cout << "Order placed successfully! Order ID: " << order.orderId << endl;

	// Display payment bill
	display_payment_bill(order);
}


// Function to store order information in a file
void store_order(const ORDER_INFO& order)
{
	ofstream order_file("order.txt", ios::app);
	if (order_file.is_open())
	{
		for (const auto& pair : order.dishes) {
			order_file << order.orderId << " "
				<< pair.first.code << " "
				<< pair.first.name << " "
				<< pair.second << endl; // quantity
		}
		order_file.close();
	}
	else
	{
		cout << "Error: Unable to open order file for writing." << endl;
	}
}

// Function to display payment bill
void display_payment_bill(const ORDER_INFO& order)
{
	system("cls");
	double total_price = 0;

	// Display header
	cout << "Order Id: " << order.orderId << endl;
	cout << "_________________________________________________________________________________" << endl;
	cout << "PAYMENT" << endl;
	cout << "_________________________________________________________________________________" << endl;
	cout << setw(6) << "Code" << setw(15) << "Dish" << setw(10) << "Qty" << setw(25) << "Unit Price(RM)" << setw(25) << "Total Price(RM)" << endl;
	cout << "_________________________________________________________________________________" << endl;

	// Display order details
	for (const auto& pair : order.dishes) {
		const DISH_INFO& dish = pair.first;
		int quantity = pair.second;
		double dish_total_price = dish.unit_price * quantity;

		cout << setw(6) << dish.code << setw(15) << dish.name << setw(10) << quantity << setw(17) << fixed << setprecision(2) << dish.unit_price << setw(25) << fixed << setprecision(2) << dish_total_price << endl;
		total_price += dish_total_price;
	}

	// Display total price
	cout << "_________________________________________________________________________________" << endl;
	cout << setw(5) << "Total Price?" << setw(61) << fixed << setprecision(2) << total_price << endl;
	cout << "_________________________________________________________________________________" << endl;



}


/*

		END FOR CUSTOMER MENU

*/



/*

		START FOR STATISTIC

*/


//Display the menu and prompt the user to enter their choice. Once user entered valid choice,
//it will display statistics to the user. Then, the program will ask for repeat from the user.

void statistics_menu()
{
	char choice;
	do
	{
		display_stats_menu(); // Display the statistics menu
		cin >> choice; //Get user input for choice
		cin.ignore(); // Ignore newline character in the input

		// Selection control structure for choice
		switch (choice)
		{
		case '1':
			display_overall_stats(); // Choice 1: Display overall statistics
			break;
		case '2':
			display_statistics_by_date(); // Choice 2: Display statistics on a particular date
			break;
		case '3':
			cout << "Returning to the main menu..." << endl; // Choice 3: Exit to main menu
			return; // Exit the main function to return to the main menu
		default:
			cout << "Invalid choice. Please enter 1 or 2." << endl; // Prompt out error message if user enters other values beside '1', and '2'
			break;
		}

		cout << "Do you want to go back to the statistics menu? (y/n): "; // Ask for repetition
		cin >> choice;
		cin.ignore(); // Ignore newline character in the input
		system("cls"); // Clear screen
	} while (tolower(choice) == 'y'); // Undergo repetition if user enters 'y' or 'Y'

	cout << "Thank you for using the restaurant statistics system. Goodbye!" << endl;

	return;
}

// Display the statistics menu
void display_stats_menu()
{
	cout << "Welcome to the restaurant statistics system!" << endl;
	cout << "Choose one of the following options:" << endl;
	cout << "1. Display all statistics" << endl;
	cout << "2. Display statistics by date" << endl;
	cout << "3. Exit to main menu" << endl;
	cout << "Enter your choice (1, 2, or 3): ";
}

// Retrieve daily statistics from a text file and display them
void retrieve_daily_statistics()
{
	char line[1000]; // Array to store line from the text file, with each line can only store up to 1000 characters
	ifstream in_stats_file("statistics.txt"); // Open text file and allow the data from text file to flow into the program
	if (!in_stats_file) // Check if there is any error when opening the file
	{
		cout << "Failed to open file: statistics.txt" << endl; // Prompt out error message if the file cannot be opened
		return;
	}

	while (in_stats_file.getline(line, 1000)) // Read each line of the file, and store each line in 'line' array. Any line beyond the 1000th line will not be read.
	{
		cout << line << endl; // Display the contents stored in the 'line' array to the screen
	}

	in_stats_file.close(); // Close the file
}

// Calculate overall statistics
void calculate_overall_stats(double* avg_daily_sales, double* avg_daily_order)
{
	ifstream in_stats_file("statistics.txt");
	if (!in_stats_file)
	{
		cout << "Failed to open file: statistics.txt" << endl; // Prompt out error message if the file cannot be opened
		return;
	}

	string line; // Variable to store each line read from the file
	bool in_date_section = false; // Flag to indicate if the program read until the section for a specific date
	double total_sales = 0.0; // Variable to store the total sales
	int total_orders = 0; // Variable to store the total orders
	int num_days = 0; // Variable to store the number of days with recorded statistics

	// Skip the first three lines in the text file because they are header
	for (int i = 0; i < 3; ++i)
		getline(in_stats_file, line);

	// Read data for each day from the text file
	while (getline(in_stats_file, line))
	{
		// Check if the line contains the separator, which indicates the end of the section for a specific date
		if (line.substr(0, 4) == "----")
		{
			// Reset the flag as the program os no longer in the section for the specified date and move to the next day's statistics
			in_date_section = false;
			continue;
		}

		if (!in_date_section)
		{
			// Process the first line of data for each day
			in_date_section = true; // The program already enters the section for a specific date
			istringstream temp(line); // Create a stringstream named 'temp' to extract data from the line
			string date; // Variable to store the date
			double daily_sales; // Variable to store the daily sales
			int daily_orders; // Variable to store the daily orders

			temp >> date >> daily_sales >> daily_orders; // Extract data from the line using the stringstream

			// Accumulate total sales and total orders
			total_sales += daily_sales;
			total_orders += daily_orders;
			num_days++; // Increase the number of days by 1
		}
	}

	in_stats_file.close(); // Close the text file once all data has been processed

	// Calculate average daily sales and average daily order
	*avg_daily_sales = total_sales / num_days;
	*avg_daily_order = double(total_orders) / num_days;
}


// Display overall statistics
void display_overall_stats()
{
	// Display section headers
	cout << "==========================================" << endl;
	cout << "All Statistics" << endl;
	cout << "==========================================" << endl;

	// Retrieve and display daily statistics
	retrieve_daily_statistics();
	cout << "==========================================" << endl;

	// Calculate overall statistics
	double avg_daily_sales, avg_daily_order;
	calculate_overall_stats(&avg_daily_sales, &avg_daily_order);

	// Display overall statistics with the outputs of average daily sales and average daily order being formatted
	cout << "Overall stats" << endl;
	cout << "=============" << endl;
	cout << "Average daily sales = RM" << fixed << setprecision(2) << avg_daily_sales << endl;
	cout << "Average daily order = " << fixed << setprecision(1) << avg_daily_order << endl << endl;
}

// Validate date format (YYYY-MM-DD)
bool validate_date(const string date)
{
	// Check if the length of the string is not equal to 10 characters
	if (date.size() != 10)
		return false;
	// Check if the characters with indexes 4 and 7 are not '-'
	else if (date[4] != '-' || date[7] != '-')
		return false;
	else
	{
		for (int i = 0; i < 10; ++i)  // Loop through each character in the string
		{
			// Ignore characters with indexes 4 and 7 because they are '-'
			if (i != 4 && i != 7 && !isdigit(date[i]))
				return false;
		}
		// If all checks pass, the date is valid
		return true;
	}
}

void display_statistics_by_date()
{
	string year, month, day;
	cout << "Press <Q> to quit.\nEnter the date (YYYY-MM-DD)" << endl;
	cout << "Year: ";
	cin >> year;
	if (year == "Q" || year == "q")
		return;
	cout << "Month: ";
	cin >> month;
	if (month == "Q" || month == "q")
		return;
	cout << "Day: ";
	cin >> day;
	if (day == "Q" || day == "q")
		return;
	string input_date = year + "-" + month + "-" + day;

	// Validate date input
	while (!validate_date(input_date))
	{
		cout << "Invalid date format. Please enter the date in YYYY-MM-DD format." << endl;
		cout << "Year: ";
		cin >> year;
		if (year == "Q" || year == "q")
			return;
		cout << "Month: ";
		cin >> month;
		if (month == "Q" || month == "q")
			return;
		cout << "Day: ";
		cin >> day;
		if (day == "Q" || day == "q")
			return;
		input_date = year + "-" + month + "-" + day;
	}

	// Retrieve and display statistics for the specified date
	cout << "===============================================================" << endl;
	cout << "Statistics for " << input_date << endl;
	cout << "===============================================================" << endl;

	bool in_date_section = false; // Flag to indicate if the program read until the section for a specific date
	bool header_displayed = false; // Flag to indicate if the header has been displayed

	// Read from the file and check for records with the specified date
	ifstream in_stats_file("statistics.txt");
	if (in_stats_file)
	{
		string line;
		bool header_skipped = false;
		while (getline(in_stats_file, line))
		{
			if (!header_skipped)
			{
				header_skipped = true;
				continue; // Skip the header line
			}

			// Extract the date from the line
			string date = line.substr(0, 10); // The first 10 characters will be the date once entering a new date session

			// Compare the extracted date with the input date
			if (date == input_date)
			{
				// Display statistics for the specified date
				in_date_section = true; // The program already enters the section for a specific date
				if (!header_displayed)
				{
					cout << "Date           Sales   Order   Dish   Sales   Qty  Preparation\n";
					cout << "               (RM)                   (RM)           (min)\n";
					cout << "===============================================================\n";
					header_displayed = true; // The headers are displayed
				}
				cout << line << endl; // Output the entire line
			}
			else if (in_date_section && line.substr(0, 4) == "----")
			{
				// Check if the line contains the separator, which indicates the end of the section for a specific date
				in_date_section = false; // Reset the flag as the program os no longer in the section for the specified date
				break; // Exit the loop if the separator is found after the specified date's statistics
			}
			else if (in_date_section)
			{
				cout << line << endl; // Display lines within the section for the specified date
			}
		}
		in_stats_file.close();

		// Check if in_date_section is still true after reading all lines
		if (in_date_section)
		{
			cout << "===============================================================" << endl;
			cout << "No records found for the specified date." << endl;
			cout << "===============================================================" << endl;
		}
	}
	else
	{
		cout << "Failed to open file: statistics.txt" << endl;
	}

	cout << "===============================================================" << endl;
}


/*

		END FOR STATISTIC

*/



/*

		START FOR FOOD OPERATOR

*/

void food_op()
{

	ORDER_INFO_FO orders[1000];
	DISH_INFO dishes[1000];
	char option;
	string order_name;
	int index = 0, num_orders, num;
	string incomplete = "Incomplete Orders";
	string complete = "Complete Orders";

	do
	{
		num_orders = open_file(incomplete, "orders", orders, "Order Code", "Order Time");
		display_all_orders(orders, num_orders);		// display orders exist in txt & get the total count of orders
		order_name = code(orders, num_orders, "order");
	} while (repeat());

	if (repeat())
		system("cls");

	display_all_dishes(dishes, num_orders);


}



void display_time(void)
{
	// Get the current time
	time_t currentTime;
	time(&currentTime);

	// Create a local time struct
	struct tm localTimeInfo;
	// localtime_s: populate the tm struct localTimeInfo with the local time information
	localtime_s(&localTimeInfo, &currentTime);

	// Format the date as YYYY-MM-DD
	char formattedDate[11]; // YYYY-MM-DD + \0 
	strftime(formattedDate, sizeof(formattedDate), "%Y-%m-%d", &localTimeInfo);

	// Output the formatted date
	cout << "Current date in YYYY-MM-DD format: " << formattedDate << endl;

	// Extract the hour, minute, and second components
	int hour = localTimeInfo.tm_hour;
	int minute = localTimeInfo.tm_min;
	int second = localTimeInfo.tm_sec;

	// Output the current time
	//cout << "Current time: " << hour << ":" << minute << ":" << second << endl;

	return;
}

int open_file(string heading, string file_name, ORDER_INFO_FO orders[], string line1, string line2)
{
	delete_line(file_name + ".txt", "\n");
	display_heading(heading, line1, line2);

	// Open the file that stores the order made by customers
	ifstream read_orders(file_name + ".txt");		// open file
	if (!read_orders)
		cout << "Error: Cannot Open" << file_name << ".txt File." << endl;
	else
	{
		int i = 0;		// initialization
		while (read_orders)		// testing
		{
			if (read_orders.peek() == '\n')
				read_orders.ignore(256, '\n');
			read_orders.getline(orders[i].order_code, 5);		 // read order code
			read_orders.getline(orders[i].order_time, 51);		 // read order time
			if (read_orders.peek() == '\n')
				read_orders.ignore(256, '\n');
			// Ignore the newline character after the order time

			i++; // updating
		}
		read_orders.close();		//close read file

		// -1 because have empty line at the bottom in txt, do not want to show the empty line
		int num_orders = i - 1;
		//num_orders = i;

		return num_orders;
	}
}

void display_heading(string heading, string line1, string line2)
{
	cout << "==================================================================" << endl;
	cout << heading << endl;
	cout << "==================================================================" << endl;
	cout << setw(4) << left << "NO."
		<< setw(13) << line1
		<< setw(20) << line2 << endl;
	cout << "__________________________________________________________________" << endl;
	return;
}

void display_all_orders(ORDER_INFO_FO orders[], int rows)
{
	// sort based on codes
	sort(orders, orders + rows, [](const ORDER_INFO_FO& a, const ORDER_INFO_FO& b) {
		return strcmp(a.order_code, b.order_code) < 0;
		});

	int i = 0; // To get the max numbers of orders for validation 
	while (i < rows)
	{

		cout << setw(1) << left << i + 1 << setw(3) << ". "
			<< setw(13) << orders[i].order_code
			<< setw(20) << orders[i].order_time << endl;
		++i;
	}
}

int check_quantity(int count)
{
	char ch_num;
	do
	{
		cout << "Enter the quantity: ";
		cin >> ch_num;

		if (ch_num == '0')
			cout << "0 is not a valid input.\n";
		else if (!isdigit(ch_num))
			cout << "Please enter an integer.\n";
		else if ((ch_num - '0') > count)
			cout << "Record not found.\n";
		else
			return true;
	} while (ch_num == '0' || (ch_num - '0') > count || !isdigit(ch_num));

	return ch_num;
}

string code(ORDER_INFO_FO orders[], int rows, string choice)
{
	int i = 0;
	bool exist = false;
	char find_code[5];

	cout << "Enter " << choice << " code: ";
	cin.getline(find_code, 5);
	cout << "[Please Press Enter to Continue.]";
	cin.ignore();


	// verify if the code format invalid
	if (strlen(find_code) != 4 ||
		!isalpha(find_code[0]) ||
		!isdigit(find_code[1]) ||
		!isdigit(find_code[2]) ||
		!isdigit(find_code[3]))
	{
		cout << "Error: Invalid code format.\nPlease enter " << choice << " code with format[T001]." << endl;
	}

	if (isalpha(find_code[0]))
	{
		find_code[0] = toupper(find_code[0]);
	}

	// verify if the code exist in txt file
	while (i < rows && !exist)
	{
		if (strcmp(find_code, orders[i].order_code) == 0)
		{
			exist = true;
		}
		else
			i++;
	}
	return orders[i].order_code;
}

/*

		END FOR FOOD OPERATOR

*/


