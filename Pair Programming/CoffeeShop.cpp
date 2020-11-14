#include<iostream>

using namespace std;

// Size Category
enum BeverageSize {
	TALL = 0,
	GRANDE = 1,
	VENTI = 2,
};

// Interface
class Beverage {
private:
	// Private Field
	BeverageSize size;

public:
	// Public Field
	string description = "Unknown Beverage";

	// getDescription
	virtual string getDescription() {
		return description;
	}

	// setSize
	// Because 'size' is Private Field
	void setSize(BeverageSize newSize) {
		this->size = newSize;
	}

	// getSize
	// Because 'size' is Private Field
	virtual BeverageSize getSize() {
		return this->size;
	}

	// cost
	virtual double cost() = 0;


	// toString
	// for Clean Printing
	virtual void toString() {
		cout << "< BEVERAGE INFORMATION > " << endl;
		cout << "MENU : " << getDescription() << endl;
		switch (getSize()) {
		case TALL:
			cout << "SIZE : TALL" << endl;
			break;
		case GRANDE:
			cout << "SIZE : GRANDE" << endl;
			break;
		case VENTI:
			cout << "SIZE : VENTI" << endl;
			break;
		}
		cout << "PRICE : " << cost() << endl;
		cout << "" << endl;
	}
};

// DarkRoast
class DarkRoast : public Beverage {
public:
	// Constructor
	DarkRoast(BeverageSize size) {
		description = "Dark Roast";
		setSize(size);
	}

	// cost
	double cost() {
		return .99;
	}
};

// Decaf
class Decaf : public Beverage {
public:
	// Constructor
	Decaf(BeverageSize size) {
		description = "Decaf Coffee";
		setSize(size);
	}

	// cost
	double cost() {
		return 1.05;
	}
};

// Espresso
class Espresso : public Beverage {
public:
	// Constructor
	Espresso(BeverageSize size) {
		description = "Espresso";
		setSize(size);
	}

	// cost
	double cost() {
		return 1.99;
	}
};

// HouseBlend
class HouseBlend : public Beverage {
public:
	// Constructor
	HouseBlend(BeverageSize size) {
		description = "HouseBlend";
		setSize(size);
	}

	// cost
	double cost() {
		return .89;
	}
};

// CondimentDecorator
// Similar to Side Menu (Additional)
class CondimentDecorator : public Beverage {
public:
	Beverage* beverage;
	virtual string getDescription() = 0; // Initial
};

// Milk
class Milk : public CondimentDecorator {
public:
	// Constructor
	Milk(Beverage* beverage) {
		this->beverage = beverage;
	}

	// getDescription
	string getDescription() {
		return beverage->getDescription() + ", Milk";
	}

	// getSize
	BeverageSize getSize() {
		return beverage->getSize();
	}

	// cost
	// Different Price with Different Size
	double cost() {
		if (beverage->getSize() == TALL) {
			return .20 + beverage->cost();
		}
		else if (beverage->getSize() == GRANDE) {
			return .25 + beverage->cost();
		}
		else if (beverage->getSize() == VENTI) {
			return .30 + beverage->cost();
		}
		else {
			return 0.0;
		}
	}
};

// Mocha
class Mocha : public CondimentDecorator {
public:
	// Constructor
	Mocha(Beverage* beverage) {
		this->beverage = beverage;
	}

	// getDescription
	string getDescription() {
		return beverage->getDescription() + ", Mocha";
	}

	// getSize
	BeverageSize getSize() {
		return beverage->getSize();
	}

	// cost
	// Different Price with Different Size
	double cost() {
		if (beverage->getSize() == TALL) {
			return .10 + beverage->cost();
		}
		else if (beverage->getSize() == GRANDE) {
			return .15 + beverage->cost();
		}
		else if (beverage->getSize() == VENTI) {
			return .20 + beverage->cost();
		}
		else {
			return 0.0;
		}
	}
};

// Soy
class Soy : public CondimentDecorator {
public:
	// Constructor
	Soy(Beverage* beverage) {
		this->beverage = beverage;
	}

	// getDescription
	string getDescription() {
		return beverage->getDescription() + ", Soy";
	}

	// getSize
	BeverageSize getSize() {
		return beverage->getSize();
	}
	
	// cost
	// Different Price with Different Size
	double cost() {
		if (beverage->getSize() == TALL) {
			return .5 + beverage->cost();
		}
		else if (beverage->getSize() == GRANDE) {
			return .10 + beverage->cost();
		}
		else if (beverage->getSize() == VENTI) {
			return .15 + beverage->cost();
		}
		else {
			return 0.0;
		}
	}
};

// Whip
class Whip : public CondimentDecorator {
public:
	// Constructor
	Whip(Beverage* beverage) {
		this->beverage = beverage;
	}

	// getDescription
	string getDescription() {
		return beverage->getDescription() + ", Whip";
	}

	// getSize
	BeverageSize getSize() {
		return beverage->getSize();
	}

	// cost
	// Different Price with Different Size
	double cost() {
		if (beverage->getSize() == TALL) {
			return .5 + beverage->cost();
		}
		else if (beverage->getSize() == GRANDE) {
			return .10 + beverage->cost();
		}
		else if (beverage->getSize() == VENTI) {
			return .15 + beverage->cost();
		}
		else {
			return 0.0;
		}
	}
};

int main() {
	// bever1
	Beverage* bever1 = new Espresso(TALL);

	bever1->toString();

	// bever2
	Beverage* bever2 = new DarkRoast(GRANDE);
	bever2 = new Mocha(bever2);
	bever2 = new Mocha(bever2);
	bever2 = new Whip(bever2);

	bever2->toString();

	// bever3
	Beverage* bever3 = new HouseBlend(VENTI);
	bever3 = new Soy(bever3);
	bever3 = new Mocha(bever3);
	bever3 = new Whip(bever3);

	bever3->toString();

	return 0;
}

