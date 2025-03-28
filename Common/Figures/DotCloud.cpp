#include "DotCloud.hpp"

std::string DotCloud::toJson() const
{
    std::string json = "{"
                       "\"type\": \"Graph\","
                       + Shape::toJson() + ","
                       "\"property\": {"
                          "\"grid\": " + ((grid) ? "\"true\"" : "\"false\"") + ","
                          "\"dots\": [";

    for (size_t i = 0; i < dots.size(); ++i)
    {
        if (dots[i]) 
        {
            json += dots[i]->toJson();
            if (i < dots.size() - 1) { json += ","; }
        }
    }

    json += "]"
            "}"
            "}";

    return json;
}
