#include <fstream>
#include <string>
#include <chrono>

#ifndef __MAIN__
#include "main.h"
#endif

/*      |--------------------------------------------------|
 *      | Minimální hranový řez hranově ohodneceného grafu |
 *      |--------------------------------------------------|
 *      |
 *      | Nalezněte rozdělení množiny uzlů V do dvou disjunktních podmnožin X, Y tak,
 *      | že množina X obsahuje a uzlů, množina Y obsahuje n-a uzlů a součet ohodnocení hran {u,v} takových,
 *      | že u je z X a v je z Y (čili velikost hranového řezu mezi X a Y), je minimální.
 *
 *
 *
 *          |-----------|
 *          | Parametry |
 *          |-----------|
 *          | n             - počet uzlů grafu (10-150)
 *          | a             - velikost jedné z disjunktních podmnnožin vrcholů (5-n/2)
 *          | G(V, E)       - jednoduchý souvislý neorientovaný hranově ohodnocený graf
 *
 *
 */


int main ( int argc, char **argv ) {
    
    if (argc != 4) {
        
        std::cout << "Bad input!" << std::endl << "Usage: " << argv[0] << " <filename> <a> <threads_to_use>" << std::endl;
        return 1;
    }
    
    std::string filePath("../graf_mro/");
    filePath.append(argv[1]);
    
    std::ifstream inputFile;
    inputFile.open(filePath);
    
    if (! inputFile.is_open()) {
        
        std::cout << "Bad filename!" << std::endl << "Usage: " << argv[0] << " <filename> <a>" << std::endl;
        return 2;
    }
    
    int size = 0;
    int load = 0;
    
    inputFile >> size;
    
    CGraph graph(std::atoi(argv[2]));
    
    std::vector<Color> nodes;
    
    int j = 0;
    
    for (int i = 0; i < size; i++) {
        
        nodes.push_back(NONE);
        graph.createNode();
        
        for (j = 0; j < i; j++) {
            
            inputFile >> load;
            graph.getLast().addNeighbor( load );
        }
        for (; j < size; j++) {
            inputFile >> load;
        }
    }
    
    /*      ===========================================================       */
    
    // TIMER START
    auto start = std::chrono::high_resolution_clock::now();
    
    graph.solve( nodes, std::atoi(argv[3]) );
    
    // TIMER END
    auto finish = std::chrono::high_resolution_clock::now();
    
    /*      ===========================================================       */
    
    std::chrono::duration<double> duration = (finish - start);
    
    std::cout << "Duration: ";
        if (duration.count() <= 10.0) {
            auto durationInMilliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
            std::cout << durationInMilliSeconds << " ms" << std::endl;
        } else {
            auto durationInSeconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
            std::cout << durationInSeconds << " s" << std::endl;
        }
    
    return 0;
}
