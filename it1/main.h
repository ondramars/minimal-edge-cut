#include <vector>
#include <iostream>
#include <iomanip>    // std::setw
#include <ios>        // std::left

/*      ========================================================================================================================       */


/*
 *      Hrana může být neobarvená, nebo je přiřazena do množiny vrcholů X, nebo Y.
 */
enum Color { X, Y, NONE };

/*      ========================================================================================================================       */


/*
 *      Třída reprezentující vrchol, uchovávající informace o barvě vrcholu a jeho sousedech.
 *
 *      Poskytuje rozhraní umožňující nastavit a získat informaci o barvě,
 *      přidat záznam o sousedovi a získat jejich seznam.
 */
class CNodeNeighbor {
    
public:
                            CNodeNeighbor       (void)                  { }
    
    void                    addNeighbor         (int value)             { _neighbors.push_back( value ); }
    std::vector<int> &      getNeighbors        (void)                  { return _neighbors; }
    
private:
    std::vector<int>        _neighbors;
};

/*      ========================================================================================================================       */

/*
 *      Třída reprezentující graf, umožňující provádět výpočet pro problém minimálního hranového řezu hranově ohodnoceného grafu.
 *
 *      Obsahuje vector vrcholů, záznam o globálním minimu a počtu obarvených vrcholů.
 */
class CGraph {
    
public:
                            CGraph              (int a)
                            : ALFA(a), _global_min(INT_MAX) { }
    
    void                    createNode          (void)                  { _neighbors.emplace_back(); }
    
    int                     cutWeight           (Color, int, std::vector<Color> &); // spočítá změnu váhy způsobenou posledním obarveným vrcholem
    bool                    canColorTo          (Color, std::vector<Color> &); // omezení velikosti disjunktních množin
    bool                    minTooMuch          (int min);              // minimum je v této větvi příliš velké
    bool                    lowerEstimate       (int min, int, std::vector<Color> &); // může vůbec být řez ještě minimum?
    void                    checkCandidate      (int min, std::vector<Color> &);  // kandidát na nové globální minimum
    
    CNodeNeighbor &         getLast             (void)                  { return _neighbors.back(); }
    
    void                    printNode           (CNodeNeighbor n);
    void                    printAllNodes       (void);
    void                    printResult         (void);
    
    void                    DFS                 (int min, int depth, std::vector<Color> nodes);
    
private:
    int                                 ALFA;
    int                                 _global_min;
    std::vector<CNodeNeighbor>          _neighbors;
    std::vector<Color>                  _best_conf;
};

int CGraph::cutWeight( Color color, int colored, std::vector<Color> & nodes ) {
    
    int curr_min = 0;
    
    const std::vector<int> neighbors = _neighbors.at( colored ).getNeighbors();
    
    for (int i = 0; i < neighbors.size(); i++) {
        
        if ( nodes.at(i) != nodes.at( colored ) )
                 curr_min += neighbors.at(i);
    }
    
    return curr_min;
}

bool CGraph::canColorTo( Color color, std::vector<Color> & nodes ) {
    
    int colorCntX = 0;
    int colorCntY = 0;
    
    for (Color c: nodes) {
        
        switch (c) {
            case X:
                colorCntX++;
                break;
                
            case Y:
                colorCntY++;
                break;
                
            default:
                break;
        }
    }
    
    return (color == X && colorCntX < ALFA) || (color == Y && colorCntY < nodes.size() - ALFA);
}

bool CGraph::minTooMuch(int min) {
    return min >= _global_min;
}

// vrátí true pokud je možné v částečném řezu pokračovat a nalézt nové globální minimum, jinak false
bool CGraph::lowerEstimate(int min, int colored, std::vector<Color> & nodes) {
    
    for (int c = colored; c < nodes.size(); c++) {
        
        int Xmin = 0;
        int Ymin = 0;
        
        const std::vector<int> neighbors = _neighbors.at(c).getNeighbors();
            
        for (int i = 0; i < neighbors.size() && i < colored; i++) {
                
            if ( nodes.at(i) != X )
                Xmin += neighbors.at(i);
                
            if ( nodes.at(i) != Y )
                Ymin += neighbors.at(i);
        }
        
        min += std::min(Xmin, Ymin);
        
        if (min > _global_min) {
            return false;
        }
    }
    
    return true;
}

void CGraph::checkCandidate(int min, std::vector<Color> & nodes) {
    if (min < _global_min) {
        _global_min = min;
        _best_conf.clear();
        for (Color c: nodes) {
            _best_conf.emplace_back( c );
        }
    }
}

void CGraph::DFS(int min, int colored, std::vector<Color> nodes) {
    
    // UKONČUJÍCÍ PODMÍNKY
    if (colored == nodes.size()) {
        checkCandidate(min, nodes); // máme nový rekord?
        return;
    }
    if (minTooMuch(min) || !lowerEstimate(min, colored, nodes)) {
        return;
    }
 
    // PŘIŘADÍME DALŠÍ UZEL DO X POKUD SE TAM VEJDE A ZKONTROLUJEME ZDA TO MÁ SMYSL
    if (canColorTo(X, nodes)) {
        
        nodes.at( colored ) = X;
        
        int Xmin = cutWeight(X, colored, nodes);
        
        DFS(Xmin + min, colored + 1, nodes);
        
        nodes.at( colored ) = NONE;
    }
    
    // PŘIŘADÍME DALŠÍ UZEL DO Y POKUD SE TAM VEJDE A ZKONTROLUJEME ZDA TO MÁ SMYSL
    if (canColorTo(Y, nodes)) {
        
        nodes.at( colored ) = Y;
        
        int Ymin = cutWeight(Y, colored, nodes);
        
        DFS(Ymin + min, colored + 1, nodes);
        
        nodes.at( colored ) = NONE;
    }
}

/*      ========================================================================================================================       */

/*
 *      Printing methods.
 */

void CGraph::printNode(CNodeNeighbor n) {
    
    std::cout << "Cnode's neighbors: ";
    
    for (int i: n.getNeighbors()) {
        
        std::cout << i << ", ";
    }
    
    std::cout << std::endl;
}

void CGraph::printAllNodes() {

    for (CNodeNeighbor c: _neighbors) {
        
        printNode(c);
    }
}

void CGraph::printResult() {
    
    for (Color c: _best_conf) {
        
        std::cout << c << ", ";
    }
    std::cout << std::endl << std::endl;
    
    for (int n = 0; n < _best_conf.size(); n++) {
        
        const std::vector<int> neighbors = _neighbors.at(n).getNeighbors();
        
        std::cout << "Node " << std::setfill ('0') << std::setw(2) << std::right << n+1 << ".: ";
        
        for (int i = 0; i < neighbors.size(); i++) {
            
            if (_best_conf.at(n) != _best_conf.at(i) )
                std::cout << std::setfill (' ') << "w(" << std::setfill ('0') << std::setw(2) << std::right << n+1 << "," << std::setw(2) << std::right << i+1 << ")=" << std::setfill (' ') << std::setw(5) << std::left << neighbors[i];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "MIN = " << _global_min << std::endl;
}

/*      ========================================================================================================================       */
