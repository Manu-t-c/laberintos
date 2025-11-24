#ifndef TESORO_H
#define TESORO_H

#include <string>

class Tesoro {
private:
    std::string tipo;

public:
    Tesoro();
    Tesoro(const std::string& tipo);

    std::string getTipo() const;
};
};



#endif //TESORO_H
