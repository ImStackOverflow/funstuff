(* $Id: bigint.ml,v 1.5 2014-11-11 15:06:24-08 - - $ *)

open Printf

module Bigint = struct

    type sign     = Pos | Neg
    type bigint   = Bigint of sign * int list
    let  radix    = 10
    let  radixlen =  1

    let car       = List.hd
    let cdr       = List.tl
    let map       = List.map
    let reverse   = List.rev
    let strcat    = String.concat
    let strlen    = String.length
    let strsub    = String.sub
    let zero      = Bigint (Pos, [])
	
	
	let trimZero penis = 
	   let penis = reverse penis
	     in let rec trimZero' vagina = 
		    match vagina with
			| []         -> []
			| 0::pussy   -> trimZero' pussy
			| dick       -> dick
		  in reverse (trimZero' penis)
	
	let rec compare' x y = 
	   if x = [] (*reached end of lists *)
	      then 0 (* numbers equal *)
		  else
		  (*check numerical value *)
		     let a = car x 
		     and b = car y
	         in match (a > b, a = b) with
	               | true, false    -> 1  (* a is bigger num *)
		           | false, false   -> 2 (*b is bigger num*)
		           | false, true    -> compare' (cdr x) (cdr y) 
				   | _, _           -> 3
		  (* go further down num *)
			     
	
	(* checks length of 2 lists
	   0 if first = second
	   1 if first > second
	   2 if second > first *)
	let compare x y = 
	    let a = List.length x
		and b = List.length y
		(*checks first using length *)
		in match (a > b, a = b) with
		   | true, false    -> 1
		   | false, false   -> 2
		   | false, true    ->
		   (*otherwise check numerical values *)
		      let x = reverse x
			  and y = reverse y 
			  in compare' x y
		   | _, _           -> 3
				 
    let charlist_of_string str = 
        let last = strlen str - 1
        in  let rec charlist pos result =
            if pos < 0
            then result
            else charlist (pos - 1) (str.[pos] :: result)
        in  charlist last []

    let bigint_of_string str =
        let len = strlen str
        in  let to_intlist first =
                let substr = strsub str first (len - first) in
                let digit char = int_of_char char - int_of_char '0' in
                map digit (reverse (charlist_of_string substr))
            in  if   len = 0
                then zero
                else if   str.[0] = '_'
                     then Bigint (Neg, to_intlist 1)
                     else Bigint (Pos, to_intlist 0)

    (*max line length = 69 *)
	let string_of_bigint (Bigint (sign, value)) =
        match value with
        | []    -> "0"
        | value -> let reversed = reverse value
                   in  strcat ""
                       ((if sign = Pos then "" else "-") ::
                        (map string_of_int reversed))
	  

    let rec add' list1 list2 carry = match (list1, list2, carry) with
        | list1, [], 0       -> list1 
        | [], list2, 0       -> list2
        | list1, [], carry   -> add' list1 [carry] 0
        | [], list2, carry   -> add' [carry] list2 0
        | car1::cdr1, car2::cdr2, carry ->
		(*if both lists have numbers to be added*)
          let sum = car1 + car2 + carry
		  (*add the digits and the carry*)
          in  sum mod radix :: add' cdr1 cdr2 (sum / radix)
          (* put in digit value and calculate carry with truncation *)

	let rec sub2' list1 list2 carry = 
	 (*list1 should always be longer *)
	    match (list1, list2, carry) with
        | list1, [], 0       -> list1 
        | list1, [], carry   -> sub2' list1 [1] 0
        | car1::cdr1, car2::cdr2, carry ->
        (*if both lists have numbers to be added*)
          let sum = car1 - car2 - carry
          in if sum < 0
          then sum + 10 :: sub2' cdr1 cdr2 1
          (* add 10 to sum and carry -1 *)
          else sum :: sub2' cdr1 cdr2 0
          (* cons on the result *)	  
        | [], list2, _       -> []
		(* if list2 is longer than list1 theres an error *)		  
		  
	let sub' neg2 value1 value2 = 
	    match (neg2, compare value1 value2) with
        | Pos, 1        -> Bigint (Pos, trimZero (sub2' value1 value2 0))
		(* a-b, a>b *)
		| Pos, 2        -> Bigint (Neg, trimZero (sub2' value2 value1 0))
		(* a-b, a<b *)
        | Neg, 1        -> Bigint (Neg, trimZero (sub2' value1 value2 0))
		(* b-a, a>b *)
        | Neg, 2        -> Bigint (Pos, trimZero (sub2' value2 value1 0))
		(* b-a, a<b *)
		| _, 0          -> Bigint (Pos, [0])
		(* numbers equal *)
		| _, _          -> Bigint (Neg, [0])
		
		
	 (* order is a - b *)
	let sub (Bigint (neg1, value1)) (Bigint (neg2, value2)) = 
        if neg1 <> neg2
		then Bigint (neg1, add' value1 value2 0)
		else sub' neg2 value1 value2

    let add (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
	    if neg1 = neg2 
		then Bigint (neg1, add' value1 value2 0)
		else match neg2 with  
		|Pos            -> sub' Neg value1 value2
        |Neg            -> sub' Pos value1 value2
   
    let rec mul' value1 value2 acumul =
	   match (value2, acumul) with
	   | [], _         -> acumul
         (* done multiplying return acumulator *)	   
	   | car::cdr, acumul   -> 
	      let operate = ( * ) car 
		  (* curry multiplicator *)
		  in let newSum = (map operate value1)
		  (* map multiplicator to list *)
	         and value1 = 0::value1
			 (* shift number *)
	         in  mul' value1 cdr (add' acumul newSum 0)
			 (* add acumulator and new list *)
	   
   
    let mul (Bigint (neg1, value1)) (Bigint (neg2, value2)) = 
	   if neg1 = neg2
	   then Bigint (Pos, mul' value1 value2 [0])
	   (*makes a positive # *)
	   else Bigint (Neg, mul' value1 value2 [0])
	   (*makes a negative # *)
	    

    let div = add

    let rem = add

	
	let rec pow' value1 value2 acumul = 
	    match value2 with
		| []         -> acumul
		| value2     -> 
		  pow' value1 (* pass in base *)
		  (trimZero (sub2' value2 [1] 0)) (* exp-- *)
		  (mul' acumul value1 [0]) (* accumulator *)
	
	(* b^a *)
    let pow (Bigint (neg1, value1)) (Bigint (neg2, value2)) = 
	   match (neg1, neg2, ((car value2) mod 2) = 0) with 
	   | _, Neg, _             -> zero
	   (* negative exponent fuck it *)
	   |Pos, _, _              -> Bigint (Pos, pow' value1 value2 [1])
	   (* positive base, othershit dont matter *)
	   |Neg, _, true           -> Bigint (Pos, pow' value1 value2 [1])
	   (* negative base but even exponent *)
	   |Neg, _, false          -> Bigint (Neg, pow' value1 value2 [1])
	   (* negative base odd exponent *)

end

