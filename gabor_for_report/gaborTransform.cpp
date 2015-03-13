#include "gaborTransform.hpp"


// Standard library includes
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>




//include cv2
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;

#include <covis/covis.h>
using namespace covis;

#include "transform.hpp"






inline std::vector< std::vector< float> > getPixelJet( cv::Mat jet, int rows){

    std::vector< std::vector<float> > response;

    std::vector<cv::Mat> jet_vector( jet.channels() );

    cv::split( jet, jet_vector );

    int rotations = jet.channels() / rows;

    for(int i=0; i < rows; i++){
        std::vector<float> theta_result;
        for(int j=0; j < rotations ; j++){
            cv::Mat wavelet_blured;
            cv::blur(jet_vector[i * rotations + j], wavelet_blured,cv::Size(13,13));
            int y = wavelet_blured.rows/2;
            int x = wavelet_blured.cols/2;
            theta_result.push_back( wavelet_blured.at<float>( y, x )  );
        }
        response.push_back( theta_result );

    }
    return response;
}


inline std::vector< std::vector< std::vector<float> > > getGridPixels( cv::Mat jet, int rows){

    std::vector< std::vector< std::vector<float> > > gridResponse;
    std::vector< std::vector<float> > response;

    std::vector<cv::Mat> jet_vector( jet.channels() );
    cv::split( jet, jet_vector );
    int rotations = jet.channels() / rows;

    std::vector< std::vector<int> > pos;
    std::vector<int> tmp;
    tmp.push_back(0);
    tmp.push_back(0);
    pos.push_back( tmp );

//    tmp.at(0) = -40;
//    tmp.at(1) = -40;
//    pos.push_back( tmp );
//    tmp.at(0) = 40;
//    pos.push_back( tmp );
//    tmp.at(1) = 40;
//    pos.push_back( tmp );
//    tmp.at(0) = -40;
//    pos.push_back( tmp );


//    tmp.at(0) = -80;
//    tmp.at(1) = -80;
//    pos.push_back( tmp );
//    tmp.at(0) = 80;
//    pos.push_back( tmp );
//    tmp.at(1) = 80;
//    pos.push_back( tmp );
//    tmp.at(0) = -80;
//    pos.push_back( tmp );


    for(int gridIndex = 0; (unsigned) gridIndex < pos.size(); gridIndex++){

        for(int i=0; i < rows; i++){
            std::vector<float> theta_result;
            for(int j=0; j < rotations ; j++){
                cv::Mat wavelet_blured;
                cv::blur(jet_vector[i * rotations + j], wavelet_blured,cv::Size(13,13));
                int y = wavelet_blured.rows/2 + pos[gridIndex][0];
                int x = wavelet_blured.cols/2 + pos[gridIndex][1];
                theta_result.push_back( wavelet_blured.at<float>( y, x )  );
            }
            response.push_back( theta_result );
        }

        gridResponse.push_back(response);
    }
    return gridResponse;
}



inline float compareSinglePixelShift(std::vector<std::vector<float> > pixelJet1, std::vector<std::vector<float> > pixelJet2 ){
    float dot = 0;
    float norm1 = 0;
    float norm2 = 0;

    float best_rotation_response = 0;

    int rotations = pixelJet1[0].size();

    for(int shift = 0; (unsigned)shift < rotations; shift++ ){
        for(int i=0; (unsigned)i < pixelJet1.size(); i++){
            for(int j=0; (unsigned)j < pixelJet1[i].size(); j++){
                dot += pixelJet1[i][j] *  pixelJet2[i][(j + shift)%pixelJet2[i].size()];
                norm1 += pixelJet1[i][j] * pixelJet1[i][j];
                norm2 += pixelJet2[i][(j + shift)%pixelJet2[i].size()] * pixelJet2[i][(j + shift)%pixelJet2[i].size()];
            }
        }

        norm1 = sqrt(norm1);
        norm2 = sqrt(norm2);

        dot /= norm1 * norm2;
        if(dot > best_rotation_response){
            best_rotation_response = dot;
        }

    }

    return best_rotation_response;
}




gaborTransform::gaborTransform(int ks, float f0, float sigma, int n_of_theta,  int start_scale, int end_scale, float k){

    _rows = end_scale - start_scale;

    _jet = filter::GaborJet(ks, f0, sigma, n_of_theta, start_scale, end_scale, k);

}


gaborTransform::~gaborTransform() {}


std::vector< std::vector< std::vector<float> > >  gaborTransform::getTransformedPixelJet( cv::Mat image, cv::Mat depth, int x, int y ){


    /** Transform image first **/

    transform plane_transform;

    cv::Mat transformed_image = plane_transform.transform_image(image, depth, x, y);

    /** Filter single pixel **/

    cv::Mat onePixelSourceROI(transformed_image, cv::Rect( cv::Point(x,y), cv::Size(1, 1) ));

    cv::Mat wavelet_result = _jet[0].filter(onePixelSourceROI);

    std::cout << wavelet_result << std::endl;

//    std::vector< std::vector< std::vector<float> > > response = getGridPixels( wavelet_result, _rows);

    return wavelet_result;
}

void gaborMatcher::showKernel( ){

    cv::Mat realimag[2];
    realimag[0] = _jet[0].getRealJet();
    realimag[1] = _jet[0].getImaginaryJet();

    // Show
    cv::imshow("Real/imaginary jet kernels (x2)", visu::tile(realimag, 2, 1, 10, cv::Scalar::all(1), 5));
    cv::waitKey();
}
