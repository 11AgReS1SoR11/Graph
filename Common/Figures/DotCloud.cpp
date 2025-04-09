#include "DotCloud.hpp"

std::string DotCloud::toJson() const
{
    std::string json = "{\n"
                       "\t\"type\": \"DotCloud\","
                       + Shape::toJson() + ",\n"
                       "\t\"property\": {\n"
                          "\t\t\"grid\": " + ((grid) ? "\"true\"" : "\"false\"") + ",\n"
                          "\t\t\"dots\": [\n";

    for (size_t i = 0; i < dots.size(); ++i)
    {
        if (dots[i]) 
        {
            json += dots[i]->toJson();
            if (i < dots.size() - 1) { json += ",\n"; }
        }
    }

    json += "]\n}\n}";

    return json;
}
