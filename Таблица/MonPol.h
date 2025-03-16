#pragma once
#include <string>
#include <iostream>

struct Monom {
	double coeff;
	int power = 0;
	std::string name;
	Monom* next;
	Monom* prev;

	Monom(double c = 0, std::string n = "");
	Monom(double c = 0, int power = 0);
	Monom(Monom& mon);
	Monom* NextMon();
	void monout(Monom& mon);

	Monom operator+(const Monom& mon);
	Monom& operator=(const Monom& mon);
	bool operator!=(const Monom& mon) const;
	Monom operator*(const double val);
	Monom operator*(const Monom& mon) const;
	Monom operator*(const Monom* mon) const;
	friend class List;
};

class List {
private:
	Monom* head;
public:
	List() :head(NULL) {}
	List(Monom& mon) {
		head = &mon;
	}
	List(const List& list) {
		head = NULL;
		Monom* ptr = list.head;
		while (ptr!=NULL) {
			this->NewMonInList(*ptr);
			ptr = ptr->next;
		}
	}
	List GetPolinomFrUser(std::string pol);//обработка полинома из строки-выражения
	/*~List() {		
		while (head != NULL) {
			Monom* ptr = head;
			head = head->next;
			delete ptr;			
		}
	}*/

	void NewMonInList(Monom& mon);
	void MonOutFromList(Monom& mon);
	void ListOut();	
	Monom* GetHead() { return head;	}
	Monom GetMonom();
	List& operator+=(Monom& monom);
	List& operator=(const List& list);
	List operator+(const List& list);
	List operator+(const Monom& mon);
	List operator*(const double val) const;
	friend List operator*(const double val, const List& l) noexcept;
	List operator*(const List& list) const;
	List operator*(const Monom mon) const;
};