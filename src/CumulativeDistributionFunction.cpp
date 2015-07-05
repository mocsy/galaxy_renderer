#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <stdexcept>
#include <utility>


#include "CumulativeDistributionFunction.h"


CumulativeDistributionFunction::CumulativeDistributionFunction()
    :
  m_intensity_funtion(&CumulativeDistributionFunction::Intensity),
  m_min(0.0),
  m_max(0.0),
  m_width(0.0),
  m_number_of_steps(1),
  m_i0(1.0),
  m_k(0.02),
  m_a(0.0),
  m_bulge_radius(0.0),
  m_vM1(),
  m_vY1(),
  m_vX1(),
  m_vM2(),
  m_vY2(),
  m_vX2()
{
  BuildCDF();
}

CumulativeDistributionFunction::CumulativeDistributionFunction(double a, double bulge_radius, double max, int number_of_steps)
  :
    m_intensity_funtion(&CumulativeDistributionFunction::Intensity),
    m_min(0.0),
    m_max(max),
    m_width(0.0),
    m_number_of_steps(number_of_steps),
    m_i0(1.0),
    m_k(0.02),
    m_a(a),
    m_bulge_radius(bulge_radius),
    m_vM1(),
    m_vY1(),
    m_vX1(),
    m_vM2(),
    m_vY2(),
    m_vX2()
{
  BuildCDF();
}


/*
m_cdf.SetupRealistic(
  1.0,                // maximum brightness
  0.02,               // k (bulge)
  m_radGalaxy / 3.0,  // disc scale length
  m_radCore,          // bulge radius
  0,                  // start of intensity curve
  m_radFarField,      // end of intensity curve
  1000                // Anzahl der stützstellen
);
*/

/*
void CumulativeDistributionFunction::SetupRealistic(double a, double bulge_radius, double max, int nSteps) {
  m_min = max;
  m_number_of_steps = nSteps;

  m_a = a;
  m_bulge_radius = bulge_radius;

  // build the distribution function
  BuildCDF(m_nSteps);
}
*/

CumulativeDistributionFunction& CumulativeDistributionFunction::operator=(CumulativeDistributionFunction&& rhs) {
  this->m_intensity_funtion = &CumulativeDistributionFunction::Intensity;
  this->m_min = rhs.m_min;
  this->m_max = rhs.m_max;
  this->m_width = rhs.m_width;
  this->m_number_of_steps = rhs.m_number_of_steps;
  this->m_i0 = rhs.m_i0;
  this->m_k = rhs.m_k;
  this->m_a = rhs.m_a;
  this->m_bulge_radius = rhs.m_bulge_radius;
  this->m_vM1 = std::move(rhs.m_vM1);
  this->m_vY1 = std::move(rhs.m_vY1);
  this->m_vX1 = std::move(rhs.m_vX1);
  this->m_vM2 = std::move(rhs.m_vM2);
  this->m_vY2 = std::move(rhs.m_vY2);
  this->m_vX2 = std::move(rhs.m_vX2);

  return *this;
}


CumulativeDistributionFunction::CumulativeDistributionFunction(CumulativeDistributionFunction&& rhs)
  :
    m_intensity_funtion(&CumulativeDistributionFunction::Intensity),
    m_min(rhs.m_min),
    m_max(rhs.m_max),
    m_width(rhs.m_width),
    m_number_of_steps(rhs.m_number_of_steps),
    m_i0(rhs.m_i0),
    m_k(rhs.m_k),
    m_a(rhs.m_a),
    m_bulge_radius(rhs.m_bulge_radius),
    m_vM1(std::move(rhs.m_vM1)),
    m_vY1(std::move(rhs.m_vY1)),
    m_vX1(std::move(rhs.m_vX1)),
    m_vM2(std::move(rhs.m_vM2)),
    m_vY2(std::move(rhs.m_vY2)),
    m_vX2(std::move(rhs.m_vX2))
{
}


void CumulativeDistributionFunction::BuildCDF() {
  double h = (m_max - m_min) / m_number_of_steps;
  double x = 0, y = 0;

  m_vX1.clear();
  m_vY1.clear();
  m_vX2.clear();
  m_vY2.clear();
  m_vM1.clear();
  m_vM2.clear();

  // impson rule for integration of the distribution function
  m_vY1.push_back(0.0);
  m_vX1.push_back(0.0);
  for (int i = 0; i < m_number_of_steps; i += 2) {
    x = (i + 2) * h;
    y += h / 3 * ((this->*m_intensity_funtion)(m_min + i * h) + 4 * (this->*m_intensity_funtion)(m_min + (i + 1) * h) + (this->*m_intensity_funtion)(m_min + (i + 2) * h));

    m_vM1.push_back((y - m_vY1.back()) / (2 * h));
    m_vX1.push_back(x);
    m_vY1.push_back(y);

//    printf("%2.2f, %2.2f, %2.2f\n", m_fMin + (i+2) * h, v, h);
  }
  m_vM1.push_back(0.0);

  // all arrays must have the same length
  if (m_vM1.size() != m_vX1.size() || m_vM1.size() != m_vY1.size())
    throw std::runtime_error("CumulativeDistributionFunction::BuildCDF: array size mismatch (1)!");

  // normalize
  for (std::size_t i = 0; i < m_vY1.size(); ++i) {
    m_vY1 [i] /= m_vY1.back();
    m_vM1 [i] /= m_vY1.back();
  }

  //
  m_vX2.push_back(0.0);
  m_vY2.push_back(0.0);

  double p = 0;
  h = 1.0 / m_number_of_steps;
  for (int i = 1, k = 0; i < m_number_of_steps; ++i) {
    p = (double) i * h;

    for (; m_vY1 [k + 1] <= p; ++k) {
    }

    y = m_vX1 [k] + (p - m_vY1 [k]) / m_vM1 [k];

    printf("%2.4f, %2.4f, k=%d, %2.4f, %2.4f\n", p, y, k, m_vY1 [k], m_vM1 [k]);

    m_vM2.push_back((y - m_vY2.back()) / h);
    m_vX2.push_back(p);
    m_vY2.push_back(y);
  }
  m_vM2.push_back(0.0);

  // all arrays must have the same length
  if (m_vM2.size() != m_vX2.size() || m_vM2.size() != m_vY2.size())
    throw std::runtime_error("CumulativeDistributionFunction::BuildCDF: array size mismatch (1)!");

}


double CumulativeDistributionFunction::ProbFromVal(double fVal) {
  if (fVal < m_min || fVal > m_max)
    throw std::runtime_error("out of range");

  double h = 2 * ((m_max - m_min) / m_number_of_steps);
  int i = (int) ((fVal - m_min) / h);
  double remainder = fVal - i * h;

//  printf("fVal=%2.2f; h=%2.2f; i=%d; m_vVal[i]=%2.2f; m_vAsc[i]=%2.2f;\n", fVal, h, i, m_vVal[i], m_vAsc[i]);

  return (m_vY1 [i] + m_vM1 [i] * remainder) /* / m_vVal.back()*/;
}


double CumulativeDistributionFunction::ValFromProb(double fVal) {
  if (fVal < 0 || fVal > 1)
    throw std::runtime_error("out of range");

  double h = 1.0 / m_vY2.size();

  int i = (int) (fVal / h);
  double remainder = fVal - i * h;

  return (m_vY2 [i] + m_vM2 [i] * remainder) /* / m_vVal.back()*/;
}


double CumulativeDistributionFunction::IntensityBulge(double R, double I0, double k) {
  return I0 * exp(-k * pow(R, 0.25));
}


double CumulativeDistributionFunction::IntensityDisc(double R, double I0, double a) {
  return I0 * exp(-R / a);
}


double CumulativeDistributionFunction::Intensity(double x) {
  return (x < m_bulge_radius) ? IntensityBulge(x, m_i0, m_k) : IntensityDisc(x - m_bulge_radius, IntensityBulge(m_bulge_radius, m_i0, m_k), m_a);
}

