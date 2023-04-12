#ifndef STATE_H
#define STATE_H

#include <vector>

class State {
  
public:
                                State               (void);
                                State               (int min,
                                                     int colored,
                                                     std::vector<Color> nodes)
                                                    : min(min), colored(colored), nodes(nodes) { }
    
    int                         getMin              (void) { return min;        }
    int                         getColored          (void) { return colored;    }
    std::vector<Color>          getNodes            (void) { return nodes;      }
    
private:
    int                         min;
    int                         colored;
    std::vector<Color>          nodes;
    
};

std::vector<int> State::serializeTask( void ) {
    
    std::vector<int> buffer;
    
    buffer.push_back(min);
    buffer.push_back(colored);
    
    for (auto const i: nodes) buffer.push_back(i);
    
    buffer.push_back(-1);
    
    return buffer;
}

static State parseSerializedTask( std::vector<int> serializedData ) {
    
    int _min = serializedData.at(0);
    int _col = serializedData.at(1);
    std::vector<Color> _nodes;
    
    for (int i = 2; serializedData.at(i) != -1; i++) {
        
        nodes.push_back((Color) serializedData.at(i));
    }
    
    return State(_min, _col, _nodes);
}

#endif
