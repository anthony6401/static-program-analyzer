#include "string"

std::string sampleSource1 =
        "procedure computeCentroid {"
        "    count = 0;" // 1
        "    cenX = 0;" // 2
        "    cenY = 0;" // 3
        "    while ((x != 0) && (y != 0)) {" // 4
        "        count = count + 1;" // 5
        "        cenX = cenX + x;" // 6
        "        cenY = cenY + y;" // 7
        "    }"
        "    if (count == 0) then {" // 8
        "        flag = 1;" // 9
        "    } else {"
        "        cenX = cenX / count;" // 10
        "        cenY = cenY / count;" // 11
        "    }"
        "    normSq = cenX * cenX + cenY * cenY;" // 12
        "}";