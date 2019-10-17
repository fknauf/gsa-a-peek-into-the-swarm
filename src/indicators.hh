#ifndef INCLUDED_SIMULATION_INDICATORS_HH
#define INCLUDED_SIMULATION_INDICATORS_HH

#include <algorithm>
#include <numeric>

namespace simulation {
  class indicators {
  public:
    template<typename Steppers>
    indicators(Steppers &steppers) {
      auto fitness = [](auto &s) {
        return s->global_best().fitness();
      };

      std::sort(begin(steppers), end(steppers), [&](auto &lhs, auto &rhs) {
          return fitness(lhs) < fitness(rhs);
        });

      best_ = fitness(steppers.front());
      worst_ = fitness(steppers.back());

      if(steppers.size() % 2 == 0) {
        median_ =
          0.5 * (fitness(steppers[steppers.size() / 2    ]) +
                 fitness(steppers[steppers.size() / 2 - 1])) ;
      } else {
        median_ = fitness(steppers[steppers.size() / 2    ]);
      }

      avg_ = std::accumulate(begin(steppers), end(steppers), 0.0,
                             [&](double sum, auto &s) {
                               return sum + fitness(s);
                             }) / steppers.size();
    }

    double best  () const { return best_  ; }
    double avg   () const { return avg_   ; }
    double median() const { return median_; }
    double worst () const { return worst_ ; }

  private:
    double avg_;
    double median_;
    double best_;
    double worst_;
  };
}

#endif
