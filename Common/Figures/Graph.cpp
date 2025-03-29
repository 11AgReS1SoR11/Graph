#include "Graph.hpp"

std::string Graph::toJson() const
{
    std::string json = "{"
                       "\"type\": \"Graph\","
                       + Shape::toJson() + ","
                       "\"property\": {"
                       "\"nodes\": [";

    for (size_t i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]) 
        {
            json += nodes[i]->toJson();
            if (i < nodes.size() - 1) { json += ","; }
        }
    }

    json += "]"
            "}"
            "}";

    return json;
}
