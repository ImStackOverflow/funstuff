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
dm_rads( degmin( Degrees, Minutes ), Radians ) :-
    Radians is (Degrees + Minutes / 60) * pi / 180.

hm_mins( time(Hrs, Mins), Minutes) :-
   Hours is Hrs * 60 + Mins.

%-----------------Conversions--------------------
%-----------------Haversine 1--------------------

% haversine formula
haversine_distance( Lat1, Lon1, Lat2, Lon2, Distance ) :-
   Dlon is Lon2 - Lon1,
   Dlat is Lat2 - Lat1,
   Tmpa is sin( Dlat / 2 ) ** 2
      + cos( Lat1 ) * cos( Lat2 ) * sin( Dlon / 2 ) ** 2,
   Udist is 2 * atan2( sqrt( Tmpa ), sqrt( 1 - Tmpa )),
   Distance is 3961 * Udist.

%-----------------Haversine 1--------------------
%-----------------Haversine 2--------------------

% plug in converted units in order to find the distance
% takes the departure area and arrival area and plugs converted 
% units into the haversine_distance function to be calculated
% (Converted) returns the distance in radians
haversine_distance_radians( Dep, Arr, Distance ) :-
   airport( Dep, _, Lat1, Lon1 ),
   airport( Arr, _, Lat2, Lon2 ), 
   dm_rads( Lat1, Lat1_rads ),
   dm_rads( Lon1, Lon1_rads ),
   dm_rads( Lat2, Lat2_rads ),
   dm_rads( Lon2, Lon2_rads ),
   haversine_distance( Lat1_rads, Lon1_rads, Lat2_rads, Lon2_rads, Distance ).

%-----------------Haversine 2--------------------
%-----------------Write Paths--------------------

% prints the flight path onto the console

writeallpaths( Node, Node ) :-
   write( Node ), write( ' is ' ), write( Node ), nl.
writeallpaths( Node, Next ) :-
   listpath( Node, Next, [Node], List, time(0, 0), Penis ),
   write( Node ), write( ' to ' ), write( Next ), write( ' is ' ),
   writepath( List ),
   fail.

writepath( [] ) :-
   nl.
writepath( [Head|Tail] ) :-
   write( ' ' ), write( Head ), writepath( Tail ).

%-----------------Write Paths--------------------
%-----------------Graph Paths--------------------

% find a path from one node to another.

listpath( Node, End, Outlist ) :-
   listpath( Node, End, [Node], Outlist ).

%base case for recursion
listpath( Node, Node, _, [Node], _, _ ).

%time is time of arrival
listpath( Node, End, Tried, [Node|List], Time, Tlist ) :-

   nl,nl,write('at '), write(Node), write(' '), write(Time),nl,
   
   %find flights from current location
   flight( Node, Next, Flight_time ),
   %check that chosen flight hasnt been analyzed before
   not( member( Next, Tried )),
   %write(Node), write(' asshole'), nl,
   %check if chosen flight has reachable time
   
   write('time before calc is '), write(Time), nl,   
   
   %add departure time of valid flight
   %[Time|Tlist],
   %write(' fuckermcfuck '),
   %compute arival time
   endtime( Node, Next, Time, Arrived),
   
   write('poopymcbutthole'), nl,
   
   %search for next path
   is_in_time( Arrived, Flight_time),
   write('fliht was in time '), write(Node), write(Next),nl,
   listpath( Next, End, [Next|Tried], List, Flight_time, Arrived ).

%-----------------Graph Paths--------------------
%-----------------Gay shit ---------------------
%computes arrival time
endtime( Arr, Dep, time(Hours, Min), time(Hhour, Hmin)) :-
   write('current airpot is '), write(Arr), 
   write(' to '), write(Dep), nl, 
    haversine_distance_radians(Dep, Arr, Result),
       %write('distance is '), write(Result), nl,
	%convert distance to time

	Res is (Result / 500) + (1/2),
   %     write('travel time is '), write(Res), nl,
        %compute arrival time	

	
	Hmin is mod(round(Min + ((Res - floor(Res)) * 60)),60),
       %write('min is '), write(Hmin),nl,
       Hhour is Hours + floor(Res) + div(Hmin,60).
        %write('hours is'), write(Hhour),nl.

is_in_time( time(Rhours, Rmin), time(Dhours, Dmin)) :-
   Rhours < Dhours.
   
is_in_time( time(Rhours, Rmin), time(Dhours, Dmin)) :-
   write(Rhours), write(' '),  write(Rmin), write(' leaving: '), write(Dhours), write(' '),  write(Dmin),
   Rhours = Dhours,
   Rmin < Dmin.

printTime( time(Rhours, Rmin) ) :-
    write(Rhours), write('penis '),  write(Rmin). 
   
   	
	


%-----------------Input Checks--------------------

% identical arguments
fly( Var, Var ) :-
   write('Error: Identical arguments'),
   !, fail.

% correct input taken
fly( Dep, Arr ) :-
   airport(Dep, _, _, _),
   airport(Arr, _, _, _),
   writeallpaths( Dep, Arr ),
   nl, !.   
% no departure
fly( Dep, _ ) :-
   not(airport(Dep, _, _, _)),
   write('Error: No argument for arrival area'),
   !, fail.

% no arrival
fly( _, Arr ) :-
   not(airport(Arr, _, _, _)),
   write('Error: No argument for departure area'),
   !, fail.

