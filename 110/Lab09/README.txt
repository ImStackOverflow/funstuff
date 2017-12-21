Gavin Chen 
Lab partner: Jason Ting
did: protocol.c and agent.c

For this lab we implemented 3 libraries each with their own concept. Protocol.c dealt with the idea of 
secure messaging and checksums. It showed how messages are encoded, albeit with an overly simplified 
example, and also how it is checked whether or not the whole message was transmitted successfully. 
Field.c was based on how to organize a field and keep track of data as for multiple boards/people. And 
finally, agent.c was an example of implementing and combining the libraries we wrote into a crude AI-
type algorithm that played the game.

The lab began by reading the lab manual. We both started by interpreting what we needed to do and
 devising an overall game plan before coding. From there we went to the header fields and descriptions 
to see what the specifics of what we needed to do was, and finally the last piece was the coding. In the 
end the coding was not terribly difficult. At this point the difficulties arise not from learning how to use 
the language but how to accomplish problems using the tools provided by C. if I were to do this lab again 
I would meet more often. There were some problems with writing agent.c as it implemented both 
libraries so both partners needed to know a bit about the others code. It was difficult as I was still coding 
protocol.c as we began agent.c.

In the end I was able to debug and get protocol.c working fully. The only piece we were unable to finish 
was agentRun() in agent.c. In the end we spent well over 25 hours collectively on this lab. it was a 
challenging lab, but I enjoyed writing the protocol.c functions as they not only incorporated everything 
we learned in the year, but also because it was easy to see how scalable the concepts were. Despite our 
relatively simplistic implementation, the ideas used for encryption, hashing, and standard message 
formatting seems to be an elegant solution to the challenge of digital communications. The grading 
seems well distributed as each partner had their fair stake in the lab. If there were one change I would
 say it would be to weight the library each person wrote when grading, so that the library written by the 
person was worth more to that person and vice versa. The lab manuals and header files were beneficial 
to a point, but the wording was unclear in some cases and could have been more simplistic. Examples of 
generating a hash would have been good.
