# Game Of Life

## Disclaimer

This is a variation of the famous game of life, it is written as an exercise,
it is not intended to be used as a working software.
*Disclaimer* : On my initial search to know what is :Game of Life" I saw the net is full of software projects. I **resisted** the temptation so this work is genuinely mine.

## Some considerations
 
* board can be templated with num of rows & columns,
* creatures have no state so we really could have create one of each kind and instantiate many pointers to the same prototype. 
* An array is used during play so empty cells are represented  and provide a simplest implementation and performance for a 100 cells board but at scale (HUGE board) memory can be a limitation in which case only existing creatures are represented but we do more search.
* the play() method is optimized for big number of turns
 instead of create and delete actual creatures on Heap
 a lightweight representation is manipulated
  till the last turn, then state is commited; this way we save many contstructor/destructor of temporary objects.
play() can be optimized for HUGE board with tradeoff of more searches
* we can optionally provide several play strategies and choose the best in runtime.

* parsing the json-like input is made ~quick & dirty~ instead of using Json::Reader for obvious time considerations.
also I used regular string and avoided handling wide string (with Unicode Characters 'LEFT/RIGHT SINGLE QUOTATION MARK' (U+2018) (U+2019)

* The DB part is written very roughly, almost like a mock, but I think we get the point ( for simplicity I made many assumptions like a single table etc ..) 

* There are definitely bugs in there :-)

### Prerequisites

git, make , gcc  (mysql is compiled from sources)

### Installing

a good old make

```
make
```

## Running the program

./myprog  // will use default input file input.txt

./myprog file.txt // will use file passed as argument 

### Output

basic output of json string representation & matric of b,f , u creatures
```
json: {'0':'b','1':'b','2':'u','3':'b','24':'f','35':'b','62':'u','7':'b','8':'b','9':'b'}

INITIAL:
b b u b       b b b

        f
          b


    u



```


## Built With
Windows Linux Subsystem, should behave as normal linux

## Acknowledgments
to Ami & Doody for this great exercise on which I spent some nice hours.
I call you ASAP.
