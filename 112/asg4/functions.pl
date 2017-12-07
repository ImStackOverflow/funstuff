% $Id: functions.pl,v 1.3 2016-11-08 15:04:13-08 - - $
% math for calculating distance

mathfns( X, List ) :-
   S is sin( X ),
   C is cos( X ),
   Q is sqrt( X ),
   List = [S, C, Q].

constants( List ) :-
   Pi is pi,
   E is e,
   Epsilon is epsilon,
   List = [Pi, E, Epsilon].

%
% functions.pl
%

% prolog version of not
not( X ) :- X, !, fail.
not( _ ).

%-----------------Conversions--------------------

% degrees/minutes -> radians

% convert degrees and minutes of arc to radians

rads( degmin( Deg, Min ), Radians ) :-
    Radians is (Deg + Min / 60) * pi / 180.

%-----------------Haversine 1--------------------

% haversine formula
haversine_distance( Lat1, Lon1, Lat2, Lon2, Distance ) :-
   Dlon is Lon2 - Lon1,
   Dlat is Lat2 - Lat1,
   Tmpa is sin( Dlat / 2 ) ** 2
      + cos( Lat1 ) * cos( Lat2 ) * sin( Dlon / 2 ) ** 2,
   Udist is 2 * atan2( sqrt( Tmpa ), sqrt( 1 - Tmpa )),
   Distance is 3961 * Udist.

%-----------------Haversine 2--------------------

% plug in converted units in order to find the distance
% takes the departure area and arrival area and plugs converted 
% units into the haversine_distance function to be calculated
% (Converted) returns the distance in radians
haversine_distance_radians( Dep, Arr, Distance ) :-
   airport( Dep, _, Lat1, Lon1 ),
   airport( Arr, _, Lat2, Lon2 ), 
   rads( Lat1, Rlat1 ),
   rads( Lon1, Rlon1 ),
   rads( Lat2, Rlat2 ),
   rads( Lon2, Rlon2 ),
   haversine_distance( Rlat1, Rlon1, Rlat2, Rlon2, Distance ). 
   
%-----------------Write Paths--------------------

% prints the flight path onto the console

writeallpaths( Node, Node ) :-
   write( Node ), write( ' is ' ), write( Node ), nl.
writeallpaths( Node, Next ) :-
   listpath( Node, Next, [Node], List, time(0, 0), [Penis] ),
   write( Node ), write( ' to ' ), write( Next ), write( ' is ' ),
   writepathA( List ),
   fail.
   
writepath( [] ) :-
   nl.
writepath( [Head|Tail] ) :-
   write( ' ' ), write( Head ), writepath( Tail ).


writepath1( [] ) :-
   nl.
writepath2( [] ) :- 
   nl.
   
writepathA( [Head|Tail] ) :-
   airport(Head, String, _, _),
   write( 'depart ' ), write( String ), writepathB( Tail ).

writepathB( [Head|Tail] ) :- 
   airport(Head, String, _, _), 
   write( 'arrive ' ), write( String ), writepathA( Tail ).
   

%-----------------Graph Paths--------------------

% find a path from one node to another.

listpath( Node, End, Outlist ) :-
   listpath( Node, End, [Node], Outlist ).

%base case for recursion
listpath( Node, Node, _, [Node], _, _ ).

%time is time of arrival
listpath( Node, End, Tried, [Node|List], Time, Tlist ) :-
   %addList(Time, Tlist),

   %nl,nl,write('at '), write(Node), write(' '), write(Time),nl,
   
   %find flights from current location
   flight( Node, Next, Flight_time ),
   %check that chosen flight hasnt been analyzed before
   not( member( Next, Tried )),
   %write(Node), write(' asshole'), nl,
   %check if chosen flight has reachable time
   
   %write('time before calc is '), write(Time), nl,   
   
   %add departure time of valid flight
   %[Time|Tlist],
   %write(' fuckermcfuck '),
   %compute arival time
   endtime( Node, Next, Time, Arrived),
   
   %write('poopymcbutthole'), nl,
   
   %search for next path
   is_in_time( Arrived, Flight_time),
   write('fliht was in time '), write(Node), write(Next), write(Flight_time), nl,
   %addList(Flight_Time, Tlist), 
   listpath( Next, End, [Next|Tried], List, Flight_time, [Arrived|Tlist] ).

%-----------------distance and time functions----------------


%computes arrival time
endtime( Arr, Dep, time(Hours, Min), time(Hhour, Hmin)) :-
   
   %write('current airpot is '), write(Arr), 
   %write(' to '), write(Dep), nl, 
    haversine_distance_radians(Dep, Arr, Result),
       %write('distance is '), write(Result), nl,
	%convert distance to time

	Res is (Result / 500) + (1/2),
   %write('travel time is '), write(Res), nl,
        %compute arrival time	

	
	Hmin is mod(round(Min + ((Res - floor(Res)) * 60)),60),
       %write('min is '), write(Hmin),nl,
       Hhour is Hours + floor(Res) + div(Hmin,60).
        %write('hours is'), write(Hhour),nl.

is_in_time( time(Rhours, Rmin), time(Dhours, Dmin)) :-
   Rhours < Dhours.
   
is_in_time( time(Rhours, Rmin), time(Dhours, Dmin)) :-
   Rhours = Dhours,
   Rmin < Dmin.
   
addList(time(Hours,Min), List) :-
   %write(Hours), write(Min), write(integer(Hours)),
   append([List], [Min], List).
   	
	


%-----------------Input Checks--------------------

% identical arguments
fly( Var, Var ) :-
   write('Error: Arguments Identical'),
   !, fail.

% correct input taken
fly( Dep, Arr ) :-
   airport(Dep, _, _, _),
   airport(Arr, _, _, _),
   writeallpaths( Dep, Arr ),
   nl, !.   