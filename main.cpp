#include <cstdlib>
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine g(seed);

int main(int argc, char** argv)
{

	ofstream F;

	//file in which to dump the sim data, it will overwrite itself on each run.
	F.open("Last Sim.txt", ofstream::out | ofstream::trunc);

	int	N = -1;
	F << "card 1" << '\t' << "card 2" << '\t' << "card 3" << '\t' << "all cards" << endl;
	cout << "enter how many runs to simulate:" << endl;
	do
	{
		cin >> N;
		if (N < 1)
			cout << "please enter a positive number:" << endl;
	} while (N < 1);

	for (int trials = 0; trials < N; trials++)
	{
		//set up conditions and variables
		//cards 0 - 48, 49 total
		int cards = 48,
			card1 = 4,
			card2 = 4,
			card3 = 10;

		bool has_card_2 = false;
		bool has_card_1 = false;
		bool has_card_3 = false;

		//roll initial 5
		for (int i = 0; i < 5; i++)
		{
			uniform_int_distribution<unsigned> rd(0, cards);
			int roll = rd(g);
			//card 1 = 0, 1, 2, 3; shift over one for each card found.
			if (roll < card1) {
				has_card_1 = true;
				card1--;
			}
			//card 2 is a subset of card 3.
			else if (roll < card1 + card2)
			{
				if (has_card_2)
					has_card_3 == true;
				has_card_2 = true;
				card2--;
			}
			else if (roll < card1 + card2 + card3)
			{
				has_card_3 = true;
				card3--;
			}
			cards--;
		}

		//determine how many cards to redraw;
		int redraw = 3;
		if (has_card_1)
		{
			redraw--;
			card1 = 3;
		}
		if (has_card_2) 
		{
			redraw--;
			card2 = 3;
		}
		if (has_card_3)
		{
			redraw--;
			card3 = 9;
		}
		
		//numerical variables can be evaluated directly as booleans according to their value, 0 == false, any other value == true
		if(!redraw)
			redraw += 2;

		//replace cards that need to be redrawn
		cards += redraw;

		//draw again
		for (int i = 0; i < redraw; i++)
		{
			uniform_int_distribution<unsigned> rd(0, cards);
			int roll = rd(g);
			if (roll < card1) {
				has_card_1 = true;
				card1--;
			}
			else if (roll < card1 + card2)
			{
				//if you have card 3 and get it again, congrats you now have card 3 too.
				if (has_card_2)
					has_card_3 == true;
				has_card_2 = true;
				card2--;
			}
			else if (roll < card1 + card2 + card3)
			{
				has_card_3 = true;
				card3--;
			}
			cards--;
		}
		//draw the final 6th card
		uniform_int_distribution<unsigned> rd(0, cards);
		int roll = rd(g);
		if (roll < card1)
		{
			has_card_1 = true;
			card1--;
		}
		else if (roll < card1 + card2)
		{
			if (has_card_2 == true)
				has_card_3 == true;
			has_card_2 = true;
			card2--;
		}
		else if (roll < card1 + card2 + card3)
		{
			has_card_3 = true;
			card3--;
		}
		cards--;
		
		if (has_card_1) F << '1' << '\t';
		else F << '0' << '\t';
		if (has_card_2) F << '1' << '\t';
		else F << '0' << '\t';
		if (has_card_3) F << '1' << '\t';
		else F << '0' << '\t';
		if (has_card_1 && has_card_2 && has_card_3) F << '1' << endl;
		else F << '0' << endl;
	}
}
