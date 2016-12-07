# abacus-approximation
Implementation of an algorithm's approximation of a specified program.

## Description
The algorithm is described in the article [ABACUS](https://www.date-conference.com/files/proceedings/2014/pdffiles/12.5_2.pdf)

It can be compiled with cmake, which will also compile some unit test.
```
mkdir build
cd build
cmake ../src
make
make test
```
The output of the program will be a detailed report about the approximation applied, accuracy obtained and the shifts applied by the approximations.

###args
The program takes some inputs which must all specified.
* File containing the algorithm to approximate: -f path/to/file
* Type of input data: -t [double|float|int]
* File containing input data: -i path/to/file
* Minimum accuracy to achieve: -a number
* Number of maximum approximation to apply: -N number
* Number of approximation to try at each iteration: -M number

Some benchmarks are provided as examples along with data.
```
./aapp -f ../benchmarks/perceptron.graph -t double -i ../benchmarks/inputs/perceptron_input6.txt -a 0.762 -N 10 -M 5
```

##Description of input algorithm
Every instruction must be translated in a way the program might understand it.
Every basic operation can be translated using the following template.
It is possible to cast data using the operation ```cast``` specifying as first parameter the type.
Also the absolute value is implemented with the ```abs``` and specifying both as first and second parameter the value or variable.
```
out_variable operation operand1 operand2
```

It is possible to use arrays using the following pattern: ```array_index```
Notice that the ```_``` could be used only for arrays and not for any other variables.
Moreover the there are some restricted arrays such as ```input``` and ```output```. The former should contain the input data and the latter should contain the output data to compare.

Some control structure are available, they employ the same pattern of a normal variables but with very specific output_variable.
```
_if operation operand1 operand2
# instructions
_elseif operation operand1 operand2
# instructions
_else
# instructions
_if
# this last if closes the structure

_for operation operand1 operand2
# instructions
_for
# closes loop
```

##Description of input data
The file containing the input data is far simpler than the one containing the algorithm.
Each variable can be filled with the following pattern:
```input_variable data```

You are invited to check the input samples for any doubts.
