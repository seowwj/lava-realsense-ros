// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#pragma once
#include <librealsense2/rs.hpp>
#include <rclcpp/rclcpp.hpp>
#include <dynamic_params.h>

namespace realsense2_camera
{
    class SensorParams
    {
        public:
            SensorParams(std::shared_ptr<Parameters> parameters, rclcpp::Logger logger):
                _logger(logger),
                _parameters(parameters) {};
            ~SensorParams();
            void registerDynamicOptions(rs2::options sensor, const std::string& module_name);
            void clearParameters();
            std::shared_ptr<Parameters> getParameters() {return _parameters;};

        public:
            rclcpp::Logger _logger;

        private:
            double float_to_double(float val, rs2::option_range option_range);
            template<class T>
            rcl_interfaces::msg::ParameterDescriptor get_parameter_descriptor(const std::string& option_name, rs2::option_range option_range,
                T option_value, const std::string& option_description, const std::string& description_addition);
            template<class T>
            void set_parameter(rs2::options sensor, rs2_option option, const std::string& module_name, const std::string& description_addition="");

        private:
            std::shared_ptr<Parameters> _parameters;
            std::vector<std::string> _parameters_names;
    };
}
