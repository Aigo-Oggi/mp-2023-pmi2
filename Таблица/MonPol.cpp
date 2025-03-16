#include "MonPol.h"
#include <string>


int Power(char c) {
	switch (c)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default:
		throw "Invalid power syntax!";
	}
}
int Variable(char c) {
	switch (c)
	{
	case 'x': return 100;
	case 'y': return 10;
	case 'z':return 1;
	default:
		throw "Ivalid name of Variable!";
	}
}
Monom::Monom(double c, std::string n) : coeff(c), name(n) {
	if (name == "" && power != 0) throw "Invalid name of monom!";
	if (!isalpha(name[0]) && name!="")
		throw "Invalid monom syntax!";// ���������, ��� ������  ������ ������ - �������� ����������
	if (name.size() > 0) {
		for (int i = 0; i < name.size(); i++) { // ��������� �� <���������� � �������>
			if (isalpha(name[i])) {
				if (i + 2 < name.size()) {
					if (name[i + 1] == '^' && isdigit(name[i + 2])) {
						power += Variable(name[i]) * Power(name[i + 2]);
						i += 2;
						if (i + 1 != name.size() && name[i + 1] != '*')
							throw "Invalid monom syntax!";
					}
					else if (name[i + 1] == '*') {
						power += Variable(name[i]);
						i++;
					}
					else throw "Invalid power syntax in monom!";
				}
				else if (i + 1 == name.size())
					power += Variable(name[i]);
				else if (i + 2 == name.size())
					throw "Invalid polinom syntax!";
			}
			else if (name[i] != '*' && i + 1 != name.size())
				throw "Invalid monom syntax!";
		}
	}
	next = NULL;
	prev = NULL;
}

void Monom::monout(Monom& mon) {
	double epsilon = 0.0000001; // ��� ���������
	if (abs(mon.coeff) < epsilon) return;//�������� ������!
	if (mon.coeff < 0) std::cout << " - ";//����� ����� �������
	else if (mon.coeff > 0 && mon.prev != NULL)std::cout << " + ";

	bool flag = 0;
	if (abs(mon.coeff) - 1 > epsilon && mon.power != 0) {
		std::cout << abs(mon.coeff);
		flag = 1;
	}
	else if (mon.power == 0) { // ������� �������, �� ����� coeff �������� ������
		std::cout << abs(mon.coeff);
		return;
	}
	//��� ��� ����, ����� ��� ������ ��������� �������� ���������� � �� ������� ���������
	std::string bukvi = "xyz";
	std::string pow;
	if (mon.power / 100 != 0) pow = std::to_string(mon.power);
	else if ((mon.power / 10) % 10 != 0) pow = "0" + std::to_string(mon.power);
	else pow = "00" + std::to_string(mon.power);

	for (int i = 0; i < bukvi.size(); i++) {
		if (flag && pow[i] != '0') std::cout << "*";
		if (pow[i] != '0')std::cout << bukvi[i];
		if (pow[i] != '1' && pow[i] != '0')std::cout << "^" << pow[i];
		if (pow[i] != '0') flag = 1;
	}
}

Monom::Monom(Monom& mon) {
	coeff = mon.coeff;
	power = mon.power;
	name = mon.name;
	next = NULL;
	prev = NULL;
}

Monom::Monom(double c, int pow) {
	this->coeff = c;
	this->power = pow;
	name = "x*y*z"; //��������� ���, ����� �� ������ � ������������ ��������
	next = NULL;
	prev = NULL;
}

Monom* Monom::NextMon() {
	return this->next;
}

Monom Monom::operator+(const Monom& mon) {
	Monom NewMon(coeff+mon.coeff,power);
	return NewMon;
}

Monom& Monom::operator=(const Monom& mon) {
	coeff = mon.coeff;
	power = mon.power;
	name = mon.name;
	next = NULL;
	prev = NULL;
	return *this;
}
bool Monom::operator!=(const Monom& mon) const {
	if (coeff != mon.coeff) return 1;
	if (power != mon.power) return 1;
	if (name != mon.name) return 1;
	return 0;
}

Monom Monom::operator*(const double val) {//��������� ������ �� ������ ������
	Monom NewMon(*this);
	NewMon.coeff *= val;
	return NewMon;
}

Monom Monom::operator*(const Monom& mon) const{ // ��������� ������ �� �����: ������� ���������� ��-�� ����, ��� �� ��������� ���� ����� ��� ������
	Monom NewMon(coeff * mon.coeff, power + mon.power);
	return NewMon;
}

Monom Monom::operator*(const Monom* mon) const {
	Monom NewMon(coeff * mon->coeff, power + mon->power);
	return NewMon;
}

std::ostream& operator<<(std::ostream& os, const Monom& mon) {
	os << mon.coeff << "*x^" << mon.power / 100 << "*y^" << (mon.power / 10) % 10 << "*z^" << mon.power % 10;
	return os;
}



//���� ��� ����� ������ ����� �������, ����� �� ���������� � �������� �������� (��� ��������� ���� ��� � �������, ���� �������� ���)
//�� ��� ������������� � ��������������� �������
List List::GetPolinomFrUser(std::string pol) { //������� ��������� ������� ����� ��������� � ��������� � ����
	if (pol.size() < 1) throw "Invalid regular statemant!";
	List NewList;
	int count = 0;
	Monom* ptr = head;
	while (count < pol.size()) {
		//������� ����� ������� ������ �� ������ � �������� �� � Monom
		std::string token = "";
		while (pol[count]!= '+' && pol[count]!='-' && count < pol.size())	{
			token += pol[count];
			count++;
		}
		Monom mon(1.0, token); //��������� ���� ����� � ��������� ��� � ������ (�������)
		NewList.NewMonInList(mon);
		count++;
	}
	return NewList;
}



void List::NewMonInList(Monom& mon) { // �������� � ������ ��������� ����� (�� ������!)
	if (mon.coeff == 0) return; //���� ����� � �����. ����, �� ��������� ������
	if (head == NULL) {
		Monom* monom = new Monom(mon);
		head = monom;
		return;
	}
	Monom* ptr = head;
	while (ptr != NULL) {
		if (mon.power > ptr->power) {//���� ������� ������ ������, ��� � head, �� ����� head
			Monom* monom = new Monom(mon);
			monom->next = ptr;
			monom->prev = ptr->prev;
			if (ptr->prev != NULL) ptr->prev->next = monom;
			ptr->prev = monom;

			if (ptr == head) head = monom;
			return;
		}
		else if (mon.power < ptr->power) {
			if (ptr->next != NULL)
				ptr = ptr->next;
			else {
				Monom* monom = new Monom(mon);
				monom->prev = ptr;
				monom->next = ptr->next;
				if (ptr->next != NULL) ptr->next->prev = monom;
				ptr->next = monom;
				return;
			}
		}
		else if (mon.power == ptr->power) {
			ptr->coeff += mon.coeff;
			if (ptr->coeff == 0) MonOutFromList(*ptr); // ���� ���-�� ����������, �� ������� ��� �� ������ � �� ������ ����
			return;
		}
	}
}

void List::MonOutFromList(Monom& mon) { // �������� �������� �� ������
	if (mon.next != NULL) mon.next->prev = mon.prev;
	if (mon.prev != NULL) mon.prev->next = mon.next;
	mon.next = NULL;
	mon.prev = NULL;
}

void List::ListOut() { // ������ ���������� ��� ���������� �������� ������
	//Monom c(0, 0);
	Monom* ptr = head;;
	while (ptr != NULL) {		
		ptr->monout(*ptr);		
		ptr = ptr->next;
	}
	std::cout << std::endl << std::endl;;
}

Monom List::GetMonom() {
	Monom mon = *head;
	if (head->next != NULL) {
		head = head->next;
		head->prev = NULL;
	}
	return mon;
}

List& List::operator+=(Monom& monom) {
	if (head == NULL) {
		head = &monom;
		return *this;
	}
	Monom* current = head;
	while (current->next != NULL) current = current->next;
	current->next = &monom;
	monom.prev = current;
	return *this;
}

List List::operator+(const List& list) { //����� ������� ����� �������, � �� ����� ������� �������
	List NewList;	
	Monom* current = NewList.head;
	Monom* current1 = head;
	Monom* current2 = list.head;

	while (current1 != NULL && current2 != NULL) {
		Monom monom(0, 0);
		if (current1->power > current2->power) {
			monom = *current1;
			current1 = current->next;
		}
		else if (current1->power < current2->power) {
			monom = *current2;
			current2 = current2->next;
		}
		else if (current1->power == current2->power) {
			monom = *current1 + *current2;
			current1 = current1->next;
			current2 = current2->next;
		}
		else if(current == NULL) current = &monom;
		NewList += monom;
	}
	while (current1!=NULL) {
		Monom m(*current1);
		NewList += m;
		current1 = current1->next;
	}
	while (current2 != NULL) {
		Monom m(*current2);
		NewList += m;
		current2 = current2->next;
	}
	return NewList;
}

List List::operator+(const Monom& mon) {
	Monom NewMon(mon.coeff, mon.power);
	List res;

	// �������� ������������ ������ � ����� ������
	Monom* current = head;
	while (current != NULL) {
		res.NewMonInList(*current);
		current = current->next;
	}

	// ��������� ����� �����
	res.NewMonInList(NewMon);

	return res; // ����������� �������� �����������, ���� �� ��������� ���������	
}

List& List::operator=(const List& list) {
	if (this != &list) { // ��������� ����������������
		// ����������� ������� 
		while (head != NULL) {
			Monom* temp = head;
			head = head->next;
			delete temp;
		}
		// �������������� ��������� ��� ������ ������
		head = NULL;
		// �������� �������� �� ������� ������
		Monom* current = list.head;
		while (current != NULL) {
			this->NewMonInList(*current); //����� *this += monom, ��� monom ������ �� ������ *current �� ������, ��� ��� ��� �������� � 
			current = current->next;
		}
	}
	return *this;
}

List List::operator*(const double val) const { // ��������� ������ �� ������ ������
	List NewList(*head);
	Monom* ptr = NewList.head;
	while (ptr != NULL) {
		ptr->coeff *= val;
		ptr = ptr->next;
	}
	return NewList;
}

List operator*(const double val, const List& l) noexcept { // ��������� ������ �� ������ �����
	List NewList;
	return NewList * val;
}

List List::operator*(const Monom mon) const{
	Monom NewMon(0, 0);
	List res;
	Monom* ptr = this->head;
	while (ptr!=NULL) {
		NewMon = mon * (*ptr);
		res = res.operator+(NewMon); //�� ����� �������� � = ���������� ������
		ptr = ptr->next;
	}
	return res;
}

List List::operator*(const List& list) const{//��������� �������� �� �������
	List NewList;
	List res;
	Monom* ptr = this->head;
	while (ptr!=NULL) {
		NewList = list * (*ptr); //�������� ������ �� ������ ����� ���������
		res = res + NewList;
		ptr = ptr->next;
	}
	return res;
}