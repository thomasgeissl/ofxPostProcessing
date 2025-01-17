/*
 *  LimbDarkeningPass.cpp
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
#include "LimbDarkeningPass.h"

namespace itg
{
LimbDarkeningPass::LimbDarkeningPass(const ofVec2f &aspect,
                                     bool arb,
                                     float radialScale,
                                     float brightness,
                                     ofColor startColor,
                                     ofColor endColor) : radialScale(radialScale), brightness(brightness), startColor(startColor), endColor(endColor), RenderPass(aspect, arb, "limbdarkening")
{

    string fragShaderSrc = STRINGIFY(
        uniform sampler2D myTexture;
        uniform float fAspect;

        uniform vec3 startColor;
        uniform vec3 endColor;

        uniform float radialScale; //0. - 1.0 - 2.0
        uniform float brightness;  //0.-1.0, deff:2.5
        void main() {
            vec2 vUv = gl_TexCoord[0].st;
            vec2 vSunPositionScreenSpace = vec2(0.5);

            vec2 diff = vUv - vSunPositionScreenSpace;

            // Correct for aspect ratio

            diff.x *= fAspect;

            float prop = length(diff) / radialScale;
            prop = clamp(2.5 * pow(1.0 - prop, 3.0), 0.0, 1.0);

            vec3 color = mix(startColor, endColor, 1.0 - prop);

            vec4 base = texture2D(myTexture, vUv);
            gl_FragColor = vec4(base.xyz * color, 1.0);
        });

    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, "#version 110\n" + fragShaderSrc);
    shader.linkProgram();

    this->startColor.set("startColor", startColor);
    this->endColor.set("endColor", endColor);
    this->radialScale.set("radialScale", radialScale, 0, 5);
    this->brightness.set("brightness", brightness, 0, 1);

    parameters.add(this->startColor);
    parameters.add(this->endColor);
    parameters.add(this->radialScale);
    parameters.add(this->brightness);
}

void LimbDarkeningPass::render(ofFbo &readFbo, ofFbo &writeFbo)
{
    writeFbo.begin();

    shader.begin();
    shader.setUniformTexture("myTexture", readFbo.getTexture(), 0);
    shader.setUniform1f("fAspect", 1);
    shader.setUniform3f("startColor", (float)(startColor->r / 255), (float)(startColor->g / 255), (float)(startColor->b / 255));
    shader.setUniform3f("endColor", (float)(endColor->r / 255), (float)(endColor->g / 255), (float)(endColor->b / 255));
    shader.setUniform1f("radialScale", radialScale);
    shader.setUniform1f("brightness", brightness);

    texturedQuad(0, 0, writeFbo.getWidth(), writeFbo.getHeight());

    shader.end();
    writeFbo.end();
}
} // namespace itg
