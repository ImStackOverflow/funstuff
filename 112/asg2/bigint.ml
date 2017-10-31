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
	
	
	let rec compare' x y = 
	   if x = [] 
	      then false
		  else
		  (*check numerical value *)
		     let a = car x 
		     and b = car y
	         in match (a > b, a = b) with
	               | true, false    -> true  (* a is bigger num *)
		           | false, false   -> false (*b is bigger num*)
		           | false, true    -> compare' (cdr x) (cdr y) 
				   | _, _           -> false
		  (* go further down num *)
			     
	
	(* checks length of 2 lists
	   true if first > second
	   false if second >= first *)
	let compare x y = 
	    let a = List.length x
		and b = List.length y
		(*checks first using length *)
		in match (a > b, a = b) with
		   | true, false    -> true
		   | false, false   -> false
		   | false, true    ->
		   (*otherwise check numerical values *)
		      let x = reverse x
			  and y = reverse y 
			  in compare' x y
		   | _, _           -> false
				 
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

    let string_of_bigint (Bigint (sign, value)) =
        match value with
        | []    -> "0"
        | value -> let reversed = reverse value
                   in  strcat ""
                       ((if sign = Pos then "" else "-") ::
                        (map string_of_int reversed))


     let rec sub' list1 list2 carry = 
	 (*list1 should always be longer *)
	 match (list1, list2, carry) with
        | list1, [], 0       -> list1 
        | list1, [], carry   -> sub' list1 [1] 0
        | car1::cdr1, car2::cdr2, carry ->
        (*if both lists have numbers to be added*)
          let sum = car1 - car2 - carry
          in if sum < 0
          then sum + 10 :: sub' cdr1 cdr2 1
          (* add 10 to sum and carry -1 *)
          else sum :: sub' cdr1 cdr2 0
          (* cons on the result *)	  
        | [], list2, _       -> []
		(* if list2 is longer than list1 theres an error *)		  

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

	 (* order is a - b *)
	 let sub (Bigint (neg1, value1)) (Bigint (neg2, value2)) = 
        if neg1 <> neg2
		then Bigint (neg1, add' value1 value2 0)
		else 
		match (neg2, compare value1 value2) with
        | Pos, true         -> Bigint (Pos, sub' value1 value2 0)
		| Pos, false        -> Bigint (Neg, sub' value2 value1 0)
        | Neg, true         -> Bigint (Neg, sub' value1 value2 0)
        | Neg, false        -> Bigint (Pos, sub' value2 value1 0)		


    let add (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
	    if neg1 = neg2 
		then Bigint (neg1, add' value1 value2 0)
		else match (neg2, compare value1 value2) with
        | Neg, true         -> Bigint (Pos, sub' value1 value2 0)
        | Neg, false        -> Bigint (Neg, sub' value2 value1 0)
        | Pos, true         -> Bigint (Neg, sub' value1 value2 0)
        | Pos, false        -> Bigint (Pos, sub' value2 value1 0)	

    
	
   
    let mul = add

    let div = add

    let rem = add

    let pow = add

end
