 
#pragma once

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

#include "elas.h"

#define DISPARITY_METHOD_BM 0
#define DISPARITY_METHOD_SGBM 1
#define DISPARITY_METHOD_ELAS 2
#if USE_TRICLOPS == 1
#define DISPARITY_METHOD_TRICLOPS 3
#define DISPARITY_METHOD_MAX 3
#else
#define DISPARITY_METHOD_MAX 2
#endif 

// Application parameters
struct Params
{
    int show_help;
    bool okay; // params _seem_ self-consistent

    // I/O
    std::string input_filename; // input yml filename
    std::string output_filename;// output yml filename

    // Input filenames -- should all be images
    std::vector<std::string> filenames;

    // Major functions to run
    bool recalc_K;
    bool recalc_F;

    // Intrinsic options
    bool single_camera;   // one camera between pairs of images
    bool apply_undistort; // assume distortion in the camera model

    // Corner detection -- intrinsic only
    int nx, ny;          // 
    double sq_side;      // veridical size of square side

    // Run surf corner detection
    bool run_surf;
    int surf_min_hessian;
    double surf_dist_ratio;
    bool surf_lmeds;

    // Rectification options
    bool use_fusiello_rect; // Uses Hartley and Zisserman by default

    // Disparity options
    // @see http://docs.opencv.org/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html
    int disp_method; // 
    int disp_min_disparity;
    int disp_num_disparities;
    int disp_SAD_window_size; 
    int disp_12_max_diff;
    int disp_prefilter_cap; 
    int disp_prefilter_size; 
    int disp_texture_threshold;
    int disp_uniqueness_ratio; 
    int disp_speckle_window_size; 
    int disp_speckle_range; 
    bool disp_full_DP;
    int disp_P1;
    int disp_P2;

    // @see libelas/elas.h for documentation on these parameters
    Elas::parameters elas_params;

    // Exporting options
    std::string output_dir; // output directory to save images
    bool export_corner_detect;
    bool export_undistorted;
    bool export_rectified;
    bool export_surf;
    bool export_xEx_costfn;
    bool export_disparity;

    // View options
    bool show_point_cloud; // a crude point-cloud viewer in glut

    // Funds testing function
    bool test_find_E;

    // -- Methods --
    Params();       
    bool operator==(const Params& o) const;
    string disp_method_name(int method_id = -1) const;
};

void print_usage(const char * exec);
Params parse_cmd_args(int argc, char * * argv);


