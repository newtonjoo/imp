/**
 *  \file Geometry.cpp
 *  \brief XXXX.
 *
 *  Copyright 2007-8 Sali Lab. All rights reserved.
 *
 */

#include "IMP/display/geometry.h"


IMPDISPLAY_BEGIN_NAMESPACE

Geometry::Geometry( ): default_color_(.7, .7, .7){
}

Geometry::~Geometry(){}

void Geometry::show(std::ostream &out) const {
  out << "Geometry" << std::endl;
}


GeometryExtractor::~GeometryExtractor(){}
GeometryExtractor::GeometryExtractor(){}

IMPDISPLAY_END_NAMESPACE
