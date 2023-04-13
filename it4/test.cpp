#include <assert.h>
#include <iostream>

#include "state.h"
/*
std::ostream & operator << ( std::ostream & os, const State & obj)
{
    os << "Min: " << obj.getMin() << ", ";
    os << "Col: " << obj.getColored() << ", ";
    os << "Nodes: " << obj.getNodes() << std::endl;
    
    return os;
}*/

inline bool operator == (const State& lhs, const State& rhs)
{
    if ( lhs.getMin()           !=      rhs.getMin()            ||
         lhs.getColored()       !=      rhs.getColored()        ||
         lhs.getNodes().size()  !=      rhs.getNodes().size()   )
        return false;
    
    int size = lhs.getNodes().size();
    
    for (int i = 0; i < size; i++) {
        
        if (lhs.getNode(i) != rhs.getNode(i)) return false;
    }
    
    return true;
}

inline bool operator != (const State& lhs, const State& rhs) {
    return !(lhs == rhs);
}

void testStateSerialization( void ) {
    
    std::cout << "Test: serialization:" << std::endl;
    
    State s1(100, 20, { X, Y, Y, NONE, X, Y, X, X, NONE });
    State s2(100, 10, { X, Y, Y, NONE, X, Y, X, X, NONE });
    State s3(200, 20, { X, Y, Y, X, Y, X, X, NONE });
    State s4(100, 20, { X, Y, Y, X, Y, X, X, NONE });
    State s5(100, 20, { X, Y, Y, NONE, X, Y, X, X, NONE });
    
    std::vector<int> serializedData1 = s1.serializeTask();
    std::vector<int> serializedData2 = s2.serializeTask();
    std::vector<int> serializedData3 = s3.serializeTask();
    
    State s6 = parseSerializedTask( serializedData1 );
    State s7 = parseSerializedTask( serializedData2 );
    State s8 = parseSerializedTask( serializedData3 );
    
    assert( s1 == s6 ); std::cout << " --> TEST 01 OK" << std::endl;
    assert( s2 == s7 ); std::cout << " --> TEST 02 OK" << std::endl;
    assert( s3 == s8 ); std::cout << " --> TEST 03 OK" << std::endl;
    
    assert( s1 == s1 ); std::cout << " --> TEST 04 OK" << std::endl;
    assert( s1 != s2 ); std::cout << " --> TEST 05 OK" << std::endl;
    assert( s1 != s3 ); std::cout << " --> TEST 06 OK" << std::endl;
    assert( s1 != s4 ); std::cout << " --> TEST 07 OK" << std::endl;
    assert( s1 == s5 ); std::cout << " --> TEST 08 OK" << std::endl;
    
    assert( s5 == s6 ); std::cout << " --> TEST 09 OK" << std::endl;
    assert( s5 != s7 ); std::cout << " --> TEST 10 OK" << std::endl;
    assert( s5 != s8 ); std::cout << " --> TEST 11 OK" << std::endl;
}

int main ( int argc, char **argv ) {
    
    testStateSerialization();
}
