#include <iostream>
#include <memory>
#include "component.h"

void clientCode() {
	
	/*Component* tree = new Composite();

	Component* branch_1 = new Composite();
	Component* branch_2 = new Composite();
	Component* branch_3 = new Composite();

	branch_1->add(new Circle(12, 5, 5));
	branch_1->add(new Rectangle(9, 12, 11, 5));
	
	branch_2->add(new Circle(36, 19, 4));
	Repeater* rep = new RemoveRepeater(branch_2, new Circle(36, 19, 4));
	rep->execute();

	rep->execute();
	Component* branch_4 = new Composite();
	branch_2->add(branch_4);
	branch_4->add(new Rectangle(28, 20, 4, 4));
	
	Component* branch_5 = new Composite();
	branch_5->add(new Circle(10, 25, 3));
	branch_5->add(new Rectangle(20, 18, 9, 5));
	
	branch_4->add(branch_5);

	tree->add(branch_1);
	tree->add(branch_2);
	tree->add(branch_3);

	Component* wanted = tree->admissibleArea(20, 18);
	if (wanted) {
		wanted->iam();
	}*/
	//Iterator<Component, listPtr>* it = tree->createIterator();

	//for (it->first(); !it->isDone(); it->next()) {
	//	it->current()->iam();
	//}

	Element tree(new Composite()); // Creation of a new shape object which can be either a composite or component
	std::cout << "Main window was created.\n" << std::endl;
	Element branch_1(new Composite()); // Create and add a new group;
	std::cout << "SubWindow1 was created." << std::endl;
	Element branch_2(new Composite());
	std::cout << "SubWindow2 was created." << std::endl;
	Element branch_3(new Composite());
	std::cout << "SubWindow3 was created." << std::endl;
	Element branch_4(new Composite());
	std::cout << "SubWindow4 was created." << std::endl;
	Element branch_5(new Composite());
	std::cout << "SubWindow5 was created." << std::endl;

	branch_1.add(Element(new Circle(12, 5, 5))); // Create and add a new shape to an existing group;
	std::cout << "Circle was created and added to the SubWindow1." << std::endl;
	branch_1.add(new Rectangle(9, 12, 11, 5));
	std::cout << "Rectangle was created and added to the SubWindow1." << std::endl;

	branch_2.add(new Circle(36, 19, 4));
	std::cout << "Circle was created and added to the SubWindow2." << std::endl;
	branch_2.add(branch_4);
	std::cout << "SubWindow4 was limited by SubWindow2 bounds." << std::endl;
	branch_4.add(new Rectangle(28, 20, 4, 4));
	std::cout << "Rectangle was created and added to the SubWindow4." << std::endl;
	branch_5.add(new Circle(10, 25, 3));
	std::cout << "Circle was created and added to the SubWindow4." << std::endl;
	branch_5.remove(new Circle(10, 25, 3)); // Removal of an object;
	std::cout << "Circle was removed from the SubWindow4." << std::endl;
	Element circle(new Circle(10, 25, 3));
	branch_5.add(circle.clone());
	std::cout << "A cloned circle was added to the SubWindow5." << std::endl;
	branch_5.add(new Rectangle(20, 18, 9, 5));
	std::cout << "Rectangle was added to the SubWindow5" << std::endl << std::endl;
	//std::cout << "Imagine the reverse button was clicked..." << std::endl << std::endl;
	//std::cout << "Imagine the repeat button was clicked..." << std::endl << std::endl;
	//Repeater* repeat = branch_5.lastAction();
	//repeat->reverse();
	//Repeat of the last action
	//repeat->execute();
	//std::cout << "Rectangle was deleted from the SubWIndow5" << std::endl;
	branch_4.add(branch_5);
	std::cout << "SubWindow5 was limited by SubWindow4 bounds." << std::endl;

	
	tree.add(branch_1);
	std::cout << "SubWindow1 was limited by the main window bounds." << std::endl;
	tree.add(branch_2);
	std::cout << "SubWindow2 was limited by the main window bounds." << std::endl;
	tree.add(branch_3);
	std::cout << "SubWindow3 was limited by the main window bounds." << std::endl << std::endl;

	std::cout << "What should be displayed by the front-end part:" << std::endl;
	tree.iam();

	std::cout << "\nIf have a click coordinates, i can find the deepest element there" << std::endl;
	std::cout << "Imagine that user clicked somewhere on the rectangle(20, 18) but not exactly at the center of it(17, 20)" << std::endl;
	tree.admissibleArea(17, 20)->iam();

	std::cout << "If we want to move en element, we can reset its coordinates." << std::endl;
	std::cout << "Imagine we move our rectangle that we found previously." << std::endl;
	Element rectangle1(tree.admissibleArea(17, 20));
	rectangle1.setX(10);
	rectangle1.setY(10);
	tree.iam();

	std::cout << "If we want to move out rectangle from SubWindow5 to, for example out main window" << std::endl;
	tree.add(rectangle1.move());

	tree.iam();

	return;
}


int main() {
	
	clientCode();
	
	

	return 0;
}