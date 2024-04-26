#include <igl/opengl/glfw/Viewer.h>
#include <igl/writePLY.h>
#include <igl/writeOBJ.h>

#include <opencv2/opencv.hpp>

#include <cmath>

int main() {
  cv::Mat1b img(200, 300);
  img = 255;
  cv::circle(img, { img.cols / 2, img.rows / 2 }, 25, { 200 }, -1);
  // print text
  cv::putText(img, "Hello, OpenCV!", cv::Point(30, img.rows / 2), cv::FONT_HERSHEY_DUPLEX, 1.0,{30}, 2);
  cv::Mat1b imb_neg(img.size(), CV_8UC1);
  imb_neg = 255 - img;

  cv::imshow("image", imb_neg);
  cv::Mat1f imf_neg;
  imb_neg.convertTo(imf_neg, CV_32FC1, 2.0/255.0);
  cv::Mat1f imf_noise = cv::Mat(imf_neg.size(), CV_32FC1);
  float std_dev = 0.05;
  cv::randn(imf_noise, 0.0f, std_dev);
  cv::GaussianBlur(imf_neg, imf_neg, {}, 1.0, 1.0);
  imf_neg += imf_noise;

  int point_count = imf_neg.rows * imf_neg.cols;
  Eigen::MatrixXd surf_v(point_count, 3);  // surface vertex
  Eigen::MatrixXi surf_f(2 * (imf_neg.rows - 1) * (imf_neg.cols - 1), 3);  // surface faccets


  int i_v = 0;
  int i_f = 0;
  for (int i_row = 0; i_row < imf_neg.rows; i_row += 1) {
    for (int i_col = 0; i_col < imf_neg.cols; i_col += 1) {
      const auto p = Eigen::Vector3d{ 0.5 + i_col, imf_neg.rows - 0.5 - i_row, imf_neg.at<float>(i_row, i_col) };
      surf_v.row(i_row * imf_neg.cols + i_col) = p;
      if (i_col < imf_neg.cols - 1 && i_row < imf_neg.rows - 1) {
        surf_f(i_f, 0) = i_v;
        surf_f(i_f, 1) = i_v + 1;
        surf_f(i_f, 2) = i_v + imf_neg.cols + 1;
        i_f += 1;
        surf_f(i_f, 0) = i_v;
        surf_f(i_f, 1) = i_v + imf_neg.cols + 1;
        surf_f(i_f, 2) = i_v + imf_neg.cols;
        i_f += 1;
      }
      i_v += 1;
    }
  }
  igl::writeOBJ("surf.obj", surf_v, surf_f);
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(surf_v, surf_f);
  viewer.launch();

  cv::waitKey(0);
  return 0;
}