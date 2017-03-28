#include <iostream>
#include <string>
using namespace std;
/*
Declare and implement the Animal, Cat, Fish, and Dog classes named in the sample program below in such a way
that the program compiles, executes, and produces the output shown. Do not IN ANY WAY change the implementations
of petAnimal or main.

All animals have a name, a sound they make, and a way they move.

You may implement the classes inline if you like to save typing.
Your class declarations should go before the petAnimal method.

*/

class Animal {
protected:
	Animal(string n) { m_name = n; } // needs to be protected to prevent animals from being instantiated

public:
	~Animal() { cout << "The " + m_species << ": " << m_name << ", is dead" << endl; } // kill the animal :'(

	void setSound(string s) { m_sound = s; } // mutators
	void setMovement(string m) { m_movement = m; }
	void setSpecies(string s) { m_species = s; }

	string getSpecies() const {return m_species;} // getters
	string getName() const { return m_name; }
	string makeSound() const { return m_sound; }
	string moves() const { return m_movement; }

private:
	string m_name, m_sound, m_movement, m_species; // variables for an animal
};

class Dog : public Animal {
public:
	Dog(string n) : Animal(n)  {
		setSound("Arf"); // use mutators to set the dog's characteristics
		setMovement("walks");
		setSpecies("Dog");
	}
};

class Fish : public Animal {
public:
	Fish(string n) : Animal(n)  {
		setSound("---"); // use mutators to set the fish's characteristics
		setMovement("swims");
		setSpecies("Fish");
	}
};

class Cat : public Animal {
public:
	Cat(string n, int age) : Animal(n)  {
		if (age <= 2) // get cat age
			setSound("Mew"); // if 2 or younger, Mew
		else
			setSound("Meow"); // else the cat Meows
		setMovement("walks");
		setSpecies("Cat");
	}
};

void petAnimal(const Animal *pet) {
	cout << "You pet " << pet->getName() << " and it says "
		<< pet->makeSound() << " then it " << pet->moves() << " away." << endl;
}

/*during testing, set numWorking to the number of array spots your code can do correctly
and comment out the lines creating the other Animals until you have implemented them.

For example, first get Dog to work.  Set numWorking to 1 and comment out the lines creating
pets[1] .. pets[3] since you haven't made them yet.  Don't code Fish or Cat until
Dog is completely correct.  That way, you don't duplicate mistakes*/

const int numWorking = 4;

void main() {
	Animal * pets[numWorking];
	pets[0] = new Dog("Cliff");
	pets[1] = new Fish("Shamoo");
	pets[2] = new Cat("Nirble", 2);  //Cats have an age that determines their sound.
									 //2 and under Mew, 3 and older Meow.  It is a whole number.
	pets[3] = new Cat("Garfield", 3);
	for (int i = 0; i<numWorking; i++)
		petAnimal(pets[i]);

	cout << "\nDeleting pets.\n";
	for (int i = 0; i<numWorking; i++) //clean up after your pets
		delete pets[i];

}
/*
The above main must produce output between the -------------------:
-------------------
You pet Cliff and it says Arf then it walks away.
You pet Shamoo and it says --- then it swims away.
You pet Nirble and it says Mew then it walks away.
You pet Garfield and it says Meow then it walks away.

Deleting pets.
The Dog: Cliff, is dead
The Fish: Shamoo, is dead
The Cat: Nirble, is dead
The Cat: Garfield, is dead
-------------------

You may NOT in any way change main or the petAnimal functions.
This means that the parameter to petAnimal must be const as shown.
Note the difference between the 1 year old Nirble and the 2 year old Garfield.
(OK, Garfield is a LOT older, but he'd scratch me if I gave his age away).

*NO* code or data may be duplicated between the individual classes (with
the possible/partial exception of empty methods).

An additional requirement is that the following MUST NOT compile
Animal pet("generic");
You can create a Dog, but not a generic Animal instance.

Animal must not have a default constructor.  It must have a constructor that takes 1 parameter
and that parameter must be used meaningfully.

Note that not all Dogs are named Cliff so your code should not rely on that.  Similarly for the others.

Inheritance and virtual are the keys so play with virtual.

Submit a single cpp file named inherit-animal.cpp
*/