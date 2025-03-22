#ifndef SEMANTICANALYZER_H
#define SEMANTICANALYZER_H

#ifdef _WIN32
  #ifdef SEMANTICANALYZER_EXPORTS
    #define SEMANTICANALYZER_API __declspec(dllexport)
  #else
    #define SEMANTICANALYZER_API __declspec(dllimport)
  #endif
#else
  #define SEMANTICANALYZER_API
#endif

class SEMANTICANALYZER_API SemanticAnalyzer
{
public:
    SemanticAnalyzer();
};

#endif // SEMANTICANALYZER_H
