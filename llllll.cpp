#include <iostream>
#include <string>
#include <fstream>
#define random(min,max) min+rand()%(max-min+1)
using namespace std;
const char LETTERS[]{ 'A','B','E','K','M','H','O','P','C','T','X' };
const string COLORS[]{ "white","black","yellow","blue","red" };
const string MODELS[]{ "Mercedes","Toyota","BMW","Lexus","Tesla" };
class Car {
private:
	static string lastNumber;
	string number;
	string model;
	string color;
public:
	Car() {};
	Car(string model, string color) {
		lastNumber = generateNumber();
		this->number = lastNumber;
		this->model = model;
		this->color = color;
		if (lastNumber != "EKH")
			lastNumber = generateNumber();
	}
	string getNumber() {
		return number;
	}
	static string getLastNumber() {
		return lastNumber;
	}
	void carInfo() {
		cout << "Car number: " << number << ", model: " << model << ", color: " << color << endl;
	}
	string getModel() {
		return model;
	}
	string getColor() {
		return color;
	}
	void setColor(string color) {
		this->color = color;
	}
private:
	string generateNumber() {
		string letters = "";
		letters += lastNumber[0];
		letters += lastNumber[4];
		letters += lastNumber[5];
		int number = stoi(lastNumber.substr(1, 3));
		if (number >= 999) {
			number = 0;
			if (letters[2] == 'X') {
				letters[2] = LETTERS[0];
				if (letters[2] == 'X') {
					letters[2] = LETTERS[0];
					if (letters[0] == 'X') {
						return "EKH";
					}
					else letters[0] = findNextLetter(letters[0]);
				}
				else letters[1] = findNextLetter(letters[1]);
			}
			else letters[2] = findNextLetter(letters[2]);
		}
		else number++;
		int count = 1;
		if (number < 100 && number>9) count = 2;
		else if (number < 1000 && number>99) count = 3;
		string newNumber = "";
		newNumber += letters[0];
		for (int i = 0; i < 3 - count; i++)
		{
			newNumber += '0';
		}
		newNumber += to_string(number);
		newNumber += letters[1];
		newNumber += letters[2];
		return newNumber;
	};
	char findNextLetter(char currentLetter) {
		for (int i = 0; i < 11; i++)
		{
			if (LETTERS[i] == currentLetter) {
				return LETTERS[i + 1];
			}
		}
	}


};
string Car::lastNumber = "A000AA";
class Parking {
private:
	string name;
	int capacity;
	int size = 0;
	float price;
	Car** cars = new Car * [size];
public:
	Parking(string name, int capacity, float price) {
		this->name = name;
		this->capacity = capacity;
		this->price = price;
	}
	void setName(string name) {
		this->name = name;
	}
	string getname() {
		return name;
	}
	void setPrice(float price) {
		this->price = price;
	}
	float getPrice() {
		return price;
	}
	void addCar(Car* car) {
		if (size >= capacity) {
			cout << "Parking is full" << endl; return;
		}

		for (int i = 0; i < size; i++)
		{
			if (car->getNumber() == cars[i]->getNumber()) {
				cout << "Car alreade in parking" << endl;; return;
			}
		}
		Car** buf = new Car * [size + 1];
		for (int i = 0; i < size; i++)
		{
			buf[i] = cars[i];
		}
		buf[size] = car;	
		delete[]  cars;
		cars = buf;
		size++;
	}

	void parkInfo() {
		cout <<"Name: "<< this->name << endl;
		cout <<"Cars count: "<< this->size << endl;
		cout << "Price: " << this->price << endl << endl;
		if (size == 0)cout << "Parking is empty" << endl;
		else {
			cout << "Cars: " << endl;
			for (int i = 0; i < size; i++)
			{
				cars[i]->carInfo();
			}
		}

	}
	void deleteCar(string carIndex) {
		if (size == 0) {
			cout << "Parking is empty" << endl;
			return;
		}
		int index = -1;
		for (int i = 0; i < size; i++)
		{
			if (cars[i]->getNumber() == carIndex) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			cout << "Car is not found" << endl;
			return;
		}
		else {
			Car** buf = new Car * [size - 1];
			for (int i = 0; i < index; i++)
			{
				buf[i] = cars[i];
			}
			for (int i = 0; i < size; i++)
			{
				buf[i]=cars[i+1];
			}
			delete[] cars;
			cars = buf;
			size--;
		}

	}
};
int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	Car** cars=new Car*[100];
	
	/*for (int i = 0; i < 100; i++)
	{
		cars[i] = Car(MODELS[random(0, 4)], COLORS[random(0, 4)]);
	}
	for (int i = 0; i < 100; i++)
	{
		cars[i].carInfo();
	}*/
	string str1 = "A000AA";
	string numbers = str1.substr(1, 4);
	Parking park1("Bob", 1000, 18.99);
	for (int i = 0; i < 100; i++)
	{
		cars[i] = new Car(MODELS[random(0, 4)], COLORS[random(0, 4)]);
	}
	park1.parkInfo();
}
