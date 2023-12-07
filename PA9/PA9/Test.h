#include "List.h"
#include "Node.h"
#include "Ship.h"
#include "HisData.h"

#include <fstream>
#include <iostream>

class Test
{
public:

	Test();
	void testShipVirtual();
	void testShipInheritance();
	void testInsertAtFront();
	void testCopyList();
	void testPrintLog();
	void testDeleteAtFront();

	void testIsEmpty();

private:
	HisData testHistory;
	List<int> testList;
	List<int> testListCopy;
	List<HisData> testHis;
	std::ofstream testFile;
};
