#include <iostream>
#include <string>
#include "SafeArray.h"

using namespace std;

int main()
{
  cout << "Dynamic Memory Lab" << endl;

  SafeArray <string>* s1 = new SafeArray <string> ();
  
  
  s1->push_back("hello");
  s1->push_back("brave");
  s1->push_back("new");
  s1->push_back("world");

  SafeArray <string>* s2 = new SafeArray <string> (*s1);
  cout << s2->getCapacity() << endl;
  cout << s2->size() << endl;
  s2->printAll();
  SafeArray <string>* s3 = new SafeArray <string> (*s1);
  SafeArray <string>* s4 = new SafeArray <string> (0);
  cout << s4->getCapacity() << endl;
  cout << s4->size() << endl;
  try{
    s4->insert(3, "string");
  }
  catch(exception& error){
    cout << error.what() << endl;
  }
  
  s4->push_back("cheese");
  s4->printAll();
  

  try{
    
    for(int i = 0; i < 100; i++){
       s2->printAll();
       cout << s2->size() << endl;
       cout << s2->getCapacity() << endl;
	s2->insert(2, "string");
	cout << s2->size() << endl;
	s2->insert(3, "cheese");
	s2->printAll();
	cout << s2->size() << endl;
	s2->insert(4, "pretty");
	cout << s2->size() << endl;
	s2->insert(105, "please");
	s2->printAll();
	s2->insert(2, *s1);
	s2->printAll();

	s2->remove(0);
	s2->printAll();

	s2->removeRange(0,5);
	SafeArray <int> intArr;
	intArr.push_back(10);
	intArr.printAll();

	cout << i << endl << endl;	
		
    }

    s2->removeRange(0,100);
    s2->removeRange(-1,100);
  }
  catch(exception& error){
    cout << error.what() << endl;
    //exit(0);
  }

  //delete s1;
  s1 = NULL;
  delete s2;
  s2 = NULL;
  delete s3;
  s3 = NULL;
  delete s4;
  s4 = NULL;
    
  return 0;
}
