#include "../header/connector.h"

Connector::Connector() {
    lhs = 0;
}

Connector::Connector(Base* left) {
    lhs = left;
}
