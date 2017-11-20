#!/afs/cats.ucsc.edu/courses/cmps112-wm/usr/smalltalk/bin/gst -f
"$Id: ghchen@ucsc.edu Gavin Chen 1492980"
"Count frequency of input characters"

nl := Character nl.

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
      visitor value: char value: string.
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

"Object subclass: #main [



]
commandLine 
Smalltalk arguments: 'nil -c -t -u'
do: [:opt :arg |
    opt = '-c' ifTrue: ['cunt ' displayNl].
	opt = '-t' ifTrue: ['twat ' displayNl].
	opt = '-u' ifTrue: ['umbilical cord ' displayNl].
	opt = 'nil' ifTrue []
	]
"
|readStdin freqtable file|
readStdin := stdin nextLine asString.
freqtable := ZeroArray new: 256.
file := FileStream open: readStdin mode: FileStream read. "get input file as input"

[file atEnd] whileFalse: [
   |ordChar index|
   ordChar := file nextLine asString. "get lines and process"
   butt := ordChar size.
   1 to: butt do: [ :index |
   freqtable incr: (ordChar at: index) asInteger.
   ].
].
freqtable incr: 256. "add EOF"

priority := SortedCollection new. 
freqtable keysAndValuesDo: [:key :value |
   (value notNil and: [value > 0]) ifTrue: [
    stdout << 'freq[' << key asCharacter visible << ']=' << value
             << nl.
      priority add: key.
   ]
].

priority sortBlock: [:a :b | 
(freqtable at: a) < (freqtable at: b)].
"sort based on frequency"

[0 = priority size] whileFalse: [
   priority last asCharacter printNl.
   priority removeLast.
].
priority inspect.

"TEST: echo aaaaaaaaaa bbbbb ccc | charfreq.st"
