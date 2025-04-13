# Graph

The applications for convenient graph manipulation

## Developers

Basalaev Daniil
Kromachev Maxim
Asanov Damir
Sazhin Daniil
Korpusova Sofia

## Requirements

C++17 and CMake are required

## Building and Running

#### Instalation

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
bash Build.sh --Release--noTest
```

#### Translation running
```bash
bash runApp  --translate--codeFilePath code.txt--outputFilePath figures.json--logFilePath log.log
```

#### Retranslation running
```bash
bash runApp  --retranslate--figresJsonFilePath figures.json--outputFilePath code.txt--logFilePath log.log
```
Use the --Release flag for (re)translation in release mode. (Re)translation is run in debug mode by default. 

```bash
bash runApp  --Release--retranslate--figresJsonFilePath figures.json--outputFilePath code.txt--logFilePath log.log
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
--Common # all tests
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
<https://github.com/11AgReS1SoR11/Graph>

