#include "string"

std::string sampleSource2 =
        "procedure First {"
        "      read x;" //1
        "      read y;\n" //2
        "      call Second; }\n" //3
        "procedure Second {\n"
        "        x = 0;\n" //4
        "        i = 5;\n" //5
        "        while (i!=0) {\n" //6
        "            x = x + 2*y;\n" //7
        "            call Third;\n" //8
        "            i = i - 1; }\n" //9
        "        if (x==1) then {\n" //10
        "            x = x+1; }\n" //11
        "        else {\n"
        "            z = 1; }\n" //12
        "        z = z + x + i;\n" //13
        "        y = z + 2;\n" //14
        "        x = x * y + z; }\n" //15
        "procedure Third {\n"
        "        z = 5;\n" //16
        "        v = z;\n" //17
        "        print v; }"; //18
