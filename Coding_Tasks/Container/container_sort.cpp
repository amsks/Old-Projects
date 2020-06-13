/*
 * Author : Aditya Mohan 
 * Date   : 20-06-2017
 * Info	  : This source code snippet will sort a std::vector of objects based on a predefined comparator operation.
 *          In this case, the comparison is based on the member data of the object itself.
 * */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T1>
class Container1Type {
private:
    T1 data;
public:
    Container1Type( T1 initializer ) {
        data = initializer;
    }

    T1 getData() {
        return data;
    }
};

template<typename T2>
class Container2Type {
private:
    T2 data;
public:
    Container2Type( T2 initializer ) {
        data = initializer;
    }

    T2 getData() {
        return data;
    }
};

template<typename T1, typename T2>
void sortContainers( vector<Container1Type<T1> > &container1, vector<Container2Type<T2> > &container2 ) {
//    container1 will be sorted based on contents of container2.
    if ( container1.size() != container2.size() ) {
      /*  cerr << "Sizes of containers are not equal!" << endl;
        return; */

        throw ( "Sizes of containers are not equal!" ) ;
    }

    vector<pair<Container1Type<T1>, Container2Type<T2> > > containers;
    for (int i = 0; i < container2.size(); i++) {
        containers.push_back(make_pair(container1[i], container2[i]));
    }
    
    struct ordering {
        bool operator()( pair<Container1Type<T1>, Container2Type<T2> > &object1,
                        pair<Container1Type<T1>, Container2Type<T2> > &object2 ) {
            return object1.second.getData() < object2.second.getData();
        }
    };
    sort( containers.begin(), containers.end(), ordering() );
    for ( int i = 0; i < containers.size(); i++ ) {
        container1[i] = containers[i].first;
        container2[i] = containers[i].second;
    }
}

/*
void sortContainersDriver() {
    
}
*/


int main() {
   // sortContainersDriver();
    
    vector<Container1Type<string> > container1;
    vector<Container2Type<string> > container2;
    
    container1.push_back(Container1Type<string>(string("Aditya")));
    container1.push_back(Container1Type<string>(string("Aishwarya")));
    container1.push_back(Container1Type<string>(string("Bhawna")));
    
    container2.push_back(Container2Type<string>(string("A")));
    container2.push_back(Container2Type<string>(string("D")));
    container2.push_back(Container2Type<string>(string("B")));

    cout << "Before sorting: " << endl;
    for (int i = 0; i < container1.size(); i++)
        cout << container1[i].getData() << " ";
    
    cout << endl;
    
    for (int i = 0; i < container2.size(); i++)
        cout << container2[i].getData() << " ";
    
    cout << endl;

    sortContainers(container1, container2);

    cout << "After sorting: " << endl;
    for (int i = 0; i < container1.size(); i++)
        cout << container1[i].getData() << " ";
    
    cout << endl;
    
    for (int i = 0; i < container2.size(); i++)
        cout << container2[i].getData() << " ";
    
    cout << endl;


    return 0;
}
