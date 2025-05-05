#include <iostream>
#include<stdlib.h>

#include "GUI.h"
#include "Utilities.h"

using namespace std;

int main() {
    string path;
    Graph* graph = nullptr;

    GUI::entryMessage(graph);

    delete graph;
    return 0;
}