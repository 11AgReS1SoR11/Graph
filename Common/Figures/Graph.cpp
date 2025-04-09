#include "Graph.hpp"

std::string Graph::toJson() const
{
    std::string json = "{\n"
                       "\t\"type\": \"Graph\","
                       + Shape::toJson() + ",\n"
                       "\t\"property\": {\n"
                       "\t\t\"nodes\": [\n";

    for (size_t i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]) 
        {
            json += nodes[i]->toJson();
            if (i < nodes.size() - 1) { json += ",\n"; }
        }
    }

    json += "]\n}\n}";

    return json;
}
