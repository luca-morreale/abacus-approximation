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
Many different version will be built, the difference between them will be listed below.
All of them, in different way, will output a detailed report about the approximations applied, accuracy obtained and the shifts applied by the approximations.

###args
Any program generated takes the following inputs, which must all specified:
* File containing the algorithm to approximate: -f path/to/file
* Type of input data: -t [double|float|int]
* File containing input data: -i path/to/file
* Minimum accuracy to achieve: -a number
* Number of maximum approximation to apply: -N number
* Number of approximation to try at each iteration: -M number

The 'aapp_fast' and 'aapp_repetition' require also the following parameter:
* Number of test that should be performed: -r number

Some benchmarks are provided as examples along with data.
```
./aapp_interpreted -f ../benchmarks/perceptron.graph -t double -i ../benchmarks/inputs/perceptron_input6.txt -a 0.762 -N 10 -M 5
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

##Application Versions
The following versions will be built:
* aapp_interpreted
* aapp_compiled
* aapp_repetition
* aapp_fast

All of the above version are based on the same algorithm, what changes is just the way the instruction are handled.
In the sections below will described how they behave.
All of this version will load the data and instruction at the beginning.

###aapp_interpreted
At runtime each instruction is interepreted and then executed.
At the end a report is presented, as described in the very first section.
This algorithm is the less efficient one.

###aapp_compiled
This version, as the name says, exploit compilation. Of each instruction a c version is generated in a file.
Each time a new version of the function has to be tested, a new file is generated. 
That file will contain all the instruction that are contained in the corresponging graph, but as said before in a compilable version. 
It is then compiled and then executed using system calls. 
The output of each test is written in an external file and then automatically handled by the application.
At the end all generated file will be deleted and a report is presented as the version above.
This version is more efficient than the previous one.

###aapp_repetition
This version is basically the same as the previous one. The only change applied has been done in order to handle several repetitions of the algorithm. Indeed this version can be seen as repeted run of the previuos version, this justify the additional argument required to launch the file.

###aapp_fast
This version exploits further compilation. A unique file is generated, compiled and executed.
That file contains both the algorithm to approximate and the algorithm that tries to approximate it.
Moreover it handles, also, the multiple run case; thus still only one program is executed. This is the main difference with respect to the previous one. 
