#include "Test.h"

Test::Test()
{
	testFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
}

void Test::testShipVirtual()
{
	Ship testShip("12", 'a');
	Cruiser testCruiser("11", 'b');

	testShip.printPlaced();
	testShip.printPlaced();
}
void Test::testShipInheritance()
{
	Ship testShip("12", 'a');
	Cruiser testCruiser("11", 'b');

	if (testShip.getCell() == "12" && testCruiser.getDirection() == 'b')
	{
		cout << "Inheritance Success!" << endl;
	}
	else
	{
		cout << "Inheritance Failure" << endl;
	}
}

void Test::testInsertAtFront()
{
	testList.insertAtFront(3);
	testList.insertAtFront(2);
	testList.insertAtFront(1);

	if (testList.getHeadPtr()->getData() == 1 && testList.getHeadPtr()->getNextPtr()->getData() == 2)
	{
		cout << "Insert at Front Success" << endl;
	}
	else
	{
		cout << "Insert at Front Failure" << endl;
	}
}