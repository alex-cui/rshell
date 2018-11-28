#include "../header/connector.h"

Connector::Connector() {
    lhs = 0;
}

Connector::Connector(Base* left) {
    lhs = left;
}

Base* Connector::getLeft() {
    return lhs;
}

void Connector::swapLeft(Base* left) {
    lhs = left;
}
