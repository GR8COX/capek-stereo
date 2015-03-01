
// Copyright (c) 2015, Aaron Michaux
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, 
//    this list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// The views and conclusions contained in the software and documentation are
// those of the authors and should not be interpreted as representing official 
// policies, either expressed or implied, of the FreeBSD Project.

#include "stdinc.hpp"
#include "disparity.hpp"

using namespace cv;
using namespace std;

// With help from http://www.jayrambhia.com/blog/disparity-maps/

void disparity_bm(const Mat& grey0, const Mat& grey1, Mat& disp,
                  int min_disparity, 
                  int num_disparities,
                  int SAD_window_size, 
                  int disp_12_max_diff,
                  int prefilter_cap, 
                  int prefilter_size,
                  int texture_threshold,
                  int uniqueness_ratio, 
                  int speckle_window_size, 
                  int speckle_range)
{
    StereoBM sbm;
    sbm.state->minDisparity = min_disparity;
    sbm.state->numberOfDisparities = num_disparities;
    sbm.state->SADWindowSize = SAD_window_size;
    sbm.state->disp12MaxDiff = disp_12_max_diff;
    sbm.state->preFilterCap = prefilter_cap;
    sbm.state->preFilterSize = prefilter_size;
    sbm.state->textureThreshold = texture_threshold;
    sbm.state->uniquenessRatio = uniqueness_ratio;
    sbm.state->speckleWindowSize = speckle_window_size;
    sbm.state->speckleRange = speckle_range;

    sbm(grey0, grey1, disp, CV_32F);
}

void disparity_sgbm(const Mat& grey0, const Mat& grey1, Mat& disp,
                    int min_disparity, 
                    int num_disparities,
                    int SAD_window_size, 
                    int disp_12_max_diff,
                    int prefilter_cap, 
                    int uniqueness_ratio, 
                    int speckle_window_size, 
                    int speckle_range,
                    bool full_DP,
                    int P1,
                    int P2)
{
    StereoSGBM sgbm;

    sgbm.minDisparity = min_disparity;
    sgbm.numberOfDisparities = num_disparities;
    sgbm.SADWindowSize = SAD_window_size;
    sgbm.disp12MaxDiff = disp_12_max_diff;


    sgbm.preFilterCap = prefilter_cap;

    sgbm.uniquenessRatio = uniqueness_ratio;
    sgbm.speckleWindowSize = speckle_window_size;
    sgbm.speckleRange = speckle_range;

    sgbm.fullDP = full_DP;
    sgbm.P1 = P1;
    sgbm.P2 = P2;

    // Convert output to CV_32F
    Mat disp16;
    sgbm(grey0, grey1, disp16);

    Mat disp_out(disp16.rows, disp16.cols, CV_32F);
    for(int r = 0; r < disp16.rows; ++r)
        for(int c = 0; c < disp16.cols; ++c)
            disp.at<float>(r, c) = float(disp16.at<short>(r, c)) / 16.0f;

    disp = disp_out;
}

