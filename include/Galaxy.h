#ifndef _GALAXY_H
#define _GALAXY_H


#include <vector>
#include <cinttypes>


#include "core/types.h"
#include "star_particles.h"


/*
 * a class to encapsulate the geometric details of a spiral galaxy
 */
class Galaxy {
  public:


  Galaxy(double rad = 15000, double radCore = 6000, double deltaAng = 0.019, double ex1 = 0.8, double ex2 = 1, double sigma = 0.5, double velInner = 200, double velOuter = 300, int numStars = 20000);
  Galaxy(Galaxy&&);
  ~Galaxy() = default;

  void Reset();
  void InitStars();


  void render();


  // Properties depending on the orbital radius
  double const GetExcentricity(double const& rad) const;
  double const GetOrbitalVelocity(double const& rad) const;
  double const GetAngularOffset(double const& rad) const;

  // getters
  double const GetRad() const;
  double const GetCoreRad() const;
  double const GetFarFieldRad() const;
  double const GetSigma() const;
  double const GetExInner() const;
  double const GetExOuter() const;
  double const GetTimeStep() const;
  double const GetTime() const;
  double const GetAngularOffset() const;
//  int const GetNumStars() const;
//  int const GetNumDust() const;
//  int const GetNumH2() const;
//  std::vector<star> const& GetDust() const;
//  std::vector<star> const& GetH2() const;
//  core::t_vec2d const& get_star_pos_at_index(int idx);


  // setters
  void SetSigma(double sigma);
  void SetAngularOffset(double offset);
  void SetCoreRad(double rad);
  void SetRad(double rad);
  void SetExInner(double ex);
  void SetExOuter(double ex);


  private:


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

  double m_time;
  double m_timeStep;

  core::t_vec2d m_pos;         // Center of the galaxy
//  std::vector<star> m_vdust;   // Pointer to an array of dusty areas
//  std::vector<star> m_vh2;

  std::vector<std::uint64_t> m_count_by_rad;  ///< Historgramm showing distribution of stars

  std::uint64_t m_seed;    // randomizer seed
  std::uint64_t m_number_of_stars;
  star_particles *m_pstars;
};


#endif // _GALAXY_H

