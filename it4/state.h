#ifndef STATE_H
#define STATE_H

#include <vector>

/*      ======================================================================================       */

/*
 *      Hrana může být neobarvená, nebo je přiřazena do množiny vrcholů X, nebo Y.
 */
enum Color { X, Y, NONE };

/*      ======================================================================================       */

class State {
  
public:
                                State               (void);
                                State               (int curr_min,
                                                     int glob_min,
                                                     int colored,
                                                     std::vector<Color> nodes)
                                                    : curr_min(curr_min), glob_min(glob_min), colored(colored), nodes(nodes) { }
    
    int                         getMin              ( void ) const { return curr_min;      }
    int                         getGlobal           ( void ) const { return glob_min;      }
    int                         getColored          ( void ) const { return colored;       }
    Color                       getNode             ( int x) const { return nodes.at(x);   }
    std::vector<Color>          getNodes            ( void ) const { return nodes;         }
    
    std::vector<int>            serializeTask       ( void );
    
private:
    int                         curr_min;
    int                         glob_min;
    int                         colored;
    std::vector<Color>          nodes;
    
};

std::vector<int> State::serializeTask( void ) {
    
    std::vector<int> buffer;
    
    buffer.push_back(curr_min);
    buffer.push_back(glob_min);
    buffer.push_back(colored);
    
    for (auto const i: nodes) buffer.push_back(i);
    
    buffer.push_back(-1);
    
    return buffer;
}

static State parseSerializedTask( std::vector<int> serializedData ) {
    
    int _curr = serializedData.at(0);
    int _glob = serializedData.at(1);
    int _col  = serializedData.at(2);
    std::vector<Color> _nodes;
    
    for (int i = 3; serializedData.at(i) != -1; i++) {
        
        _nodes.push_back((Color) serializedData.at(i));
    }
    
    return State(_curr, _glob, _col, _nodes);
}

#endif
