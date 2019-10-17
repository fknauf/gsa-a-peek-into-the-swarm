#ifndef INCLUDED_COMMON_SLIDE_HH
#define INCLUDED_COMMON_SLIDE_HH

#include <cmath>
#include <cstddef>
#include <vector>

namespace common {
  class slide {
  public:
    slide(std::size_t max_step);
    
    virtual ~slide();
    virtual double operator()(std::size_t step) const = 0;

    inline std::size_t max_step() const { return max_step_; }

  protected:
    double t(std::size_t step) const;
    
  private:
    std::size_t max_step_;
  };

  class constant_slide : public slide {
  public:
    constant_slide(double value);

    virtual double operator()(std::size_t step) const;    

  private:
    double value_;
  };
  
  class linear_slide : public slide {
  public:
    linear_slide(std::size_t max_step, double start, double end);

    virtual double operator()(std::size_t step) const;
    
  private:
    double start_;
    double end_;
  };

  class exponential_slide : public slide {
  public:
    exponential_slide(std::size_t max_step, double alpha, double G0);
    
    virtual double operator()(std::size_t step) const;
    
  private:
    std::size_t max_step_;
    double alpha_;
    double G0_;
  };

  template<typename OrdinarySlide>
  class chaotic_slide : public slide {
  public:
    chaotic_slide(OrdinarySlide const &ordinary, double chaos_initial)
      : slide     (ordinary.max_step()),
	ordinary_ (ordinary),
	chaos_map_(ordinary.max_step()),
	chaos0_   (chaos_initial)
    {
      chaos_map_[0] = 0.7;
    
      for(std::size_t i = 1; i < max_step(); ++i) {
	double last = chaos_map_[i - 1];
	
	chaos_map_[i] = 2.3 * last * last * sin(M_PI * last);
	//	chaos_map_[i] = std::sin(M_PI * chaos_map_[i - 1]);
      }
    }

    double operator()(std::size_t step) const {
      return chaos_map_[step] * chaos0_ * (1 - t(step)) + ordinary_(step);
    }    

  private:
    OrdinarySlide       ordinary_;
    std::vector<double> chaos_map_;
    double              chaos0_;
  };

  template<typename SlideType>
  chaotic_slide<SlideType> make_chaotic(SlideType const &slide, double chaos_initial) {
    return { slide, chaos_initial };
  }
}

#endif
