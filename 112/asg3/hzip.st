#!/afs/cats.ucsc.edu/courses/cmps112-wm/usr/smalltalk/bin/gst -f
"$Id: ghchen@ucsc.edu Gavin Chen 1492980"
"Count frequency of input characters"

nl := Character nl.

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


|readStdin|
readStdin := stdin next asInteger


freqtable := ZeroArray new: 256.
file := FileStream stdin. "get input file as input"



[file atEnd] whileFalse: [
   |ordChar|
   ordChar := Array new: 30
   ordChar := file nextLine asInteger. "get lines and process"
   freqtable incr: ordChar.
].

freqtable keysAndValuesDo: [:key :value |
   (value notNil and: [value > 0]) ifTrue: [
      stdout << 'freq[' << key asCharacter visible << ']=' << value
             << nl.
   ]
].

"TEST: echo aaaaaaaaaa bbbbb ccc | charfreq.st"