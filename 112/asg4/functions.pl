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

% returns the distance
haversine_distance_radians( Dep, Arr, Distance ) :-
   airport( Dep, _, Lat1, Lon1 ),
   airport( Arr, _, Lat2, Lon2 ), 
   rads( Lat1, Rlat1 ),
   rads( Lon1, Rlon1 ),
   rads( Lat2, Rlat2 ),
   rads( Lon2, Rlon2 ),
   haversine_distance( Rlat1, Rlon1, Rlat2, Rlon2, Distance ). 
   
%-----------------Write Paths--------------------

% prints the flight path

writeallpaths( Node, Node ) :-
   write( Node ), write( ' is ' ), write( Node ), nl.
writeallpaths( Node, Next ) :-
   listpath( Node, Next, [Node], List, time(0, 0), [] ),
   %write( Node ), write( ' to ' ), write( Next ), write( ' is ' ), 

   writeshit( List),
  fail. 
/*writepath( [] ) :-
   nl.
writepath( [Head|Tail] ) :-
   write( ' ' ), write( Head ), writepath( Tail ).
*/
writeshit( [] ) :- nl.

writeshit( [Arr, Dep |Tail]) :-
   !, flight(Arr, Dep, Time), !,
   airport(Arr, String, _, _), !,
   airport(Dep, Str, _, _), !,
   endtime(Arr, Dep, Time, Red),
    write('depart '), write(String), write('   '), 
   writeTime(Time), nl,
   
   write('arrive '), write(Str), write('   '), 
   writeTime(Red), nl,
   writeshit([Dep|Tail]),!.
   

%-----------------Graph Paths--------------------

% find a path from one node to another.

listpath( Node, End, Outlist ) :-
   listpath( Node, End, [Node], Outlist ).

%base case for recursion
listpath( Node, Node, _, [Node], _, _ ).

%time is time of arrival
listpath( Node, End, Tried, [Node|List], Time, Tlist ) :-
   %find flights from current location
   flight( Node, Next, Flight_time ),
   %check that chosen flight hasnt been analyzed before
   not( member( Next, Tried )),
   %check if chosen flight has reachable time
   
   %add departure time of valid flight
   %compute arival time
   endtime( Node, Next, Time, Arrived), 
   
   %search for next path
   is_in_time( Arrived, Flight_time),

   listpath( Next, End, [Next|Tried], List, Flight_time, Tlist ).

%-----------------distance and time functions----------------


%computes arrival time
endtime( Arr, Dep, time(Hours, Min), time(Hhour, Hmin)) :-
    haversine_distance_radians(Dep, Arr, Result),
    
    %convert distance to time
   Res is (Result / 500) + (1/2),
    
    %compute arrival time   
   Hmin is mod(round(Min + ((Res - floor(Res)) * 60)),60),
    Hhour is Hours + floor(Res) + div(Hmin,60).

is_in_time( time(Rhours, _), time(Dhours, _)) :-
   Rhours < Dhours.
   
is_in_time( time(Rhours, Rmin), time(Dhours, Dmin)) :-
   Rhours = Dhours,
   Rmin < Dmin.
   
addList(time(Hours,Min), M1) :-
  M1 is Min + Hours.
   
writeTime(time(Hours,Min)) :- 
   write(Hours), write(':'), write(Min).
      
   


%-----------------Input Checks--------------------

% identical arguments
fly( Var, Var ) :-
   write('Error: Arguments Identical or dont exist'),
   !, fail.

% correct input taken
fly( Dep, Arr ) :-
   airport(Dep, _, _, _),
   airport(Arr, _, _, _),
   writeallpaths( Dep, Arr ),
   nl, !, fail. 


fly( Dep, _ ) :-
   not(airport(Dep, _, _, _)),
   write('airports dont exist '), nl.
 
fly( _, Arr ) :-
   not(airport(Arr, _, _, _)),
   write('airports dont exist '), nl.
