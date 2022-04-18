#include <iostream>
#include <string>
#include <vector>

using namespace std;

void StupidFoolTest() {
	while (1)
	{
		bool good = false;
		string fio;
		getline(cin, fio);
		for (size_t i = 0; i < fio.size(); i++)
		{

			if (fio[i] != '0' && fio[i] != '1' && fio[i] != '2' && fio[i] != '3' && fio[i] != '4' && fio[i] != '5' && fio[i] != '6' && fio[i] != '7' && fio[i] != '8' && fio[i] != '9') {
				good = false;
				break;
			}
			else {
				good = true;
			}
		}
		if (good==true)
		{
			cout << "good\n";
			break;
		}
		else
		{
			cout << "bad\n";
		}
	}
}
/*I miraculously found the right solution. In my opinion, we need more literature, or references to literature.*/
ostream& endll(ostream& os) 
{
	os.put(os.widen('\n'));
	os.put(os.widen('\n'));
	os.flush();
	return os;
}








class Card {
public:
	enum rank { Ace = 1, Two, Tree, Four, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};
	enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };
	Card(rank r = Ace, suit s = SPADES, bool ifu = true);
	int GetValue() const;
	void Flip();
	//5 
	friend ostream& operator<<(ostream& os, const Card& card);
private:
	rank m_Rank;
	suit m_Suit;
	bool m_IsFaceUp;
};

void Card::Flip() { m_IsFaceUp = !(m_IsFaceUp); }
int Card::GetValue()const {
	int value = 0;
	if (m_IsFaceUp) {
		value = m_Rank;
		if (value > 10) {
			value = 10;
		}
	}
	return value;
}


ostream& operator<<(ostream& os, const Card& card) {
	const string Ranks[] = {"0", "А", "2", "З", "4", "5", "6", "7", "8", "9", "10", "J", "О", "К"};
	const string Suits[] = { "H", "D", "C", "S" };
	if (card.m_IsFaceUp) {
		os << Ranks[card.m_Rank] << Suits[card.m_Suit];
	}
	else {
		os << "XX";
	}
	return os;
}

class Hand
{
protected:
	vector<Card*>m_Cards;
public:
	Hand();
	virtual ~Hand();
	void Add(Card* someCard);
	void Clear();
	int GetTotal() const;
};

Hand::Hand() { m_Cards.reserve(7); }
Hand::~Hand() { Clear(); }

void Hand::Add(Card* pCard) { m_Cards.push_back(pCard); }
void Hand::Clear() { m_Cards.clear(); }

int Hand::GetTotal()const {
	if (m_Cards.empty()) {return 0;	}
	if (m_Cards[0]->GetValue() == 0) { return 0; }
	int total = 0;
	vector<Card*>::const_iterator iter;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
		total += (*iter)->GetValue();
	}
	bool containsAce = false;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter){
		if ((*iter)->GetValue() == 0) {
			containsAce = true; 
		}
	}
	if (containsAce && total < 11) {
		total += 10;
	}
	return total;
}


class GenericPlayer :public Hand
{
	friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
public:
	GenericPlayer(const string& name="");
	virtual ~GenericPlayer();

	virtual bool IsHitting() const = 0;

	bool IsBoosted() const;
	void Bust() const;
protected:
	string m_Name;
};

GenericPlayer::GenericPlayer(const string& name) :m_Name(name) {};
GenericPlayer::~GenericPlayer(){};

bool GenericPlayer::IsBoosted()const { return GetTotal() > 21; }
void GenericPlayer::Bust() const { cout << m_Name << "busts \n"; }

ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer) {
	os << aGenericPlayer.m_Name << ":\t";
	vector<Card*>::const_iterator pCard;
	if (!aGenericPlayer.m_Cards.empty()) {
		for (pCard = aGenericPlayer.m_Cards.begin(); pCard != aGenericPlayer.m_Cards.end(); ++pCard) {
			os << *(*pCard) << "\t";
		}
		if (aGenericPlayer.GetTotal() != 0) {
			cout << " ( " << aGenericPlayer.GetTotal() << " )";
		}
	}
	else {
		os << "<empty>";
	}
	return os;
}




class Player: public GenericPlayer
{
public:
	Player(const string name="");
	
	virtual bool IsHitting() {
		char question;
		cout << "Need more card?(y/n)";
		do{
			cin >> question;
		} while (question=='y'||question=='n');
		if (question=='y'){
			return true;
		}
		else{
			return false;
		}	
	}
	void Win()const {
		cout << Player::m_Name << "Win!";
	}
	void Loose()const {
		cout << Player::m_Name << "Loose :(";
	}
	void Puhh()const {
		cout << Player::m_Name << "got Draw!";
	}
};

class House:public GenericPlayer
{
public:
	House(string name):GenericPlayer("Dealer") {};
	
	virtual bool IsHitting() {
		if (Hand::GetTotal() < 16) {
			return true;
		}
		else {
			return false;
		}
	}
	void FlipFirstCard() {
		m_Cards[0]->Flip();
	}


};




int main()
{
	StupidFoolTest();
	cout << "A" << endll;
	cout << "A" << endll;
	return 0;
}
