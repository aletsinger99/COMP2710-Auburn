

//Sources and help:
//Talked with my roommate about the type of loop to use and the merits of each
//Used the hint sheet provided by Dr. Li on canvas. Most formatting comes from that in some form
//Used the stackoverflow link provided by a TA on Piazza to solve non numeric inputs
//Used c++ documentation to learn about the proper use of c.in() and c.fail()

#include <iostream>
#include <limits>
using namespace std;
int main()
{
    //initializing/allocating space for variables
    //size of the loan for the given month. Is initialized as starting loan amount
    double loanAmount = 0;
    double interest;
    //monthlyPaidAmount is the maximum amount payed per month
    double monthlyPaidAmount = 0;
    //interestDecimal is the input interest after getting divided down to a percent of loan paid each month
    double interestDecimal;
    //monthlypaidinterest is the interest paid each month output in the amortization table
    double monthlyPaidInterest;
    //monthlyPrinciple is the monthly principle (monthlyPaidAmount - monthlyPaidInterest)
    double monthlyPrinciple;
    //month is initialized to zero because no months of payments have happened
    //this will be incremented to track the number of months in which the user has payed on the loan
    int month = 0;
    //interestTotal is the accumulated interest paid while paying off the loan
    //found by adding up all monthlyPaidInterests
    double interestTotal;


    //decimal format. Taken from the template provided by Dr. Li
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    
    //Prompts the user for a loan amount. Program will continue prompting for a loan amount until a vaild inout is received
    
    //A do while loop always runs at least once. This accepts a user input for a value. 
    //If an invalid input is received, it prompts the user for another value
    do
    {
        
        cout << "Loan Amount: ";
        cin >> loanAmount;
        if(!loanAmount)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (loanAmount <= 0);
    
    do
    {
        cout << "Interest Rate (% per year): ";
        cin >> interest;

        if(cin.fail())
        {
            interest = -1;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }   
        

        
    } while (interest < 0);

    interest = interest / 12;
    interestDecimal = interest / 100;
    monthlyPaidInterest = interestDecimal * loanAmount;
    do
    {
        cout << "Amont Paid Monthly: ";
        cin >> monthlyPaidAmount;
        if(!monthlyPaidAmount)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
        }

    } while (monthlyPaidAmount <= monthlyPaidInterest);
    
    cout << endl;

    //Start of table formatting/output
    cout << "**********************************************************\n"
         << "\tAmortization Table\n"
         << "**********************************************************\n"
         << "Month"
         << "\tBalance"
         << "\t   Payment"
         << "\tRate"
         << "\t   Interest"
         << "\tPrinciple"
         << endl;

    while (loanAmount>0)
    {
        if (month == 0)
        {
            cout << month
                 << "\t$"
                 << loanAmount
                 << "   N/A\t\tN/A\t   N/A\t\tN/A\n"
                 << endl;

                 month++;
        

        }
        else
        {
            if(loanAmount >= monthlyPaidAmount)
            {
                monthlyPaidInterest = loanAmount * interestDecimal;
                //monthlyPrinciple is what is subtracted from the loan each month
                monthlyPrinciple = monthlyPaidAmount - monthlyPaidInterest;
                
            }
            else
            {
                monthlyPaidInterest = loanAmount * interestDecimal;
                monthlyPrinciple = loanAmount;
                monthlyPaidAmount = (loanAmount * (1+interestDecimal));
            }
            loanAmount = loanAmount - monthlyPrinciple;
            //The following code keeps the correct alignment in the amortization table
            
            if(loanAmount > 1000)
            {
                cout << month << "\t$" << loanAmount <<"   $"
                << monthlyPaidAmount << "\t" << interest << "\t   $"
                << monthlyPaidInterest << "\t$" << monthlyPrinciple
                << endl;
            }
            else
            {
                cout << month << "\t$"  <<loanAmount << "\t   $"
                << monthlyPaidAmount << "\t" << interest << "\t   $"
                << monthlyPaidInterest << "\t$" << monthlyPrinciple
                << endl;

            }
            month++;
            interestTotal = interestTotal + monthlyPaidInterest;
            
        }
    

    }
    //month iterates again at the end of the loop, so you must subtract one before output. Sources from Dr. Li help    
    cout << "**********************************************************\n"
    << "\nIt takes " << month-1 << " months to pay off the loan\n"
    << "Total interest paid is $ " << interestTotal
    << endl;

}