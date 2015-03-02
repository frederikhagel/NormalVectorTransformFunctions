// Copyright (c) 2013, University of Southern Denmark
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 3. Neither the name of the University of Southern Denmark nor the names of
//    its contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY OF SOUTHERN DENMARK BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef COVIS_FILTER_GABOR_FILTER_H
#define COVIS_FILTER_GABOR_FILTER_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

// Own

        /**
         * @class GaborFilter
         * @ingroup filter
         * @brief Gabor filter
         * 
         * @todo Document this class
         * 
         * @sa GaborJet
         * @author Frederik Hagelskjær
         * @example example/gabor_filter/gabor_filter.cpp
         */
        class GaborFilter {
            public:
                /**
                 * Initialize Gabor filter
                 * @param ksize size of kernel in pixels
                 * @param f0 normalized frequency of the base filter
                 * @param sigma sigma of the Gauss distribution
                 * @param theta rotation in @f$[0,\pi]@f$
                 * @param scale scale of the filter
                 * @param scaling scale size of each scaling
                 */
                GaborFilter(int ksize, float f0, float sigma, float theta, float scale, float scaling);

                /// Destructor
                virtual ~GaborFilter();

                /**
                 * Apply the gabor filter to BGR or grayscale image
                 *
                 * @note If @b image has 3 channels, it is automatically converted to grayscale
                 * @note The internally used grayscale representation of the input image is normalized to the range
                 * [0,1] before filtering
                 *
                 * @param image input RGB or grayscale image, can have either integral or floating point elements
                 * @return a 1-channel floating point image representing magnitude of signal
                 */
                cv::Mat filter(const cv::Mat& image, int x, int y);

                /**
                 * Get the real kernel
                 * @return a 1-channel floating point image of the real kernel
                 */
                inline cv::Mat getRealKernel() {
                    return _realKernel;
                }

                /**
                 * Get the imaginary kernel
                 * @return a 1-channel floating point image of the imaginary kernel
                 */
                cv::Mat getImaginaryKernel() {
                    return _imaginaryKernel;
                }

            private:
                /// Scaling of the filter
                float _scaling;

		/// Size of the scaling
		float _scaleSize;
                
                /// Real kernel of the complex filter
                cv::Mat _realKernel;
                
                /// Imaginary kernel of the complex filter
                cv::Mat _imaginaryKernel;
        };

#endif
