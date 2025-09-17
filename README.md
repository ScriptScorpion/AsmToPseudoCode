# ATPC(AsmToPseudoCode)
**ATPC** - is utility that helps convert Assembly code to more readable variant of Assembly called 'Pseudo code', example of this: `mov register, value` will be translated as `register = value`

## How compile:
  For compilation you need: `make`, `g++`
1. `git clone https://github.com/ScriptScorpion/AsmToPseudoCode/`
2. `cd AsmToPseudoCode`
3. `make`

## Usage:
1. create file with extension of ".s" or ".S" or ".asm" and paste in this file commands you need to convert
2. run `./pseudo your_file` (you get output in file with ".psc" extension) 


## TO-DO:
* Make support for AT&T syntax
* add support for `div` instruction
* add support for `[]` specifier
* add support for `()` specifier
