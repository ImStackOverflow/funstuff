#!/afs/cats.ucsc.edu/courses/cmps112-wm/usr/smalltalk/bin/gst -f
"$Id: ghchen@ucsc.edu Gavin Chen 1492980"


Character extend [
   isGraph [
      ^ (Character space < self) & (self <= $~)
   ]
   visible [
      self isGraph ifTrue: [^ '$', self asString]
                   ifFalse: [^ self asInteger printStringRadix: 16]
   ]
]

Object subclass: BitStream [
   |bitIndex byte myStream|
   BitStream class >> new: fileStream [
      |result|
      result := super new.
      result init: fileStream.
      ^result
   ]
   init: fileStream [
      myStream := fileStream.
      bitIndex := 1.
   ]
   nextBit [
      bitIndex = 1 ifTrue: [
         byte := myStream next.
         bitIndex := 9.
      ].
      bitIndex := bitIndex - 1.
      ^byte value bitAt: bitIndex
   ]
   atEnd [
      ^bitIndex = 1 and: [myStream atEnd]
   ]
   currByte [
      ^byte
   ]
]

Object subclass: Leaf [
   |char count|
   char [ ^ char ]
   count [ ^ count ]

   Leaf class >> new [
      self shouldNotImplement
   ]

   Leaf class >> new: aChar count: aCount [
      |result|
      result := super new.
      result setChar: aChar andCount: aCount.
      ^result
   ]

   setChar: aChar andCount: aCount [
      char := aChar.
      count := aCount.
   ]

   <= other [
      ^ (count < other count)
      | ((count = other count) & (char <= other char))
   ]

   printBase: aStream [
      ^ aStream << self class << '(' << char << ',' << count
   ]

   printOn: aStream [
      (self printBase: aStream) << ')'.
   ]

   inorder: visitor prefix: string [
      visitor value: char value: string value: count.
   ]

]


Leaf subclass: Tree [
   |left right|

   Tree class >> new: aChar count: aCount [
      self shouldNotImplement
   ]

   Tree class >> new: aChar count: aCount left: aLeft right: aRight [
      |result|
      result := super new: aChar count: aCount.
      result setLeft: aLeft andRight: aRight.
      ^ result
   ]

   setLeft: aLeft andRight: aRight [
      left := aLeft.
      right := aRight.
   ]

   printOn: aStream [
      (self printBase: aStream) << ',' << left << ',' << right << ')'.
   ]

   inorder: visitor prefix: string [
      left inorder: visitor prefix: string, '0'.
      right inorder: visitor prefix: string, '1'.
   ]

]

Character extend [
   isPrint [
      ^ (Character space <= self) & (self <= $~)
   ]
   visible [
      self isPrint ifTrue: [^ '$', self asString]
                   ifFalse: [^ self asInteger printStringRadix: 8]
   ]
]

Object subclass: ZeroArray [
   |theArray|

   ZeroArray class >> new [
      self shouldNotImplement.
   ]

   ZeroArray class >> new: size [
      |result|
      result := super new.
      result init: size.
      ^ result
   ]

   init: size [
      theArray := Array new: size.
   ]

   size [
      ^ theArray size.
   ]

   at: index [
      ^ theArray at: index + 1.
   ]

   at: index put: value [
      ^ theArray at: index + 1 put: value.
   ]

   incr: index [
      (self at: index) isNil
         ifTrue: [ self at: index put: 0].
      self at: index put: (self at: index) + 1.
   ]

   keysAndValuesDo: aBlock [
      (0 to: (self size) - 1) do: [:index |
         aBlock value: index value: (self at: index).
      ]
   ]

]

Eval [
|freqtable file arg flag|
freqtable := ZeroArray new: 256.
arg := Smalltalk arguments.
flag := 0.

"check input count"
(2 <= arg size) ifFalse: [ 
'need more inputs yo' displayNl.
ObjectMemory quit: 1 ].

"check input file"
poop := arg at: 2.
(File exists: poop) ifFalse: [ 
   'file dont exist bro' displayNl.
   ObjectMemory quit: 1 ].

file := FileStream open: poop mode: FileStream read.    
(3 = arg size) ifTrue: [
   "if 3 args, then output file specified"
   poop := arg at: 3.
   stdout := FileStream open: poop mode: FileStream write.
   ].

"set flag"   
poop := arg at: 1.
('-c' = poop) ifTrue: [
        flag := 3.].
('-t' = poop) ifTrue: [
      flag := 2.].
('-u' = poop) ifTrue: [
 flag := 1.].

(0 = flag) ifTrue: [
'not right arg bro' displayNl.
      ObjectMemory quit: 1 ].
"compression"
(2 <= flag) ifTrue:[
"generate compression tree"

"freq table"
   [file atEnd] whileFalse: [
      |ordChar index|
      ordChar := file nextLine asString. 
      "get lines and process"
      butt := ordChar size.
      1 to: butt do: [ :index |
      freqtable incr: (ordChar at: index) asInteger.
      ].
   ].
   freqtable incr: 255. "add EOF"

"priority queue"
   priority := SortedCollection new. 
   freqtable keysAndValuesDo: [:key :value |
      (value notNil and: [value > 0]) ifTrue: [
      |vagina|
        vagina := Leaf new: key asCharacter count: value asInteger.
        priority add: vagina.
        "add leafs into priority queue"
      ]
   ].
   
   priority sortBlock: [:a :b | 
    a count < b count].

"make tree"
   [1 = priority size] whileFalse: [
      |left right vagina|
      left := priority removeFirst.
      "left is smaller"
      right := priority removeFirst.
      vagina := Tree new: left char 
      count: left count + right count
      left: left right: right.
      "make tree"
      priority add: vagina.
      "add back into tree"
      priority sortBlock: [:a :b | 
      a count < b count].
      "resort"
   ].
].
(flag = 2) ifTrue: [
"just print tree mutherfucker"
   priority removeFirst inorder: [:char :string :count |
      stdout << char << '    ' << count
      << '    ' << string << Character nl.
      stdout flush.
   ] prefix: ''.
   ].

(flag = 3) ifTrue: [
"compress"
poop := arg at: 2.
file := FileStream open: poop mode: FileStream read.
   ordChar := file nextLine.
   stdinBits := BitStream new: file.
   [stdinBits atEnd] whileFalse: [
      stdout << stdinBits nextBit.
      stdout flush.
].
].

"decompress"
(flag = 1) ifTrue: [
   1 to: 100  do: [ :x |
   stdout << ' wassup my dude '.
   ].
].
]

