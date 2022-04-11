#pragma once

#include <yaml-cpp/yaml.h>

#include "control.hpp"

#include <iostream>

namespace YAML
{
    template <>
    struct convert<guis::Control>
    {
        static bool decode(const Node &node, guis::Control &control)
        {
            if (node["x"])
                control.setX(node["x"].as<int>());

            if (node["y"])
                control.setY(node["y"].as<int>());

            if (node["width"])
                control.setWidth(node["width"].as<int>());

            if (node["height"])
                control.setHeight(node["height"].as<int>());

            return true;
        }
    };
}
