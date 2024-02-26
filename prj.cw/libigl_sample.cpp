//
// vcpkg install libigl[core,opengl,glfw]
// vcpkg install tinyspline

#include <igl/opengl/glfw/Viewer.h>
#include <igl/writePLY.h>

#include <tinysplinecxx.h>

#include <cmath>


class Shell {
public:
  Shell();
  Shell(const Shell&) = delete;
  Shell& operator=(const Shell&) = delete;
  ~Shell() = default;

  void SetW(const double w) { w_ = w; }
  void SetH(const double h) { h_ = h; }
public:
  tinyspline::BSpline spline_;    // medial spline
  Eigen::MatrixXd medial_poly_;   // medial polyline
  Eigen::MatrixXd section_poly_;  // shell closed polyline
  Eigen::MatrixXd shell_surf_v_;   // shell surface vertex
  Eigen::MatrixXi shell_surf_f_;  // shell surface faccets
  double r_ = 0.4;                //  iccv
  double w_ = 10.0;                //
  double h_ = 10.0;                //
  int n_medial_seg_ = 100;        // medial uniform segments count
private:
  void UpdateCountour();
  void UpdateShell();
};

Shell::Shell() {
  spline_ = tinyspline::BSpline::interpolateCubicNatural(
    { 1.0, -1.0, 0, // P1
      -1.0, 2.0, 0,  // P2
        1.0, 4.0, 0, // P3
        4.0, 3.0, 0, // P4
        7.0, 5.0, 0, // P5
    }, 3); //  < -dimensionality of the points
  UpdateCountour();
  UpdateShell();
}

void Shell::UpdateCountour() {
  const int n_points = n_medial_seg_ + 1;
  auto knots = spline_.uniformKnotSeq(n_points);
  auto points = spline_.evalAll(knots);
  auto tnb_vectors = spline_.computeRMF(knots);
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
  section_poly_ = Eigen::MatrixXd(pts1.rows() + pts2.rows(), pts1.cols());
  section_poly_ << pts1, pts2;
}

void Shell::UpdateShell() {
  const int n_m = medial_poly_.rows();
  const int n_u = section_poly_.rows(); // number of poins in direction 0u
  const int n_v = 2;                    // number of point layers in direction 0v
  auto dv = Eigen::Vector3d{ 0.0, h_ / (n_v - 1), 0.0 };
  auto dz = Eigen::Vector3d{ 0.0, 0.0, r_ };

  Eigen::MatrixXd& v = shell_surf_v_;
  //v = Eigen::MatrixXd(n_u * 2 * (n_v + 2), 3);
  v = Eigen::MatrixXd(n_u * 2 * (n_v - 1), 3);
  // bottom medial line
  v.block(0, 0, n_m, 3) = medial_poly_;
  v.block(0, 0, n_m, 3) = medial_poly_;

  // top medial line
  auto medial_top = v.block(n_m, 0, n_m, 3);
  medial_top = medial_poly_;
  for (int i = 0; i < n_m; i += 1) {
    medial_top.row(i) += dv;
  }
  // shell
  for (int i = 0; i < n_v - 1; i += 1) {
    auto section = v.block(n_u * (1 + i), 0, n_u, 3);
    section = section_poly_;
    for (int i = 0; i < n_u; i += 1) {
      section.row(i) += dz;
    }
  }

  Eigen::MatrixXi& f = shell_surf_f_;
  //f = Eigen::MatrixXi(n_u * 2 - 4, 3);
  f = Eigen::MatrixXi(n_u - 2, 3);
  for (int i = 0; i < n_m - 1; i += 1) {
    f(i, 0) = i;
    f(i, 1) = n_u + i + 1;
    f(i, 2) = i + 1;

    f(i, 0) = i;
    f(i, 1) = n_u + i + 1;
    f(i, 2) = i + 1;

    f(i + n_m - 1, 0) = i + 1;
    f(i + n_m - 1, 1) = i + n_u;
    f(i + n_m - 1, 2) = i + n_u + 1;
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

int main() {
  Shell surf;

  //igl::writeOBJ("curv.obj", surf.section_poly_, surf.f_);
  igl::writeOBJ("surf.obj", surf.shell_surf_v_, surf.shell_surf_f_);
  //igl::writeOFF("surf.off", surf.shell_surf_v_, surf.shell_surf_f_);
  igl::writePLY("surf.ply", surf.shell_surf_v_, surf.shell_surf_f_);

  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(surf.shell_surf_v_, surf.shell_surf_f_);
  viewer.launch();

  return 0;
}
