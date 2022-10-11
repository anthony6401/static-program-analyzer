#ifndef SPA_HASHFUNCTION_H
#define SPA_HASHFUNCTION_H

#include <string>

struct hashFunction {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &pair) const {
        auto h1 = std::hash<T1>{}(pair.first);
        auto h2 = std::hash<T2>{}(pair.second);
        return h1 ^ h2;
    }
};

#endif //SPA_HASHFUNCTION_H
