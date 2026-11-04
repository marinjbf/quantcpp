#pragma once 
#include <Eigen/Dense>
#include <numcpp/UnivariateDistributions/Normal.hpp>
#include <numcpp/UnivariateDistributions/Uniform.hpp>

namespace quantcpp {

    class RandomNumbers {

        public:
            RandomNumbers(std::mt19937 &gen): gen_(gen){}

            using StandardNormal = double;
            using StandardNormalVector = Eigen::VectorXd;
            using StandardNormalMatrix = Eigen::MatrixXd;

            using StandardUniform = double;
            using StandardUniformVector = Eigen::VectorXd;
            using StandardUniformMatrix = Eigen::MatrixXd;

            StandardNormal generateStandardNormal() const {

                return numcpp::NormalDistribution{}.sample(gen_);
            }
        
        private: 
            std::mt19937& gen_;
    };
}