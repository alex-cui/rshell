#include "../header/connector.h"

Connector::Connector() {
    lhs = 0;
    id = "Connector";
}

Connector::Connector(Base* left) {
    lhs = left;
    id = "Connector";
}

Base* Connector::getLeft() {
    return lhs;
}

void Connector::swapLeft(Base* left) {
    lhs = left;
}
