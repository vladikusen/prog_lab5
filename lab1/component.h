#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <list>
#include <string>
#include <memory>



template<typename T, typename U>
class Iterator {
public:
	typedef typename std::list<T*>::iterator it_t;
	Iterator(U& const _children) : children(_children) {
		it = children.begin();
	};
	void first() {
		it = children.begin();
	}
	void next() {
		it++;
	}
	T* current() {
		return *it;
	}
	bool isDone() {
		return (it == children.end());
	}
	


private:
	U& children;
	it_t it;
};

class Component {
protected:
	int x{ 0 }, y{ 0 };
	Component* parent;
public:
	Component() {};
	Component(int _x, int _y) : x(_x), y(_y) {};
	virtual void add (Component* component) { };
	virtual void remove (Component* component) {};
	void setParent (Component* _parent) {
		parent = _parent;
	}
	virtual void setX(int _x) {
		x = _x;
	}
	virtual void setY(int _y) {
		y = _y;
	}
	Component* getParent () const {
		return parent;
	}
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	virtual void iam () {
		std::cout << "I am a component" << std::endl;
	};
	virtual bool isComposite () const {
		return false;
	}
	virtual Component* clone() {
		return nullptr;
	};
	Component* move() {
		Component* buffer = this->clone();
		this->getParent()->remove(this);
		return buffer;
	}

	virtual Component* admissibleArea(int _x, int _y) {
		return nullptr;
	};
	virtual Iterator<Component, std::list<Component*>>* createIterator() {
		return nullptr;
	}
};

class Command {
public:
	virtual void execute() const = 0;
};

class Repeater : public Command {
protected:
	Component* parent;
	Component* child;
public:
	Repeater(Component* _parent, Component* _child) : parent(_parent), child(_child) {};
	void execute() const override {};
	void setRepeater(Component* _parent, Component* _child) {
		parent = _parent;
		child = _child;
	}
	virtual void reverse() = 0;
};

class AddRepeater : public Repeater {
public:
	AddRepeater(Component* _parent, Component* _child) : Repeater(_parent, _child) {}
	void execute() const override {
		parent->add(child);
	}
	void reverse() override {
		parent->remove(child);
	}
};

class RemoveRepeater : public Repeater {
public:
	RemoveRepeater(Component* _parent, Component* _child) : Repeater(_parent, _child) {}
	void execute() const override {
		parent->remove(child);
	}
	void reverse() override {
		parent->add(child);
	}
};


class Leaf : public Component {
public:
	Leaf() : Component() {};
	Leaf(int _x, int _y) : Component(_x, _y) {};
	void iam() override {
		std::cout << "I am a leaf" << std::endl;
	}
};

class Circle : public Leaf {
private:
	int radius { 5 };
public:
	Circle() : Leaf() {};
	Circle(int _x, int _y, int _r) : Leaf(_x, _y), radius(_r) {};
	void iam() override {
		std::cout << "circle(" << x << ";" << y << ")" << " with radius = " << radius << std::endl;
	}
	Component* clone() override {
		return new Circle(*this);
	}
	Component* admissibleArea(int _x, int _y) override {
		if (_x >= (x - radius) && _x <= (x + radius)) {
			if (_y >= (y - radius) && _y <= (y + radius)) {
				return this;
			}
		}
		return nullptr;
	};

};

class Rectangle : public Leaf {
private:
	int lenght{ 5 }, height{ 5 };
public:
	Rectangle() : Leaf() {};
	Rectangle(int _x, int _y, int _l, int _h) : Leaf(_x, _y), lenght(_l), height(_h) {};
	void iam() override {
		std::cout << "rectangle(" << x << ";" << y << ")" << " with height = " << height << " and length = " << lenght << std::endl;
	}
	Component* clone() override {
		return new Rectangle(*this);
	}
	Component* admissibleArea(int _x, int _y) override {
		if (_x >= (x - lenght / 2) && _x <= (x + lenght / 2)) {
			if (_y >= (y - height / 2) && _y <= (y + height / 2)) {
				return this;
			}
		}
		return nullptr;
	};
};

using listPtr = std::list<Component*>;



class Composite : public Component {
private:
	listPtr children;
public:
	void add(Component* component) override {
		component->setParent(this);
		int currentX = component->getX();
		int currentY = component->getY();
		component->setX(currentX - x);
		component->setY(currentY - y);
		children.push_back(component);
	}
	void remove(Component* component) override {
		component->setParent(nullptr);
		children.remove(component);
	}
	Iterator<Component, listPtr>* createIterator() override {
		return new Iterator<Component, listPtr>(this->children);
	}
	void iam() override {
		std::cout << "group of: " << std::endl;
		Iterator<Component, listPtr>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			it->current()->iam();
		}
		
		
	}
	Component* clone() override {
		return new Composite(*this);
	}

	Component* admissibleArea(int _x, int _y) override {
		for (auto& child : children) {
			if (child->admissibleArea(_x, _y) != nullptr) {
				return child->admissibleArea(_x, _y);
			}
		}
		return nullptr;
	}
};

class Element {
private:
	Component* element;
	Repeater* repeater;
public:
	Element(Component* _element) : element(_element) {}
	Element(Element* _element) : element(_element->element) {};
	void add(const Element& that) {
		element->add(that.element);
		repeater = new AddRepeater(this->element, that.element);
	}
	void remove(const Element& that) {
		element->remove(that.element);
		repeater = new RemoveRepeater(this->element, that.element);
	}
	void iam() {
		element->iam();
	}
	int getX() const {
		return element->getX();
	}
	int getY() const {
		return element->getY();
	}
	void setX(int _x) {
		element->setX(_x);
	}
	void setY(int _y) {
		element->setY(_y);
	}
	bool isComposite() const {
		return element->isComposite();
	}
	Repeater* lastAction() const {
		return repeater;
	}
	Element* clone() {
		return new Element(element->clone());
	}
	Element* getParent() const {
		return new Element(element->getParent());
	}
	Element* admissibleArea(int _x, int _y) {
		return new Element(element->admissibleArea(_x, _y));
	}
	Element* move() {
		return new Element(element->move());
	}
};


#endif 