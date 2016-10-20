//
// Created by yanlei on 16-10-20.
//
#include <string>

#include "Classifier.h"

int main()
{
    string model_file = "/home/yanlei/Documents/code/cpp/ClionProjects/caffe_cmake/cnn_age_gender/deploy_age.prototxt";
    string trained_file = "/home/yanlei/Documents/code/cpp/ClionProjects/caffe_cmake/cnn_age_gender/age_net.caffemodel";
    string mean_file = "/home/yanlei/Documents/code/cpp/ClionProjects/caffe_cmake/cnn_age_gender/mean.binaryproto";
    string label_file = "/home/yanlei/Documents/code/cpp/ClionProjects/caffe_cmake/cnn_age_gender/age_label.txt";

    string model_file_gender = "/home/yanlei/Documents/code/cpp/ClionProjects/caffe_cmake/cnn_age_gender/deploy_gender.prototxt";
    string trained_file_gender = "/home/yanlei/Documents/code/cpp/ClionProjects/caffe_cmake/cnn_age_gender/gender_net.caffemodel";
    //string mean_file = "/home/yanlei/Documents/code/cpp/ClionProjects/caffe_cmake/cnn_age_gender/mean.binaryproto";
    string label_file_gender = "/home/yanlei/Documents/code/cpp/ClionProjects/caffe_cmake/cnn_age_gender/gender_label.txt";


    Classifier age_estimator(model_file, trained_file, mean_file, label_file);
    Classifier gender_estimator(model_file_gender, trained_file_gender, mean_file, label_file_gender);

    //cv::Mat img = cv::imread("/home/yanlei/Documents/code/cpp/ClionProjects/caffe_cmake/cnn_age_gender/tmp.jpg", -1);
    cv::VideoCapture capture(0);
    cv::namedWindow("image");
    if(!capture.isOpened())
    {
        exit(0);
    }
    cv::Mat frame;
    int keyboard;
    while((char)keyboard != 'q' && (char)keyboard != 27)
    {
        capture>>frame;
        std::vector<Prediction> gender_pred = gender_estimator.Classify(frame, 1);
        std::vector<Prediction> predictions = age_estimator.Classify(frame, 1);
        for(size_t i=0; i<predictions.size();++i)
        {
            Prediction p = predictions[i];
            std::cout << std::fixed << std::setprecision(4) << p.second << " - \""
                      << p.first << "\"" << std::endl;
        }

        for(size_t i=0; i<gender_pred.size();++i)
        {
            Prediction p = gender_pred[i];
            std::cout << std::fixed << std::setprecision(4) << p.second << " - \""
                      << p.first << "\"" << std::endl;
        }
        cv::imshow("image", frame);
        keyboard=cv::waitKey(1);
    }
    capture.release();
    cv::destroyAllWindows();
    return 0;
}

