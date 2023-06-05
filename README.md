# Linguistic Neuroscience: Exploring the Hebb-Jorion Law

## Table of Contents
- [Introduction](#introduction)
- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
- [Additional Dependencies](@additional-dependencies)
- [Usage](#usage)
- [Testing](#testing)
- [Project Structure](#project-structure)
- [License](#license)
- [Main References](#main-references)
- [External Links](#external-links)
- [Contact](#contact)


## Introduction
This project provides a research framework to study the Hebb-Jorion Law, a new concept in linguistic neuroscience. We test the idea that content words create enduring connections via spontaneous associations, which subsequently forms a linguistic memory. This process is examined using the Google Ngram dataset and C++ for analysis and data processing, along with R for N-gram data extraction.

## Getting Started

### Prerequisites
- A modern C++ compiler supporting the C++14 standard.
- Make sure you have R installed, along with the required libraries: `tidyverse`, `future.apply`, and `ngramr`.
- The online [Google Ngram](https://books.google.com/ngrams/) dataset.
- GoogleTest for unit testing (if you plan to run the tests).

### Installation
1. Clone the repo.
```sh
git clone https://github.com/josephcmac/Hebb-Jorion.git
```
2. Navigate to the `r/` directory and run `script.R` to extract N-gram data.

## Usage
The C++ code can be compiled and run from the project root directory:
1. Compile the project:
```sh
make
```

2. Run the compiled executable:
```sh
cd bin
./main
```

Please adjust these commands based on your specific environment and setup.

## Additional Dependencies

Apart from the prerequisites mentioned above, this project also uses [RapidJSON](https://rapidjson.org/), a fast JSON parser/generator for C++ with both SAX/DOM style API. This library is used for handling JSON data within the application. 

### Installation

RapidJSON is a header-only library. To install it, you can simply copy the `include/rapidjson` folder to your system or project's include path. If you are using the vcpkg dependency manager, you can download and install RapidJSON with CMake integration in a single command:

```sh
vcpkg install rapidjson
```

### Usage

RapidJSON is used within the project in the following file: /hebbian-ngram/src/data_processing.cpp


### License

RapidJSON is distributed under the following license:

```
Tencent is pleased to support the open source community by making RapidJSON available.
 
Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
 
Licensed under the MIT License (the "License"); you may not use this file except
in compliance with the License. You may obtain a copy of the License at
 
http://opensource.org/licenses/MIT
 
Unless required by applicable law or agreed to in writing, software distributed 
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
CONDITIONS OF ANY KIND, either express or implied. See the License for the 
specific language governing permissions and limitations under the License.
```


## Testing
After ensuring GoogleTest is properly installed in your environment, you can compile and run the tests in the project root directory:

```sh
make run_tests
./run_tests
```

## Project Structure
This project is structured as follows:
```
project/
├── bin/
│   ├── main (compiled)
├── src/
│   ├── main.cpp
│   ├── data_processing.cpp
│   ├── model.cpp
│   └── utilities.cpp
├── include/
│   ├── data_processing.h
│   ├── model.h
│   └── utilities.h
├── data/
│   ├── input/
│   │   ├── dataset.csv
│   │   └── ...
│   └── output/
│       ├── results.csv
│       └── ...
├── r/
│   ├── script.R
│   └── ...
├── test/
│   └── utilities_test.cpp
│   └── ...
├── README.md
└── run_tests (compiled)
```

### `/src`

— `main.cpp`

This is the main entry point for the application. It calls the necessary functions from other files to achieve the desired functionalities of the application.

Functions:
- `main()`: Main function that starts and manages the execution flow of the application.

— `data_processing.cpp`

This file contains all functions necessary to process the data to be used by the model.

Functions:
- `loadData()`: This function reads the input dataset and prepares it for the model.
- `preprocessData()`: This function cleans and pre-processes the data.
- `splitData()`: This function splits the data into training and testing sets.

— `model.cpp`

This file contains the main model that is trained and tested on the provided data.

Functions:
- `trainModel()`: This function trains the model using the provided training data.
- `testModel()`: This function tests the model on the test data and returns the model's performance metrics.

— `utilities.cpp`

This file contains utility functions that are used throughout the application.

Functions:
- `findMedian()`: This function returns the median of a given list.

### `/include`

This folder contains the header files for the corresponding `.cpp` files. The header files declare the functions and classes implemented in the `.cpp` files.

— `data_processing.h`, `model.h`, `utilities.h`

These are the header files for `data_processing.cpp`, `model.cpp`, and `utilities.cpp` respectively.

### `/data`

This folder contains the input and output data of the application.

— `/input`
This folder contains the dataset that the model will use to train and test.

— `/output`
This folder contains the results from the model after testing.

### `/r`

This folder contains `script.R`, an R script that extracts N-gram data for specific words.

### `/test`

This folder contains unit tests for the utility functions implemented in `utilities.cpp`.

— `utilities_test.cpp`

This file contains the unit tests for the functions in `utilities.cpp`. It uses Google Test as the testing framework. It includes a test fixture (`UtilitiesTest`) and several test cases (e.g., `FindMedianEmptyList`).

## License
Distributed under the MIT License. See `LICENSE` for more information.

## Main References
- Hebb, Donald Olding. [The organization of behavior: A neuropsychological theory.](https://books.google.ca/books?id=ddB4AgAAQBAJ&dq=Hebb,+D.+O.+(1949).+The+organization+of+behavior:+A+neuropsychological+theory.&lr=) Psychology press, 2005.

- Jorion, Paul. [Principes des systèmes intelligents.](https://www.amazon.fr/Principes-syst%C3%A8mes-intelligents-Paul-Jorion/dp/2365120164/ref=ntt_at_ep_dpt_6) Masson 1989 ; éditions du Croquant 2012.

- Kendall, Maurice G. [A new measure of rank correlation.](https://www.jstor.org/stable/2332226) Biometrika 30.1/2 (1938): 81-93.

- Spearman, Charles. [The proof and measurement of association between two things.](https://psycnet.apa.org/record/2006-10257-005) The American journal of psychology 100.3/4 (1987): 441-471.


## External Links
- [Blog post about the book "Principes des systèmes intelligents"](https://www.pauljorion.com/blog/2012/10/30/principes-des-systemes-intelligents-1989-chapitre-2-reedition-en-libraire-le-23-novembre/)

- [Thought as Word Dynamics (blog post)](https://www.pauljorion.com/blog_en/2007/09/30/thought-as-word-dynamics/)

- [Thought as Word Dynamics (video series)](https://youtu.be/RPrvEoN2K3w)

## Contact
This code was developed by [José Manuel Rodríguez Caballero](https://github.com/josephcmac/) as a tool to empirically explore [Paul Jorion](https://www.pauljorion.com/blog_en/)'s theory of intelligent systems.