# Graph

The project provides domain-specific language (DSL) designed for creating and manipulating graphs, diagrams, and dot clouds via code. It allows user to define complex visual structures and convert them from DSL code to JSON and backwards. 

## Developers

Basalaev Daniil\
Kromachev Maxim\
Asanov Damir\
Sazhin Daniil\
Korpusova Sofia

## Requirements

C++17 and CMake are required

## Building and Running

#### Building

```bash
bash Build.sh
```
#### Release mode
```bash
bash Build.sh --Release
```
#### Without tests
```bash
bash Build.sh --noTest
```
Using the combination of two previous flags is possible:
```bash
bash Build.sh --Release --noTest
```

#### Translation running
```bash
bash runApp --translate --codeFilePath code.txt --outputFilePath figures.json --logFilePath log.log
```

#### Retranslation running
```bash
bash runApp --retranslate --figresJsonFilePath figures.json --outputFilePath code.txt --logFilePath log.log
```
Use the --Release flag for (re)translation in release mode. (Re)translation is run in debug mode by default. 

```bash
bash runApp --Release --retranslate --figresJsonFilePath figures.json --outputFilePath code.txt --logFilePath log.log
```
#### Test running
```bash
bash runTest
```
or

```bash
bash runTest --Release
```
There are some optional flags for test running:

```bash
--all # all tests
--Common # common components tests
--Backend # backend tests
--AST # abstract syntax tree
--Logger
--FileManager
--SA # semantic analyzer
--Retranslator
--FiguresStorage
--Translator
--Parser

```
## Documentation

See the documentation for additional infrmation:
<https://github.com/11AgReS1SoR11/Graph/blob/master/Docs/GRAPHS_documentation.pdf>

