#ifndef _GALAXY_H
#define _GALAXY_H


#include <vector>


#include "core/vectors.h"
#include "star.h"
#include "CumulativeDistributionFunction.h"


/*
 * a class to encapsulate the geometric details of a spiral galaxy
 */
class Galaxy {
  public:


  Galaxy(double rad = 15000, double radCore = 6000, double deltaAng = 0.019, double ex1 = 0.8, double ex2 = 1, double sigma = 0.5, double velInner = 200, double velOuter = 300, int numStars = 20000);
  ~Galaxy() = default;

  void Reset(double rad, double radCore, double deltaAng, double ex1, double ex2, double sigma, double velInner, double velOuter, int numStars);

  void Reset();

  std::vector<star> const& GetStars() const;
  std::vector<star> const& GetDust() const;
  std::vector<star> const& GetH2() const;

  double GetRad() const;
  double GetCoreRad() const;
  double GetFarFieldRad() const;
  double GetSigma() const;

  // Properties depending on the orbital radius

  double GetExcentricity(double rad) const;
  double GetOrbitalVelocity(double rad) const;

  double GetAngularOffset(double rad) const;
  double GetAngularOffset() const;

  double GetExInner() const;
  double GetExOuter() const;
  double GetTimeStep() const;
  double GetTime() const;
  int const GetNumStars() const;
  int const GetNumDust() const;
  int const GetNumH2() const;

  void SingleTimeStep(double time);

  core::t_vec2d const& GetStarPos(int idx);

  void SetSigma(double sigma);
  void SetAngularOffset(double offset);
  void SetCoreRad(double rad);
  void SetRad(double rad);
  void SetExInner(double ex);
  void SetExOuter(double ex);


  private:


  void InitStars(double sigma);

  // Parameters needed for defining the general structure of the galaxy

  double m_elEx1;          ///< Excentricity of the innermost ellipse
  double m_elEx2;          ///< Excentricity of the outermost ellipse

  double m_velOrigin;      ///< Velovity at the innermost core in km/s
  double m_velInner;       ///< Velocity at the core edge in km/s
  double m_velOuter;       ///< Velocity at the edge of the disk in km/s

  double m_angleOffset;    ///< Angular offset per parsec

  double m_radCore;        ///< Radius of the inner core
  double m_radGalaxy;      ///< Radius of the galaxy
  double m_radFarField;    ///< The radius after which all density waves must have circular shape
  double m_sigma;          ///< Distribution of stars
  double m_velAngle;       ///< Angular velocity of the density waves
//  int m_numStars;          ///< Total number of stars
//  int m_numDust;           ///< Number of Dust Particles
//  int m_numH2;             ///< Number of H2 Regions

  double m_time;
  double m_timeStep;


  public:


  int m_numberByRad [100];  ///< Historgramm showing distribution of stars


  private:


  core::t_vec2d m_pos;         // Center of the galaxy
  std::vector<star> m_vstar;   // Pointer to an array of star data
  std::vector<star> m_vdust;   // Pointer to an array of dusty areas
  std::vector<star> m_vh2;
  CumulativeDistributionFunction m_cdf;
};


#endif // _GALAXY_H

