#!/afs/cats.ucsc.edu/courses/cmps112-wm/usr/smalltalk/bin/gst -f
"$Id: charfreq.st,v 1.6 2012-02-23 18:57:46-08 - - $"
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


freqtable := ZeroArray new: 256.
|ordChar dick butt|
dick := stdin nextLine.
butt := 'Hello World' splitOn: Character space.
stdout << butt.

"[stdin atEnd not] whileTrue: [
   |ordChar dick butt|
	dick := stdin next aschar.
	dick := dick splitOn: Character ' '.
		stdout << dick.
	
   ordChar := Array new: 15.
   ordChar at: 1 put: dick.
   ordChar inspect
   ordChar := ordChar splitOn: Character space.
   stdout << asCharacter ordChar at: 1.
   freqtable incr: ordChar.
].

freqtable keysAndValuesDo: [:key :value |
   (value notNil and: [value > 0]) ifTrue: [
      stdout << 'freq[' << key asCharacter visible << ']=' << value
             << nl.
   ]
]."

"TEST: echo aaaaaaaaaa bbbbb ccc | charfreq.st"
