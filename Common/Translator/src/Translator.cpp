#include "Translator.hpp"

// work with semantic_analysator_parser

//parsing style ASK BOUT coinsidence of #define and colors
Style parseStyle(std::vector<SEMANTICANALYZER::Property>& _props, Style const& default_style) {
  Style _style = default_style;
  for (auto& _prop : _props) {
    if (_prop.key == "color") {
      if (_prop.value == "RED") { _style.color = color_e::RED; }
      else if (_prop.value == "GREEN") { _style.color = color_e::GREEN; } 
      else if (_prop.value == "BLUE") { _style.color = color_e::BLUE; } 
      else if (_prop.value == "BLACK") { _style.color = color_e::BLACK; } 
      else if (_prop.value == "WHITE") { _style.color = color_e::WHITE; } 
      else if (_prop.value == "YELLOW") { _style.color = color_e::YELLOW; } 
      else if (_prop.value == "PURPLE") { _style.color = color_e::PURPLE; } 
      else if (_prop.value == "NONE") { _style.color = color_e::NONE; } 
    }
    else if (_prop.key == "border") {
      _style.border = std::stod(_prop.value);
    }
    else if (_prop.key == "size_text") {_style.textSize = std::stod(_prop.value);}
  }
  return _style;
}

void parseCommonProperty(std::vector<SEMANTICANALYZER::Property>& _props, Shape* _shape, Style const& graph_style){
  for (auto& _prop : _props){
      if (_prop.key == "text") { _shape->text = _prop.value; }
      else if (_prop.key == "x") { _shape->x = std::stod(_prop.value); }
      else if (_prop.key == "y") { _shape->y = std::stod(_prop.value); }
  }
  Style _style = parseStyle(_props, graph_style);
  _shape->style = _style;
}

Shape* parseObject(SEMANTICANALYZER::ObjectDecl& object, Style const& graph_style){
  const std::string& obj_shape = object.shape;

  if (obj_shape == "circle") {
      Circle* _circle = new Circle;
      _circle->id = object.id;
      parseCommonProperty(object.properties, _circle, graph_style);
      for (auto& _prop : object.properties) {
          if (_prop.key == "radius") {
            _circle->radius = std::stod(_prop.value);
            }
      }
      return _circle;
  }

  else if (obj_shape == "rectangle") {
      Rectangle* _react = new Rectangle;
      _react->id = object.id;
      parseCommonProperty(object.properties, _react, graph_style);
      for (auto& _prop : object.properties) {
          if (_prop.key == "size_A") { _react->sizeA = std::stod(_prop.value); }
          else if (_prop.key == "size_B") { _react->sizeB = std::stod(_prop.value); }
      }
      return _react;
  }
  
  else if (obj_shape == "diamond") {
      Diamond* _diam = new Diamond;
      _diam->id = object.id;
      parseCommonProperty(object.properties, _diam, {});
      for (auto& _prop : object.properties) {
          if (_prop.key == "size_A") { _diam->sizeA = std::stod(_prop.value); }
          else if (_prop.key == "size_B") { _diam->sizeB = std::stod(_prop.value); }
          else if (_prop.key == "angle") { _diam->angle = std::stod(_prop.value); }
      }
      return _diam;
  }


  return nullptr;
}

Shape* parseRelation(SEMANTICANALYZER::Relation& relation, Style const& graph_style){
    Line* _line = new Line;
    _line->idFrom = relation.id1;
    _line->idTo = relation.id2;

    //fill for arrow
    if (relation.arrow == "->") {
    _line->type = line_type_e::Solid;
    _line->orientation = line_orientation_e::Directed;
    }
    else if (relation.arrow == "-->") {
    _line->type = line_type_e::Dotted;
    _line->orientation = line_orientation_e::Directed;
    }
    else if (relation.arrow == "<->") {
    _line->type = line_type_e::Solid;
    _line->orientation = line_orientation_e::DoubleDirected;
    }
    else if (relation.arrow == "<-->") {
    _line->type = line_type_e::Dotted;
    _line->orientation = line_orientation_e::DoubleDirected;
    }
    else if (relation.arrow == "--") {
    _line->type = line_type_e::Dotted;
    _line->orientation = line_orientation_e::Undirected;
    }
    else if (relation.arrow == "-") {
    _line->type = line_type_e::Solid;
    _line->orientation = line_orientation_e::Undirected;
    }
    parseCommonProperty(relation.properties, _line, graph_style);

    return _line;
}

Shape* parseNote(SEMANTICANALYZER::Note& note){
  Note* _note = new Note;
  _note->id = note.id;
  parseCommonProperty(note.properties, _note, {});
  return _note;
}

Shape* parseGraph(SEMANTICANALYZER::Graph& graph){
  Graph* _graph = new Graph;
  _graph->id = graph.id;
  parseCommonProperty(graph.properties, _graph, {});
  std::vector<Shape*> _nodes;

  for (auto& _obj : graph.objects) {
    Shape* object_shape = parseObject(_obj, _graph->style);
    //for all shapes set graph's style
    _nodes.push_back(object_shape);
  }
  for (auto& _rel : graph.relations) {
    Shape* relation_shape = parseRelation(_rel, _graph->style);
    //for all shapes set graph's style
    _nodes.push_back(relation_shape);
  }
  _graph->nodes = std::move(_nodes);
  return _graph;
}

Shape* parseDotCloud(SEMANTICANALYZER::DotCloud& dot_cloud){
  DotCloud* _dtcld = new DotCloud();
  _dtcld->id = dot_cloud.id;
  parseCommonProperty(dot_cloud.externalProperties, _dtcld, {});
  for(auto& _prop : dot_cloud.externalProperties){
      if(_prop.key == "grid"){
          if(_prop.value == "true") {_dtcld->grid = true;}
          else if(_prop.value == "false") {_dtcld->grid = false;}
      }
  }
  std::vector<Circle*> dots;
  for(auto& dot : dot_cloud.dots){
      Circle* _circle = new Circle();
      parseCommonProperty(dot.internalProperties, _circle, _dtcld->style);
      //for all circles set dot_cloud's style
      dots.push_back(_circle);
  }
  _dtcld->dots = std::move(dots);
  return _dtcld;
}

FiguresStorage Translator::translate(std::vector<std::pair<std::string, std::any>>& parsed_ast_tree) {
  FiguresStorage _figures_storage;

  for (auto& vector_shape : parsed_ast_tree) {
    Shape* shape;
    const std::string& type = vector_shape.first;

    //object_decl
    if (type == "object_decl") {
      SEMANTICANALYZER::ObjectDecl& _obj = std::any_cast<SEMANTICANALYZER::ObjectDecl&>(vector_shape.second);
      shape = parseObject(_obj, {});
    }

    //relation
    else if (type  == "relation") {
      SEMANTICANALYZER::Relation& _rel = std::any_cast<SEMANTICANALYZER::Relation&>(vector_shape.second);
      shape = parseRelation(_rel, {});
    }

    //note
    else if (type == "note") {
      SEMANTICANALYZER::Note& nnote = std::any_cast<SEMANTICANALYZER::Note&>(vector_shape.second);
      shape = parseNote(nnote);
    }

    //graph - uncomplete ALL OBJ&REL HAVE GRAPH COMMON style!!! 
    else if (type  == "graph") {
      SEMANTICANALYZER::Graph& ggraph = std::any_cast<SEMANTICANALYZER::Graph&>(vector_shape.second);
      shape = parseGraph(ggraph);
    }

    //dot_cloud
    else if (type == "dot_cloud") {
      SEMANTICANALYZER::DotCloud& dotCloud = std::any_cast<SEMANTICANALYZER::DotCloud&>(vector_shape.second);
      shape = parseDotCloud(dotCloud);
    }

    //add to hashmap
    _figures_storage.push_back(shape);
  }

  return _figures_storage;
}
