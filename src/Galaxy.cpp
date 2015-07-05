/*
 * Galaxy.cpp
 *
 *  Created on: 03.07.2015
 *      Author: beltoforion, scones
 */

#include <cstdlib>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>


#include "Galaxy.h"
#include "Constants.h"
#include "core/support/xorshift.h"


double rnd_spread(double v, double o) {
  return (v + (2 * o * (double) rand() / RAND_MAX - o));
}


Galaxy::Galaxy(double rad, double radCore, double deltaAng, double ex1, double ex2, double sigma, double velInner, double velOuter, int numStars)
    :
      m_elEx1(ex1),
      m_elEx2(ex2),
      m_velOrigin(30),
      m_velInner(velInner),
      m_velOuter(velOuter),
      m_angleOffset(deltaAng),
      m_radCore(radCore),
      m_radGalaxy(rad),
      m_radFarField(m_radGalaxy * 2),
      m_sigma(sigma),
      m_velAngle(0.000001),
      m_time(0),
      m_timeStep(0),
      m_pos(0, 0),
      m_vstar(std::vector<star>()),
      m_vdust(std::vector<star>()),
      m_vh2(std::vector<star>()),
      m_cdf(CumulativeDistributionFunction()),
      m_count_by_rad(std::vector<std::uint64_t>()),
      m_seed(1),
      m_number_of_stars(numStars)
{
  // fixed size intializiations
  m_vh2.resize(600);
  m_count_by_rad.resize(100);

  Reset();
}


Galaxy::Galaxy(Galaxy&& rhs)
  :
    m_elEx1(rhs.m_elEx1),
    m_elEx2(rhs.m_elEx2),
    m_velOrigin(rhs.m_velOrigin),
    m_velInner(rhs.m_velInner),
    m_velOuter(rhs.m_velOuter),
    m_angleOffset(rhs.m_angleOffset),
    m_radCore(rhs.m_radCore),
    m_radGalaxy(rhs.m_radGalaxy),
    m_radFarField(rhs.m_radFarField),
    m_sigma(rhs.m_sigma),
    m_velAngle(rhs.m_velAngle),
    m_time(rhs.m_time),
    m_timeStep(rhs.m_timeStep),
    m_pos(std::move(rhs.m_pos)),
    m_vstar(std::move(rhs.m_vstar)),
    m_vdust(std::move(rhs.m_vdust)),
    m_vh2(std::move(rhs.m_vh2)),
    m_cdf(std::move(rhs.m_cdf)),
    m_count_by_rad(std::move(rhs.m_count_by_rad)),
    m_seed(rhs.m_seed),
    m_number_of_stars(rhs.m_number_of_stars)
{
// fixed size intializiations
m_vh2.resize(600);
m_count_by_rad.resize(100);

Reset();
}


void Galaxy::Reset() {
  // match (new?) size
  m_vstar.resize(m_number_of_stars);
  m_vdust.resize(m_number_of_stars >> 1);

  // empty fill structures
  std::fill(m_count_by_rad.begin(), m_count_by_rad.end(), 0);
  std::fill(m_vstar.begin(), m_vstar.end(), star());
  std::fill(m_vdust.begin(), m_vdust.end(), star());
  std::fill(m_vh2.begin(), m_vh2.end(), star());

  // calculate derived values
  m_radFarField = m_radGalaxy * 2.0;
  m_cdf = CumulativeDistributionFunction(m_radGalaxy / 3.0, m_radCore, m_radFarField);

  // obviously generate the stars
  InitStars();
}


void Galaxy::InitStars() {
  static const double c_temperature = 6000.0;

  assert(3 <= m_vstar.size());

  core::support::xorshift<std::uint64_t> random_generator(m_seed);
  std::uniform_real_distribution<double> distributor(0.0, 1.0);
  std::uniform_real_distribution<double> theta_distributor(0.0, 360.0);
  std::uniform_real_distribution<double> galactic_axis_distributor(-m_radGalaxy, m_radGalaxy);
  std::uniform_real_distribution<double> dust_brightness_distributor(0.015, 0.025);
  std::uniform_real_distribution<double> h2_temperature_distributor(3000.0, 9000.0);
  std::uniform_real_distribution<double> h2_brightness_distributor(0.1, 0.15);
  std::uniform_real_distribution<double> star_brightness_distributor(0.1, 0.3);
  std::uniform_real_distribution<double> star_temperatur_distributor(4000.0, 8000.0);

  // The first three stars can be used for aligning the
  // camera with the galaxy rotation.


  // First star is the black hole at the center
  m_vstar[0] = star(
    0.0,               // theta
    0.0,               // velocity theta
    0.0,               // angle
    0.0,               // minor half axis
    0.0,               // major half axis
    c_temperature,
    core::t_vec2d()    // center
  );

  // second star is at the edge of the core area
  double major_half_axis = m_radCore * GetExcentricity(m_radCore);
  double minor_half_axis = m_radCore;
  m_vstar[1] = star(
    0.0,                                                                // theta
    GetOrbitalVelocity((minor_half_axis + major_half_axis) / 2.0),      // velocity theta
    GetAngularOffset(m_radCore),                                        // angle
    minor_half_axis,
    major_half_axis,
    c_temperature,
    core::t_vec2d()                                                     // center
  );

  // third star is at the edge of the disk
  minor_half_axis = m_radGalaxy;
  major_half_axis = m_radGalaxy * GetExcentricity(m_radGalaxy);
  m_vstar[2] = star(
    0.0,                                                                // theta
    GetOrbitalVelocity((minor_half_axis + major_half_axis) / 2.0),      // velocity theta
    GetAngularOffset(m_radGalaxy),                                      // angle
    minor_half_axis,
    major_half_axis,
    c_temperature,
    core::t_vec2d()                                                     // center
  );

  // cell width of the histogram
  double dh = (double) m_radFarField / 100.0;
  double rad;

  // Initialize the other stars
  for (auto it = m_vstar.begin() + 3; it != m_vstar.end(); ++it) {
    // random value between -1 and 1
    rad = m_cdf.ValFromProb(distributor(random_generator));

    *it = star(
      theta_distributor(random_generator),                    // theta
      GetOrbitalVelocity(rad),                                // velocity theta
      GetAngularOffset(rad),                                  // angle
      rad,                                                    // half minor axis
      rad *  GetExcentricity(rad),                            // half major axis
      star_temperatur_distributor(random_generator),          // temperature
      core::t_vec2d(),                                        // center
      star_brightness_distributor(random_generator)           // brightness
    );

    int idx = std::min(1.0 / dh * (it->m_a + it->m_b) / 2.0, 99.0);
    m_count_by_rad [idx]++;
  }

  // initialize Dust
  double x, y;
  int i = 0;
  for (auto & dust : m_vdust ) {
    if (0 == i++ % 4) {
      rad = m_cdf.ValFromProb((double) rand() / (double) RAND_MAX);
    } else {
      x = galactic_axis_distributor(random_generator);
      y = galactic_axis_distributor(random_generator);
      rad = sqrt(x * x + y * y);
    }

    dust.m_a = rad;
    dust.m_b = rad * GetExcentricity(rad);
    dust.m_angle = GetAngularOffset(rad);
    dust.m_theta = theta_distributor(random_generator);
    dust.m_velTheta = GetOrbitalVelocity((dust.m_a + dust.m_b) / 2.0);
    dust.m_center = core::t_vec2d();

    // I want the outer parts to appear blue, the inner parts yellow. I'm imposing
    // the following temperature distributor (no science here it just looks right)
    dust.m_temp = 5000 + rad / 4.5;

    dust.m_mag = dust_brightness_distributor(random_generator);

    int idx = std::min(1.0 / dh * (dust.m_a + dust.m_b) / 2.0, 99.0);
    m_count_by_rad [idx]++;
  }

  // initialize h2
  for (unsigned int i = 0; i < m_vh2.size() >> 1; ++i) {
    x = galactic_axis_distributor(random_generator);
    y = galactic_axis_distributor(random_generator);
    rad = sqrt(x * x + y * y);

    int k1 = 2 * i;
    m_vh2[k1].m_a = rad;
    m_vh2[k1].m_b = rad * GetExcentricity(rad);
    m_vh2[k1].m_angle = GetAngularOffset(rad);
    m_vh2[k1].m_theta = theta_distributor(random_generator);
    m_vh2[k1].m_velTheta = GetOrbitalVelocity((m_vh2 [k1].m_a + m_vh2 [k1].m_b) / 2.0);
    m_vh2[k1].m_center = core::t_vec2d();
    m_vh2[k1].m_temp = h2_temperature_distributor(random_generator);
    m_vh2[k1].m_mag = h2_brightness_distributor(random_generator);

    int idx = static_cast<int>(std::min(1.0 / dh * (m_vh2[k1].m_a + m_vh2[k1].m_b) / 2.0, 99.0));
    m_count_by_rad [idx]++;

    int k2 = 2 * i + 1;
    m_vh2[k2].m_a = rad + 1000;
    m_vh2[k2].m_b = rad * GetExcentricity(rad);
    m_vh2[k2].m_angle = /*m_pH2[k1].m_angle;*/GetAngularOffset(rad);
    m_vh2[k2].m_theta = m_vh2[k1].m_theta;
    m_vh2[k2].m_velTheta = m_vh2[k1].m_velTheta;
    m_vh2[k2].m_center = m_vh2[k1].m_center;
    m_vh2[k2].m_temp = m_vh2[k1].m_temp;
    m_vh2[k2].m_mag = m_vh2[k1].m_mag;
    idx = static_cast<int>(std::min(1.0 / dh * (m_vh2[k2].m_a + m_vh2[k2].m_b) / 2.0, 99.0));
    m_count_by_rad [idx]++;
  }
}


double const Galaxy::GetSigma() const {
  return m_sigma;
}


void Galaxy::SetSigma(double s) {
  m_sigma = s;
  Reset();
}


std::vector<star> const& Galaxy::GetStars() const {
  return m_vstar;
}


std::vector<star> const& Galaxy::GetDust() const {
  return m_vdust;
}


std::vector<star> const& Galaxy::GetH2() const {
  return m_vh2;
}


double const Galaxy::GetRad() const {
  return m_radGalaxy;
}


double const Galaxy::GetCoreRad() const {
  return m_radCore;
}


double const Galaxy::GetFarFieldRad() const {
  return m_radFarField;
}


void Galaxy::SetAngularOffset(double offset) {
  m_angleOffset = offset;
  Reset();
}


/*
 * brief
 * Returns the orbital velocity in degrees per year.
 *
 * param
 * rad Radius in parsec
 */
double const Galaxy::GetOrbitalVelocity(double const& rad) const {
  double vel_kms = 0.0;  // velovity in kilometer per seconds

  // Realistically looking velocity curves for the Wikipedia models.
  struct VelocityCurve {
    static double MS(double r) {
      double d = 2000;  // Dicke der Scheibe
      double rho_so = 1;  // Dichte im Mittelpunkt
      double rH = 2000; // Radius auf dem die Dichte um die Hälfte gefallen ist
      return rho_so * exp(-r / rH) * (r * r) * glm::pi<double>() * d;
    }

    static double MH(double r) {
      double rho_h0 = 0.15; // Dichte des Halos im Zentrum
      double rC = 2500;     // typische skalenlänge im Halo
      return rho_h0 * 1 / (1 + pow(r / rC, 2)) * (4 * glm::pi<double>() * pow(r, 3) / 3);
    }

    // Velocity curve with dark matter
    static double v(double r) {
      double MZ = 100;
      double G = 6.672e-11;
      return 20000 * sqrt(G * (MH(r) + MS(r) + MZ) / r);
    }

    // velocity curve without dark matter
    static double vd(double r) {
      double MZ = 100;
      double G = 6.672e-11;
      return 20000 * sqrt(G * (MS(r) + MZ) / r);
    }
  };

  //  with dark matter
  vel_kms = VelocityCurve::v(rad);

  // without dark matter:
//    vel_kms = VelocityCurve::vd(rad);

  // Calculate velocity in degree per year
  double u = 2 * glm::pi<double>() * rad * constants::PC_TO_KM;        // Umfang in km
  double time = u / (vel_kms * constants::SEC_PER_YEAR);  // Umlaufzeit in Jahren

  return 360.0 / time;                                   // Grad pro Jahr
}


double const Galaxy::GetExcentricity(double const& r) const {
  if (r < m_radCore) {
    // Core region of the galaxy. Innermost part is round
    // excentricity increasing linear to the border of the core.
    return 1 + (r / m_radCore) * (m_elEx1 - 1);
  } else if (r > m_radCore && r <= m_radGalaxy) {
    return m_elEx1 + (r - m_radCore) / (m_radGalaxy - m_radCore) * (m_elEx2 - m_elEx1);
  } else if (r > m_radGalaxy && r < m_radFarField) {
    // excentricity is slowly reduced to 1.
    return m_elEx2 + (r - m_radGalaxy) / (m_radFarField - m_radGalaxy) * (1 - m_elEx2);
  } else
    return 1;
}


double const Galaxy::GetAngularOffset(double const& rad) const {
  return rad * m_angleOffset;
}


double const Galaxy::GetAngularOffset() const {
  return m_angleOffset;
}


double const Galaxy::GetExInner() const {
  return m_elEx1;
}


double const Galaxy::GetExOuter() const {
  return m_elEx2;
}


void Galaxy::SetRad(double rad) {
  m_radGalaxy = rad;
  Reset();
}


void Galaxy::SetCoreRad(double rad) {
  m_radCore = rad;
  Reset();
}


void Galaxy::SetExInner(double ex) {
  m_elEx1 = ex;
  Reset();
}


void Galaxy::SetExOuter(double ex) {
  m_elEx2 = ex;
  Reset();
}


double const Galaxy::GetTimeStep() const {
  return m_timeStep;
}


double const Galaxy::GetTime() const {
  return m_time;
}


void Galaxy::SingleTimeStep(double time) {
  m_timeStep = time;
  m_time += time;

  for (auto & s : m_vstar) {
    auto pos_old = s.m_pos;
    s.m_theta += s.m_velTheta * time;
    s.CalcXY();

    s.m_vel = s.m_pos - pos_old;
  }

  for (auto & d : m_vdust) {
    d.m_theta += d.m_velTheta * time;
    d.CalcXY();
  }

  for (auto & h : m_vh2) {
    h.m_theta += h.m_velTheta * time;
    h.CalcXY();
  }

}


core::t_vec2d const& Galaxy::get_star_pos_at_index(int idx) {
  return m_vstar.at(idx).m_pos;
}


int const Galaxy::GetNumH2() const {
  return m_vh2.size();
}


int const Galaxy::GetNumStars() const {
  return m_vstar.size();
}


int const Galaxy::GetNumDust() const {
  return m_vdust.size();
}

