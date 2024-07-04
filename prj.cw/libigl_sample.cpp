//
// vcpkg install libigl[core,opengl,glfw]
// vcpkg install tinyspline

#include <igl/opengl/glfw/Viewer.h>
#include <igl/writePLY.h>

#include <tinysplinecxx.h>

#include <cmath>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuizmoWidget.h>
#include <sstream>
#include <vector>

#include <igl/per_vertex_normals.h>

#include <opencv2/opencv.hpp>

class Shell {
public:
  Shell();
  Shell(const Shell&) = delete;
  Shell& operator=(const Shell&) = delete;
  ~Shell() = default;
  Shell(const double& a, const double& b);
  void SetW(const double w) { w_ = w; }
  void SetH(const double h) { h_ = h; }
public:
  tinyspline::BSpline spline_;    // medial spline
  Eigen::MatrixXd medial_poly_;   // medial polyline
  //Eigen::MatrixXd section_poly_;  // shell closed polyline
  Eigen::MatrixXd shell_surf_v_;   // shell surface vertex
  Eigen::MatrixXi shell_surf_f_;  // shell surface faccets
  std::vector<int> side_v_;
  double r_ = 0.4;                //  iccv
  double w_ = 0.5;                //
  double h_ = 0.5;                //
  int n_medial_seg_ = 3;        // medial uniform segments count
  int z_seg_ = 4;
private:
  void UpdateCountour();
  void UpdateShell();
  void eigen_sort_rows_by_head(Eigen::MatrixXd &A);
  void Upline();
  void Lid();
  void Cube();
};

Shell::Shell() {
  /*/spline_ = tinyspline::BSpline::interpolateCubicNatural(
    { -1.0, -1.0, 0, // P1
    //0.0, 0.0, 0.0,
      1.0, 2.0, 0,  // P2
        3.0, 3.5, 0, // P3
        4.0, 3.0, 0, // P4
        7.0, 4.0, 0, // P5
    }, 3);*/ //  < -dimensionality of the points
  spline_ = tinyspline::BSpline::interpolateCubicNatural(
    { 
      -1.0, 0.0, 0.0,
      1.0, 0.0, 0.0, 
      2.0, 0.0, 0.0,
      4.0, 0.0, 0.0,

    }, 3);
  UpdateCountour();
  UpdateShell();
  for (int i = 0; i < z_seg_; i++) {
    Upline();
  }
  Lid();
  Cube();
}

Shell::Shell(const double& a, const double& b) : n_medial_seg_(a-1), z_seg_(b-1) {
  spline_ = tinyspline::BSpline::interpolateCubicNatural(
    { -1.0, -1.0, 0, // P1
    //0.0, 0.0, 0.0,
      1.0, 2.0, 0,  // P2
        3.0, 3.5, 0, // P3
        4.0, 3.0, 0, // P4
        7.0, 4.0, 0, // P5
    }, 3); //  < -dimensionality of the points
  /*/spline_ = tinyspline::BSpline::interpolateCubicNatural(
    {
      -1.0, 0.0, 0.0,
 //     1.0, 0.0, 0.0,
 //     2.0, 0.0, 0.0,
      4.0, 0.0, 0.0,

    }, 3);*/
  UpdateCountour();
  UpdateShell();
  for (int i = 0; i < z_seg_; i++) {
    Upline();
  }
  Lid();
  Cube();
}

void Shell::UpdateCountour() {
  const int n_points = n_medial_seg_ + 1;
  auto knots = spline_.uniformKnotSeq(n_points);
  auto points = spline_.evalAll(knots);
  auto tnb_vectors = spline_.computeRMF(knots);

  double len_spline_(0);
  int x(3), y(4), z(5);
  while (z + 1 <= points.size()) {
    len_spline_ += std::sqrt(std::pow(points[x - 3] - points[x], 2) + std::pow(points[y - 3] - points[y], 2) + std::pow(points[z - 3] - points[z], 2));
    x += 3;
    y += 3;
    z += 3;
  }
  double len = len_spline_ / n_points;
  const int tn_points = n_points * 100;
  auto knots2 = spline_.uniformKnotSeq(tn_points);
  auto points2 = spline_.evalAll(knots2);
  int count(0);
  int i(0);
  while (count + 1 < n_points) {
    double x2(0), y2(0), z2(0);
    while ((std::sqrt(std::pow(points[count * 3] - points2[i], 2) + std::pow(points[count * 3 + 1] - points2[i + 1], 2) + std::pow(points[count * 3 + 2] - points2[i + 2], 2)) < len)) {
      x2 = (points2[i] + points2[i + 3]) / 2;
      y2 = (points2[i + 1] + points2[i + 4]) / 2;
      z2 = (points2[i + 2] + points2[i + 5]) / 2;
      i += 3;
    }
    points[count * 3 + 3] = x2;
    points[count * 3 + 4] = y2;
    points[count * 3 + 5] = z2;
    count += 1;
  }
  Eigen::MatrixXd pts1(n_points, 3);
  Eigen::MatrixXd pts2(n_points, 3);
  medial_poly_ = Eigen::MatrixXd(n_points, 3);
  for (int i = 0; i < tnb_vectors.size(); i += 1) {
    const Eigen::Vector3d pt{ points[i * 3], points[i * 3 + 1], points[i * 3 + 2] };
    medial_poly_.row(i) = pt;
    const auto& normal = tnb_vectors.at(i).binormal(); // normal vector
    const Eigen::Vector3d n{ normal.x(), normal.y(), normal.z() }; // TODO: rewrite
    pts1.row(i) = pt + n * r_;
    pts2.row(n_points - i - 1) = pt - n * r_;
  }
  eigen_sort_rows_by_head(medial_poly_);
  //std::cout << medial_poly_ << std::endl;
  //section_poly_ = Eigen::MatrixXd(pts1.rows() + pts2.rows(), pts1.cols());
  //section_poly_ << pts1, pts2;
}

void Shell::UpdateShell() {
  const int n_m = medial_poly_.rows();
  //const int n_u = section_poly_.rows(); // number of poins in direction 0u
  const int n_v = 2;                    // number of point layers in direction 0v
  auto dv = Eigen::Vector3d{ 0.0, h_ / (n_v - 1), 0.0 };
  //auto dz = Eigen::Vector3d{ 0.0, 0.0, 0.0 };

  Eigen::MatrixXd& v = shell_surf_v_;
  //v = Eigen::MatrixXd(n_u * 2 * (n_v + 2), 3);
  v = Eigen::MatrixXd(2* n_m * (n_v - 1), 3);
  // bottom medial line
  v.block(0, 0, n_m, 3) = medial_poly_;

  // top medial line
  auto medial_top = v.block(n_m, 0, n_m, 3);
  medial_top = medial_poly_;
  for (int i = 0; i < n_m; i += 1) {
    medial_top.row(i) += dv;
  }
  /*hell
  for (int i = 0; i < n_v - 1; i += 1) {
    auto section = v.block(n_u * (1 + i), 0, n_u, 3);
    section = section_poly_;
    for (int i = 0; i < n_u; i += 1) {
      section.row(i) += dz;
    }
  }*/
  
  Eigen::MatrixXi& f = shell_surf_f_;
  //f = Eigen::MatrixXi(n_u * 2 - 4, 3);
  f = Eigen::MatrixXi(2*n_m - 2, 3);
  for (int i = 0; i < n_m - 1; i += 1) {
    f(i, 0) = i;
    f(i, 1) = n_m + i;
    f(i, 2) = i + 1;

    f(i + n_m-1, 0) = i + 1;
    f(i + n_m-1, 1) = i + n_m;
    f(i + n_m-1, 2) = i + n_m + 1;
  }
}

void Shell::Upline() {
  int n_m = n_medial_seg_*2;
  int n = (n_medial_seg_+1) * 2;
  int start = shell_surf_v_.rows() - n;
  Eigen::MatrixXd v = shell_surf_v_;
  Eigen::MatrixXd z(n, 3);
  for (int i = 0; i < n; i++) {
    z(i, 0) = v(i + start, 0);
    z(i, 1) = v(i + start, 1);
    z(i, 2) = v(i + start, 2) + (shell_surf_v_(1, 0) - shell_surf_v_(0, 0));
    if (i >= n / 2) {
      side_v_.push_back(i + start);
    }
  }
  shell_surf_v_ = Eigen::MatrixXd(v.rows() + z.rows(), 3);
  shell_surf_v_ << v, z;
  Eigen::MatrixXi old = shell_surf_f_;
  Eigen::MatrixXi new_(n_m, 3);
  for (int i = 0; i < n_m/2; i += 1) {
    new_(i, 0) = i + start;
    new_(i, 1) = i + 1 + start;
    new_(i, 2) = i + n + start;

    new_(i + n_m/2, 0) = i + 1 + start;
    new_(i + n_m/2, 1) = i + n + start + 1;
    new_(i + n_m/2, 2) = i + n + start;
  }
  Eigen::MatrixXi new_side(n_m, 3);
  for (int i = 0; i < n_m / 2; i += 1) {
    new_side(i, 0) = i + n/2 + start;
    new_side(i, 1) = i + n + n / 2 + start;
    new_side(i, 2) = i + 1 + n / 2 + start;

    new_side(i + n_m / 2, 0) = i + 1 + n / 2 + start;
    new_side(i + n_m / 2, 1) = i + n + n / 2 + start;
    new_side(i + n_m / 2, 2) = i + n + n / 2 + start + 1;
  }
  /*Eigen::MatrixXi new_1(n_m, 3);
  for (int i = 0; i < n_m / 2; i += 1) {
    new_1(i, 0) = i + start/2;
    new_1(i, 1) = i + n / 2 + start/2;
    new_1(i, 2) = i + 1 + start/2;

    new_1(i + n_m / 2, 0) = i + 1 + start/2;
    new_1(i + n_m / 2, 1) = i + n/2 + start/2;
    new_1(i + n_m / 2, 2) = i + n/2 + start/2 + 1;
  }
  Eigen::MatrixXi f(n_m, 3);
  for (int i = 0; i < n_m/2; i += 1) {
    f(i, 0) = i + n + start;
    f(i, 1) = i + n + n/2 + start;
    f(i, 2) = i + 1 + n + start;

    f(i + n_m/2, 0) = i + 1 + n + start;
    f(i + n_m/2, 1) = i + n/2+ n + start;
    f(i + n_m/2, 2) = i + n/2+ 1 + n + start;
  }*/
  Eigen::MatrixXi ff{{start, start + n, start + n / 2},
  { start + n / 2, start + n, start + n + n / 2},
    {start +n/2-1, start + n - 1, start + n / 2 - 1 + n },
    { start + n - 1, start + 2 * n - 1 , start + n / 2 - 1 + n }};
  shell_surf_f_ = Eigen::MatrixXi(shell_surf_f_.rows() + 2*n_m + ff.rows(), 3);
  shell_surf_f_ << old, new_, new_side, ff;
}

void Shell::Lid() {
  int n_m = n_medial_seg_ * 2;
  int n = (n_medial_seg_ + 1) * 2;
  int start = shell_surf_v_.rows() - n;
  for (int i = n / 2; i < n; i++) {
    side_v_.push_back(i + start);
  }
  Eigen::MatrixXi old = shell_surf_f_;
  Eigen::MatrixXi f(n_m, 3);
  for (int i = 0; i < n_m / 2; i += 1) {
    f(i, 0) = i + start;
    f(i, 1) = i + 1 + start;
    f(i, 2) = i + n/2 + start; 

    f(i + n_m / 2, 0) = i + 1 + start;
    f(i + n_m / 2, 1) = i + n / 2 + 1 + start;
    f(i + n_m / 2, 2) = i + n / 2 + start;
  }
  shell_surf_f_ = Eigen::MatrixXi(f.rows() + old.rows(), 3);
  shell_surf_f_ << old, f;
}

void Shell::Cube() {
  Eigen::Vector3d min_ = shell_surf_v_.colwise().minCoeff();
  Eigen::Vector3d max_ = shell_surf_v_.colwise().maxCoeff();
  double mn, mx;
  mn = std::min(min_(0), std::min(min_(1), min_(2)));
  mn = 1 - mn;
  mx = (std::max(max_(0), std::max(max_(1), max_(2)))) + mn;
  mx = std::abs(mx);
  for (int i = 0; i < shell_surf_v_.rows(); i++) {
    shell_surf_v_(i, 0) = (shell_surf_v_(i, 0) + mn)/(mx+1);
    shell_surf_v_(i, 1) = (shell_surf_v_(i, 1) + mn)/(mx+1);
    shell_surf_v_(i, 2) = (shell_surf_v_(i, 2) + mn)/(mx+1);
  }
}

Eigen::MatrixXd CalcContour(
    const tinyspline::BSpline& crv, 
    const int n_points, 
    const double r = 0.1) {
  const int count_points = 101;
  auto knots = crv.uniformKnotSeq(n_points);
  auto points = crv.evalAll(knots);
  auto tnb_vectors = crv.computeRMF(knots);
  Eigen::MatrixXd pts1(n_points, 3);
  Eigen::MatrixXd pts2(n_points, 3);
  for (int i = 0; i < tnb_vectors.size(); i += 1) {
    const Eigen::Vector3d pt{points[i * 3], points[i * 3 + 1], points[i* 3 + 2]};
    const auto& normal = tnb_vectors.at(i).binormal(); // normal vector
    const Eigen::Vector3d n{ normal.x(), normal.y(), normal.z()}; // TODO: rewrite
    pts1.row(i) = pt + n * r;
    pts2.row(n_points - i - 1) = pt - n * r;
  }
  Eigen::MatrixXd pts(pts1.rows() + pts2.rows(), pts1.cols());
  pts << pts1, pts2;
  return pts;
}


void Extrusion(Shell& s, cv::Mat1b& im, cv::Mat1f im_neg) {
  int sdvg(0);
  Eigen::MatrixXd N;
  igl::per_vertex_normals(s.shell_surf_v_, s.shell_surf_f_, N);
  for (int i = 0; i < im.rows; i++) {
    for (int j = 0; j < im.cols; j++) {
      auto scale = im_neg.at<float>(i, j) * 0.01;
      //if (imb_neg.at<float>(j, i) == 255) 
      {
        s.shell_surf_v_(s.side_v_[j + sdvg], 0) += scale * N(s.side_v_[j + sdvg], 0);
        s.shell_surf_v_(s.side_v_[j + sdvg], 1) += scale * N(s.side_v_[j + sdvg], 1);
        s.shell_surf_v_(s.side_v_[j + sdvg], 2) += scale * N(s.side_v_[j + sdvg], 2);
      }
    }
    sdvg += im.cols;
  }
}


int main() {
  
  //picture
  cv::Mat1b img(200, 300);
  img = 255;
  cv::circle(img, { img.cols / 2, img.rows / 2 }, 25, { 200 }, -1);
  // print text
  cv::putText(img, "Hello, OpenCV!", cv::Point(30, img.rows / 2), cv::FONT_HERSHEY_DUPLEX, 1.0, { 30 }, 2);
  cv::Mat1b imb_neg(img.size(), CV_8UC1);
  imb_neg = 255 - img;

  cv::imshow("image", imb_neg);
  cv::Mat1f imf_neg;
  imb_neg.convertTo(imf_neg, CV_32FC1, 2.0 / 255.0);
  cv::Mat1f imf_noise = cv::Mat(imf_neg.size(), CV_32FC1);
  float std_dev = 0.05;
  cv::randn(imf_noise, 0.0f, std_dev);
  cv::GaussianBlur(imf_neg, imf_neg, {}, 1.0, 1.0);
  imf_neg += imf_noise;

  //surf.shell_surf_v_(surf.side_v_[surf.side_v_.size()/2], 1) += 0.05;
  Shell surf(img.cols, img.rows);

  //img+surf
  Extrusion(surf, img, imf_neg);

  Eigen::MatrixXd& V = surf.shell_surf_v_;
  Eigen::MatrixXi& F = surf.shell_surf_f_;

  //igl::writeOBJ("curv.obj", surf.section_poly_, surf.f_);
  igl::writeOBJ("surf.obj", V, F);
  //igl::writeOFF("surf.off", surf.shell_surf_v_, surf.shell_surf_f_);
  igl::writePLY("surf.ply", V, F);

  igl::opengl::glfw::Viewer viewer;

    // Load a mesh in OFF format
  viewer.data().set_mesh(V, F);
    // Find the bounding box
  //Eigen::Vector3d m = V.colwise().minCoeff();
  Eigen::Vector3d m{0, 0, 0};
  //Eigen::Vector3d M = V.colwise().maxCoeff();
  Eigen::Vector3d M{1, 1, 1};
  
  // Corners of the bounding box
  Eigen::MatrixXd V_box(8, 3);
  V_box <<
    m(0), m(1), m(2),
    M(0), m(1), m(2),
    M(0), M(1), m(2),
    m(0), M(1), m(2),
    m(0), m(1), M(2),
    M(0), m(1), M(2),
    M(0), M(1), M(2),
    m(0), M(1), M(2);

  // Edges of the bounding box
  Eigen::MatrixXi E_box(12, 2);
  E_box <<
    0, 1,
    1, 2,
    2, 3,
    3, 0,
    4, 5,
    5, 6,
    6, 7,
    7, 4,
    0, 4,
    1, 5,
    2, 6,
    7, 3;

  // Plot the mesh
  //viewer.data().set_mesh(V, F);
  //viewer.data().set_mesh(surf.side_v_, surf.side_f_);
  
  // Plot the corners of the bounding box as points
  viewer.data().add_points(V_box, Eigen::RowVector3d(1, 0, 0));

  // Plot the edges of the bounding box
  for (unsigned i = 0; i < E_box.rows(); ++i)
    viewer.data().add_edges
    (
      V_box.row(E_box(i, 0)),
      V_box.row(E_box(i, 1)),
      Eigen::RowVector3d(0.5, 0, 0)
    );
  viewer.data().point_size = 5;

  // Plot labels with the coordinates of bounding box vertices
  std::stringstream l1;
  l1 << m(0) << ", " << m(1) << ", " << m(2);
  viewer.data().add_label(m + Eigen::Vector3d(-0.007, 0, 0), l1.str());
  std::stringstream l2;
  l2 << M(0) << ", " << M(1) << ", " << M(2);
  viewer.data().add_label(M + Eigen::Vector3d(0.007, 0, 0), l2.str());
  // activate label rendering
  viewer.data().show_custom_labels = true;

  igl::opengl::glfw::imgui::ImGuiPlugin imgui_plugin;
  viewer.plugins.push_back(&imgui_plugin);

  igl::opengl::glfw::imgui::ImGuizmoWidget gizmo;
  imgui_plugin.widgets.push_back(&gizmo);
  // Initialize ImGuizmo at mesh centroid
  gizmo.T.block(0, 3, 3, 1) =
    0.5 * (V.colwise().maxCoeff() + V.colwise().minCoeff()).transpose().cast<float>();
  // Update can be applied relative to this remembered initial transform
  const Eigen::Matrix4f T0 = gizmo.T;
  // Attach callback to apply imguizmo's transform to mesh
  gizmo.callback = [&](const Eigen::Matrix4f& T)
  {
    const Eigen::Matrix4d TT = (T * T0.inverse()).cast<double>().transpose();
    viewer.data().set_vertices(
      (V.rowwise().homogeneous() * TT).rowwise().hnormalized());
    viewer.data().compute_normals();
  };

  gizmo.operation = ImGuizmo::TRANSLATE;
   
  viewer.launch();

  return 0;
}

void Shell::eigen_sort_rows_by_head(Eigen::MatrixXd& A)
{
  std::vector<Eigen::VectorXd> vec;
  for (int64_t i = 0; i < A.rows(); ++i)
    vec.push_back(A.row(i));

  std::sort(vec.begin(), vec.end(), [](Eigen::VectorXd const& t1, Eigen::VectorXd const& t2) { return t1(0) < t2(0); });

  for (int64_t i = 0; i < A.rows(); ++i)
    A.row(i) = vec[i];
};