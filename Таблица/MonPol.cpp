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
		throw "Invalid monom syntax!";// проверяем, что первый  символ монома - название переменной
	if (name.size() > 0) {
		for (int i = 0; i < name.size(); i++) { // разбиваем на <переменная в степени>
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
	double epsilon = 0.0000001; // для сравнения
	if (abs(mon.coeff) < epsilon) return;//выводить нечего!
	if (mon.coeff < 0) std::cout << " - ";//знаки перед мономом
	else if (mon.coeff > 0 && mon.prev != NULL)std::cout << " + ";

	bool flag = 0;
	if (abs(mon.coeff) - 1 > epsilon && mon.power != 0) {
		std::cout << abs(mon.coeff);
		flag = 1;
	}
	else if (mon.power == 0) { // степень нулевая, то кроме coeff выводить нечего
		std::cout << abs(mon.coeff);
		return;
	}
	//это для того, чтобы без лишних махинаций выводить переменные и их степени корректно
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
	name = "x*y*z"; //дефолтное имя, чтобы не путать с исключающими случаями
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

Monom Monom::operator*(const double val) {//умножение монома на скаляр справа
	Monom NewMon(*this);
	NewMon.coeff *= val;
	return NewMon;
}

Monom Monom::operator*(const Monom& mon) const{ // умножение монома на моном: степени корректные из-за того, что их обработка идет через имя монома
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



//пока что можно ввести сумму мономов, чтобы их обработать и привести подобные (или запихнуть прям так в полином, если подобных нет)
//но без коэффициентов у соответствующих мономов
List List::GetPolinomFrUser(std::string pol) { //сделать обработку ручного ввода полиномов и выражений с ними
	if (pol.size() < 1) throw "Invalid regular statemant!";
	List NewList;
	int count = 0;
	Monom* ptr = head;
	while (count < pol.size()) {
		//сделать через нарезку строки на мономы и отправку их в Monom
		std::string token = "";
		while (pol[count]!= '+' && pol[count]!='-' && count < pol.size())	{
			token += pol[count];
			count++;
		}
		Monom mon(1.0, token); //вычленили один моном и добавляем его в список (полином)
		NewList.NewMonInList(mon);
		count++;
	}
	return NewList;
}



void List::NewMonInList(Monom& mon) { // добавить в список отдельный моном (не список!)
	if (mon.coeff == 0) return; //если моном с коэфф. ноль, то добавлять нечего
	if (head == NULL) {
		Monom* monom = new Monom(mon);
		head = monom;
		return;
	}
	Monom* ptr = head;
	while (ptr != NULL) {
		if (mon.power > ptr->power) {//если степени монома больше, чем в head, то новый head
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
			if (ptr->coeff == 0) MonOutFromList(*ptr); // если что-то занулилось, то удаляем это из списка и не храним нули
			return;
		}
	}
}

void List::MonOutFromList(Monom& mon) { // удаление элемента из списка
	if (mon.next != NULL) mon.next->prev = mon.prev;
	if (mon.prev != NULL) mon.prev->next = mon.next;
	mon.next = NULL;
	mon.prev = NULL;
}

void List::ListOut() { // должен вызываться для начального элемента списка
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

List List::operator+(const List& list) { //нужно сделать через слияние, а не через вставку мономов
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

	// Копируем существующие мономы в новый список
	Monom* current = head;
	while (current != NULL) {
		res.NewMonInList(*current);
		current = current->next;
	}

	// Добавляем новый моном
	res.NewMonInList(NewMon);

	return res; // Используйте оператор копирования, если он правильно определен	
}

List& List::operator=(const List& list) {
	if (this != &list) { // Проверяем самоприсваивание
		// Освобождаем текущие 
		while (head != NULL) {
			Monom* temp = head;
			head = head->next;
			delete temp;
		}
		// Инициализируем указатели для нового списка
		head = NULL;
		// Копируем элементы из другого списка
		Monom* current = list.head;
		while (current != NULL) {
			this->NewMonInList(*current); //через *this += monom, где monom создан по образу *current не выйдет, так как там проблема с 
			current = current->next;
		}
	}
	return *this;
}

List List::operator*(const double val) const { // умножение списка на скаляр справа
	List NewList(*head);
	Monom* ptr = NewList.head;
	while (ptr != NULL) {
		ptr->coeff *= val;
		ptr = ptr->next;
	}
	return NewList;
}

List operator*(const double val, const List& l) noexcept { // умножение списка на скаляр слева
	List NewList;
	return NewList * val;
}

List List::operator*(const Monom mon) const{
	Monom NewMon(0, 0);
	List res;
	Monom* ptr = this->head;
	while (ptr!=NULL) {
		NewMon = mon * (*ptr);
		res = res.operator+(NewMon); //не может передать в = полученный список
		ptr = ptr->next;
	}
	return res;
}

List List::operator*(const List& list) const{//умножение полинома на полином
	List NewList;
	List res;
	Monom* ptr = this->head;
	while (ptr!=NULL) {
		NewList = list * (*ptr); //умножаем список на каждый моном поочердно
		res = res + NewList;
		ptr = ptr->next;
	}
	return res;
}