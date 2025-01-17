/*
 *  RimHighlightingPass.h
 *
 *  Copyright (c) 2013, satcy, http://satcy.net
 *  All rights reserved. 
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met: 
 *  
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 *  * Neither the name of Neil Mendoza nor the names of its contributors may be used 
 *    to endorse or promote products derived from this software without 
 *    specific prior written permission. 
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 *  POSSIBILITY OF SUCH DAMAGE. 
 *
 */
#pragma once

#include "RenderPass.h"

namespace itg
{
class LimbDarkeningPass : public RenderPass
{
public:
    typedef shared_ptr<LimbDarkeningPass> Ptr;

    LimbDarkeningPass(const ofVec2f &aspect,
                      bool arb,
                      float radialScale = 1.2,
                      float brightness = 2.5,
                      ofColor startColor = ofColor(255, 255, 255),
                      ofColor endColor = ofColor(255, 255, 255));

    void render(ofFbo &readFbo, ofFbo &writeFbo);

    void setRadialScale(float val) { radialScale = val; };
    ofParameter<float> &getRadialScale() { return radialScale; }

    void setBrightness(float val) { brightness = val; }
    ofParameter<float> getBrightness() { return brightness; }

    void setStartColor(const ofColor &val) { startColor = val; }
    ofParameter<ofColor> &getStartColor() { return startColor; }

    void setEndColor(const ofColor &val) { endColor = val; }
    ofParameter<ofColor> &getEndColor() { return endColor; }

private:
    ofShader shader;
    ofParameter<ofColor> startColor;
    ofParameter<ofColor> endColor;
    ofParameter<float> radialScale;
    ofParameter<float> brightness;
};
} // namespace itg
