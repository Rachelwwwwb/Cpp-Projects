# HW08 Grading Rubric

## Project Manual Functionality Tests (65%)

## Test 1 - INIT File (5%)

Each test case is independent of each other, and points are allocated based on the tasks a student succeeds in the "Point Distribution" section.

Tests may use different config files so make sure the input to the test is correct.

### 1.1 - First INIT File (2%)

```
./scrabble scrabble_configs/config_INIT_1.txt
1
human
```

+ __(1%)__ Game Loads with "ANTLERS" vertically from (5, 8) to (11, 8)
+ __(1%)__ "ANTLERS" tiles have scores of 1 each.

### 1.2 - Second INIT File (3%)

```
./scrabble scrabble_configs/config_INIT_2.txt
1
human
```

+ __(1.5%)__ Tiles have letters A-Z sequentially going around the board CounterClockwise
+ __(1.5%)__ Tiles have scores 0-9 sequentially going around the board CounterClockwise 


## Test 2 - CPUS Functionality Tests (15%)

Functionality tests are designed to test basic functionality of the Maximum Score CPU.

Each test case is independent of each other, and points are allocated based on the tasks a student succeeds in the "Point Distribution" section.

Tests may use different config files so make sure the input to the test is correct.

+ For each test the CPU must make a move in under __1 min__. Use a cellphone or online timer to time this.
+ If a student goes over this threshold, terminate their program and fail the test with "__TimeOut__"

### 2.1 - Move After Human Short Word (2%)

```
./scrabble scrabble_configs/config_BASE_1.txt
2
human
CPUS BOB
PLACE | 8 8 HI
```

+ __(2%)__ CPUS BOB makes a move that scores: 32 points
+ Possible Move: `PLACE | 7 9 WEFT` which forms 'WEFT'

### 2.2 - Move After Human Long Word (2%)

```
./scrabble scrabble_configs/config_BASE_1.txt
2
human
CPUS BOB
PLACE - 8 8 THULIA
```

+ __(2%)__ CPUS BOB makes a move that scores: 29 points
+ Possible Move: `PLACE - 9 11 FEW` which forms 'FEW'

### 2.3 - Move After INIT (2%)

```
./scrabble scrabble_configs/config_BASE_2.txt
2
CPUS BOB
human
```

+ __(2%)__ CPUS BOB makes a move that scores: 37 points
+ Possible Move: `PLACE - 10 4 HAZE` which forms 'HAZER'

### 2.4 - Move After INIT And Human (2%)

```
./scrabble scrabble_configs/config_BASE_2.txt
2
human
CPUS BOB
PLACE - 8 5 MEA
```

+ __(2%)__ CPUS BOB makes a move that scores: 39 points
+ Possible Move: `PLACE | 5 9 SEX" which forms 'SEX'

### 2.5 - Move After INIT With Many Multipliers (2%)

```
./scrabble scrabble_configs/config_BASE_3.txt
2
CPUS BOB
human
```

+ __(2%)__ CPUS BOB makes a move that scores: 144 points
+ Possible Move: `PLACE - 10 5 ZAIE` which forms 'ZAIRE'

### 2.6 - Move After INIT With One ? (2%)

Reminder that this tests should take 1 min or less.

```
./scrabble scrabble_configs/config_BASE_4.txt
2
CPUS BOB
human
```

+ __(2%)__ CPUS BOB makes a move that scores: 44 points
+ Possible Move: `PLACE - 10 6 HE?TZ` which forms 'HERTZ'

### 2.7 - Move After INIT With Two ? (3%)

Reminder that this tests should take 1 min or less.

```
./scrabble scrabble_configs/config_BASE_5.txt
2
CPUS BOB
human
```

+ __(3%)__ CPUS BOB makes a move that scores: 72 points
+ Possible Move: `PLACE - 5 2 C?AUSEW?Y` which forms 'CAUSEWAY'

## Test 3 - CPUS Stress Tests (10%)

These are runtime tests for larger hands and ? tiles.

### 3.1 - HandSize 9 With One ? (2.5%)

Reminder that this tests should take 1 min or less.

```
./scrabble scrabble_configs/config_BASE_6.txt
2
CPUS BOB
human
```

+ __(2.5%)__ CPUS BOB makes a move that scores: 46 points
+ Possible Move: `PLACE - 11 2 ZEPHE?R` which forms 'ZEPHERS'

### 3.2 - HandSize 9 With Two ? (2.5%)

Reminder that this tests should take 1 min or less.

```
./scrabble scrabble_configs/config_BASE_7.txt
2
CPUS BOB
human
```

+ __(2.5%)__ CPUS BOB makes a move that scores: 48 points
+ Possible Move: `PLACE - 5 4 SCA?LW?AG` which forms 'SCALAWAG'

### 3.3 - HandSize 10 With One ? (2.5%)

Reminder that this tests should take 1 min or less.

```
./scrabble scrabble_configs/config_BASE_8.txt
2
CPUS BOB
human
```

+ __(2.5%)__ CPUS BOB makes a move that scores: 68 points
+ Possible Move: `PLACE - 5 4 EXPI?TED` which forms 'EXPIATED'
+ Possible Move: `PLACE - 5 5 EXP?NDER` which forms 'EXPANDER'

### 3.4 - HandSize 10 With Two ? (2.5%)

Reminder that this tests should take 1 min or less.

```
./scrabble scrabble_configs/config_BASE_9.txt
2
CPUS BOB
human
```

+ __(2.5%)__ CPUS BOB makes a move that scores: 64 points
+ Possible Move: `PLACE - 5 2 CAUSEWY?E?D` which forms 'CAUSEWAYED'

## Test 4 - CPUL Functionality Tests (15%)

Functionality tests are designed to test basic functionality of the Maximum Tile Placement (Length) CPU, which makes the move that places the maximum number of tiles in hand.

Each test case is independent of each other, and points are allocated based on the tasks a student succeeds in the "Point Distribution" section.

Tests may use different config files so make sure the input to the test is correct.

+ For each test the CPU must make a move in under __1 min__. Use a cellphone or online timer to time this.
+ If a student goes over this threshold, terminate their program and fail the test with "__TimeOut__"


### 4.1 - Move After Human Short Word (2%)

```
./scrabble scrabble_configs/config_BASE_1.txt
2
human
CPUL BOB
PLACE | 8 8 HI
```

+ __(2%)__ CPUS BOB makes a move that places: 5 tiles
+ Possible Move: `PLACE - 8 4 MENTE` which forms 'MENTHE'
+ Possible Move: `PLACE - 5 9 TWEEN` which forms 'TWEEN'

### 4.2 - Move After Human Long Word (2%)

```
./scrabble scrabble_configs/config_BASE_1.txt
2
human
CPUL BOB
PLACE - 8 8 THULIA
```

+ __(2%)__ CPUS BOB makes a move that places: 5 tiles
+ Possible Move: `PLACE - 7 6 TWEEN` which forms 'TWEEN'
+ Possible Move: `PLACE - 4 9 MENTE` which forms 'MENTHE'

### 4.3 - Move After INIT (2%)

```
./scrabble scrabble_configs/config_BASE_2.txt
2
CPUL BOB
human
```

+ __(2%)__ CPUS BOB makes a move that places: 5 tiles
+ Possible Move: `PLACE - 6 6 MEAIE` which forms 'MEANIE'
+ Possible Move: `PLACE | 10 7 MAIZE` which forms 'MAIZE'

### 4.4 - Move After INIT And Human (2%)

```
./scrabble scrabble_configs/config_BASE_2.txt
2
human
CPUL BOB
PLACE - 8 5 MEA
```

+ __(2%)__ CPUS BOB makes a move that places: 5 tiles
+ Possible Move: `PLACE - 6 5 AKEES` which forms 'AKENES'

### 4.5 - Move After INIT And Human With Many Multipliers (2%)

```
./scrabble scrabble_configs/config_BASE_3.txt
2
CPUL BOB
human
```

+ __(2%)__ CPUS BOB makes a move that places: 5 tiles
+ Possible Move: `PLACE - 6 6 MEAIE` which forms 'MEANIE'
+ Possible Move: `PLACE | 10 7 MAIZE` which forms 'MAIZE'

### 4.6 - Move After INIT And Human With One ? (2%)

Reminder that this tests should take 1 min or less.

```
./scrabble scrabble_configs/config_BASE_4.txt
2
CPUL BOB
human
```

+ __(2%)__ CPUS BOB makes a move that places: 6 tiles
+ Possible Move: `PLACE - 6 7 IHU?MED` which forms 'INHUMED'

### 4.7 - Move After INIT With Two ? (3%)

Reminder that this tests should take 1 min or less.

```
./scrabble scrabble_configs/config_BASE_5.txt
2
CPUL BOB
human
```

+ __(3%)__ CPUS BOB makes a move that places: 7 tiles
+ Possible Move: `PLACE - 5 2 C?AUSEW?Y` which forms 'CAUSEWAY'

## Test 5 - CPUL Stress Tests (10%)

These are runtime tests for larger hands and ? tiles.

### 5.1 - HandSize 9 With One ? (2.5%)

Reminder that this tests should take 1 min or less.

```
./scrabble scrabble_configs/config_BASE_6.txt
2
CPUL BOB
human
```

+ __(2.5%)__ CPUS BOB makes a move that places: 7 tiles
+ Possible Move: `PLACE - 8 4 PA?RAYZE` which forms 'PARALYZE'
+ Possible Move: `PLACE - 8 1 UPHEA?VA` which forms 'UPHEAVAL'

### 5.2 - HandSize 9 With Two ? (2.5%)

Reminder that this tests should take 1 min or less.

```
./scrabble scrabble_configs/config_BASE_7.txt
2
CPUL BOB
human
```

+ __(2.5%)__ CPUS BOB makes a move that places: 8 tiles
+ Possible Move: `PLACE | 8 7 ?E?SCUAGES` which forms 'ESCUAGES'
+ Possible Move: `PLACE - 5 2 CAUSEWY?E?D` which forms 'CAUSEWAYED'

### 5.3 - HandSize 10 With One ? (2.5%)

Reminder that this tests should take 1 min or less.

```
./scrabble scrabble_configs/config_BASE_8.txt
2
CPUL BOB
human
```

+ __(2.5%)__ CPUS BOB makes a move that places: 9 tiles
+ Possible Move: `PLACE - 5 0 ?VIPERIDE` which forms 'VIPERIDAE`

### 5.4 - HandSize 10 With Two ? (2.5%)

Reminder that this tests should take 1 min or less.

```
./scrabble scrabble_configs/config_BASE_9.txt
2
CPUL BOB
human
```

+ __(2.5%)__ CPUS BOB makes a move that places: 9 tiles
+ Possible Move: `PLACE - 5 2 CAUSEWY?E?D` which forms 'CAUSEWAYED'

## Test 6 - Longer Combined Game (10%)

For this test you will have to make a move by yourself so we can test a longer game.

### 6.1 - Human + CPUS + CPUL, 6 Moves Total (5%)

```
./scrabble scrabble_configs/config_LONG.txt
3
human
CPUS
CPUL
PLACE - 8 6 ?CHIMED
PASS
```

+ __(2.5%)__ After the first human move, CPUs make moves in under 1 min each. 
+ __(2.5%)__ After the second human move, CPUs make moves in under 1 min each.


### 6.2 - Human + CPUL + CPUS, 6 Moves Total (5%)

```
./scrabble scrabble_configs/config_LONG.txt
3
human
CPUL
CPUS
PLACE | 4 8 H?UMID
PASS
```

+ __(2.5%)__ After the first human move, CPUs make moves in under 1 min each. 
+ __(2.5%)__ After the second human move, CPUs make moves in under 1 min each.
