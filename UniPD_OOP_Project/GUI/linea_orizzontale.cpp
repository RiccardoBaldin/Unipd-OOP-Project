#include "linea_orizzontale.hpp"

LineaOrizzontale::LineaOrizzontale(QWidget* parent) : QFrame(parent) {
    setFrameShape(QFrame::HLine);
    setFrameShadow(QFrame::Sunken);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}