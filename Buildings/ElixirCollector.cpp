#include "ElixirCollector.h"

ElixirCollector::ElixirCollector(Position p) 
    : ResourceGenerator(p, 3, 3, "🧪", "🔮", 
                      Resources(100, 0), 3, 
                      Resources(0, 5), 150) {}