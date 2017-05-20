// Element.cpp
// created by Kuangdai on 27-Mar-2016 
// base class of AxiSEM3D spectral elements

#include "Element.h"
#include "Point.h"

#include "Gradient.h"
#include "PRT.h"

Element::Element(Gradient *grad, PRT *prt, 
    const std::array<Point *, nPntElem> &points):
mGradient(grad), mPRT(prt) {
    mMaxNr = mMaxNu = -1;
    for (int i = 0; i < nPntElem; i++) {
        mPoints[i] = points[i];
        mMaxNr = std::max(mMaxNr, mPoints[i]->getNr());
        mMaxNu = std::max(mMaxNu, mPoints[i]->getNu());
    }
}

Element::~Element() {
    delete mGradient;
    if (hasPRT()) {
        delete mPRT;
    }
}

void Element::addSourceTerm(const arPP_CMatX3 &source) const {
    for (int i = 0; i < nPntElem; i++) {
        mPoints[i]->addToStiff(source[i]);
    }
}

bool Element::axial() const {
    return mPoints[0]->axial();
}

std::string Element::costSignature() const {
    std::stringstream ss;
    ss << verbose() << "$DimAzimuth=" << mMaxNr << "$Axial=" << (axial() ? "T" : "F");
    return ss.str();
}

