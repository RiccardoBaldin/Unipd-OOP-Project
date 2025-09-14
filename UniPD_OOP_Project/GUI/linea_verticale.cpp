#include "linea_verticale.hpp"

LineaVerticale::LineaVerticale(QWidget* parent) : QFrame(parent) {
    setFrameShape(QFrame::VLine);
    setFrameShadow(QFrame::Sunken);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}
