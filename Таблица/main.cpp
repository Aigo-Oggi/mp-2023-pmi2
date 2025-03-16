#include <iostream>
#include "MonPol.h"

int main() {
	Monom head(1.0, "x*y*z");	  // головной элемент
	List list(head);			  //создаем список
	Monom mon1(1, "x^2*y*z");	  //добавляем первый элемент
	Monom mon2(2, "x*y^2*z");	  //добавляем элемент с коэффициентом, отличным от единицы
	Monom mon3(1, "x*y*z^2");
	Monom mon4(4.5, "x^2*y*z^2"); //дробный коэффициент
	Monom mon5(-1, "x*y^2*z^2");
	Monom mon6(1, "x^2*y^2*z^2"); //новый головной элемент из-за своей высокой степеНИ
	Monom mon7(-1, "x^2*y^2*z^3");//после сортировки это будет новый головной элемент с отрицательным коэффициентом
	Monom mon8(1, "x*y");		  //моном меньшего порядка
	Monom mon9(-121, "x*z");	  //короткий моном с большим коэфф.
	Monom mon10(1, "y*z");
	Monom mon11(1, "x");
	Monom monAnti11(-1, "x");	  //добавляем элемент, котрый должен уничтожить x (из полинома его должно удалить)
	Monom mon12(1, "y");
	Monom mon13(0, "z");		  //одночлен с нулевым коэфф. (его не должно вывести)
	Monom mon14(10, "");		  //свободный член

	list.NewMonInList(mon1); //list.ListOut();
	list.NewMonInList(mon2); //list.ListOut();
	list.NewMonInList(mon3); //list.ListOut();
	list.NewMonInList(mon4); //list.ListOut();
	list.NewMonInList(mon5); //list.ListOut();
	list.NewMonInList(mon6); //list.ListOut();
	list.NewMonInList(mon7);// list.ListOut();
	list.NewMonInList(mon8);// list.ListOut();
	list.NewMonInList(mon9); //list.ListOut();
	list.NewMonInList(mon10); //list.ListOut();
	list.NewMonInList(mon11); //list.ListOut();
	list.NewMonInList(mon12); //list.ListOut();
	list.NewMonInList(mon13); //list.ListOut();
	list.NewMonInList(mon14);
	list.NewMonInList(monAnti11);
	
	std::cout << "Polinom was created: \n";
	list.ListOut(); // проверяем, что полином правильно собрался (и вообще собрался)


	List pol = pol.GetPolinomFrUser("x^2*y*z^2+x^2*y^2*z^3");//ввести обработку выражений в моном
	std::cout << "Polinom from user: ";
	pol.ListOut();
	Monom mon16(-1, "x^2*y^2*z^3");
	List list1(mon4); // list1 = x*y (mon8)
	List list2(mon7); // list2 = x^2*y^2*z^2 (mon6)
	
	

	List list3;
	list3 = list1 * list2; // list3 = x^3*y^3*z^2		для mon4 и mon7 : 4,5*x^4*y*3*z^5	
	std::cout << "Result of multiplying of two polinoms: \n";
	list3.ListOut();

	std::cout << "Result of addition: \n";
	List list4;
	list4 = list1 + list2;
	list4.ListOut();

	/*std::cout << "result of multiply polinom on scalar:\n";
	list = 2 * list;
	list.ListOut();*/

	//Monom monom(1, "x^2");
	//Monom monom2(1, "y^2");
	//monom = monom * monom2;
	//monom.monout(monom);
	return 0;
}