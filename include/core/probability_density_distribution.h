/*
 * probability_density_distribution.h
 *
 *  Created on: 09.07.2015
 *      Author: scones
 */

#ifndef INCLUDE_CORE_PROBABILITY_DENSITY_DISTRIBUTION_H_
#define INCLUDE_CORE_PROBABILITY_DENSITY_DISTRIBUTION_H_


#include <type_traits>
#include <random>
#include <cinttypes>


namespace core  {


  template <typename real_type = double>
  class probability_density_distribution {
    static_assert(std::is_floating_point<real_type>::value, "template argument not a floating point type");

    public:

    typedef real_type result_type;


    template <class probability_function>
    explicit probability_density_distribution(probability_function &pf, std::uint64_t c_integration_steps = 1000, real_type start = real_type(0), real_type end = real_type(1))
      :
        m_start(start),
        m_end(end),
        m_inverse_cumulative_probability_points(),
        m_inverse_cumulative_probability_slopes()
    {
      // build up the lookup table
      assert(m_end > m_start);

      real_type interval_size = (real_type)(m_end - m_start) / (real_type)(c_integration_steps);
      real_type x = real_type(0),
                y = real_type(0);

      // local vectors for temporary function values
      std::vector<real_type> cdf_x;
      std::vector<real_type> cdf_y;
      std::vector<real_type> cdf_slope;
      std::vector<real_type> function_values;

      // predefine vector sizes
      cdf_x.resize(    c_integration_steps + 1, real_type(0));
      cdf_y.resize(    c_integration_steps + 1, real_type(0));
      cdf_slope.resize(c_integration_steps + 1, real_type(0));
      function_values.resize(c_integration_steps + 2);

      // precalculate function values ( calculate once, not thrice )
      for (std::uint64_t i(0); i < c_integration_steps + 2; ++i) {
        function_values[i] =  pf(m_start + ((real_type)i * interval_size));
      }

      // step 1:  integrate using simpson's rule in c_integration_steps number of steps
      for (std::uint64_t i(0); i < c_integration_steps; ++i) {
        x  = (i + 2) * interval_size;
        y += interval_size / 3 * ( function_values[i] + 4 * function_values[i+1] + function_values[i+2] );

        cdf_slope[i] = (y - cdf_y[i]) / (2.0 * interval_size);
        cdf_x[i + 1] = x;
        cdf_y[i + 1] = y;
      }

      // normalize y and slope
      auto maximum_y = cdf_y.back();
      for (std::uint64_t i(0); i < c_integration_steps + 1; ++i) {
        cdf_y[i]     /= maximum_y;
        cdf_slope[i] /= maximum_y;
      }

      // step 2: find inversion values
      std::vector<real_type> icdf_x;
      icdf_x.resize(c_integration_steps + 1, real_type(0));
      m_inverse_cumulative_probability_points.resize(c_integration_steps + 1, real_type(0));
      m_inverse_cumulative_probability_slopes.resize(c_integration_steps + 1, real_type(0));
      result_type p(0);
      interval_size = real_type(1) / (real_type)c_integration_steps;
      for (std::uint64_t i(0), j(0); i < c_integration_steps; ++i) {
        p = (real_type)i * interval_size;

        for (; cdf_y[j + 1] <= p; ++j);

        y = cdf_x[j] + (p - cdf_y[j]) / cdf_slope[j];

        m_inverse_cumulative_probability_slopes[i] = (y - m_inverse_cumulative_probability_points[i]) / interval_size;
        m_inverse_cumulative_probability_points[i + 1] = y;
      }
    }

    ~probability_density_distribution() = default;


    template <class random_number_generator>
    result_type operator()(random_number_generator &rng) {
      std::__detail::_Adaptor<random_number_generator, result_type> rng_adaptor(rng);
      result_type random_value = (rng_adaptor() * (real_type)m_inverse_cumulative_probability_points.size());

      double integral_part;
      double fractional_part = std::modf(random_value, &integral_part);
      std::uint64_t integral(static_cast<std::uint64_t>(std::floor(integral_part)));

      return m_inverse_cumulative_probability_points.at(integral) + m_inverse_cumulative_probability_slopes.at(integral) * fractional_part;
    }


    private:


    real_type m_start,
              m_end;
    std::vector<result_type> m_inverse_cumulative_probability_points;
    std::vector<result_type> m_inverse_cumulative_probability_slopes;
  };
}


#endif /* INCLUDE_CORE_PROBABILITY_DENSITY_DISTRIBUTION_H_ */
