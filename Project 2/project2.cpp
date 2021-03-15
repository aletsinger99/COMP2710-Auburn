
//Cited Sources: 
//Used Dr. Li's provided hints sheet on canvas
//Used advice given in piazza about the inclusivity/exclusivity of rand function
//used a stack overlow page to learn about the cin.get() function used in the press_any_key() function
//used a stack overflow page to troubleshoot a warning message given on line 121. Resolved with a comment now
//used a classmate's advice to use <iomanip> and setprecision(2) before printing to make sure correct number of decimals print
//talked with some classmates on how to implement assert() on testing the test_****_shoots methods
//the hints sheet provided on canvas was the source utilized the most.
#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<ctime>
#include<iomanip> //used to set precision
using namespace std;
//////////////////////////////
//Defining variables and functions
//////////////////////////////
int numWinsAaron = 0;
const int hitPercentAaron = 33; //constant variable 1
const int hitPercentBob = 50;  //constant variable 2
int numWinsBob = 0;
int numWinsCharlie = 0;
bool at_least_two_alive(bool a_alive, bool b_alive, bool c_alive); //determines if at least 2 people are alive
void Aaron_shoots1(bool& b_alive, bool& c_alive); //simulates aaron shooting using strategy 1
void Bob_shoots(bool& a_alive, bool& c_alive); //simulates bob shooting
void Charlie_shoots(bool& a_alive, bool& b_alive); //simulates charlie shooting
void Aaron_shoots2(bool& b_alive, bool& c_alive); //simulates aaron shooting using strategy 2
void test_at_least_two_alive(void); //test driver for at_least_two_alive
void test_Aaron_shoots1(void); //test driver for aaron_shoots1
void test_Bob_shoots(void); //test driver for bob_shoots
void test_Charlie_shoots(void); //test driver for charlie shoots
void test_Aaron_shoots2(void); //test driver for aaron_shoots2
void strategy1(void); //implementation of strategy 1 for aaron
void strategy2(void); //implemenation of strategy 2 for aaron
void press_any_key(void); //function accepts a user input to continue

/////Below is the implentation of all of the functions defined near the top of the file
/////All test drivers use assert() in some capacity
//////////////////////////////////
bool at_least_two_alive(bool a_alive, bool b_alive, bool c_alive)
{
	if(a_alive)
	{
		if(b_alive || c_alive)
		{
			return true;
		}
	}
	else if(b_alive)
	{
		if(c_alive)
		{
			return true;
		}
	}
	else
	{
		return false;
	}
    return false; //compiler was throwing a warning without a default. needs to have return not in if statement even if
} //if statement is always true
void Aaron_shoots1(bool& b_alive, bool& c_alive)
{
	if(c_alive == true)
	{
		int i = rand()%100;
		if(i < hitPercentAaron)
		{
			c_alive = false;
		}
	}
	else
	{
		int j = rand()%100;
		if(j < hitPercentAaron)
		{
			b_alive = false;
		}
	}
}
void Bob_shoots(bool& a_alive, bool& c_alive)
{
	if(c_alive == true)
	{
		int i = rand()%100;
		if(i < hitPercentBob)
		{
			c_alive = false;
		}
	}
	else
	{
		int j = rand()%100;
		if(j < hitPercentBob)
		{
			a_alive = false;
		}
	}
}
//dont need to use a hitPercentCharlie variable because he never misses
void Charlie_shoots(bool& a_alive, bool& b_alive)
{
	if(b_alive == true)
	{
		b_alive = false;
	}
	else
	{
		a_alive = false;
	}
}
void Aaron_shoots2(bool& b_alive, bool& c_alive)
{
	if(!b_alive || !c_alive) //this means bob or charlie has already died
	{
		int i = rand()%100;
		if(i < hitPercentAaron)
		{
			if(c_alive) 
			{
				c_alive = false;
			}
		  else
			{
				b_alive = false;
			}
		}
	}
}

void strategy1(void)
{//all players start off as alive
	bool a_alive = true;
	bool b_alive = true;
	bool c_alive = true;
	while(at_least_two_alive(a_alive, b_alive, c_alive))
	{
		if (a_alive)
		{
			Aaron_shoots1(b_alive, c_alive);
		}
		if (b_alive)
		{
			Bob_shoots(a_alive, c_alive);
		}
		if (c_alive)
		{
			Charlie_shoots(a_alive, b_alive);
		}
	}
	//There is only one person left at the end of each round, so whoever is left wins the round
	if(a_alive)
	{
		numWinsAaron++;
	}
	else if(b_alive)
	{
		numWinsBob++;
	}
	else
	{
		numWinsCharlie++;
	}
}
void strategy2(void)
{
	bool a_alive = true; //by setting these all to true it signifies a new round
	bool b_alive = true;
	bool c_alive = true;
	while(at_least_two_alive(a_alive, b_alive, c_alive))
	{
		if (a_alive)
		{
			Aaron_shoots2(b_alive, c_alive);
		}
		if (b_alive)
		{
			Bob_shoots(a_alive, c_alive);
		}
		if (c_alive)
		{
			Charlie_shoots(a_alive, b_alive);
		}
	}
	//there is only 1 person left at the end of each round, so whoever is left gets the point
	if(a_alive)
	{
		numWinsAaron++;
	}
	else if(b_alive)
	{
		numWinsBob++;
	}
	else
	{
		numWinsCharlie++;
	}
}
void test_at_least_two_alive(void)
{//output is taken from Dr. Li's example to match formatting
	cout << "Unit Testing 1: Function - at_least_two_alive()\n";
	cout<< "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(true, true, true));
	cout << "\tCase passed...\n";
	cout<< "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(false, true, true));
	cout << "\tCase passed...\n";
	cout<< "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
	assert(true == at_least_two_alive(true, false, true));
	cout << "\tCase passed...\n";
	cout<< "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
	assert(true == at_least_two_alive(true, true, false));
	cout << "\tCase passed...\n";
	cout<< "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
	assert(false == at_least_two_alive(false, false, true));
	cout << "\tCase passed...\n";
	cout<< "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
	assert(false == at_least_two_alive(false, true, false));
	cout << "\tCase passed...\n";
	cout<< "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(true, false, false));
	cout << "\tCase passed...\n";
	cout<< "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(false, false, false));
	cout << "\tCase passed...\n";
}
void test_Aaron_shoots1(void)
{
	bool b2_alive;
	bool c2_alive;
	cout << "Unit Test 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
	cout << "\tCase 1: Bob alive, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	b2_alive = true; //set the inputs of each test in the unit test
	c2_alive = true;
	Aaron_shoots1(b2_alive, c2_alive);
	assert(true == b2_alive);
	cout << "\tCase 2: Bob dead, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	b2_alive = false;
	c2_alive = true;
	Aaron_shoots1(b2_alive, c2_alive);
	assert(false == b2_alive);
	cout << "\tCase 3: Bob alive, Charlie dead\n";
	cout << "\t\tAaron is shooting at Bob\n";
	b2_alive = true;
	c2_alive = false;
	Aaron_shoots1(b2_alive, c2_alive);
	assert(false == c2_alive); 
}
void test_Bob_shoots(void)
{
	bool a3_alive;
	bool c3_alive;
	cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
	cout << "\tCase 1: Aaron alive, Charlie alive\n";
	cout << "\t\tBob is shooting at Charlie\n";
	a3_alive = true;
	c3_alive = true;
	Bob_shoots(a3_alive, c3_alive);
	assert(true == a3_alive);
	cout << "\tCase 2: Aaron dead, Charlie alive\n";
	cout << "\t\tBob is shooting at Charlie\n";
	a3_alive = false;
	c3_alive = true;
	Bob_shoots(a3_alive, c3_alive);
	assert(false == a3_alive);
	cout << "\tCase 3: Aaron alive, Charlie dead\n";
	cout << "\t\tBob is shooting at Aaron\n";
	a3_alive = true;
	c3_alive = false;
	Bob_shoots(a3_alive, c3_alive);
	assert(false == c3_alive);
}
void test_Charlie_shoots(void)
{
	bool a4_alive;
	bool b4_alive;
	cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
	cout << "\tCase 1: Aaron alive, Bob alive\n";
	cout << "\t\tCharlie is shooting at Bob\n";
	a4_alive = true;
	b4_alive = true;
	Charlie_shoots(a4_alive, b4_alive);
	assert(true == a4_alive);
	assert(false == b4_alive);
	cout << "\tCase 2: Aaron dead, Bob alive\n";
	cout << "\t\tCharlie is shooting at Bob\n";
	a4_alive = false;
	b4_alive = true;
	Charlie_shoots(a4_alive, b4_alive);
	assert(false == a4_alive);
	assert(false == b4_alive);
	cout << "\tCase 3: Aaron alive, Bob dead\n";
	cout << "\t\tCharlie is shooting at Aaron\n";
	a4_alive = true;
	b4_alive = false;
	Charlie_shoots(a4_alive, b4_alive);
	assert(false == b4_alive);
	assert(false == a4_alive);
}
void test_Aaron_shoots2(void)
{
	cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
	bool b5_alive;
	bool c5_alive;
	cout << "\tCase 1: Bob alive, Charlie alive\n";
	cout << "\t\tAaron intentionally misses his first shot\n";
	b5_alive = true;
	c5_alive = true;
	Aaron_shoots2(b5_alive, c5_alive);
	assert(true == b5_alive);
	assert(true == c5_alive);
	cout << "\t\tBoth Bob and Charlie are alive\n";
	cout << "\tCase 2: Bob dead, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	b5_alive = false;
	c5_alive = true;
	Aaron_shoots2(b5_alive, c5_alive);
	assert(false == b5_alive);
	cout << "\tCase 3: Bob alive, Charlie dead\n";
	cout << "\t\tAaron is shooting at Bob\n";
	b5_alive = true;
	c5_alive = false;
	Aaron_shoots2(b5_alive, c5_alive);
	assert(false == c5_alive);
}
void press_any_key(void)
{
    cout << "Press any key to continue...\n";
    cin.ignore().get(); //played around using cin.get() instead of cin.ignore().get()
}//cin.ignore().get() was recommended by Dr. Li, so I am using that one

////////////////////////////
//main function is used to call all of the test implementations and other utilized functions
//main is called last after everything is defined
////////////////////////////
int main()
{
	cout.setf(ios::fixed | ios::showpoint);
	const int numRuns = 10000; //constant variable 3
	cout << "*** Welcome to Alecs's Duel Simulator ***\n";
	srand(time(0)); //used to essentially set a seed
	test_at_least_two_alive(); //this part of main is where all of the test driver implementations run
	press_any_key();
	test_Aaron_shoots1();
	press_any_key();
	test_Bob_shoots();
	press_any_key();
	test_Charlie_shoots();
	press_any_key();
	test_Aaron_shoots2();
	press_any_key();
	cout << "Ready to test strategy 1 (run 10000 times):\n";
	press_any_key();
	for(int i = 0; i < numRuns; i++) //loop runs strategy1 for the number of desired duels to happen
	{
		strategy1();
	}
	//cast as double to make the win percentage a double
	double winPercentageAaron = (double) numWinsAaron / (double) numRuns;
	double winPercentageBob = (double) numWinsBob / (double) numRuns;
	double winPercentageCharlie = (double) numWinsCharlie / (double) numRuns;
	int numWinsAaronStrategy1 = numWinsAaron; //uses numWinAaronStrategy1 to store numWinsAaron, so numWinsAaron can be used in strategy2
	cout << "Aaron won " << numWinsAaron << "/" << numRuns << " duels or "
		 << setprecision(2) << winPercentageAaron * 100 << "%\n";
	cout << "Bob won " << numWinsBob << "/" << numRuns << " duels or "
		 << setprecision(2) << winPercentageBob * 100 << "%\n";
	cout << "Charlie won " << numWinsCharlie << "/" << numRuns << " duels or "
		 << setprecision(2) << winPercentageCharlie * 100 << "%\n\n";
	cout << "Ready to test strategy 2 (run 10000 times):\n";
	press_any_key();
	//Have to reset the win counter because strategy 2 is a separate trial
	numWinsAaron = 0;
	numWinsBob = 0;
	numWinsCharlie = 0;
	for (int j = 0; j < numRuns; j++)
	{
		strategy2();
	}
	//cast as double in order to make the percentage a double
	double winPercentageAaron2 = (double) numWinsAaron / (double) numRuns;
	double winPercentageBob2 = (double) numWinsBob / (double) numRuns;
	double winPercentageCharlie2 = (double) numWinsCharlie / (double) numRuns;
	//print statements
	cout << "Aaron won " << numWinsAaron << "/" << numRuns << " duels or "
		 << setprecision(2) << winPercentageAaron2 * 100 << "%\n";
	cout << "Bob won " << numWinsBob << "/" << numRuns << " duels or "
		 << setprecision(2) << winPercentageBob2 * 100 << "%\n";
	cout << "Charlie won " << numWinsCharlie << "/" << numRuns << " duels or "
		 << setprecision(2) << winPercentageCharlie2* 100 << "%\n\n";
//numWinsAaron in this scenario is the number of wins Aaron got in strategy2 because that was the last time the variable was updated
	if(numWinsAaron > numWinsAaronStrategy1) //compares strategy 1 with strategy 2 for Aaron
	{
		cout << "Strategy 2 is better than strategy 1\n";
	}
	else if(numWinsAaron < numWinsAaronStrategy1)
	{
		cout << "Strategy 1 is better than strategy 2\n";
	}
	else
	{
		cout << "The strategies have equal win percentages\n";
	}
}