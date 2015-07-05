#ifndef _CUMULATIVE_DISTRIBUTION_FUNCTION_H
#define _CUMULATIVE_DISTRIBUTION_FUNCTION_H


#include <vector>


class CumulativeDistributionFunction {
  public:


  typedef double (CumulativeDistributionFunction::*dist_fun_t)(double x);

  CumulativeDistributionFunction();
  CumulativeDistributionFunction(double a, double bulge_radius, double max, int nSteps = 1000);
  CumulativeDistributionFunction(CumulativeDistributionFunction&& rhs);

  virtual ~CumulativeDistributionFunction() = default;

  CumulativeDistributionFunction& operator=(CumulativeDistributionFunction&& rhs);

  double ProbFromVal(double fVal);
  double ValFromProb(double fVal);


  private:


  dist_fun_t m_intensity_funtion;
  double m_min;
  double m_max;
  double m_width;
  int m_number_of_steps;

  // parameters for realistic star distribution
  double m_i0;
  double m_k;
  double m_a;
  double m_bulge_radius;

  std::vector <double> m_vM1;
  std::vector <double> m_vY1;
  std::vector <double> m_vX1;

  std::vector <double> m_vM2;
  std::vector <double> m_vY2;
  std::vector <double> m_vX2;

  void BuildCDF();

  double IntensityBulge(double R, double I0, double k);
  double IntensityDisc(double R, double I0, double a);
  double Intensity(double x);
};


#endif // CUMULATIVEDISTRIBUTIONFUNCTION_H

